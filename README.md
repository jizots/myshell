## Minishell Project README

# Overview
The Minishell project challenges you to create your own shell program, similar to Bash.  
It's designed to deepen your understanding of processes, file descriptors, and the Unix environment.  
This project is an opportunity to explore how shells operate, manage command execution, and handle user input, thereby providing a practical framework for understanding the inner workings of shell environments.  

## Key Features
__Command Prompt__: Display a customizable prompt awaiting user input.  
__Command Execution__: Execute commands found in the PATH environment or specified by absolute or relative paths.  
__Signal Handling__: Implement custom responses to signals like SIGINT (ctrl-C), SIGQUIT (ctrl-\), and EOF (ctrl-D).  
__Builtins Implementation__: Includes builtins like echo, cd, pwd, export, unset, env, and exit.  
__Redirections and Pipes__: Manage input and output redirections (<, >, <<, >>) and pipe execution (|).  
__Environment Variables__: Handle expansion of environment variables and the special parameter $? for the last command's exit status.  
__Command History__: Maintain a history of executed commands for easy recall.  
Bonus Features (Not availavle)  

## Skills Acquired from Minishell Project
__Unix Processes and IPC__: Understanding of process creation, execution, and inter-process communication.  
__Signal Handling__: Proficiency in handling Unix signals for process control.  
__Environment Management__: Skills in managing environment variables and shell session states.  
__Input/Output Redirection__: Mastery of redirecting command input and output, crucial for Unix/Linux environment scripting.  
__Parsing and Execution__: Advanced techniques in parsing user input and executing shell commands.  
__Custom Shell Features__: Experience in implementing shell-specific features like command history and builtins.  

## Usage
Compile the project using the provided Makefile.  
Run ./minishell to start the shell.  
Use built-in commands or any executable programs found in your PATH.  
