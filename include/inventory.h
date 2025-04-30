/**
 * @brief It defines the inventory module interface
 * @author Rodrigo Cruz
 *
 * @file inventory.h
 * @version 1.0
 * @date 18-03-2025
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "objects.h"
#include "set.h"

/**
 * @brief Default inventory size for the player
 */
#define BACKPACK_SIZE 3  

/**
 * @brief Private datatype for inventory implementation
 */
typedef struct _Inventory Inventory;

/**
 * @brief Creates an inventory with a maximum capacity of objects
 * @author Rodrigo Cruz
 * 
 * @param max_objs the maximum number of objects the inventory can hold
 * @return a pointer to the `Inventory` structure, or NULL if an error occurs
 */
Inventory* inventory_create(int max_objs);

/**
 * @brief Frees the memory allocated for an inventory
 * @author Rodrigo Cruz
 * 
 * @param inventory a pointer to the inventory to destroy
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_destroy(Inventory* inventory);

/**
 * @brief Adds an object to the inventory
 * @author Rodrigo Cruz
 * 
 * @param inventory a pointer to the inventory
 * @param id_object the ID of the object to add
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_add_object(Inventory* inventory, Id id_object);

/**
 * @brief Deletes an object from the inventory
 * @author Rodrigo Cruz
 * 
 * @param inventory a pointer to the inventory
 * @param id_object the ID of the object to delete
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_del_object(Inventory* inventory, Id id_object);

/**
 * @brief Checks if an object is in the inventory
 * @author Rodrigo Cruz
 * 
 * @param inventory a pointer to the inventory
 * @param id_object the ID of the object to check
 * @return TRUE if the object is in the inventory, FALSE otherwise
 */
Bool inventory_contains_object(Inventory* inventory, Id id_object);

/**
 * @brief Prints the contents of the inventory
 * @author Rodrigo Cruz
 * 
 * @param inventory a pointer to the inventory
 * @return OK, if the print operation was successful or ERROR otherwise
 */
Status inventory_print(Inventory* inventory);

/**
 * @brief Gets the objects in the inventory
 * @author Alejandro Gonzalez
 * 
 * @param inventory a pointer to the inventory
 * @return a pointer to the set of objects in the inventory, or NULL if an error occurs
 */
Set* inventory_get_objects(Inventory* inventory);

/**
 * @brief Gets the number of objects in the inventory
 * @author Alejandro Gonzalez
 * 
 * @param inventory a pointer to the inventory
 * @return the number of objects in the inventory, or -1 if an error occurs
 */
int inventory_get_count(Inventory* inventory);

#endif