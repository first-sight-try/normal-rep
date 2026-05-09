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

void fcfs(Process p[], int n) {
    cout << "\n--- FCFS ---\n";

    // Sort by arrival time
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (p[j].at > p[j+1].at ||
               (p[j].at == p[j+1].at && p[j].id > p[j+1].id)) {
                swap(p[j], p[j+1]);
            }
        }
    }

    int time = 0;

    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;

        time += p[i].bt;
        p[i].ct = time;
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

    cout << "\nAverage WT = " << totalWT / n;
    cout << "\nAverage TAT = " << totalTAT / n << endl;
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

    fcfs(p, n);

    return 0;
}