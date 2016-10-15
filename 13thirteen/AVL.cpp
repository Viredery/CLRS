#include <iostream>
#include <algorithm>
#include <list>

struct Node {
    int data;
    int height;
    Node *left;
    Node *right;
};

class AVL {
public:
    AVL();
    ~AVL();
    void Insert(int data);
    void Remove(int data);
    void PrintTree();
    Node* Search(int data);
private:
    Node *root;
    int GetHeight(Node* p);
    Node* Insert(Node* &tree, int data);
    Node* Remove(Node* &tree, Node* target);
    void Destroy(Node* tree);
    Node* Maximum(Node* tree);
    Node* Minimum(Node* tree);
    Node* LeftLeftRotation(Node* p);
    Node* RightRightRotation(Node* p);
    Node* LeftRightRotation(Node* p);
    Node* RightLeftRotation(Node* p);
};

AVL::AVL() {
    root = NULL;
}

AVL::~AVL() {
    Destroy(root);
}

void AVL::Destroy(Node* tree) {
    if (tree == NULL)
        return;
    Destroy(tree->left);
    Destroy(tree->right);
    delete tree;
}

void AVL::Insert(int data) {
    Insert(root, data);
}

Node* AVL::Insert(Node* &tree, int data) {
    if (tree == NULL) {
        tree = new Node;
        tree->data = data;
        tree->height = 1;
        tree->left = tree->right = NULL;
    } else if (data < tree->data) {
        tree->left = Insert(tree->left, data);
        if (GetHeight(tree->left) - GetHeight(tree->right) >= 2) {
	    if (data < tree->left->data)
	        tree = LeftLeftRotation(tree);
	    else
	        tree = LeftRightRotation(tree);
	}
    } else if (data > tree->data) {
        tree->right = Insert(tree->right, data);
        if (GetHeight(tree->right) - GetHeight(tree->left) >= 2) {
	    if (data > tree->right->data)
	        tree = RightRightRotation(tree);
	    else
	        tree = RightLeftRotation(tree);
	}
    } else
        std::cout << "插入元素重复" << std::endl;
    tree->height = std::max(GetHeight(tree->left), GetHeight(tree->right)) + 1;
    return tree;
}

void AVL::Remove(int data) {
    Node *target = Search(data);
    if (target == NULL)
        return;
    Remove(root, target);
}

Node* AVL::Remove(Node* &tree, Node* target) {
    if (tree == NULL || target == NULL)
        return NULL;
    if (target->data < tree->data) {
        tree->left = Remove(tree->left, target);
	if (GetHeight(tree->right) - GetHeight(tree->left) >= 2) {
	    Node *r = tree->right;
	    if (GetHeight(r->right) > GetHeight(r->left))
	        tree = RightRightRotation(tree);
	    else
	        tree = RightLeftRotation(tree);
	}
    } else if (target->data > tree->data) {
        tree->right = Remove(tree->right, target);
	if (GetHeight(tree->left) - GetHeight(tree->right) >= 2) {
	    Node *r = tree->left;
	    if (GetHeight(r->left) > GetHeight(r->right))
	        tree = LeftLeftRotation(tree);
	    else
	        tree = LeftRightRotation(tree);
	}
    } else {
        //'target->data' is equal to 'tree->data'
	if (tree->left != NULL && tree->right != NULL) {
            if (GetHeight(tree->left) > GetHeight(tree->right)) {
	        Node *maxNode = Maximum(tree->left);
		tree->data = maxNode->data;
		tree->left = Remove(tree->left, maxNode);
	    } else {
	        Node *minNode = Minimum(tree->right);
		tree->data = minNode->data;
		tree->right = Remove(tree->right, minNode);
	    }
	} else {
	    Node *tmp = tree;
	    tree = (tree->left != NULL) ? tree->left : tree->right;
	    delete tmp;
	}
        
    }
    if (tree != NULL)
        tree->height = std::max(GetHeight(tree->left), GetHeight(tree->right)) + 1;
    return tree;
}

Node* AVL::Search(int data) {
    Node *p = root;
    while (p != NULL) {
        if (p->data == data)
	    return p;
	else if (data < p->data)
	    p = p->left;
	else
	    p = p->right;
    }
    return NULL;
}

int AVL::GetHeight(Node *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

Node* AVL::Maximum(Node* tree) {
    if (tree == NULL)
        return NULL;
    Node *p = tree;
    while (p->right != NULL)
        p = p->right;
    return p;
}

Node* AVL::Minimum(Node* tree) {
    if (tree == NULL)
        return NULL;
    Node *p = tree;
    while (p->left != NULL)
        p = p->left;
    return p;
}

Node* AVL::LeftLeftRotation(Node *node) {
    Node *leftNode = node->left;
    node->left = leftNode->right;
    leftNode->right = node;
    
    node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
    leftNode->height = std::max(GetHeight(leftNode->left), GetHeight(leftNode->right)) + 1;
    
    return leftNode;
}

Node* AVL::RightRightRotation(Node *node) {
    Node *rightNode = node->right;
    node->right = rightNode->left;
    rightNode->left = node;

    node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
    rightNode->height = std::max(GetHeight(rightNode->left), GetHeight(rightNode->right)) + 1;
    
    return rightNode;
}

Node* AVL::LeftRightRotation(Node *node) {
    Node *leftNode = node->left;
    node->left = RightRightRotation(leftNode);
    return LeftLeftRotation(node);
}

Node* AVL::RightLeftRotation(Node *node) {
    Node *rightNode = node->right;
    node->right = LeftLeftRotation(rightNode);
    return RightRightRotation(node);
}

void AVL::PrintTree() {
    std::list<Node *> queue;
    if (root != NULL)
        queue.push_back(root);
    while(!queue.empty()) {
        Node *p = queue.front();
        queue.pop_front();
        if(p->left != NULL) {
            queue.push_back(p->left);
            std::cout << p->data << "->" << p->left->data << std::endl;
        }
        if(p->right != NULL) {
            queue.push_back(p->right);
            std::cout << p->data << "->" << p->right->data << std::endl;
        }
    }
    std::cout << std::endl;
}

int main() {
    AVL avl;
    avl.Insert(34);
    avl.Insert(23);
    avl.Insert(15);
    avl.Insert(98);
    avl.Insert(115);
    avl.Insert(28);
    avl.Insert(107);
    avl.PrintTree();
    avl.Remove(34);
    avl.PrintTree();
    avl.Remove(23);
    avl.PrintTree();
}
