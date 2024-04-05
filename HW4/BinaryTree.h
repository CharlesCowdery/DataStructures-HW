#pragma once
#include <string>
#include <math.h>
#include <ostream>
#include <ctype.h>
/* Exception Classes */
class valueDNE : public std::exception {
public:
    const char* what() {
        return "Value Not In Tree";
    }
};

class repeatValue : public std::exception {
public:
    const char* what() {
        return "Value already in Tree";
    }
};

/* Word Frequency Class */
class Word {
public:
    std::string word;
    int size;
    int count;

    Word() {
        word = "";
        size = 0;
    }
    Word(std::string w) {
        for (int i = 0; i < w.size(); i++) {
            w[i] = tolower(w[i]);
        }
        word = w;
        size = w.size();
        count = 1;
    }

    void inc() {
        count++;
    }

    char operator[](int v) {
        return word[v];
    }
    bool operator >(Word& right) {
        int index = 0;
        int min = std::min(right.size, size);
        while (index < min) {
            char c1 = word[index];
            char c2 = right[index];
            if (c1 > c2) return true;
            if (c2 > c1) return false;
            index++;
        }
        return false;
    }
    bool operator <(Word& right) {
        int index = 0;
        int min = std::min(right.size, size);
        while (index < min) {
            char c1 = word[index];
            char c2 = right[index];
            if (c1 < c2) return true;
            if (c2 < c1) return false;
            index++;
        }
        return false;
    }
    bool operator ==(Word& right) {
        int index = 0;
        if (size != right.size) return false;
        while (index < size) {
            char c1 = word[index];
            char c2 = right[index];
            if (c2 != c1) return false;
            index++;
        }
        return true;
    }
};

/* Node Class */
template <typename T>
class Node {
public:
    T data;
    Node<T>* left;
    Node<T>* right;

    Node(T _data) {
        left = nullptr;
        right = nullptr;
        data = _data;
    };
    std::string to_string() {
        return std::to_string(data);
    }
};

/* Tree Class */
template <typename T>
class BinaryTree {
public:
    Node<T>* root = nullptr;
    BinaryTree() {}
    ~BinaryTree() {
        emptyTree();
    }

