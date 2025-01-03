/* Self-Balancing Binary Search Tree */

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct Node{
    int data;
    Node *LC; // left child
    Node *RC; // right child
    int height; // height of node (for AVL)
};

class AVLTree {
    private:
    Node *root; // pointer to root node of tree

    // Search Helper Function
    Node* search(Node* root, int key) {
        if (root == NULL || root->data == key) {
            return root; // return root, found or not found
        }
        if (key > root->data) { // key larger -> search right
            return search(root->RC, key);
        }
        return search(root->LC, key); // key smaller -> search left
    }

    /*
    // [BST] Insert Helper Function
    Node* insert(Node* node, int data) {
        if (node == NULL) { // insert node if NULL
            node = new Node{data, NULL, NULL};
        } else if (node->data > data) { // insert left if less than root
            node->LC = insert(node->LC, data);
        } else if (node->data < data) { // insert right if more than root
            node->RC = insert(node->RC, data);
        }
        return node;
    }

    // [BST] Remove Helper Function
    Node* remove(Node* node, int key){
        if (node == NULL) { return node; } // return if no nodes left to check

        if (key < node->data) { // key is smaller -> search left
            node->LC = remove(node->LC, key);
        } else if (key > node->data) { // key is larger -> search right
            node->RC = remove(node->RC, key);
        } else { // Key Found -> Removal Cases
            // Case 1 & 2: 0 or 1 child
            if (node->LC == NULL) { // LC empty, delete node, return RC
                Node *temp = node->RC;
                delete node;
                return temp;
            } else if (node->RC == NULL) { // RC empty, delete node, return LC
                Node *temp = node->LC;
                delete node;
                return temp;
            }
            // Case 3: 2 Children, get rightmost of left subtree
            Node* temp = rightmostNode(node->LC); // input left subtree -> find rightmost of that subtree
            node->data = temp->data; // switch node with rightmost of left subtree node
            node->LC = remove(node->LC, temp->data); // remove the rightmost of left subtree node
        }
        return node;
    }
    */

    // [AVL] Insert Node
    Node* insert(Node* node, int key) {
        // 1. Perform normal BST insertion
        if (node == NULL) {
            return(new Node{key, NULL, NULL, 0});
        } else if (key < node->data) {
            node->LC = insert(node->LC, key);
        } else if (key > node->data) {
            node->RC = insert(node->RC, key);
        } else { // Duplicate keys not allowed
            return node; 
        }
        // 2. Update height of ancestor node
        node->height = 1 + max(height(node->LC), height(node->RC));
        // 3. Get Balance Factor of this ancestor node to check whether this node became unbalanced
        int balance = getBalance(node);
        // If this node becomes unbalanced, there are 4 cases
        // (1) Left Left Case
        if (balance > 1 && key < node->LC->data) {
            return rightRotate(node);
        }
        // (2) Right Right Case
        if (balance < -1 && key > node->RC->data) {
            return leftRotate(node);
        }
        // (3) Left Right Case
        if (balance > 1 && key > node->LC->data) {
            node->LC = leftRotate(node->LC);
            return rightRotate(node);
        }
        // (4) Right Left Case
        if (balance < -1 && key < node->RC->data) {
            node->RC = rightRotate(node->RC);
            return leftRotate(node);
        }
        // Return the (unchanged) node pointer
        return node;
    }

    // [AVL] Delete Node from AVL Tree
    Node* remove(Node* node, int key) {
            // 1. Perform standard BST delete
            if (node == NULL) {
                return node;
            }
            if (key < node->data) {
                node->LC = remove(node->LC, key);
            } else if (key > node->data) {
                node->RC = remove(node->RC, key);
            } else {
                // Case 1 & 2: 0 or 1 child
                if (node->LC == NULL) {
                    Node *temp = node->RC;
                    delete node;
                    return temp;
                } else if (node->RC == NULL) {
                    Node *temp = node->LC;
                    delete node;
                    return temp;
                }
                // Case 3: 2 children, get rightmost of left subtree
                Node* temp = rightmostNode(node->LC);
                node->data = temp->data;
                node->LC = remove(node->LC, temp->data);
            }
            // If Tree had only one node, return
            if (node == NULL) { return node; }

            // 2. Update height of current node
            node->height = 1 + max(height(node->LC), height(node->RC));

            // 3. Get Balance Factor of this Node (check if became unbalanced)
            int balance = getBalance(node);

            // If this node becomes unbalanced, there are 4 cases
            // (1) Left Left Case
            if (balance > 1 && getBalance(node->LC) >= 0) {
                return rightRotate(node);
            }
            // (2) Left Right Case
            if (balance > 1 && getBalance(node->LC) < 0) {
                node->LC = leftRotate(node->LC);
                return rightRotate(node);
            }
            // (3) Right Right Case
            if (balance < -1 && getBalance(node->RC) <= 0) {
                return leftRotate(node);
            }
            // (4) Right Left Case
            if (balance < -1 && getBalance(node->RC) > 0) {
                node->RC = rightRotate(node->RC);
                return leftRotate(node);
            }
            return node;
        }

