#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

// Define a node for the BST
struct Node {
    std::string ip;
    int count;
    Node* left;
    Node* right;
};

// Creates a new node for the BST
Node* newNode(const std::string& ip) {
    Node* temp = new Node;
    temp->ip = ip;
    temp->count = 1;
    temp->left = temp->right = nullptr;
    return temp;
}

// Inserts an IP into the BST
Node* insert(Node* root, const std::string& ip) {
    if (!root) {
        return newNode(ip);
    }
    if (ip == root->ip) {
        root->count++;
    } else if (ip < root->ip) {
        root->left = insert(root->left, ip);
    } else {
        root->right = insert(root->right, ip);
    }
    return root;
}

// Traverses the BST and stores nodes in a vector
void storeBSTNodes(Node* root, std::vector<Node*>& nodes) {
    if (!root) return;
    storeBSTNodes(root->left, nodes);
    nodes.push_back(root);
    storeBSTNodes(root->right, nodes);
}

// Converts the BST to an AVL
Node* buildTreeUtil(std::vector<Node*>& nodes, int start, int end) {
    if (start > end) return nullptr;
    int mid = (start + end) / 2;
    Node* root = nodes[mid];
    root->left = buildTreeUtil(nodes, start, mid - 1);
    root->right = buildTreeUtil(nodes, mid + 1, end);
    return root;
}

Node* balanceTree(Node* root) {
    std::vector<Node*> nodes;
    storeBSTNodes(root, nodes);
    int n = nodes.size();
    return buildTreeUtil(nodes, 0, n - 1);
}

// Performs in-order traversal and writes to a .csv file
void inOrderExport(Node* root, std::ofstream& out) {
    if (!root) return;

    inOrderExport(root->left, out);
    out << root->ip << "," << root->count << "\n";
    inOrderExport(root->right, out);
}

// Searches for an IP in the BST and returns its frequency
int searchIPFrequency(Node* root, const std::string& ip) {
    while (root != nullptr) {
        if (ip == root->ip) {
            return root->count;
        } else if (ip < root->ip) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return 0;
}

int main() {
    std::ifstream file("log.txt");
    std::string line, ip;
    Node* root = nullptr;

    // Read file and add IPs to the BST
    while (getline(file, line)) {
        std::istringstream ss(line);
        std::string token;
        for (int i = 0; i < 4; ++i) {
            ss >> token;
        }
        ip = token.substr(0, token.find(":"));
        root = insert(root, ip);
    }

    // Convert BST to AVL and export to .csv
    root = balanceTree(root);
    std::ofstream out("output.csv");
    out << "IP,Frequency\n";
    inOrderExport(root, out);
    out.close();

    // Search for an IP entered by the user
    std::string userIP;
    std::cout << "Enter the IP in format XX.XX.XXX.XXX:XXXX: ";
    std::cin >> userIP;
    userIP = userIP.substr(0, userIP.find(":"));
    int frequency = searchIPFrequency(root, userIP);
    if (frequency > 0) {
        std::cout << "The IP " << userIP << " appears " << frequency << " times in the file." << std::endl;
    } else {
        std::cout << "The IP " << userIP << " was not found in the file." << std::endl;
    }

    file.close();
    return 0;
}
