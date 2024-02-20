/*
 * Descripción: Programa para leer un archivo de bitácora, extraer direcciones IP, 
 * construir un BST con ellas, convertirlo en AVL, y exportar las IPs y sus frecuencias 
 * a un archivo .csv.
 * Autor(es): Diego Ivan Morales Gallardo | A01643382, Jorge Javier Blasquez Gonzalez | A01637706, Christian Navarro | A01643903
 * Fecha de creación: 02/11/2023
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

// Definimos un nodo para el BST
struct Node {
    std::string ip;
    int count;
    Node* left;
    Node* right;
};

// Crea un nuevo nodo para el BST
Node* newNode(const std::string& ip) {
    Node* temp = new Node;
    temp->ip = ip;
    temp->count = 1;
    temp->left = temp->right = nullptr;
    return temp;
}

// Inserta una IP en el BST
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

// Recorre el BST y almacena nodos en un vector
void storeBSTNodes(Node* root, std::vector<Node*>& nodes) {
    if (!root) return;
    storeBSTNodes(root->left, nodes);
    nodes.push_back(root);
    storeBSTNodes(root->right, nodes);
}

// Convierte el BST a un AVL
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

// Realiza el recorrido in-order y escribe en un archivo .csv
void inOrderExport(Node* root, std::ofstream& out) {
    if (!root) return;

    inOrderExport(root->left, out);
    out << root->ip << "," << root->count << "\n";
    inOrderExport(root->right, out);
}

// Busca una IP en el BST y devuelve su frecuencia
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
    std::ifstream file("bitacora3.txt");
    std::string line, ip;
    Node* root = nullptr;

    // Leer archivo y agregar IPs al BST
    while (getline(file, line)) {
        std::istringstream ss(line);
        std::string token;
        for (int i = 0; i < 4; ++i) {
            ss >> token;
        }
        ip = token.substr(0, token.find(":"));
        root = insert(root, ip);
    }

    // Convertir BST a AVL y exportar al .csv
    root = balanceTree(root);
    std::ofstream out("output.csv");
    out << "IP,Frecuencia\n";
    inOrderExport(root, out);
    out.close();

    // Buscar una IP ingresada por el usuario
    std::string userIP;
    std::cout << "Ingrese la IP en formato XX.XX.XXX.XXX:XXXX: ";
    std::cin >> userIP;
    userIP = userIP.substr(0, userIP.find(":"));
    int frequency = searchIPFrequency(root, userIP);
    if (frequency > 0) {
        std::cout << "La IP " << userIP << " aparece " << frequency << " veces en el archivo." << std::endl;
    } else {
        std::cout << "La IP " << userIP << " no fue encontrada en el archivo." << std::endl;
    }

    file.close();
    return 0;
}
