#include <iostream>
#include <string>
using namespace std;

class Stack
{
    int top, size;
    string *arr;

public:
    Stack(int n)
    {
        size = n;
        top = -1;
        arr = new string[size];
    }

    void push(string val)
    {
        if (top == size - 1)
        {
            cout << "Stack Overflow" << endl;
        }
        else
        {
            arr[++top] = val;
        }
    }

    string pop()
    {
        if (top == -1)
        {
            cout << "Stack Underflow" << endl;
            return "";
        }
        else
        {
            return arr[top--];
        }
    }

    string peek()
    {
        if (top == -1)
        {
            return "";
        }
        else
        {
            return arr[top];
        }
    }

    bool isEmpty()
    {
        return top == -1;
    }
};

string prefixToInfix(string prefix)
{
    Stack st(prefix.length());
    for (int i = prefix.length() - 1; i >= 0; i--)
    {
        char c = prefix[i];
        if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            st.push(string(1, c));
        }
        else
        {
            if (st.isEmpty())
                return "Invalid Expression";
            string op1 = st.pop();

            if (st.isEmpty())
                return "Invalid Expression";
            string op2 = st.pop();

            string expr = "(" + op1 + string(1, c) + op2 + ")";
            st.push(expr);
        }
    }
    return st.pop();
}

int precedence(char c)
{
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '^')
        return 3;
    else
        return -1;
}

string infixToPostfix(string infix)
{
    Stack st(infix.length());
    string result = "";

    for (int i = 0; i < infix.length(); i++)
    {
        char c = infix[i];
        if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            result += c;
        }
        else if (c == '(')
        {
            st.push(string(1, c));
        }
        else if (c == ')')
        {
            while (!st.isEmpty() && st.peek() != "(")
            {
                result += st.pop();
            }
            if (!st.isEmpty())
                st.pop(); // remove '('
        }
        else
        {
            while (!st.isEmpty() && precedence(st.peek()[0]) >= precedence(c))
            {
                result += st.pop();
            }
            st.push(string(1, c));
        }
    }

    while (!st.isEmpty())
    {
        result += st.pop();
    }

    return result;
}

int main()
{
    string prefix = "";
    string infix = "";
    string postfix = "";
    int choice;

    do
    {
        cout << "\n-----------------------------\n";
        cout << "1. Enter Prefix Expression\n";
        cout << "2. Show Infix Expression\n";
        cout << "3. Show Postfix Expression\n";
        cout << "4. Exit\n";
        cout << "-----------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        cin.clear();
        cin.ignore(10000, '\n'); // clear input buffer

        switch (choice)
        {
        case 1:
            cout << "Enter Prefix Expression (no spaces): ";
            cin >> prefix;
            infix = "";
            postfix = "";
            break;

        case 2:
            if (prefix.empty())
            {
                cout << "Please enter a prefix expression first.\n";
            }
            else
            {
                infix = prefixToInfix(prefix);
                cout << "Infix Expression: " << infix << endl;
            }
            break;

        case 3:
            if (prefix.empty())
            {
                cout << "Please enter a prefix expression first.\n";
            }
            else
            {
                if (infix.empty())
                    infix = prefixToInfix(prefix);
                postfix = infixToPostfix(infix);
                cout << "Postfix Expression: " << postfix << endl;
            }
            break;

        case 4:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}

