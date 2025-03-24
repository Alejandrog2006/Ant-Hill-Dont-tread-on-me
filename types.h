/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

 #ifndef TYPES_H
 #define TYPES_H
 
 /**
  * @brief Maximum size for strings (e.g., names, descriptions).
  */
 #define WORD_SIZE 1000
 
 /**
  * @brief Represents an invalid ID.
  */
 #define NO_ID -1
 
 /**
  * @brief Type definition for an identifier (ID).
  *
  * This type is used to uniquely identify entities within the system.
  */
 typedef long Id;
 
 /**
  * @brief Boolean type definition.
  *
  * This enumeration defines the possible boolean values: FALSE and TRUE.
  */
 typedef enum { 
     FALSE,  /**< Represents a false value. */
     TRUE    /**< Represents a true value. */
 } Bool;
 
 /**
  * @brief Status type definition.
  *
  * This enumeration defines the possible status values: ERROR and OK.
  */
 typedef enum { 
     ERROR,  /**< Represents an error status. */
     OK      /**< Represents a successful status. */
 } Status;
 
 /**
  * @brief Direction type definition.
  *
  * This enumeration defines the possible cardinal directions: North, South, East, and West.
  */
 typedef enum { 
     N,  /**< Represents the North direction. */
     S,  /**< Represents the South direction. */
     E,  /**< Represents the East direction. */
     W   /**< Represents the West direction. */
 } Direction;
 
 #endif