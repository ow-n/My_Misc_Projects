/**
 * @file pcbtable.h
 * @author Owen Man
 * @brief This is the main function of a simple UNIX Shell.
 * @version 0.1
 */

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

#define MAX_LINE 80 // The maximum length command

/**
 * @brief parse out the command and arguments from the input command separated by spaces
 *
 * @param command
 * @param args
 * @return int
 */
int parse_command(char command[], char *args[]) {
    int i = 0;
    char *token = strtok(command, " \n");
    while (token != NULL) {
        args[i] = token;
        i++;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL; // Last element must be NULL for execvp
    return i; // Return number of arguments
}

/**
 * @brief The main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */
int main(int argc, char *argv[]) {
    char command[MAX_LINE];       // the command that was entered
    char *args[MAX_LINE / 2 + 1]; // hold parsed out command line arguments
    int should_run = 1;           /* flag to determine when to exit program */

    pid_t pid;
    char lastCommand[MAX_LINE] = ""; // stores the last command
    char fullCommand[MAX_LINE] = ""; // backups full cmd before parsing

    while (should_run) {
        printf("osh>");
        fflush(stdout);
        fgets(command, MAX_LINE, stdin); // Read Input Command
        strcpy(fullCommand, command); // backups fullCmd before parsing
        int num_args = parse_command(command, args); // Parse Input Command

        // Creates 'exit' Cmd
        if (strcmp(command, "exit") == 0) {
            should_run = 0; // Exit the loop and terminate the shell
            exit(0);
        }

        // Creates '!!' Cmd: Executes last cmd
        if (strcmp(args[0], "!!") == 0) {
            if (strlen(lastCommand) == 0) {
                printf("No command history\n");
                continue;
            }
            printf("%s", lastCommand);      // print last cmd
            strcpy(command, lastCommand);   // restore last cmd
            parse_command(command, args);   // re-parse cmd to include args
        } else {
                strcpy(lastCommand, fullCommand); // update last command
        }

        // Creates '|' Pipe Cmd
        int pipePos = -1;
        for (int j = 0; j < num_args; j++) {
            if (strcmp(args[j], "|") == 0) {
                pipePos = j;
                args[j] = NULL; // split args into two commands at the pipe symbol
                break;
            }
        }

        if (pipePos != -1) { // pipe detected
            int pipefd[2];
            pipe(pipefd); // create pipe

            pid_t pid1 = fork();
            if (pid1 == 0) { // Child 1: handle cmd before pipe
                dup2(pipefd[1], STDOUT_FILENO); // redirect STDOUT to pipe write-end
                close(pipefd[0]); // close unused read-end
                execvp(args[0], args);
                perror("execvp");
                exit(1);
            }

            pid_t pid2 = fork();
            if (pid2 == 0) { // Child 2: handle cmd after pipem
                dup2(pipefd[0], STDIN_FILENO); // redirect STDIN to pipe read-end
                close(pipefd[1]); // close unused write-end
                execvp(args[pipePos + 1], &args[pipePos + 1]);
                perror("execvp");
                exit(1);
            }

            // Parent Proces: closes both ends, waits for both children
            close(pipefd[0]);
            close(pipefd[1]);
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
        }

        // Determine if the command should run in the background
        int background = 0; // reset background flag for each cmd
        if (num_args > 0) {
            int lastArgLen = strlen(args[num_args - 1]);
            // Check if last argument ends with '&'
            if (args[num_args - 1][lastArgLen - 1] == '&') {
                background = 1;
                if (lastArgLen > 1) { // Remove '&' if part of larger argument "command&"
                    args[num_args - 1][lastArgLen - 1] = '\0';
                } else { // If '&' by it self, remove
                    args[num_args - 1] = NULL;
                    num_args--;
                }
            }
        }

        
        pid = fork();
        if (pid < 0) {          // (1) Fork Child Process using fork()
            fprintf(stderr, "Fork failed\n");
            return 1;
        } else if (pid == 0) {  // (2) Child Process uses execvp()
            //  Inout Output Redirection Feature
            for (int j = 0; j < num_args; j++) {
                if (strcmp(args[j], ">") == 0 && args[j+1] != NULL) { // Output Redirection
                    int out = open(args[j+1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU); // open file
                    dup2(out, STDOUT_FILENO); // redirect stdout to file
                    close(out);
                    args[j] = NULL; // join args to remove redirection symbols
                    break;
                } else if (strcmp(args[j], "<") == 0 && args[j+1] != NULL) { // Input Redirection
                    // Open the file for reading.
                    int in = open(args[j+1], O_RDONLY); // open file
                    dup2(in, STDIN_FILENO); // redirect stdin to read from file
                    close(in);
                    args[j] = NULL; // join args to remove redirection symbols
                    break;
                }
            }
            if (execvp(args[0], args) == -1) {
                printf("Command not found\n");
                exit(1);
            }
        } else {                // (3) Parent process behavior
            if (!background) {  // [IF !&]: Parent waits for Child Process to complete
                waitpid(pid, NULL, 0);
            } else {            // [IF  &]: Parent doesn't wait, allowing child to run in background
                printf("Background PID: %d\n", pid);
            }
        }
    }
    return 0;
}
