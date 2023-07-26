#include "shell.h"

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

/**
 * help_env - displays information on the shellby builtin command 'env'
 */
void help_env(void)
{
	char *msg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg, str_len(msg));
}

/**
 * help_setenv - displays information on the shellby builtin command 'setenv'
 */
void help_setenv(void)
{
	char *msg = "setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, str_len(msg));
}

/**
 * help_unsetenv - displays information on the shellby builtin command
 * 'unsetenv'
 */
void help_unsetenv(void)
{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemove an ";

	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, str_len(msg));
}
