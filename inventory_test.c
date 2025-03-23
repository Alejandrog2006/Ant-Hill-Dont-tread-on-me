/** 
 * @brief It tests inventory module
 * 
 * @file inventory_test.c
 * @author Rodrigo Cruz Asensio
 * @version 1.0 
 * @date 18-03-2025
 * @copyright GNU Public License
 */

#include "inventory.h"

void test_inventory() {
    Inventory *inventory = inventory_create(3);
    assert(inventory != NULL);

    assert(inventory_add_object(inventory, 1) == OK);
    assert(inventory_add_object(inventory, 2) == OK);
    assert(inventory_has_object(inventory, 1) == TRUE);
    
    assert(inventory_remove_object(inventory, 1) == OK);
    assert(inventory_has_object(inventory, 1) == FALSE);

    inventory_destroy(inventory);
}
