#include <stdio.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
} Process;

void scheduleProcesses(Process processes[], int numProcesses) {
    int currentTime = 0;
    int systemQueueIndex = 0;
    int userQueueIndex = 0;

    // Process queues
    Process systemQueue[MAX_PROCESSES];
    Process userQueue[MAX_PROCESSES];

    // Separate system and user processes
    for (int i = 0; i < numProcesses; i++) {
        if (processes[i].priority == 0) {
            systemQueue[systemQueueIndex++] = processes[i];
        } else {
            userQueue[userQueueIndex++] = processes[i];
        }
    }

    // Sort system and user processes by arrival time
    for (int i = 0; i < systemQueueIndex - 1; i++) {
        for (int j = 0; j < systemQueueIndex - i - 1; j++) {
            if (systemQueue[j].arrivalTime > systemQueue[j + 1].arrivalTime) {
                Process temp = systemQueue[j];
                systemQueue[j] = systemQueue[j + 1];
                systemQueue[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < userQueueIndex - 1; i++) {
        for (int j = 0; j < userQueueIndex - i - 1; j++) {
            if (userQueue[j].arrivalTime > userQueue[j + 1].arrivalTime) {
                Process temp = userQueue[j];
                userQueue[j] = userQueue[j + 1];
                userQueue[j + 1] = temp;
            }
        }
    }

    printf("System Queue:\n");
    for (int i = 0; i < systemQueueIndex; i++) {
        printf("PID: %d\t Arrival Time: %d\t Burst Time: %d\n",
            systemQueue[i].pid, systemQueue[i].arrivalTime, systemQueue[i].burstTime);
    }

    printf("\nUser Queue:\n");
    for (int i = 0; i < userQueueIndex; i++) {
        printf("PID: %d\t Arrival Time: %d\t Burst Time: %d\n",
            userQueue[i].pid, userQueue[i].arrivalTime, userQueue[i].burstTime);
    }

    printf("\nGantt Chart:\n");
    while (systemQueueIndex > 0 || userQueueIndex > 0) {
        if (systemQueueIndex > 0) {
            printf("P%d ", systemQueue[0].pid);
            currentTime += systemQueue[0].burstTime;
            systemQueue[0].burstTime = 0;
            for (int i = 1; i < systemQueueIndex; i++) {
                systemQueue[i].arrivalTime -= systemQueue[0].burstTime;
            }
            for (int i = 0; i < systemQueueIndex - 1; i++) {
                systemQueue[i] = systemQueue[i + 1];
            }
            systemQueueIndex--;
        } else if (userQueueIndex > 0) {
            printf("P%d ", userQueue[0].pid);
            currentTime += userQueue[0].burstTime;
            userQueue[0].burstTime = 0;
            for (int i = 1; i < userQueueIndex; i++) {
                userQueue[i].arrivalTime -= userQueue[0].burstTime;
            }
            for (int i = 0; i < userQueueIndex - 1; i++) {
                userQueue[i] = userQueue[i + 1];
            }
            userQueueIndex--;
        }
    }

    printf("\n\nTotal Execution Time: %d\n", currentTime);
}

int main() {
    int numProcesses;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    printf("Enter process details:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d:\n", i + 1);
        printf("PID: ");
        scanf("%d", &processes[i].pid);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
        printf("Priority (0 for system, 1 for user): ");
        scanf("%d", &processes[i].priority);
    }

    scheduleProcesses(processes, numProcesses);

    return 0;
}
