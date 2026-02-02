/**
 * @brief It implements the player module
 *
 * @file player.c
 * @author Rodrigo Cruz Asensio
 * @version 0
 * @date 27-01-2026
 * @copyright GNU Public License
 */

#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Player
 * 
 * This struct stores all the information of a player
 */
struct _Player {
   Id id;                     /*!< Id of the player */       
   char name[WORD_SIZE + 1];  /*!< Name of the player */
   Id location;               /*!< Id of the space where the player is located */
   Id object;                 /*!< Id of the object that the player is carrying */
};

/** player_create allocates memory for a new player
 *  and initializes its members
 */
Player* player_create(Id id){
   Player* newPlayer = NULL;

   /* Error control */
   if(id == NO_ID) return NULL;

   newPlayer = (Player*)calloc(1,sizeof(Player));
   if(newPlayer == NULL){
       return NULL;
   } 

   /* Initialization of a player */
   newPlayer->id = id;
   newPlayer->name[0] = '\0';
   newPlayer->location = NO_ID;
   newPlayer->object = NO_ID;
 
   return newPlayer;
}

Status player_destroy(Player* player){
   if(!player) return ERROR;

   free(player);
   return OK;
}

Id player_get_id(Player* player){
    if (!player) return NO_ID;

    return player->id;
}

Status player_set_name(Player* player, char* name){
    if(!player || !name) return ERROR;

    if(!strcpy(player->name, name)){
        return ERROR;
    }

    return OK;
}

const char* player_get_name(Player* player){
    if(!player) return NULL;

    return player->name;
}

Status player_set_location_id(Player*player, Id location){
    if(player == NULL || location == NO_ID){
        return ERROR;
    }

    player->location = location;
    return OK;
}

Id player_get_location_id(Player* player){
    if(!player) return NO_ID;

    return player->location;
}

Status player_set_object_id(Player*player, Id object){
    if(player == NULL || object == NO_ID){
        return ERROR;
    }

    player->object = object;
    return OK;
}

Id player_get_object_id(Player* player){
    if(!player) return NO_ID;

    return player->object;
}

Status player_print(Player* player){
    Id idaux = NO_ID;

    /* Error Control */
    if(!player){
        return ERROR;
    }

    /* 1. Print the id and the name of the player */
    fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->id, player->name);

    /* 2. Print the rest of the data */
    idaux = player_get_location_id(player);
    if(idaux != NO_ID){
        fprintf(stdout, "---> The player is in the space with the id: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> The player isn't located in a space");
    }
    idaux = player_get_object_id(player);
    if(idaux != NO_ID){
        fprintf(stdout, "---> The player has an object with the id: %ld.\n", idaux);
    } else {
        fprintf(stdout, "---> The player doesn't have an object");
    }

    return OK;

}