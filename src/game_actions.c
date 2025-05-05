/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Private functions
*/

/**
 * @brief Handles the "unknown" command.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 */
void game_actions_unknown(Game *game);

/**
 * @brief Handles the "exit" command.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 */
void game_actions_exit(Game *game);

/**
 * @brief Handles the "take" command.
 * @author Izan Robles
 *
 * @param game A pointer to the game structure.
 */
Status game_actions_take(Game *game);

/**
 * @brief Handles the "drop" command.
 * @author Izan Robles
 *
 * @param game A pointer to the game structure.
 */
Status game_actions_drop(Game *game);

/**
 * @brief Handles the "attack" command.
 * @author Izan Robles
 *
 * @param game A pointer to the game structure.
 */
Status game_actions_attack(Game *game);

/**
 * @brief Handles the "chat" command.
 * @author Izan Robles
 *
 * @param game A pointer to the game structure.
 */
Status game_actions_chat(Game *game);

/**
 * @brief Handles the "move" command.
 * @author Daniel Martín Jaén
 *
 * @param game A pointer to the game structure.
 */
Status game_actions_move(Game *game);

/**
 * @brief Handles the "inspect" command.
 * @author Alejandro Gonzalez
 *
 * @param game A pointer to the game structure.
 */
Status game_actions_inspect(Game *game);

/**
 * @brief Handles the "recruit" command.
 * @author Alejandro Gonzalez
 *
 * @param game A pointer to the game structure.
 */
Status game_actions_recruit(Game *game);

/**
 * @brief Handles the "abandon" command.
 * @author Alejandro Gonzalez
 *
 * @param game A pointer to the game structure.
 */
Status game_actions_abandon(Game *game);
/**
   Game actions implementation
*/

Status game_actions_update(Game *game, Command *command)
{
	CommandCode cmd;
	Status status = OK;

	game_set_last_command(game, command);

	cmd = command_get_code(command);

	switch (cmd)
	{
	case UNKNOWN:
		game_actions_unknown(game);
		;
		status = ERROR;
		break;

	case EXIT:
		game_actions_exit(game);
		break;

	case TAKE:
		status = game_actions_take(game);
		break;

	case DROP:
		status = game_actions_drop(game);
		break;

	case ATTACK:
		status = game_actions_attack(game);
		break;

	case CHAT:
		status = game_actions_chat(game);
		break;

	case MOVE:
		status = game_actions_move(game);
		break;

	case INSPECT:
		status = game_actions_inspect(game);
		break;

	case RECRUIT:
		status = game_actions_recruit(game);
		break;

	case ABANDON:
		status = game_actions_abandon(game);
		break;

	default:
		status = ERROR;
		break;
	}

	command_set_status(command, status);
	return status;
}

/**
   Calls implementation for each action
*/

void game_actions_unknown(Game *game) {}

void game_actions_exit(Game *game) {}

Status game_actions_take(Game *game)
{
	Id object_id = NO_ID;
	Id player_location_id = NO_ID;
	const char *obj_name = NULL;
	int i = 0;
	Command *cmd = game_get_last_command(game);

	if (!cmd)
		return ERROR;

	obj_name = command_get_arg(cmd);
	if (!obj_name || obj_name[0] == '\0')
	{
		return ERROR;
	}

	player_location_id = game_get_player_location(game);

	for (i = 0; i < *(game_get_n_objects(game)); i++)
	{
		object_id = game_get_object_location(game, i);

		if (object_id == player_location_id &&
			strcasecmp(object_get_name(game_get_objects(game)[i]), obj_name) == 0)
		{
			if (player_add_object(game_get_player_at(game, game_get_turn(game)), object_get_id(game_get_objects(game)[i])) == OK)
			{
				game_set_object_location(game, NO_ID, i);
				return OK;
			}
			else
			{
				return ERROR;
			}
		}
	}

	return ERROR;
}

