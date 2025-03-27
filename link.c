/**
 * @brief It implements the link module interface
 *
 * @file link.c
 * @author Rodrigo Cruz Asensio
 * @version 1.0
 * @date 20-03-2025
 * @copyright GNU Public License
 */

 #include "link.h"

struct _Link{
    Id id;
    char name[WORD_SIZE + 1]; 
    Id origin;
    Id destination;
    Direction direction;
    Bool open;
 };

Link* link_create(Id id){
   Link*newLink = NULL;
   if (id == NO_ID) return NULL; /* Error control */
   
   newLink = (Link*)malloc(sizeof(Link)); /* Memory allocation */
   
   if (newLink == NULL){
   return NULL; /* Error control */
   }
   
   newLink->id = id; /* Initialization of the structure */
   newLink->name[0] = '\0';
   newLink->origin = NO_ID; 
   newLink->destination = NO_ID;
   newLink->direction = NONE;
   newLink->open = TRUE;

   return newLink;
 }

Status link_destroy(Link*link){
   if (!link) return ERROR;
  
   free(link);

   return OK;
 }

Status link_set_name(Link* link, char* name){
   if (!link || !name) return ERROR;

   if (!strcpy( link->name, name)){
      return ERROR;
   }
   
   return OK;

 }

const char* link_get_name(Link* link){
   if (!link){
      return NULL;
   }

   return link->name;
 }

Status link_set_origin(Link*link, Id origin){ 
  if (!link || origin == NO_ID){
    return ERROR;
  }
  
  link->origin = origin;
  return OK;
 }

Id link_get_origin(Link*link){
  if (!link){
    return NO_ID;
  }

  return link->origin; 
 }

Status link_set_destination(Link*link, Id destination){ 
  if (!link || destination == NO_ID){
    return ERROR;
  }
  
  link->destination = destination;
  return OK;
 }

Id link_get_destination(Link*link){
  if (!link){
    return NO_ID;
  }

  return link->destination; 
 }

Status link_set_direction(Link*link, Direction direction){ 
  if (!link || direction == NONE){
    return ERROR;
  }
  
  link->direction = direction;
  return OK;
 }

Direction link_get_direction(Link*link){
  if (!link){
    return NONE;
  }

  return link->direction; 
 }

Status link_set_open(Link*link, Bool open){ 
  if (!link || open == FALSE){
    return ERROR;
  }
  
  link->open = open;
  return OK;
 }

Bool link_get_open(Link*link){
  if (!link){
    return FALSE;
  }

  return link->open; 
 }

void link_print(Link*link){
  if (!link){
    printf("Link ERROR\n");
    return;
  }
   
  printf("Link ID: %d\n", link->id);
  printf("Link name: %s\n", link->name);
  printf("Link origin: %d\n", link->origin);
  printf("Link destination: %d\n", link->destination);
  printf("Link direction: %d\n", link->direction);
  printf("¿Is the Link open?: %s\n", link->open ? "Yes" : "No");

}






































































 