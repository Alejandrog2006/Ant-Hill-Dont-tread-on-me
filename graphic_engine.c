/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "graphic_engine.h"

#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"
#include "game.h"

#define WIDTH_MAP 80
#define WIDTH_DES 40
#define WIDTH_BAN 30
#define HEIGHT_MAP 25
#define HEIGHT_BAN 1
#define HEIGHT_HLP 2
#define HEIGHT_FDB 5

struct _Graphic_engine {
  Area *map, *descript, *banner, *help, *feedback;
};

Graphic_engine *graphic_engine_create() {
  static Graphic_engine *ge = NULL;

  if (ge) {
    return ge;
  }

  screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);
  ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
  if (ge == NULL) {
    return NULL;
  }

  ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
  ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
  ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge) {
  if (!ge) return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, obj_loc = NO_ID, id_right = NO_ID, id_left = NO_ID;
  Space *space_act = NULL;
  char obj[15] = "";
  char obj1[15] = "";
  char obj2[15] = "";
  char ch[4] = "";
  char ch1[4] = "";
  char ch2[4] = "";
  char str[255];
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i;
  int game_n_objects = *(game_get_n_objects(game));
  const char *message = NULL;
  Character **characters;
  Id player_location;
  Bool same_location = FALSE;
  Object **objects = game_get_objects(game);
  const char *obj_name;
  Bool friendly; 
  const char *temporal_feedback;
  Status cmd_status;

  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID) {
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);
    id_right = space_get_east(space_act);
    id_left = space_get_west(space_act);

    strcpy(obj, " ");

    for (i = 0; i < game_n_objects; i++) {
      if (game_get_object_location(game, i) == id_back) {
        if (strlen(obj) > 1) {
          strcat(obj, ", ");
        }
        strncat(obj, object_get_name(objects[i]), 14);
      }
    }

    strcpy(ch, "   ");

    for (i = 0; i < MAX_CHARACTERS; i++) {
      if (game_get_character_array(game)[i] != NULL && character_get_location(game_get_character_array(game)[i]) == id_back) {
        strcpy(ch, "^8m");
        ch[3] = '\0';
        break;
      }
    }

    if (id_back != NO_ID) {
      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |        %s %3d|", ch, (int)id_back);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%-15s|", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "        ^");
      screen_area_puts(ge->map, str);
    }

    strcpy(obj, " ");

    for (i = 0; i < game_n_objects; i++) {
      if (game_get_object_location(game, i) == id_act) {
        if (strlen(obj) > 1) {
          strcat(obj, ", ");
        }
        strncat(obj, object_get_name(objects[i]), 14);
      }
    }

    strcpy(ch, "   ");

    for (i = 0; i < MAX_CHARACTERS; i++) {
      if (game_get_character_array(game)[i] != NULL && character_get_location(game_get_character_array(game)[i]) == id_act) {
        strcpy(ch, "^8m");
        ch[3] = '\0';
        break;
      }
    }
    

    if (id_act != NO_ID && id_right == NO_ID && id_left == NO_ID) {
      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | m0^    %s %3d|", ch, (int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%-15s|", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
    }

    strcpy(obj, " ");

    for (i = 0; i < game_n_objects; i++) {
      if (game_get_object_location(game, i) == id_act) {
        if (strlen(obj) > 1) {
          strcat(obj, ", ");
        }
        strncat(obj, object_get_name(objects[i]), 14);
      }
    }
    
    strcpy(obj1, " ");

    for (i = 0; i < game_n_objects; i++) {
      if (game_get_object_location(game, i) == id_right) {
        if (strlen(obj1) > 1) {
          strcat(obj1, ", ");
        }
        strncat(obj1, object_get_name(objects[i]), 14);
      }
    }
    
    strcpy(ch, "   ");

    for (i = 0; i < MAX_CHARACTERS; i++) {
      if (game_get_character_array(game)[i] != NULL && character_get_location(game_get_character_array(game)[i]) == id_act) {
        strcpy(ch, "^8m");
        ch[3] = '\0';
        break;
      }
    }

    strcpy(ch1, "   ");

    for (i = 0; i < MAX_CHARACTERS; i++) {
      if (game_get_character_array(game)[i] != NULL && character_get_location(game_get_character_array(game)[i]) == id_right) {
        strcpy(ch1, "^8m");
        ch1[3] = '\0';
        break;
      }
    }

    if (id_act != NO_ID && id_right != NO_ID && id_left == NO_ID) {
      sprintf(str, "  +---------------+   +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | m0^    %s %3d|   |        %s %3d|",ch, (int)id_act, ch1, (int)id_right);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |   |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |   |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               | > |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |   |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |   |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%-15s|   |%-15s|", obj, obj1);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+   +---------------+");
      screen_area_puts(ge->map, str);
    }
  
    strcpy(obj, " ");

    for (i = 0; i < game_n_objects; i++) {
      if (game_get_object_location(game, i) == id_act) {
        if (strlen(obj) > 1) {
          strcat(obj, ", ");
        }
        strncat(obj, object_get_name(objects[i]), 14);
      }
    }
    
    strcpy(obj1, " ");

    for(i = 0; i < game_n_objects; i++) {
      if (game_get_object_location(game, i) == id_left) {
        if (strlen(obj1) > 1) {
          strcat(obj1, ", ");
        }
        strncat(obj1, object_get_name(objects[i]), 14);
      }
    }

    strcpy(obj2, " ");

    for(i = 0; i < game_n_objects; i++) {
      if (game_get_object_location(game, i) == id_right) {
        if (strlen(obj2) > 1) {
          strcat(obj2, ", ");
        }
        strncat(obj2, object_get_name(objects[i]), 14);
      }
    }

    strcpy(ch, "   ");

    for (i = 0; i < MAX_CHARACTERS; i++) {
      if (game_get_character_array(game)[i] != NULL && character_get_location(game_get_character_array(game)[i]) == id_left) {
        strcpy(ch, "^8m");
        ch[3] = '\0';
        break;
      }
    }

    strcpy(ch1, "   ");

    for (i = 0; i < MAX_CHARACTERS; i++) {
      if (game_get_character_array(game)[i] != NULL && character_get_location(game_get_character_array(game)[i]) == id_act) {
        strcpy(ch1, "^8m");
        ch1[3] = '\0';
        break;
      }
    }

    strcpy(ch2, "   ");

    for (i = 0; i < MAX_CHARACTERS; i++) {
      if (game_get_character_array(game)[i] != NULL && character_get_location(game_get_character_array(game)[i]) == id_right) {
        strcpy(ch1, "^8m");
        ch2[3] = '\0';
        break;
      }
    }

    if (id_act != NO_ID && id_left != NO_ID && id_right != NO_ID) {  

      sprintf(str, "_");
      screen_area_puts(ge->map, str);
      sprintf(str, "_");
      screen_area_puts(ge->map, str);
      sprintf(str, "_");
      screen_area_puts(ge->map, str);
      sprintf(str, "_");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+   +---------------+   +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |        %s %3d|   | m0^    %s %3d|   |        %s %3d|", ch, (int)id_left, ch1, (int)id_act, ch2, (int)id_right);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |   |               |   |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |   |               |   |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               | < |               | > |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |   |               |   |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |   |               |   |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%-15s|   |%-15s|   |%-15s|", obj1, obj, obj2);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+   +---------------+   +---------------+");
      screen_area_puts(ge->map, str);
    }
    
    strcpy(obj, " ");

    for (i = 0; i < game_n_objects; i++) {
      if (game_get_object_location(game, i) == id_act) {
        if (strlen(obj) > 1) {
          strcat(obj, ", ");
        }
        strncat(obj, object_get_name(objects[i]), 14);
      }
    }

    strcpy(obj1, " ");

    for (i = 0; i < game_n_objects; i++) {
      if (game_get_object_location(game, i) == id_left) {
        if (strlen(obj1) > 1) {
          strcat(obj1, ", ");
        }
        strncat(obj1, object_get_name(objects[i]), 14);
      }
    }

    strcpy(ch, "   ");

    for (i = 0; i < MAX_CHARACTERS; i++) {
      if (game_get_character_array(game)[i] != NULL && character_get_location(game_get_character_array(game)[i]) == id_act) {
        strcpy(ch, "^8m");
        ch[3] = '\0';
        break;
      }
    }

    strcpy(ch1, "   ");

    for (i = 0; i < MAX_CHARACTERS; i++) {
      if (game_get_character_array(game)[i] != NULL && character_get_location(game_get_character_array(game)[i]) == id_left) {
        strcpy(ch1, "^8m");
        ch1[3] = '\0';
        break;
      }
    }

    if (id_act != NO_ID && id_right == NO_ID && id_left != NO_ID) {
      
      sprintf(str, "_");
      screen_area_puts(ge->map, str);
      sprintf(str, "_");
      screen_area_puts(ge->map, str);
      sprintf(str, "_");
      screen_area_puts(ge->map, str);
      sprintf(str, "_");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+   +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |        %s% 3d|   | m0^    %s% 3d|", ch1, (int)id_left, ch, (int)id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |   |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |   |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               | < |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |   |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |   |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%-15s|   |%-15s|", obj1, obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+   +---------------+");
      screen_area_puts(ge->map, str);
    }

    strcpy(obj, " ");

    for (i = 0; i < game_n_objects; i++) {
      if (game_get_object_location(game, i) == id_next) {
        if (strlen(obj) > 1) {
          strcat(obj, ", ");
        }
        strncat(obj, object_get_name(objects[i]), 14);
      }
    }

    strcpy(ch, "   ");

    for (i = 0; i < MAX_CHARACTERS; i++) {
      if (game_get_character_array(game)[i] != NULL && character_get_location(game_get_character_array(game)[i]) == id_next) {
        strcpy(ch, "^8m");
        ch[3] = '\0';
        break;
      }
    }

    if (id_next != NO_ID) {
      sprintf(str, "        v");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |        %s %3d|", ch, (int)id_next);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |               |");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |%-15s|", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +---------------+");
      screen_area_puts(ge->map, str);
    }
  }
  
  screen_area_clear(ge->descript);

  sprintf(str, "  Player: Health %d, Position %d", player_get_health(game_get_player(game)), (int)game_get_player_location(game));
  screen_area_puts(ge->descript, str);
  
  characters = game_get_character_array(game);
  player_location = game_get_player_location(game);

  sprintf(str, " ");
  screen_area_puts(ge->descript, str); 

  for (i = 0; i < MAX_CHARACTERS; i++) {
    if (characters[i] != NULL && character_get_location(characters[i]) == player_location) {
      sprintf(str, "  %s:", character_get_name(characters[i]));
      screen_area_puts(ge->descript, str);
      sprintf(str, "  Health: %d", character_get_health(characters[i]));
      screen_area_puts(ge->descript, str);
      friendly = character_get_friendly(characters[i]);
      if (friendly == TRUE) {
        sprintf(str, "  Friend");
        screen_area_puts(ge->descript, str);
      } else {
        sprintf(str, "  Enemy");
        screen_area_puts(ge->descript, str);
      }
      
      break; 
    }
  }
  
  sprintf(str, " ");
  screen_area_puts(ge->descript, str);
  sprintf(str, "  Objects:");
  screen_area_puts(ge->descript, str);

  for (i = 0; i < game_n_objects; i++) {
    if (objects[i] != NULL) {
        obj_loc = game_get_object_location(game, i);
        obj_name = object_get_name(objects[i]);
        
        if (obj_loc != NO_ID && obj_name != NULL) {
            sprintf(str, "  %s --> %d", obj_name, (int)obj_loc);
            screen_area_puts(ge->descript, str);
        }
    }
  }
  
  if (player_get_object(game_get_player(game)) == TRUE) {
    for (i = 0; i < game_n_objects; i++) {
      if (game_get_object_location(game, i) == NO_ID) {
        sprintf(str, "  Player objects: %s", object_get_name(objects[i]));
        screen_area_puts(ge->descript, str);
        break;
      }
    }
  } else {
    sprintf(str, "  Player objects: None");
    screen_area_puts(ge->descript, str);
  }
  
  screen_area_puts(ge->banner, "    The anthill game ");
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, " next or n, back or b, right or r, left or l, take or t, drop or d, atack or a, exit or e, chat or c");
  screen_area_puts(ge->help, str);

  screen_area_clear(ge->feedback);
  last_cmd = command_get_code(game_get_last_command(game));
  cmd_status = command_get_status(game_get_last_command(game));
  
  if (cmd_status == OK) {
    sprintf(str, " %s (%s) - OK", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  } else {
    sprintf(str, " %s (%s) - ERROR", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  }
  screen_area_puts(ge->feedback, str);

  temporal_feedback = game_get_temporal_feedback(game);
  if (temporal_feedback && last_cmd == ATTACK) {
    sprintf(str, " %s", temporal_feedback);
    screen_area_puts(ge->feedback, str);
  }
  
  message = game_get_last_message(game);
  if (message && last_cmd == CHAT) {
  characters = game_get_character_array(game);
  player_location = game_get_player_location(game);

  for (i = 0; i < MAX_CHARACTERS; i++) {
    if (characters[i] != NULL && character_get_location(characters[i]) == player_location) {
      same_location = TRUE;
      break;
    }
  }

  if (same_location) {
    sprintf(str, " Character says: %s", message);
    screen_area_puts(ge->feedback, str);
  }
}

  screen_paint();
  printf("prompt:> ");
}
