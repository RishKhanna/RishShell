# RishShell
A custom shell I made using C

Name: Rishabh Khanna <br>
Roll Number: 2019113025

## How to run the shell:
- Run "make" in the RishShell directory.
- Then, run "./RishShell" to run the shell
- Type "quit", "bye" and 'exit" to exit the shell


## Display
- On executing the code, a shell prompt of the following form appears along with it:
  - ```<username@system_name:curr_dir>```
- The directory from which the shell is invoked is the home directory of the shell and is indicated by "~"


## Implemented Commands:
- ```cd [directory path]```
  - "cd [directory path]" will change the present working directory of the terminal
  - "cd" or "cd ~" will change the present working directory to the home directory of the shell
  - "cd -" will change the present working directory to the previous working directory of the shell
  - cd is implemented in "customCd.c" and "customCd.h"

- ``` pwd ```
  - "pwd" will print the absolute path to the present working directory
  - pwd is implemented in "customPwd.c" and "customPwd.h"
  
- ```echo [string]```
  - "echo [string]" will print the string in the terminal after removing extra white spaces (spaces-' ', and tabs-'\t')
  - echo is implemented in "customEcho.c" and "customEcho.h"
  
  
- ```ls [flags] [directory path]```
  - "ls" lists all files present in the current working directory in alphabetical order
  - "ls [directory path]" lists all files present in the directory specified by [directory path] in alphabetical order
  - Possible flags: -l (displays extra information regarding files), -a (display all files, including hidden files), -al/-la (displays extra information regarding all files, including hidden files)
  - ls can also handle multiple [directory path]s, in which case it will list the files of all provided directories
  - The order in which the flags and [directory path]s are provided is inconsequential to the working of ls
  - In the -l flag files more than 6 months old, display year instead of time
  - ls is implemented in "customLs.c" and "customLs.h"
  
- ```repeat```
  - The command is responsible for executing the given instruction multiple times
  - The first argument to the command specifies the number of times the following command is to be run
  - ls is implemented in "customRepeat.c" and "customRepeat.h"

- ```pinfo```
  - "pinfo" prints information regarding the process corresponding to the shell beingg executed
  - "pinfo [pid]" prints information regarding the process corresponding to the [pid] provided
  - pinfo makes use of the /proc/[pid]/stat and /proc/[pid]/exe files to obtain information regarding ongoing processes
  - To get process status and memory, it is assumed that they are the 3rd and 23rd elements in /proc/[pid]/stat, this is consistent with BASH shell
  - pinfo is implemented in "customPinfo.c" and "customPinfo.h"

- ```jobs```
  - "jobs" prints information regarding all running and/or stopped background processes.
  - "jobs" prints the job number, execution status, executed command, and pid of each running or stopped background process.
  - jobs is implemented in "jobs.c" and "jobs.h".

  
- ```history [number of commands]```
  - "history" lists the 10 most recently executed commands (incuding the history command)
  - "history [number of commands]" lists the [number of commands] most recently executed commands
  - If [number of commands] is entered as a value greater than 20, then the available history will be printed
  - If number of executed commands is less than requested number of commands, the maximum number of recorded commands will be printed
  - The executed commands are stored in ".RishShell_history", and if ".RishShell_history" does not exist then it will be created as a part of the command
  - History is implemented in "customHistory.c" and "customHistory.h"
  
- ```quit```
  - "quit", "bye" and 'exit" quits the shell
  - "Ctrl+D" will also quit the shell

## Foreground and background processes:
- Foreground
  - Handles foreground processes other than the implemented commands using execvp
- Background
  - Handles background processes other than the implemented commands using execvp
  - Print info (pip) of background processes when terminated.
- It is implemented in "sysCommands.c" and "sysCommands.h"

## Other things to note:
- ';' separated commands
- RishShell is equipped to execute multiple ';' separated commands
- Handling extra white space
- RishShell is equipped to handle extra spaces(' ') and tabs('\t') in commands
