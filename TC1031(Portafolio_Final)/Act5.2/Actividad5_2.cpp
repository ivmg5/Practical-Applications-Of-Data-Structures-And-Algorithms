/**
 * Hash Table y Lista Ligada para procesar y resumir registros de bitácora
 * Autor: Diego Ivan Morales Gallardo A01643382, Christian Navarro García A01643903, Jorge Javier Blásquez A01637706
 * Fecha: 1 de Diciembre de 2023
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Nodo para la lista ligada
struct Node {
    string logEntry;
    Node* next;

    // Constructor para inicializar un nodo con una entrada de log
    // Complejidad: O(1)
    Node(string log) : logEntry(log), next(nullptr) {}
};

// Lista ligada para almacenar los registros de cada dirección IP
struct LinkedList {
    Node* head;
    int size;

    // Constructor para inicializar una lista ligada vacía
    // Complejidad: O(1)
    LinkedList() : head(nullptr), size(0) {}

    // Añade un nuevo registro al final de la lista
    // Complejidad: O(n) donde n es el número de elementos en la lista
    void add(string logEntry) {
        Node* newNode = new Node(logEntry);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        size++;
    }

    // Muestra todos los registros de la lista
    // Complejidad: O(n) donde n es el número de elementos en la lista
    void display() {
        Node* temp = head;
        while (temp) {
            cout << temp->logEntry << endl;
            temp = temp->next;
        }
    }

    // Destructor para liberar la memoria de los nodos de la lista
    // Complejidad: O(n) donde n es el número de elementos en la lista
    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }
};

// Estructura para almacenar la información de cada dirección IP en la Hash Table
struct IPInfo {
    string ip;
    int count;
    LinkedList logs;

    // Constructor para inicializar la información de una IP
    // Complejidad: O(1)
    IPInfo(string ip) : ip(ip), count(0) {}
};

// Tamaño de la Hash Table
const int HASH_TABLE_SIZE = 20000;

// Hash Table
IPInfo* hashTable[HASH_TABLE_SIZE];

// Función de hash para convertir una dirección IP a un índice de la tabla
// Complejidad: O(k) donde k es el número de caracteres en la dirección IP
int hashFunction(string ip) {
    int hashValue = 0;
    for (char c : ip) {
        if (c != '.') {
            hashValue = (hashValue * 10 + c - '0') % HASH_TABLE_SIZE;
        }
    }
    return hashValue;
}

// Inserta o actualiza la información de una dirección IP en la Hash Table
// Complejidad: O(1) en promedio, O(n) en el peor caso si hay muchas colisiones
void insertOrUpdate(string ip, string logEntry) {
    int index = hashFunction(ip);
    if (!hashTable[index] || hashTable[index]->ip != ip) {
        hashTable[index] = new IPInfo(ip);
    }
    hashTable[index]->count++;
    hashTable[index]->logs.add(logEntry);
}

// Muestra el resumen de una dirección IP específica
// Complejidad: O(1) en promedio, O(n) en el peor caso si hay muchas colisiones
void printIPSummary(string ip) {
    int index = hashFunction(ip);
    if (hashTable[index] && hashTable[index]->ip == ip) {
        cout << "IP: " << ip << "\nTotal Accesses: " << hashTable[index]->count << endl;
        cout << "Log Entries:" << endl;
        hashTable[index]->logs.display();
    } else {
        cout << "No records found for IP: " << ip << endl;
    }
}

// Función para extraer solo la dirección IP, sin el puerto
// Complejidad: O(k) donde k es el número de caracteres en la entrada del log
string extractIP(string logEntry) {
    stringstream ss(logEntry);
    string month, day, time, ipPort;
    ss >> month >> day >> time >> ipPort;
    size_t colonPos = ipPort.find(':');
    if (colonPos != string::npos) {
        return ipPort.substr(0, colonPos);
    }
    return ipPort; // Devuelve toda la cadena si no se encuentra ':'
}

int main() {
    ifstream file("bitacora3.txt");
    string line, ip, logEntry;

    // Leer y procesar cada línea del archivo
    // Complejidad: O(m * k) donde m es el número de líneas y k el tamaño promedio de una línea
    while (getline(file, line)) {
        ip = extractIP(line); // Extrae solo la dirección IP, sin el puerto
        logEntry = line; // Toma toda la línea como entrada del registro
        insertOrUpdate(ip, logEntry);
    }
    file.close();

    // Test: Imprimir el resumen de una dirección IP específica (ejemplo)
    string testIP = "10.15.175.237";
    printIPSummary(testIP);

    return 0;
}
