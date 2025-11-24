#include <iostream>
using namespace std;
int main() {
    int hashTable[11];
    int i, key, index;
    for (i = 0; i < 11; i++)
        hashTable[i] = -1;
	int mangoes[11] = {25, 15, 10, 5, 11, 19, 13, 16, 24, 28, 32};
	for (i = 0; i < 11; i++) {
        key = mangoes[i];
        index = key % 11;

        if (hashTable[index] == -1) hashTable[index] = key;
		else {
            int k = 1;
            int newIndex = index;
            while (k < 11) {
                newIndex = (index + k * k) % 11;
                if (hashTable[newIndex] == -1) {
                    hashTable[newIndex] = key;
                    break;
                }
                k++;
            }
	        if (k == 11) cout << "Table full! Could not insert " << key << endl;
        }
    } cout << "\nHash Table (Quadratic Probing without Replacement):\n";
    for (i = 0; i < 11; i++)
        cout << "Index " << i << " : " << hashTable[i] << "\n";
	return 0;
}