Status game_actions_drop(Game *game)
{
	Id player_location_id = NO_ID;
	Object *object = NULL;
	const char *obj_name = NULL;
	int i;
	Command *cmd = NULL;

	if (!game)
		return ERROR;

	cmd = game_get_last_command(game);
	if (!cmd)
		return ERROR;

	obj_name = command_get_arg(cmd);
	if (!obj_name || obj_name[0] == '\0')
	{
		return ERROR;
	}

	player_location_id = game_get_player_location(game);
	if (player_location_id == NO_ID)
	{
		return ERROR;
	}

	for (i = 0; i < *(game_get_n_objects(game)); i++)
	{
		object = game_get_objects(game)[i];
		if (object == NULL)
			continue;

		if (strcasecmp(object_get_name(object), obj_name) == 0 &&
			player_has_object(game_get_player_at(game, game_get_turn(game)), object_get_id(object)) == TRUE)
		{
			if (player_del_object(game_get_player_at(game, game_get_turn(game)), object_get_id(object)) == OK)
			{
				if (game_set_object_location(game, player_location_id, i) == OK)
				{
					return OK;
				}
				else
				{
					return ERROR;
				}
			}
			else
			{
				return ERROR;
			}
		}
	}

	return ERROR;
}

Status game_actions_attack(Game *game)
{
	Id player_location_id = NO_ID;
	Id character_location_id = NO_ID;
	Player *player = NULL;
	Character **character_array = NULL;
	int i, random;
	char temp[WORD_SIZE];
	Bool enemy_found = FALSE;

	player = game_get_player_at(game, game_get_turn(game));
	if (!(character_array = game_get_character_array(game)))
	{
		return ERROR;
	}

	player_location_id = game_get_player_location(game);
	if (player_location_id == NO_ID)
	{
		return ERROR;
	}

	for (i = 0; i < MAX_CHARACTERS; i++)
	{
		character_location_id = game_find_character(game, character_get_id(character_array[i]));
		if (character_location_id == player_location_id)
		{
			if (character_get_friendly(character_array[i]) == FALSE)
			{
				enemy_found = TRUE;
				random = rand() % 2;

				if (random == 0)
				{
					character_set_health(character_array[i], character_get_health(character_array[i]) - 10);
					strcpy(temp, character_get_name(character_array[i]));
					if (character_get_health(character_array[i]) > 0)
					{
						strcat(temp, " - 10");
						game_set_temporal_feedback(game, temp);
					}
					else
					{
						strcat(temp, " is dead");
						game_set_temporal_feedback(game, temp);
					}
				}
				else
				{
					if (character_get_health(character_array[i]) > 0)
					{
						player_set_health(player, player_get_health(player) - 10);
						game_set_temporal_feedback(game, "Player - 10");
					}
					else
					{
						strcpy(temp, character_get_name(character_array[i]));
						strcat(temp, " is dead");
						game_set_temporal_feedback(game, temp);
					}
				}
			}
		}
	}

	if (!enemy_found)
	{
		return ERROR;
	}

	return OK;
}

Status game_actions_chat(Game *game)
{
	Id player_location_id = NO_ID;
	Id character_location_id = NO_ID;
	Character **character_array = NULL;
	int i;
	const char *message = NULL;
	const char *character_name = NULL;
	Command *cmd = NULL;

	if (!(character_array = game_get_character_array(game)))
	{
		return ERROR;
	}

	cmd = game_get_last_command(game);
	if (!cmd)
	{
		return ERROR;
	}

	character_name = command_get_arg(cmd);
	if (!(character_name) || character_name[0] == '\0')
	{
		return ERROR;
	}

	player_location_id = game_get_player_location(game);
	if (player_location_id == NO_ID)
	{
		return ERROR;
	}

	for (i = 0; i < MAX_CHARACTERS; i++)
	{
		character_location_id = game_find_character(game, character_get_id(character_array[i]));
		if (character_location_id == player_location_id && strcasecmp(character_get_name(character_array[i]), character_name) == 0)
		{
			if (character_get_friendly(character_array[i]) == TRUE)
			{
				message = character_get_message(character_array[i]);
				if (message)
				{
					game_set_last_message(game, message);
					return OK;
				}
			}
		}
	}

	return ERROR;
}

