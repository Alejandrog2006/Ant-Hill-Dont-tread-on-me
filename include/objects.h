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

/**
 * @brief Private implementation of object datatype
 */
typedef struct _Object Object;

/**
 * @brief Maximum number of a spaces
 */
#define MAX_SPACES 100

/**
 * @brief Maximum number of  objects
 */
#define MAX_OBJECTS 10

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

/**
 * @brief It gets the name of a object
 * @author Alejandro Gonzalez
 *
 * @param object a pointer to the object
 * @param description a pointer to the new description
 * @return  a string with the name of the object
 */
Status object_set_description(Object* object, char* description);

/**
 * @brief It gets the description of a object
 * @author Alejandro Gonzalez
 *
 * @param object a pointer to the object
 * @return  a string with the name of the object
 */
const char* object_get_description(Object* object);

/**
 * @brief It gets the id of a object by its name
 * @author Alejandro Gonzalez
 *
 * @param objects a pointer to the array of objects
 * @param name a string with the name of the object
 * @return  the id of the object, NO_ID if there was some mistake
 */
Id object_get_id_by_name(Object **objects, const char *name);

/**
 * @brief It sets the health of a object
 * @author Alejandro Gonzalez
 *
 * @param object a pointer to the object
 * @param health the health to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_set_health(Object* object, int health);

/**
 * @brief It gets the health of a object
 * @author Alejandro Gonzalez
 *
 * @param object a pointer to the object
 * @return  the health of the object, NO_ID if there was some mistake
 */
int object_get_health(Object* object);

/**
 * @brief It sets if the object is movable or not
 * @author Alejandro Gonzalez
 * 
 * @param object a pointer to the object
 * @param movable a boolean value to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_set_movable(Object* object, Bool movable);

/**
 * @brief It gets if the object is movable or not
 * @author Alejandro Gonzalez
 *
 * @param object a pointer to the object
 * @return  the health of the object, NO_ID if there was some mistake
 */
Bool object_get_movable(Object* object);

/**
 * @brief It sets the dependency of a object
 * @author Alejandro Gonzalez
 * 
 * @param object a pointer to the object
 * @param dependency the id of the object that is needed to use this one
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_set_dependency(Object* object, Id dependency);

/**
 * @brief It gets the dependency of a object
 * @author Alejandro Gonzalez
 *
 * @param object a pointer to the object
 * @return  the id of the object that is needed to use this one, NO_ID if there was some mistake
 */
Id object_get_dependency(Object* object);

/**
 * @brief It sets the open id of a object
 * @author Alejandro Gonzalez
 * 
 * @param object a pointer to the object
 * @param open the id of the object that is needed to use this one
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_set_open(Object* object, Id open);

/**
 * @brief It gets the open id of a object
 * @author Alejandro Gonzalez
 *
 * @param object a pointer to the object
 * @return  the id of the object that is needed to use this one, NO_ID if there was some mistake
 */
Id object_get_open(Object* object);

#endif
