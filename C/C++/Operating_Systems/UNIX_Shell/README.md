# Problem Description:
This assignment solves the problem of implementing our own Unix shell and history
feature. The primary functionalities of this program include: UNIX command execution,
forking child processes, and providing a history feature with ‘!!’, an exit command ‘exit’,
IO (input and output) redirection, and creating a UNIX pipe (allowing the output of one
command to serve as input to another using a pipe).

# Program Design
The overall design of my program is structured around a main while loop that reads user
input, and parses the user input into commands and arguments. I used ‘strtok’ to split
user input into tokens based on spaces and special symbols. I also used an array of
strings to store the parsed commands and arguments for easy access and
manipulation.

My program is designed this way so that it is easy to implement additional functions to
check for additional commands. It is simple to add another check for a custom
command, by adding it into the while loop to check for.

# System Implementation
I tackled the implementation of this assignment one function at a time, beginning first
with an execution function, and then handling the ‘exit’ and ‘!!’ commands. I continually
worked on the structure of my main function so that each piece of the code was modular
and worked well with the other functions, making sure that args, num_args, and
command, were all correct for each stage of the function call.

An issue I ran into was trying to print the last command in the ‘!!’ history process. I didn’t
understand why strcpy(lastCommand, command) wasn’t copying the arguments of the
original command. The solution I went with was incorporating an additional variable that
temporarily stored the full command before it was parsed. I’m unsure if there was a
better way to do this, but I didn’t see another solution to needing to save the original
state of ‘command’ before parsing but needing to process ‘!!’ afterward.

# Results
The features implemented in my final results were: command execution, history,
input/output redirection, and piping; there were no missing features. Some online
resources I referenced included POSIX documentation in order to effectively apply
system calls like fork, execvp, pipe, and dup2. To improve this program, I would extend it with more
complex features such as job control to manage background processes more
effectively, scripting, and more advanced piping.
