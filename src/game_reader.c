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
    char *toks = NULL;
    Id id = NO_ID, location = NO_ID, dependency = NO_ID, open = NO_ID;
    int health = 0, mov = -1;
    Bool movable = FALSE;
    Object *object = NULL;
    Status status = OK;

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

            toks = strtok(NULL, "|\n");
            open = atoi(toks); 

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

                if (game_add_objects(game, object) == ERROR)
                {
                    object_destroy(object);
                    fprintf(stderr, "Error while adding object to game.\n");
                }
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
			character_set_location(char_p, position);
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

			game_add_character(game, char_p);
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

Status game_add_character(Game *game, Character *char_p)
{
	int *n_characters = game_get_n_characters(game);
	Character **characters_p = game_get_character_array(game);

	if (game == NULL || char_p == NULL || *n_characters == MAX_CHARACTERS || *n_characters < 0)
	{
		return ERROR;
	}

	characters_p[*n_characters] = char_p;
	(*n_characters)++;
	return OK;
}