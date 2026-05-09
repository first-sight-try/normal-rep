#include <iostream>
using namespace std;

struct Process {
    string id;
    int at, bt, ct, tat, wt, rt;
};

// ---------------- CALCULATION ----------------
void calculate(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
}

// ---------------- ROUND ROBIN ----------------
void roundRobin(Process p[], int n, int quantum) {
    cout << "\n--- Round Robin Scheduling ---\n";

    int time = 0;
    int queue[100], front = 0, rear = 0;
    bool inQueue[100] = {false};

    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    int completed = 0;

    while (completed < n) {

        // Add arrived processes
        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && p[i].at <= time && p[i].rt > 0) {
                queue[rear++] = i;
                inQueue[i] = true;
            }
        }

        // If queue empty → CPU idle
        if (front == rear) {
            time++;
            continue;
        }

        int i = queue[front++];

        int exec = min(quantum, p[i].rt);
        p[i].rt -= exec;
        time += exec;

        // Add newly arrived processes during execution
        for (int j = 0; j < n; j++) {
            if (!inQueue[j] && p[j].at <= time && p[j].rt > 0) {
                queue[rear++] = j;
                inQueue[j] = true;
            }
        }

        if (p[i].rt > 0) {
            queue[rear++] = i;
        } else {
            p[i].ct = time;
            completed++;
        }
    }

    calculate(p, n);

    cout << "\nID\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].id << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << endl;
    }

    // ---------------- AWT & ATAT ----------------
    double totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    cout << "\nAverage Waiting Time (AWT) = " << totalWT / n;
    cout << "\nAverage Turnaround Time (ATAT) = " << totalTAT / n << endl;
}

// ---------------- MAIN ----------------
int main() {
    int n, quantum;

    cout << "Enter number of processes: ";
    cin >> n;

    Process p[100];

    for (int i = 0; i < n; i++) {
        cout << "Process ID: ";
        cin >> p[i].id;
        cout << "Arrival Time: ";
        cin >> p[i].at;
        cout << "Burst Time: ";
        cin >> p[i].bt;
    }

    cout << "Enter Time Quantum: ";
    cin >> quantum;

    roundRobin(p, n, quantum);

    return 0;
}