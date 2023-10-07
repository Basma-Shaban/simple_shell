#include "shell.h"

/**
 * validate_input - Validates the input buffer.
 *
 * @buf: The input buffer.
 * @fd: The file descriptor to read from.
 *
 * Returns:
 * 0 on success.
 * 2 if there is a syntax error.
 * A negative value if there is a syscall error.
 */

int validate_input(char **buf, int fd) {
	/**
	 * Allocate a temporary buffer.
	 */
	char *newbuf = NULL;

	/**
	 * Read the next line from the file descriptor.
	 */
	ssize_t lenr = getline(&newbuf, fd);
	if (lenr == 0 && !isatty(fd))
	{
	/**
	 * If we reached the end of the file and are not in interactive mode,
	 *  then there is an unterminated quoted string.
	 */
	free(*buf);
	free(newbuf);
	printerr(": Syntax error: unterminated quoted string\n");
	return (-1);
	}
	if (lenr == -1)
	{
 	/**
	 * Handle any other getline() errors here.
	 */
 	return (-1);
	}

	/**
	 * Check if the input is complete.
	 */
	if (*newbuf != '\n')
	{
	/**
	 * Prompt the user to continue the input.
	 */
	fprintstrs(1, ">", NULL);

	/**Recursively validate the input.
	 */
	int ret = validate_input(&newbuf, fd);
	if (ret != 0)
	{
	return (ret);
	}
	}

	/**Free the old input buffer.
	 */
	free(*buf);

	/**
	 * Copy the new input buffer to the old one.
	 */
	*buf = newbuf;

	/**
	 * Parse the input.
	 */
	return (parse_args(buf));
}

/**
 * shintmode - Runs the shell in interactive mode.
 *
 * Returns:
 * 0 on success.
 * A negative value if there is an error.
 */

int shintmode(void)
{
	/**
	 * Allocate a temporary buffer.
	 */
	char *bufgl = NULL;

	/**
	 * Set the prompt.
	 */
	fprintstrs(1, "Homemade shell$", NULL);

	/**
	 * Read the next line from the terminal.
	 */
	ssize_t lenr = getline(&bufgl, STDIN_FILENO);
 	while (lenr > 0)
	{
 	/**
	 * Validate the input.
	 */
 	int ret = validate_input(&bufgl, STDIN_FILENO);
 	if (ret != 0)
	{
 	return (ret);
	}

	/**
	 * Read the next line from the terminal.
	 */
	lenr = getline(&bufgl, STDIN_FILENO);
	}

	/**
	 * Free the temporary buffer.
	 */
	free(bufgl);

	return (0);
}

/**
 * scriptmode - Runs the shell in script mode.
 *
 * @av: The command line arguments.
 *
 * Returns:
 * 0 on success.
 * A negative value if there is an error.
 */

int scriptmode(char *av[])
{
	/**
	 * Open the script file.
	 */
	int infile = open(av[1], O_RDONLY);
	if (infile == -1)
	{
	fprintstrs(STDERR_FILENO, av[0], ": 0: Can't open ", av[1], "\n", NULL);
	return (127);
	}

	/**
	 * Allocate a temporary buffer.
	 */
	char *bufgl = NULL;

	/**
	 * Read the next line from the script file.
	 */
	ssize_t lenr = getline(&bufgl, infile);
	while (lenr > 0)
	{
	/**
	 * Validate the input.
	 */
	int ret = validate_input(&bufgl, infile);
	if (ret != 0)
	{
	return (ret);
	}

	/**
	 * Read the next line from the script file.
	 */
	lenr = getline(&bufgl, infile);
	}

	/**
	 * Close the script file.
	 */
	close(infile);

	/**
	 * Free the temporary buffer.
	 */
	free(bufgl);

	return (0);
}

/**
 * main - Starts the shell.
 *
 * @argc: The number of command line arguments.
 * @argv: The command line arguments.
 * @envp: The environment variables.
 *
 * Returns:
 * 	The return value of the last command.
 */

int main(int argc, char *argv[], char **envp) {
	/**
	 * Initialize the shell variables.
	 */
	initialize_shell_variables(argc - 1, argv);

	/**
	 * Get the PID of the shell process.
	 */
	char *pidptr = _getpid();

	/**
	 * Set the shell variable `$` to the PID of the shell process.
	 */
	set_shell_variable("$", pidptr);

	/**
	 * Free the PID pointer.
	 */
	free(pidptr);

	/**
	 * Clear the history buffer.
	 */
	clear_history_buffer();

	/**
	 * Set the environment variables.
	 */
	set_all_environment_variables(envp, NULL);

#ifdef DEBUGINIT
	/**
	 * Print the values of some shell variables.
	 */
	printf("?:%s\n", get_shell_variable("?"));
	printf("0:%s\n", get_shell_variable("0"));
	set_shell_variable(_strdup("simplevar"), _strdup("98"));
	printf("simplevar:%s\n", get_shell_variable("simplevar"));
#endif

	/**
	 * If there is more than one command line argument, then run the shell in script mode.
	 * Otherwise, run the shell in interactive mode.
	 */
	int ret = 0;
	if (argc > 1)
	{
	ret = run_shell_in_script_mode(argv);
	}
	else
	{
	ret = run_shell_in_interactive_mode();
	}

	/**
	 * Clean up the shell before exiting.
	 */
	exit_shell_cleanup(NULL);

	/**
	 * Exit the shell history.
	 */
	exit_history();

	return (ret);
}

