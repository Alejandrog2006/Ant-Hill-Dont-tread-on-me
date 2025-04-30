/**
 * @brief It implements the player module
 *
 * @file player.c
 * @author Alejandro Gonzalez
 * @author Izan Robles
 * @date 13-03-2025
 * @copyright GNU Public License
 */

#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Private implementation of player
 */
struct _Player
{
	Id id;									/*!< Player's ID*/
	char name[WORD_SIZE + 1];				/*!< Player's name*/
	Id location;							/*!< Player's location*/
	Inventory *backpack;					/*!< Player's objects*/
	int player_health;						/*!< Player's health*/
	char gdesc_player[PLAYER_GDESC_COLUMS]; /*!< Player's graphical description*/
};

Player *player_create(Id id)
{
	Player *newPlayer = NULL;

	newPlayer = (Player *)malloc(sizeof(Player));
	if (newPlayer == NULL)
	{
		return NULL;
	}

	newPlayer->id = id;
	newPlayer->name[0] = '\0';
	newPlayer->location = NO_ID;
	newPlayer->backpack = NULL;
	newPlayer->player_health = -1;
	newPlayer->gdesc_player[0] = '\0';

	return newPlayer;
}

Status player_destroy(Player *player)
{
	if (!player)
	{
		return ERROR;
	}

	inventory_destroy(player->backpack);
	free(player);
	player = NULL;
	return OK;
}

Id player_get_id(Player *player)
{
	if (!player)
	{
		return NO_ID;
	}
	return player->id;
}

Status player_set_name(Player *player, char *name)
{
	if ((player) == NULL || !(name))
	{
		return ERROR;
	}

	if (!strcpy(player->name, name))
	{
		return ERROR;
	}
	return OK;
}

const char *player_get_name(Player *player)
{
	if ((player) == NULL)
	{
		return NULL;
	}
	return player->name;
}

Status player_add_object(Player *player, Id id)
{
	if ((player) == NULL || id == NO_ID)
	{
		return ERROR;
	}

	return inventory_add_object(player->backpack, id);
}
Status player_del_object(Player *player, Id id)
{
	if ((player) == NULL || id == NO_ID)
	{
		return ERROR;
	}

	return inventory_del_object(player->backpack, id);
}

Bool player_has_object(Player *player, Id id)
{
	if ((player) == NULL || id == NO_ID)
	{
		return FALSE;
	}
	return inventory_contains_object(player->backpack, id);
}

Status player_print(Player *player)
{
	if ((player) == NULL)
	{
		return ERROR;
	}

	fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->id, player->name);

	if (inventory_print(player->backpack) == ERROR)
	{
		return ERROR;
	}

	if (player->location != NO_ID)
	{
		fprintf(stdout, "Location: %ld\n", player->location);
	}
	else
	{
		fprintf(stdout, "Location: No location\n");
	}

	if (player->player_health > 0)
	{
		fprintf(stdout, "Health: %d\n", player->player_health);
	}
	else
	{
		fprintf(stdout, "Health: No health\n");
	}

	return OK;
}

Id player_get_location(Player *player)
{
	if (!player)
	{
		return NO_ID;
	}
	return player->location;
}

Id *player_get_location_pointer(Player *player)
{
	if (!player)
	{
		return NULL;
	}
	return &(player->location);
}

Status player_set_health(Player *player, int health)
{
	if (!player || health < 0)
	{
		return ERROR;
	}
	player->player_health = health;

	return OK;
}

int player_get_health(Player *player)
{
	if (!player || player->player_health < 0)
	{
		return -1;
	}

	return player->player_health;
}

Inventory *player_get_inventory(Player *player)
{
	if (!player)
	{
		return NULL;
	}
	return player->backpack;
}

const char *player_get_gdesc(Player *player)
{
	if (player == NULL)
	{
		return NULL;
	}

	return player->gdesc_player;
}

Status player_set_gdesc(Player *player, char *gdesc)
{
	if (player == NULL || gdesc == NULL)
	{
		return ERROR;
	}

	while (strlen(gdesc) < 3)
	{
		strcat(gdesc, " ");
	}

	strcpy(player->gdesc_player, gdesc);
	return OK;
}

Status player_set_location(Player *player, Id location)
{
	if (player == NULL || location == NO_ID)
	{
		return ERROR;
	}

	player->location = location;
	return OK;
}

Status player_set_inventory(Player *player, Inventory *inv)
{
	if (player == NULL || inv == NULL)
	{
		return ERROR;
	}

	player->backpack = inv;
	return OK;
}