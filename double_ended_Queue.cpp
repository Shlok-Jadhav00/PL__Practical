#include <iostream>
using namespace std;

#define MAX_SIZE 10 // Maximum size of Deque

// Deque class
class Deque {
    int array[MAX_SIZE];
    int front;
    int rear;
    int size;

public:
    Deque(int size) {
        front = -1;
        rear = 0;
        this->size = size;
    }

    // Core Deque operations
    void insertFront(int key);
    void insertRear(int key);
    void deleteFront();
    void deleteRear();
    int getFront();
    int getRear();
    bool isFull();
    bool isEmpty();
    void display();
};

// Check if Deque is full
bool Deque::isFull() {
    return ((front == 0 && rear == size - 1) || front == rear + 1);
}

// Check if Deque is empty
bool Deque::isEmpty() {
    return (front == -1);
}

// Insert element at front
void Deque::insertFront(int key) {
    if (isFull()) {
        cout << "\n Queue Overflow!\n";
        return;
    }

    if (front == -1) { // First element
        front = 0;
        rear = 0;
    } else if (front == 0)
        front = size - 1;
    else
        front = front - 1;

    array[front] = key;
    cout << "Inserted customer ID " << key << " at FRONT.\n";
}

// Insert element at rear
void Deque::insertRear(int key) {
    if (isFull()) {
        cout << "\n Queue Overflow!\n";
        return;
    }

    if (front == -1) { // First element
        front = 0;
        rear = 0;
    } else if (rear == size - 1)
        rear = 0;
    else
        rear = rear + 1;

    array[rear] = key;
    cout << " Inserted customer ID " << key << " at REAR.\n";
}

// Delete element at front
void Deque::deleteFront() {
    if (isEmpty()) {
        cout << "\n Queue Underflow!\n";
        return;
    }

    cout << "🚶‍♂️ Customer ID " << array[front] << " left from FRONT.\n";

    if (front == rear)
        front = rear = -1;
    else if (front == size - 1)
        front = 0;
    else
        front = front + 1;
}

// Delete element at rear
void Deque::deleteRear() {
    if (isEmpty()) {
        cout << "\n Queue Underflow!\n";
        return;
    }

    cout << "🚶‍♀️ Customer ID " << array[rear] << " left from REAR.\n";

    if (front == rear)
        front = rear = -1;
    else if (rear == 0)
        rear = size - 1;
    else
        rear = rear - 1;
}

// Get front element
int Deque::getFront() {
    if (isEmpty()) {
        cout << "Queue is Empty!\n";
        return -1;
    }
    return array[front];
}

// Get rear element
int Deque::getRear() {
    if (isEmpty()) {
        cout << "Queue is Empty!\n";
        return -1;
    }
    return array[rear];
}

// Display all customers in the queue
void Deque::display() {
    if (isEmpty()) {
        cout << "\n Queue is empty!\n";
        return;
    }

    cout << "\nCurrent Queue (Shopping Mall): ";
    int i = front;
    while (true) {
        cout << array[i] << " ";
        if (i == rear)
            break;
        i = (i + 1) % size;
    }
    cout << endl;
}

// Main Function
int main() {
    int size;
    cout << "Enter the size of the shopping queue: ";
    cin >> size;
    Deque dq(size);

    int choice, type, id;
    cout << "\nSelect Deque Type:\n";
    cout << "1. Input Restricted Deque\n";
    cout << "2. Output Restricted Deque\n";
    cout << "Enter your choice: ";
    cin >> type;

    cout << "\n--- Shopping Mall Queue Simulation ---\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert Customer at Front\n";
        cout << "2. Insert Customer at Rear\n";
        cout << "3. Remove Customer from Front\n";
        cout << "4. Remove Customer from Rear\n";
        cout << "5. Display Queue\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (type == 1)
                cout << " Insertion at front is not allowed in Input Restricted Deque!\n";
            else {
                cout << "Enter Customer ID to insert at front: ";
                cin >> id;
                dq.insertFront(id);
            }
            break;

        case 2:
            cout << "Enter Customer ID to insert at rear: ";
            cin >> id;
            dq.insertRear(id);
            break;

        case 3:
            dq.deleteFront();
            break;

        case 4:
            if (type == 2)
                cout << " Deletion at rear is not allowed in Output Restricted Deque!\n";
            else
                dq.deleteRear();
            break;

        case 5:
            dq.display();
            break;

        case 6:
            cout << "\nThank you! Mall Queue closed.\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
