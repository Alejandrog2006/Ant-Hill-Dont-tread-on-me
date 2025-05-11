#include "game_rules.h"

/**
 * @brief If the conditions are met, creates a room adjacent to the current one on the east direction
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 * @return OK if everything went correctly, ERROR otherwise
 */
Status event_1(Game *game);

/**
 * @brief If the conditions are met, ends the game
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 * @return OK if everything went correctly, ERROR otherwise
 */
Status event_2(Game *game);

/**
 * @brief If the conditions are met, an enemy spawns in the player's position
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 * @return OK if everything went correctly, ERROR otherwise
 */
Status event_3(Game *game);

/**
 * @brief If the conditions are met, a door is opened
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 * @return OK if everything went correctly, ERROR otherwise
 */
Status event_4(Game *game);

/**
 * @brief If the conditions are met, a new link is made
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 * @return OK if everything went correctly, ERROR otherwise
 */
Status event_5(Game *game);

/**
 * @brief If the conditions are met, the player takes damage
 * @author Daniel Martín Jaén
 * 
 * @param game
 * @return OK if everything went correctly, ERROR otherwise
 */
Status event_6(Game *game);

Space *event_create_space_adjacent(Game *game, Id current_id, Direction dir);

Status game_rules_event(Game *game, Command *last_cmd)
{
    Status status = OK;
    int r_num;
    r_num = rand() % 4;


    if (!game || !last_cmd)
    {
        return ERROR;
    }

    if (event_1(game) == ERROR)
    {
        status = ERROR;
    }

    if (event_2(game) == ERROR)
    {
        status = ERROR;
    }

    if (r_num == 0 && command_get_code(last_cmd) == MOVE)
    {
        status = event_3(game);
    }

    if (event_4(game) == ERROR)
    {
        status = ERROR;
    }

    if (event_5(game) == ERROR)
    {
        status = ERROR;
    }

    if (r_num == 1 && command_get_code(last_cmd) == MOVE)
    {
        status = event_6(game);
    }

    return status;
}

Status event_1(Game *game)
{
    Character **char_p = NULL;
    Id current_id;
    Space *new_space = NULL;
    Object *new_object = NULL;
    int i;

    if (!game)
    {
        return ERROR;
    }

    char_p = game_get_character_array(game);

    for (i = 0; i < *game_get_n_characters(game); i++)
    {
        if(strcasecmp(character_get_name(char_p[i]), "Spider") == 0 && character_get_health(char_p[i]) <= 0)
        {
            break;
        }
    }

    if (i == *game_get_n_characters(game))
    {
        return ERROR;
    }

    current_id = game_find_character(game, character_get_id(char_p[i]));
    if (game_get_connection(game, current_id, E) != NO_ID)
    {
        return ERROR;
    }

    new_space = event_create_space_adjacent(game, current_id, E);
    if (new_space == NULL)
    {
        return ERROR;
    }

    space_set_gdesc_at(new_space, "   ___   ", 0);
    space_set_gdesc_at(new_space, "  /<+>\\  ", 1);
    space_set_gdesc_at(new_space, "  !---!  ", 2);
    space_set_gdesc_at(new_space, "   \\ /   ", 3);
    space_set_gdesc_at(new_space, "   / \\   ", 4);
    space_set_discovered(new_space, FALSE);

    new_object = event_create_object(game, new_space);
    object_set_description(new_object, "The queens crown!");
    object_set_health(new_object, 0);
    object_set_name(new_object, "Crown");
    object_set_movable(new_object, TRUE);

    return OK;

}

Status event_2(Game *game)
{
    Object **objects_p = NULL;
    int i;


    if (!game)
    {
        return ERROR;
    }

    objects_p = game_get_objects(game);

    for (i = 0; i < *game_get_n_objects(game); i++)
    {
        if (strcasecmp(object_get_name(objects_p[i]), "Crown") == 0)
        {
            break;
        }
    }

    if (i == *game_get_n_objects(game))
    {
        return ERROR;
    }

    if (game_get_object_location(game , i) == 21)
    {
        command_set_code(game_get_last_command(game), EXIT);
        return OK;
    }

    return ERROR;
}

Status event_3(Game *game)
{
    Id id_act;
    Space *space_act = NULL;
    Character *new_enemy = NULL;
    Character **chars_p = NULL;
    char *last_message = NULL;
    int i;

    if (!game)
    {
        return ERROR;
    }
 
    chars_p = game_get_character_array(game);

    id_act = game_get_player_location(game);
    if (id_act == NO_ID)
    {
        return ERROR;
    }

    for (i = 0; i < *game_get_n_characters(game); i++)
    {
        if(strcasecmp(character_get_name(chars_p[i]), "Mole") == 0 && game_find_character(game, character_get_id(chars_p[i])) == id_act)
        {
            return ERROR;
        }
    }


    space_act = game_get_space(game, id_act);

    new_enemy = event_create_character(game, space_act);
    character_set_friendly(new_enemy, FALSE);
    character_set_gdesc(new_enemy, " ._.! ");
    character_set_health(new_enemy, 3);
    character_set_name(new_enemy, "Mole");

    last_message = (char *)game_get_last_message(game);
    strcat(last_message, " || AN AMBUSH!!");
    game_set_last_message(game, last_message);

    return ERROR;
}

