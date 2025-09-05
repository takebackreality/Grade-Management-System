// YourName_Lab2.cpp — CSCI 272 Week 2 (Arrays + Function Overloading)
// Name: Mellad Sultani
// Date: September 9, 2025
// Purpose: Student Grade Management System using arrays and function overloading

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
using namespace std

const int MAX = 5; // max number of students

// ---------- Functions ----------

// Input n students’ names and grades
void inputGrades(int n, string NameArr[], double Score[][3]) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline
    for (int i = 0; i < n; i++) {
        cout << "Enter name of student " << i << ": ";
        getline(cin, NameArr[i]);
        for (int j = 0; j < 3; j++) {
            string subject;
            if (j == 0) subject = "Math";
            else if (j == 1) subject = "C Programming";
            else subject = "Operating Systems";

            double grade;
            while (true) {
                cout << "  Enter " << subject << " grade (0–100): ";
                cin >> grade;
                if (cin.fail() || grade < 0 || grade > 100) {
                    cout << "  Invalid grade. Try again.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } else {
                    Score[i][j] = grade;
                    break;
                }
            }
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // prepare for next name
    }
}

// Calculate one student’s total & average
void calculateStudent(int i, double Score[][3], double &total, double &avg) {
    total = Score[i][0] + Score[i][1] + Score[i][2];
    avg = total / 3.0;
}

// Find the top student index
int findTopStudent(int n, double Score[][3]) {
    int topIdx = 0;
    double topTotal = -1;
    for (int i = 0; i < n; i++) {
        double total, avg;
        calculateStudent(i, Score, total, avg);
        if (total > topTotal) {
            topTotal = total;
            topIdx = i;
        }
    }
    return topIdx;
}

// Overloading: print info for ONE student
void printInfo(string name, double scores[3]) {
    double total = scores[0] + scores[1] + scores[2];
    double avg = total / 3.0;
    cout << left << setw(15) << name
         << " Math: " << setw(6) << scores[0]
         << " C Prog: " << setw(6) << scores[1]
         << " OS: " << setw(6) << scores[2]
         << " Total: " << setw(6) << total
         << " Avg: " << setw(6) << avg
         << endl;
}

// Overloading: print info for ALL students
void printInfo(int n, string NameArr[], double Score[][3]) {
    for (int i = 0; i < n; i++) {
        printInfo(NameArr[i], Score[i]);
    }
}

// Part 1 (initial): display all (now delegates to overloaded function)
void displayAll(int n, string NameArr[], double Score[][3]) {
    // Original version would compute & print inline
    // Updated to reuse overloaded function
    printInfo(n, NameArr, Score);
}

// ------------------------------ main ------------------------------
int main() {
    string NameArr[MAX];
    double Score[MAX][3] = {}; // zero-initialize
    int n = 0;
    bool hasData = false;

    cout << fixed << setprecision(2);

    int choice;
    do {
        cout << "\n--- Menu ---\n"
             << "1) Record grades\n"
             << "2) Calculate one student's total & average\n"
             << "3) Display all students\n"
             << "4) Find top student\n"
             << "5) Exit\n"
             << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter number of students (1–" << MAX << "): ";
            cin >> n;
            if (cin.fail() || n <= 0 || n > MAX) {
                cout << "Invalid number of students.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            inputGrades(n, NameArr, Score);
            hasData = true;
            break;
        }
        case 2: {
            if (!hasData) {
                cout << "Please record grades first (option 1).\n";
                break;
            }
            int idx;
            cout << "Enter student index (0–" << n-1 << "): ";
            cin >> idx;
            if (cin.fail() || idx < 0 || idx >= n) {
                cout << "Invalid index.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            double total, avg;
            calculateStudent(idx, Score, total, avg);
            cout << "Student: " << NameArr[idx]
                 << " Total=" << total
                 << " Average=" << avg << endl;
            break;
        }
        case 3: {
            if (!hasData) {
                cout << "Please record grades first (option 1).\n";
                break;
            }
            displayAll(n, NameArr, Score);
            break;
        }
        case 4: {
            if (!hasData) {
                cout << "Please record grades first (option 1).\n";
                break;
            }
            int idx = findTopStudent(n, Score);
            double total, avg;
            calculateStudent(idx, Score, total, avg);
            cout << "Top student: " << NameArr[idx]
                 << " with Total=" << total
                 << " and Average=" << avg << endl;
            break;
        }
        case 5:
            cout << "Bye!\n"; break;
        default:
            cout << "Invalid choice. Try 1–5.\n";
        }
    } while (choice != 5);

    return 0;
}
