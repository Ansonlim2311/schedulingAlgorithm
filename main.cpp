#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>
#include <climits>
#include <algorithm>

using namespace std;

void createGantt(vector<string> border,  vector<string> ganttChart, vector<string> ganttChartTime, int ganttChartCounter, int ganttChartTimeCounter, int borderCounter) {
    for (int i = 0; i < borderCounter; i++) {
        cout << border[i];
    }
    cout << "-" << endl;

    for (int i = 0; i < ganttChartCounter; i++) {
        cout << ganttChart[i];
    }
    cout << "|" << endl;

    for (int i = 0; i < borderCounter; i++) {
        cout << border[i];
    }
    cout << "-" << endl;

    for (int i = 0; i < ganttChartTimeCounter; i++) {
        cout << ganttChartTime[i];
    }
    cout << endl;
}

void createTable(int arrivalTime[], int burstTime[], int finishTime[], int turnaroundTime[], int waitingTime[], int priority[], int numProcesses) {
    
    cout << endl << "Process Details:" << endl;
    cout << "     Arrival Time   " << "Burst Time   " << "Priority   " << "Finish Time   " << "Turnaround Time   " << "Waiting Time" << endl;
    for (int i = 0; i < numProcesses; i++) {
        cout << "P" << i
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

    cout << "Total Turnaround Time   : " << averageTurnaroundTime << endl;
    averageTurnaroundTime /= numProcesses;
    cout << "Average Turnaround Time : " << averageTurnaroundTime << endl;

    cout << "Total Waiting Time      : " << averageWaitingTime << endl;
    averageWaitingTime /= numProcesses;
    cout << "Average Waiting Time    : " << averageWaitingTime << endl << endl;
}

void roundRobin(int arrivalTime[], int burstTime[], int waitingTime[], int turnaroundTime[], int priority[], int remainingBurstTime[], int numProcesses, int finishTime[], int timeQuantum) {
    int time = 0, gantt = 0, completed = 0, counter = 0;
    int quantum = timeQuantum;
    vector<string> border, ganttChart, ganttChartTime;
    ganttChartTime.push_back("0");
    int ganttCounter = 1;

    queue<int> readyQueue;
    bool processFinished[numProcesses] = {false};
    bool inReadyQueue[numProcesses] = {false};  // Tracks if a process is in the queue
    int completionTime[numProcesses] = {0};  // Stores when each process completes

    cout << endl << "Round Robin with Quantum " << quantum << endl;

    while (completed != numProcesses) {
        // Add processes to the ready queue if their arrival time has passed
        for (int i = 0; i < numProcesses; i++) {
            if (!processFinished[i] && arrivalTime[i] <= time && !inReadyQueue[i]) {
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
                border.push_back("-------");
                // cout << "Process P" << currentProcess << " executed for " << quantum << " units of time. Time now: " << time << endl;
                ganttChart.push_back("|  P" + to_string(currentProcess) + "  ");
                if (time >= 10) {
                    ganttChartTime.push_back("     " + to_string(time));
                } 
                else {
                    ganttChartTime.push_back("      " + to_string(time));
                }
            }
            else {
                time += remainingBurstTime[currentProcess];
                turnaroundTime[currentProcess] = time - arrivalTime[currentProcess];
                waitingTime[currentProcess] = turnaroundTime[currentProcess] - burstTime[currentProcess];
                // cout << "Process P" << currentProcess << " executed for " << remainingBurstTime[currentProcess] << " units of time. Time now: " << time << endl;
                if (remainingBurstTime[currentProcess] == quantum) {
                    border.push_back("-------");
                    ganttChart.push_back("|  P" + to_string(currentProcess) + "  ");
                    if (time >= 10) {
                        ganttChartTime.push_back("     " + to_string(time));
                    } 
                    else {
                        ganttChartTime.push_back("      " + to_string(time));
                    }
                }
                else {
                    border.push_back("-----");
                    ganttChart.push_back("| P" + to_string(currentProcess) + " ");
                    if (time >= 10) {
                        ganttChartTime.push_back("   " + to_string(time));
                    }
                    else {
                        ganttChartTime.push_back("    " + to_string(time));
                    }
                }
                remainingBurstTime[currentProcess] = 0;
                processFinished[currentProcess] = true;  // Mark this process as finished
            }

            counter++;
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
                completed++;
            }
        }
        else {
            time++;
        }
    }

    createGantt(border, ganttChart, ganttChartTime, gantt, ganttCounter, counter);
    createTable(arrivalTime, burstTime, finishTime, turnaroundTime, waitingTime, priority, numProcesses);
    cout << endl;
    calculation(numProcesses, turnaroundTime, waitingTime);
}

