#include <iostream>
using namespace std;

class lib_management {
	int id;
	string title;
	string author;

public:
	void insert() {
		cout << "Enter ID: ";
		cin >> id;
		cout << "Enter Title of Book : ";
		cin >> title;
		cout << "Enter Author name of the book : ";
		cin >> author;
	}

	void display() {
		cout << "ID : " << id << "   Title : " << title << "   Author_Name : " << author << endl;
	}

	bool search(int k) {
		return id == k;
	}

	void update() {
        
        cout << "Enter new title of book: ";
        cin >> title;
		cout << "Enter new Author Name: ";
		cin >> author;
		cout << "Book updated successfully!\n";
	}

};

int main() {
	lib_management m[3];
	int count = 0;

    cout << "Welcome to Library Management System\n";


	while (true) {
		int choice;
		cout << "\n1. Insert\n2. Display\n3. Search\n4. Update\n5. Delete\n6. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
			case 1:{
				if (count == 3) {
                    cout << "Library is full cannot add more books.\n";
                    continue;
                }
                cout << "Inserting Book:\n";
                m[count].insert();
                count++;
				break;
            }

			case 2:{
                if (count == 0) {
                    cout << "No books available.\n";
                    continue;
                }
            
                cout << "Displaying all books:\n";
				for (int i = 0; i < count; i++) {
					m[i].display();
					cout << "------------------\n";
				}
				break;
            }

			case 3: {
                if (count == 0) {
                    cout << "No books available to search.\n";
                    continue;
                }

                cout << "Searching Book:\n";
				int req_id;
				cout << "Enter ID to search: ";
				cin >> req_id;
				bool found = false;
				for (int i = 0; i < count; i++) {
					if (m[i].search(req_id)) {
						cout << "ID Found:\n";
						m[i].display();
						found = true;
					}
				}
				if (!found) cout << "ID Not Found\n";
				break;
			}

			case 4: {
                if (count == 0) {
                    cout << "No books available to update.\n";
                    continue;
                }
                
                cout << "Updating Book:\n";
				int Book_id;
				cout << "Enter Book ID to update book: ";
				cin >> Book_id;
				bool updated = false;
				for (int i = 0; i < count; i++) {
					if (m[i].search(Book_id)) {
						m[i].update();
						updated = true;
					}
				}
				if (!updated) cout << "Book ID not found.\n";
				break;
			}

            case 5:{
                if (count == 0) {
                    cout << "No books available to delete.\n";
                    continue;
                }

                cout << "Deleting Book:\n";
                int del_id;
                cout << "Enter ID of book to delete: ";
                cin >> del_id;
                bool deleted = false;
                for (int i = 0; i < count; i++) {
                    if (m[i].search(del_id)) {
                        for (int j = i; j < count - 1; j++) {
                            m[j] = m[j + 1];

                        }
                        count--;
                        deleted = true;
                        cout << "Book deleted successfully.\n";
                    }
                }
                if (!deleted) cout << "Book ID not found.\n";
                break;
            }

			case 6:
				cout << "Exiting Program.\n";
				return 0;

			default:
				cout << "Invalid choice. Please try No. between 1-5.\n";
		}
	}
}

