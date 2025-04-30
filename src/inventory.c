/**
 * @brief It implements the inventory module
 *
 * @file inventory.c
 * @author Rodrigo Cruz Asensio
 * @version 1.0
 * @date 18-03-2025
 * @copyright GNU Public License
 */

#include "inventory.h"

/**
 * @brief Private implementation of inventory datatype
 */
struct _Inventory
{
	Set *objs;	  /**< Set of objects in the inventory */
	int max_objs; /**< Maximum number of objects in the inventory */
};

Inventory *inventory_create(int max_objs)
{
	Inventory *inventory = NULL;

	inventory = (Inventory *)malloc(sizeof(Inventory));
	if (!inventory)
	{
		return NULL;
	}

	inventory->objs = set_create();
	if (!inventory->objs)
	{
		free(inventory);
		return NULL;
	}

	inventory->max_objs = max_objs;
	return inventory;
}

Status inventory_destroy(Inventory *inventory)
{
	if (!inventory)
	{
		return ERROR;
	}

	set_destroy(inventory->objs);
	free(inventory);
	return OK;
}

Status inventory_add_object(Inventory *inventory, Id id_object)
{
	if (!inventory || id_object == NO_ID)
	{
		return ERROR;
	}
	if (set_get_count(inventory->objs) >= inventory->max_objs)
	{
		return ERROR;
	}

	return set_add(inventory->objs, id_object);
}

Status inventory_del_object(Inventory *inventory, Id id_object)
{
	if (!inventory || id_object == NO_ID)
	{
		return ERROR;
	}

	return set_del(inventory->objs, id_object);
}

Bool inventory_contains_object(Inventory *inventory, Id id_object)
{
	int i;

	if (!inventory || id_object == NO_ID)
	{
		return FALSE;
	}

	for (i = 0; i < set_get_count(inventory->objs); i++)
	{
		if (set_get_id_at(inventory->objs, i) == id_object)
		{
			return TRUE;
		}
	}

	return FALSE;
}

Status inventory_print(Inventory *inventory)
{
	if (!inventory)
	{
		printf("Inventory: NULL\n");
		return ERROR;
	}

	if (set_get_count(inventory->objs) == 0)
	{
		printf("The inventory is empty\n");
	}
	return OK;

	printf("Inventory has %d objects (max %d objects): \n", set_get_count(inventory->objs), inventory->max_objs);
	if (set_print(inventory->objs) == ERROR)
	{
		return ERROR;
	}
}

Set *inventory_get_objects(Inventory *inventory)
{
	if (!inventory)
	{
		return NULL;
	}

	return inventory->objs;
}

int inventory_get_count(Inventory *inventory)
{
	if (!inventory)
	{
		return -1;
	}

	return set_get_count(inventory->objs);
}