void SJN(int arrivalTime[], int burstTime[], int waitingTime[], int turnaroundTime[], int priority[], int remainingBurstTime[], int numProcesses, int finishTime[]) {
    vector<string> border, ganttChart, ganttChartTime;
    int ganttChartCounter = 0, ganttChartTimeCounter = 0, borderCounter = 0, time = 0;
    int completed = 0;
    bool processFinished[numProcesses] = {false};
    ganttChartTime.push_back("0");

    cout << endl;
    cout << "Shortest Job Next" << endl;

    while (completed != numProcesses) {
        int currentProcess = -1;
        int smallestBurstTime = INT_MAX;

        // Find the next process with the smallest burst time that has arrived
        for (int i = 0; i < numProcesses; i++) {
            if (arrivalTime[i] <= time && !processFinished[i] && burstTime[i] < smallestBurstTime) {
                smallestBurstTime = burstTime[i];
                currentProcess = i;
            }
        }

        if (currentProcess == -1) {
            // No process is ready to execute, increment time
            time++;
            ganttChartTime.push_back("    " + to_string(time));
            continue;
        }

        time += burstTime[currentProcess];
        turnaroundTime[currentProcess] = time - arrivalTime[currentProcess];
        waitingTime[currentProcess] = turnaroundTime[currentProcess] - burstTime[currentProcess];
        finishTime[currentProcess] = time;
        processFinished[currentProcess] = true;
        completed++;
        
        // Update Gantt chart
        border.push_back("-------");
        ganttChart.push_back("|  P" + to_string(currentProcess) + "  ");

        if (time >= 10) {
            ganttChartTime.push_back("     " + to_string(time));
        } else {
            ganttChartTime.push_back("      " + to_string(time));
        }

        ganttChartCounter++;
        ganttChartTimeCounter++;
        borderCounter++;
    }

    ganttChartTime.push_back("      " + to_string(time));
    ganttChartTimeCounter++;

    createGantt(border, ganttChart, ganttChartTime, ganttChartCounter, ganttChartTimeCounter, borderCounter);
    createTable(arrivalTime, burstTime, finishTime, turnaroundTime, waitingTime, priority, numProcesses);
    cout << endl;
    calculation(numProcesses, turnaroundTime, waitingTime);
}

void preemptivePriority(int arrivalTime[], int burstTime[], int waitingTime[], int turnaroundTime[], int priority[], int remainingBurstTime[], int numProcesses, int finishTime[]) {

    int time = 0, ganttChartCounter = 0, completed = 0, previousProcess = -1, borderCounter = 0, swapCounter = 0;

    bool processFinished[numProcesses] = {false};
    vector<string> border, ganttChart, ganttChartTime;
    int ganttChartTimeCounter = 1;

    cout << endl << "Preemptive Priority" << endl;

    while (completed != numProcesses) {
        int minPriority = INT_MAX;
        int currentProcess = -1;

        for (int i = 0; i < numProcesses; i++) {
            if (arrivalTime[i] <= time && !processFinished[i]) {
                if (priority[i] < minPriority) {
                    minPriority = priority[i];
                    currentProcess = i;
                }
            }
        }

        if (currentProcess == -1) {
            time++;
            continue;
        }

        if (currentProcess != previousProcess) {
            swapCounter++;

            border.push_back("------");
            ganttChart.push_back("|  P" + to_string(currentProcess) + "  ");
            if (time == 0) {
                ganttChartTime.push_back("0");
            }
            else if (time >= 10) {
                ganttChartTime.push_back("     " + to_string(time));
            } 
            else {
                ganttChartTime.push_back("      " + to_string(time));
            }
            borderCounter++;
            ganttChartCounter++;
            ganttChartTimeCounter++;
        }

        remainingBurstTime[currentProcess]--;
        time++;
        previousProcess = currentProcess;

        // cout << "Process P" << currentProcess << " executed at time " << time << endl;

        if (remainingBurstTime[currentProcess] == 0) {
            border.push_back("-");
            finishTime[currentProcess] = time;
            processFinished[currentProcess] = true;
            completed++;
            borderCounter++;
        }
    }

    ganttChartTime.push_back("     " + to_string(time));

    for (int i = 0; i < numProcesses; i++) {
        turnaroundTime[i] = finishTime[i] - arrivalTime[i];
        waitingTime[i] = turnaroundTime[i] - burstTime[i];
    }

    if (swapCounter > numProcesses) {
        swapCounter = swapCounter - numProcesses;
        for (int i = 0; i < swapCounter; i++) {
            border.push_back("-");
            borderCounter++;
        }
    }
    
    createGantt(border, ganttChart, ganttChartTime, ganttChartCounter, ganttChartTimeCounter, borderCounter);
    createTable(arrivalTime, burstTime, finishTime, turnaroundTime, waitingTime, priority, numProcesses);
    cout << endl;
    calculation(numProcesses, turnaroundTime, waitingTime);
}

