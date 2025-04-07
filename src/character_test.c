/** 
 * @brief It tests character module
 * 
 * @file character_test.c
 * @author Izan Robles
 * @version 1.0 
 * @date 3-03-2025
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "character.h"
#include "test.h"

/**
 * @brief Defines maximum number of tests per execution
 */
#define MAX_TESTS 26

/** 
 * @brief It tests the creation of a character.
 */
void test1_character_create();

/** 
 * @brief It tests the creation of a character with an invalid ID.
 * 
 * This test tries to create a character with an invalid ID (`NO_ID`) and verifies that the function returns NULL,
 * indicating that the character creation has failed. No destruction is needed since the character creation is unsuccessful.
 */
void test2_character_create();

/** 
 * @brief It tests the destruction of a character.
 */
void test1_character_destroy();

/** 
 * @brief It tests the destruction of a NULL character.
 * 
 * This test verifies that trying to destroy a NULL character returns an error (`ERROR`), which helps confirm 
 * the correct handling of invalid input when attempting to destroy a character.
 */
void test2_character_destroy();

/** 
 * @brief It tests setting the name of a character.
 */
void test1_character_set_name();

/** 
 * @brief It tests setting the name of a character with NULL.
 * 
 * This test tries to set the name of a character to NULL and verifies that the operation fails by returning an error (`ERROR`).
 * This ensures that the system handles invalid input correctly.
 */
void test2_character_set_name();

/** 
 * @brief It tests getting the name of a character.
 */
void test1_character_get_name();

/** 
 * @brief It tests getting the name of a character.
 * 
 * This test creates a character with a valid ID (1), sets its name to "Izan", and verifies that the 
 * `character_get_name()` function returns the correct name. It checks if the returned name is "Izan".
 */
void test2_character_get_name();

/** 
 * @brief It tests setting the location of a character.
 */
void test1_character_set_location();

/** 
 * @brief It tests setting the location of a NULL character.
 * 
 * This test tries to set the location of a NULL character and verifies that the operation fails by returning an error (`ERROR`).
 * This ensures that the system handles invalid input correctly.
 */
void test2_character_set_location();

/** 
 * @brief It tests getting the location of a character.
 */
void test1_character_get_location();

/** 
 * @brief It tests getting the location of a character.
 * 
 * This test creates a character with a valid ID (1), sets its location to 2, and verifies that the 
 * `character_get_location()` function correctly retrieves the location ID (2). The character is then destroyed after the test.
 */
void test2_character_get_location();

/** 
 * @brief It tests setting the friendly status of a character.
 */
void test1_character_set_friendly();

/** 
 * @brief It tests setting the friendly status of a NULL character.
 * 
 * This test tries to set the friendly status of a NULL character and verifies that the operation fails by returning an error (`ERROR`).
 * This ensures that the system handles invalid input correctly.
 */
void test2_character_set_friendly();

/** 
 * @brief It tests setting the health of a character.
 */
void test1_character_set_health();

/** 
 * @brief It tests setting the health of a NULL character.
 * 
 * This test tries to set the health of a NULL character and verifies that the operation fails by returning an error (`ERROR`).
 * This ensures that the system handles invalid input correctly.
 */
void test2_character_set_health();

/** 
 * @brief It tests getting the health of a character.
 */
void test1_character_get_health();

/** 
 * @brief It tests getting the health of a NULL character.
 * 
 * This test tries to get the health of a NULL character and verifies that the operation fails by returning an error (`ERROR`).
 * This ensures that the system handles invalid input correctly.
 */
void test2_character_get_health();

/** 
 * @brief It tests setting the message of a character.
 */
void test1_character_set_message();

/** 
 * @brief It tests setting the message of a NULL character.
 * 
 * This test tries to set the message of a NULL character and verifies that the operation fails by returning an error (`ERROR`).
 * This ensures that the system handles invalid input correctly.
 */
void test2_character_set_message();

/** 
 * @brief It tests getting the message of a character.
 */
void test1_character_get_message();

/** 
 * @brief It tests getting the message of a NULL character.
 * 
 * This test tries to get the message of a NULL character and verifies that the operation fails by returning an error (`ERROR`).
 * This ensures that the system handles invalid input correctly.
 */
