# Simple Shell Project

## Description

The Simple Shell project is a UNIX command interpreter that provides a basic user interface for interacting with the operating system. It allows users to execute commands and perform various operations.

This project aims to create a simple shell that can handle commands, execute programs, and manage processes. It utilizes the `execve()` system call to execute commands and creates child processes using `fork()` for command execution. The shell also handles the `PATH` environment variable to locate and execute programs.

The shell provides support for built-in commands such as `exit` to close the shell and `env` to display environment variables. It handles the `CTRL+C` signal to prevent the shell from closing unintentionally.

## Requirements

- GCC (GNU Compiler Collection) version 4.8 or later

## Compilation

To compile the Simple Shell project, use the following command:

```
gcc-4.8 -Wall -Werror -Wextra -pedantic *.c -o hsh
```

## Execution

To run the Simple Shell, execute the compiled binary:

```
./hsh
```

## Usage

The Simple Shell project supports various commands and operations. Some examples include:

- Running a command using the `PATH` environment variable:

  ````
  $ ls
  ```

- Running a specific program by providing its absolute path:

  ````
  $ /bin/ls
  ```

- Using built-in commands:

  ````
  $ exit
  ```

  ````
  $ env
  ```

## Exiting the Shell

To exit the Simple Shell, you can either type the `exit` command:

```
$ exit
```

Or use the keyboard shortcut `CTRL+D`.

## Authors

- Basma Shaban Ali <shaabanbasma@gmail.com>
- Loay Awadalla <loay_awadalla@gmail.com>
