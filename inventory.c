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

struct _Inventory {
    Set* objs;
    int max_objs;
};

Inventory *inventory_create() {
    Inventory *inventory = NULL;

    inventory = (Inventory *)malloc(sizeof(Inventory));
    if (!inventory) {
        return NULL;
    }

    inventory->objs = set_create();
    if (!inventory->objs) {
        free(inventory);
        return NULL;
    }

    inventory->max_objs = BACKPACK_SIZE;
    return inventory;
}

void inventory_destroy(Inventory *inventory) {
    if (!inventory) return;

    set_destroy(inventory->objs);
    free(inventory);
}

Status inventory_add_object(Inventory *inventory, Id id_object) {
    if (!inventory || id_object == NO_ID) {
        return ERROR;
    }
    if (set_get_count(inventory->objs) >= inventory->max_objs) {
        return ERROR;
    }

    return set_add(inventory->objs, id_object);
}

Status inventory_del_object(Inventory *inventory, Id id_object) {
    if (!inventory || id_object == NO_ID) {
        return ERROR;
    }

    return set_del(inventory->objs, id_object);
}

Bool inventory_contains_object(Inventory *inventory, Id id_object) {
    int i;

    if (!inventory || id_object == NO_ID) {
        return FALSE;
    }

    for (i = 0; i < set_get_count(inventory->objs); i++) {
        if (set_get_id_at(inventory->objs, i) == id_object) {
            return TRUE;
        }
    }

    return FALSE;
}

Status inventory_print(Inventory *inventory) {
    if (!inventory) {
        printf("Inventory: NULL\n");
        return ERROR;
    }

    printf("Inventory (max %d objects): \n", inventory->max_objs);
    if (set_print(inventory->objs) == ERROR) {
        return ERROR;
    }
    return OK;
}