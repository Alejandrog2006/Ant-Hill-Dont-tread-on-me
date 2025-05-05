/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game.h"
#include "game_reader.h"
#include "character.h"
#include "time.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Private implementation of the interface module
 */
struct _InterfaceData
{
	Command *last_cmd;					 /**< Last command of a specific player */
	char last_message[MESSAGE_SIZE + 1]; /**< Last message of a specific player */
};

/**
 * @brief Private implementation of game module
 */
struct _Game
{
	Player *players[MAX_PLAYERS];			  /**< Array of pointers to the players */
	InterfaceData *interfaces[MAX_PLAYERS];	  /**< Array of pointers to the interfaces of each player */
	Space *spaces[MAX_SPACES];				  /**< Array of spaces in the game. */
	Object *objects[MAX_OBJECTS];			  /**< Array of objects in the game. */
	Character *characters[MAX_CHARACTERS];	  /**< Array of characters in the game. */
	Link *links[MAX_LINKS];					  /**< Array of links in the game */
	int n_spaces;							  /**< Number of spaces in the game. */
	int n_objects;							  /**< Number of objects in the game. */
	int n_characters;						  /**< Number of characters in the game. */
	int n_links;							  /**< Number of links in the game. */
	int n_players;							  /**< Number of players in the game */
	Bool finished;							  /**< Whether the game is finished or not. */
	char temporal_feedback[MESSAGE_SIZE + 1]; /**< Temporal feedback message. */
	int turn;								  /**< The position of the active player in the players array */
};

InterfaceData *game_create_interface()
{
	InterfaceData *new_interface = NULL;

	if (!(new_interface = (InterfaceData *)malloc(sizeof(InterfaceData))))
	{
		return NULL;
	}

	new_interface->last_cmd = command_create();
	new_interface->last_message[0] = '\0';
	return new_interface;
}

Status game_create(Game **game)
{
	int i;

	if (*game == NULL)
	{
		*game = (Game *)malloc(sizeof(Game));
		if (!*game)
		{
			return ERROR;
		}
	}

	/*Initialize seed for random numbers*/
	srand(time(NULL));

	/*Initialize character array*/
	(*game)->n_characters = 0;
	for (i = 0; i < MAX_CHARACTERS; i++)
	{
		(*game)->characters[i] = NULL;
	}

	for (i = 0; i < MAX_SPACES; i++)
	{
		(*game)->spaces[i] = NULL;
	}

	(*game)->n_spaces = 0;
	(*game)->n_objects = 0;
	(*game)->n_links = 0;
	(*game)->n_players = 0;

	for (i = 0; i < MAX_PLAYERS; i++)
	{
		(*game)->players[i] = NULL;
	}

	for (i = 0; i < MAX_PLAYERS; i++)
	{
		(*game)->interfaces[i] = NULL;
	}

	for (i = 0; i < MAX_OBJECTS; i++)
	{
		(*game)->objects[i] = NULL;
	}
	/*(*game)->object[0] = object_create(NO_ID);
	if ((*game)->object[0] == NULL) {
	  return ERROR;
	}
	(*game)->n_objects++;*/

	(*game)->finished = FALSE;

	for (i = 0; i < MAX_LINKS; i++)
	{
		(*game)->links[i] = NULL;
	}

	(*game)->temporal_feedback[0] = '\0';
	(*game)->turn = 0;

	return OK;
}

Status game_create_from_file(Game **game, char *filename)
{
	if (game_create(game) == ERROR)
	{
		fprintf(stderr, "Error: Failed to create game structure.\n");
		return ERROR;
	}

	if (game_load_spaces(*game, filename) == ERROR)
	{
		fprintf(stderr, "Error: Failed to load spaces from file.\n");
		return ERROR;
	}

	if (game_load_players(*game, filename) == ERROR)
	{
		fprintf(stderr, "Error: Failed to load players from file.\n");
		return ERROR;
	}

	if (game_load_objects(*game, filename) == ERROR)
	{
		fprintf(stderr, "Error: Failed to load objects from file.\n");
		return ERROR;
	}

	if (game_load_links(*game, filename) == ERROR)
	{
		fprintf(stderr, "Error: Failed to load links from file.\n");
		return ERROR;
	}

	if (game_load_characters(*game, filename) == ERROR)
	{
		fprintf(stderr, "Error: Failed to load characters from file.\n");
		return ERROR;
	}

	/* The player is located in the first space */
	game_set_player_location(*game, player_get_location(game_get_player_at(*game, game_get_turn(*game))));
	/*game_set_object_location(*game, game_get_space_id_at(*game, 0), 0);*/

	object_set_description((*game)->objects[0], "A magic wand");
	object_set_description((*game)->objects[1], "A book of magic.");
	object_set_description((*game)->objects[2], "A magic potion.");
	object_set_description((*game)->objects[3], "A magic ring.");

	return OK;
}

