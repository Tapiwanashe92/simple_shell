#include "shell.h"

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);

/**
 * help_all - displays all possible builtin shellby commands
 */
void help_all(void)
{
	char *msg = "Shellby\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "Type 'help' to see this list.\nType 'help name' to find ";
	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "out more about the function 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "alias[NAME['VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "[DIRECTORY]\n  exit    \texit[STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "\n  setenv  \tsetenv[VARIABLE][VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "unsetevn[VARIABLE]\n";
	write(STDOUT_FILENO, msg, str_len(msg));
}

/**
* help_alias - Displays information on shellby builtin command 'alias'.
*/
void help_alias(void)
{
	char *msg = "alias : alias[NAME['VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "\n\talias : Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "the format NAME = 'VALUE'.\n\talias name[name2 ...] : prints";
	write(STDOUT_FILENO, msg, str_len(msg));
	msg = " the aliases name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "form NAME = 'VALUE'.\n\talias NAME = 'VALUE'[...] : Defines";
	write(STDOUT_FILENO, msg, str_len(msg));
	msg = " an alias for each NAME whose VALUE is given. if NAME ";
	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, msg, str_len(msg));
}

/**
* help_cd - displays information on the shellby builtin command 'cd'
*/
void help_cd(void)
{
	char *msg = "cd : cd[DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, msg, str_len(msg));
	msg = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, msg, str_len(msg));
	msg = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "after a change of directory.\n";
	write(STDOUT_FILENO, msg, str_len(msg));
}

/**
* help_exit - displays information on the shellby builtin command 'exit'
*/
void help_exit(void)
{
	char *msg = "exit : exit[STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, msg, str_len(msg));
	msg = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, msg, str_len(msg));
	msg = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, msg, str_len(msg));
	msg = " exit 0.\n";
	write(STDOUT_FILENO, msg, str_len(msg));
}

/**
* help_help - displays information on the shellby builtin command 'help'
*/
void help_help(void)
{
char *msg = "help : help\n\tSee all possible shellby builtin commands.\n";

write(STDOUT_FILENO, msg, str_len(msg));
msg = "\n      help[BUILTIN NAME]\n\tSee specific information on each ";
write(STDOUT_FILENO, msg, str_len(msg));
msg = "builtin command.\n";
write(STDOUT_FILENO, msg, str_len(msg));
}
