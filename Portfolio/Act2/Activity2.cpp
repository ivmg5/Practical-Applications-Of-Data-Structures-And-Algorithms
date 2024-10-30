#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Structure to store a log entry.
struct LogEntry {
    string month;
    string day;
    string time;
    string ip;
    string description;
};

// Structure for a node in the Deque.
struct Node {
    LogEntry data;
    Node* next;
    Node* prev;
};

class DoubleEndedQueue {
private:
    Node* start;
    Node* end;

    // Function to split the doubly linked list into two halves and return the midpoint
    Node* split(Node* start) {
        Node* slow = start;
        Node* fast = start->next;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    // Function to merge two sorted lists into one sorted list
    Node* merge(Node* left, Node* right) {
        if (!left) return right;
        if (!right) return left;

        if (compareIPs(left->data.ip, right->data.ip) < 0) {
            left->next = merge(left->next, right);
            left->next->prev = left;
            left->prev = nullptr;
            return left;
        } else {
            right->next = merge(left, right->next);
            right->next->prev = right;
            right->prev = nullptr;
            return right;
        }
    }

    // MergeSort function adapted for doubly linked lists
    Node* mergeSort(Node* start) {
        if (!start || !start->next) return start;

        Node* middle = split(start);
        Node* middleNext = middle->next;

        middle->next = nullptr;

        Node* left = mergeSort(start);
        Node* right = mergeSort(middleNext);

        return merge(left, right);
    }

public:
    // Default constructor
    DoubleEndedQueue() : start(nullptr), end(nullptr) {}

    // Adds a new record to the end of the Deque
    void pushBack(const LogEntry& record) {
        Node* newNode = new Node{ record, nullptr, end };
        // If the list is empty
        if (!start) {
            start = newNode;
        }
        // If there are elements in the list
        if (end) {
            end->next = newNode;
        }
        end = newNode;
    }

    // Sorts the Deque by IP address
    void sortQueue() {
        start = mergeSort(start);
        // Update 'end' pointer after sorting
        while (end && end->next) {
            end = end->next;
        }
    }

    // Displays the sorted Deque
    void displayQueue() const {
        Node* current = start;
        // Iterates through all nodes and displays them
        while (current) {
            cout << current->data.month << " " << current->data.day << " " << current->data.time << " " << current->data.ip << " " << current->data.description << endl;
            current = current->next;
        }
    }

    // Searches and displays records within an IP range
    void searchByIPRange(const string& startIP, const string& endIP) {
        Node* current = start;
        // Iterates through all nodes and displays those within the specified IP range
        while (current) {
            if (compareIPs(current->data.ip, startIP) >= 0 && compareIPs(current->data.ip, endIP) <= 0) {
                cout << current->data.month << " " << current->data.day << " " << current->data.time << " " << current->data.ip << " " << current->data.description << endl;
            }
            current = current->next;
        }
    }

    // Saves the sorted Deque to a file
    void saveToFile(const string& filename) {
        ofstream file(filename);
        Node* current = start;
        // Iterates through all nodes and saves them to a file
        while (current) {
            file << current->data.month << " " << current->data.day << " " << current->data.time << " " << current->data.ip << " " << current->data.description << "\n";
            current = current->next;
        }
        file.close();
    }

    // Compares two IP addresses
    int compareIPs(const string& ip1, const string& ip2) const {
        vector<int> nums1 = splitIP(ip1);
        vector<int> nums2 = splitIP(ip2);
        // Compares each segment of the IPs
        for (int i = 0; i < 4; i++) {
            if (nums1[i] < nums2[i]) {
                return -1;
            }
            if (nums1[i] > nums2[i]) {
                return 1;
            }
        }
        return 0; // they are equal
    }

    // Splits an IP into its component numbers
    vector<int> splitIP(const string& ip) const {
        vector<int> numbers;
        stringstream ss(ip);
        string segment;
        // Splits the IP into segments by each dot
        while (getline(ss, segment, '.')) {
            numbers.push_back(stoi(segment));
        }
        return numbers;
    }
};

int main() {
    DoubleEndedQueue log;

    ifstream inputFile("log.txt");
    // Checks if the file opened correctly
    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    // Reads the file line by line
    while (getline(inputFile, line)) {
        istringstream iss(line);
        LogEntry record;

        iss >> record.month >> record.day >> record.time >> record.ip;
        getline(iss, record.description);

        log.pushBack(record);
    }
    inputFile.close();

    log.sortQueue();

    cout << "Log sorted by IP address:" << endl;
    log.displayQueue();

    string startIP, endIP;
    cout << "\nEnter the start IP: ";
    cin >> startIP;
    cout << "Enter the end IP: ";
    cin >> endIP;

    log.searchByIPRange(startIP, endIP);
    log.saveToFile("results.txt");

    return 0;
}
