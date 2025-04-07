/**
 * @brief It defines the player module interface
 *
 * @file player.h
 * @author Alejandro Gonzalez
 * @author Izan Robles
 * @date 13-03-2025
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "inventory.h"

/**
 * @brief Maximum number of colums of the graphical description of the player
 */
#define PLAYER_GDESC_COLUMS 3

/**
 * @brief Private implementation of player datatype
 */
typedef struct _Player Player;

/**
 * @brief It creates a new player, allocating memory and initializing its members
 * @author Alejandro Gonzalez
 *
 * @param id the identification number for the new player
 * @return a new player, initialized
 */
Player* player_create(Id id);

/**
 * @brief It destroys a player, freeing the allocated memory
 * @author Alejandro Gonzalez
 *
 * @param player a pointer to the player that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_destroy(Player* player);

/**
 * @brief It gets the id of a player
 * @author Alejandro Gonzalez
 *
 * @param player a pointer to the player
 * @return the id of player
 */
Id player_get_id(Player* player);

/**
 * @brief It sets the name of a player
 * @author Alejandro Gonzalez
 *
 * @param player a pointer to the player
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_name(Player* player, char* name);

/**
 * @brief It gets the name of a player
 * @author Alejandro Gonzalez
 *
 * @param player a pointer to the player
 * @return  a string with the name of the player
 */
const char* player_get_name(Player* player);

/**
 * @brief It adds an object to the player's backpack inventory
 * @author Alejandro Gonzalez
 * 
 * @param player a pointer to the player
 * @param id the id of the object to add
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_add_object(Player* player, Id id);

/**
 * @brief It deletes an object from the player's backpack inventory
 * @author Alejandro Gonzalez
 * 
 * @param player a pointer to the player
 * @param id the id of the object to delete
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_del_object(Player* player, Id id);

/**
 * @brief It checks if an object is in the player's backpack inventory or not
 * @author Alejandro Gonzalez
 * 
 * @param player a pointer to the player
 * @param id the id of the object to check
 * @return TRUE if the object is in the inventory, FALSE otherwise
 */
Bool player_has_object(Player* player, Id id);  

/**
 * @brief It prints the player information
 * @author Alejandro Gonzalez
 *
 * This function shows the id and name of the player, the spaces that surrounds it and whether it has an object or not.
 * @param player a pointer to the player
 * @return OK, if everything goes well or ERROR if there was some mistake 
 */
Status player_print(Player* player);

/**
 * @brief It sets the location of a player
 * @author Alejandro Gonzalez
 * 
 * @param player a pointer to the player
 * 
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Id player_get_location(Player* player);

/**
 * @brief It gets the location of a player
 * @author Alejandro Gonzalez
 * 
 * @param player a pointer to the player
 * 
 * @return the location of the player
 */
Id *player_get_location_pointer(Player* player); 

/**
 * @brief Changes the value of the player's health
 * @author Izan Robles
 * 
 * @param player a pointer to the player
 * @param health the new health value
 * 
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_health(Player* player, int health);

/**
 * @brief Gets the player's health value
 * @author Izan Robles
 * 
 * @param player a pointer to the player
 * 
 * @return the player's health value or -1 if there was an error
 */
int player_get_health(Player* player);

/**
 * @brief Gets the player's backpack inventory
 * @author Alejandro Gonzalez)
 * 
 * @param player a pointer to the player
 * 
 * @return the player's backpack inventory
 */
Inventory* player_get_inventory(Player* player);

/**
 * @brief Gets the player's graphical description
 * @author Daniel Martín Jaén
 * 
 * @param player A pointer to the player struct
 * @return A pointer to the player's graphical description NULL if something went wrong
 */
const char *player_get_gdesc(Player *player);

/**
 * @brief Changes the player's graphical description to a given one
 * @author Daniel Martín Jaén
 * 
 * @param player A pointer to the player struct
 * @param gdesc The new graphical description that's being added to player
 * @return OK if everything went correctly ERROR if something went wrong
 */
Status player_set_gdesc(Player *player, char *gdesc);

/**
 * @brief Changes the location of the player to a new one
 * @author Daniel Martín Jaén
 * 
 * @param player A pointer to the player struct
 * @param location The new location for the player
 * @return OK if everything went corretly ERROR if something went wrong
 */
Status player_set_location(Player *player, Id location);

/**
 * @brief Changes the player's inventory to a new one
 * @author Daniel Martín Jaén
 * 
 * @param player A pointer to the player struct
 * @param inv A pointer to the new inventory
 * @return OK if everything went correctly ERROR if something went wrong
 */
Status player_set_inventory(Player *player, Inventory *inv);

#endif
