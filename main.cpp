#include <iostream>
#include <queue>

using namespace std;

void roundRobin() {
    int numProcesses;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    if (numProcesses < 3 || numProcesses > 10) {
        cout << "Number of processes must be between 3 and 10." << endl;
        return;
    }

    int arrivalTime[numProcesses], burstTime[numProcesses], waitingTime[numProcesses], turnaroundTime[numProcesses], priority[numProcesses];
    int remainingBurstTime[numProcesses];
    float averageWaitingTime = 0, averageTurnaroundTime = 0;

    cout << "Enter arrival times for each process:\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << "Process P" << i + 1 << ": ";
        cin >> arrivalTime[i];
    }

    cout << "Enter burst times for each process:\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << "Process P" << i + 1 << ": ";
        cin >> burstTime[i];
        remainingBurstTime[i] = burstTime[i];
    }

    cout << "Enter priority for each process:\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << "Process P" << i + 1 << ": ";
        cin >> priority[i];
    }
}

void SRT() {

}

void preemptivePriority() {

}

void non_preemptivePriority() {

}

int main() {
    int choice;

    cout << "Choose scheduling algorithm:\n";
    cout << "1. Round Robin Of Quantum 3\n";
    cout << "2. Shortest Remaining Time\n";
    cout << "3. Preemptive Priority\n";
    cout << "4. Non-Preemptive Priority\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            roundRobin();
            break;
        case 2:
            SRT();
            break;
        case 3:
            preemptivePriority();
            break;
        case 4:
            non_preemptivePriority();
            break;
        default:
            cout << "Invalid choice!";
    }
}
