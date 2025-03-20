/**
 * @brief It implements the character module
 *
 * @file character.c
 * @author Izan Robles
 * @version 1.0
 * @date 03-03-2024
 * @copyright GNU Public License
 */

#include "character.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Character {
    Id id;                            /*!< Character's id */
    char name[WORD_SIZE + 1];         /*!< Character's name */
    char gdesc[GDESC_SIZE];          /*!< Character's graphic description */
    int health;                      /*!< Character's health points */
    Bool friendly;                   /*!< Whether character is friendly */
    char message[MESSAGE_SIZE + 1];   /*!< Character's message */
    Id location;                     /*!< Character's location */
};

Character* character_create(Id id) {
    Character *newCharacter = NULL;

    if (id == NO_ID) {
        return NULL;
    }

    newCharacter = (Character*)malloc(sizeof(Character));
    if (!newCharacter) {
        return NULL;
    }

    /* Initialize character */
    newCharacter->id = id;
    newCharacter->name[0] = '\0';
    newCharacter->gdesc[0] = '\0';
    newCharacter->health = 100; 
    newCharacter->friendly = TRUE;
    newCharacter->message[0] = '\0';
    newCharacter->location = NO_ID;

    return newCharacter;
}

Status character_destroy(Character* character) {
    if (!character) {
        return ERROR;
    }

    free(character);
    return OK;
}

Id character_get_id(Character* character) {
    if (!character) {
        return NO_ID;
    }
    return character->id;
}

Status character_set_name(Character* character, char* name) {
    if (!character || !name) {
        return ERROR;
    }

    if (strlen(name) > WORD_SIZE) {
        return ERROR;
    }

    strcpy(character->name, name);
    return OK;
}

const char* character_get_name(Character* character) {
    if (!character) {
        return NULL;
    }
    return character->name;
}

Status character_set_gdesc(Character* character, char* gdesc) {
    if (!character || !gdesc) {
        return ERROR;
    }

    if (strlen(gdesc) != GDESC_SIZE - 1) {  /* -1 for null terminator */
        return ERROR;
    }

    strcpy(character->gdesc, gdesc);
    return OK;
}

const char* character_get_gdesc(Character* character) {
    if (!character) {
        return NULL;
    }
    return character->gdesc;
}

Status character_set_health(Character* character, int health) {
    if (!character || health < 0) {
        return ERROR;
    }

    character->health = health;
    return OK;
}

int character_get_health(Character* character) {
    if (!character) {
        return -1;
    }
    return character->health;
}

Status character_set_friendly(Character* character, Bool friendly) {
    if (!character) {
        return ERROR;
    }

    character->friendly = friendly;
    return OK;
}

Bool character_get_friendly(Character* character) {
    if (!character) {
        return FALSE;
    }
    return character->friendly;
}

Status character_set_message(Character* character, char* message) {
    if (!character || !message) {
        return ERROR;
    }

    if (strlen(message) > MESSAGE_SIZE) {
        return ERROR;
    }

    strcpy(character->message, message);
    return OK;
}

const char* character_get_message(Character* character) {
    if (!character) {
        return NULL;
    }
    return character->message;
}

Status character_set_location(Character* character, Id location) {
    if (!character || location == NO_ID) {
        return ERROR;
    }

    character->location = location;
    return OK;
}

Id character_get_location(Character* character) {
    if (!character) {
        return NO_ID;
    }
    return character->location;
}

Id* character_get_location_pointer(Character* character) {
    if (!character) {
        return NULL;
    }
    return &(character->location);
}

Status character_print(Character* character) {
    if (!character) {
        return ERROR;
    }

    fprintf(stdout, "--> Character (Id: %ld; Name: %s)\n", character->id, character->name);
    fprintf(stdout, "Graphics: %s\n", character->gdesc);
    fprintf(stdout, "Health: %d\n", character->health);
    fprintf(stdout, "Friendly: %s\n", character->friendly ? "YES" : "NO");
    fprintf(stdout, "Message: %s\n", character->message);
    fprintf(stdout, "Location: %ld\n", character->location);

    return OK;
}
