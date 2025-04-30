/**
 * @brief It defines the link module interface
 *
 * @file link_l.h
 * @author Rodrigo Cruz
 * @version 1.0
 * @date 20-03-2025
 */

#ifndef LINK_L_H
#define LINK_L_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "space.h"

/**
 * @brief Private implementation of link datatype
 */
typedef struct _Link Link;

/**
 * @brief Creates a new link with the given identifier.
 * 
 * @author Rodrigo Cruz
 * @param id The identifier for the new link.
 * @return A pointer to the newly created link, or NULL if the creation failed.
 */
Link* link_create(Id id);

/**
 * @brief Destroys a link, freeing its allocated memory.
 * 
 * @author Rodrigo Cruz
 * @param link A pointer to the link to be destroyed.
 * @return Status indicating the success or failure of the operation.
 */
Status link_destroy(Link* link);

/**
 * @brief Sets the name of the link.
 * 
 * @author Rodrigo Cruz
 * @param link A pointer to the link.
 * @param name The new name for the link.
 * @return Status indicating the success or failure of the operation.
 */
Status link_set_name(Link* link, char* name);

/**
 * @brief Gets the name of the link.
 * 
 * @author Rodrigo Cruz
 * @param link A pointer to the link.
 * @return The name of the link, or NULL if the link is NULL.
 */
const char* link_get_name(Link* link);

/**
 * @brief Sets the origin of the link.
 * 
 * @author Rodrigo Cruz
 * @param link A pointer to the link.
 * @param origin The ID of the origin of the Link.
 * @return 
 * OK if done correctly
 * ERROR otherwise
 */
Status link_set_origin(Link* link, Id origin);

/**
 * @brief Gets the origin of the link.
 * 
 * @author Rodrigo Cruz
 * @param link A pointer to the link.
 * @return 
 * The origin of the link
 * NO_ID if the link is NULL.
 */
Id link_get_origin(Link* link);

/**
 * @brief Sets the destination of the link.
 * 
 * @author Rodrigo Cruz
 * @param link A pointer to the link.
 * @param destination The ID of the destination for the link.
 * @return 
 * OK if done correctly
 * ERROR otherwise
 */
Status link_set_destination(Link* link, Id destination);

/**
 * @brief Gets the destination for the link.
 * 
 * @author Rodrigo Cruz
 * @param link A pointer to the link.
 * @return 
 * The destination for the link
 * NO_ID if the link is NULL.
 */
Id link_get_destination(Link* link);

/**
 * @brief Sets the direction of the link.
 * 
 * @author Rodrigo Cruz
 * @param link A pointer to the link.
 * @param direction The direction of the link.
 * @return 
 * OK if done correctly
 * ERROR otherwise
 */
Status link_set_direction(Link* link, Direction direction);

/**
 * @brief Gets the direction of the link.
 * 
 * @author Rodrigo Cruz
 * @param link A pointer to the link.
 * @return 
 * The direction of the link
 * NONE if the link is NULL.
 */
Direction link_get_direction(Link* link);

/**
 * @brief Sets whether a link is open or not.
 * 
 * @author Rodrigo Cruz
 * @param link A pointer to the link.
 * @param open A boolean that says whether the link is open or not.
 * @return 
 * OK if is open
 * ERROR otherwise
 */
Status link_set_open(Link* link, Bool open);

/**
 * @brief Gets whether a link is open or not.
 * 
 * @author Rodrigo Cruz
 * @param link A pointer to the link.
 * @return 
 * TRUE if the link is open
 * FALSE otherwise.
 */
Bool link_get_open(Link* link);

/**
 * @brief Prints the contents of the link for debugging purposes.
 * 
 * @author Rodrigo Cruz
 * @param link A pointer to the link that we want to print.
 */
void link_print(Link* link);

#endif
