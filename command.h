/**
 * @brief It defines the command interpreter interface
 *
 * @file command.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

 #ifndef COMMAND_H
 #define COMMAND_H
 
 #include "types.h"
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <strings.h>

 /**
  * @brief Number of command types (short and long).
  */
 #define N_CMDT 2
 
 /**
  * @brief Number of available commands.
  */
 #define N_CMD 11
 
 /**
  * @brief Command type enumeration.
  *
  * This enumeration defines the types of command inputs: short (CMDS) and long (CMDL).
  */
 typedef enum { 
     CMDS,  /**< Short command type (e.g., "e" for Exit). */
     CMDL   /**< Long command type (e.g., "Exit"). */
 } CommandType;
 
 /**
  * @brief Command code enumeration.
  *
  * This enumeration defines the possible command codes, including NO_CMD (no command), UNKNOWN (unknown command),
  * and specific commands like EXIT, NEXT, BACK, TAKE, and DROP.
  */
 typedef enum { 
     NO_CMD = -1,  /**< No command. */
     UNKNOWN,      /**< Unknown command. */
     EXIT,         /**< Exit command. */
     NEXT,         /**< Next command. */
     BACK,         /**< Back command. */
     TAKE,         /**< Take command. */
     DROP,          /**< Drop command. */
     ATTACK,       /**< Attack command. */
     LEFT,         /**< Left command. */
     RIGHT,         /**< Right command. */
     CHAT         /**< Chat command. */
 } CommandCode;
 
 /**
  * @brief Command structure.
  *
  * This struct stores all the information related to a command.
  */
 typedef struct _Command Command;
 
 /**
  * @brief Creates a new command.
  * @author Profesores PPROG
  *
  * This function allocates memory for a new command and initializes its members.
  * @return A pointer to the newly created command.
  */
 Command* command_create();
 
 /**
  * @brief Destroys a command, freeing the allocated memory.
  * @author Profesores PPROG
  *
  * @param command A pointer to the command to be destroyed.
  * @return OK if the command was successfully destroyed, ERROR otherwise.
  */
 Status command_destroy(Command* command);
 
 /**
  * @brief Sets the command code for a given command.
  * @author Profesores PPROG
  *
  * @param command A pointer to the command.
  * @param code The command code to set.
  * @return OK if the code was successfully set, ERROR otherwise.
  */
 Status command_set_code(Command* command, CommandCode code);
 
 /**
  * @brief Gets the command code from a given command.
  * @author Profesores PPROG
  *
  * @param command A pointer to the command.
  * @return The command code.
  */
 CommandCode command_get_code(Command* command);
 
 /**
  * @brief Gets user input and sets the corresponding command code.
  * @author Profesores PPROG
  *
  * This function reads user input, parses it, and sets the appropriate command code.
  * @param command A pointer to the command.
  * @return OK if the input was successfully processed, ERROR otherwise.
  */
 Status command_get_user_input(Command* command);

 /**
  * @brief Gets the argument from a given command.
  * @author Izan Robles
  * 
  * @param command A pointer to the command.
  * @return The argument of the command.
  */
 const char* command_get_arg(Command* command);
 
 /**
  * @brief Sets the argument for a given command.
  * @author Izan Robles
  * 
  * @param command A pointer to the command.
  * @param arg The argument to set.
  * @return OK if the argument was successfully set, ERROR otherwise.
  */
 Status command_set_arg(Command* command, char* arg);

  /**
  *  @brief Gets the status of a given command.
  * @author Alejandro Gonzalez
  * 
  * @param command A pointer to the command.
  * @return The status of the command.
  */  
 Status command_get_status(Command *command);

  /**
  * 
  * @brief Sets the status of a given command.
  * @author Alejandro Gonzalez
  * 
  * @param command A pointer to the command.
  * @param status The status to set.
  *  @return OK if the status was successfully set, ERROR otherwise.
  */
 Status command_set_status(Command *command, Status status);

 #endif