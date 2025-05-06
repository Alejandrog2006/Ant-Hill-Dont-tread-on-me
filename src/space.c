/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "space.h"
#include "objects.h"
#include "set.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Private implementation of space datatype
 */
struct _Space
{
	Id id;								/*!< Id number of the space, it must be unique */
	char name[WORD_SIZE + 1];			/*!< Name of the space */
	Set *characters;					/*!< Set of the characters in that space*/
	Set *object_locations;				/*!< Set of objects in the space */
	char gdesc[GDESC_ROWS][GDESC_COLS]; /*!< Graphical description of the space */
	Bool discovered;					/*!< Wether the space is discovered or not*/
};

Space *space_create(Id id)
{
	Space *newSpace = NULL;
	int i;

	if (id == NO_ID)
		return NULL;

	newSpace = (Space *)malloc(sizeof(Space));
	if (newSpace == NULL)
	{
		return NULL;
	}

	newSpace->id = id;
	newSpace->name[0] = '\0';
	newSpace->characters = set_create();
	newSpace->discovered = FALSE;

	newSpace->object_locations = set_create();
	if (newSpace->object_locations == NULL)
	{
		free(newSpace);
		return NULL;
	}

	/* Initialize graphical description */
	for (i = 0; i < GDESC_ROWS; i++)
	{
		memset(newSpace->gdesc[i], ' ', GDESC_COLS);
		newSpace->gdesc[i][GDESC_COLS] = '\0';
	}

	return newSpace;
}

Status space_destroy(Space *space)
{
	if (!space)
	{
		return ERROR;
	}

	if (space->object_locations != NULL)
	{
		set_destroy(space->object_locations);
	}

	if (space->characters != NULL)
	{
		set_destroy(space->characters);
	}

	free(space);
	space = NULL;
	return OK;
}

Id space_get_id(Space *space)
{
	if (!space)
	{
		return NO_ID;
	}
	return space->id;
}

Status space_set_name(Space *space, char *name)
{
	if (!space || !name)
	{
		return ERROR;
	}

	if (!strcpy(space->name, name))
	{
		return ERROR;
	}
	return OK;
}

const char *space_get_name(Space *space)
{
	if (!space)
	{
		return NULL;
	}
	return space->name;
}

Status space_set_object(Space *space, Bool value)
{
	if (!space)
	{
		return ERROR;
	}

	if (set_get_count(space->object_locations) > 0)
	{
		value = TRUE;
	}
	else
	{
		value = FALSE;
	}

	return OK;
}

Bool space_get_object(Space *space, Id id)
{
	int i, n_ids;

	if (!space || id == NO_ID)
	{
		return FALSE;
	}

	n_ids = set_get_count(space->object_locations);
	for (i = 0; i < n_ids; i++)
	{
		if (set_get_id_at(space->object_locations, i) == id)
		{
			return TRUE;
		}
	}
	return FALSE;
}

Status space_print(Space *space)
{
	int i, n_ids;

	if (!space)
	{
		return ERROR;
	}

	fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

	n_ids = set_get_count(space->object_locations);
	if (n_ids > 0)
	{
		fprintf(stdout, "---> Objects in the space:\n");
		for (i = 0; i < n_ids; i++)
		{
			fprintf(stdout, "------> Object Id: %ld\n", set_get_id_at(space->object_locations, i));
		}
	}
	else
	{
		fprintf(stdout, "---> No objects in the space.\n");
	}

	fprintf(stdout, "---> Graphical description:\n");
	for (i = 0; i < GDESC_ROWS; i++)
	{
		fprintf(stdout, "     %s\n", space->gdesc[i]);
	}

	return OK;
}

Status space_set_gdesc(Space *space, char gdesc[GDESC_ROWS][GDESC_COLS + 1])
{
	int i;
	if (!space || !gdesc)
	{
		return ERROR;
	}

	for (i = 0; i < GDESC_ROWS; i++)
	{
		strcpy(space->gdesc[i], gdesc[i]);
	}

	return OK;
}

const char **space_get_gdesc(Space *space)
{
	if (!space)
	{
		return NULL;
	}
	return (const char **)space->gdesc;
}
Set *space_get_object_locations(Space *space)
{
	if (!space)
	{
		return NULL;
	}
	return space->object_locations;
}

const char *space_get_gdesc_at(Space *space, int position)
{
	if (!space || position < 0)
	{
		return NULL;
	}

	return space->gdesc[position];
}

Status space_set_gdesc_at(Space *space, char *gdesc_new, int position)
{
	if (!space || !gdesc_new || position < 0)
	{
		return ERROR;
	}

	strcpy(space->gdesc[position], gdesc_new);
	return OK;
}

Bool space_is_discovered(Space *space)
{
	if (space == NULL)
	{
		return FALSE;
	}

	return space->discovered;
}

Status space_set_discovered(Space *space, Bool discovered)
{
	if (!space)
	{
		return ERROR;
	}

	space->discovered = discovered;
	return OK;
}

Status space_add_character(Space *space, Character *character)
{
	Id char_id = NO_ID;

	if (!space || !character)
	{
		return ERROR;
	}

	char_id = character_get_id(character);
	set_add(space->characters, char_id);

	return OK;
}

Status space_del_character(Space *space, Character *character)
{
	Id char_id = NO_ID;

	if (!space || !character)
	{
		return ERROR;
	}

	char_id = character_get_id(character);
	set_del(space->characters, char_id);

	return OK;
}

Set *space_get_characters(Space *space)
{
	if (!space)
	{
		return NULL;
	}

	return space->characters;
}