Status event_4(Game *game)
{
    Character **chars_p = NULL;
    Link **links_p = NULL;
    Id id_space, id_next;
    int i;

    if (!game)
    {
        return ERROR;
    }

    chars_p = game_get_character_array(game);
    links_p = game_get_links(game);

    for (i = 0; i < *game_get_n_characters(game); i++)
    {
        if (strcasecmp(character_get_name(chars_p[i]), "Traitor ant") == 0)
        {
            break;
        }
    }

    if (i == *game_get_n_characters(game))
    {
        return ERROR;
    }

    id_space = game_find_character(game, character_get_id(chars_p[i]));
    id_next = game_get_connection(game, id_space, W);

    if (game_connection_is_open(game, id_space, W) == FALSE && character_get_health(chars_p[i]) <= 0)
    {
        for (i = 0; i < *game_get_n_links(game); i++)
        {
            if (link_get_origin(links_p[i]) == id_space && link_get_destination(links_p[i]) == id_next && link_get_direction(links_p[i]) == W)
            {
                link_set_open(links_p[i], TRUE);
                return OK;
            }
        }
    }

    return ERROR;
}

Status event_5(Game *game)
{
    Object **objects_p = NULL;
    Link *new_link_1 = NULL, *new_link_2 = NULL;
    Id space_obj;
    char *last_message = NULL;
    int i;

    if (!game)
    {
        return ERROR;
    }

    objects_p = game_get_objects(game);

    for (i = 0; i < *game_get_n_objects(game); i++)
    {
        if (strcasecmp(object_get_name(objects_p[i]), "Stick") == 0)
        {
            break;
        }
    }

    if (i == *game_get_n_objects(game))
    {
        return ERROR;
    }

    space_obj = object_get_location(objects_p[i]);
    if (space_obj != 14 && game_get_connection(game, 14, U) == NO_ID) 
    {
        new_link_1 = link_create(*game_get_n_links(game) - 1 + 200);
        link_set_origin(new_link_1 ,14);
        link_set_destination(new_link_1, 24);
        link_set_direction(new_link_1, U);
        link_set_open(new_link_1, TRUE);
        link_set_name(new_link_1, "Hole");
        game_add_link(game, new_link_1);

        new_link_2 = link_create(*game_get_n_links(game) -1 + 200);
        link_set_origin(new_link_2, 23);
        link_set_destination(new_link_2, 25);
        link_set_direction(new_link_2, D);
        link_set_open(new_link_2, TRUE);
        link_set_name(new_link_2, "Hole");
        game_add_link(game, new_link_2);

        player_set_health(game_get_player_at(game, game_get_turn(game)), player_get_health(game_get_player_at(game, game_get_turn(game))) - 2);
        last_message = (char *)game_get_last_message(game);
        game_set_last_message(game, strcat(last_message, " The rooft collapsed!"));

        return OK;
    }

    return ERROR;
}

Status event_6(Game *game)
{
    int player_health;
    char *last_message = NULL;

    if (!game)
    {
        return ERROR;
    }

    player_health = player_get_health(game_get_player_at(game, game_get_turn(game)));
    last_message = (char *)game_get_last_message(game);
    game_set_last_message(game, strcat(last_message, "|| The roof collapsed!"));
    player_health -= 2;

    player_set_health(game_get_player_at(game, game_get_turn(game)), player_health);

    return OK;
}

Space *event_create_space_adjacent(Game *game, Id current_id, Direction dir)
{
    Space *new_space = NULL;
    Link *new_link_1 = NULL, *new_link_2 = NULL;
    Direction r_dir;
    Id space_new_id, link_1_new_id, link_2_new_id;

    if(!game || current_id == NO_ID || dir == NONE)
    {
        return NULL;
    } 

    switch(dir)
    {
        case N:
            r_dir = S;
            break;

        case S:
            r_dir = N;
            break;
        
        case E:
            r_dir = W;
            break;

        case W:
            r_dir = E;
            break;

        case U:
            r_dir = D;
            break;

        case D:
            r_dir = U;
            break;

        default:
            r_dir = NONE;
    }

    if(r_dir == NONE)
    {
        return NULL;
    }

    space_new_id = *game_get_n_spaces(game) - 1 + 100;
    link_1_new_id = *game_get_n_links(game) - 1 + 200;
    link_2_new_id = *game_get_n_links(game) - 1 + 300;

    new_space = space_create(space_new_id);
    game_add_space(game, new_space);

    new_link_1 = link_create(link_1_new_id);
    link_set_origin(new_link_1 ,current_id);
    link_set_destination(new_link_1, space_new_id);
    link_set_open(new_link_1, TRUE);
    link_set_name(new_link_1, "Secret passage");
    link_set_direction(new_link_1, dir);
    game_add_link(game, new_link_1);

    new_link_2 = link_create(link_2_new_id);
    link_set_origin(new_link_2, space_new_id);
    link_set_destination(new_link_2, current_id);
    link_set_open(new_link_2, TRUE);
    link_set_name(new_link_2, "Secret exit");
    link_set_direction(new_link_2, r_dir);
    game_add_link(game, new_link_2);

    return new_space;
}

Object *event_create_object(Game *game, Space *space)
{
    Object *new_object = NULL;
    Id object_new_id;

    if (!game || !space)
    {
        return NULL;
    }

    object_new_id = *game_get_n_objects(game) - 1 + 400;
    new_object = object_create(object_new_id);
    object_set_location(new_object, space_get_id(space));
    game_add_objects(game, new_object);

    return new_object;
}

Character *event_create_character(Game *game, Space *space)
{
    Character *new_character = NULL;
    Id character_new_id;

    if (!game || !space)
    {
        return NULL;
    }

    character_new_id = *game_get_n_characters(game) - 1 + 500;
    new_character = character_create(character_new_id);
    game_add_character(game, new_character, space_get_id(space));

    return new_character;
}