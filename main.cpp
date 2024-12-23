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

    while (true) {
        bool allFinished = true;  // Flag to check if all processes are finished
        // Add processes to the ready queue if their arrival time has passed
        for (int i = 0; i < numProcesses; i++) {
            if (!isFinished[i] && arrivalTime[i] <= time &&!inReadyQueue[i]) {
                readyQueue.push(i);
                inReadyQueue[i] = true;  // Mark process as added to the ready queue
            }
        }
        // Process the queue until it's empty
        if (!readyQueue.empty()) {
            int currentProcess = readyQueue.front();
            // readyQueue.pop();
            // inReadyQueue[currentProcess] = false;

            // Check if the process can execute within the quantum
            if (remainingBurstTime[currentProcess] > quantum) {
                time += quantum;
                remainingBurstTime[currentProcess] -= quantum;
            } else {
                time += remainingBurstTime[currentProcess];
                turnaroundTime[currentProcess] = time - arrivalTime[currentProcess];
                waitingTime[currentProcess] = turnaroundTime[currentProcess] - burstTime[currentProcess];
                remainingBurstTime[currentProcess] = 0;
                isFinished[currentProcess] = true;  // Mark this process as finished
            }

            cout << "Process P" << currentProcess 
                 << " executed for " << quantum 
                 << " units of time. Time now: " << time << endl;

            // After executing, check for new arrivals
            for (int i = 0; i < numProcesses; i++) {
                if (!isFinished[i] && arrivalTime[i] <= time && !inReadyQueue[i]) {
                    readyQueue.push(i);
                    inReadyQueue[i] = true;
                }
            }
            readyQueue.pop();
            inReadyQueue[currentProcess] = false;

            if (remainingBurstTime[currentProcess] > 0) {
                readyQueue.push(currentProcess);
                inReadyQueue[currentProcess] = true;
            } else {
                cout << "Process P" << currentProcess + 1 
                     << " completed at time " << time << endl;
                isFinished[currentProcess] = true;
            }
        }
        // Check if all processes are finished
        bool finishedAll = true;
        for (int i = 0; i < numProcesses; i++) {
            if (!isFinished[i]) {
                finishedAll = false;
                break;
            }
        }
        if (finishedAll) break;
    }

    // Display results
    cout << "\nProcess Details:\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << "Process P" << i + 1 << ": Waiting Time = " 
             << waitingTime[i] << ", Turnaround Time = " 
             << turnaroundTime[i] << endl;
    }

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

void SJN(int arrivalTime[], int burstTime[], int waitingTime[], int turnaroundTime[], int remainingBurstTime[], int numProcesses) {

}

void preemptivePriority(int arrivalTime[], int burstTime[], int waitingTime[], int turnaroundTime[], int priority[], int remainingBurstTime[], int numProcesses) {

}

void non_preemptivePriority(int arrivalTime[], int burstTime[], int waitingTime[], int turnaroundTime[], int priority[], int remainingBurstTime[], int numProcesses) {

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
            cin >> arrivalTime[i];
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
            cin >> burstTime[i];
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
            cin >> priority[i];
        } else {
                cout << "Process P" << i + 1 << ": ";
            cin >> priority[i]; 
        }
    }

    roundRobin(arrivalTime, burstTime, waitingTime, turnaroundTime, priority, remainingBurstTime, numProcesses);

    int choice;

    cout << "Choose scheduling algorithm:\n";
    cout << "1. Shortest Job Next\n";
    cout << "2. Preemptive Priority\n";
    cout << "3. Non-Preemptive Priority\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            SJN(arrivalTime, burstTime, waitingTime, turnaroundTime, remainingBurstTime, numProcesses);
            break;
        case 2:
            preemptivePriority(arrivalTime, burstTime, waitingTime, turnaroundTime, priority, remainingBurstTime, numProcesses);
            break;
        case 3:
            non_preemptivePriority(arrivalTime, burstTime, waitingTime, turnaroundTime, priority, remainingBurstTime, numProcesses);
            break;
        default:
            cout << "Invalid choice!";
    }
}
