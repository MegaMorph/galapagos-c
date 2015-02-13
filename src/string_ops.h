/*
 * string_ops.h
 *
 *  Created on: Aug 4, 2011
 *      Author: barden
 */

/*!
 * \defgroup string_ops String operations
 *
 * This module provides convenient functions for working with strings.
 */

/**@{*/

/*!
 * \file string_ops.h
 *
 * Header for string operation routine
 *
 * \author Marco Barden
 * \since   04 Aug 2011
 * \date    04 Aug 2011
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <cpl.h>

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#ifndef STRING_OPS_H
#define STRING_OPS_H

/* convert string to upper/lower case */
void strtolower(char *str);
void strtoupper(char *str);

/* initialise string str of length n*/
void initialise_string(char *str, const long n);

/*  make sure a string is terminated with '\0'
 *  Note that no checks are performed whether
 *  there is space for an additional character
 */
void terminate_string(char *str);

/* remove leading and trailing blanks from a string */
char* strtrim( char *str );
void strtrim_inplace( char *str );

/* check if string is valid number (returns 1) or not (returns 0) */
cpl_boolean isnumber(char *str);
cpl_boolean isinteger(char *str);

/* remove extension from file/path */
char *rem_ext (const char *str, const char dot, const char sep);

/* find the number of specified characters in a string */
int countChar(char* txt, char chr, char chr2);

/* Removes "*" and "[" if contained in GALFIT output because of contraints or
 fixed parameters */

cpl_error_code remove_chr(char *xp);


#endif /* STRING_OPS_H */

#ifdef __cplusplus
}
#endif

/**@}*/
