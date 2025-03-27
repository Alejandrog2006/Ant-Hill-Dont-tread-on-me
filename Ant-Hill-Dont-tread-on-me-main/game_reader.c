#include "game_reader.h"
#include "space.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Status game_load_spaces(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  char gdesc[GDESC_ROWS][GDESC_COLS + 1];
  Space *space = NULL;
  Status status = OK;
  int i, len;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);

      for (i = 0; i < GDESC_ROWS; i++) {
        toks = strtok(NULL, "|");
        if (toks) {
            while (*toks == ' ' || *toks == '\t') toks++;
            
            strncpy(gdesc[i], toks, GDESC_COLS);
            gdesc[i][GDESC_COLS] = '\0';
            
            len = strlen(gdesc[i]);
            while (len > 0 && (gdesc[i][len-1] == ' ' || gdesc[i][len-1] == '\t' || gdesc[i][len-1] == '\n')) {
                gdesc[i][--len] = '\0';
            }
        } else {
            memset(gdesc[i], ' ', GDESC_COLS);
            gdesc[i][GDESC_COLS] = '\0';
        }
      }

      #ifdef DEBUG
      printf("Leído: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
      printf("Gdesc:\n");
      for (i = 0; i < GDESC_ROWS; i++) {
          printf("[%s]\n", gdesc[i]); 
      }
      #endif
      space = space_create(id);
      if (space != NULL) {
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        space_set_gdesc(space, gdesc);
        game_add_space(game, space);
      }
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);
  return status;
}

Status game_add_space(Game *game, Space *space) {
  int *numSpaces = game_get_n_spaces(game);
  Space **spacePointer = game_get_spaces(game);

  if ((space == NULL) || (*numSpaces >= MAX_SPACES) || (spacePointer == NULL) || numSpaces == NULL) {
    return ERROR;
  }

  spacePointer[*numSpaces] = space;
  (*numSpaces)++;

  return OK;
}

Id game_get_space_id_at(Game *game, int position) {
  int *numSpaces = game_get_n_spaces(game);
  Space **SpacesPointer = game_get_spaces(game);

  if (position < 0 || position >= *(numSpaces) || SpacesPointer == NULL || numSpaces == NULL) {
    return NO_ID;
  }

  return space_get_id(SpacesPointer[position]);
}

Status game_load_objects(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, location = NO_ID;
  Object *object = NULL;
  Status status = OK;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
#ifdef DEBUG
      printf("Leído: %ld|%s|%ld\n", id, name, location);
#endif
      object = object_create(id);
      if (object != NULL) {
        object_set_name(object, name);
        object_set_location(object, location);

        if (game_add_objects(game, object) == ERROR) {
          object_destroy(object);
          fprintf(stderr, "Error while adding object to game.\n");
        }
      }
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);
  return status;
}

Status game_add_objects(Game *game, Object *object) {
  int *numObjects = game_get_n_objects(game);
  Object **objectPointer = game_get_objects(game);

  if ((object == NULL) || (*numObjects >= MAX_OBJECTS) || (objectPointer == NULL)) {
    fprintf(stderr, "Error while adding object to game.\n");
    return ERROR;
  }

  objectPointer[*numObjects] = object;
  (*numObjects)++;
  
  return OK;
}


