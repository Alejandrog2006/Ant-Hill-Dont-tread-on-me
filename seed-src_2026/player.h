/**
 * @brief It defines the player module interface
 *
 * @file player.h
 * @author Rodrigo Cruz Asensio
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

typedef struct _Player Player;

/**
 * @brief It creates a new player, allocating memory and initializing its members
 * @author Rodrigo Cruz Asensio
 *
 * @param id the identification number for the new player
 * @return a new player, initialized
 */
Player* player_create(Id id);

/**
 * @brief It destroys a player, freeing the allocated memory
 * @author Rodrigo Cruz Asensio
 *
 * @param player a pointer to the player that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_destroy(Player* player);

/**
 * @brief It gets the id of a player
 * @author Rodrigo Cruz Asensio
 *
 * @param player a pointer to the player
 * @return the id of the player
 */
Id player_get_id(Player* player);

/**
 * @brief It sets the name of a player
 * @author Rodrigo Cruz Asensio
 *
 * @param player a pointer to the player
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_name(Player* player, char* name);

/**
 * @brief It gets the name of a player
 * @author Rodrigo Cruz Asensio
 *
 * @param player a pointer to the player
 * @return  a string with the name of the player
 */
const char* player_get_name(Player* player);

/**
 * @brief It sets the location id of a player
 * @author Rodrigo Cruz Asensio
 *
 * @param player a pointer to the player
 * @param location an id with the location id
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_location_id(Player* player, Id location);

/**
 * @brief It gets the id of the space where the player is located
 * @author Rodrigo Cruz Asensio
 *
 * @param player a pointer to the player
 * @return the id of player
 */
Id player_get_location_id(Player* player);

/**
 * @brief It sets the object id of the object that the player is carrying
 * @author Rodrigo Cruz Asensio
 *
 * @param player a pointer to the player
 * @param object an id with the object id
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_object_id(Player* player, Id object);

/**
 * @brief It gets the id of the object that the player is carrying
 * @author Rodrigo Cruz Asensio
 *
 * @param player a pointer to the player
 * @return the id of player
 */
Id player_get_object_id(Player* player);

/**
 * @brief It prints the player information
 * @author Rodrigo Cruz Asensio
 *
 * This fucntion shows the id and name of the player, the space where it is located and whether or not the player has an object.
 * @param player a pointer to the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_print(Player* player);

#endif
