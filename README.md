# cpsc380assign2
Simple Shell Program
## Information
*  @author: Travis Mayer
*     ID: 002273275
*     Email: mayer129@mail.chapman.edu
*     Course: CPSC 380-01

## Program Purpose
"The objective of this assignment is to familiarize yourself with the notion of a process and the
system call fork() used to create a new process and pipe() to communicate between processes."
## Steps to Compile & Run:
1. Path to the sshell directory
2. type `gcc sshell.c -o sshell` to compile the program
3. type `./sshell`
* This will compile the program. The program will then prompt you for input and will send the input to the child process
and execute shell commands. The program will run until the user enters either `q` or `quit`.
