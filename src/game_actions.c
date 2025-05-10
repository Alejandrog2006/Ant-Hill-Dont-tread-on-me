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
 * @brief Handles the "pass" command.
 * @author Daniel Martín Jaén
 *
 * @param game A pointer to the game struct
 */
Status game_actions_pass(Game *game);

/**
 * @brief Handles the open command.
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 */
Status game_actions_open(Game *game);

/**
 * @brief Handles the save command
 * @author Izan Robles
 * 
 * @param game A pointer to the game struct
 */
Status game_actions_save(Game *game);

/**
 * @brief Handles the load command
 * @author Izan Robles
 * 
 * @param game A pointer to a pointer to the game struct
 */
Status game_actions_load(Game **game);

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

	case SAVE:
		status = game_actions_save(game);
		break;

	case LOAD:
		status = game_actions_load(&game);
		break;

	case PASS:
		status = game_actions_pass(game);
		break;

	case OPEN:
		status = game_actions_open(game);
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
	Id object_dependency = NO_ID;
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
		object_dependency = object_get_dependency(game_get_objects(game)[i]);

		if (object_get_movable(game_get_objects(game)[i]) == FALSE)
		{
			game_set_last_message(game, "This object is not movable.");
		}

		if (object_id == player_location_id &&
			strcasecmp(object_get_name(game_get_objects(game)[i]), obj_name) == 0 &&
			object_get_movable(game_get_objects(game)[i]) == TRUE)
		{
			if (object_dependency == NO_ID)
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
			else
			{
				if (player_has_object(game_get_player_at(game, game_get_turn(game)), object_dependency) == TRUE)
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
				else
				{
					game_set_last_message(game, "You need another object to take this one.");
					return ERROR;
				}
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
	Id player_id = NO_ID;
	Player *player = NULL;
	Character **character_array = NULL;
	int i, j, random, followers_count = 0, damage = 0;
	char temp[WORD_SIZE];
	Bool enemy_found = FALSE;

	if (!game)
	{
		return ERROR;
	}

	if (game_get_actions(game) == 0)
	{
		game_set_last_message(game, " I'm too tired for that!");
	}

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

	player_id = player_get_id(game_get_player_at(game, game_get_turn(game)));
	if (player_id == NO_ID)
	{
		return ERROR;
	}

	for (i = 0; i < MAX_CHARACTERS; i++)
	{
		if (character_array[i] != NULL && character_get_following(character_array[i]) == player_id)
		{
			followers_count++;
		}
	}

	for (i = 0; i < MAX_CHARACTERS; i++)
	{
		character_location_id = game_find_character(game, character_get_id(character_array[i]));
		if (character_location_id == player_location_id)
		{
			if (character_get_friendly(character_array[i]) == FALSE && character_get_following(character_array[i]) != player_id)
			{
				enemy_found = TRUE;
				random = rand() % 2;

				if (random == 0)
				{
					damage = 1 + followers_count;
					character_set_health(character_array[i], character_get_health(character_array[i]) - damage);
					strcpy(temp, character_get_name(character_array[i]));
					if (character_get_health(character_array[i]) > 0)
					{
						sprintf(temp + strlen(temp), " - %d", damage);
						game_set_last_message(game, temp);
					}
					else
					{
						strcat(temp, " is dead");
						game_set_last_message(game, temp);
					}
				}
				else if (character_get_health(character_array[i]) > 0)
				{
					int target = rand() % (followers_count + 1);
					if (target == 0)
					{
						player_set_health(player, player_get_health(player) - 1);
						game_set_last_message(game, "Player - 1");
					}
					else
					{
						int follower_index = 0;
						for (j = 0; j < MAX_CHARACTERS; j++)
						{
							if (character_array[j] != NULL && character_get_following(character_array[j]) == player_id)
							{
								if (++follower_index == target)
								{
									character_set_health(character_array[j], character_get_health(character_array[j]) - 1);
									sprintf(temp, "%s - 1", character_get_name(character_array[j]));
									game_set_last_message(game, temp);
									break;
								}
							}
						}
					}
				}
				else
				{
					return ERROR;
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
	Direction dir, r_dir;
	Id id_act, id_new;
	Id player_id = NO_ID;
	Id character_location_id = NO_ID;
	Character **character_array = NULL;
	Bool is_open = FALSE;
	char feedback[30];
	int i;

	if (game == NULL)
	{
		return ERROR;
	}

	if (game_get_actions(game) == 0)
	{
		game_set_last_message(game, " I'm too tired for that!");
		return OK;
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
		r_dir = S;
	}
	else if (strcasecmp(arg, "E") == 0 || strcasecmp(arg, "EAST") == 0)
	{
		dir = E;
		r_dir = W;
	}
	else if (strcasecmp(arg, "W") == 0 || strcasecmp(arg, "WEST") == 0)
	{
		dir = W;
		r_dir = E;
	}
	else if (strcasecmp(arg, "S") == 0 || strcasecmp(arg, "SOUTH") == 0)
	{
		dir = S;
		r_dir = N;
	}
	else if (strcasecmp(arg, "U") == 0 || strcasecmp(arg, "UP") == 0)
	{
		dir = U;
		r_dir = D;
	}
	else if (strcasecmp(arg, "D") == 0 || strcasecmp(arg, "DOWN") == 0)
	{
		dir = D;
		r_dir = U;
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

		if(game_connection_is_open(game, id_new, r_dir) == FALSE)
		{
			link_set_open(game_get_link(game, id_new, r_dir), TRUE);
		}

		game_set_last_message(game, " ");
	}
	else if (id_new != NO_ID && is_open == FALSE)
	{
		sprintf(feedback, "A %s blocks the way!", link_get_name(game_get_link(game, id_act, dir)));
		game_set_last_message(game, feedback);
		return ERROR;
	}
	else
	{
		game_set_last_message(game, " I can't do that.");
		return ERROR;
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

	game_set_last_message(game, " You can't inspect that object.");
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
				game_set_last_message(game, " Character recruited successfully!");
				return OK;
			}
		}
	}
	game_set_last_message(game, " You cannot recruit this character.");
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
		game_set_last_message(game, " Invalid character name.");
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
				game_set_last_message(game, " Character abandoned successfully!");
				character_found = TRUE;
				break;
			}
			else
			{
				game_set_last_message(game, " Failed to abandon the character.");
				return ERROR;
			}
		}
	}

	if (!character_found)
	{
		game_set_last_message(game, " The character is not following you or is not in your location.");
		return ERROR;
	}

	return OK;
}

