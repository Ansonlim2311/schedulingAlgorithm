#include <iostream>
#include <queue>
#include <vector>

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
    int remainingBurstTime[numProcesses];  // For tracking the remaining burst time of processes
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
        remainingBurstTime[i] = burstTime[i];  // Initialize remaining burst time
    }

    cout << "Enter priority for each process:\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << "Process P" << i + 1 << ": ";
        cin >> priority[i];
    }

    // Round Robin Scheduling with Quantum of 3
    int quantum = 3;  // Time quantum
    int time = 0;     // Start time
    queue<int> readyQueue;  // Queue to manage ready processes
    bool isFinished[numProcesses] = {false};  // Array to track if a process is completed
    bool inReadyQueue[numProcesses] = {false};  // Track if a process is in the ready queue

    // Loop until all processes are completed
    while (true) {
        bool allFinished = true;  // Flag to check if all processes are finished

        // Add processes to the ready queue if their arrival time has passed
        for (int i = 0; i < numProcesses; i++) {
            if (!isFinished[i] && arrivalTime[i] <= time && !inReadyQueue[i]) {
                readyQueue.push(i);
                inReadyQueue[i] = true;  // Mark process as added to the ready queue
            }
        }

        // Process the queue until it's empty
        if (!readyQueue.empty()) {
            int currentProcess = readyQueue.front();
            readyQueue.pop();
            inReadyQueue[currentProcess] = false;  // Remove from ready queue

            // Check if the process can execute within the quantum
            if (remainingBurstTime[currentProcess] > quantum) {
                remainingBurstTime[currentProcess] -= quantum;
                time += quantum;
                cout << "Process P" << currentProcess + 1 << " executed for " << quantum << " units of time. Remaining burst time: " << remainingBurstTime[currentProcess] << endl;
                readyQueue.push(currentProcess);  // Re-add to the queue if not finished
            } else {
                time += remainingBurstTime[currentProcess];
                cout << "Process P" << currentProcess + 1 << " executed for " << remainingBurstTime[currentProcess] << " units of time. Completed at time " << time << endl;
                remainingBurstTime[currentProcess] = 0;
                isFinished[currentProcess] = true;  // Mark this process as finished
            }
        }

        // If all processes are finished, break the loop
        bool finishedAll = true;
        for (int i = 0; i < numProcesses; i++) {
            if (!isFinished[i]) {
                finishedAll = false;
                break;
            }
        }

        if (finishedAll) break;
    }

    // Calculate Waiting Time and Turnaround Time
    for (int i = 0; i < numProcesses; i++) {
        turnaroundTime[i] = time - arrivalTime[i];  // Turnaround Time = Completion Time - Arrival Time
        waitingTime[i] = turnaroundTime[i] - burstTime[i];  // Waiting Time = Turnaround Time - Burst Time

        averageWaitingTime += waitingTime[i];
        averageTurnaroundTime += turnaroundTime[i];
    }

    // Calculate average Waiting Time and Turnaround Time
    averageWaitingTime /= numProcesses;
    averageTurnaroundTime /= numProcesses;

    // Output results
    cout << "\nProcess Details:\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << "Process P" << i + 1 << ": Waiting Time = " << waitingTime[i] << ", Turnaround Time = " << turnaroundTime[i] << endl;
    }

    cout << "\nAverage Waiting Time: " << averageWaitingTime << endl;
    cout << "Average Turnaround Time: " << averageTurnaroundTime << endl;
}

int main() {
    roundRobin();  // Call the Round Robin function
    return 0;
}