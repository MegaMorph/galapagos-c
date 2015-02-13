/*!
 * \defgroup sextractor_utils SExtractor Utilities
 *
 * This module provides utilities for interfacing with SExtractor. Mainly,
 * reading of SExtractor-.param and table files is covered. Also, routines
 * managing column types and required columns are included.
 */

/**@{*/

/*!
 * \file sextractor_utils.h
 *
 * \brief Header file for SExtractor utilities
 *
 * \author Marco Barden
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SEXTRACTOR_UTILS_H
#define SEXTRACTOR_UTILS_H

#include <string.h>

#include <cpl.h>

#include "string_ops.h"

/*!
 * Compose CPL_TABLE of SExtractor entries required by GALAPAGOS including
 * ellipse parameters. Column types are defined in ::su_reqcoltypes.
 *
 * \b OUTPUT:
 * \return tab      CPL_TABLE with required column names
 *
 * \note ::su_reqcoltypes must be updated if columns are changed.
 */
cpl_table *su_reqcols(void);


/*!
 * Find data type of SExtractor column \em col. Default is CPL_TYPE_DOUBLE.
 *
 * \b INPUT:
 * \param col      String with column id
 *
 * \b OUTPUT:
 * \return coltype      CPL_TYPE of column
 *
 * \note ::su_reqcoltypes must be updated if columns are changed in
 * ::su_reqcols.
 */
cpl_type su_reqcoltypes(const char *col);


/*!
 * Read SExtractor parameter file \em parfile into CPL_TABLE \em tab.
 * \em parfile contains column descriptors for output \em tab table.
 * \em tab has to exist as zero-length table on input and contains all
 * columns of the parameter file on output. Columns added through the
 * CPL_TABLE \em addcols can be of arbitrary type. If \em addreqcols is set,
 * required columns defined in ::su_reqcols are added as well.
 *
 * \b INPUT:
 * \param parfile     name of SExtractor parameter file
 * \param addcols     CPL_TABLE with additional columns
 * \param addreqcols  CPL_BOOLEAN: add required columns?
 *
 * \b OUTPUT:
 * \param tab         CPL_TABLE for data
 *
 * \b ERRORS:
 * - CPL_ERROR_FILE_NOT_FOUND if parameter file missing
 */
cpl_error_code su_read_par(cpl_table *tab, const char *parfile,
                           const cpl_table *addcols, cpl_boolean addreqcols);

/*!
 * Read SExtractor ascii table \em datafile into CPL_TABLE \em tab.
 * \em tab must already contain all columns (e.g. after su_read_par).

 * \b INPUT:
 * \param datafile    name of SExtractor ascii table
 *
 * \b OUTPUT:
 * \param tab         CPL_TABLE for data
 *
 * \note Table columns of \em tab and \em datafile must be in the same
 *       order. No checks are performed!
 *
 */
cpl_error_code su_read_sextab(cpl_table *tab, const char *datafile);


/*!
 * \par Running SExtractor.
 *
 * \b INPUT:
 * \param sexexe	Pointer to char array with the according path and the
 * 					command "sex" to run SExtractor within the desired
 * 					directory
 * \param sexsetup	Pointer to char array with the according path to the
 *					.sex file which should contain the setup parameters for
 *					SExtractor
 * \param cat 		Pointer to char array with according path to the output
 * 					catalogue .cat
 * \param outpar	Pointer to char array with the according path to the
 * 					parameter file with the parameters in the catalogue
 * \param image		Pointer to char array with the according path to the
 * 					SExtractor image file
 * \param seg		Pointer to char array with the according path to the
 * 					SExtractor segmentation map
 * \param weight	Pointer to char array with the according path to the
 * 					SExtractor weight image
 * \param check		Pointer to char array with the according path to the
 * 					SExtractor check image
 * \param chktype	Pointer to char array with the according path to the
 * 					SExtractor chktype for the check image (e.g. "APERTURES").
 * \param chk		Boolean, "TRUE" if check image is desired, "FALSE" if not
 * \param dryrun	Boolean, "TRUE" if dryrun for testing, "FALSE" if not
 * \param exptime	Exposure time used for the image.
 * \param zerop		Zeropoint for calculating magnitude zeropoint.
 *
 * \b OUTPUT:
 * \param outtab	Pointer to table containing the whole SExtractor
 * 					information for each element
 *
 * \b ERRORS:
 * \param CPL_ERROR_FILE_NOT_FOUND 		File not found.
 * \param CPL_ERROR_UNSPECIFIED			Unspecified problem with SExtractor.
 * \param CPL_ERROR_ILLEGAL INPUT		Illegal input for SExtractor when
 * 										Kron Radius is always O.
 *
 *\return CPL_ERROR_NONE if no error occurred
 *
 * This routine runs \par SExtractor for a given image and a \b .sex setup file.
 *
 * \note:
 * The paths to the input files must be written in separate \b char arrays.
 *
 * The routine check if an image header with the image is available,
 * calculates its magnitude zeropoint and produces a check image from
 * SExtractor, if desired.
 *
 * After running SExtractor the results are read in a catalogue by the
 * sub-functions su_read_par () and su_read_sextab () and bad
 * Kron Radii are replaced.
 */
cpl_error_code gala_run_sextractor(cpl_table *outtab, const char *sexexe,
		const char *sexsetup, const char *cat, const char *outpar,
		const char *image, const char *seg, const char *weight,
		const char *check, const char *chktype, const double *zerop,
		cpl_boolean chk, cpl_boolean dryrun, const int *multi);


/*!
 * \par Merging two tables.
 *
 * \b INPUT:
 * \param tab1		Pointer to tab1
 * \param tab2		Pointer to tab2
 * \param seg1 		Pointer to char array with the according path to the
 * 					segmentation map of the first SExtractor run
 * \param seg2		Pointer to char array with the according path to the
 * 					segmentation map of the second SExtractor run
 * \param outseg	Pointer to char array with the according path to the
 *  					SExtractor segmentation map
 * \param cat1		Pointer to char array with the according path to the
 * 					SExtractor catalogue 1
 * \param cat2  	Pointer to char array with the according path to the
 * 					SExtractor catalogue 2
 * \param enlarge	Specified value to separate galaxies in the runs
 * \param outonly	Boolean, if "TRUE" sextab will be the only output and
 *  					cat1, cat2, seg1 and seg2 will be removed.
 *
 * \b OUTPUT:
 * \param tab1		Pointer to table containing the whole SExtractor
 * 					information for each element
 *\return CPL_ERROR_NONE if no error occurred
 *
 * This routine merges two tables containing each desired information about
 * each object which was detected in the according SExtractor run.
 *
 * In the first step we use the table with the information about the "cold"
 * objects, meaning the biggest objects with less respect to small
 * irregularities.
 *
 * In the the next step SExtractor is run with a "hotter" setup
 * meaning a setup with more respect to small irregularities.
 *
 * The table with the objects which are not contained in the "cold" run
 * table are added if they fulfil a certain distance criteria.
 */
cpl_error_code gala_merge_tables (cpl_table *tab1,
		cpl_table *tab2, const char *seg1, const char *seg2, const char *outseg,
		const char *cat1, const char *cat2, double *enlarge,
		cpl_boolean outonly);

cpl_error_code create_checkimage(const char *file, const char *cat,
		const char *image);

cpl_error_code check_sextractor_input(cpl_parameterlist *gala_setup);

#endif /* SEXTRACTOR_UTILS_H */

#ifdef __cplusplus
}
#endif

/**@}*/
