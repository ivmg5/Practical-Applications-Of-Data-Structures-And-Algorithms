// Descripción: Programa que lee, ordena y busca registros por dirección IP en una bitácora.
// Autores: 
// Diego Ivan Morales Gallardo | A01643382
// Jorge Javier Blasquez Gonzalez | A01637706
// Christian Navarro | A01643903
// Fecha de creación: 2023-10-05

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Estructura para almacenar una entrada del log.
struct LogEntry {
    string mes;
    string dia;
    string hora;
    string ip;
    string descripcion;
};

// Estructura para un nodo en la Deque.
struct Node {
    LogEntry dato;
    Node* siguiente;
    Node* anterior;
};

class DoubleEndedQueue {
private:
    Node* inicio;
    Node* fin;

    // Función que divide la lista doblemente ligada en dos mitades y devuelve el punto medio
    Node* split(Node* inicio) {
        Node* slow = inicio;
        Node* fast = inicio->siguiente;

        while (fast != nullptr && fast->siguiente != nullptr) {
            slow = slow->siguiente;
            fast = fast->siguiente->siguiente;
        }

        return slow;
    }

    // Función que fusiona dos listas ordenadas en una lista ordenada
    Node* merge(Node* left, Node* right) {
        if (!left) return right;
        if (!right) return left;

        if (compareIPs(left->dato.ip, right->dato.ip) < 0) {
            left->siguiente = merge(left->siguiente, right);
            left->siguiente->anterior = left;
            left->anterior = nullptr;
            return left;
        } else {
            right->siguiente = merge(left, right->siguiente);
            right->siguiente->anterior = right;
            right->anterior = nullptr;
            return right;
        }
    }

    // Función MergeSort adaptada para listas doblemente ligadas
    Node* mergeSort(Node* inicio) {
        if (!inicio || !inicio->siguiente) return inicio;

        Node* medio = split(inicio);
        Node* medioSiguiente = medio->siguiente;

        medio->siguiente = nullptr;

        Node* left = mergeSort(inicio);
        Node* right = mergeSort(medioSiguiente);

        return merge(left, right);
    }

public:
    // Constructor por defecto
    DoubleEndedQueue() : inicio(nullptr), fin(nullptr) {}

    // Agrega un nuevo registro al final del Deque
    void pushBack(const LogEntry& registro) {
        Node* nuevo = new Node{ registro, nullptr, fin };
        // Si la lista está vacía
        if (!inicio) {
            inicio = nuevo;
        }
        // Si hay elementos en la lista
        if (fin) {
            fin->siguiente = nuevo;
        }
        fin = nuevo;
    }

    // Ordena la Deque por dirección IP
    void sortQueue() {
        inicio = mergeSort(inicio);
        // Actualizar el puntero 'fin' después de ordenar
        while (fin && fin->siguiente) {
            fin = fin->siguiente;
        }
    }

    // Muestra la Deque ordenada
    void displayQueue() const {
        Node* actual = inicio;
        // Itera a través de todos los nodos y los muestra
        while (actual) {
            cout << actual->dato.mes << " " << actual->dato.dia << " " << actual->dato.hora << " " << actual->dato.ip << " " << actual->dato.descripcion << endl;
            actual = actual->siguiente;
        }
    }

    // Busca y muestra registros dentro de un rango de IPs
    void searchByIPRange(const string& inicioIP, const string& finIP) {
        Node* actual = inicio;
        // Itera a través de todos los nodos y muestra los que estén en el rango de IPs especificado
        while (actual) {
            if (compareIPs(actual->dato.ip, inicioIP) >= 0 && compareIPs(actual->dato.ip, finIP) <= 0) {
                cout << actual->dato.mes << " " << actual->dato.dia << " " << actual->dato.hora << " " << actual->dato.ip << " " << actual->dato.descripcion << endl;
            }
            actual = actual->siguiente;
        }
    }

    // Guarda la Deque ordenada en un archivo
    void saveToFile(const string& filename) {
        ofstream file(filename);
        Node* actual = inicio;
        // Itera a través de todos los nodos y los guarda en un archivo
        while (actual) {
            file << actual->dato.mes << " " << actual->dato.dia << " " << actual->dato.hora << " " << actual->dato.ip << " " << actual->dato.descripcion << "\n";
            actual = actual->siguiente;
        }
        file.close();
    }

    // Compara dos direcciones IP
    int compareIPs(const string& ip1, const string& ip2) const {
        vector<int> nums1 = splitIP(ip1);
        vector<int> nums2 = splitIP(ip2);
        // Compara cada segmento de las IPs
        for (int i = 0; i < 4; i++) {
            if (nums1[i] < nums2[i]) {
                return -1;
            }
            if (nums1[i] > nums2[i]) {
                return 1;
            }
        }
        return 0; // son iguales
    }

    // Divide una IP en sus números componentes
    vector<int> splitIP(const string& ip) const {
        vector<int> numeros;
        stringstream ss(ip);
        string segmento;
        // Divide la IP en segmentos por cada punto
        while (getline(ss, segmento, '.')) {
            numeros.push_back(stoi(segmento));
        }
        return numeros;
    }
};

int main() {
    DoubleEndedQueue bitacora;

    ifstream inputFile("bitacora.txt");
    // Verifica si el archivo se abrió correctamente
    if (!inputFile.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    string linea;
    // Lee el archivo línea por línea
    while (getline(inputFile, linea)) {
        istringstream iss(linea);
        LogEntry registro;

        iss >> registro.mes >> registro.dia >> registro.hora >> registro.ip;
        getline(iss, registro.descripcion);

        bitacora.pushBack(registro);
    }
    inputFile.close();

    bitacora.sortQueue();

    cout << "Bitácora ordenada por dirección IP:" << endl;
    bitacora.displayQueue();

    string inicioIP, finIP;
    cout << "\nIntroduce la IP de inicio: ";
    cin >> inicioIP;
    cout << "Introduce la IP de fin: ";
    cin >> finIP;

    bitacora.searchByIPRange(inicioIP, finIP);
    bitacora.saveToFile("resultado.txt");

    return 0;
}