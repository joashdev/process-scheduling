#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char pid[5];
  int arrival;  // for arrival time or priority
  int burst;
  int remaining;  // for remaining;
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

void sjf_preemptive(int items, Process *process) {
  for (int i = 0; i < items; i++) {
    printf("\n%s %d %d %d", process[i].pid, process[i].arrival,
           process[i].burst, process[i].remaining);
  }
  Gantt gantt[items * items];
  Process temp;
  float avg_tat, avg_wt = 0;
  int done = 0, waitTime = 0, turnaroundTime = 0, ganttIndex = 0;
  int prevProcess = (-1);
  int endTime;
  int min = 0;
  for (int currentTime = 0; done != items; currentTime++) {
    for (int ii = 0; ii < items; ii++) {
        if(!process[ii].complete){
          min = ii;
        }
    }
      for (int ii = 0; ii < items; ii++) {
        if (process[min].remaining > process[ii].remaining &&
            process[ii].arrival <= currentTime && process[ii].remaining > 0) {
          min = ii;
        //   printf("\nMin: %d\t Prev: %d", min, prevProcess);
        }
      }
    // printf("\nTime:%d\t%s %d %d %d\tDone: %d", currentTime, process[min].pid,
        //    process[min].arrival, process[min].burst, process[min].remaining,
        //    done);
        if (prevProcess != min) {
          ganttIndex++;
          strcpy(gantt[ganttIndex - 1].pid, process[min].pid);
          gantt[ganttIndex - 1].start = currentTime;
        }
    process[min].remaining--;
    if (process[min].remaining == 0) {
      done++;
      process[min].complete = 1;
        endTime = currentTime + 1;
        waitTime = endTime - process[min].arrival - process[min].burst;
        turnaroundTime = endTime - process[min].arrival;
        // add to average time placeholders
        avg_tat = avg_tat + turnaroundTime;
        avg_wt = avg_wt + waitTime;
    }
        gantt[ganttIndex - 1].done = currentTime + 1;
    prevProcess = min;
    // if (currentTime == 20) {
    //   break;
    // }
  }
    avg_tat = avg_tat / (float)items;
    avg_wt = avg_wt / (float)items;
    printf("\n** Average Turn Around Time: %.6f **", avg_tat);
    printf("\n** Average Waiting Around Time: %.6f **\n", avg_wt);
    printChart(ganttIndex, &gantt);
    memset(gantt, 0, sizeof(gantt));
}

void sjf_nonpreemptive(int items, Process *process) {
  Gantt gantt[items];
  Process temp;
  float avg_tat, avg_wt = 0;
  int currentTime, waitTime, turnaroundTime = 0;
  int ganttIndex = 0;
  for (int i = 0; i < items; i++) {
    int min = i;
    for (int ii = i + 1; ii < items; ii++) {
      if (process[min].burst > process[ii].burst &&
          process[ii].arrival <= currentTime) {
        min = ii;
      }
    }
    // printf("\n%s %d %d", process[min].pid, process[min].arrival,
        //    process[min].burst);
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
  printf("going to process");
  int items = 4;
  Process process[items];
  strcpy(process[0].pid, "P0");
  process[0].arrival = 0;
  process[0].burst = 8;
  process[0].remaining = 8;
  process[0].complete = 0;
  strcpy(process[1].pid, "P1");
  process[1].arrival = 1;
  process[1].burst = 4;
  process[1].remaining = 4;
  process[1].complete = 0;
  strcpy(process[2].pid, "P2");
  process[2].arrival = 2;
  process[2].burst = 9;
  process[2].remaining = 9;
  process[2].complete = 0;
  strcpy(process[3].pid, "P3");
  process[3].arrival = 3;
  process[3].burst = 5;
  process[3].remaining = 5;
  process[3].complete = 0;
  printf("going to sjf");

  sjf_preemptive(items, &process);
  memset(process, '\0', sizeof(process));

  Process processes[items];
  strcpy(processes[0].pid, "P0");
  processes[0].arrival = 0;
  processes[0].burst = 7;
  processes[0].remaining = 7;
  processes[0].complete = 0;
  strcpy(processes[1].pid, "P1");
  processes[1].arrival = 2;
  processes[1].burst = 4;
  processes[1].remaining = 4;
  processes[1].complete = 0;
  strcpy(processes[2].pid, "P2");
  processes[2].arrival = 4;
  processes[2].burst = 1;
  processes[2].remaining = 1;
  processes[2].complete = 0;
  strcpy(processes[3].pid, "P3");
  processes[3].arrival = 5;
  processes[3].burst = 4;
  processes[3].remaining = 4;
  processes[3].complete = 0;
  sjf_preemptive(items, &processes);

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
  //   sjf_nonpreemptive(items, &process);
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
  //   sjf_nonpreemptive(items, &processes);

  return 0;
}