    // [AVL] Balancing Helper - Find Bigger Value
    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    // [AVL] Balancing Helper - Get Height of Node
    int height(Node *node) {
        if (node == NULL) { return -1; } // Null Node: BF = -1
        return node->height;
    }

    // [AVL] Balancing Helper - Get Balance Factor
    int getBalance(Node *node) {
        if (node == NULL) { return 0; } // Null Node: BF = 0
        return height(node->LC) - height(node->RC);
    }

    // [AVL] Balancing Helper - Left Rotate
    Node* leftRotate(Node *z) {
        Node *y = z->RC;
        Node *T2 = y->LC;
        // Perform Rotation
        y->LC = z;
        z->RC = T2;
        // Update Heights
        z->height = max(height(z->LC), height(z->RC))+1;
        y->height = max(height(y->LC), height(y->RC))+1;
        // Return New Root
        return y;
    }

    // [AVL] Balancing Helper - Right Rotate
    Node* rightRotate(Node *z) {
        Node *y = z->LC;
        Node *T3 = y->RC;
        // Perform Rotation
        y->RC = z;
        z->LC = T3;
        // Update Heights
        z->height = max(height(z->LC), height(z->RC))+1;
        y->height = max(height(y->LC), height(y->RC))+1;
        // Return New Root
        return y;
    }

    // [BST & AVL] Remove Helper Helper Function: Leftmost Node
    Node* rightmostNode(Node* node) {
        Node* current = node;
        // Loop down to find rightmost leaf
        while (current->RC != NULL) {
            current = current->RC;
        }
        return current;
    }

    // Helper function to Print Tree
    void printTree(Node* node, int space) {
        if (node == NULL) { return; } // Base case: if the node is null, return

        int nodeDistance = 10; // distance between nodes
        space += nodeDistance; // increase distance each recursive call, simualte depth
        
        printTree(node->RC, space); // Print Right Children First

        // Print current node after right children
        cout << endl; // New line for current node
        for (int i = nodeDistance; i < space; i++) { // i starts at spacing
            cout << " "; // prints spaces to read current depth
        }
        cout << node->data << endl; // print node

        printTree(node->LC, space); // Process Left Children
    }

    // Pre Order Traversal Helper: Root, Left, Right
    void preorder(Node *root) {
        if (root != NULL) {
            cout << root->data << " ";
            preorder(root->LC);
            preorder(root->RC);
        }
    }

    // In Order Traversal Helper: Left, Root, Right
    void inorder(Node *root) {
        if (root != NULL) {
            inorder(root->LC);
            cout << root->data << " ";
            inorder(root->RC);
        }
    }

    // Post Order Traversal Helper: Left, Right, Root
    void postorder(Node *root) {
            if (root != NULL) {
                postorder(root->LC);
                postorder(root->RC);
                cout << root->data << " ";
            }
        }

    public:
        AVLTree() {
            root = NULL;
        };

        // Search for Node in BST
        Node* search(int key) {
            return search(root, key);
        }

        // Insert Node into BST
        void insert(int data) {
            root = insert(root, data);
        }

        // Delete Node from BST
        void remove(int key) {
            root = remove(root, key);
        }
        
        // Print the BST
        void print() {
            printTree(root, 0);
        }

        // Pre Order Traversal: Root, Left, Right
        void preorder() {
            preorder(root);
        }

        // In Order Traversal: Left, Root, Right
        void inorder() {
            inorder(root);
        }

        // Post Order Traversal: Left, Right, Root
        void postorder() {
            postorder(root);
        }
};

int main() {
    AVLTree avl;
    string input;
    int extractedNum; 

    // User Input for Tree
    cout << "Enter integers separated by spaces to create the AVL tree: ";
    getline(cin, input);         // read a line of input
    stringstream ss(input);      // stringstream handles input
    while (ss >> extractedNum) { // insert each num into tree
        avl.insert(extractedNum);
    }

    // Drawing Tree
    cout << "\nDrawing AVL Tree:\n";
    avl.print();

    // Perform Traversals
    cout << "\nTesting Traversals:";
    cout << "\nPre-order traversal: ";
    avl.preorder();
    cout << "\nIn-order traversal: ";
    avl.inorder();
    cout << "\nPost-order traversal: ";
    avl.postorder();
    cout << endl;

    // Search Node
    cout << "\nEnter Integer to Search: ";
    cin >> extractedNum;
    Node* foundNode = avl.search(extractedNum);
    if (foundNode != NULL) { // found = not null
        cout << "\"" << extractedNum << "\" found.\n";
    } else {                 // not found
        cout << "\"" << extractedNum << "\" not found.\n";
    }

    // Delete Node
    cout << "\nEnter Integer Delete: ";
    cin >> extractedNum;
    avl.remove(extractedNum);
    cout << "Redrawing tree...\n";
    avl.print();

    return 0;
}
