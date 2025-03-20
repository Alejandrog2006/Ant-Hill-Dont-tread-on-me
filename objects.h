/**
 * 
 * @brief It defines the object module interface
 *
 * @file objects.h
 * @author Andres Falcon
 * @version 1
 * @date 03-02-2025
 * @copyright GNU Public License
 * 
 * 
 */

#ifndef OBJECTS_H
#define OBJECTS_H

#include "types.h"

typedef struct _Object Object;

#define MAX_SPACES 100

/**
 * @brief It creates a new object, allocating memory and initializing its members
 * @author Andres Falcon
 *
 * @param id the identification number for the new object
 * @return a pointer for a new object, initialized
 */
Object* object_create(Id id);

/**
 * @brief It destros an existing object, freeing the allocated memory
 * @author Andres Falcon
 *
 * @param object a pointer to the object that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_destroy(Object* object);

/**
 * @brief It gets the id of a object
 * @author Andres Falcon
 *
 * @param object a pointer to the object
 * @return the id of object
 */
Id object_get_id(Object* object);

/** 
 * @brief It gets the location of a object
 * @author Andres Falcon
 * 
 * @param object a pointer to the object
 * @return Id of the location of the object, NO_ID if there was some mistake
 */
Id object_get_location(Object* object);

/** 
 * @brief It gets the location of a object
 * @author Andres Falcon
 * 
 * @param object a pointer to the object
 * @return Pointer of the location of the object, NO_ID if there was some mistake
 */
Id *object_get_location_pointer(Object* object);

/**
 * @brief It sets the location of a object
 * @author Alejandro Gonzalez
 * 
 * @param object a pointer to the object
 * @param id the id of the location to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_set_location(Object* object, Id id);

/**
 * @brief It sets the name of a object
 * @author Andres Falcon
 *
 * @param object a pointer to the object
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_set_name(Object* object, char* name);

/**
 * @brief It gets the name of a object
 * @author Andres Falcon
 *
 * @param object a pointer to the object
 * @return  a string with the name of the object
 */
const char* object_get_name(Object* object);


#endif
