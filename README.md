# PROCESS SCHEDULING ALGORITHMS
	Created by: ProCrust
	For: CMSC 125 (Operating Systems) Laboratory 1

---
[Algorithms](#Overview)   
[How to use](#How-to-Use)   
[Docs](#Docs)
	

---
## Overview
### The repository contains the following process scheduling algorithms:   

1. First Come, First Serve (FCFS)   
As the name suggests, the first process to arrive at the CPU will be the first to be executed

2. Shortest Job First (SJF)   
Shortest Job First Algorithm selects the process with the least burst time to execute. In a nonpreemptive approach, even if process *b* has a shorter burst time, if it arrives later than process *a* that has a longer burst time, that process *b* will have to wait until process *a* finishes execution. On the other hand, with preemptive approach, in the same situation, process *a* will be interrupted to give way to process *b* since it has shorter burst time.
3. Priority Based Scheduling   
 Given a set of processes with corresponding priorities, Priority Based Algorithm selects the one with the highest priority for execution. This selection is done throughout the set of processes.
4. Round Robin   
 The set of processes are being executed based on Quantum Time or the set time for each process to be in the CPU. The algorithm iterates thoughout the set repeatedly until all process is done executing.

---
## How to Use
Just run the following snippets in the terminal to compile or run the program. Make sure that the directory in the terminal is the same as the file location.
### Compile
`gcc -o lab1 ZamudioK_Lab1.c`
### Run (Manual Input)
`./lab1 `
### Run (Using input file)	
`./lab1<t[x] `   

NOTE: Replace `[x]` with number corresponding to the algorithm.
`1` for FCFS, `2` for SJF, `3` for Priority Based, or `4` for Round Robin

---
## Docs
### Functions

 name | type | details
:---: | --- | ---
`main` | `int` | main function of the program
`collector` | `void` | collects the details of the processes
`printChart` | `void` | function for printing the Gantt Chart
`printDetails` | `void` | function for printing the process summary
`fcfs` | `void` | function for the FCFS implementation
`sjf_nonpreemptive` | `void` | function for the nonpreemptive approach of SJF implementation
`priority` | `void` | function for the Priority Based Algorithm implementation
`roundrobin` | `void` | function for the roundrobin implementation using quantum time

---
### Function Details

 The functions that utilizes sorting [`fcfs()`, `sjf_nonpreemptive()`, `priority()`] implements a selection sort algorithm to select the process earliest arrival time, shortest burst time, or highest priority.

