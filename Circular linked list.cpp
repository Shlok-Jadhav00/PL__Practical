#include <iostream>
using namespace std;

class Node {
public:
    int orderID;
    string type;   // Small / Medium / Large
    int quantity;  // number of pizzas
    Node* next;

    Node(int id, string t, int q) {
        orderID = id;
        type = t;
        quantity = q;
        next = NULL;
    }
};

class PizzaParlor {
    Node* front;   // first order
    Node* rear;    // last order
    int count;     // current orders
    int maxOrders; // maximum capacity

public:
    PizzaParlor(int M) {
        front = rear = NULL;
        count = 0;
        maxOrders = M;
    }

    bool isFull() {
        return count == maxOrders;
    }

    bool isEmpty() {
        return count == 0;
    }

    // Place Order
    bool placeOrder(int id, string type, int qty) {
        if (isFull()) {
            cout << "Parlor FULL! Cannot take more orders"<<endl;
            return false; // order not placed
        }

        Node* newNode = new Node(id, type, qty);

        if (front == NULL) {
            front = rear = newNode;
            rear->next = front; // circular
        } else {
            rear->next = newNode;
            rear = newNode;
            rear->next = front;
        }

        count++;
        cout << "Order " << id << " placed (" << qty << " " << type << " pizza)"<<endl;
        return true; // order placed
    }

    // Serve Order
    void serveOrder() {
        if (isEmpty()) {
            cout << "No orders to serve<<endl";
            return;
        }

        cout << "Order " << front->orderID
             << " served (" << front->quantity
             << " " << front->type << " pizza)"<<endl;

        if (front == rear) { // only one order
            delete front;
            front = rear = NULL;
        } else {
            Node* temp = front;
            front = front->next;
            rear->next = front;
            delete temp;
        }

        count--;
    }

    // Display Orders
    void displayOrders() {
        if (isEmpty()) {
            cout << "No pending orders"<<endl;
            return;
        }

        Node* temp = front;
        cout << "Pending Orders:"<<endl;
        do {
            cout << "OrderID: " << temp->orderID
                 << " | Type: " << temp->type
                 << " | Qty: " << temp->quantity << endl;
            temp = temp->next;
        } while (temp != front);
    }
};

int main() {
    int M;
    cout << "Enter maximum number of orders: ";
    cin >> M;

    PizzaParlor parlor(M);
    int choice, orderID = 1;

    do {
        cout << "\n--- Pizza Parlor ---"<<endl;
        cout << "1. Place Order"<<endl;
        cout << "2. Serve Order"<<endl;
        cout << "3. Display Orders"<<endl;
        cout << "4. Exit"<<endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            if (parlor.isFull()) {
                cout << "***Parlor is already FULL. Cannot place new orders!***"<<endl;
            } else {
                string type;
                int qty;
                cout << "Enter pizza type (Small/Medium/Large): ";
                cin >> type;
                cout << "Enter quantity: ";
                cin >> qty;

                // only increment orderID if order was actually placed
                if (parlor.placeOrder(orderID, type, qty)) {
                    orderID++;
                }
            }
        }
        else if (choice == 2) {
            parlor.serveOrder();
        }
        else if (choice == 3) {
            parlor.displayOrders();
        }
        else if (choice == 4) {
            cout << "Closing Pizza Parlor..."<<endl;
        }
        else {
            cout << "Invalid choice!"<<endl;
        }

    } while (choice != 4);

    return 0;
}

