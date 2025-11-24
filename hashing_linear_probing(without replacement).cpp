#include <iostream>
using namespace std;
int main() {
    int hashTable[6];
    int i, key, index, n;
	for (i = 0; i < 6; i++)
        hashTable[i] = -1;

    cout << "Enter number of cold drink keys to insert: ";
    cin >> n;
	for (i = 0; i < n; i++) {
        cout << "Enter key " << i + 1 << ": ";
        cin >> key;
        index = key % 6;

        int j = 0;
        while (hashTable[(index + j) % 6] != -1 && j < 6)
            j++;
		if (j < 6)
            hashTable[(index + j) % 6] = key;
        else
            cout << "Table full! Could not insert key " << key << endl;
    }
	cout << "\nHash Table (Linear Probing without Replacement):\n";
    for (i = 0; i < 6; i++)
        cout << "Index " << i << " : " << hashTable[i] << "\n";

    return 0;
}
