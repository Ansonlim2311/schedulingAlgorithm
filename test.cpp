#include <iostream>
#include <climits>

using namespace std;

void preemptivePriority() {
    int numProcesses;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    if (numProcesses < 3 || numProcesses > 10) {
        cout << "Number of processes must be between 3 and 10." << endl;
        return;
    }

    int arrivalTime[numProcesses], burstTime[numProcesses], remainingBurstTime[numProcesses];
    int priority[numProcesses], waitingTime[numProcesses], turnaroundTime[numProcesses], finishTime[numProcesses];
    bool processFinished[numProcesses] = {false};

    int time = 0, completed = 0;
    float averageWaitingTime = 0, averageTurnaroundTime = 0;

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


    // Preemptive Priority Scheduling Logic
    while (completed != numProcesses) {
        int minPriority = INT_MAX;
        int currentProcess = -1;

        // Find process with highest priority (lowest value) that has arrived
        for (int i = 0; i < numProcesses; i++) {
            if (arrivalTime[i] <= time && !processFinished[i]) {
                if (priority[i] < minPriority) {
                    minPriority = priority[i];
                    currentProcess = i;
                }
            }
        }

        if (currentProcess == -1) {
            time++;  // No process ready, increment time
            continue;
        }

        // Execute the selected process for 1 unit of time
        remainingBurstTime[currentProcess]--;
        time++;

        cout << "Process P" << currentProcess << " executed at time " << time << endl;

        // If process is completed
        if (remainingBurstTime[currentProcess] == 0) {
            finishTime[currentProcess] = time;
            processFinished[currentProcess] = true;
            completed++;
        }
    }

    // Calculate waiting time and turnaround time
    for (int i = 0; i < numProcesses; i++) {
        turnaroundTime[i] = finishTime[i] - arrivalTime[i];
        waitingTime[i] = turnaroundTime[i] - burstTime[i];

        averageWaitingTime += waitingTime[i];
        averageTurnaroundTime += turnaroundTime[i];
    }

    averageWaitingTime /= numProcesses;
    averageTurnaroundTime /= numProcesses;

    // Display results
    cout << "\nProcess Details:\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << "Process P" << i + 1 << ": Waiting Time = " << waitingTime[i]
             << ", Turnaround Time = " << turnaroundTime[i] << endl;
    }

    cout << "\nAverage Waiting Time: " << averageWaitingTime << endl;
    cout << "Average Turnaround Time: " << averageTurnaroundTime << endl;
}

int main() {
    preemptivePriority();
    return 0;
}