Status game_actions_save(Game *game)
{
	const char *filename = NULL;
	filename = command_get_arg(game_get_last_command(game));

	if (!filename || filename[0] == '\0')
	{
		filename = "save.dat";
		fprintf(stdout, "No filename provided\n");
	}

	if (game_management_save(game, filename) == ERROR)
	{
		game_set_last_message(game, "Error saving the game.");
		return ERROR;
	}
	game_set_last_message(game, "Game saved successfully.");
	return OK;
}

Status game_actions_load(Game **game)
{
	const char *filename = NULL;
	char *temp = NULL;
	filename = command_get_arg(game_get_last_command(*game));

	if (filename == NULL || filename[0] == '\0')
	{
		temp = malloc(sizeof(char) * 11);
		if (!temp)
		{
			game_set_last_message(*game, " Error loading the game");
			return ERROR;
		}

		strcpy(temp, "save.dat");
	}
	else
	{
		temp = malloc(sizeof(char) * (strlen(filename) + 1));
		if (!temp)
		{
			game_set_last_message(*game, " Error loading the game");
			return ERROR;
		}

		strcpy(temp, filename);
	}

	if (game_management_load(game, temp) == ERROR)
	{
		free(temp);
		game_set_last_message(*game, " Error loading the game.");
		return ERROR;
	}

	free(temp);
	game_set_last_message(*game, " Game loaded successfully.");
	return OK;
}

Status game_actions_pass(Game *game)
{
	if (!game)
	{
		return ERROR;
	}

	game_set_actions(game, MAX_ACTIONS);
	game_set_pass(game, TRUE);
	return OK;
}

Status game_actions_open(Game *game){
	Command *cmd = NULL;
	const char *arg1 = NULL, *arg2 = NULL;
	char feedback[30];
	Link *link_act = NULL;
	Object **objects_p = NULL, *object_act = NULL;
	Id id_act;
	int i, n_objects;

	if(!game) 
	{
		return ERROR;
	}

	cmd = game_get_last_command(game);
	arg1 = command_get_arg(cmd);
	arg2 = command_get_arg2(cmd);
	id_act = game_get_player_location(game);
	objects_p = game_get_objects(game);
	n_objects = inventory_get_count(player_get_inventory(game_get_player_at(game, game_get_turn(game))));

	if (arg1 == NULL || arg1[0] == '\0' || arg2 == NULL || arg2[0] == '\0' || id_act == NO_ID || objects_p == NULL)
	{
		return ERROR;
	}

	for(i = 0; i < n_objects; i++)
	{
		if(strcasecmp(arg2, object_get_name(objects_p[i])) == 0)
		{
			object_act = objects_p[i];
			break;
		}
	}

	if(i == n_objects)
	{
		game_set_last_message(game, " That object isn't in your inventory.");
		return ERROR;
	}

	for (i = 0; i < 6; i++)
	{
		link_act = game_get_link(game, id_act, (Direction)i);

		if(strcasecmp(link_get_name(link_act), arg1) == 0 && link_get_id(link_act) == object_get_open(object_act) && link_get_open(link_act) == FALSE && 
						inventory_contains_object(player_get_inventory(game_get_player_at(game, game_get_turn(game))), object_get_id(object_act)) == TRUE)
		{
			link_set_open(link_act, TRUE);
			sprintf(feedback, " %s is open now.", arg1);
			game_set_last_message(game, feedback);
			return OK;
		} 
		else if(link_get_open(link_act) == TRUE && strcasecmp(link_get_name(link_act), arg1) == 0)
		{
			sprintf(feedback, " %s is already open.", arg1);
			game_set_last_message(game, feedback);
			return ERROR;
		}

		else if(strcasecmp(link_get_name(link_act), arg1) == 0)
		{
			sprintf(feedback, " %s can't be used to open %s.", arg2 , arg1);
			game_set_last_message(game, feedback);
			return ERROR;
		}
	}

	sprintf(feedback, " I can't do that.");
	game_set_last_message(game, feedback);
	return ERROR;
}