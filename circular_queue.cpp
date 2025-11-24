#include <iostream>
#include <iomanip>
using namespace std;

#define MAX 20

// Circular Queue implementation
struct CircularQueue {
    int items[MAX];
    int front, rear;
};

void initQueue(CircularQueue &q) {
    q.front = -1;
    q.rear = -1;
}

bool isEmpty(CircularQueue &q) {
    return (q.front == -1);
}

bool isFull(CircularQueue &q) {
    return ((q.rear + 1) % MAX == q.front);
}

void enqueue(CircularQueue &q, int value) {
    if (isFull(q)) return;
    if (q.front == -1) q.front = 0;
    q.rear = (q.rear + 1) % MAX;
    q.items[q.rear] = value;
}

int dequeue(CircularQueue &q) {
    if (isEmpty(q)) return -1;
    int value = q.items[q.front];
    if (q.front == q.rear) q.front = q.rear = -1;
    else q.front = (q.front + 1) % MAX;
    return value;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int arrival[MAX], burst[MAX], remaining[MAX];
    int turnaround[MAX], waiting[MAX];
    int quantum;

    cout << "\nEnter Arrival Time for each process:\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << ": ";
        cin >> arrival[i];
    }

    cout << "\nEnter Burst Time for each process:\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << ": ";
        cin >> burst[i];
        remaining[i] = burst[i];
    }

    cout << "\nEnter Time Quantum: ";
    cin >> quantum;

    CircularQueue q;
    initQueue(q);

    int time = 0, completed = 0;
    bool visited[MAX] = {false};

    // enqueue first process which has arrived first
    int firstProcess = 0;
    for (int i = 0; i < n; i++) {
        if (arrival[i] <= time) {
            firstProcess = i;
            break;
        }
    }
    enqueue(q, firstProcess);
    visited[firstProcess] = true;

    // Store Gantt chart timeline
    int ganttTimeline[100], ganttProcess[100];
    int ganttIndex = 0;

    while (!isEmpty(q)) {
        int i = dequeue(q);

        // execution start for Gantt chart
        int execTime = (remaining[i] > quantum) ? quantum : remaining[i];
        ganttProcess[ganttIndex] = i;
        ganttTimeline[ganttIndex] = time;
        ganttIndex++;

        // Execute process
        if (remaining[i] > quantum) {
            remaining[i] -= quantum;
            time += quantum;
        } else {
            time += remaining[i];
            remaining[i] = 0;
            completed++;
            turnaround[i] = time - arrival[i];
            waiting[i] = turnaround[i] - burst[i];
        }

        // Enqueue newly arrived processes
        for (int j = 0; j < n; j++) {
            if (!visited[j] && arrival[j] <= time) {
                enqueue(q, j);
                visited[j] = true;
            }
        }

        // Re-add current process if not finished
        if (remaining[i] > 0)
            enqueue(q, i);
    }

    // Append final time to Gantt timeline
    ganttTimeline[ganttIndex] = time;

    // Print Gantt Chart
    cout << "\n=== Gantt Chart ===\n";
    cout << "|";
    for (int i = 0; i < ganttIndex; i++) {
        cout << " P" << ganttProcess[i] + 1 << " |";
    }
    cout << "\n0";
    for (int i = 0; i < ganttIndex; i++) {
        cout << setw(5) << ganttTimeline[i + 1];
    }
    cout << endl;

    // Print Process Table
    cout << "\nProcess Details:\n";
    cout << "---------------------------------------------------------------\n";
    cout << setw(8) << "Process" << setw(15) << "Arrival Time" << setw(15)
         << "Burst Time" << setw(15) << "Waiting" << setw(15) << "Turnaround\n";
    cout << "---------------------------------------------------------------\n";

    float total_wait = 0, total_turnaround = 0;
    for (int i = 0; i < n; i++) {
        cout << setw(8) << "P" + to_string(i + 1)
             << setw(15) << arrival[i]
             << setw(15) << burst[i]
             << setw(15) << waiting[i]
             << setw(15) << turnaround[i] << endl;
        total_wait += waiting[i];
        total_turnaround += turnaround[i];
    }

    cout << "---------------------------------------------------------------\n";
    cout << "Average Waiting Time: " << fixed << setprecision(2)
         << total_wait / n << endl;
    cout << "Average Turnaround Time: " << fixed << setprecision(2)
         << total_turnaround / n << endl;

    return 0;
}
