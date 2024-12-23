#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

void createGantt(string border[],  string ganttChart[], string ganttChartTime[], int gantt, int ganttCounter) {
    for (int i = 0; i < gantt; i++) {
        cout << border[i];
    }
    cout << "-" << endl;

    for (int i = 0; i < gantt; i++) {
        cout << ganttChart[i];
    }
    cout << "|" << endl;

    for (int i = 0; i < gantt; i++) {
        cout << border[i];
    }
    cout << "-" << endl;

    for (int i = 0; i < ganttCounter; i++) {
        cout << ganttChartTime[i];
    }
    cout << endl;
}

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

void calculation(int numProcesses, int turnaroundTime[], int waitingTime[]) {
    float averageWaitingTime = 0, averageTurnaroundTime = 0;

    for (int i = 0; i < numProcesses; i++) {
        averageWaitingTime += waitingTime[i];
        averageTurnaroundTime += turnaroundTime[i];
    }

    cout << "Total Turnaround Time  : " << averageTurnaroundTime << endl;
    averageTurnaroundTime /= numProcesses;
    cout << "Average Turnaround Time: " << averageTurnaroundTime << endl;

    cout << "Total Waiting Time     : " << averageWaitingTime << endl;
    averageWaitingTime /= numProcesses;
    cout << "Average Waiting Time   : " << averageWaitingTime << endl << endl;
}

void roundRobin(int arrivalTime[], int burstTime[], int waitingTime[], int turnaroundTime[], int priority[], int remainingBurstTime[], int numProcesses, int finishTime[]) {
    int time = 0, gantt = 0;
    int quantum = 3;
    string border[50], ganttChart[50], ganttChartTime[50];
    ganttChartTime[0] = "0";
    int ganttCounter = 1;

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
                border[gantt] = "-------";
                // cout << "Process P" << currentProcess << " executed for " << quantum << " units of time. Time now: " << time << endl;
                ganttChart[gantt] = "|  P" + to_string(currentProcess) + "  ";
                // cout << "|  P" << currentProcess << "  ";
                if (time >= 10) {
                    ganttChartTime[ganttCounter] =  "     " + to_string(time);
                } 
                else {
                    ganttChartTime[ganttCounter] =  "      " + to_string(time);
                }
            } 
            else {
                time += remainingBurstTime[currentProcess];
                turnaroundTime[currentProcess] = time - arrivalTime[currentProcess];
                waitingTime[currentProcess] = turnaroundTime[currentProcess] - burstTime[currentProcess];
                border[gantt] = "-----";
                // cout << "Process P" << currentProcess << " executed for " << remainingBurstTime[currentProcess] << " units of time. Time now: " << time << endl;
                ganttChart[gantt] = "| P" + to_string(currentProcess) + " ";
                // cout << "| P" << currentProcess << " ";
                if (time >= 10) {
                    ganttChartTime[ganttCounter] =  "   " + to_string(time);
                }
                else {
                    ganttChartTime[ganttCounter] =  "    " + to_string(time);
                }
                remainingBurstTime[currentProcess] = 0;
                processFinished[currentProcess] = true;  // Mark this process as finished
            }

            gantt++;
            ganttCounter++;

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
            break;
        }
    }

    createGantt(border, ganttChart, ganttChartTime, gantt, ganttCounter);
    createTable(arrivalTime, burstTime, finishTime, turnaroundTime, waitingTime, priority, numProcesses);
    cout << endl;
    calculation(numProcesses, turnaroundTime, waitingTime);
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