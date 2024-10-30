#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Node for the linked list
struct Node {
    string logEntry;
    Node* next;

    // Constructor to initialize a node with a log entry
    // Complexity: O(1)
    Node(string log) : logEntry(log), next(nullptr) {}
};

// Linked list to store the records for each IP address
struct LinkedList {
    Node* head;
    int size;

    // Constructor to initialize an empty linked list
    // Complexity: O(1)
    LinkedList() : head(nullptr), size(0) {}

    // Adds a new record to the end of the list
    // Complexity: O(n) where n is the number of elements in the list
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

    // Displays all records in the list
    // Complexity: O(n) where n is the number of elements in the list
    void display() {
        Node* temp = head;
        while (temp) {
            cout << temp->logEntry << endl;
            temp = temp->next;
        }
    }

    // Destructor to free the memory of the nodes in the list
    // Complexity: O(n) where n is the number of elements in the list
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

// Structure to store information for each IP address in the Hash Table
struct IPInfo {
    string ip;
    int count;
    LinkedList logs;

    // Constructor to initialize IP information
    // Complexity: O(1)
    IPInfo(string ip) : ip(ip), count(0) {}
};

// Size of the Hash Table
const int HASH_TABLE_SIZE = 20000;

// Hash Table
IPInfo* hashTable[HASH_TABLE_SIZE];

// Hash function to convert an IP address to a table index
// Complexity: O(k) where k is the number of characters in the IP address
int hashFunction(string ip) {
    int hashValue = 0;
    for (char c : ip) {
        if (c != '.') {
            hashValue = (hashValue * 10 + c - '0') % HASH_TABLE_SIZE;
        }
    }
    return hashValue;
}

// Inserts or updates the information for an IP address in the Hash Table
// Complexity: O(1) on average, O(n) in the worst case if there are many collisions
void insertOrUpdate(string ip, string logEntry) {
    int index = hashFunction(ip);
    if (!hashTable[index] || hashTable[index]->ip != ip) {
        hashTable[index] = new IPInfo(ip);
    }
    hashTable[index]->count++;
    hashTable[index]->logs.add(logEntry);
}

// Displays the summary for a specific IP address
// Complexity: O(1) on average, O(n) in the worst case if there are many collisions
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

// Function to extract only the IP address, without the port
// Complexity: O(k) where k is the number of characters in the log entry
string extractIP(string logEntry) {
    stringstream ss(logEntry);
    string month, day, time, ipPort;
    ss >> month >> day >> time >> ipPort;
    size_t colonPos = ipPort.find(':');
    if (colonPos != string::npos) {
        return ipPort.substr(0, colonPos);
    }
    return ipPort; // Returns the whole string if ':' is not found
}

int main() {
    ifstream file("log.txt");
    string line, ip, logEntry;

    // Read and process each line in the file
    // Complexity: O(m * k) where m is the number of lines and k is the average line length
    while (getline(file, line)) {
        ip = extractIP(line); // Extract only the IP address, without the port
        logEntry = line; // Take the entire line as the log entry
        insertOrUpdate(ip, logEntry);
    }
    file.close();

    // Test: Print the summary for a specific IP address (example)
    string testIP = "10.15.175.237";
    printIPSummary(testIP);

    return 0;
}
