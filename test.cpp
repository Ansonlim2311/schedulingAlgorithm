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
        remainingBurstTime[i] = burstTime[i];  // Initialize remaining burst time
    }

    cout << "Enter priority for each process:\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << "Process P" << i + 1 << ": ";
        cin >> priority[i];
    }

    // Round Robin Scheduling with Quantum of 3
    int quantum = 3;
    int time = 0;
    queue<int> readyQueue;
    bool isFinished[numProcesses] = {false};
    bool inReadyQueue[numProcesses] = {false};

    // Loop until all processes are completed
    while (true) {
        bool allFinished = true;

        // Add processes to ready queue if their arrival time <= current time
        for (int i = 0; i < numProcesses; i++) {
            if (!isFinished[i] && arrivalTime[i] <= time && !inReadyQueue[i]) {
                readyQueue.push(i);
                inReadyQueue[i] = true;
            }
        }

        // Process the queue until it's empty
        if (!readyQueue.empty()) {
            int currentProcess = readyQueue.front();
            readyQueue.pop();
            inReadyQueue[currentProcess] = false;

            // Check if the process can execute within the quantum
            int execTime = min(quantum, remainingBurstTime[currentProcess]);
            remainingBurstTime[currentProcess] -= execTime;
            time += execTime;

            cout << "Process P" << currentProcess + 1 
                 << " executed for " << execTime 
                 << " units of time. Time now: " << time << endl;

            // After executing, check for new arrivals
            for (int i = 0; i < numProcesses; i++) {
                if (!isFinished[i] && arrivalTime[i] <= time && !inReadyQueue[i]) {
                    readyQueue.push(i);
                    inReadyQueue[i] = true;
                }
            }

            // If the process is not finished, re-add it to the queue
            if (remainingBurstTime[currentProcess] > 0) {
                readyQueue.push(currentProcess);
                inReadyQueue[currentProcess] = true;
            } else {
                cout << "Process P" << currentProcess + 1 
                     << " completed at time " << time << endl;
                isFinished[currentProcess] = true;
            }
        } else {
            // If no process is ready, increment time
            time++;
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

    // Calculate Waiting Time and Turnaround Time
    for (int i = 0; i < numProcesses; i++) {
        turnaroundTime[i] = time - arrivalTime[i];  
        waitingTime[i] = turnaroundTime[i] - burstTime[i];

        averageWaitingTime += waitingTime[i];
        averageTurnaroundTime += turnaroundTime[i];
    }

    averageWaitingTime /= numProcesses;
    averageTurnaroundTime /= numProcesses;

    // Display results
    cout << "\nProcess Details:\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << "Process P" << i + 1 << ": Waiting Time = " 
             << waitingTime[i] << ", Turnaround Time = " 
             << turnaroundTime[i] << endl;
    }

    cout << "\nAverage Waiting Time: " << averageWaitingTime << endl;
    cout << "Average Turnaround Time: " << averageTurnaroundTime << endl;
}

int main() {
    roundRobin();
    return 0;
}
