/** 
 * @brief It tests set module
 * @author Alejandro González
 * 
 * @file set_test.c
 * @version 1.0 
 * @date 27-02-2025
 */

#include <stdio.h> 
#include <stdlib.h> 
#include "set.h"
#include "test.h"

#define MAX_TESTS 12

void test1_set_create();
void test2_set_create();
void test1_set_destroy();
void test2_set_destroy();
void test1_set_add();
void test2_set_add();
void test1_set_del();
void test2_set_del();
void test1_set_get_count();
void test2_set_get_count();
void test1_set_get_id_at();
void test2_set_get_id_at();

/** 
 * @brief Main function for SET unit tests. 
 * @author Alejandro Gonzalez
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
    printf("Running all test for module Set:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
  }

  if (all || test == 1) test1_set_create();
  if (all || test == 2) test2_set_create();
  if (all || test == 3) test1_set_destroy();
  if (all || test == 4) test2_set_destroy();
  if (all || test == 5) test1_set_add();
  if (all || test == 6) test2_set_add();
  if (all || test == 7) test1_set_del();
  if (all || test == 8) test2_set_del();
  if (all || test == 9) test1_set_get_count();
  if (all || test == 10) test2_set_get_count();
  if (all || test == 11) test1_set_get_id_at();
  if (all || test == 12) test2_set_get_id_at();

  PRINT_PASSED_PERCENTAGE;

  return 1;
}

void test1_set_create() {
  Set *set = set_create();
  PRINT_TEST_RESULT(set != NULL);
  set_destroy(set);
}

void test2_set_create() {
  Set *set = set_create();
  PRINT_TEST_RESULT(set_get_count(set) == 0);
  set_destroy(set);
}

void test1_set_destroy() {
  Set *set = set_create();
  PRINT_TEST_RESULT(set_destroy(set) == OK);
}

void test2_set_destroy() {
  Set *set = NULL;
  PRINT_TEST_RESULT(set_destroy(set) == ERROR);
}

void test1_set_add() {
  Set *set = set_create();
  PRINT_TEST_RESULT(set_add(set, 1) == OK);
  set_destroy(set);
}

void test2_set_add() {
  Set *set = set_create();
  set_add(set, 1);
  PRINT_TEST_RESULT(set_add(set, 1) == ERROR);
  set_destroy(set);
}

void test1_set_del() {
  Set *set = set_create();
  set_add(set, 1);
  PRINT_TEST_RESULT(set_del(set, 1) == OK);
  set_destroy(set);
}

void test2_set_del() {
  Set *set = set_create();
  PRINT_TEST_RESULT(set_del(set, 1) == ERROR);
  set_destroy(set);
}

void test1_set_get_count() {
  Set *set = set_create();
  set_add(set, 1);
  set_add(set, 2);
  PRINT_TEST_RESULT(set_get_count(set) == 2);
  set_destroy(set);
}

void test2_set_get_count() {
  Set *set = set_create();
  PRINT_TEST_RESULT(set_get_count(set) == 0);
  set_destroy(set);
}

void test1_set_get_id_at() {
  Set *set = set_create();
  set_add(set, 1);
  PRINT_TEST_RESULT(set_get_id_at(set, 0) == 1);
  set_destroy(set);
}

void test2_set_get_id_at() {
  Set *set = set_create();
  PRINT_TEST_RESULT(set_get_id_at(set, 0) == NO_ID);
  set_destroy(set);
}