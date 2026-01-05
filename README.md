# Group Name: 

Team 8 - (SysForge)

# Group Members:

1. Colten Mikulastik

2. Mayuresh Keshav Kamble

3. Nathanlie Ortega  -  (Assigned as a Team Leader)

4. Igor Leeck


# Organization of the Project / Components Each Member is Responsible:


### Individual Built-in Commands

Each member is responsible for implementing one Built-in Command and committing their code to GitLab.
These consist of: cd, exit, path, myhistory.

1. **Nathanlie Ortega**

   - Built-in Command: cd

2. **Colten Mikulastik**

   - Built-in Command: path

3. **Mayuresh Keshav Kamble**

   - Built-in Command: exit

4. **Igor Leeck**

   - Built-in Command: myhistory

### Advanced Features

All advanced features are implemented as group work. Each member takes the lead on one feature while collaborating with the team for integration and testing.
These consist of: I/O Redirection, Pipelining, Signal Handling, Alias Support.

1. **Nathanlie Ortega**

   - Advanced Feature: Alias Support

2. **Colten Mikulastik**

   - Advanced Feature: I/O Redirection

3. **Mayuresh Keshav Kamble**

   - Advanced Feature: Pipelining

4. **Igor Leeck**

   - Advanced Feature: Signal Handling


# Project Title:

Major Assignment 2 – The Shell and System Calls


# Design Overview (A few paragraphs describing the overall structure of your code and any important structures):

cd Built-in Command (Nathanlie Ortega):

The cd command is implemented in cd.c as a built-in function that directly calls the chdir system call to change the current working directory. The implementation supports three distinct modes of operation. When the user provides a directory path as an argument, the command changes to that specific directory. When no argument is provided, the command changes to the HOME directory by retrieving the HOME environment variable using the getenv system call. When the tilde symbol is used as the argument, the command also changes to the HOME directory using the same HOME environment variable retrieval process.

The cd function includes comprehensive error handling to ensure the shell remains stable even when directory changes fail. When the chdir system call returns an error, the function uses perror to display a meaningful error message to the user that describes why the directory change failed. The function returns 1 on successful directory changes and 0 on failures, but the main shell loop is designed to continue running regardless of the return value. This design prevents the shell from crashing when users attempt to change to invalid or non-existent directory paths. If the HOME environment variable is not set in the system, the function displays a specific error message and returns 0 without attempting to change directories.

Alias Support Command (Nathanlie Ortega):

The alias feature is implemented in alias.c using a custom data structure that maintains up to 50 alias entries in a static array. Each entry in the AliasEntry structure contains three fields that work together to manage alias functionality. The shortcut name field stores the alias name with a maximum length of 50 characters. The full command field stores the complete command string that the alias represents with a maximum length of 256 characters. The active flag is an integer that indicates whether the alias entry is currently in use, with a value of 1 for active aliases and 0 for deleted or unused slots.

The alias system supports four primary operations that allow users to manage their command shortcuts effectively. Users can create new aliases or update existing ones using the syntax where the alias name is followed by an equals sign and the command enclosed in quotes. Users can view all currently defined aliases by typing the alias command without any arguments, which triggers the printAliases function to display the complete list. Users can remove individual aliases by using the -r flag followed by the alias name they want to delete, or clear all defined aliases at once by using the -c flag. When a user types a command, the shell first checks whether the input matches any active alias name, and if a match is found, the aliased command string is duplicated using strdup to prevent corruption during parsing, then parsed and executed recursively through the main command execution function to work seamlessly with other shell features.

Signal Handling (Igor Leeck)

Signal handling in the shell is structured to separate responsibilities between the shell itself and the processes it spawns. The shell initially ignores key signals (such as SIGINT, SIGTSTP, and SIGQUIT) to prevent itself from being interrupted by user input. Child processes, however, are set up to handle these signals directly, allowing them to respond appropriately to user actions like stopping, pausing, or terminating. Each child process establishes its own process group and manages standard input independently, ensuring that signal handling and terminal control remain isolated between the shell and its subprocesses. This design ensures robust and predictable behavior in interactive sessions.

MyHistory (Igor Leeck)

The myhistory functionality provides both a record of previous commands and the ability to re-execute them. Commands entered by the user are stored in a structured history buffer, with new entries replacing the oldest when capacity is exceeded. The myhistory command itself interprets flags and arguments to either display command history or execute past commands. Executing a previous command involves parsing and validating the original command string, then running it in a separate child process to avoid interfering with the shell state. This design cleanly separates storage, retrieval, and execution responsibilities while maintaining the order and integrity of the command history.

Exit Command (Mayuresh Kamble)

The exit command terminates the current shell session or script. When typed in a terminal, it closes that shell window or returns you to the parent shell if you're in a nested session. You can optionally specify an exit status code like exit 0 for success or exit 1 for an error.

Pipeline Command (Mayuresh Kamble )

