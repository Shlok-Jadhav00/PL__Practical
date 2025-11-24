#include <iostream>
using namespace std;
class Node {
    public:
        int data;
        Node* next;
};
int main() {
    Node* hashTable[20];
    int i;
    for (i = 0; i < 20; i++)
        hashTable[i] = NULL;

    int keys[20] = {33,56,78,12,10,67,89,99,100,23,45,71,39,62,59,90,91,20,75,66};
    int n = 20;
	for (i = 0; i < n; i++) {
        int key = keys[i];
        int index = key % 20;

        Node* newNode = new Node;
        newNode->data = key;
        newNode->next = NULL;

        if (hashTable[index] == NULL)
            hashTable[index] = newNode;
        else {
            Node* temp = hashTable[index];
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }
    }
	cout << "\nHash Table using Separate Chaining:\n";
    for (i = 0; i < 20; i++) {
        cout << "Index " << i << " : ";
        Node* temp = hashTable[i];
        while (temp != NULL) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
	return 0;
}
