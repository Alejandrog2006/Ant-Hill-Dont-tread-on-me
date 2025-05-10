/**
 * @brief Implementation of game reader
 *
 * @file game_reader.c
 * @version 0
 * @date 27-01-2025
 */

#include "game_reader.h"
#include "space.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Status game_load_spaces(Game *game, char *filename)
{
	FILE *file = NULL;
	char line[WORD_SIZE] = "";
	char name[WORD_SIZE] = "";
	char *toks = NULL;
	Id id = NO_ID;
	char gdesc[GDESC_ROWS][GDESC_COLS + 1];
	Space *space = NULL;
	Status status = OK;
	int i;

	if (!filename)
	{
		return ERROR;
	}

	file = fopen(filename, "r");
	if (file == NULL)
	{
		return ERROR;
	}

	while (fgets(line, WORD_SIZE, file))
	{
		if (strncmp("#s:", line, 3) == 0)
		{
			toks = strtok(line + 3, "|");
			id = atol(toks);
			toks = strtok(NULL, "|");
			strcpy(name, toks);

			for (i = 0; i < GDESC_ROWS; i++)
			{
				toks = strtok(NULL, "|\n");

				if (toks == NULL)
				{
					gdesc[i][0] = '\0';
				}
				else
				{
					strcpy(gdesc[i], toks);
				}
			}

#ifdef DEBUG
			printf("Leído: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
			printf("Gdesc:\n");
			for (i = 0; i < GDESC_ROWS; i++)
			{
				printf("[%s]\n", gdesc[i]);
			}
#endif
			space = space_create(id);
			if (space != NULL)
			{
				space_set_name(space, name);

				for (i = 0; i < GDESC_ROWS; i++)
				{
					space_set_gdesc_at(space, gdesc[i], i);
				}

				game_add_space(game, space);
			}
		}
	}

	if (ferror(file))
	{
		status = ERROR;
	}

	fclose(file);
	return status;
}

Status game_add_space(Game *game, Space *space)
{
	int *numSpaces = game_get_n_spaces(game);
	Space **spacePointer = game_get_spaces(game);

	if ((space == NULL) || (*numSpaces >= MAX_SPACES) || (spacePointer == NULL) || numSpaces == NULL)
	{
		return ERROR;
	}

	spacePointer[*numSpaces] = space;
	(*numSpaces)++;

	return OK;
}

Id game_get_space_id_at(Game *game, int position)
{
	int *numSpaces = game_get_n_spaces(game);
	Space **SpacesPointer = game_get_spaces(game);

	if (position < 0 || position >= *(numSpaces) || SpacesPointer == NULL || numSpaces == NULL)
	{
		return NO_ID;
	}

	return space_get_id(SpacesPointer[position]);
}

Status game_load_objects(Game *game, char *filename)
{
	FILE *file = NULL;
	char line[WORD_SIZE] = "";
	char name[WORD_SIZE] = "";
	char desc[WORD_SIZE] = "";
	char *toks = NULL;
	Id id = NO_ID, location = NO_ID, dependency = NO_ID, open = NO_ID;
	int health = 0, mov = -1;
	Bool movable = FALSE;
	Object *object = NULL;

	if (!filename)
	{
		return ERROR;
	}

	file = fopen(filename, "r");
	if (file == NULL)
	{
		return ERROR;
	}

	while (fgets(line, WORD_SIZE, file))
	{
		if (strncmp("#o:", line, 3) == 0)
		{
			toks = strtok(line + 3, "|");
			id = atol(toks);

			toks = strtok(NULL, "|");
			strcpy(name, toks);

			toks = strtok(NULL, "|");
			location = atol(toks);

			toks = strtok(NULL, "|");
			health = atoi(toks);

			toks = strtok(NULL, "|");
			mov = atoi(toks);

			toks = strtok(NULL, "|");
			dependency = atol(toks);

			toks = strtok(NULL, "|");
			open = atoi(toks);

			toks = strtok(NULL, "|\n");
			strcpy(desc, toks);

#ifdef DEBUG
			printf("Leído: %ld|%s|%ld|%d|%d|%ld|%ld\n", id, name, location, health, movable, dependency, open);
#endif
			if (mov == 0)
			{
				movable = FALSE;
			}
			else if (mov == 1)
			{
				movable = TRUE;
			}
			else
			{
				fprintf(stderr, "Error: Invalid value for movable.\n");
				fclose(file);
				return ERROR;
			}

			object = object_create(id);
			if (object != NULL)
			{
				object_set_name(object, name);
				object_set_location(object, location);
				object_set_health(object, health);
				object_set_movable(object, movable);
				object_set_dependency(object, dependency);
				object_set_open(object, open);
				object_set_description(object, desc);

				if (game_add_objects(game, object) == ERROR)
				{
					object_destroy(object);
					fprintf(stderr, "Error while adding object to game.\n");
				}
			}
		}
	}

	return OK;
}

Status game_add_objects(Game *game, Object *object)
{
	int *numObjects = game_get_n_objects(game);
	Object **objectPointer = game_get_objects(game);

	if ((object == NULL) || (*numObjects >= MAX_OBJECTS) || (objectPointer == NULL))
	{
		fprintf(stderr, "Error while adding object to game.\n");
		return ERROR;
	}

	objectPointer[*numObjects] = object;
	(*numObjects)++;

	return OK;
}

Status game_add_link(Game *game, Link *link)
{
	int *n_links = game_get_n_links(game);
	Link **links_p = game_get_links(game);

	if (game == NULL || link == NULL || *n_links == MAX_LINKS || n_links == NULL || links_p == NULL)
	{
		return ERROR;
	}

	links_p[*n_links] = link;
	(*n_links)++;
	return OK;
}

Status game_load_players(Game *game, char *filename)
{
	FILE *f = NULL;
	char line[WORD_SIZE], name[WORD_SIZE], gdesc[PLAYER_GDESC_COLUMS], *toks = NULL;
	int backpack_size, health_points;
	Id id, location;
	Player *player_p = NULL;
	Inventory *inventory_p = NULL;

	if (game == NULL || filename == NULL)
	{
		fprintf(stderr, "Error: Invalid parameters in game_load_players.\n");
		return ERROR;
	}

	f = fopen(filename, "r");
	if (!f)
	{
		fprintf(stderr, "Error: Could not open file %s.\n", filename);
		return ERROR;
	}

	while (fgets(line, WORD_SIZE, f))
	{
		if (strncmp(line, "#p:", 3) == 0)
		{
			toks = strtok(line + 3, "|");
			if (!toks)
			{
				fprintf(stderr, "Error: Missing player ID.\n");
				fclose(f);
				return ERROR;
			}
			id = atol(toks);

			toks = strtok(NULL, "|");
			if (!toks)
			{
				fprintf(stderr, "Error: Missing player name.\n");
				fclose(f);
				return ERROR;
			}
			strcpy(name, toks);

			toks = strtok(NULL, "|");
			if (!toks)
			{
				fprintf(stderr, "Error: Missing player graphic description.\n");
				fclose(f);
				return ERROR;
			}
			strcpy(gdesc, toks);

			toks = strtok(NULL, "|");
			if (!toks)
			{
				fprintf(stderr, "Error: Missing player location.\n");
				fclose(f);
				return ERROR;
			}
			location = atol(toks);

			toks = strtok(NULL, "|");
			if (!toks)
			{
				fprintf(stderr, "Error: Missing player health points.\n");
				fclose(f);
				return ERROR;
			}
			health_points = (int)atol(toks);

			toks = strtok(NULL, "|\n");
			if (!toks)
			{
				fprintf(stderr, "Error: Missing player backpack size.\n");
				fclose(f);
				return ERROR;
			}
			backpack_size = (int)atol(toks);

			player_p = player_create(id);
			if (!player_p)
			{
				fprintf(stderr, "Error: Could not create player.\n");
				fclose(f);
				return ERROR;
			}

			inventory_p = inventory_create(backpack_size);
			if (!inventory_p)
			{
				fprintf(stderr, "Error: Could not create inventory.\n");
				player_destroy(player_p);
				fclose(f);
				return ERROR;
			}

			player_set_name(player_p, name);
			player_set_gdesc(player_p, gdesc);
			player_set_location(player_p, location);
			space_set_discovered(game_get_space(game, location), TRUE);
			player_set_health(player_p, health_points);
			player_set_inventory(player_p, inventory_p);

			if (game_add_player(game, player_p) == ERROR)
			{
				fprintf(stderr, "Error: Could not add player to game.\n");
				player_destroy(player_p);
				fclose(f);
				return ERROR;
			}
		}
	}

	fclose(f);
	return OK;
}

Status game_load_links(Game *game, char *filename)
{
	char line[WORD_SIZE], name[WORD_SIZE], *toks;
	Link *link_p = NULL;
	Id id, orig, dest;
	Direction dir;
	Bool is_open = FALSE;
	FILE *f = NULL;

	if (game == NULL || filename == NULL)
	{
		return ERROR;
	}

	if (!(f = fopen(filename, "r")))
	{
		return ERROR;
	}

	while (fgets(line, WORD_SIZE, f))
	{
		if (strncmp(line, "#l:", 3) == 0)
		{
			toks = strtok(line + 3, "|");
			id = atol(toks);
			toks = strtok(NULL, "|");
			strcpy(name, toks);
			toks = strtok(NULL, "|");
			orig = atol(toks);
			toks = strtok(NULL, "|");
			dest = atol(toks);
			toks = strtok(NULL, "|");
			dir = atol(toks);
			toks = strtok(NULL, "|\n");
			is_open = atol(toks);

			link_p = link_create(id);

			if (link_p != NULL)
			{
				link_set_name(link_p, name);
				link_set_origin(link_p, orig);
				link_set_destination(link_p, dest);
				link_set_direction(link_p, dir);
				link_set_open(link_p, is_open);

				game_add_link(game, link_p);
			}
			else
			{
				return ERROR;
			}
		}
	}

	fclose(f);
	return OK;
}

Status game_load_characters(Game *game, char *filename)
{
	FILE *f = NULL;
	char line[WORD_SIZE], name[WORD_SIZE], gdesc[WORD_SIZE], message[MESSAGE_SIZE], *toks = NULL;
	Id id = 0, position = 0;
	int health = 0;
	Bool friendly = FALSE;
	Character *char_p = NULL;

	if (game == NULL || filename == NULL)
	{
		return ERROR;
	}

	if (!(f = fopen(filename, "r")))
	{
		return ERROR;
	}

	while (fgets(line, WORD_SIZE, f))
	{
		if (strncmp(line, "#c:", 3) == 0)
		{
			toks = strtok(line + 3, "|");
			id = atol(toks);
			toks = strtok(NULL, "|");
			strcpy(name, toks);
			toks = strtok(NULL, "|");
			strcpy(gdesc, toks);
			toks = strtok(NULL, "|");
			position = atol(toks);
			toks = strtok(NULL, "|");
			health = atol(toks);
			toks = strtok(NULL, "|\n");
			friendly = atol(toks);

			char_p = character_create(id);
			if (char_p == NULL)
			{
				fclose(f);
				return ERROR;
			}

			character_set_name(char_p, name);
			character_set_gdesc(char_p, gdesc);
			character_set_health(char_p, health);
			character_set_friendly(char_p, friendly);

			if (friendly == TRUE)
			{
				toks = strtok(NULL, "|\n");
				if (toks != NULL)
				{
					strcpy(message, toks);
					character_set_message(char_p, message);
				}
			}
			else
			{
				character_set_message(char_p, "");
			}

			game_add_character(game, char_p, position);
		}
	}

	fclose(f);
	return OK;
}

Status game_add_player(Game *game, Player *player)
{
	Player **players_array = NULL;
	InterfaceData **interfaces_array = NULL;
	const int n_players = game_get_n_players(game);

	if (game == NULL || player == NULL)
	{
		return ERROR;
	}

	players_array = game_get_players(game);
	interfaces_array = game_get_interfaces(game);
	if (players_array == NULL || n_players < 0)
	{
		return ERROR;
	}

	players_array[n_players] = player;
	interfaces_array[n_players] = game_create_interface();
	game_set_n_players(game, n_players + 1);

	if (interfaces_array[n_players] == NULL)
	{
		return ERROR;
	}

	return OK;
}

Status game_add_character(Game *game, Character *char_p, Id location)
{
	int *n_characters = game_get_n_characters(game);
	Character **characters_p = game_get_character_array(game);
	Space *current_space = NULL;

	if (game == NULL || char_p == NULL || *n_characters == MAX_CHARACTERS || *n_characters < 0 || location < 0)
	{
		return ERROR;
	}

	characters_p[*n_characters] = char_p;
	(*n_characters)++;
	current_space = game_get_space(game, location);

	if (current_space)
	{
		space_add_character(current_space, char_p);
	}

	return OK;
}

Status game_management_save(Game *game, const char *filename)
{
	FILE *file = NULL;
	Player **player_array = NULL;
	Character **character_array = NULL;
	Space **space_array = NULL;
	Object **object_array = NULL;
	Link **link_array = NULL;
	const int n_players = game_get_n_players(game), n_characters = *game_get_n_characters(game);
	const int n_spaces = *game_get_n_spaces(game), n_objects = *game_get_n_objects(game);
	const int n_links = *game_get_n_links(game);
	int i, j;

	if (!(file = fopen(filename, "w")))
	{
		fprintf(stderr, "DEBUG -- Could not open file");
		return ERROR;
	}

	if (n_players <= 0 || !n_characters || !n_spaces || !n_objects || !n_links)
	{
		fprintf(stderr, "DEBUG -- Could not read load number of elements from game");
		return ERROR;
	}

	player_array = game_get_players(game);
	if (player_array == NULL)
	{
		fprintf(stderr, "DEBUG -- Could not load player array");
		return ERROR;
	}

	for (i = 1; i <= n_players; i++)
	{
		fprintf(file, "#p:%d|%s|%s|%ld|%d|%d|\n", i,
				player_get_name(player_array[i - 1]),
				player_get_gdesc(player_array[i - 1]),
				player_get_location(player_array[i - 1]),
				player_get_health(player_array[i - 1]),
				player_get_inventory_size(player_array[i - 1]));
	}

	character_array = game_get_character_array(game);
	if (character_array == NULL)
	{
		fprintf(stderr, "DEBUG -- Could not load character array");
		return ERROR;
	}

	for (i = 0; i < n_characters; i++)
	{
		fprintf(file, "#c:%ld|%s|%s|%ld|%d|%d|%s|\n",
				character_get_id(character_array[i]),
				character_get_name(character_array[i]),
				character_get_gdesc(character_array[i]),
				game_find_character(game, character_get_id(character_array[i])),
				character_get_health(character_array[i]),
				character_get_friendly(character_array[i]),
				character_get_friendly(character_array[i]) ? character_get_message(character_array[i]) : "");
	}

	space_array = game_get_spaces(game);
	if (space_array == NULL)
	{
		fprintf(stderr, "DEBUG -- Could not load space array");
		return ERROR;
	}

	for (i = 0; i < n_spaces; i++)
	{
		fprintf(file, "#s:%ld|%s",
				space_get_id(space_array[i]),
				space_get_name(space_array[i]));

		for (j = 0; j < GDESC_ROWS; j++)
		{
			fprintf(file, "|%s", space_get_gdesc_at(space_array[i], j));
		}
		fprintf(file, "|\n");
	}

	object_array = game_get_objects(game);
	if (object_array == NULL)
	{
		fprintf(stderr, "DEBUG -- Could not load object array");
		return ERROR;
	}

	for (i = 0; i < n_objects; i++)
	{
		fprintf(file, "#o:%ld|%s|%ld|%d|%d|%ld|%ld|\n",
				object_get_id(object_array[i]),
				object_get_name(object_array[i]),
				(object_get_location(object_array[i]) == -1 ? 0 : object_get_location(object_array[i])),
				object_get_health(object_array[i]),
				object_get_movable(object_array[i]),
				object_get_dependency(object_array[i]),
				object_get_open(object_array[i]));
	}

	link_array = game_get_links(game);
	if (link_array == NULL)
	{
		fprintf(stderr, "DEBUG -- Could not load link array");
		return ERROR;
	}

	for (i = 0; i < n_links; i++)
	{
		fprintf(file, "#l:%ld|%s|%ld|%ld|%d|%d|\n",
				link_get_id(link_array[i]),
				link_get_name(link_array[i]),
				link_get_origin(link_array[i]),
				link_get_destination(link_array[i]),
				link_get_direction(link_array[i]),
				link_get_open(link_array[i]));
	}

	fclose(file);
	return OK;
}

Status game_management_load(Game **game, char *filename)
{
	Game *new_game = NULL;

	if (!game || !filename)
	{
		return ERROR;
	}

	if (game_create_from_file(&new_game, filename) == ERROR)
	{
		fprintf(stdout, "Error while loading game from file.\n");
		return ERROR;
	}

	game_destroy(*game);
	*game = new_game;
	return OK;
}