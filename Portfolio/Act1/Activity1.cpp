// Import necessary libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Record Class to know what each line of the file contains
struct Record {
    string month; // variable for the month
    int day;    // variable for the day
    string time; // variable for the time
    string ip; // variable for the IP
    string reason; // variable for the reason
};

// Methods to compare records and see which month, day, and time is greater (in pairs)
bool compareRecords(const Record& a, const Record& b) {
    string months = "JanFebMarAprMayJunJulAugSepOctNovDec"; // variable for the months
    int monthA = months.find(a.month) / 3; // find the first month in the string
    int monthB = months.find(b.month) / 3; // find the second month in the string
    if (monthA != monthB) return monthA < monthB; // if they are different, return T or F to know which is greater
    if (a.day != b.day) return a.day < b.day; // same with the days
    return a.time < b.time; // time (implicit with the above)
}

void bubbleSort(vector<Record>& records) { // bubble sort method
    int n = records.size(); // variable for the size of the records
    for (int i = 0; i < n - 1; i++) { // loop to compare records for bubble sort
        for (int j = 0; j < n - i - 1; j++) { // " "
            if (compareRecords(records[j + 1], records[j])) { // if the next record is greater than the current, swap
                swap(records[j], records[j + 1]);
            }
        }
    }
}

bool inRange(const Record& record, const string& start, const string& end) { // method to check if the record is within the date range
    string months = "JanFebMarAprMayJunJulAugSepOctNovDec";
    istringstream issStart(start), issEnd(end); // variables for start and end dates, using the months string
    string startMonth, endMonth; // range of months (start and end)
    int startDay, endDay; // start and end dates (day, integer)
    issStart >> startMonth >> startDay; // input for start date
    issEnd >> endMonth >> endDay; // input for end date
    int monthA = months.find(record.month) / 3; // search the month in the record
    int startMonthIndex = months.find(startMonth) / 3; // find the start month index
    int endMonthIndex = months.find(endMonth) / 3; // find the end month index
    
    if (monthA < startMonthIndex || monthA > endMonthIndex) return false; // if the record month is less than the start month or greater than the end month, false (out of range)
    if (monthA == startMonthIndex && record.day < startDay) return false; // if the record month equals the start month but the day is before, false (out of range)
    if (monthA == endMonthIndex && record.day > endDay) return false; // if the record month equals the end month but the day is after, false (out of range)
    
    return true;
}

int main() {
    vector<Record> records; // vector of records
    
    ifstream file("log.txt"); // read log file
    string line; // variable for each line in the file
    while (getline(file, line)) { // loop to read each line in the file
        istringstream iss(line);
        Record record;
        iss >> record.month >> record.day >> record.time >> record.ip; // data input
        string remainder; // variable for the remainder of the line (not month, day, time, or IP)
        getline(iss, remainder); // read the rest of the line
        record.reason = remainder.substr(1);
        records.push_back(record); // add it to the records vector
    }
    
    bubbleSort(records); // sort records with Bubble Sort
    
    string dateStart, dateEnd; // variables for start and end dates
    cout << "Enter start date (Example: Aug 4): "; // request start date of search range
    getline(cin, dateStart); // receive user input
    cout << "Enter end date (Example: Oct 9): "; // request end date
    getline(cin, dateEnd); // receive user input
    
    cout << "Records between " << dateStart << " and " << dateEnd << ":\n"; // print "records between the given dates..."
    for (const auto& record : records) { // loop to print records between the given dates
        if (inRange(record, dateStart, dateEnd)) { // if data is within range, display it
            cout << record.month << " " << record.day << " " << record.time << " " << record.ip << " " << record.reason << endl;
        }
    }
    
    ofstream output("results.txt"); // output file
    for (const auto& record : records) { // loop to print records in the output file ("results.txt"); we are writing the new file
        output << record.month << " " << record.day << " " << record.time << " " << record.ip << " " << record.reason << endl;
    }
    
    return 0;
}
