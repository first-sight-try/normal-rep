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

// ---------------- SRTF SCHEDULING ----------------
void srtf(Process p[], int n) {
    cout << "\n--- SRTF Scheduling ---\n";

    int time = 0, completed = 0;

    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    while (completed < n) {

        int idx = -1;
        int minRT = 9999;

        // Find process with shortest remaining time
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                if (p[i].rt < minRT) {
                    minRT = p[i].rt;
                    idx = i;
                }
                else if (p[i].rt == minRT) {
                    if (idx == -1 || p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            time++; // CPU idle
        } else {
            p[idx].rt--;
            time++;

            if (p[idx].rt == 0) {
                p[idx].ct = time;
                completed++;
            }
        }
    }

    // ---------------- CALCULATE TAT & WT ----------------
    calculate(p, n);

    int totalWT = 0, totalTAT = 0;

    cout << "\nID\tCT\tTAT\tWT\n";

    for (int i = 0; i < n; i++) {
        cout << p[i].id << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << endl;

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    // ---------------- AVERAGES ----------------
    cout << "\n----------------------\n";
    cout << "Average Waiting Time = " << (float)totalWT / n << endl;
    cout << "Average Turnaround Time = " << (float)totalTAT / n << endl;
}

// ---------------- MAIN ----------------
int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[100];

    for (int i = 0; i < n; i++) {
        cout << "\nProcess " << i + 1 << endl;

        cout << "Process ID: ";
        cin >> p[i].id;

        cout << "Arrival Time: ";
        cin >> p[i].at;

        cout << "Burst Time: ";
        cin >> p[i].bt;
    }

    srtf(p, n);

    return 0;
}