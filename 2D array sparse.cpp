#include <iostream>
using namespace std;
class sparse
{
public:
    int row, col, value;
    int matrix[10][10];

    void input(sparse s[])
    {
        int R, C;
        cout << "Enter dimensions of first matrix (Seperated by space): ";
        cin >> R >> C;
        if (R <= 0 || C <= 0) {
            cout << "Invalid dimensions. Please enter positive integers." << endl;
            return;
        }
        
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                cout << "Enter element at position (" << i << "," << j << "): ";
                cin >> matrix[i][j];
            }
        }

        cout << "The matrix is:\n";
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }

        s[0].row = R;
        s[0].col = C;

        cout << "Converting to sparse matrix representation..." << endl;
        int k = 1;
        for (int i = 0; i < R; i++)
        {
            for (int j = 0; j < C; j++)
            {
                if (matrix[i][j] != 0)
                {
                    s[k].row = i;
                    s[k].col = j;
                    s[k].value = matrix[i][j];
                    k++;
                }
            }
        }
        cout << "Number of non-zero elements: " << k - 1 << endl;
        s[0].value = k - 1;
    }

    void display(sparse s[]) {
        cout << "Row    Column    Value\n";
        cout << "------------------------\n";
        for (int i = 0; i <= s[0].value; i++){
            cout << " " << s[i].row << "        " << s[i].col << "        " << s[i].value << endl;
        }
    }

    void trans(const sparse s[], sparse Trans_Result[])
    {
        Trans_Result[0].row = s[0].col;
        Trans_Result[0].col = s[0].row;
        Trans_Result[0].value = s[0].value;

        int k = 1;
        for (int c = 0; c < s[0].col; c++)
        {
            for (int i = 1; i <= s[0].value; i++)
            {
                if (s[i].col == c)
                {
                    Trans_Result[k].row = s[i].col;
                    Trans_Result[k].col = s[i].row;
                    Trans_Result[k].value = s[i].value;
                    k++;
                }
            }
        }
    }

    void fast_stranspose(sparse s[], sparse fast_trans[]){
        int k;
        int total[s[0].col];//Creating a total array
        for (int j = 0; j < s[0].col; j++)
        {
            k = 0;
            for (int i = 0; i < s[0].row; i++){
                if (matrix[i][j] != 0){
                    k++;
                }
            }
            total[j] = k;
        }

        int index[s[0].col + 1];
        index[0] = 1;//Creating a Index array
        for (int i = 1; i <= s[0].col; i++)
        {
            index[i] = index[i - 1] + total[i - 1];
        }

        
        for (int i = 1; i <= s[0].value; i++)
        {
            int j = s[i].col;
            int pos = index[j];
            fast_trans[pos].row = s[i].col;
            fast_trans[pos].col = s[i].row;
            fast_trans[pos].value = s[i].value;
            index[j]++;
        }

        fast_trans[0].row = s[0].col;
        fast_trans[0].col = s[0].row;
        fast_trans[0].value = s[0].value;
    }

    void add(sparse s1[], sparse s2[], sparse Add_Result[]) {
        if (s1[0].row != s2[0].row || s1[0].col != s2[0].col) {
            cout << "Matrices cannot be added. Dimensions don't match!" << endl;
            return ;
        }

        int count = 1, k1 = 1, k2 = 1;
        for (int i = 0; i < s1[0].row; i++) {
            for (int j = 0; j < s2[0].col; j++) {
                int sum = 0;
                while (k1 <= s1[0].value && s1[k1].row == i && s1[k1].col == j) {
                    sum += s1[k1].value;
                    k1++;
                }
                while (k2 <= s2[0].value && s2[k2].row == i && s2[k2].col == j) {
                    sum += s2[k2].value;
                    k2++;
                }
                if (sum != 0) {
                    Add_Result[count].row = i;
                    Add_Result[count].col = j;
                    Add_Result[count].value = sum;
                    count++;
                }
            }
        }
        Add_Result[0].row = s1[0].row;
        Add_Result[0].col = s1[0].col;
        Add_Result[0].value = count - 1;
    }

    void multiply(sparse s1[], sparse s2[], sparse Mult_Result[]) {
        if (s1[0].col != s2[0].row) {
            cout << "Matrices cannot be multiplied. Dimensions don't match!" << endl;
            return ;
        }
        int resultMatrix[10][10] = {0};
        for (int i = 1; i <= s1[0].value; i++) {
            for (int j = 1; j <= s2[0].value; j++) {
                if (s1[i].col == s2[j].row) {
                    resultMatrix[s1[i].row][s2[j].col] += s1[i].value * s2[j].value;
                }
            }
        }

        int k = 1;
        for (int i = 0; i < s1[0].row; i++) {
            for (int j = 0; j < s2[0].col; j++) {
                if (resultMatrix[i][j] != 0) {
                    Mult_Result[k].row = i;
                    Mult_Result[k].col = j; 
                    Mult_Result[k].value = resultMatrix[i][j];
                    k++;
                }
            }
        }

        Mult_Result[0].row = s1[0].row;
        Mult_Result[0].col = s2[0].col;
        Mult_Result[0].value = k - 1;
    }
};

int main()
{
    sparse s1[20], s2[20], Trans_Result[20], fast_trans[50], Add_Result[20], Mult_Result[20];

    cout << "Input for 1st Matrix " << endl;
    s1[0].input(s1);

    cout << "\nInput for 2nd Matrix " << endl;
    s2[0].input(s2);

    cout << "\n1st Matrix in Triplet Form: " << endl;
    s1[0].display(s1);

    cout << "\n2nd Matrix in Triplet Form: " << endl;
    s2[0].display(s2);

    cout << "\nTranspose of 1st matrix is: " << endl;
    s1[0].trans(s1, Trans_Result);
    Trans_Result[0].display(Trans_Result);

    cout << "\nFast Transpose of 2st matrix is: " << endl;
    s2[0].fast_stranspose(s2, fast_trans);
    fast_trans[0].display(fast_trans);

    cout << "\nResultant Sparse Matrix after Addition:" << endl;
    s1[0].add(s1, s2, Add_Result);
    Add_Result[0].display(Add_Result);

    cout << "\nResultant Sparse Matrix after Multiplication:" << endl;
    s1[0].multiply(s1, s2, Mult_Result);
    if (Mult_Result[0].value != -1) {
        Mult_Result[0].display(Mult_Result);
    }

    return 0;
}

