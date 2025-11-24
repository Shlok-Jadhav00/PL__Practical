#include <iostream>
#include <string>
using namespace std;

struct Student {
    int rollNo;
    string name;
    float sgpa;
    string department;
};

// Bubble sort by roll number (Ascending)
void bubbleSort(Student s[], int n) {
    Student temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (s[i].rollNo > s[j].rollNo) {
                temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }
}

// Insertion sort by name (Alphabetical order)
void insertionSort(Student s[], int n) {
    Student temp;
    for (int i = 1; i < n; i++) {
        temp = s[i];
        int j = i - 1;
        while (j >= 0 && s[j].name > temp.name) {
            s[j + 1] = s[j];
            j--;
        }
        s[j + 1] = temp;
    }
}

// Quick sort by SGPA (for toppers)
int partition(Student s[], int low, int high) {
    float pivot = s[high].sgpa;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (s[j].sgpa > pivot) { // descending for toppers
            i++;
            swap(s[i], s[j]);
        }
    }
    swap(s[i + 1], s[high]);
    return i + 1;
}

void quickSort(Student s[], int low, int high) {
    if (low < high) {
        int pi = partition(s, low, high);
        quickSort(s, low, pi - 1);
        quickSort(s, pi + 1, high);
    }
}

// Linear search by SGPA
void linearSearchSGPA(Student s[], int n, float sgpa) {
    bool found = false;
    cout << "\nStudents with SGPA " << sgpa << ":\n";
    cout << "Roll No\tName\tSGPA\tDepartment\n";
    for (int i = 0; i < n; i++) {
        if (s[i].sgpa == sgpa) {
            cout << s[i].rollNo << "\t" << s[i].name << "\t"
                 << s[i].sgpa << "\t" << s[i].department << endl;
            found = true;
        }
    }
    if (!found)
        cout << "No student found with SGPA " << sgpa << endl;
}

// Binary search by name (non-recursive)
void binarySearchName(Student s[], int n, string name) {
    insertionSort(s, n); // ensure list sorted alphabetically
    int low = 0, high = n - 1;
    bool found = false;

    cout << "\nSearch results for name containing '" << name << "':\n";
    while (low <= high) {
        int mid = (low + high) / 2;
        if (s[mid].name == name) {
            cout << "Roll No\tName\tSGPA\tDepartment\n";
            for (int i = 0; i < n; i++) {
                if (s[i].name == name) {
                    cout << s[i].rollNo << "\t" << s[i].name << "\t"
                         << s[i].sgpa << "\t" << s[i].department << endl;
                }
            }
            found = true;
            break;
        } else if (s[mid].name < name)
            low = mid + 1;
        else
            high = mid - 1;
    }
    if (!found)
        cout << "No student found with name '" << name << "'\n";
}

// Fibonacci search to find and display all students from a given department
void fibonacciSearchDept(Student s[], int n) {
    string dept;
    cout << "Enter department to search: ";
    cin >> dept;

    bool found = false;
    cout << "\nStudents belonging to " << dept << " department:\n";
    cout << "Roll No\tName\tSGPA\tDepartment\n";

    int fib2 = 0;
    int fib1 = 1;
    int fib = fib2 + fib1;

    while (fib < n) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib2 + fib1;
    }

    int offset = -1;

    while (fib > 1) {
        int i = min(offset + fib2, n - 1);
        if (s[i].department < dept) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        } else if (s[i].department > dept) {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        } else {
            found = true;
            break;
        }
    }

    // display all students from the searched department
    for (int i = 0; i < n; i++) {
        if (s[i].department == dept) {
            cout << s[i].rollNo << "\t" << s[i].name << "\t"
                 << s[i].sgpa << "\t" << s[i].department << endl;
            found = true;
        }
    }

    if (!found)
        cout << "No student found in " << dept << " department.\n";
}

// Display all students
void display(Student s[], int n) {
    cout << "\nRoll No\tName\tSGPA\tDepartment\n";
    for (int i = 0; i < n; i++) {
        cout << s[i].rollNo << "\t" << s[i].name << "\t"
             << s[i].sgpa << "\t" << s[i].department << endl;
    }
}

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;
    Student s[n];

    for (int i = 0; i < n; i++) {
        cout << "Enter roll no, name, sgpa and department: ";
        cin >> s[i].rollNo >> s[i].name >> s[i].sgpa >> s[i].department;
    }

    int ch;
    do {
        cout << "\n\n--- STUDENT DATABASE MENU ---";
        cout << "\n1. Bubble Sort by roll no";
        cout << "\n2. Insertion Sort by Name";
        cout << "\n3. Quick Sort (Toppers)";
        cout << "\n4. Linear Search by SGPA ";
        cout << "\n5. Binary Search by Name ";
        cout << "\n6. Fibonacci Search by Department";
        cout << "\n7. Display All Students";
        cout << "\n8. Exit";
        cout << "\nEnter choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                bubbleSort(s, n);
                cout << "\n Bubble Sorted by Roll Number:\n";
                display(s, n);
                break;

            case 2:
                insertionSort(s, n);
                cout << "\nInsertion Sorted by Name:\n";
                display(s, n);
                break;

            case 3:
                quickSort(s, 0, n - 1);
                cout << "\nTop 10 Toppers:\n";
                cout << "Roll No\tName\tSGPA\tDepartment\n";
                for (int i = 0; i < n && i < 10; i++) {
                    cout << s[i].rollNo << "\t" << s[i].name << "\t"
                         << s[i].sgpa << "\t" << s[i].department << endl;
                }
                break;

            case 4: {
                float sgpa;
                cout << "Enter SGPA to search: ";
                cin >> sgpa;
                linearSearchSGPA(s, n, sgpa);
                break;
            }

            case 5: {
                string name;
                cout << "Enter name to search: ";
                cin >> name;
                binarySearchName(s, n, name);
                break;
            }

            case 6:
                fibonacciSearchDept(s, n);
                break;

            case 7:
                display(s, n);
                break;

            case 8:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }
    } while (ch != 8);

    return 0;
}
