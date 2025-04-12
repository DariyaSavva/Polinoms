#include "AVLtree.h"

AVLtree::Node* AVLtree::insert(Node* root, const string& key, const Polinom& value) {
    vector<Node**> path;
    Node** curr = &root;

    // ����� ����� ��� �������
    while (*curr != nullptr) {
        path.push_back(curr);
        if (key < (*curr)->data.key) {
            curr = &((*curr)->left);
        }
        else if (key > (*curr)->data.key) {
            curr = &((*curr)->right);
        }
        else {
            (*curr)->data.value = value;
            return root;
        }
    }

    *curr = new Node(Element(key, value));
    path.push_back(curr);

    // ���������� ����� � ������������
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
        Node* node = **it;
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = BalanceFactor(node);

        // ������������ ������� ������������
        if (balance > 1) { // ������ ��������� ����
            if (BalanceFactor(node->right) >= 0) { // LL ������
                **it = rotateLeft(node);
            }
            else { // RL ������
                node->right = rotateRight(node->right);
                **it = rotateLeft(node);
            }
        }
        else if (balance < -1) { // ����� ��������� ����
            if (BalanceFactor(node->left) <= 0) { // RR ������
                **it = rotateRight(node);
            }
            else { // LR ������
                node->left = rotateLeft(node->left);
                **it = rotateRight(node);
            }
        }
    }

    return root;
}

AVLtree::Node* AVLtree::remove(Node* root, const string& key) {
    vector<Node**> path;
    Node** curr = &root;

    // ����� ���� ��� ��������
    while (*curr != nullptr && (*curr)->data.key != key) {
        path.push_back(curr);
        if (key < (*curr)->data.key) {
            curr = &((*curr)->left);
        }
        else {
            curr = &((*curr)->right);
        }
    }

    if (*curr == nullptr) return root; // ���� �� ������

    // �������� ����
    if ((*curr)->left == nullptr || (*curr)->right == nullptr) {
        Node* temp = (*curr)->left ? (*curr)->left : (*curr)->right;
        if (temp == nullptr) {
            delete* curr;
            *curr = nullptr;
        }
        else {
            Node* old = *curr;
            *curr = temp;
            delete old;
        }
    }
    else {
        // ����� ������������ ���� � ������ ���������
        Node** minNode = &((*curr)->right);
        while ((*minNode)->left != nullptr) {
            path.push_back(minNode);
            minNode = &((*minNode)->left);
        }
        (*curr)->data = (*minNode)->data;
        delete* minNode;
        *minNode = nullptr;
    }

    // ���������� ����� � ������������
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
        Node* node = **it;
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = BalanceFactor(node);

        if (balance > 1) {
            if (BalanceFactor(node->right) >= 0) {
                **it = rotateLeft(node);
            }
            else {
                node->right = rotateRight(node->right);
                **it = rotateLeft(node);
            }
        }
        else if (balance < -1) {
            if (BalanceFactor(node->left) <= 0) {
                **it = rotateRight(node);
            }
            else {
                node->left = rotateLeft(node->left);
                **it = rotateRight(node);
            }
        }
    }

    return root;
}

AVLtree::Node* AVLtree::balance(Node* curr) {
    int bf = BalanceFactor(curr);

    if (bf > 1) { // ������ ��������� ����
        if (BalanceFactor(curr->right) >= 0) {
            return rotateLeft(curr);
        } else {
            curr->right = rotateRight(curr->right);
            return rotateLeft(curr);
        }
    } else if (bf < -1) { // ����� ��������� ����
        if (BalanceFactor(curr->left) <= 0) {
            return rotateRight(curr);
        } else {
            curr->left = rotateLeft(curr->left);
            return rotateRight(curr);
        }
    }

    return curr;
}

AVLtree::Node* AVLtree::rotateLeft(Node* x) {
    // �������� �� nullptr
    if (x == nullptr || x->right == nullptr) {
        return x; // ���������� ��������� ��������
    }

    Node* y = x->right;
    Node* T2 = y->left;

    // ���������� ��������
    y->left = x;
    x->right = T2;

    // ���������� �����
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

AVLtree::Node* AVLtree::rotateRight(Node* x) {
    // �������� �� nullptr
    if (x == nullptr || x->left == nullptr) {
        return x; // ���������� ��������� ��������
    }

    Node* y = x->left;
    Node* T2 = y->right;

    // ���������� ��������
    y->right = x;
    x->left = T2;

    // ���������� �����
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}
int AVLtree::getHeight(Node* N)
{
    if (N == nullptr) {
        return 0;
    }
    return N->height;
}

int AVLtree::BalanceFactor(Node* N) {
    if (N == nullptr) {
        return 0; 
    }
    return getHeight(N->right) - getHeight(N->left);
}

AVLtree::Node* AVLtree::findMinNode(Node* node)
{
    while (node->left) {
        node = node->left;
    }
    return node;
}

void AVLtree::clear(Node* node)
{
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

AVLtree::Node* AVLtree::clone(Node* node)
{
    if (node == nullptr) {
        return nullptr;
    }
    return new Node(node->data, clone(node->left), clone(node->right), node->height);
}



AVLtree::AVLtree(const AVLtree& other)
{
    root = clone(other.root);
}

AVLtree& AVLtree::operator=(const AVLtree& tr)
{
    if (this != &tr) {
        clear(root);
        root = clone(tr.root);
    }
    return *this;
}

AVLtree::~AVLtree()
{
    clear(root);
    root = nullptr;
}

AVLtree::Node* AVLtree::Insert(string key, Polinom value)
{
    if (Find(key)) throw "������������ ����";
    root = insert(root, key, value);
    return root;
}

AVLtree::Node* AVLtree::Delete(string key)
{
    root = remove(root, key);
    return root;
}

Polinom* AVLtree::Find(string key)
{
	Node* current = root;

	while (current != nullptr) {
		if (key == current->data.key) {
			return &current->data.value;
		}
		else if (key < current->data.key) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	return nullptr;
}
