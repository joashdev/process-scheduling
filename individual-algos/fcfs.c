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
  }
}

void fcfs(int items, struct Process *process) {}

void printer(int items, struct Process *process) {
  for (int j = 0; j < items; j++) {
    puts("\n............");
    printf("%s %2d %2d\n", process[j].pid, process[j].arrival,
           process[j].burst);
  }
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
    switch (choice){
      case 1:
        fcfs(items, &Processes);
        // *Processes = NULL;
		printer(items, &Processes);
        memset(Processes, '\0', sizeof(Processes));
        break;
      default:
        break;
    }
    printf("\nPress ENTER key to continue...\n");
    while (getchar() != '\n'){}
    getchar();
  } while (1);

  puts("\nterminating...");
  return 0;
}
