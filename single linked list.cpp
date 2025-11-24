#include <iostream> 
#include <string> 
using namespace std; 
 
class Node { 
public: 
    int trainNo; 
    string name; 
    string destination; 
    string gender; 
    string date; 
    Node* next; 
 
    Node(int p, string n, string t, string g, string d) { 
        trainNo = p; 
        name = n; 
        destination = t; 
        gender = g; 
        date = d; 
        next = NULL; 
    } 
}; 
 
class RailwayReservation { 
    Node* head; 
 
public: 
    RailwayReservation() { 
        head = NULL; 
    } 
 
    void insert() { 
        int trainNo; 
        string name, destination, gender, date; 
        cout << "\nEnter TrainNo: "; 
        cin >> trainNo; 
        cout << "Enter Passenger Name: "; 
        cin.ignore(); 
        getline(cin, name); 
        cout << "Enter Destination: "; 
        getline(cin, destination); 
        cout << "Enter Gender (Male/Female/Other): "; 
        getline(cin, gender); 
        cout << "Enter Reservation Date (DD/MM/YYYY): "; 
        getline(cin, date); 
 
        Node* newNode = new Node(trainNo, name, destination, gender, date); 
 
        if (head == NULL) { 
            head = newNode; 
        } else { 
            newNode->next = head; 
            head = newNode; 
        } 
 
        cout << "Reservation Added Successfully!\n"; 
    } 
 
    void update() { 
        int trainNo; 
        cout << "\nEnter TrainNo to Update: "; 
        cin >> trainNo; 
 
        Node* temp = head; 
        while (temp != NULL) { 
            if (temp->trainNo == trainNo) { 
                cout << "Enter New Passenger Name: "; 
                cin.ignore(); 
                getline(cin, temp->name); 
                cout << "Enter New Destination: "; 
                getline(cin, temp->destination); 
                cout << "Enter New Gender: "; 
                getline(cin, temp->gender); 
                cout << "Enter New Date (DD/MM/YYYY): "; 
                getline(cin, temp->date); 
                cout << "Reservation Updated Successfully!\n"; 
                return; 
            } 
            temp = temp->next; 
        } 
        cout << "Reservation with TrainNo " << trainNo << " Not Found!\n"; 
    } 
 
    void search() { 
        int trainNo; 
        cout << "\nEnter TrainNo to Search: "; 
        cin >> trainNo; 
 
        Node* temp = head; 
        while (temp != NULL) { 
            if (temp->trainNo == trainNo) { 
                cout << "Reservation Found:\n"; 
                cout << "TrainNo=" << temp->trainNo 
                     << ", Name=" << temp->name 
                     << ", Destination=" << temp->destination 
                     << ", Gender=" << temp->gender 
                     << ", Date=" << temp->date << endl; 
                return; 
            } 
            temp = temp->next; 
        } 
        cout << "Reservation with TrainNo " << trainNo << " Not Found!\n"; 
    } 
 
    void remove() { 
        int trainNo; 
        cout << "\nEnter trainNo to Delete: "; 
        cin >> trainNo; 
 
        Node* temp = head; 
        if (temp != NULL && temp->trainNo == trainNo) { 
            head = temp->next; 
            delete temp; 
            cout << "Reservation Deleted Successfully!\n"; 
            return; 
        } 
 
        Node* prev = NULL; 
        while (temp != NULL && temp->trainNo != trainNo) { 
            prev = temp; 
            temp = temp->next; 
        } 
 
        if (temp == NULL) { 
            cout << "Reservation with TrainNo" << trainNo << " Not Found!\n"; 
            return; 
        } 
 
        prev->next = temp->next; 
        delete temp; 
        cout << "Reservation Deleted Successfully!\n"; 
    } 
 
    void sort() { 
        if (head == NULL || head->next == NULL) return; 
 
        bool swapped; 
        do { 
            swapped = false; 
            Node* curr = head; 
 
            while (curr != NULL && curr->next != NULL) { 
                if (curr->trainNo > curr->next->trainNo) { 
                    swap(curr->trainNo, curr->next->trainNo); 
                    swap(curr->name, curr->next->name); 
                    swap(curr->destination, curr->next->destination); 
                    swap(curr->gender, curr->next->gender); 
                    swap(curr->date, curr->next->date); 
                    swapped = true; 
                } 
                curr = curr->next; 
            } 
        } while (swapped); 
 
        cout << "Reservations Sorted by TrainNo!\n"; 
    } 
 
    void display() { 
        if (head == NULL) { 
            cout << "No Reservations Found!\n"; 
            return; 
        } 
        cout << "\n=== Reservation List ===\n"; 
        Node* temp = head; 
        while (temp != NULL) { 
            cout << "[ TrainNo=" << temp->trainNo 
                 << ", Name=" << temp->name 
                 << ", Destination=" << temp->destination 
                 << ", Gender=" << temp->gender 
                 << ", Date=" << temp->date << "] -> "; 
            temp = temp->next; 
        } 
        cout << "NULL\n"; 
    } 
}; 
 
int main() { 
    RailwayReservation r; 
    int choice; 
 
    while (true) { 
        cout << "\n--- Railway Reservation System ---\n"; 
        cout << "1. Insert Reservation\n"; 
        cout << "2. Update Reservation\n"; 
        cout << "3. Search Reservation\n"; 
        cout << "4. Delete Reservation\n"; 
        cout << "5. Sort Reservations by PNR\n"; 
        cout << "6. Display All Reservations\n"; 
        cout << "7. Exit\n"; 
        cout << "Enter Your Choice: "; 
        cin >> choice; 
 
        switch (choice) { 
            case 1: r.insert(); break; 
            case 2: r.update(); break; 
            case 3: r.search(); break; 
            case 4: r.remove(); break; 
            case 5: r.sort(); break; 
            case 6: r.display(); break; 
            case 7: 
                cout << "Exiting Program...\n"; 
                return 0; 
            default: cout << "Invalid Choice!\n"; 
        } 
    } 
 
    return 0; 
}
