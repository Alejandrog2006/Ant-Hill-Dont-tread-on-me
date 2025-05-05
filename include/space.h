/**
 * @brief It defines the space module interface
 *
 * @file space.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

/**
 * @brief Number of rows in a space
 */
#define GDESC_ROWS 5

/**
 * @brief Number of columns in a space
 */
#define GDESC_COLS 20

#include "types.h"
#include "objects.h"
#include "set.h"
#include "character.h"

/**
 * @brief Private implementation of space datatype
 */
typedef struct _Space Space;

/**
 * @brief It creates a new space, allocating memory and initializing its members
 * @author Profesores PPROG
 *
 * @param id the identification number for the new space
 * @return a new space, initialized
 */
Space* space_create(Id id);

/**
 * @brief It destroys a space, freeing the allocated memory
 * @author Profesores PPROG
 *
 * @param space a pointer to the space that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_destroy(Space* space);

/**
 * @brief It gets the id of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id of space
 */
Id space_get_id(Space* space);

/**
 * @brief It sets the name of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_name(Space* space, char* name);

/**
 * @brief It gets the name of a space
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return  a string with the name of the space
 */
const char* space_get_name(Space* space);

/**
 * @brief It sets the id of the space located at the north
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the north
 * @return OK, if everything goes well or ERROR if there was some mistake
 */

Status space_set_north(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the north
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the north
 */
Id space_get_north(Space* space);

/**
 * @brief It sets the id of the space located at the south
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the south
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_south(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the south
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the south
 */
Id space_get_south(Space* space);

/**
 * @brief It sets the id of the space located at the east
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the east
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_east(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the east
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the east
 */
Id space_get_east(Space* space);

/**
 * @brief It sets the id of the space located at the west
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id the id number of the space located at the west
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_west(Space* space, Id id);

/**
 * @brief It gets the id of the space located at the west
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @return the id number of the space located at the west
 */
Id space_get_west(Space* space);

/**
 * @brief It sets whether the space has an object or not
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param value a boolean, specifying if in the space there is an object (TRUE) or not (FALSE)
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_object(Space* space, Bool value);

/**
 * @brief It gets whether the space has an object or not
 * @author Profesores PPROG
 *
 * @param space a pointer to the space
 * @param id id of the object to be looked for
 * @return a boolean, specifying if in the space there is an object (TRUE) or not (FALSE)
 */
Bool space_get_object(Space* space, Id id);

/**
 * @brief It prints the space information
 * @author Profesores PPROG
 *
 * This fucntion shows the id and name of the space, the spaces that surrounds it and wheter it has an object or not.
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_print(Space* space);

/**
 * @brief Sets the graphical description of a space
 * @author Izan Robles
 *
 * @param space A pointer to the space
 * @param gdesc Array of strings containing the graphical description
 * @return OK if successful, ERROR otherwise
 */
Status space_set_gdesc(Space *space, char gdesc[GDESC_ROWS][GDESC_COLS + 1]);

/**
 * @brief Gets the graphical description of a space
 * @author Izan Robles
 *
 * @param space A pointer to the space
 * @return Pointer to the graphical description array
 */
const char **space_get_gdesc(Space *space);

/**
 * @brief Gets the object locations in a space
 * @author Alejandro Gonzalez
 * 
 * @param space A pointer to the space
 * @return A pointer to the set of object locations
 */
Set *space_get_object_locations(Space *space);

/**
 * @brief It returns a part of the graphic description of a space
 * @author Daniel Martín Jaén
 * 
 * @param space The space with the gdesc array
 * @param position The position of the partial graphic description in the gdesc array
 * @return The part of the graphic description stored in the given position
 */
const char *space_get_gdesc_at(Space *space, int position);

/**
 * @brief Changes a part of the full graphic description of a space
 * @author Daniel Martín Jaén
 * 
 * @param space The space with the gdesc array
 * @param gdesc_new The new partial graphic description
 * @param position The position of the gdesc array that's being changed
 * @return
 *  ERROR if something went wrong
 *  OK if everything went well
 */
Status space_set_gdesc_at(Space *space, char *gdesc_new, int position);

/**
 * @brief Returns the discovered value of a given space
 * @author Alejandro Gonzalez
 * 
 * @param space The pointer to the given space
 * @return TRUE if the space is discovered, FALSE otherwise
 */
Bool space_is_discovered(Space *space);

/**
 * @brief Sets a new value to the discovered field in a given space
 * @author Alejandro Gonzalez
 * 
 * @param space The pointer to the space that's being changed
 * @param discovered The new value of the discovered field
 * @return 
 *  OK if everything went correctly
 *  ERROR otherwise
 */
Status space_set_discovered(Space *space, Bool discovered);

/**
 * @brief Gets the characters set of a given space
 * @author Daniel Martín Jaén
 * 
 * @param space A pointer to the space with the set
 * @return NULL if something went wrong, a pointer to the set otherwise
 */
Set *space_get_characters(Space *space);

/**
 * @brief Removes a character in a given space
 * @author Daniel Martín Jaén
 * 
 * @param space A pointer to the space with the character
 * @param character A pointer to the character that's being removed
 * @return ERROR if something went wrong, OK otherwise
 */
Status space_del_character(Space *space, Character *character);

/**
 * @brief Adds a character to a given space
 * @author Daniel Martín Jaén
 * 
 * @param space A pointer to the space where the character is being added
 * @param character A pointer to the character that's being added
 * @return ERROR if something went wrong, OK otherwise
 */
Status space_add_character(Space *space, Character *character);

#endif
