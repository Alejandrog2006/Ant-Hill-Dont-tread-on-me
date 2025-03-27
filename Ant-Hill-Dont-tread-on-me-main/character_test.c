/** 
 * @brief It tests character module
 * @author Alejandro González
 * 
 * @file character_test.c
 * @version 1.0 
 * @date 27-02-2025
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "character.h"
#include "test.h"

#define MAX_TESTS 14

void test1_character_create();
void test2_character_create();
void test1_character_destroy();
void test2_character_destroy();
void test1_character_set_name();
void test2_character_set_name();
void test1_character_get_name();
void test2_character_get_name();
void test1_character_set_location();
void test2_character_set_location();
void test1_character_get_location();
void test2_character_get_location();
void test1_character_set_friendly();
void test2_character_set_friendly();

/** 
 * @brief Main function for CHARACTER unit tests. 
 * @author Alejandro González
 * 
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed 
 *   2.- A number means a particular test (the one identified by that number) 
 *       is executed
 *  
 */
int main(int argc, char** argv) {

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module Character:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
  }

  if (all || test == 1) test1_character_create();
  if (all || test == 2) test2_character_create();
  if (all || test == 3) test1_character_destroy();
  if (all || test == 4) test2_character_destroy();
  if (all || test == 5) test1_character_set_name();
  if (all || test == 6) test2_character_set_name();
  if (all || test == 7) test1_character_get_name();
  if (all || test == 8) test2_character_get_name();
  if (all || test == 9) test1_character_set_location();
  if (all || test == 10) test2_character_set_location();
  if (all || test == 11) test1_character_get_location();
  if (all || test == 12) test2_character_get_location();
  if (all || test == 13) test1_character_set_friendly();
  if (all || test == 14) test2_character_set_friendly();

  PRINT_PASSED_PERCENTAGE;

  return 1;
}

void test1_character_create() {
  Character *character = character_create(1);
  PRINT_TEST_RESULT(character != NULL);
  character_destroy(character);
}

void test2_character_create() {
  Character *character = character_create(NO_ID);
  PRINT_TEST_RESULT(character == NULL);
}

void test1_character_destroy() {
  Character *character = character_create(1);
  PRINT_TEST_RESULT(character_destroy(character) == OK);
}

void test2_character_destroy() {
  Character *character = NULL;
  PRINT_TEST_RESULT(character_destroy(character) == ERROR);
}

void test1_character_set_name() {
  Character *character = character_create(1);
  PRINT_TEST_RESULT(character_set_name(character, "Izan") == OK);
  character_destroy(character);
}

void test2_character_set_name() {
  Character *character = character_create(1);
  PRINT_TEST_RESULT(character_set_name(character, NULL) == ERROR);
  character_destroy(character);
}

void test1_character_get_name() {
  Character *character = character_create(1);
  character_set_name(character, "Izan");
  PRINT_TEST_RESULT(strcmp(character_get_name(character), "Izan") == 0);
  character_destroy(character);
}

void test2_character_get_name() {
  Character *character = character_create(1);
  character_set_name(character, "Alex");
  PRINT_TEST_RESULT(strcmp(character_get_name(character), "Alex") == 0);
  character_destroy(character);
}

void test1_character_set_location() {
  Character *character = character_create(1);
  PRINT_TEST_RESULT(character_set_location(character, 2) == OK);
  character_destroy(character);
}

void test2_character_set_location() {
  Character *character = NULL;
  PRINT_TEST_RESULT(character_set_location(character, 2) == ERROR);
}

void test1_character_get_location() {
  Character *character = character_create(1);
  character_set_location(character, 2);
  PRINT_TEST_RESULT(character_get_location(character) == 2);
  character_destroy(character);
}

void test2_character_get_location() {
  Character *character = NULL;
  PRINT_TEST_RESULT(character_get_location(character) == NO_ID);
}

void test1_character_set_friendly() {
  Character *character = character_create(1);
  PRINT_TEST_RESULT(character_set_friendly(character, TRUE) == OK);
  character_destroy(character);
}

void test2_character_set_friendly() {
  Character *character = NULL;
  PRINT_TEST_RESULT(character_set_friendly(character, TRUE) == ERROR);
}