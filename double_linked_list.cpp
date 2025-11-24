#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;
    Node(int val) : data(val), prev(NULL), next(NULL) {}
};

class DoublyLinkedList {
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(NULL), tail(NULL) {}

    // Insert node at the end
    void insertEnd(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Display list with <-> arrows
    void display() {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }
        Node* temp = head;
        while (temp) {
            cout << temp->data;
            if (temp->next) cout << " <-> ";
            temp = temp->next;
        }
        cout << "\n";
    }

    // Sort using bubble sort (swapping data)
    void sortList() {
        if (!head) return;
        bool swapped;
        do {
            swapped = false;
            Node* curr = head;
            while (curr->next) {
                if (curr->data > curr->next->data) {
                    swap(curr->data, curr->next->data);
                    swapped = true;
                }
                curr = curr->next;
            }
        } while (swapped);
    }

    Node* getHead() { return head; }

    // Merge two sorted DLLs
    static DoublyLinkedList mergeSorted(DoublyLinkedList& a, DoublyLinkedList& b) {
        DoublyLinkedList result;
        Node* p = a.getHead();
        Node* q = b.getHead();

        while (p && q) {
            if (p->data <= q->data) {
                result.insertEnd(p->data);
                p = p->next;
            } else {
                result.insertEnd(q->data);
                q = q->next;
            }
        }
        while (p) {
            result.insertEnd(p->data);
            p = p->next;
        }
        while (q) {
            result.insertEnd(q->data);
            q = q->next;
        }
        return result;
    }
};

int main() {
    DoublyLinkedList list1, list2;

    int n1, n2, val;
    cout << "Enter number of students in List 1: ";
    cin >> n1;
    cout << "Enter marks for List 1:\n";
    for (int i = 0; i < n1; i++) {
        cin >> val;
        list1.insertEnd(val);
    }

    cout << "Enter number of students in List 2: ";
    cin >> n2;
    cout << "Enter marks for List 2:\n";
    for (int i = 0; i < n2; i++) {
        cin >> val;
        list2.insertEnd(val);
    }

    cout << "\nSorting both lists...\n";
    list1.sortList();
    list2.sortList();

    cout << "Sorted List 1: ";
    list1.display();
    cout << "Sorted List 2: ";
    list2.display();

    cout << "\nMerging the two sorted lists...\n";
    DoublyLinkedList merged = DoublyLinkedList::mergeSorted(list1, list2);

    cout << "Final Merged & Sorted List of Marks:\n";
    merged.display();

    return 0;
}