Status game_actions_move(Game *game)
{
	Command *cmd = NULL;
	const char *arg = NULL;
	Direction dir;
	Id id_act, id_new;
	Id player_id = NO_ID;
	Id character_location_id = NO_ID;
	Character **character_array = NULL;
	Bool is_open = FALSE;
	int i;

	if (game == NULL)
	{
		return ERROR;
	}

	cmd = game_get_last_command(game);
	if (cmd == NULL)
	{
		return ERROR;
	}

	arg = command_get_arg(cmd);
	if (arg == NULL)
	{
		return ERROR;
	}

	id_act = game_get_player_location(game);
	if (id_act == NO_ID)
	{
		return ERROR;
	}

	player_id = player_get_id(game_get_player_at(game, game_get_turn(game)));
	if (player_id == NO_ID)
	{
		return ERROR;
	}

	if (!(character_array = game_get_character_array(game)))
	{
		return ERROR;
	}

	if (strcasecmp(arg, "N") == 0 || strcasecmp(arg, "NORTH") == 0)
	{
		dir = N;
	}
	else if (strcasecmp(arg, "E") == 0 || strcasecmp(arg, "EAST") == 0)
	{
		dir = E;
	}
	else if (strcasecmp(arg, "W") == 0 || strcasecmp(arg, "WEST") == 0)
	{
		dir = W;
	}
	else if (strcasecmp(arg, "S") == 0 || strcasecmp(arg, "SOUTH") == 0)
	{
		dir = S;
	}
	else
	{
		return ERROR;
	}

	id_new = game_get_connection(game, id_act, dir);
	is_open = game_connection_is_open(game, id_act, dir);

	if (id_new != NO_ID && is_open == TRUE)
	{
		game_set_player_location(game, id_new);
		space_set_discovered(game_get_space(game, id_new), TRUE);
		game_set_temporal_feedback(game, " ");
	}
	else if (id_new != NO_ID && is_open == FALSE)
	{
		game_set_temporal_feedback(game, "The door is locked");
		return OK;
	}
	else
	{
		game_set_temporal_feedback(game, "I can't do that");
		return OK;
	}

	for (i = 0; i < *game_get_n_characters(game); i++)
	{
		character_location_id = game_find_character(game, character_get_id(character_array[i]));
		if (character_location_id == id_act && character_get_following(character_array[i]) == player_id)
		{
			game_change_character_location(game, character_array[i], id_new);
		}
	}

	return OK;
}

Status game_actions_inspect(Game *game)
{
	Id player_location_id = NO_ID;
	Id object_location_id = NO_ID;
	Id obj_id = NO_ID;
	const char *obj_name = NULL;
	const char *description = NULL;
	Object *object = NULL;
	Inventory *player_inventory = NULL;
	int i;
	Command *cmd = NULL;

	if (!game)
		return ERROR;

	cmd = game_get_last_command(game);
	if (!cmd)
		return ERROR;

	obj_name = command_get_arg(cmd);
	if (!obj_name || obj_name[0] == '\0')
	{
		return ERROR;
	}

	player_location_id = game_get_player_location(game);
	if (player_location_id == NO_ID)
	{
		return ERROR;
	}

	for (i = 0; i < *(game_get_n_objects(game)); i++)
	{
		object = game_get_objects(game)[i];
		object_location_id = game_get_object_location(game, i);

		if (object_location_id == player_location_id && strcasecmp(object_get_name(object), obj_name) == 0)
		{
			description = object_get_description(object);
			game_set_last_message(game, description);
			return OK;
		}
	}

	player_inventory = player_get_inventory(game_get_player_at(game, game_get_turn(game)));
	if (!player_inventory)
	{
		return ERROR;
	}

	for (i = 0; i < inventory_get_count(player_inventory); i++)
	{
		obj_id = set_get_id_at(inventory_get_objects(player_inventory), i);
		object = game_get_object_by_id(game, obj_id);
		if (object && strcasecmp(object_get_name(object), obj_name) == 0)
		{
			description = object_get_description(object);
			game_set_last_message(game, description);
			return OK;
		}
	}

	game_set_last_message(game, "You can't inspect that object.");
	return ERROR;
}