void test2_character_get_message();

/** 
 * @brief It tests getting the friendly status of a character.
 */
void test1_character_get_friendly();

/** 
 * @brief It tests getting the friendly status of a NULL character.
 * 
 * This test tries to get the friendly status of a NULL character and verifies that the operation fails by returning an error (`ERROR`).
 * This ensures that the system handles invalid input correctly.
 */
void test2_character_get_friendly();

/** 
 * @brief It tests getting the ID of a character.
 */
void test1_character_get_id();

/** 
 * @brief It tests getting the ID of a NULL character.
 * 
 * This test tries to get the ID of a NULL character and verifies that the operation fails by returning an error (`ERROR`).
 * This ensures that the system handles invalid input correctly.
 */
void test2_character_get_id();

/** 
 * @brief It tests printing a character.
 */
void test1_character_print();

/** 
 * @brief It tests printing a NULL character.
 * 
 * This test tries to print a NULL character and verifies that the operation fails by returning an error (`ERROR`).
 * This ensures that the system handles invalid input correctly.
 */
void test2_character_print();

/** 
 * @brief Main function for CHARACTER unit tests. 
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
  if (all || test == 15) test1_character_set_health();
  if (all || test == 16) test2_character_set_health();
  if (all || test == 17) test1_character_get_health();
  if (all || test == 18) test2_character_get_health();
  if (all || test == 19) test1_character_set_message();
  if (all || test == 20) test2_character_set_message();
  if (all || test == 21) test1_character_get_message();
  if (all || test == 22) test2_character_get_message();
  if (all || test == 23) test1_character_get_friendly();
  if (all || test == 24) test2_character_get_friendly();
  if (all || test == 25) test1_character_get_id();
  if (all || test == 26) test2_character_get_id();
  if (all || test == 27) test1_character_print();
  if (all || test == 28) test2_character_print();

  PRINT_PASSED_PERCENTAGE;

  return 0;
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

void test1_character_set_health() {
  Character *character = character_create(1);
  PRINT_TEST_RESULT(character_set_health(character, 100) == OK);
  character_destroy(character);
}

void test2_character_set_health() {
  Character *character = NULL;
  PRINT_TEST_RESULT(character_set_health(character, 100) == ERROR);
}

void test1_character_get_health() {
  Character *character = character_create(1);
  character_set_health(character, 100);
  PRINT_TEST_RESULT(character_get_health(character) == 100);
  character_destroy(character);
}

void test2_character_get_health() {
  Character *character = NULL;
  PRINT_TEST_RESULT(character_get_health(character) == -1); 
}

void test1_character_set_message() {
  Character *character = character_create(1);
  PRINT_TEST_RESULT(character_set_message(character, "Hello!") == OK);
  character_destroy(character);
}

void test2_character_set_message() {
  Character *character = NULL;
  PRINT_TEST_RESULT(character_set_message(character, "Hello!") == ERROR);
}

void test1_character_get_message() {
  Character *character = character_create(1);
  character_set_message(character, "Hello!");
  PRINT_TEST_RESULT(strcmp(character_get_message(character), "Hello!") == 0);
  character_destroy(character);
}

void test2_character_get_message() {
  Character *character = NULL;
  PRINT_TEST_RESULT(character_get_message(character) == NULL);
}

void test1_character_get_friendly() {
  Character *character = character_create(1);
  character_set_friendly(character, TRUE);
  PRINT_TEST_RESULT(character_get_friendly(character) == TRUE);
  character_destroy(character);
}

void test2_character_get_friendly() {
  Character *character = NULL;
  PRINT_TEST_RESULT(character_get_friendly(character) == FALSE);
}

void test1_character_get_id() {
  Character *character = character_create(1);
  PRINT_TEST_RESULT(character_get_id(character) == 1);
  character_destroy(character);
}

void test2_character_get_id() {
  Character *character = NULL;
  PRINT_TEST_RESULT(character_get_id(character) == NO_ID);
}

void test1_character_print() {
  Character *character = character_create(1);
  PRINT_TEST_RESULT(character_print(character) == OK);
  character_destroy(character);
}

void test2_character_print() {
  Character *character = NULL;
  PRINT_TEST_RESULT(character_print(character) == ERROR);
}