Status game_destroy(Game *game)
{
	int i = 0;

	if (!game)
	{
		return ERROR;
	}

	for (i = 0; i < game->n_spaces; i++)
	{
		if (game->spaces[i] != NULL)
		{
			space_destroy(game->spaces[i]);
			game->spaces[i] = NULL;
		}
	}

	/*Checks all character array and frees as needed*/
	for (i = 0; i < MAX_CHARACTERS; i++)
	{
		if (game->characters[i] != NULL)
		{
			character_destroy(game->characters[i]);
			game->characters[i] = NULL;
		}
	}

	for (i = 0; i < MAX_PLAYERS; i++)
	{
		if (game->players[i] != NULL)
		{
			player_destroy(game->players[i]);
			game->players[i] = NULL;
		}
	}

	for (i = 0; i < MAX_PLAYERS; i++)
	{
		if (game->interfaces[i] != NULL)
		{
			command_destroy(game->interfaces[i]->last_cmd);
			free(game->interfaces[i]);
			game->interfaces[i] = NULL;
		}
	}

	for (i = 0; i < game->n_objects; i++)
	{
		if (game->objects[i] != NULL)
		{
			object_destroy(game->objects[i]);
			game->objects[i] = NULL;
		}
	}

	for (i = 0; i < game->n_links; i++)
	{
		if (game->links[i] != NULL)
		{
			link_destroy(game->links[i]);
			game->links[i] = NULL;
		}
	}

	free(game);
	game = NULL;
	return OK;
}

Space *game_get_space(Game *game, Id id)
{
	int i = 0;

	if (id == NO_ID)
	{
		return NULL;
	}

	for (i = 0; i < game->n_spaces; i++)
	{
		if (id == space_get_id(game->spaces[i]))
		{
			return game->spaces[i];
		}
	}

	return NULL;
}

Id game_get_player_location(Game *game)
{

	Id location = player_get_location(game->players[game->turn]);

	return location;
}

Status game_set_player_location(Game *game, Id id)
{
	if (id == NO_ID)
	{
		return ERROR;
	}

	*(player_get_location_pointer(game->players[game->turn])) = id;

	return OK;
}

Id game_get_object_location(Game *game, int position)
{
	int i = 0;

	if (game == NULL || position < 0 || position >= MAX_OBJECTS || game->objects[position] == NULL)
	{
		return NO_ID;
	}

	for (i = 0; i < game->n_spaces; i++)
	{

		if (game->spaces[i] != NULL && (space_get_id(game->spaces[i]) == object_get_location(game->objects[position])))
		{
			return object_get_location(game->objects[position]);
		}
	}

	return NO_ID;
}

Status game_set_object_location(Game *game, Id id, int position)
{
	if (position < 0 || position >= MAX_OBJECTS || game == NULL)
	{
		return ERROR;
	}

	*(object_get_location_pointer(game->objects[position])) = id;

	if (game->n_objects == position)
	{
		game->n_objects++;
	}

	space_set_object(game_get_space(game, id), TRUE);

	return OK;
}

Command *game_get_last_command(Game *game)
{
	return game->interfaces[game->turn]->last_cmd;
}

Status game_set_last_command(Game *game, Command *command)
{
	game->interfaces[game->turn]->last_cmd = command;

	return OK;
}

Bool game_get_finished(Game *game)
{
	return game->finished;
}

Status game_set_finished(Game *game, Bool finished)
{
	game->finished = finished;

	return OK;
}

void game_print(Game *game)
{
	int i = 0;

	printf("\n\n-------------\n\n");

	printf("=> Spaces: \n");
	for (i = 0; i < game->n_spaces; i++)
	{
		space_print(game->spaces[i]);
	}

	for (i = 0; i < game->n_objects; i++)
	{
		printf("=> Object location: %d\n", (int)object_get_id(game->objects[i]));
	}
}

/*ADDITIONAL FUNCTIONS*/

int *game_get_n_spaces(Game *game)
{
	if (game == NULL)
	{
		return NULL;
	}
	return &(game->n_spaces);
}

Space **game_get_spaces(Game *game)
{
	if (game == NULL)
	{
		return NULL;
	}
	return game->spaces;
}

int *game_get_n_objects(Game *game)
{
	if (game == NULL)
	{
		return NULL;
	}
	return &(game->n_objects);
}

Object **game_get_objects(Game *game)
{
	if (game == NULL)
	{
		return NULL;
	}
	return game->objects;
}

Character **game_get_character_array(Game *game)
{
	if (game == NULL)
	{
		return NULL;
	}
	return game->characters;
}

