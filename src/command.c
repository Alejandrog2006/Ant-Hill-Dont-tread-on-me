/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "command.h"

/**
 * @brief Defines length of the command
 */
#define CMD_LENGHT 30

/**
 * @brief Defines maximum argument size
 */
#define CMD_ARG_SIZE 32

/**
 * @brief Defines database for commands
 */
char *cmd_to_str[N_CMD][N_CMDT] = {{"", "No command"}, {"", "Unknown"}, {"e", "Exit"}, {"t", "Take"}, {"d", "Drop"}, {"a", "Attack"}, {"c", "Chat"}, {"m", "Move"}, {"i", "Inspect"}, {"r", "Recruit"}, {"ab", "Abandon"}};

/**
 * @brief Private implementation of command datatype
 */
struct _Command
{
	CommandCode code;		/*!< Name of the command */
	char arg[CMD_ARG_SIZE]; /*!< Argument of the command */
	Status command_status;	/*!< Status of the command */
};

Command *command_create()
{
	Command *newCommand = NULL;

	newCommand = (Command *)malloc(sizeof(Command));
	if (newCommand == NULL)
	{
		return NULL;
	}

	newCommand->code = NO_CMD;
	newCommand->arg[0] = '\0';
	newCommand->command_status = ERROR;

	return newCommand;
}

Status command_destroy(Command *command)
{
	if (!command)
	{
		return ERROR;
	}

	free(command);
	command = NULL;
	return OK;
}

Status command_set_code(Command *command, CommandCode code)
{
	if (!command)
	{
		return ERROR;
	}

	command->code = code;

	return OK;
}

CommandCode command_get_code(Command *command)
{
	if (!command)
	{
		return NO_CMD;
	}
	return command->code;
}

Status command_get_user_input(Command *command)
{
	char input[CMD_LENGHT] = "", *token = NULL;
	int i = UNKNOWN - NO_CMD + 1;
	CommandCode cmd;

	if (!command)
	{
		return ERROR;
	}

	if (fgets(input, CMD_LENGHT, stdin))
	{
		token = strtok(input, " \n");
		if (!token)
		{
			return command_set_code(command, UNKNOWN);
		}

		cmd = UNKNOWN;
		while (cmd == UNKNOWN && i < N_CMD)
		{
			if (!strcasecmp(token, cmd_to_str[i][CMDS]) || !strcasecmp(token, cmd_to_str[i][CMDL]))
			{
				cmd = i + NO_CMD;
			}
			else
			{
				i++;
			}
		}

		command_set_code(command, cmd);

		if (cmd == TAKE || cmd == DROP || cmd == MOVE || cmd == INSPECT || cmd == RECRUIT || cmd == ABANDON || cmd == CHAT)
		{
			token = strtok(NULL, "\n");
			if (token)
			{
				while (*token == ' ')
					token++;
				command_set_arg(command, token);
			}
			else
			{
				command_set_arg(command, "");
			}
		}

		return OK;
	}
	return command_set_code(command, EXIT);
}

const char *command_get_arg(Command *command)
{
	if (!command)
	{
		return NULL;
	}
	return command->arg;
}

Status command_set_arg(Command *command, char *arg)
{
	if (!command || !arg)
	{
		return ERROR;
	}

	if (strlen(arg) >= CMD_ARG_SIZE)
	{
		return ERROR;
	}

	strcpy(command->arg, arg);
	return OK;
}

Status command_get_status(Command *command)
{
	if (!command)
	{
		return ERROR;
	}
	return command->command_status;
}

Status command_set_status(Command *command, Status status)
{
	if (!command)
	{
		return ERROR;
	}
	command->command_status = status;
	return OK;
}
