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
     Set* objs;     /* Id group using the Set module */
     int max_objs;  /* Max number of objects inside the backpack */
 };
 
 Inventory *inventory_create(int max_objs) {
     Inventory*inventory = NULL;     
    
     if (max_objs <= 0) return NULL;   /* Deleting backpacks with under 0 space */
     
     inventory = (Inventory*)malloc(sizeof(Inventory));
     if (!inventory) return NULL;
     
     inventory->objs = set_create();
     if (!inventory->objs) {
         free(inventory);
         return NULL;
     }
 
     inventory->max_objs = max_objs;
     return inventory;
 }
 
 void inventory_destroy(Inventory* inventory) {
     if (inventory == NULL) return;
 
     set_destroy(inventory->objs);
     free(inventory);
 }
 
 Status inventory_add_object(Inventory* inventory, Id id_object) {
     if (!inventory || id_object == NO_ID) return ERROR;    /* Check if the inventory and the object exist */
     if (set_get_count(inventory->objs) >= inventory->max_objs) return ERROR;   /* Check to not have reached the limit (max_objs) */
 
     return set_add(inventory->objs, id_object);  /* It's possible because set_add is declared with Status */
 }
 
 Status inventory_del_object(Inventory* inventory, Id id_object) {
     if (!inventory || id_object == NO_ID) return ERROR;     /* Check if the inventory and the object exist */
     
     return set_del(inventory->objs, id_object);
 }
 
 Bool inventory_contains_object(Inventory* inventory, Id id_object) {
     if (!inventory || id_object == NO_ID) return FALSE;     /* Check if the inventory and the object exist */
     
     return set_contains(inventory->objs, id_object);
 }
 
 Status inventory_print(Inventory* inventory) {
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