/**
 * @brief It tests the link module
 * 
 * @file link_test.c
 * @author 
 * @version 1.0
 * @date 01-04-2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"
#include "test.h"

#define MAX_TESTS 16

void test1_link_create();
void test2_link_create();
void test1_link_destroy();
void test2_link_destroy();
void test1_link_set_name();
void test2_link_set_name();
void test1_link_get_name();
void test2_link_get_name();
void test1_link_set_origin();
void test2_link_set_origin();
void test1_link_get_origin();
void test2_link_get_origin();
void test1_link_set_destination();
void test2_link_set_destination();
void test1_link_get_destination();
void test2_link_get_destination();

/**
 * @brief Main function for LINK unit tests.
 * 
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL tests are executed
 *   2.- A number means a particular test (the one identified by that number)
 */
int main(int argc, char** argv) {
    int test = 0;
    int all = 1;

    if (argc < 2) {
        printf("Running all tests for module Link:\n");
    } else {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
    }

    if (all || test == 1) test1_link_create();
    if (all || test == 2) test2_link_create();
    if (all || test == 3) test1_link_destroy();
    if (all || test == 4) test2_link_destroy();
    if (all || test == 5) test1_link_set_name();
    if (all || test == 6) test2_link_set_name();
    if (all || test == 7) test1_link_get_name();
    if (all || test == 8) test2_link_get_name();
    if (all || test == 9) test1_link_set_origin();
    if (all || test == 10) test2_link_set_origin();
    if (all || test == 11) test1_link_get_origin();
    if (all || test == 12) test2_link_get_origin();
    if (all || test == 13) test1_link_set_destination();
    if (all || test == 14) test2_link_set_destination();
    if (all || test == 15) test1_link_get_destination();
    if (all || test == 16) test2_link_get_destination();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_link_create() {
    Link *link = link_create(1);
    PRINT_TEST_RESULT(link != NULL);
    link_destroy(link);
}

void test2_link_create() {
    Link *link = link_create(NO_ID);
    PRINT_TEST_RESULT(link == NULL);
}

void test1_link_destroy() {
    Link *link = link_create(1);
    PRINT_TEST_RESULT(link_destroy(link) == OK);
}

void test2_link_destroy() {
    Link *link = NULL;
    PRINT_TEST_RESULT(link_destroy(link) == ERROR);
}

void test1_link_set_name() {
    Link *link = link_create(1);
    PRINT_TEST_RESULT(link_set_name(link, "Test Link") == OK);
    link_destroy(link);
}

void test2_link_set_name() {
    Link *link = link_create(1);
    PRINT_TEST_RESULT(link_set_name(link, NULL) == ERROR);
    link_destroy(link);
}

void test1_link_get_name() {
    Link *link = link_create(1);
    link_set_name(link, "Test Link");
    PRINT_TEST_RESULT(strcmp(link_get_name(link), "Test Link") == 0);
    link_destroy(link);
}

void test2_link_get_name() {
    Link *link = NULL;
    PRINT_TEST_RESULT(link_get_name(link) == NULL);
}

void test1_link_set_origin() {
    Link *link = link_create(1);
    PRINT_TEST_RESULT(link_set_origin(link, 2) == OK);
    link_destroy(link);
}

void test2_link_set_origin() {
    Link *link = NULL;
    PRINT_TEST_RESULT(link_set_origin(link, 2) == ERROR);
}

void test1_link_get_origin() {
    Link *link = link_create(1);
    link_set_origin(link, 2);
    PRINT_TEST_RESULT(link_get_origin(link) == 2);
    link_destroy(link);
}

void test2_link_get_origin() {
    Link *link = NULL;
    PRINT_TEST_RESULT(link_get_origin(link) == NO_ID);
}

void test1_link_set_destination() {
    Link *link = link_create(1);
    PRINT_TEST_RESULT(link_set_destination(link, 3) == OK);
    link_destroy(link);
}

void test2_link_set_destination() {
    Link *link = NULL;
    PRINT_TEST_RESULT(link_set_destination(link, 3) == ERROR);
}

void test1_link_get_destination() {
    Link *link = link_create(1);
    link_set_destination(link, 3);
    PRINT_TEST_RESULT(link_get_destination(link) == 3);
    link_destroy(link);
}

void test2_link_get_destination() {
    Link *link = NULL;
    PRINT_TEST_RESULT(link_get_destination(link) == NO_ID);
}