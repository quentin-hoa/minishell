#  Minishell - Unix Shell Implementation

## Description
Minishell is a fundamental system programming project that involves creating a functional Unix shell. It recreates the core behavior of an interpreter like Bash, allowing users to execute system commands, manage environment variables, and handle process communications.

## Key Technical Skills
* **Process Management:** Mastering the creation and synchronization of processes using `fork()`, `execve()`, and `waitpid()`.
* **Signal Handling:** Managing user interruptions (like `Ctrl+C`) to ensure shell stability.
* **Parsing:** Developing a robust command-line parser to handle arguments, paths, and special characters.



##  Constraints & Rules
* **Executables:** Must find and execute binaries located in the `PATH`.
* **Built-ins:** Implementation of essential internal commands like `cd`, `setenv`, `unsetenv`, `env`, and `exit`.
* **Error Handling:** Must display clear error messages on `stderr` (e.g., "Command not found").
* **Clean Exit:** No memory leaks or zombie processes allowed.

## How to Use

### 1. Compilation
Use the provided Makefile to compile the project:
* In a terminal: `make`

### 2. Execution
Launch the shell:
* In a terminal: `./mysh`