    void insert(T w) { //inserts a node starting at tree root
        Node<T>* w_node = new Node<T>(w);
        if (root == nullptr) {
            root = w_node;
            rebalance(&root);
            return 1;
        }
        else {
            int v = 1 + insert(w_node, root);
            rebalance(&root);
            return v;
        }
    }
    int insert(Node<T>* w, Node<T>* N) {
        //checks which node path is appropriate, if it exists, it propogates the function down that path.
        //Otherwise, it sets that child pointer to the node
        //if it finds a node with value equal to the node were trying to insert, it errors out
        if (w->data > N->data) {
            if (N->right != nullptr)return 1 + insert(w, N->right);
            else N->right = w;
        }
        if (w->data < N->data) {
            if (N->left != nullptr)return 1 + insert(w, N->left);
            else N->left = w;
        }
        if (w->data == N->data) {
            delete w;
            throw repeatValue();
        }
    }
    Node<T>* find(T v) {
        if (root == nullptr) return nullptr;
        return find(v, root);
    }
    Node<T>* find(T v, Node<T>* N) {
        if (N->data == v) return N; //if node is value return
        if (v > N->data && N->right != nullptr) return find(v, N->right);   //checks if child exists and searches down it if appropriate
        if (v < N->data && N->left != nullptr) return find(v, N->left);
        return nullptr;
    };
    int size() {
        return size(root);
    }
    int size(Node<T>* N) {
        if (N == nullptr) return 0;
        return 1 + size(N->left) + size(N->right); //recurses down the tree, with each node adding one to size
    }
    Node<T>** getAllAscending() {
        return getAllAscending(root);
    }
    Node<T>** getAllAscending(Node<T>* N) {
        Node<T>** arr = (Node<T>**) malloc(sizeof(Node<T>*) * size()); //init array
        int position = 0; //init position increment variable
        if (root == nullptr) return arr;
        getAllAscending(N, arr, position);
        return arr;
    }
    void getAllAscending(Node<T>* N, Node<T>** arr, int& position) {
        if (N->left != nullptr) { //if left exists, add all nodes on left first
            getAllAscending(N->left, arr, position);
        }
        arr[position] = N; //then add self and increment
        position++;
        if (N->right != nullptr) { //if right exists add all nodes on right last
            getAllAscending(N->right, arr, position);
        }
    };
    Node<T>** getAllDescending() {
        return getAllDescending(root);

    }
    Node<T>** getAllDescending(Node<T>* N) {
        Node<T>** arr = (Node<T>**) malloc(sizeof(Node<T>*) * size()); //refer to ascending. Order of child traversal is reversed.
        int position = 0;
        if (root == nullptr) return arr;
        getAllDescending(N, arr, position);
        return arr;
    }
    void getAllDescending(Node<T>* N, Node<T>** arr, int& position) {
        if (N->right != nullptr) {
            getAllDescending(N->right, arr, position);
        }
        arr[position] = N;
        position++;
        if (N->left != nullptr) {
            getAllAscending(N->left, arr, position);
        }
    };
    int nodeHeight() {
        return nodeHeight(root);
    }
    int nodeHeight(Node<T>* N) {
        int height = 0;
        if (N == nullptr) return -1;
        if (N->left != nullptr) height = std::max(height, nodeHeight(N->left) + 1);
        if (N->right != nullptr) height = std::max(height, nodeHeight(N->right) + 1); // if right has more height it will override left
        return height;
    }
    void emptyTree() {
        emptyTree(&root);
    }
    void emptyTree(Node<T>** N) {
        if (N == nullptr) return; //ensures repeat calls will not crash due to trying to deallocate a nullptr root
        if ((*N)->left != nullptr) emptyTree(&((*N)->left));//empty children if they exists
        if ((*N)->right != nullptr) emptyTree(&((*N)->right));
        delete* N;
        (*N) = nullptr;
    }
    Node<T>** swap_next(Node<T>** socket, Node<T>** here) {
        if ((*here)->left == nullptr) {
            Node<T>* temp = *here;
            Node<T>* t_socket = *socket;
            Node<T>* temp_c = temp->right;
            *here = *socket;
            *socket = temp;
            (*socket)->left = t_socket->left;
            (*socket)->right = t_socket->right;
            (*here)->right = temp_c;
            return here;
        }
        else {
            return swap_next(socket, &((*here)->left));

        }
    }
    int remove(T w) {
        return remove(w, &root);
    }
    int remove(T w, Node<T>** socket) {
        if ((*socket)->data == w) {
            Node<T>* t = (*socket);
            if ((*socket)->left == nullptr) {
                (*socket) = (*socket)->right;
                rebalance();
                return 1;
            }
            if ((*socket)->right == nullptr) {
                (*socket) = (*socket)->left;
                rebalance();
                return 1;
            }
            Node<T>** final_spot = swap_next(socket, &((*socket)->right));

            (*final_spot) = (*final_spot)->right;
            return 1;
        }
        if (w > (*socket)->data) 1+remove(w, &((*socket)->right));
        if (w < (*socket)->data) 1+remove(w, &((*socket)->left));
    }
    void rebalance() {
        rebalance(&root);
    }
    int bf(Node<T>* N) {
        return nodeHeight(N->left) - nodeHeight(N->right);
    }
    void rebalance(Node<T>** socket) {
        bool cont = true;
        while (cont == true) {
            cont = false;
            Node<T>* node = *socket;
            bool l_exist = node->left != nullptr;
            bool r_exist = node->right != nullptr;

            if (l_exist) rebalance(&(node->left));
            if (r_exist) rebalance(&(node->right));
            int dl = nodeHeight(node->left);
            int dr = nodeHeight(node->right);
            while (dr - dl > 1) {
                rotateLeft(node, socket);
                dl = nodeHeight((*socket)->left);
                dr = nodeHeight((*socket)->right);
                cont = true;
            }
            while (dl - dr > 1) {
                rotateRight(node, socket);
                dl = nodeHeight((*socket)->left);
                dr = nodeHeight((*socket)->right);
                cont = true;
            }
        }
    }
    void rotateRight(Node<T>* N, Node<T>** socket) {
        if (N->left->right != nullptr) {
            if (N->left->left == nullptr || nodeHeight(N->left->left) < nodeHeight(N->left->right)) {
                rotateLeft(N->left, &(N->left));
                return;
            }
        }
        (*socket) = N->left;
        N->left = nullptr;
        if ((*socket)->right == nullptr) {
            (*socket)->right = N;
            return;
        }

        N->left = (*socket)->right;
        (*socket)->right = N;
    }
    void rotateLeft(Node<T>* N, Node<T>** socket) {
        if (N->right->left != nullptr) {
            if (N->right->right == nullptr || nodeHeight(N->right->right) < nodeHeight(N->right->left)) {
                rotateRight(N->right, &(N->right));
                return;
            }
        }
        (*socket) = N->right;
        N->right = nullptr;
        if ((*socket)->left == nullptr) {
            (*socket)->left = N;
            return;
        }
        N->right = (*socket)->left;
        (*socket)->left = N;
    }

};
