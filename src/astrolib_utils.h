/*
 * astrolib_utils.h
 *
 *  Created on: Oct 25, 2011
 *      Author: barden
 */

/**@{*/

/*!
 * \file astrolib_utils.h
 *
 * \brief Header file for SExtractor utilities
 *
 * \author Marco Barden
 * \since  04 Aug 2011
 * \date   04 Aug 2011
 */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef GALA_UTILS_H
#define GALA_UTILS_H

#include <string.h>
#include <math.h>

#include <cpl.h>

#include "string_ops.h"

#include <libgen.h>

/*!
 * Read in a setup_file.

 * \b INPUT:
 * \param setup_file     \em const \em char array containing setup parameters
 *
 * \b OUTPUT:
 * \param test     	 	 \em char \em array containing setup information
 *
 */
cpl_error_code gala_readsetup(const char *setup_file);


/*!
 * \par Assign coordinates of hot and cold run galaxy centers.
 *
 * This is a program to assign coordinates of galaxy centers from the
 * \em b run to the \em a run and vice versa.
 *
 * The program calculates the distances from one galaxy center in the a run
 * to every other galaxy center in the b run.
 *
 * We define a certain threshold "rmax" which has to be gone below
 * for a galaxy - galaxy center distance to be detected as a
 * corresponding galaxy.
 *
 * The match in which the corresponding galaxy will also be printed by
 * the program. If there are two or more galaxy centers inside this
 * threshold radius,
 *
 * the program will also be able to manage this and it will return
 * the match of the corresponding galaxy with the shortest distance.
 *
 * The \b input has to contain:
 *
 * 		\b cpl_tables containing coordinates of corresponding galaxy centers
 *
 * 		\b cpl_arrays containing indices of corresponding galaxy centers
 *
 *      a \b threshold \b value for rmax to separate the galaxies
 *
 *
 * These values must be read in a cpl_array. The routine will
 * calculate an array with the inverse indices containing all indices
 * which do not occur in the input array.
 *
 * \b INPUT:
 * \param table a       Pointer to table.
 * \param table b		Pointer to table.
 * \param index_a		Pointer to array.
 * \param index_b		Pointer to array.
 * \param rmax			Threshold radius to compare the distances.
 *
 * \b OUTPUT:
 * \param index_a		Pointer to cpl_array.
 * \param index_b		Pointer to cpl_array.
 *
 * \b ERRORS:
 * - CPL_ERROR_NONE:  			no error occurred
 * - CPL_ERROR_ILLEGAL_INPUT: 	cpl_tables contain no values
 *
 * \return CPL_ERROR_NONE if no error occurred
 */
cpl_error_code astrolib_srcor(
		   	   	   	  cpl_table *a, const char *xa, const char *ya,
		   	   	   	  cpl_table *b, const char *xb, const char *yb,
		   	   	   	  cpl_array *index_a, cpl_array *index_b,
		   	   	   	  const double *rmax);


/*!
 * \par Select corresponding indices of non-selected galaxy centers.
 *
 * This routine returns indices of selected galaxies. The indices are
 * read in an array.
 *
 * If the index number is found in the array, it will be canceled
 * out and only the remaining indices will be handed back by the program.
 *
 * \warning
 * If the input indices are not sorted in ascending order,
 * the program will not work.
 *
 * \sa
 * In this case you have to use the \b bubblesort program at first
 * to sort the indices accordingly.
 *
 *
 * The \b input has to contain:
 *
 * 		\b number of rows overall
 *
 * 		\b indices of the picked out galaxies
 *
 *
 * These values must be read in a cpl_array.The routine will calculate an
 * array with the inverse indices containing all indices which do not
 * occur in the input array.
 *
 * \b INPUT:
 * \param row			Pointer to array.
 * \param idx			Pointer to array.
 *
 * \b OUTPUT:
 * \param sel			Pointer to array.
 *
 * \b ERRORS:
 * - CPL_ERROR_NONE:  			no error occurred
 * - CPL_ERROR_ILLEGAL_INPUT:  	size of the index array is too big or
 * 								number of rows is too small
 *
 * \return CPL_ERROR_NONE if no error occurred
 */
cpl_error_code astrolib_invertidx (cpl_array *sel, const int a, cpl_array *idx);


/*!
 * \par Sort cpl_arrays (CPL_TYPE_INT) in ascending order.
 *
 * This routine returns sorted cpl_arrays in an \b ascending order.
 * Therefore we use the common \b bubblesort algorithm.
 * \note The operating time is a function of (n^2).
 *
 * This procedure can be optimized with some refinements in the code
 * to accelerate the operating time. This is advisable if your array
 * contains a huge number of elements.
 *
 * The \b input has to contain:
 *
 * 		the \b array containing the numbers you want to sort
 *
 * 		the \b number of elements in the array
 *
 * The routine will count through the whole array and start at the end
 * finding the smallest value. It will check if each element is smaller
 * than its parent element.
 *
 * If this is the case, the positions of the two elements in the array
 * will be changed.
 *
 * This goes on until the smallest element will be the element with
 * the lowest value and the last element ist the element
 * with the highest value.
 *
 * \b INPUT:
 * \param array			Pointer to array.
 * \param len			Length of the input array.
 *
 * \b OUTPUT:
 * \param array			Sorted array.
 *
 * \b ERRORS:
 * - CPL_ERROR_NONE:  			no error occurred
 * - CPL_ERROR_TYPE_MISMATCH:  	input array is not an integer array
 *
 * \return CPL_ERROR_NONE if no error occurred
 */
cpl_error_code astrolib_bubblesort (cpl_array *array, int len);




#endif /* GALA_UTILS_H */

#ifdef __cplusplus
}
#endif

/**@}*/
