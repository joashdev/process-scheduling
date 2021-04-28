# PROCESS SCHEDULING ALGORITHMS
	Created by: ProCrust
	For: CMSC 125 (Operating Systems) Laboratory 1

---
[Contents](#Contents)  
[How to use](#How-to-Use)  
[Docs](#Docs)

---
## Contents
### The repository contains the following process scheduling algorithms:
1. First Come, First Serve (FCFS)
    ##### As the name suggests, the first process to arrive at the CPU will be the first to be executed

2. Shortest Job First (SJF)
3. Priority Based Scheduling
4. Round Robin

---
## How to Use
Just run the following snippets in the terminal to compile or run the program. Make sure that the directory in the terminal is the same as the file location.
### Compile
`gcc -o lab1 ZamudioK_Lab1.c`
### Run (Manual Input)
`./lab1 `
### Run (Use test.txt file as input)	
`./lab1<test.txt `	

---
## Docs
### Functions

 name | type | details
--- | --- | ---
`main` | `int` | main function of the program
`collector` | `void` | collects the details of the processes
`sort` | `void` | sorts the processes depending on scheduling algorithm
`fcfs` | `void` | function for the fcfs implementation