void non_preemptivePriority(int arrivalTime[], int burstTime[], int waitingTime[], int turnaroundTime[], int priority[], int remainingBurstTime[], int numProcesses, int finishTime[]) {
    vector<string> border, ganttChart, ganttChartTime;
    int ganttChartCounter = 0, ganttChartTimeCounter = 0, borderCounter = 0, time = 0;
    int completed = 0;
    bool processFinished[numProcesses] = {false};
    ganttChartTime.push_back("0");

    cout << endl;
    cout << "Non Preeemptive Priority" << endl;

    while (completed != numProcesses) {
        int currentProcess = -1;
        int highestPriority = INT_MAX;

        // Find the next process with the smallest burst time that has arrived
        for (int i = 0; i < numProcesses; i++) {
            if (arrivalTime[i] <= time && !processFinished[i] && priority[i] < highestPriority) {
                highestPriority = priority[i];
                currentProcess = i;
            }
        }

        if (currentProcess == -1) {
            // No process is ready to execute, increment time
            time++;
            ganttChartTime.push_back("    " + to_string(time));
            continue;
        }

        time += burstTime[currentProcess];
        turnaroundTime[currentProcess] = time - arrivalTime[currentProcess];
        waitingTime[currentProcess] = turnaroundTime[currentProcess] - burstTime[currentProcess];
        finishTime[currentProcess] = time;
        processFinished[currentProcess] = true;
        completed++;
        
        // Update Gantt chart
        border.push_back("-------");
        ganttChart.push_back("|  P" + to_string(currentProcess) + "  ");

        if (time >= 10) {
            ganttChartTime.push_back("     " + to_string(time));
        } else {
            ganttChartTime.push_back("      " + to_string(time));
        }

        ganttChartCounter++;
        ganttChartTimeCounter++;
        borderCounter++;
    }

    ganttChartTime.push_back("      " + to_string(time));
    ganttChartTimeCounter++;

    createGantt(border, ganttChart, ganttChartTime, ganttChartCounter, ganttChartTimeCounter, borderCounter);
    createTable(arrivalTime, burstTime, finishTime, turnaroundTime, waitingTime, priority, numProcesses);
    cout << endl;
    calculation(numProcesses, turnaroundTime, waitingTime);

}

void userSelection(int arrivalTime[], int burstTime[], int waitingTime[], int turnaroundTime[], int priority[], int remainingBurstTime[], int numProcesses, int finishTime[]) {
    int choice;

    cout << "Choose scheduling algorithm:\n";
    cout << "1. Shortest Job Next\n";
    cout << "2. Preemptive Priority\n";
    cout << "3. Non-Preemptive Priority\n";
    cout << "4. Exit The Program\n";

    cout << "Enter your choice: ";
    cin >> choice;

    for (int i = 0; i < numProcesses; i++) {
        remainingBurstTime[i] = burstTime[i];
        }

    switch (choice) {
        case 1:
            SJN(arrivalTime, burstTime, waitingTime, turnaroundTime, remainingBurstTime, priority, numProcesses, finishTime);
            userSelection(arrivalTime, burstTime, waitingTime, turnaroundTime, priority, remainingBurstTime, numProcesses, finishTime);
            break;
        case 2:
            preemptivePriority(arrivalTime, burstTime, waitingTime, turnaroundTime, priority, remainingBurstTime, numProcesses, finishTime);
            userSelection(arrivalTime, burstTime, waitingTime, turnaroundTime, priority, remainingBurstTime, numProcesses, finishTime);
            break;
        case 3:
            non_preemptivePriority(arrivalTime, burstTime, waitingTime, turnaroundTime, priority, remainingBurstTime, numProcesses, finishTime);
            userSelection(arrivalTime, burstTime, waitingTime, turnaroundTime, priority, remainingBurstTime, numProcesses, finishTime);
            break;
        case 4:
        cout << endl << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl << endl;
            userSelection(arrivalTime, burstTime, waitingTime, turnaroundTime, priority, remainingBurstTime, numProcesses, finishTime);
    }
}

int main() {

    int numProcesses;
    int timeQuantum;

    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    if (numProcesses < 3 || numProcesses > 10) {
        cout << "Number of processes must be between 3 and 10." << endl;
        return 0;
    }

    int arrivalTime[numProcesses], burstTime[numProcesses], waitingTime[numProcesses], 
        turnaroundTime[numProcesses], priority[numProcesses], finishTime[numProcesses], remainingBurstTime[numProcesses];

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

    cout << "Enter Time Quantum For Round Robin: ";
    cin >> timeQuantum;

    roundRobin(arrivalTime, burstTime, waitingTime, turnaroundTime, priority, remainingBurstTime, numProcesses, finishTime, timeQuantum);

    userSelection(arrivalTime, burstTime, waitingTime, turnaroundTime, priority, remainingBurstTime, numProcesses, finishTime);
}