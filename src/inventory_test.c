/**
 * @brief It tests inventory module
 *
 * @file inventory_test.c
 * @author Rodrigo Cruz Asensio
 * @version 1.0
 * @date 18-03-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "inventory.h"
#include "test.h"

/**
 * @brief Defines maximum number of test per execution
 */
#define MAX_TESTS 10

/**
 * @brief It tests the creation of an inventory.
 *
 * This test creates an inventory with a maximum size and checks if the inventory is successfully created.
 * The inventory is then destroyed after the test to ensure proper memory management.
 */
void test_inventory_create();

/**
 * @brief It tests the destruction of an inventory.
 *
 * This test creates an inventory, and then checks if it can be destroyed correctly.
 * It verifies that the function returns the expected result (OK) when destroying the inventory.
 */
void test_inventory_destroy();

/**
 * @brief It tests adding an object to the inventory.
 *
 * This test creates an inventory and adds an object (with ID 1) to it. It then verifies that the addition was successful
 * by checking the return value (OK). The inventory is destroyed after the test.
 */
void test1_inventory_add_object();

/**
 * @brief It tests adding an object to a full inventory.
 *
 * This test creates an inventory, adds three objects to it, and then tries to add a fourth object. It verifies
 * that the addition of the fourth object fails by returning an error (ERROR). The inventory is destroyed after the test.
 */
void test2_inventory_add_object();

/**
 * @brief It tests deleting an object from the inventory.
 *
 * This test creates an inventory, adds an object (with ID 1), and then deletes that object. It verifies that the object
 * is successfully removed by checking the return value (OK). The inventory is destroyed after the test.
 */
void test1_inventory_del_object();

/**
 * @brief It tests deleting a non-existent object from the inventory.
 *
 * This test creates an inventory and attempts to delete an object that has not been added to the inventory.
 * It verifies that the deletion fails and returns an error (ERROR). The inventory is destroyed after the test.
 */
void test2_inventory_del_object();

/**
 * @brief It tests if an object is present in the inventory.
 *
 * This test creates an inventory, adds an object (with ID 1), and then checks if the object exists in the inventory.
 * It verifies that the object is present by checking that the function returns TRUE. The inventory is destroyed after the test.
 */
void test1_inventory_contains_object();

/**
 * @brief It tests if an object is not present in the inventory.
 *
 * This test creates an inventory and checks if an object (with ID 1) is present, but the object has not been added yet.
 * It verifies that the object is not present by checking that the function returns FALSE. The inventory is destroyed after the test.
 */
void test2_inventory_contains_object();

/**
 * @brief Main function for INVENTORY unit tests.
 *
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL tests are executed
 *   2.- A number means a particular test (the one identified by that number)
 */
int main(int argc, char **argv)
{
	int test = 0;
	int all = 1;

	if (argc < 2)
	{
		printf("Running all tests for module Inventory:\n");
	}
	else
	{
		test = atoi(argv[1]);
		all = 0;
		printf("Running test %d:\t", test);
	}

	if (all || test == 1)
		test_inventory_create();
	if (all || test == 2)
		test_inventory_destroy();
	if (all || test == 3)
		test1_inventory_add_object();
	if (all || test == 4)
		test2_inventory_add_object();
	if (all || test == 5)
		test1_inventory_del_object();
	if (all || test == 6)
		test2_inventory_del_object();
	if (all || test == 7)
		test1_inventory_contains_object();
	if (all || test == 8)
		test2_inventory_contains_object();

	PRINT_PASSED_PERCENTAGE;

	return 1;
	if (all || test == 3)
		test_inventory_destroy();
}

void test_inventory_create()
{
	Inventory *inventory = inventory_create(3);
	PRINT_TEST_RESULT(inventory != NULL);
	inventory_destroy(inventory);
}

void test_inventory_destroy()
{
	Inventory *inventory = inventory_create(3);
	PRINT_TEST_RESULT(inventory_destroy(inventory) == OK);
}

void test1_inventory_add_object()
{
	Inventory *inventory = inventory_create(3);
	PRINT_TEST_RESULT(inventory_add_object(inventory, 1) == OK);
	inventory_destroy(inventory);
}

void test2_inventory_add_object()
{
	Inventory *inventory = inventory_create(3);
	inventory_add_object(inventory, 1);
	inventory_add_object(inventory, 2);
	inventory_add_object(inventory, 3);
	PRINT_TEST_RESULT(inventory_add_object(inventory, 4) == ERROR);
	inventory_destroy(inventory);
}

void test1_inventory_del_object()
{
	Inventory *inventory = inventory_create(3);
	inventory_add_object(inventory, 1);
	PRINT_TEST_RESULT(inventory_del_object(inventory, 1) == OK);
	inventory_destroy(inventory);
}

void test2_inventory_del_object()
{
	Inventory *inventory = inventory_create(3);
	PRINT_TEST_RESULT(inventory_del_object(inventory, 1) == ERROR);
	inventory_destroy(inventory);
}

void test1_inventory_contains_object()
{
	Inventory *inventory = inventory_create(3);
	inventory_add_object(inventory, 1);
	PRINT_TEST_RESULT(inventory_contains_object(inventory, 1) == TRUE);
	inventory_destroy(inventory);
}

void test2_inventory_contains_object()
{
	Inventory *inventory = inventory_create(3);
	PRINT_TEST_RESULT(inventory_contains_object(inventory, 1) == FALSE);
	inventory_destroy(inventory);
}
