# **Practical Applications of Data Structures and Algorithms**
> *A portfolio showcasing the application of data structures and algorithms to solve real-world problems.*

## **Introduction**
This repository contains the portfolio of activities completed in the Data Structures and Fundamental Algorithms course at [Tecnológico de Monterrey](https://tec.mx/). Each project is designed to address specific data management and algorithmic challenges, utilizing data structures to enhance computational efficiency and solve practical problems.

## **Project Description**
- **Main functionality:** Each activity in this portfolio leverages distinct data structures and algorithms, including sorting, searching, linked lists, binary trees, AVL trees, and hash tables. These implementations facilitate data processing, efficient searching, and optimized data management for applications like log file analysis and IP frequency tracking.
- **Technologies used:** C++ for the core algorithms and Python for data visualization, utilizing tools such as Visual Studio Code, Git, and GitHub.
- **Challenges faced:** Efficient handling and sorting of large datasets, memory management in linked lists, and balancing binary trees for optimal search times.
- **Future improvements:** Expand on the variety of data processing functions and optimize data structures to further reduce time complexity.

## **Activities Overview**

### Activity 1: Log Sorting and Filtering
This activity focuses on sorting and filtering records from a log file based on dates. Using a `Record` class to represent each entry, it employs the **Bubble Sort** algorithm to order records by month, day, and time. It allows users to define a date range and displays only the records within that range. The output is saved in a `results.txt` file, providing a filtered view of logs for analysis.

- **Key functions**: `bubbleSort` to sort entries, `inRange` to filter logs by date.
- **Objective**: Demonstrate basic sorting and filtering techniques on structured data using simple algorithms.

### Activity 2: Doubly Linked List with Sorting and Search by IP
In this activity, a **Double-Ended Queue (Deque)** is implemented using a doubly linked list structure, allowing efficient management of log entries by IP addresses. The list is sorted using a **Merge Sort** algorithm adapted for doubly linked lists, which optimizes searching by IP. Users can input an IP range to filter and display only the entries within that range. Additionally, the sorted list is saved in a `results.txt` file for future reference.

- **Key functions**: `mergeSort` for sorting linked list nodes, `searchByIPRange` for filtering by IP range.
- **Objective**: Explore linked list operations and implement advanced sorting and search algorithms to manage data efficiently.

### Activity 3: Frequency Analysis and AVL Tree Conversion
This activity utilizes a **Binary Search Tree (BST)** to track the frequency of unique IP addresses found in a log file. Each IP address is added to the tree, where it counts the occurrences. After the data is gathered, the BST is converted to an **AVL tree** (a balanced BST) to optimize search times. The program exports the IP frequency data into an `output.csv` file, which can then be visualized through Python histograms showing the most frequent IPs.

- **Key functions**: `insert` to add IPs to the BST, `balanceTree` to convert the BST to an AVL, and `inOrderExport` for exporting data.
- **Objective**: Demonstrate efficient data retrieval with binary trees, explore tree balancing with AVL conversions, and visualize results for frequency analysis.

### Activity 4: Hash Table with Linked Lists for IP Summaries
In this final activity, a **Hash Table** with separate chaining using linked lists is implemented to store and summarize logs by IP address. Each IP address is hashed into an index, where its log entries and access count are stored. The linked list structure attached to each IP allows efficient logging of each access. Users can enter an IP to retrieve a detailed summary of its access frequency and logs.

- **Key functions**: `hashFunction` for hashing IPs to table indices, `insertOrUpdate` to add or update IP data, and `printIPSummary` to display IP-specific data.
- **Objective**: Showcases the power of hash tables in handling large data efficiently and provides rapid lookups with IP-based summaries.

## **Table of Contents**
1. [Introduction](#introduction)
2. [Project Description](#project-description)
3. [Activities Overview](#activities-overview)
4. [Installation](#installation)
5. [Usage](#usage)
6. [License](#license)

## **Installation**
1. **Prerequisites:**
   - **C++ Compiler** - [Installation guide](https://gcc.gnu.org/install/)
   - **Python** (for data visualization) - [Download Python](https://www.python.org/downloads/)

2. **Clone the repository:**
   ```bash
   git clone https://github.com/ivmg5/Practical-Applications-Of-Data-Structures-And-Algorithms.git
   cd Practical-Applications-Of-Data-Structures-And-Algorithms
   ```

3. **Compile C++ files for each activity:**
   - Navigate to each activity folder, e.g., `Portfolio/Act1/`, and run:
     ```bash
     g++ Activity1.cpp -o Activity1
     ./Activity1
     ```

4. **Run Python scripts (if applicable):**
   ```bash
   python Portfolio/Act3/histogram.py
   ```

### **Configuration Options**
- **Debug Mode:** Set `DEBUG=true` in environment variables for verbose output.
- **Data Input:** Place input log files (e.g., `log.txt`) in the corresponding activity folders.

## **Usage**
Follow these basic steps for each activity:

1. **Run the desired activity program:** Each C++ file contains code specific to the activity's function (e.g., sorting logs, searching by IP range).
2. **Input required data:** Some activities may prompt for specific input such as date ranges or IP ranges.
3. **Review output files:** Results are saved in corresponding output files like `results.txt` or `output.csv` for analysis.

**Example usage:**
```cpp
// Run Activity 1 to sort and filter log entries based on dates
g++ Portfolio/Act1/Activity1.cpp -o Activity1
./Activity1
```

## **License**
This project is licensed under the MIT License.

[![Build Status](https://img.shields.io/badge/status-active-brightgreen)](#)
[![Code Coverage](https://img.shields.io/badge/coverage-80%25-yellowgreen)](#)
