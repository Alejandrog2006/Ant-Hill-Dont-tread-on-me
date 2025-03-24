/**
 * @brief It defines the inventory module interface
 *
 * @file inventory.h
 * @author Rodrigo Cruz Asensio
 * @version 1.0
 * @date 18-03-2025
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#define BACKPACK_SIZE 3  /* Default maximum backpack size */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "objects.h"
#include "set.h"

typedef struct _Inventory Inventory;

/**
 * @brief Creates an inventory with a maximum capacity of objects.
 * @author Rodrigo Cruz Asensio
 * 
 * @return 
 * Pointer to the `Inventory` structure
 * or NULL if an error occurs.
 */
Inventory *inventory_create();

/**
 * @brief Frees the memory allocated for an inventory.
 * @author Rodrigo Cruz Asensio
 * @param inventory Destroy the inventory.
 */
Status inventory_destroy(Inventory*inventory);

/**
 * @brief Adds an object to the inventory.
 * @author Rodrigo Cruz Asensio
 * @param inventory Pointer to the inventory.
 * @param id_object ID of the object to be added.
 * @return 
 * OK if successfully added
 * ERROR otherwise.
 */
Status inventory_add_object(Inventory*inventory, Id id_object);

/**
 * @brief Deletes an object from the inventory.
 * @author Rodrigo Cruz Asensio
 * @param inventory Pointer to the inventory.
 * @param id_object ID of the object to be deleted.
 * @return 
 * OK if successfully deleted
 * ERROR otherwise.
 */
Status inventory_del_object(Inventory*inventory, Id id_object);

/**
 * @brief Checks if an object is in the inventory.
 * @author Rodrigo Cruz Asensio
 * @param inventory Pointer to the inventory.
 * @param id_object ID of the object to check.
 * @return 
 * TRUE if the object is in the inventory
 * FALSE otherwise.
 */
Bool inventory_contains_object(Inventory*inventory, Id id_object);

/**
 * @brief Prints the contents of the inventory.
 * @author Rodrigo Cruz Asensio
 * @param inventory Pointer to the inventory.
 * @return 
 * OK if the print operation was successful
 * ERROR otherwise.
 */
Status inventory_print(Inventory*inventory);

#endif