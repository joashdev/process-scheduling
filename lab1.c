/*
 * Author: Kent Joash A. Zamudio (https://github.com/ProCrust/)
 * For: CMSC 125 Operating Systems Laboratory
 * Details: CPU Scheduling Algorithm implemented in C.
 *          Includes (i) First Come, First Serve; (ii) Shortest Job First;
 *                   (iii) Priority-based; and, (iv) Round Robin.
 * Video: https://bit.ly/zamudio_125lab1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char pid[5];
  int arrival;    // for arrival time
  int burst;      // for burst time
  int remaining;  // for remaining burst time (sjf & roundrobin)
  int priority;   // for priority(priority based)
  int latestStart;
  int preemption;
  int complete;  // if process is complete or not
  int wt;
  int tat;
} Process;

typedef struct {
  char pid[5];
  int start;
  int done;
} Gantt;

// scheduling functions prototype
void fcfs(int items, Process *process);
void sjf_nonpreemptive(int items, Process *process);
// void sjf_preemptive(int items, Process *process);    // unimplemented
void priority(int items, Process *process);
void roundrobin(int items, int quantum, Process *process);

// auxillary functions prototype
void collector(int choice, int items, Process *process);
void printChart(int items, Gantt *gantt);
void printDetails(int items, Process *process);

int main(int argc, char *argv[]) {
  int items, choice, quantum, sjfOption;

  do {
    puts("\n-----Scheduling Algorithms-----");
    puts("1. FCFS");
    puts("2. SJF");
    puts("3. Priority Based");
    puts("4. Round Robin");
    puts("5. Exit");

    printf("Enter your choice: ");
    scanf("%d", &choice);
    if (choice == 5) {
      break;
    } else if (choice == 4) {
      printf("\nEnter time quantum: ");
      scanf("%d", &quantum);
    }
    // unimplemented preemptive sjf
    //  else if (choice == 2) {
    //   printf("\n1. Nonpreemptive SJF\n2. Preemptive SJF\nChoice: ");
    //   scanf("%d", &sjfOption);
    // }

    printf("\nHow many processes? ");
    scanf("%d", &items);
    Process Processes[items];              // initialize process array
    collector(choice, items, &Processes);  // collect processes
    switch (choice) {
      case 1:
        fcfs(items, &Processes);
        memset(Processes, '\0', sizeof(Processes));  // null struct
        break;
      case 2:
        sjf_nonpreemptive(items, &Processes);
        memset(Processes, '\0', sizeof(Processes));
        break;
      case 3:
        priority(items, &Processes);
        memset(Processes, '\0', sizeof(Processes));
        break;
      case 4:
        roundrobin(items, quantum, &Processes);
        memset(Processes, '\0', sizeof(Processes));
        break;
      default:
        break;
    }
    printf("\nPress ENTER key to continue...\n");
    while (getchar() != '\n') {
    }
    getchar();
  } while (1);

  puts("\nterminating...\n");

  return 0;
}

void fcfs(int items, Process *process) {
  Gantt gantt[items];
  Process temp;
  float avg_tat = 0, avg_wt = 0;
  int currentTime = 0, waitTime = 0, turnaroundTime = 0;
  int ganttIndex = 0;
  for (int i = 0; i < items; i++) {
    int min = i;
    // find one with earliest arrival
    for (int ii = i + 1; ii < items; ii++) {
      if (process[min].arrival > process[ii].arrival) {
        min = ii;
      }
    }

    // create new item on gantt chart
    strcpy(gantt[ganttIndex].pid, process[min].pid);
    if (currentTime < process[min].arrival) {
      gantt[ganttIndex].start = process[min].arrival;
      currentTime = currentTime + (process[i].arrival - currentTime);
    } else {
      gantt[ganttIndex].start = currentTime;
    }
    //recalculate latestStart
    process[min].latestStart = currentTime;

    // currentTime == completion of the current process
    currentTime = currentTime + process[min].burst;
    process[min].complete = currentTime;
    gantt[ganttIndex].done = currentTime;

    // turn around time and wait time of current process
    turnaroundTime = currentTime - process[min].arrival;
    waitTime = turnaroundTime - process[min].burst;

    // add to average time placeholders
    avg_tat = avg_tat + turnaroundTime;
    avg_wt = avg_wt + waitTime;

    // complete the process details
    process[min].tat = turnaroundTime;
    process[min].wt = waitTime;
    process[min].remaining = 0;
    process[min].preemption = 0;

    ganttIndex++;
    process[min].complete = 1;  // set complete to true
    // all done processes are move to the left side
    if (min != i) {
      temp = process[min];
      process[min] = process[i];
      process[i] = temp;
    }
  }
  // print process array
  printDetails(items, process);

  // solve average turnaround and wait time
  avg_tat = avg_tat / (float)items;
  avg_wt = avg_wt / (float)items;
  printf("\n\n** Average Turn Around Time: %.6f **", avg_tat);
  printf("\n** Average Waiting Time: %.6f **\n", avg_wt);
  // print gantt chart
  printChart(ganttIndex, &gantt);
  memset(gantt, 0, sizeof(gantt));  // nullify struct
}

void sjf_nonpreemptive(int items, Process *process) {
  Gantt gantt[items];
  Process temp;
  float avg_tat = 0, avg_wt = 0;
  int currentTime = 0, waitTime = 0, turnaroundTime = 0;
  int ganttIndex = 0;
  for (int i = 0; i < items; i++) {
    int min = i;
    // find process with shortest burst time
    for (int ii = i + 1; ii < items; ii++) {
      if (process[min].burst > process[ii].burst &&
          process[ii].arrival <= currentTime) {
        min = ii;
      }
    }

    // initialize new item to gantt
    strcpy(gantt[ganttIndex].pid, process[min].pid);
    if (currentTime < process[min].arrival) {
      gantt[ganttIndex].start = process[min].arrival;
      currentTime = currentTime + (process[i].arrival - currentTime);
    } else {
      gantt[ganttIndex].start = currentTime;
    }
    // recalculate latestStart
    process[min].latestStart = currentTime;

    // currentTime == completion of the current process
    currentTime = currentTime + process[min].burst;
    process[min].complete = currentTime;
    gantt[ganttIndex].done = currentTime;

    // turn around time and wait time of current process
    turnaroundTime = currentTime - process[min].arrival;
    waitTime = turnaroundTime - process[min].burst;

    // add to average time placeholders
    avg_tat = avg_tat + turnaroundTime;
    avg_wt = avg_wt + waitTime;

    // complete the process Details
    process[min].tat = turnaroundTime;
    process[min].wt = waitTime;
    process[min].remaining = 0;
    process[min].preemption = 0;

    ganttIndex++;
    if (min != i) {
      temp = process[min];
      process[min] = process[i];
      process[i] = temp;
    }
  }
  // print process array
  printDetails(items, process);

  // solve average times
  avg_tat = avg_tat / (float)items;
  avg_wt = avg_wt / (float)items;
  printf("\n\n** Average Turn Around Time: %.6f **", avg_tat);
  printf("\n** Average Waiting Time: %.6f **\n", avg_wt);
  // print gantt chart
  printChart(ganttIndex, &gantt);
  memset(gantt, 0, sizeof(gantt));  // nullify
}

void priority(int items, Process *process) {
  Gantt gantt[items];
  Process temp;
  float avg_tat = 0, avg_wt = 0;
  int currentTime = 0, waitTime = 0, turnaroundTime = 0;
  int ganttIndex = 0;
  for (int i = 0; i < items; i++) {
    int min = i;
    for (int ii = i + 1; ii < items; ii++) {
      if (process[min].priority > process[ii].priority) {
        min = ii;
      }
    }

    // initialize new item on gantt
    strcpy(gantt[ganttIndex].pid, process[min].pid);
    gantt[ganttIndex].start = currentTime;

    // recalculate latestStart
    process[min].latestStart = currentTime;

    // currentTime == completion of the current process
    currentTime = currentTime + process[min].burst;
    process[min].complete = currentTime;
    gantt[ganttIndex].done = currentTime;

    // turn around time and wait time of current process
    turnaroundTime = currentTime;
    waitTime = turnaroundTime - process[min].burst;

    // add to average time placeholders
    avg_tat = avg_tat + turnaroundTime;
    avg_wt = avg_wt + waitTime;

    // complete the process Details
    process[min].tat = turnaroundTime;
    process[min].wt = waitTime;
    process[min].remaining = 0;
    process[min].preemption = 0;

    ganttIndex++;
    if (min != i) {
      temp = process[min];
      process[min] = process[i];
      process[i] = temp;
    }
  }
  // print process array
  printDetails(items, process);

  // solve average times
  avg_tat = avg_tat / (float)items;
  avg_wt = avg_wt / (float)items;
  printf("\n\n** Average Turn Around Time: %.6f **", avg_tat);
  printf("\n** Average Waiting Time: %.6f **\n", avg_wt);
  // print gantt chart
  printChart(ganttIndex, &gantt);
  memset(gantt, 0, sizeof(gantt));  // nullify
}

void roundrobin(int items, int quantum, Process *process) {
  Gantt gantt[items * items];  // since number of process in gantt may be
                               // greater than items
  float avg_tat = 0, avg_wt = 0;
  int currentTime = 0, waitTime = 0, turnaroundTime = 0;
  int done = 0;
  int ganttIndex = 0;

  // loop til all processes are done
  while (done < items) {
    // for every process
    for (int i = 0; i < items; i++) {
      if (process[i].remaining <= 0) {  // when the process is done
        continue;                       // skip process[i] and iterate for loop
      }

      // initialize new item on gantt
      strcpy(gantt[ganttIndex].pid, process[i].pid);
      gantt[ganttIndex].start = currentTime;

      // latest start will be used to solve for waiting time
      process[i].latestStart = currentTime;

      // increment preemption (starting at -1)
      process[i].preemption++;

      // change currentTime according to remaining burst time
      if (process[i].remaining < quantum && process[i].remaining > 0) {
        currentTime = currentTime + process[i].remaining;
      } else {
        currentTime = currentTime + quantum;
      }

      // recalculate the remaining burst time
      process[i].remaining = process[i].remaining - quantum;
      if (process[i].remaining <= 0) {
        done++;
        process[i].complete = currentTime;
      }
      // currentTime == completion of the current process
      gantt[ganttIndex].done = currentTime;
      // turn around time and wait time of current process
      ganttIndex++;
    }
  }

  for (int i = 0; i < items; i++) {
    // calculate turn around and waiting time for each process
    turnaroundTime = process[i].complete - process[i].arrival;
    waitTime = process[i].latestStart - process[i].arrival -
               (process[i].preemption * quantum);
    // add to average time placeholders
    avg_tat = avg_tat + turnaroundTime;
    avg_wt = avg_wt + waitTime;

    // details in the process
    process[i].tat = turnaroundTime;
    process[i].wt = waitTime;
  }
  // print process array
  printDetails(items, process);

  // solve the average times
  avg_tat = avg_tat / (float)items;
  avg_wt = avg_wt / (float)items;
  printf("\n\n** Average Turn Around Time: %.6f **", avg_tat);
  printf("\n** Average Waiting Time: %.6f **\n", avg_wt);
  // print gantt chart
  printChart(ganttIndex, &gantt);
  memset(gantt, 0, sizeof(gantt));  // nullify
}

void collector(int choice, int items, Process *process) {
  puts("\nEnter values...");
  if (choice == 3) {
    puts("Arrival time should be 0...");
    puts("Priority and Burst Time");
    for (int i = 0; i < items; i++) {
      sprintf(process[i].pid, "P%d", i);
      printf("Enter for Process %d: ", i);
      fflush(stdin);
      scanf("%d %d", &process[i].priority, &process[i].burst);
      process[i].remaining = process[i].burst;
      process[i].arrival = 0;
      process[i].latestStart = 0;
      process[i].preemption = -1;
      process[i].complete = 0;
      process[i].tat = 0;
      process[i].wt = 0;
    }
  } else {
    if (choice == 4) {
      puts("Arrival time should be 0...");
    }
    puts("Arrival Time and Burst Time");
    for (int i = 0; i < items; i++) {
      sprintf(process[i].pid, "P%d", i);
      printf("Enter for Process %d: ", i);
      fflush(stdin);
      scanf("%d %d", &process[i].arrival, &process[i].burst);
      process[i].remaining = process[i].burst;
      process[i].priority = 0;
      process[i].latestStart = 0;
      process[i].preemption = -1;
      process[i].complete = 0;
      process[i].tat = 0;
      process[i].wt = 0;
    }
  }
}

/* void sort(int choice, int items, Process *process) {
  Process temp;

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
} */

void printChart(int items, Gantt *gantt) {
  printf("\n\n\tGANTT CHART\n");
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
  printf("\n");
}

void printDetails(int items, Process *process) {
  printf("\n\nPROCESS SUMMARY:");
  printf("\n%5s\t%8s\t%8s\t%8s\t%8s\t%8s", "ID", "Arrival", "Burst", "Priority",
         "TA", "WT");
  for (int i = 0; i < items; i++) {
    printf("\n%5s", process[i].pid);
    printf("\t%8d\t%8d", process[i].arrival, process[i].burst);
    printf("\t%8d\t%8d\t%8d", process[i].priority, process[i].tat, process[i].wt);
    }
}