/** 
 * @brief It declares the tests for the space module
 * 
 * @file space_test.h
 * @author Profesores Pprog
 * @version 0.0 
 * @date 17-02-2025
 * @copyright GNU Public License
 */

 #ifndef SPACE_TEST_H
 #define SPACE_TEST_H
 
 /**
  * @test Test space creation
  * @pre Space ID 
  * @post Non NULL pointer to space 
  */
 void test1_space_create();
 
 /**
  * @test Test space creation
  * @pre Space ID 
  * @post Space_ID == Supplied Space Id
  */
 void test2_space_create();
 
 /**
  * @test Test function for space_name setting
  * @pre String with space name
  * @post Output==OK 
  */
 void test1_space_set_name();
 
 /**
  * @test Test function for space_name setting
  * @pre Pointer to space = NULL 
  * @post Output==ERROR
  */
 void test2_space_set_name();
 
 /**
  * @test Test function for space_name setting
  * @pre Pointer to space_name = NULL (pointer to space = NON NULL) 
  * @post Output==ERROR
  */
 void test3_space_set_name();
 
 /**
  * @test Test setting an object in space
  * @pre Valid space and object ID
  * @post Output==OK
  */
 void test1_space_set_object();
 
 /**
  * @test Test setting object with NULL space
  * @pre NULL space
  * @post Output==ERROR
  */
 void test2_space_set_object();
 
 /**
  * @test Test getting space ID from valid space
  * @pre Valid space
  * @post Correct ID returned
  */
 void test1_space_get_id();
 
 /**
  * @test Test getting space ID from NULL space
  * @pre NULL space
  * @post Output==NO_ID
  */
 void test2_space_get_id();
 
 /**
  * @test Test getting name from valid space
  * @pre Valid space
  * @post Correct name returned
  */
 void test1_space_get_name();
 
 /**
  * @test Test getting name from NULL space
  * @pre NULL space
  * @post Output==NULL
  */
 void test2_space_get_name();
 
 /**
  * @test Test if space contains an object
  * @pre Valid space
  * @post Correct object presence status
  */
 void test1_space_get_object();
 
 /**
  * @test Test object presence in empty space
  * @pre Valid space with no object
  * @post Output==FALSE
  */
 void test2_space_get_object();
 
 /**
  * @test Test object presence in NULL space
  * @pre NULL space
  * @post Output==FALSE
  */
 void test3_space_get_object();
 
 #endif
 