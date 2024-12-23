#include <iostream>
#include <queue>

using namespace std;

void roundRobin(int arrivalTime[], int burstTime[], int waitingTime[], int turnaroundTime[], int priority[], int remainingBurstTime[], int numProcesses) {
    float averageWaitingTime = 0, averageTurnaroundTime = 0;
    int time = 0;
    int quantum = 3;

    queue<int> readyQueue;
    bool isFinished[numProcesses] = {false};  // Process completion tracker
    bool inReadyQueue[numProcesses] = {false};  // Tracks if a process is in the queue
    int completionTime[numProcesses] = {0};  // Stores when each process completes

    cout << "Round Robin with Quantum 3" << endl;

    // for checking purpose
    // cout << "Arrival times for each process:\n";
    // for (int i = 0; i < numProcesses; i++) {
    //     cout << "Process P" << i + 1 << ": ";
    //     cout << arrivalTime[i];
    //     cout << endl;
    // }

    // cout << "Burst times for each process:\n";
    // for (int i = 0; i < numProcesses; i++) {
    //     cout << "Process P" << i + 1 << ": ";
    //     cout << burstTime[i];
    //     remainingBurstTime[i] = burstTime[i];
    //     cout << endl;
    // }

    // cout << "Priority for each process:\n";
    // for (int i = 0; i < numProcesses; i++) {
    //     cout << "Process P" << i + 1 << ": ";
    //     cout << priority[i];
    //     cout << endl;
    // }

    
}

void SRT() {

}

void preemptivePriority() {

}

void non_preemptivePriority() {

}

int main() {

    int numProcesses;

    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    if (numProcesses < 3 || numProcesses > 10) {
        cout << "Number of processes must be between 3 and 10." << endl;
        return 0;
    }

    int arrivalTime[numProcesses], burstTime[numProcesses], waitingTime[numProcesses], turnaroundTime[numProcesses], priority[numProcesses];
    int remainingBurstTime[numProcesses];

    cout << "Enter arrival times for each process:\n";
    for (int i = 0; i < numProcesses; i++) {
        if (i == 0) {
            cout << "Process P" << i << ": ";
        } 
        else {
            cout << "Process P" << i + 1 << ": ";
            cin >> arrivalTime[i];
        }
    }

    cout << "Enter burst times for each process:\n";
    for (int i = 0; i < numProcesses; i++) {
        if (i == 0) {
            cout << "Process P" << i << ": ";
        } 
        else {
            cout << "Process P" << i + 1 << ": ";
            cin >> burstTime[i];
        }
        remainingBurstTime[i] = burstTime[i];
    }

    cout << "Enter priority for each process:\n";
    for (int i = 0; i < numProcesses; i++) {
        if (i == 0) {
            cout << "Process P" << i << ": ";
        } else {
                cout << "Process P" << i + 1 << ": ";
            cin >> priority[i]; 
        }
    }

    roundRobin(arrivalTime, burstTime, waitingTime, turnaroundTime, priority, remainingBurstTime, numProcesses);

    int choice;

    cout << "Choose scheduling algorithm:\n";
    cout << "1. Shortest Remaining Time\n";
    cout << "2. Preemptive Priority\n";
    cout << "3. Non-Preemptive Priority\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            SRT();
            break;
        case 2:
            preemptivePriority();
            break;
        case 3:
            non_preemptivePriority();
            break;
        default:
            cout << "Invalid choice!";
    }
}