Status game_set_last_message(Game *game, const char *message)
{
	if (!game || !message)
	{
		return ERROR;
	}
	strncpy(game->interfaces[game->turn]->last_message, message, MESSAGE_SIZE);
	game->interfaces[game->turn]->last_message[MESSAGE_SIZE] = '\0';
	return OK;
}

const char *game_get_last_message(Game *game)
{
	if (!game)
	{
		return NULL;
	}
	return game->interfaces[game->turn]->last_message;
}

const char *game_get_temporal_feedback(Game *game)
{
	if (!game)
	{
		return NULL;
	}
	return game->temporal_feedback;
}

Status game_set_temporal_feedback(Game *game, const char *feedback)
{
	if (!game || !feedback)
	{
		return ERROR;
	}
	strncpy(game->temporal_feedback, feedback, MESSAGE_SIZE - 1);
	game->temporal_feedback[MESSAGE_SIZE - 1] = '\0';
	return OK;
}

Object *game_get_object_by_id(Game *game, Id id)
{
	int i;

	if (!game || id == NO_ID)
	{
		return NULL;
	}

	for (i = 0; i < *(game_get_n_objects(game)); i++)
	{
		if (object_get_id(game->objects[i]) == id)
		{
			return game->objects[i];
		}
	}

	return NULL;
}

Link **game_get_links(Game *game)
{
	if (game == NULL)
	{
		return NULL;
	}

	return game->links;
}

int *game_get_n_links(Game *game)
{
	if (game == NULL)
	{
		return NULL;
	}

	return &game->n_links;
}

Id game_get_connection(Game *game, Id id_orig, Direction dir)
{
	int i;

	if (game == NULL || id_orig == NO_ID || dir == NONE)
	{
		return NO_ID;
	}

	for (i = 0; i < game->n_links; i++)
	{
		if (link_get_origin(game->links[i]) == id_orig && link_get_direction(game->links[i]) == dir)
		{
			return link_get_destination(game->links[i]);
		}
	}

	return NO_ID;
}

Bool game_connection_is_open(Game *game, Id id_orig, Direction dir)
{
	int i;

	if (game == NULL || id_orig == NO_ID || dir == NONE)
	{
		return FALSE;
	}

	for (i = 0; i < game->n_links; i++)
	{
		if (link_get_origin(game->links[i]) == id_orig && link_get_direction(game->links[i]) == dir)
		{
			return link_get_open(game->links[i]);
		}
	}

	return FALSE;
}

int *game_get_n_characters(Game *game)
{
	if (game == NULL)
	{
		return NULL;
	}

	return &game->n_characters;
}

const int game_get_turn(Game *game)
{
	if (game == NULL)
	{
		return -1;
	}

	return game->turn;
}

Status game_set_turn(Game *game, int turn_n)
{
	if (game == NULL || turn_n < 0)
	{
		return ERROR;
	}

	game->turn = turn_n;
	return OK;
}

Player **game_get_players(Game *game)
{
	if (game == NULL)
	{
		return NULL;
	}

	return game->players;
}

const int game_get_n_players(Game *game)
{
	if (game == NULL)
	{
		return -1;
	}

	return game->n_players;
}

Status game_set_n_players(Game *game, int n_players)
{
	if (game == NULL || n_players < 0)
	{
		return ERROR;
	}

	game->n_players = n_players;
	return OK;
}

InterfaceData **game_get_interfaces(Game *game)
{
	if (game == NULL)
	{
		return NULL;
	}

	return game->interfaces;
}

Player *game_get_player_at(Game *game, int position)
{
	if (game == NULL || position < 0)
	{
		return NULL;
	}

	return game->players[position];
}

Id game_find_character(Game *game, Id id)
{
	int i, j, n;
	Set *current_chars = NULL;
	Space **spaces_p = NULL;

	if (!game || id == NO_ID)
	{
		return NO_ID;
	}

	spaces_p = game_get_spaces(game);

	for (i = 0; i < game->n_spaces; i++)
	{
		current_chars = space_get_characters(spaces_p[i]);
		n = set_get_count(current_chars);

		for (j = 0; j < n; j++)
		{
			if (id == set_get_id_at(current_chars, j))
			{
				return space_get_id(spaces_p[i]);
			}
		}
	}

	return NO_ID;
}

Status game_change_character_location(Game *game, Character *char_p, Id new_location)
{
	Id old_location;

	if (!game || !char_p || new_location < 0 || new_location == NO_ID)
	{
		return ERROR;
	}

	old_location = game_find_character(game, character_get_id(char_p));
	space_del_character(game_get_space(game, old_location), char_p);

	space_add_character(game_get_space(game, new_location), char_p);

	return OK;
}