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

struct _Player {
  Id id; /*Player's id*/
  char name[WORD_SIZE + 1]; /*Player's name*/
  Id location; /*Player's location*/
  Bool object; /*Player's object*/
  int player_health; /*Player's health*/
};


Player* player_create(Id id) {
  Player* newPlayer = NULL;


  newPlayer = (Player*)malloc(sizeof(Player));
  if (newPlayer == NULL) {
    return NULL;
  }

  newPlayer->id = id;
  newPlayer->name[0] = '\0';
  newPlayer->location = NO_ID;
  newPlayer->object = FALSE;
  newPlayer->player_health = 100;

  return newPlayer;
}

Status player_destroy(Player *player) {
  if (!player) {
    return ERROR;
  }

  free(player);
  player = NULL;
  return OK;
}

Id player_get_id(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->id;
}

Status player_set_name(Player* player, char* name) {
  if ((player) == NULL || !(name)) {
    return ERROR;
  }

  if (!strcpy(player->name, name)) {
    return ERROR;
  }
  return OK;
}

const char* player_get_name(Player* player) {
  if ((player) == NULL) {
    return NULL;
  }
  return player->name;
}

Status player_set_object(Player* player, Bool value) {
  if ((player) == NULL) {
    return ERROR;
  }
  player->object = value;
  return OK;
}

Bool player_get_object(Player* player) {
  if ((player) == NULL) {
    return FALSE;
  }
  
  return player->object;  
  /*return TRUE;*/
}

Status player_print(Player* player) {
  if ((player) == NULL) {
    return ERROR;
  }

  fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->id, player->name);

  if (player_get_object(player)) {
    fprintf(stdout, "---> Object in the space.\n");
  } else {
    fprintf(stdout, "---> No object in the space.\n");
  }

  return OK;
}

Id player_get_location(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->location;
}

Id *player_get_location_pointer(Player* player) {
  if (!player) {
    return NULL;
  }
  return &(player->location);
}

Status player_set_health(Player* player, int health) {
  if (!player || health < 0) {
    return ERROR;
  }
  player->player_health = health;
  
  return OK;
}

int player_get_health(Player* player) {
  if (!player || player->player_health < 0) {
    return -1;
  }

  return player->player_health;
}
