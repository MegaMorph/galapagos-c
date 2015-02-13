/*
 ============================================================================
 Name        : galapagos.c
 Author      : Marco Barden
 Version     :
 Copyright   : GPL
 Description : GALAPAGOS in C, Ansi-style
 ============================================================================
 */

/*!
 * \ingroup astrolib_utils
 */

/**@{*/

/*!
 * \callgraph
 *
 * \file astrolib_utils.c
 *
 * \brief Utilities for interfacing with SExtractor.
 *
 * \author Marco and Andreas
 *
 * \date 12 December 2011
 */

#include <stdio.h>

#include <cpl.h>

#include "astrolib_utils.h"

cpl_error_code astrolib_srcor(
		   	   	   	  cpl_table *a, const char *xa, const char *ya,
		   	   	   	  cpl_table *b, const char *xb, const char *yb,
		   	   	   	  cpl_array *index_a, cpl_array *index_b,
		   	   	   	  const double *rmx){

	int i, j;
	int c = 0;
	int z = 0;
	double dist;

// If no corresponding galaxy is found by the program it will return the
// initialized value -1 for the corresponding argument match.

	int min_idx = -1;
	double min_dist = DBL_MAX;

// Calculating the distance between each detected galaxy in the a run
// and the b run and save it in the array radius[j]:

	if ( cpl_table_get_nrow(a) == 0 || cpl_table_get_nrow(b) == 0) {
		return CPL_ERROR_ILLEGAL_INPUT;
		}

	for (i = 0; i < cpl_table_get_nrow(a); i++){
		printf("\n");
			{
			min_dist = DBL_MAX;
			for (j = 0; j < cpl_table_get_nrow(b); j++){
				dist = sqrt(pow(cpl_table_get_double(a, "x", i, NULL) -
					cpl_table_get_double(b, "x", j, NULL), 2) +
					pow(cpl_table_get_double(a, "y", i, NULL) -
					cpl_table_get_double(b, "y", j, NULL), 2));

// If there is a new minimum distance found within a new loop the old
// minimum distance will be overwritten...

				if (dist < min_dist) {
					min_dist = dist;
					min_idx = j;
				}

// ...and it is saved into the new column "Distance":

				if (min_dist < *rmx){
				cpl_table_set (a, "Distance", i, min_dist);
			}
				else {
				cpl_table_set (a, "Index", i, -1);
				cpl_table_set (b, "Index", i, -1);
				}
			}

// If there is a corresponding coordinate found within the threshold radius
// the index of this coordinate can be found in the column "index".
// "-1" means that there is no corresponding coordinate found.

			if (min_dist < *rmx){
				cpl_table_set_double(b, "Distance", min_idx, min_dist);
				cpl_table_set_int(a, "Index", i, min_idx);
				cpl_table_set_int(b, "Index", min_idx, i);
				cpl_array_set_size(index_a, z+1);
				cpl_array_set_size(index_b, z+1);
				cpl_array_set_int(index_a, z, i);
				cpl_array_set_int(index_b, z, min_idx);
				z++;
			}
			else {
			c++;
			}
		}
	}

	return CPL_ERROR_NONE;
}


cpl_error_code astrolib_invertidx (cpl_array *sel, const int a, cpl_array *idx){

	int i, j, k;

	if (cpl_array_get_size (idx) > a){
		return CPL_ERROR_ILLEGAL_INPUT;
	}

	sel = cpl_array_new (a - cpl_array_get_size (idx), CPL_TYPE_INT);

	for (i = 0, j = 0, k = 0; i < a; i++){
		if (cpl_array_get_int (idx, j, NULL) != i) {
			cpl_array_set_int (sel, k, i);
			k++;
		} else {
			j++;
		}
	}

	printf ("Inverted indices:\n");
	cpl_array_dump(sel, 0, cpl_array_get_size(sel), NULL);

	return CPL_ERROR_NONE;
}


cpl_error_code astrolib_bubblesort (cpl_array *array, int len){

	int i, j;       // counting variables
	int tmp;        // helping variable to swap the values

	if (cpl_array_get_type (array) != CPL_TYPE_INT){
		return CPL_ERROR_TYPE_MISMATCH;
	}

	for (i = 0; i < len; i++)
	{

		for (j = len - 1; j >= i; j--)
		{

			if (cpl_array_get_int (array, j, NULL) <
					cpl_array_get_int (array, j - 1, NULL))
			{
				tmp = cpl_array_get_int (array, j, NULL);
				cpl_array_set_int (array, j, cpl_array_get_int
														(array, j - 1, NULL));
				cpl_array_set_int (array, j - 1, tmp);
			}
		}
	}

	return CPL_ERROR_NONE;
}

/**@}*/
