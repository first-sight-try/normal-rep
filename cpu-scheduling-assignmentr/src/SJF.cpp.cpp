#include <iostream>
using namespace std;

struct Process {
    string id;
    int at, bt, ct, tat, wt;
};

void calculate(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
}

void sjf(Process p[], int n) {
    cout << "\n--- SJF (Non-Preemptive) ---\n";

    int completed = 0, time = 0;
    bool done[100] = {false};

    while (completed < n) {
        int idx = -1;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time) {
                if (idx == -1 ||
                    p[i].bt < p[idx].bt ||
                   (p[i].bt == p[idx].bt && p[i].at < p[idx].at)) {
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++; // CPU idle
        } else {
            time += p[idx].bt;
            p[idx].ct = time;
            done[idx] = true;
            completed++;
        }
    }

    calculate(p, n);

    float totalWT = 0, totalTAT = 0;

    cout << "\nID\tAT\tBT\tCT\tTAT\tWT\n";

    for (int i = 0; i < n; i++) {
        cout << p[i].id << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << endl;

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    cout << "\nAverage Waiting Time = " << totalWT / n;
    cout << "\nAverage Turnaround Time = " << totalTAT / n << endl;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[100];

    for (int i = 0; i < n; i++) {
        cout << "\nEnter Process ID: ";
        cin >> p[i].id;

        cout << "Enter Arrival Time: ";
        cin >> p[i].at;

        cout << "Enter Burst Time: ";
        cin >> p[i].bt;
    }

    sjf(p, n);

    return 0;
}