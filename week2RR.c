#include <stdio.h>

#define MAX_PROCESSES 10

struct Process {
    int processID;
    int burstTime;
    int priority;
    int waitingTime;
    int turnaroundTime;
    int remainingTime;
    int arrivalTime;
};

void calculateWaitingTime(struct Process processes[], int n);
void calculateTurnaroundTime(struct Process processes[], int n);
void schedulePriorityNonPreemptive(struct Process processes[], int n);
void schedulePriorityPreemptive(struct Process processes[], int n);
void scheduleRoundRobin(struct Process processes[], int n, int quantum);

int main() {
    int n, choice, quantum;

    struct Process processes[MAX_PROCESSES];

    printf("Enter the total number of processes (up to %d): ", MAX_PROCESSES);
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for process %d:\n", i + 1);
        processes[i].processID = i + 1;
        printf("Enter burst time: ");
        scanf("%d", &processes[i].burstTime);
        printf("Enter priority: ");
        scanf("%d", &processes[i].priority);
        processes[i].remainingTime = processes[i].burstTime;
    }

    printf("\nSelect the CPU scheduling algorithm:\n");
    printf("1. Priority (Non-preemptive)\n");
    printf("2. Priority (Preemptive)\n");
    printf("3. Round Robin\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            schedulePriorityNonPreemptive(processes, n);
            break;
        case 2:
            schedulePriorityPreemptive(processes, n);
            break;
        case 3:
            printf("Enter quantum size for Round Robin: ");
            scanf("%d", &quantum);
            scheduleRoundRobin(processes, n, quantum);
            break;
        default:
            printf("Invalid choice.\n");
            return 1;
    }

    calculateWaitingTime(processes, n);
    calculateTurnaroundTime(processes, n);

    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processID, processes[i].burstTime,
               processes[i].priority, processes[i].waitingTime, processes[i].turnaroundTime);
    }

    return 0;
}

void calculateWaitingTime(struct Process processes[], int n) {
    processes[0].waitingTime = 0;

    for (int i = 1; i < n; i++) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }
}

void calculateTurnaroundTime(struct Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

void schedulePriorityNonPreemptive(struct Process processes[], int n) {
    struct Process temp;
    int i, j;

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (processes[i].priority > processes[j].priority) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void schedulePriorityPreemptive(struct Process processes[], int n) {
    int currentTime = 0;
    int completed = 0;
    int highestPriority = 9999;
    int highestPriorityIndex = -1;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0 && processes[i].priority < highestPriority &&
                processes[i].burstTime > 0 && processes[i].arrivalTime <= currentTime) {
                highestPriority = processes[i].priority;
                highestPriorityIndex = i;
            }
        }

        if (highestPriorityIndex != -1) {
            processes[highestPriorityIndex].remainingTime--;
            currentTime++;

            if (processes[highestPriorityIndex].remainingTime == 0) {
                completed++;
                processes[highestPriorityIndex].turnaroundTime = currentTime - processes[highestPriorityIndex].arrivalTime;
                highestPriority = 9999;
                highestPriorityIndex = -1;
            }
        } else {
            currentTime++;
        }
    }
}

void scheduleRoundRobin(struct Process processes[], int n, int quantum) {
    int currentTime = 0;
    int completed = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0) {
                if (processes[i].remainingTime <= quantum) {
                    currentTime += processes[i].remainingTime;
                    processes[i].remainingTime = 0;
                    processes[i].turnaroundTime = currentTime - processes[i].arrivalTime;
                    completed++;
                } else {
                    currentTime += quantum;
                    processes[i].remainingTime -= quantum;
                }
            }
        }
    }
}
