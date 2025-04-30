/**
 *
 * @brief Implementation of object module
 *
 * @file objects.c
 * @author Andres Falcon
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "objects.h"
#include "types.h"

/**
 * @brief Private implementation of object datatype
 */
struct _Object
{
	Id id;							 /*!< Id number of the object, it must be unique */
	char name[WORD_SIZE + 1];		 /*!< Name of the object */
	Id location;					 /*!< Id number of the space the object resides in */
	char description[WORD_SIZE + 1]; /*!< Description of the object */
};

Object *object_create(Id id)
{
	Object *newObject = NULL;

	newObject = (Object *)malloc(sizeof(Object));
	if (newObject == NULL)
	{
		return NULL;
	}

	newObject->id = id;
	newObject->location = NO_ID;
	strcpy(newObject->name, "");
	strcpy(newObject->description, "");

	return newObject;
}

Status object_destroy(Object *object)
{
	if (!object)
	{
		return ERROR;
	}

	free(object);
	object = NULL;
	return OK;
}

Id object_get_id(Object *object)
{
	if (!object)
	{
		return NO_ID;
	}
	return object->id;
}

Id object_get_location(Object *object)
{
	if (!object)
	{
		return NO_ID;
	}
	return object->location;
}

Id *object_get_location_pointer(Object *object)
{
	if (!object)
	{
		return NULL;
	}
	return &(object->location);
}

Status object_set_location(Object *object, Id id)
{
	if (!object)
	{
		return ERROR;
	}
	object->location = id;
	return OK;
}

Status object_set_name(Object *object, char *name)
{
	if ((object) == NULL || !name)
	{
		return ERROR;
	}

	if (!strcpy(object->name, name))
	{
		return ERROR;
	}
	return OK;
}

const char *object_get_name(Object *object)
{
	if (object == NULL)
	{
		return NULL;
	}
	return object->name;
}

Status object_set_description(Object *object, char *description)
{
	if ((object) == NULL || !description)
	{
		return ERROR;
	}

	if (!strcpy(object->description, description))
	{
		return ERROR;
	}
	return OK;
}

const char *object_get_description(Object *object)
{
	if (object == NULL)
	{
		return NULL;
	}
	return object->description;
}

Id object_get_id_by_name(Object **objects, const char *name)
{
	int i;

	if (!objects || !name)
	{
		return NO_ID;
	}

	for (i = 0; i < MAX_OBJECTS; i++)
	{
		if (objects[i] && strcmp(object_get_name(objects[i]), name) == 0)
		{
			return object_get_id(objects[i]);
		}
	}

	return NO_ID;
}
