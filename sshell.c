/**
*  @author: Travis Mayer
*     ID: 002273275
*     Email: mayer129@mail.chapman.edu
*     Course: CPSC 353-01
*     Sources:
*       https://stackoverflow.com/questions/12102332/when-should-i-use-perror-and-fprintfstderr
*       https://www.tutorialspoint.com/cprogramming/c_input_output.htm
*       https://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm
*       https://www.geeksforgeeks.org/fgets-gets-c-language/
*       https://stackoverflow.com/questions/8004237/how-do-i-properly-compare-strings
*       https://linuxhint.com/exec_linux_system_call_c/
*       https://www.tutorialspoint.com/c_standard_library/c_function_system.htm
*       https://stackoverflow.com/questions/12450066/flushing-buffers-in-c
*       http://man7.org/linux/man-pages/man3/fpurge.3.html
*       https://stackoverflow.com/questions/37537479/difference-between-int-fpurge-and-int-fflush-in-c
*       Example program demonstrating UNIX pipes by Silberschatz, Galvin, and Gagne
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 256
#define READ_END	0
#define WRITE_END	1


int main(int argc, char** argv) {

  char write_msg[BUFFER_SIZE];
	char read_msg[BUFFER_SIZE];
  pid_t pid;
	int fd[2];

	// creates the pipe
	if (pipe(fd) == -1) {
		perror("Pipe Failed");
		return 1;
	}

	// forks child process
	pid = fork();

	if (pid < 0) {
		perror("Fork Failed");
		return 1;
	}

  if (pid > 0) { // parent process
    close(fd[READ_END]); // close unused read end
    printf("osh> "); // simple shell name

    while (strcmp(write_msg, "q\n") != 0 && strcmp(write_msg, "quit\n") != 0) { //while not the exit conditions
      fgets(write_msg, BUFFER_SIZE, stdin); // take user input
      write(fd[WRITE_END], write_msg, strlen(write_msg)+1); // write to pipe
    }
     close(fd[WRITE_END]); // close write end of pipe
  }
  else { // child process
    close(fd[WRITE_END]); // close unused write end
    read(fd[READ_END], read_msg, BUFFER_SIZE); // take parent input

    while (strcmp(read_msg, "q\n") != 0 && strcmp(read_msg, "quit\n") != 0) { // while not the exit conditions
      system(read_msg); // execlp() was very convoluted. Looked for alternativs and found system()
      printf("osh> "); // simple shell name
      fflush(stdout); // forces buffer to flush after printf instead of waiting till full.
      //Otherwise the printf won't appear when needed.
      read(fd[READ_END], read_msg, BUFFER_SIZE); // take parent input

    }
    close(fd[READ_END]); //close read end of pipe
  }

return 0;

}
