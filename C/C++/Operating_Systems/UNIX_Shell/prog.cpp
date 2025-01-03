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
 * @brief Parses out the command and arguments from the input command separated by spaces
 * @param command The input command string
 * @param args Array to store parsed arugments
 * @return The number of arguments passed
 */
int parse_command(char command[], char *args[]) {
    int i = 0; // num of arguments
    char *token = strtok(command, " \n");
    while (token != NULL) {
        args[i] = token;
        i++;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL; // last element must be NULL for execvp to detect end of argument list
    return i;
}

/**
 * @brief Handles the exit command 'exit', sets the should_run flag to 0
 * @param command The input command string
 * @param should_run Flag indicating if shell should continue
 */
void handle_exit_command(const char* command, int &should_run) {
    if (strcmp(command, "exit") == 0) {
        should_run = 0;
        exit(0);
    }
}

/**
 * @brief Handles the history command '!!' by executing most recent command
 * @param fullCommand Full input command string
 * @param lastCommand Storage for the last executed command
 * @param command Current command string for re-execution
 * @param args Current set of parsed arguments
 */
void handle_history_command(const char* fullCommand, char* lastCommand, char* command, char** args) {
    if (strcmp(args[0], "!!") == 0) {
        if (strlen(lastCommand) == 0) {
            printf("No command history\n");
        } else {
            printf("Executing previous command> %s", lastCommand); // print last cmd
            strcpy(command, lastCommand);   // restore last cmd
            parse_command(command, args);   // re-parse cmd to include args
        }
    } else {
        strcpy(lastCommand, fullCommand);   // update last cmd
    }
}

/**
 * @brief Handles piping command '|'
 * @param args Array of arguments
 * @param num_args Number of arguments
 */
void handle_pipe(char **args, int num_args) {
    int pipefd[2];
    int pipe_pos = -1;

    // Find the pipe symbol and record its position
    for (int i = 0; i < num_args; i++) {
        if (strcmp(args[i], "|") == 0) {
            pipe_pos = i;
            break;
        }
    }

    if (pipe_pos != -1) {   // pipe detected
        pipe(pipefd);       // create pipe

        pid_t pid1 = fork();
        if (pid1 == 0) { // Child 1: command before the pipe
            dup2(pipefd[1], STDOUT_FILENO); // redirect STDOUT to pipe write-end
            close(pipefd[0]);
            args[pipe_pos] = NULL;
            execvp(args[0], args);
            perror("execvp");
            exit(1);
        }

        pid_t pid2 = fork();
        if (pid2 == 0) { // Child 2: command after the pipe
            dup2(pipefd[0], STDIN_FILENO); // redirect STDIN to pipe read-end
            close(pipefd[1]);
            execvp(args[pipe_pos + 1], &args[pipe_pos + 1]);
            perror("execvp");
            exit(1);
        }

        // Parent Process
        close(pipefd[0]); // closes both ends
        close(pipefd[1]);
        waitpid(pid1, NULL, 0); // waits for both children
        waitpid(pid2, NULL, 0);
    }
}

/**
 * @brief Checks if the command should be executed in the background
 * @param args Array of arguments
 * @param num_args Number of arguments
 * @param background Flag indicating if command is a background process
 * @return 1 if command is background process, 0 otherwise
 */
int is_background(char **args, int &num_args, int &background) {
    if (num_args > 0) {
        int lastArgLen = strlen(args[num_args - 1]); // access last argument position
        // Check if last argument ends with '&'
        if (args[num_args - 1][lastArgLen - 1] == '&') {
            if (lastArgLen > 1) { // Remove '&' if part of larger argument "command&"
                args[num_args - 1][lastArgLen - 1] = '\0';
            } else { // If '&' by it self, remove
                args[num_args - 1] = NULL;
                num_args--;
            }
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Handles IO Redirection '>' or '<'
 * @param args Array of arguments
 * @param num_args Number of arguments
 */
void handle_redirection(char **args, int num_args) {
    for (int j = 0; j < num_args; j++) {
        if (strcmp(args[j], ">") == 0 && args[j+1] != NULL) { // Output Redirection
            int out = open(args[j+1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU); // open file
            dup2(out, STDOUT_FILENO); // redirect stdout to file
            close(out);
            args[j] = NULL; // join args to remove redirection symbols
            break;
        } else if (strcmp(args[j], "<") == 0 && args[j+1] != NULL) { // Input Redirection
            int in = open(args[j+1], O_RDONLY); // open file
            dup2(in, STDIN_FILENO); // redirect stdin to read from file
            close(in);
            args[j] = NULL; // join args to remove redirection symbols
            break;
        }
    }
}

/**
 * @brief Executes the command
 * @param args Array of arguments
 * @param num_args Number of arguments
 * @param background Flag indicating if command is a background process
 */
void execute_command(char **args, int num_args, int background) {
    pid_t pid = fork();
    if (pid < 0) {          // (1) Fork Child Process using fork()
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (pid == 0) {  // (2) Child Process uses execvp()
        handle_redirection(args, num_args); // Add IO Redirection Feature
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

/**
 * @brief The main function of a simple UNIX Shell
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */
int main(int argc, char *argv[]) {
    char command[MAX_LINE];             // the command that was entered
    char *args[MAX_LINE / 2 + 1];       // hold parsed out command line arguments
    int should_run = 1;                 /* flag to determine when to exit program */

    char lastCommand[MAX_LINE] = "";    // stores the last command
    char fullCommand[MAX_LINE] = "";    // backups full cmd before parsing

    while (should_run) {
        printf("osh>");
        fflush(stdout);
        fgets(command, MAX_LINE, stdin);                // Read Input Command
        strcpy(fullCommand, command);                   // backups fullCmd before parsing
        int num_args = parse_command(command, args);    // Parse Input Command

        handle_exit_command(command, should_run);       // Creates Exit Cmd: 'exit'
        handle_history_command(fullCommand, lastCommand, command, args); // Creates History Cmd: '!!'
        handle_pipe(args, num_args);                    // Creates Pipe Cmd: '|'

        int background = is_background(args, num_args, background); // Determine if command should run in background
        execute_command(args, num_args, background);                // Execute Command
    }

    return 0;
}
