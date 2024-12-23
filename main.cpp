#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

void createTable(int arrivalTime[], int burstTime[], int finishTime[], int turnaroundTime[], int waitingTime[], int priority[], int numProcesses) {
    
    cout << endl << "Process Details:" << endl;
    cout << "     Arrival Time   " << "Burst Time   " << "Priority   " << "Finish Time   " << "Turnaround Time   " << "Waiting Time" << endl;
    for (int i = 0; i < numProcesses; i++) {
        cout << "P" << i + 1
             << setw(4) << arrivalTime[i]
             << setw(15) << burstTime[i]
             << setw(13) << priority[i]
             << setw(12) << finishTime[i]
             << setw(14) << turnaroundTime[i] 
             << setw(18) << waitingTime[i] 
             << endl;
    }
}

void roundRobin(int arrivalTime[], int burstTime[], int waitingTime[], int turnaroundTime[], int priority[], int remainingBurstTime[], int numProcesses, int finishTime[]) {
    float averageWaitingTime = 0, averageTurnaroundTime = 0;
    int time = 0;
    int quantum = 3;

    queue<int> readyQueue;
    bool processFinished[numProcesses] = {false};  // Process completion tracker
    bool inReadyQueue[numProcesses] = {false};  // Tracks if a process is in the queue
    int completionTime[numProcesses] = {0};  // Stores when each process completes

    cout << endl << "Round Robin with Quantum 3" << endl << endl;

    while (true) {
        bool allFinished = true;  // Flag to check if all processes are finished
        // Add processes to the ready queue if their arrival time has passed
        for (int i = 0; i < numProcesses; i++) {
            if (!processFinished[i] && arrivalTime[i] <= time &&!inReadyQueue[i]) {
                readyQueue.push(i);
                inReadyQueue[i] = true;  // Mark process as added to the ready queue
            }
        }
        // Process the queue until it's empty
        if (!readyQueue.empty()) {
            int currentProcess = readyQueue.front();

            // Check if the process can execute within the quantum
            if (remainingBurstTime[currentProcess] > quantum) {
                time += quantum;
                remainingBurstTime[currentProcess] -= quantum;
                // cout << "Process P" << currentProcess << " executed for " << quantum << " units of time. Time now: " << time << endl;
                cout << "| P" << currentProcess << " ";
            } else {
                time += remainingBurstTime[currentProcess];
                turnaroundTime[currentProcess] = time - arrivalTime[currentProcess];
                waitingTime[currentProcess] = turnaroundTime[currentProcess] - burstTime[currentProcess];
                // cout << "Process P" << currentProcess << " executed for " << remainingBurstTime[currentProcess] << " units of time. Time now: " << time << endl;
                cout << "|P" << currentProcess << "";
                remainingBurstTime[currentProcess] = 0;
                processFinished[currentProcess] = true;  // Mark this process as finished
            }

            // After executing, check for new arrivals
            for (int i = 0; i < numProcesses; i++) {
                if (!processFinished[i] && arrivalTime[i] <= time && !inReadyQueue[i]) {
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
                // cout << "Process P" << currentProcess << " completed at time " << time << endl;
                finishTime[currentProcess] = time;
                processFinished[currentProcess] = true;
            }
        }
        else {
            time++;
        }
        // Check if all processes are finished
        bool finishedAll = true;
        for (int i = 0; i < numProcesses; i++) {
            if (!processFinished[i]) {
                finishedAll = false;
                break;
            }
        }
        if (finishedAll) {
            cout << "|" << endl;
            break;
        }
    }

    // Calculate Waiting Time and Turnaround Time
    for (int i = 0; i < numProcesses; i++) {
        averageWaitingTime += waitingTime[i];
        averageTurnaroundTime += turnaroundTime[i];
    }

    averageWaitingTime /= numProcesses;
    averageTurnaroundTime /= numProcesses;

    createTable(arrivalTime, burstTime, finishTime, turnaroundTime, waitingTime, priority, numProcesses);

    cout << endl;
    cout << "Average Turnaround Time: " << averageTurnaroundTime << endl;
    cout << "Average Waiting Time   : " << averageWaitingTime << endl << endl;
}

void SJN(int arrivalTime[], int burstTime[], int waitingTime[], int turnaroundTime[], int remainingBurstTime[], int numProcesses, int finishTime[]) {

}

void preemptivePriority(int arrivalTime[], int burstTime[], int waitingTime[], int turnaroundTime[], int priority[], int remainingBurstTime[], int numProcesses, int finishTime[]) {

}

void non_preemptivePriority(int arrivalTime[], int burstTime[], int waitingTime[], int turnaroundTime[], int priority[], int remainingBurstTime[], int numProcesses, int finishTime[]) {

}

int main() {

    int numProcesses;

    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    if (numProcesses < 3 || numProcesses > 10) {
        cout << "Number of processes must be between 3 and 10." << endl;
        return 0;
    }

    int arrivalTime[numProcesses], burstTime[numProcesses], waitingTime[numProcesses], turnaroundTime[numProcesses], priority[numProcesses], finishTime[numProcesses];
    int remainingBurstTime[numProcesses];

    cout << "Enter arrival times for each process:\n";
    for (int i = 0; i < numProcesses; i++) {
        if (i == 0) {
            cout << "Process P" << i << ": ";
            cin >> arrivalTime[i];
        } 
        else {
            cout << "Process P" << i << ": ";
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
            cout << "Process P" << i << ": ";
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
                cout << "Process P" << i << ": ";
            cin >> priority[i]; 
        }
    }

    roundRobin(arrivalTime, burstTime, waitingTime, turnaroundTime, priority, remainingBurstTime, numProcesses, finishTime);

    int choice;

    cout << "Choose scheduling algorithm:\n";
    cout << "1. Shortest Job Next\n";
    cout << "2. Preemptive Priority\n";
    cout << "3. Non-Preemptive Priority\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            SJN(arrivalTime, burstTime, waitingTime, turnaroundTime, remainingBurstTime, numProcesses, finishTime);
            break;
        case 2:
            preemptivePriority(arrivalTime, burstTime, waitingTime, turnaroundTime, priority, remainingBurstTime, numProcesses, finishTime);
            break;
        case 3:
            non_preemptivePriority(arrivalTime, burstTime, waitingTime, turnaroundTime, priority, remainingBurstTime, numProcesses, finishTime);
            break;
        default:
            cout << "Invalid choice!";
    }
}