Status game_actions_recruit(Game *game)
{
	Id player_location = NO_ID;
	Id player_id = NO_ID;
	Id character_location_id = NO_ID;
	Character **character_array = NULL;
	const char *character_name = NULL;
	Command *cmd = NULL;
	int i;

	cmd = game_get_last_command(game);
	if (!cmd)
	{
		return ERROR;
	}

	character_name = command_get_arg(cmd);
	if (character_name == NULL || character_name[0] == '\0')
	{
		return ERROR;
	}

	if (!(character_array = game_get_character_array(game)))
	{
		return ERROR;
	}

	player_location = game_get_player_location(game);
	if (player_location == NO_ID)
	{
		return ERROR;
	}
	player_id = player_get_id(game_get_player_at(game, game_get_turn(game)));
	if (player_id == NO_ID)
	{
		return ERROR;
	}

	for (i = 0; i < MAX_CHARACTERS; i++)
	{
		character_location_id = game_find_character(game, character_get_id(character_array[i]));
		if (character_location_id == player_location &&
			strcasecmp(character_get_name(character_array[i]), character_name) == 0 &&
			character_get_friendly(character_array[i]) == TRUE)
		{
			if (character_set_following(character_array[i], player_id) == OK)
			{
				game_set_temporal_feedback(game, "Character recruited successfully!");
				return OK;
			}
		}
	}
	game_set_temporal_feedback(game, "You cannot recruit this character.");
	return ERROR;
}

Status game_actions_abandon(Game *game)
{
	Id player_location = NO_ID;
	Id player_id = NO_ID;
	Id character_location_id = NO_ID;
	Character **character_array = NULL;
	const char *character_name = NULL;
	Command *cmd = NULL;
	int i;
	Bool character_found = FALSE;

	cmd = game_get_last_command(game);
	if (!cmd)
	{
		return ERROR;
	}

	character_name = command_get_arg(cmd);
	if (character_name == NULL || character_name[0] == '\0')
	{
		game_set_temporal_feedback(game, "Invalid character name.");
		return ERROR;
	}

	if (!(character_array = game_get_character_array(game)))
	{
		return ERROR;
	}

	player_location = game_get_player_location(game);
	if (player_location == NO_ID)
	{
		return ERROR;
	}

	player_id = player_get_id(game_get_player_at(game, game_get_turn(game)));
	if (player_id == NO_ID)
	{
		return ERROR;
	}

	for (i = 0; i < MAX_CHARACTERS; i++)
	{
		character_location_id = game_find_character(game, character_get_id(character_array[i]));
		if (character_location_id == player_location &&
			strcasecmp(character_get_name(character_array[i]), character_name) == 0 &&
			character_get_following(character_array[i]) == player_id)
		{

			if (character_set_following(character_array[i], NO_ID) == OK)
			{
				game_set_temporal_feedback(game, "Character abandoned successfully!");
				character_found = TRUE;
				break;
			}
			else
			{
				game_set_temporal_feedback(game, "Failed to abandon the character.");
				return ERROR;
			}
		}
	}

	if (!character_found)
	{
		game_set_temporal_feedback(game, "The character is not following you or is not in your location.");
		return ERROR;
	}

	return OK;
}