The pipeline (represented by |) connects multiple commands by taking the output of one command and feeding it as input to the next command. For example, ls | grep ".txt" lists files and then filters for only .txt files. This allows you to chain commands together to perform complex data processing in a single line.

# Complete Specification (Describe how you handled any ambiguities in the specification. For example, for this project, explain how your shell will handle lines that have no commands between semi-colons):

cd Built-in Command (Nathanlie Ortega):

The cd command handles errors by printing descriptive error messages and continuing shell execution rather than terminating the program when directory changes fail. When a user attempts to change to a non-existent or inaccessible directory, the shell displays an error message using perror and remains in the current directory without crashing. If the HOME environment variable is not set when the user types cd without arguments or cd with the tilde symbol, the shell displays a specific error message and stays in the current working directory. The alias system handles quote removal automatically by detecting both single quotes and double quotes around command strings and stripping them during parsing. When the maximum capacity of 50 aliases is reached, new alias creation attempts are rejected with a clear error message rather than overwriting existing entries, and the shell creates a copy of aliased command strings using strdup before parsing to prevent corruption from the strtok function that modifies strings in place during tokenization.

Alias Support Command (Nathanlie Ortega):

The alias command handles quote removal automatically by detecting both single quotes and double quotes around command strings and stripping them during the parsing process. When creating an alias, the implementation reconstructs the full command string from multiple arguments because the shell parser splits input by spaces, which allows commands with spaces like ls -la to be properly stored as a single unified alias command. If a user enters the alias command with invalid syntax such as missing the equals sign or missing quotes around the command, the shell displays a helpful error message that explains the correct format rather than attempting to process the malformed input. When the maximum capacity of 50 aliases is reached, new alias creation attempts are rejected with a clear error message rather than overwriting existing entries or causing unpredictable behavior. The shell creates a copy of aliased command strings using strdup before parsing to prevent corruption from the strtok function that modifies strings in place during tokenization, and this duplicated string is then parsed and executed recursively through the main command execution function to allow aliases to work seamlessly with built-in commands and other features.

Signal Handling (Igor Leeck):

In this shell, signal handling is designed to protect the shell while allowing child processes to respond to terminal signals. The shell initially ignores SIGINT, SIGTSTP, and SIGQUIT to prevent itself from being interrupted, but child processes—including those spawned by built-in commands like myhistory—restore default signal handling. This is particularly important for commands executed via myhistory that may involve pipelines, as restoring default signals ensures that all processes in the pipeline can properly respond to Ctrl-C or Ctrl-Z. Each child also sets its own process group and takes terminal control while running, allowing signals to propagate correctly to the foreground processes without affecting the shell itself.

myhistory command (Igor Leeck):

The myhistory command is obviously called when the first argument is "myhistory", however, this built in command must also keep track of the previous arguments that were passed into the shell. The primary function which comprises the functionality of myhistory is executeMyHistory. In the function it contains default branching to handle the different flags of the myhistory functionality. While the main functionality and its clear history functionality are relatively simple in design, its ability to execute past commands isn't. To do this it relies on a parser function and copies the string so that it doesn't change the string held in the history. After the arguments passed in for an execution are validated it executes them in a child process. One of the trickier things to think about was keeping the new commands at the highest index of history while pushing the oldest ones out. Another problem I ran into dealt with signal handling, myhistory, and pipelines. In order to fix it I had to return the default signals to the commands ran with a pipeline which I discovered when testing the capabilities of myhistory.

Exit Command (Mayuresh Kamble)

When handling the pipeline command (represented by |), my shell connects multiple commands by redirecting the standard output of the left command to the standard input of the right command. If a pipe appears at the beginning of a line (e.g., | ls) or at the end without a following command (e.g., ls |), the shell displays an error message indicating invalid syntax. For multiple pipes in sequence (e.g., cat file.txt | sort | uniq), the shell chains all commands together, passing output through each stage until the final command executes and displays the result.

Pipeline command (Mayuresh Kamble)

When handling the pipeline command (represented by the | symbol), I implemented it to connect multiple commands by redirecting the standard output of one command to the standard input of the next command in the sequence. If a pipe appears at the beginning of a command line without a preceding command (e.g., | ls) or at the end without a following command (e.g., ls |), the shell treats this as invalid syntax and displays an appropriate error message rather than attempting execution. For multiple pipes chained together (such as cat file.txt | sort | uniq), the shell creates a pipeline where each command's output feeds into the next command's input, allowing data to flow through multiple transformations sequentially. The shell also handles errors gracefully within pipelines—if any command in the chain fails, the error is reported, but subsequent commands may still attempt to execute depending on whether they receive input. Empty commands between pipes (like ls | | pwd) are treated as syntax errors. This implementation ensures that pipelines work reliably for complex data processing while providing clear feedback when syntax is incorrect, matching the behavior of standard Unix shells.


# Known Bugs or Problems: 

There are NO known bugs or problems for Major2.


# Date of Setup:

November 11, 2025
