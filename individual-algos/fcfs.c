// first come first serve algorithm
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Process {
  char pid[5];
  int arrival;  // for arrival time or priority
  int burst;
  int completion;
};

struct Gantt {
  char pid[5];
  int start;
  int done;
};

void collector(int choice, int items, struct Process *process) {
  puts("\nEnter values...");
  if (choice == 3) {
    puts("Priority and Burst Time");
  } else {
    puts("Arrival Time and Burst Time");
  }
  for (int i = 0; i < items; i++) {
    sprintf(process[i].pid, "P%d", i);
    printf("Enter for Process %d: ", i);
    fflush(stdin);
    scanf("%d %d", &process[i].arrival, &process[i].burst);
    process[i].completion = 0;
  }
}

void sort(int choice, int items, struct Process *process) {
  struct Process temp;

  if (choice == 2) {
    for (int i = 0; i < items; i++) {
      int min = i;
      for (int ii = i + 1; ii < items; ii++) {
        if (process[min].burst > process[ii].burst) {
          min = ii;
        }
      }

      if (min != i) {
        temp = process[min];
        process[min] = process[i];
        process[i] = temp;
      }
    }
  } else {
    for (int i = 0; i < items; i++) {
      int min = i;
      for (int ii = i + 1; ii < items; ii++) {
        if (process[min].arrival > process[ii].arrival) {
          min = ii;
        }
      }

      if (min != i) {
        temp = process[min];
        process[min] = process[i];
        process[i] = temp;
      }
    }
  }
}

void printChart(int items, struct Gantt *gantt) {
  printf("\n\n");
  for (int i = 0; i < items; i++) {
    printf("%-8d", gantt[i].start);
    if (gantt[i].done != gantt[i + 1].start) {
      printf("%-8d", gantt[i].done);
    }
  }
  printf("\n");
  for (int i = 0; i < items; i++) {
    printf("  %4s  ", gantt[i].pid);
    if (gantt[i].done != gantt[i + 1].start && (i + 1) < items) {
      printf("  %4s  ", "IDLE");
    }
  }
}
void fcfs(int items, struct Process *process) {
  struct Gantt gantt[items];
  float avg_tat, avg_wt = 0;
  int currentTime, waitTime, turnaroundTime = 0;
  printf("PID    AT    BT    Completion\n");
  for (int i = 0; i < items; i++) {
    strcpy(gantt[i].pid, process[i].pid);
    if (currentTime < process[i].arrival) {
      gantt[i].start = process[i].arrival;
      currentTime = currentTime + (process[i].arrival - currentTime);
    } else {
      gantt[i].start = currentTime;
    }
    currentTime = currentTime + process[i].burst;
    process[i].completion = currentTime;
    printf("%s\t%d\t%d\t%d\n", process[i].pid, process[i].arrival,
           process[i].burst, process[i].completion);
    gantt[i].done = process[i].completion;

    turnaroundTime = process[i].completion - process[i].arrival;
    avg_tat = avg_tat + turnaroundTime;
    waitTime = turnaroundTime - process[i].burst;
    avg_wt = avg_wt + waitTime;
  }
  avg_tat = avg_tat / (float)items;
  avg_wt = avg_wt / (float)items;
  printf("** Average Turn Around Time: %.6f **", avg_tat);
  printf("** Average Waiting Around Time: %.6f **", avg_wt);
  printChart(items, &gantt);
}

int main(int argc, char const *argv[]) {
  int choice;
  int items;
  int quantum;

  do {
    puts("-----Scheduling Algorithms-----");
    puts("1. FCFS");
    puts("2. SJF");
    puts("3. Priority Based");
    puts("4. Round Robin");
    puts("5. Exit");

    printf("Enter your choice: ");
    scanf("%d", &choice);
    if (choice == 5) {
      break;
    }

    if (choice == 4) {
      printf("\nEnter time quantum: ");
      scanf("%d", &quantum);
    }

    printf("\nHow many processes? ");
    scanf("%d", &items);
    struct Process Processes[items];  // initialize process array

    collector(choice, items, &Processes);
    switch (choice) {
      case 1:
        sort(choice, items, &Processes);
        fcfs(items, &Processes);
        // printer(items, &Processes);
        memset(Processes, '\0',
               sizeof(Processes));  // null the struct for the next iteration of
                                    // the program
        break;
      default:
        break;
    }
    printf("\nPress ENTER key to continue...\n");
    while (getchar() != '\n') {
    }
    getchar();
  } while (1);

  puts("\nterminating...");
  return 0;
}
