# RishShell README

## Introduction
RishShell is a custom shell developed by Rishabh Khanna using the C programming language. This shell provides a command-line interface with various implemented commands, allowing users to navigate directories, manage processes, and execute commands efficiently.


## How to Run the Shell
To run RishShell, follow these steps:
1. Run `make` in the RishShell directory.
2. Execute `./RishShell` to start the shell.
3. Type "quit," "bye," or "exit" to exit the shell.

## Display
Upon execution, the shell prompt takes the form: `<username@system_name:curr_dir>`. The home directory is represented by "~".

## Implemented Commands

### 1. cd [directory path]
- Changes the current working directory.
- Usage:
  - `cd [directory path]`: Change to the specified directory.
  - `cd` or `cd ~`: Change to the home directory.
  - `cd -`: Change to the previous working directory.

### 2. pwd
- Prints the absolute path to the current working directory.

### 3. echo [string]
- Prints the given string after removing extra white spaces.

### 4. ls [flags] [directory path]
- Lists files in alphabetical order.
- Flags:
  - `-l`: Displays extra information regarding files.
  - `-a`: Displays hidden files.
  - `-al` or `-la`: Displays extra information for all files, including hidden ones.

### 5. repeat
- Executes a given instruction multiple times.
- Usage: `repeat [num] [command]`

### 6. pinfo [pid]
- Prints information about a process.
- Usage: `pinfo` or `pinfo [pid]`

### 7. jobs
- Prints information about running and/or stopped background processes.

### 8. history [number of commands]
- Displays recently executed commands.
- Usage: `history` or `history [num]`

### 9. quit
- Exits the shell.
- Also exits on "bye" and "exit" commands or by pressing `Ctrl+D`.

## Foreground and Background Processes
- Foreground: Handles foreground processes using `execvp`.
- Background: Handles background processes using `execvp` and prints information when terminated.

## Additional Features
- Supports ';' separated commands.
- Handles extra white spaces in commands.

## Files and Implementation
- `customCd.c` and `customCd.h`: Implement the `cd` command.
- `customPwd.c` and `customPwd.h`: Implement the `pwd` command.
- `customEcho.c` and `customEcho.h`: Implement the `echo` command.
- `customLs.c` and `customLs.h`: Implement the `ls` command.
- `customRepeat.c` and `customRepeat.h`: Implement the `repeat` command.
- `customPinfo.c` and `customPinfo.h`: Implement the `pinfo` command.
- `jobs.c` and `jobs.h`: Implement the `jobs` command.
- `customHistory.c` and `customHistory.h`: Implement the `history` command.
- `sysCommands.c` and `sysCommands.h`: Implement foreground and background process handling.

## Notes
- The shell is equipped to execute multiple ';' separated commands.
- Handles extra spaces and tabs in commands.
- Command history is stored in ".RishShell_history" for reference.

Feel free to explore and customize RishShell for your command-line needs!
