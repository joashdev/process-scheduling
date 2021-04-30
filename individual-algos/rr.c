#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char pid[5];
  int arrival;  // for arrival time or priority
  int burst;
  int remaining;  // for remaining;
  int latestStart;
  int preemption;
  int complete;
} Process;

typedef struct {
  char pid[5];
  int start;
  int done;
} Gantt;

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

void rr(int items, int quantum, Process *process) {
  Gantt gantt[items * items];
  float avg_tat = 0, avg_wt = 0;
  int currentTime = 0, waitTime = 0, turnaroundTime = 0;
  int done = 0;
  int ganttIndex = 0;
  while (done < items) {
    for (int i = 0; i < items; i++) {
      if (process[i].remaining <= 0) {
        continue;
      }
      strcpy(gantt[ganttIndex].pid, process[i].pid);
      gantt[ganttIndex].start = currentTime;
      // arrival will be used as the latest starting time of the process
      process[i].latestStart = currentTime;
      // increment preemption
      process[i].preemption++;
      if (process[i].remaining < quantum && process[i].remaining > 0) {
        currentTime = currentTime + process[i].remaining;
      } else {
        currentTime = currentTime + quantum;
      }
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
      turnaroundTime = process[i].complete - process[i].arrival;
      // add to average time placeholders
      avg_tat = avg_tat + turnaroundTime;
    waitTime = process[i].latestStart - process[i].arrival -
               (process[i].preemption * quantum);
    printf("\n%s  %d  %d  Quantum: %d  Waittime: %d", process[i].pid, process[i].latestStart,
           process[i].preemption, quantum,waitTime);
    avg_wt = avg_wt + waitTime;
    printf("   Completion: %d", process[i].complete);
  }
  avg_tat = avg_tat / (float)items;
  avg_wt = avg_wt / (float)items;
  printf("\n** Average Turn Around Time: %.6f **", avg_tat);
  printf("\n** Average Waiting Around Time: %.6f **\n", avg_wt);
    printChart(ganttIndex, &gantt);
  memset(gantt, 0, sizeof(gantt));
}

int main(int argc, char const *argv[]) {
  printf("going to process");
  int items = 3;
  int quantum = 4;
  Process process[items];
  strcpy(process[0].pid, "P0");
  process[0].arrival = 0;
  process[0].burst = 24;
  process[0].remaining = 24;
  process[0].preemption = (-1);
  process[0].complete = 0;
  strcpy(process[1].pid, "P1");
  process[1].arrival = 0;
  process[1].burst = 3;
  process[1].remaining = 3;
  process[1].preemption = (-1);
  process[1].complete = 0;
  strcpy(process[2].pid, "P2");
  process[2].arrival = 0;
  process[2].burst = 3;
  process[2].remaining = 3;
  process[2].preemption = (-1);
  process[2].complete = 0;

  rr(items, quantum, &process);
  memset(process, '\0', sizeof(process));

  //   items = 3;
  //   quantum = 4;
  //   Process processes[items];
  //   strcpy(processes[0].pid, "P0");
  //   processes[0].arrival = 0;
  //   processes[0].burst = 30;
  //   processes[0].remaining = 30;
  //   processes[0].preemption = 0;
  //   processes[0].complete = 0;
  //   processes[0].latestStart = 0;
  //   strcpy(processes[1].pid, "P1");
  //   processes[1].arrival = 0;
  //   processes[1].burst = 7;
  //   processes[1].remaining = 7;
  //   processes[1].preemption = 0;
  //   processes[1].complete = 0;
  //   processes[1].latestStart = 0;
  //   strcpy(processes[2].pid, "P2");
  //   processes[2].arrival = 0;
  //   processes[2].burst = 10;
  //   processes[2].remaining = 10;
  //   processes[2].preemption = 0;
  //   processes[2].complete = 0;
  //   processes[2].latestStart = 0;
  //   rr(items, quantum, &processes);

  //   Process process[items];
  //   strcpy(process[0].pid, "P0");
  //   process[0].arrival = 0;
  //   process[0].burst = 6;
  //   process[0].completion = 0;
  //   strcpy(process[1].pid, "P1");
  //   process[1].arrival = 0;
  //   process[1].burst = 8;
  //   process[1].completion = 0;
  //   strcpy(process[2].pid, "P2");
  //   process[2].arrival = 0;
  //   process[2].burst = 7;
  //   process[2].completion = 0;
  //   strcpy(process[3].pid, "P3");
  //   process[3].arrival = 0;
  //   process[3].burst = 3;
  //   process[3].completion = 0;
  //   printf("going to sjf");
  //   rr(items, &process);
  //   memset(process, '\0', sizeof(process));

  //   Process processes[items];
  //   strcpy(processes[0].pid, "P0");
  //   processes[0].arrival = 0;
  //   processes[0].burst = 7;
  //   processes[0].completion = 0;
  //   strcpy(processes[1].pid, "P1");
  //   processes[1].arrival = 2;
  //   processes[1].burst = 4;
  //   processes[1].completion = 0;
  //   strcpy(processes[2].pid, "P2");
  //   processes[2].arrival = 4;
  //   processes[2].burst = 1;
  //   processes[2].completion = 0;
  //   strcpy(processes[3].pid, "P3");
  //   processes[3].arrival = 5;
  //   processes[3].burst = 4;
  //   processes[3].completion = 0;
  //   rr(items, &processes);

  return 0;
}
