#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char pid[5];
  int arrival;
  int burst;
  int completion;
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

void fcfs(int items, Process *process) {
  Gantt gantt[items];
  Process temp;
  float avg_tat, avg_wt = 0;
  int currentTime, waitTime, turnaroundTime = 0;
  int ganttIndex = 0;
  for (int i = 0; i < items; i++) {
    int min = i; 
    for (int ii = i+1; ii < items; ii++) {
      if (process[min].arrival > process[ii].arrival) {
        min = ii;
      }
    }
    printf("\n%s %d %d %d", process[min].pid, process[min].arrival, process[min].burst, process[min].completion);
    strcpy(gantt[ganttIndex].pid, process[min].pid);
    if (currentTime < process[min].arrival) {
      gantt[ganttIndex].start = process[min].arrival;
      currentTime = currentTime + (process[i].arrival - currentTime);
    } else {
      gantt[ganttIndex].start = currentTime;
    }
    currentTime = currentTime + process[min].burst;
    // currentTime == completion of the current process
    gantt[ganttIndex].done = currentTime;
    // turn around time and wait time of current process
    turnaroundTime = currentTime - process[min].arrival;
    waitTime = turnaroundTime - process[min].burst;
    // add to average time placeholders
    avg_tat = avg_tat + turnaroundTime;
    avg_wt = avg_wt + waitTime;
    ganttIndex++;
    if (min != i) {
      temp = process[min];
      process[min] = process[i];
      process[i] = temp;
    }
  }
  avg_tat = avg_tat / (float)items;
  avg_wt = avg_wt / (float)items;
  printf("\n** Average Turn Around Time: %.6f **", avg_tat);
  printf("\n** Average Waiting Around Time: %.6f **\n", avg_wt);
  printChart(items, &gantt);
  memset(gantt, 0, sizeof(gantt));
}
int main(int argc, char const *argv[]) {
  int items = 3;
  Process process[items];
  strcpy(process[0].pid, "P0");
  process[0].arrival = 0;
  process[0].burst = 24;
  process[0].completion = 0;
  strcpy(process[1].pid, "P1");
  process[1].arrival = 0;
  process[1].burst = 3;
  process[1].completion = 0;
  strcpy(process[2].pid, "P2");
  process[2].arrival = 0;
  process[2].burst = 3;
  process[2].completion = 0;

  fcfs(items, &process);
  memset(process, '\0', sizeof(process));

  Process processes[items];
  strcpy(processes[0].pid, "P0");
  processes[0].arrival = 0;
  processes[0].burst = 1;
  processes[0].completion = 0;
  strcpy(processes[1].pid, "P1");
  processes[1].arrival = 2;
  processes[1].burst = 3;
  processes[1].completion = 0;
  strcpy(processes[2].pid, "P2");
  processes[2].arrival = 3;
  processes[2].burst = 3;
  processes[2].completion = 0;

  fcfs(items, &processes);
  return 0;
}
