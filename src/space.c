/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "space.h"
#include "objects.h"
#include "set.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Space {
  Id id;                    /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the space */
  Id north;                 /*!< Id of the space at the north */
  Id south;                 /*!< Id of the space at the south */
  Id east;                  /*!< Id of the space at the east */
  Id west;                  /*!< Id of the space at the west */
  Id character;             /*!< Id of the character in the space */        
  Set *object_locations;     /*!< Set of objects in the space */ 
  char gdesc[GDESC_ROWS][GDESC_COLS]; /*!< Graphical description of the space */
};

Space* space_create(Id id) {
  Space* newSpace = NULL;
  int i;

  if (id == NO_ID) return NULL;

  newSpace = (Space*)malloc(sizeof(Space));
  if (newSpace == NULL) {
    return NULL;
  }

  newSpace->id = id;
  newSpace->name[0] = '\0';
  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  newSpace->character = NO_ID;

  newSpace->object_locations = set_create();
  if (newSpace->object_locations == NULL) {
    free(newSpace);
    return NULL;
  }

  /* Initialize graphical description */
  for (i = 0; i < GDESC_ROWS; i++) {
    memset(newSpace->gdesc[i], ' ', GDESC_COLS);
    newSpace->gdesc[i][GDESC_COLS] = '\0';
  }

  return newSpace;
}

Status space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }

  if (space->object_locations != NULL) {   
    set_destroy(space->object_locations);
  }

  free(space);
  space = NULL;
  return OK;
}

Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}

Status space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  if (!strcpy(space->name, name)) {
    return ERROR;
  }
  return OK;
}

const char* space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}

Status space_set_north(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->north = id;
  return OK;
}

Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}

Status space_set_south(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->south = id;
  return OK;
}

Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}

Status space_set_east(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->east = id;
  return OK;
}

Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}

Status space_set_west(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->west = id;
  return OK;
}

Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
}

Status space_set_object(Space* space, Bool value) {
  if (!space) {
    return ERROR;
  }

  if (set_get_count(space->object_locations) > 0) {
    value = TRUE;
  } else {
    value = FALSE;
  }

  return OK;
}

Bool space_get_object(Space* space, Id id) {
  int i, n_ids;

  if (!space || id == NO_ID) {
    return FALSE;
  }

  n_ids = set_get_count(space->object_locations);
  for (i = 0; i < n_ids; i++) {
    if (set_get_id_at(space->object_locations, i) == id) {
      return TRUE;
    }
  }
  return FALSE;
}

Status space_print(Space* space) {
  Id idaux = NO_ID;
  int i, n_ids;

  if (!space) {
    return ERROR;
  }

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  idaux = space_get_north(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }
  idaux = space_get_south(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }
  idaux = space_get_east(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }
  idaux = space_get_west(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  n_ids = set_get_count(space->object_locations);
  if (n_ids > 0) {
    fprintf(stdout, "---> Objects in the space:\n");
    for (i = 0; i < n_ids; i++) {
      fprintf(stdout, "------> Object Id: %ld\n", set_get_id_at(space->object_locations, i));
    }
  } else {
    fprintf(stdout, "---> No objects in the space.\n");
  }

  fprintf(stdout, "---> Graphical description:\n");
  for (i = 0; i < GDESC_ROWS; i++) {
    fprintf(stdout, "     %s\n", space->gdesc[i]);
  }

  return OK;
}

Status space_set_gdesc(Space *space, char gdesc[GDESC_ROWS][GDESC_COLS + 1]) {
  int i;
  if (!space || !gdesc) {
      return ERROR;
  }
  
  for (i = 0; i < GDESC_ROWS; i++) {
      strcpy(space->gdesc[i], gdesc[i]);
  }
  
  return OK;
}

const char **space_get_gdesc(Space *space) {
  if (!space) {
      return NULL;
  }
  return (const char **)space->gdesc;
}
Set *space_get_object_locations(Space *space) {
  if (!space) {
    return NULL;
  }
  return space->object_locations;
}
