#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <dirent.h> 
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>

// Calculate fibonacci number
int64_t calculate_fibonacci(int64_t n, pid_t pid, pid_t ppid) {
	int64_t prev = 1;
	int64_t curr = 1;
	for (int64_t i = 2; i < n; ++i) {
		// Print exception if overflow occured
		if (ULLONG_MAX - curr < prev) {
			printf("ERROR: fibonacci value overflow!\nProccess id: %u\nParent proccess id: %u\n\n", pid, ppid);
			wait(NULL);
			exit(EXIT_FAILURE);
		}
		int64_t tmp = curr;
		curr = curr + prev;
		prev = tmp;
	}
	return curr;
}

// Calculate factorial
int64_t calculate_factorial(int64_t n, pid_t pid, pid_t ppid) {
	int64_t curr = 1;
	for (int64_t i = 1; i <= n; ++i) {
		// Print exception if overflow occured
		if (ULLONG_MAX / i < curr) {
			printf("ERROR: factorial value overflow!\nProccess id: %u\nParent proccess id: %u\n\n", pid, ppid);
			exit(EXIT_FAILURE);
		}
		curr = curr * i;
	}
	return curr;
}

// Print all the name of all files in the directory
void print_files() {
	printf("Files in the current directory:\n");
	DIR *dr;
	struct dirent *dir;
	dr = opendir(".");
	if (dr) {
		while ((dir = readdir(dr)) != NULL) {
	        printf("%s\n", dir->d_name);
	      }
	     closedir(dr);
	}
}

int main(int argc, char** argv) {
	// Get argument
	int64_t arg = atoi(argv[1]);
	// Create new proccess
	pid_t thread = fork();
	// Get proccess ID
	pid_t pid = getpid();
	// Get ID of the parent proccess
	pid_t ppid = getppid();
	if (thread == 0) {
		printf("Factorial: %lu\nProccess id: %u\nParent proccess id: %u\n\n", calculate_factorial(arg, pid, ppid), pid, ppid);
	} else {
		printf("Fibonacci: %lu\nProccess id: %u\nParent proccess id: %u\n\n", calculate_fibonacci(arg, pid, ppid), pid, ppid);
	}
	// Papent proccess creates proccess for printing file names
	if (thread != 0) {
		// Wait the child proccess to finish
		wait(NULL);
		// Create proccess to print file names in the directory
		pid_t thread_d = fork();
		// If child - print file names, if parent - wait child to finish
		if (thread_d == 0) {
			print_files();
		} else {
			wait(NULL);
		}
	}
	return 0;
}
