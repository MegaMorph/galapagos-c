/*
 * galapagos_utils.h
 *
 *  Created on: Aug 4, 2011
 *      Author: barden
 */

/**@{*/

/*!
 * \file galapagos_utils.h.
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

#include <math.h>

#include <stdlib.h>

#include <cpl.h>

#include "string_ops.h"

#include <libgen.h>

#include <string.h>

#include <time.h>

#include <sys/stat.h>

#include <cpl_wcs.h>

#include "wcslib.h"

#include "mpi.h"


// Define type of struct for every object

struct fitlist {

	// Variable to allow or prohibit fitting
	// 0 : Fitting is allowed
	// 1:  Fitting is prohibited
	// (2: Fit crashed once?)

	short dofit;

	// Variable to define number of secondaries

	long n;

	// Array containing SExtractor numbers as identifiers for secondaries
	// Define a maximum number of secondaries? 20? Reallocation of memory
	// could cause problems because array containing all structs of every
	// object is already "mallocated"...

	long secondaries[20];

	// Array containing indices of brighter secondaries
	// A fit from these secondaries has to exist before the primary can
	// be fitted.

	long brightsecs[10];
};


// Define type of struct for every object

struct fitlistct {

	// Variable to allow or prohibit fitting
	// 0 : Fitting is allowed
	// 1:  Fitting is prohibited
	// (2: Fit crashed once?)

	short dofit;

	// Variable to define number of secondaries

	long n;

	// Array containing SExtractor numbers as identifiers for contrib targets
	// Define a maximum number of contribs? 20? Reallocation of memory
	// could cause problems because array containing all structs of every
	// object is already "mallocated"...

	long ctn[20];
};



/*!
 * Read in a setup_file.
 *
 * \b INPUT:
 * \param setup_file     \em const \em char array containing setup parameters
 *
 * \b OUTPUT:
 * \param test     	 	 \em char \em array containing setup information
 *
 */

cpl_error_code gala_readsetup(const char *setup_file);


/*!
 * Read in a formatted file into a \em cpl_table.
 *
 * The format contains three columns formatted with a \em string variable in
 * the first column and \em int variables in the second and the third columns.
 * This routine will return a \em cpl_table with three columns containing the
 * corresponding variables.

 * \b INPUT:
 * \param exclude_tab     	\em cpl_table with given name
 * \param exclude         	\em const char array containing a path
 * 							string to find the corresponding exclude file
 *
 * \b OUTPUT:
 * \param exclude_tab     	\em cpl_table
 * 							 filled with the content of the exclude file
 *
 * \b ERRORS:
 * - CPL_ERROR_FILE_NOT_FOUND:   		if parameter file missing
 * - CPL_ERROR_UNSPECIFIED:      		if the file was found but the format
 * 								 		was not appropriate to be read in
 * - CPL_ERROR_NONE:             		no error occured
 */

cpl_error_code gala_readexclude(cpl_table *exclude_tab, const char *exclude);


/*!
 * Cutting Postage Stamps
 *
 * This routine cuts postage stamps containing one object apart from
 * overlapping partial sources. It contains three sub-routines:
 * get_stamp_param() extracts the image coordinates to define the postage
 * stamp location
 * create_stamp_file() creates the output file to save the postage stamps
 * save stamp() cuts the postage stamps and saves them into the
 * desired directory.
 *
 * \b INPUT:
 * \param cp_setup 		setup for SExtractor CPL_PARAMETERLIST
 *
 * \return CPL_ERROR_NONE if no error occurred
 *
 */
cpl_error_code cut_post(cpl_parameterlist *gala_setup);


/*!
 * Extract the retangular stamps coordiantes and parameters.
 *
 * This routine extracts the stamps parameters in the picture in x und y
 * direction from the lower to the higher border.
 *
 * \b INPUT:
 * \param i     		numberating parameters for every postage stamp
 * \param tab         	\em cpl_table containing object parameters
 * \param x             image size in x
 * \param y             image size in y
 *
 * \b OUTPUT:
 * \param xlo         	lower x coordinate
 * \param xhi           higher x coordinate
 * \param ylo           lower y coordinate
 * \param yhi  		    higher y coordinate
 *
 * \b ERRORS:
 * CPL_ERROR_NONE:      no error occured
 */

cpl_error_code get_stamp_param(const int *i, int *xlo, int *xhi, int *ylo,
							   int *yhi, const int *x, const int *y,
							   const double *sizefac, cpl_table *tab, FILE *fp);


/*!  Create filename for postage stamp output file.
 *
 * According to i the filename is attached by "_i.fits".
 * Example: i = 97, outprefix : outstamp -> outstamp_97.fits
 *
 * \b INPUT:
 * \param dir          directory to create - if directory already exists
 *                     files are saved into existing directory
 * \param outprefix    filename prefix
 * \param i            numeration value
 *
 * \b OUTPUT:
 * \param dir          complete filename (= dir + "/" + outprefix + "_i.fits")
 *
 * \b ERRORS:
 * CPL_ERROR_NONE:     no error occured
 */

cpl_error_code create_stamp_file(char *outname, char *stampfile, char *outprefix,
		                         cpl_table *outtab, const int *i);


/*!  Cutting stamps and save them.
 *
 * This routine cuts postage stamps by extracting them from the given cpl_image
 * according to the image coordinates. The postage stamps are saved in the file
 * \em outstamp.
 *
 * \b INPUT:
 * \param im           \em cpl_image
 * \param xlo          lower x coordinate
 * \param xhi          higher x coordinate
 * \param ylo          lower y coordinate
 * \param yhi  		   higher y coordinate
 *
 * \b OUTPUT:
 * \param outstamp     complete filename (= dir + "/" + outprefix + "_i.fits")
 * \param header       postage stamp image header
 *
 * \b ERRORS:
 * CPL_ERROR_NONE:     no error occured
 */

cpl_error_code save_stamp(const char *outstamp, const char *header,
		int *xlo, int *xhi, int *ylo, int *yhi,
		cpl_image *im);


/*!
 * \brief
 *   Calculate mean and rms using sigma-clipping routine
 *
 * This function calculates the mean and rms of a cpl_array first by
 * computing the median absolute difference and afterwards applying
 * Huber's method. Values identified as outliers are flagged "invalid"
 * in the input array. If a more stringent value on the mean/rms is
 * desired, /em clip can be set to 1, resulting in the outliers being
 * removed from the calculation of the mean/rms (in contrast to
 * "compressing" them to the outer boundaries of the clipping, i.e.
 * Huber's method). See: AMC Technical Briefs - ISSN 1757-5958, No.6,
 * Royal Society of Chemistry, 2001
 * http://www.rsc.org/images/brief6_tcm18-25948.pdf
 *
 * \note
 *   The input array might have invalid rows on output. Invalid rows on
 *   input are excluded from the computation.
 *
 * \b INPUT:
 * \param arr   cpl_array
 * \param clip  flag for clipping mode
 *
 * \b OUTPUT:
 * \param mean  mean
 * \param rms   root-mean-square
 *
 * \b ERRORS:
 * - none
 */
cpl_error_code sc_basic_clipmean(double *mean, double *rms,
                                 cpl_array *arr, const cpl_boolean clip);



/*!
 * \brief Copy one cpl_table into another.
 *
 * \b INPUT:
 * \param table 		Pointer to input table.
 *
 * \b OUTPUT:
 * \param table			Pointer to output table.
 *
 * \returns CPL_ERROR_NONE if no error occurred
 *
 * \error
 *   <table class="ec" align="center">
 *     <tr>
 *       <td class="ecl">CPL_ERROR_NULL_INPUT</td>
 *       <td class="ecr">
 *         The <i>filepointer</i> to the <i>file</i> is a <tt>NULL</tt> pointer.
 *       </td>
 *     </tr>
 *     <tr>
 *       <td class="ecl">CPL_ERROR_INVALID_TYPE</td>
 *       <td class="ecr">
 *         <i>cloumns</i> are not available.
 *       </td>
 *     </tr>
 *     <tr>
 *       <td class="ecl">CPL_ERROR_UNSPECIFIED</td>
 *       <td class="ecr">
 *         The <i>table</i> has zero length.
 *       </td>
 *     </tr>
 *     <tr>
 *       <td class="ecl">CPL_ERROR_NONE</td>
 *       <td class="ecr">
 *         No <tt>ERROR</tt> occurred.
 *       </td>
 *     </tr>
 *     <tr>
 *   </table>
 * \enderror
 *
 * This routine replaces the cpl_command ::cpl_table_duplicate().
 *
 * Use it if you want to copy a \em table (second argument in the function)
 * to another \em table (first argument in the function).
 */

cpl_error_code cpl_table_copy (cpl_table *outtable, cpl_table *intable);


/*!
 * Check if the input file is correct.
 *
 * \param filename     Path to the local filename.
 *
 * \return             \c CPL_ERROR_NONE or error if an error occurred.
 *
 * \error
 *   <table class="ec" align="center">
 *     <tr>
 *       <td class="ecl">CPL_ERROR_FILE_NOT_FOUND</td>
 *       <td class="ecr">
 *         The input <i>file</i> is a <tt>NULL</tt> pointer.
 *       </td>
 *     </tr>
 *     <tr>
 *       <td class="ecl">CPL_ERROR_INCOMPATIBLE_INPUT</td>
 *       <td class="ecr">
 *         <i>file</i> but input was not readable by SExtractor.
 *       </td>
 *     </tr>
 *   </table>
 * \enderror
 *
 * This function is to check if a file can be located and if its content
 * to the correct input file for galapagos. This is achieved by
 * comparing the first line of the file to the first line of the
 * galapagos input setup.
 */

cpl_error_code filecheck(const char *filename);


//******************************************************************
// Read in GALAPAGOS setup file
//
// Reads input parameters from setup file and writes them into a
// parameterlist
// Checks if number of files is matching
//
// Author: Andreas
// Date: 2.5.2012
// Place: Doha University, Qatar
//*******************************************************************

cpl_error_code read_galasetup(cpl_parameterlist *gala_setup,
							  char *filename);


//*******************************************************************
// Adjust and complete SExtractor setup file
//
// Automatically adjusted to the number of input images
// Overwrites the standing alone SExtractor input file
// according to the input image, the weight image and
// the SExtractor output file.
//********************************************************************

cpl_error_code adjust_galasetup(cpl_parameterlist *sex_setup,
		cpl_array *imagearray, cpl_array *weightarray,
		cpl_array *directory,  cpl_array *suffix,
	    const int rank);

cpl_error_code clean_galasetup(cpl_parameterlist *sex_setup);

//********************************************************************
// Read a GALAPAGOS input parameter from a setup file line
// on a parameterlist
//********************************************************************

int get_param(cpl_parameterlist *sex_setup, char *line, FILE *fp,
			  const char *filen);


//******************************************************************
// Read in GALAPAGOS input file
//
// Reads input file and writes data into arrays
// image -> imagearray
// weightimage -> weightimagearray
// directory -> directoryarray
// suffix -> suffixarray
// Checks if number of files is matching
//
// Author: Andreas
// Date: 2.5.2012
// Place: Doha University, Qatar
//*******************************************************************

cpl_error_code read_galafile(cpl_array *image,     cpl_array *weight,
		                     cpl_array *directory, cpl_array *suffix,
		                     char *filename);


//********************************************************************
// Create a combined SExtractor output catalog over all tiles
//********************************************************************

cpl_error_code create_combcat(cpl_parameterlist *gala_setup,
		cpl_array *directory);


//********************************************************************
// Calculate stamp parameters for a current object in a loop
//
// INPUT : i						Current loop variable
//		   x						Image size x
//         y						Image size y
//         sizefac 					Enlarging factor for stamps
//         tab      				SExtractor table
//
// OUTPUT: xlo, xhi, ylo, yhi       Stamp parameters
//
// ERRORS: CPL_ERROR_NONE           No error occurred
//********************************************************************

cpl_error_code get_loop_param(const int *i, int *xlo, int *xhi, int *ylo,
							   int *yhi, const int *x, const int *y,
							   const double *sizefac, cpl_table *tab);


//********************************************************************
// Create skymap
//********************************************************************

cpl_error_code create_skymap(cpl_parameterlist *gala_setup);


//********************************************************************
// Checks if user input is valid
//********************************************************************

cpl_error_code check_gala_input(cpl_parameterlist *gala_setup);


//********************************************************************
// Background estimation routine
//********************************************************************

cpl_error_code estimate_background(cpl_parameterlist *gala_setup);


//********************************************************************
// Write background values into combined catalog
//
// INPUT: All required variables are read from a cpl_parameterlist.
//        Should contain an output directory "outdir" where the
//        combined catalog is located and its name "combcat".
//        Additionally a filename for the sky file "outsky" is
//        required.
//********************************************************************

cpl_error_code write_sky_output(cpl_parameterlist *gala_setup);

double global_sky (const char *imagefile, const char *mapfile,
		const char *savefile);


//********************************************************************
// Estimating slope for nslope measuring points
//********************************************************************

double calculate_slope(cpl_array *slopecalc, const int *nslope);


//********************************************************************
// Run GALFIT parallel
//********************************************************************

cpl_error_code run_galfit_parallel_NEW(cpl_parameterlist *gala_setup);


//********************************************************************
// Run GALFIT Fourier modes
//********************************************************************

cpl_error_code run_galfit_fourier_modes(cpl_parameterlist *gala_setup);


//****************************************************************************
// Identify Secondaries and write them into a cpl_table
//
// Checks for an object in a cpl_table if there are secondaries
//
// INPUT : cpl_table *tab              SExtractor Output table
//         const double *secenlarge    Enlarging factor for SExtractor ellipses
//         const double *offset        Offset for enlarging SExtractor ellipses
//         const int *i     		   SExtractor catalog number of the object
//									   to search of secondaries
//
// OUTPUT : cpl_table *secondary       cpl_table containing secondaries
//
// ERRORS : CPL_ERROR_DATA_NOT_FOUND   Input SExtractor table is empty
//			CPL_ERROR_NONE             No error occured
//****************************************************************************

cpl_error_code find_secondaries_NEW(cpl_table *tab, const double *offset,
		const double *secenlarge, const double *magexclude);

//****************************************************************************
// Checking overlap of two ellipses
//
// Checks for two given ellipses if they are overlapping or not.
// (Quick & dirty but ok for this purpose. Is there a better method?)
// If they do, a cpl_boolean CPL_TRUE is returned, if not, CPL_FALSE.
//
// INPUT: Ellipse parameters for both ellipses
//			xc1      Center coordinate of first ellipse
//			yc1      Center coordinate of first ellipse
//			a1       Semi-half major axis of first ellipse
//			b1       Semi-half minor axis of first ellipse
//			theta1   Inclination angle of first ellipse
//			xc2      Center coordinate of second ellipse
//			yc2      Center coordinate of second ellipse
//			a2       Semi-half major axis of second ellipse
//			b2       Semi-half minor axis of second ellipse
//			theta2   Inclination angle of second ellipse
// RETURN: CPL_TRUE if overlapping, CPL_FALSE if not
//****************************************************************************

cpl_boolean ellipse_overlap(const double *x1, const double *y1,
		const double *a1, const double *b1, const double *phi1,
		const double *x2, const double *y2,
		const double *a2, const double *b2, const double *phi2);

double ell_rad(const double *a, const double *b, const double *phi);


//****************************************************************************
// Check if point is inside of an ellpise or not
//
// Checks for a given ellipse and a point if the point is
// lying inside of the ellipse not.
// If it does, a cpl_boolean CPL_TRUE is returned, if not, CPL_FALSE.
//
// INPUT: Ellipse parameters and point coordinates
//          xp       x-coordinate of point
//          yp       y-coordinate of point
//			xc       Center coordinate of ellipse
//			yc       Center coordinate of ellipse
//			a        Semi-half major axis of ellipse
//			b        Semi-half minor axis of ellipse
//			theta    Inclination angle of ellipse
// RETURN: CPL_TRUE if inside, CPL_FALSE if not
//****************************************************************************

cpl_boolean point_ellipse(const double *xp, const double *yp,
		                  const double *xc, const double *yc,
		                  const double *a,  const double *b,
		                  const double *theta);


//****************************************************************************
// Creating a bad pixel mask for GALFIT
//
// We mask out: Tertiaries, zero pixels in the weight image,
// overlapping areas from tertiaries with secondaries according to
// the segmentation image, faint object covering primary according to
// the segmentation image.
// Pixel with value = 0 are valid for GALFIT, nonzero pixels are excluded.
//
// INPUT:  sextractor output table
//         secondary table
//		   weight image
//		   segmentation image
//         postage stamp parameter table (loaded from file)
//
// OUTPUT: mask image saved into maskfile
//
// ERRORS: CPL_ERROR_DATA_NOT_FOUND    Input SExtractor table is empty
//		   CPL_ERROR_NONE              No error occured
//****************************************************************************

cpl_error_code create_mask_NEW(const char *badpix,
		                       const double *secenlarge, const double *offset,
		                       cpl_table *tab, cpl_image *weight,
		                       cpl_image *seg, const long *i);


//****************************************************************************
// Creating a setup file for GALFIT
//
// According to the current parameterlist values a setup file for the
// current object is generated.
//****************************************************************************

cpl_error_code create_GALFIT_setup_NEW(cpl_parameterlist *gala_setup,
								   const long *i);

//****************************************************************************
// Read from a GALFIT fits header if a fit is flagged or not
//
// INPUT: imagefile       Path to GALFIT imageblock
//
//
//****************************************************************************

int readfits_header(const char *imagefile);

cpl_error_code *construct_aquarium(cpl_array *borderpix, cpl_image *image,
		const double *rebinfactor);

double calc_dist_to_edge(double *xc, double *yc, cpl_array *borderpix,
		int *xsize, int *ysize, const double *rebinfactor);

cpl_matrix *identify_neighbortiles(cpl_array *imagearray);

cpl_boolean ellpoint(const double *xc, const double *yc, const double *xp,
		const double *yp, const double* a, const double *b,
		const double *theta);

cpl_error_code clear_catalogue(cpl_table *centraltab,
		cpl_table *neighbortab, cpl_table *combtab, cpl_wcs *wcs);

cpl_error_code merge_tables(cpl_array *imagearray, cpl_array *directory,
		cpl_parameterlist *gala_setup);

cpl_error_code gala_complete_table(cpl_table *tab, const int *i,
		const char *galfitfile);

cpl_error_code create_constraintfile_NEW(const char *constraintfile,
		const double *re_max, const double *mag_min, const double *mag_max,
		cpl_table *tab, const long *i);

cpl_error_code create_fittinglist_NEW(struct fitlist *object, cpl_table *tab);

cpl_error_code update_fittinglist_NEW(struct fitlist *obj, cpl_array *done,
		const long *nrow);

int find_tabindex(cpl_table *tab, const int *number);

cpl_error_code update_table_NEW(cpl_table *tab, const char *galfitprefix);

cpl_error_code flag_table(cpl_table *tab, int i, cpl_propertylist *header);

/* Fit the data (x_i, y_i) to the linear relationship

   Y = c0 + c1 x

   returning,

   c0, c1  --  coefficients

   This fit can be used in the case where the errors for the data are
   uknown, but assumed equal for all points. The resulting
   variance-covariance matrix estimates the error in the coefficients
   from the observed variance of the points around the best fit line.
*/

cpl_error_code fit_linear (cpl_array *slopecalc, const int *n, double *c0,
		double *c1);

//***************************************************************************
// Computes the relative position angle of a point in the refernce system
// of an ellipse with a central coordinate an an intrinsic position angle.
//***************************************************************************

double rel_pos_ang(const double *tgt_x, const double *tgt_y,
		const double *ctr_x, const double *ctr_y, const double *ctr_pa);

//***************************************************************************
// A rough approximation for the gamma function.
//***************************************************************************

double gamma(double x);

//***************************************************************************
// Computes the sersic flux at a certain position w.r.t. a source with
// known sersic profile parameters.
//***************************************************************************

double sersic_flux(const double *r, const double *phi, const double *q,
		const double *f0, const double *re, const double *n);

cpl_error_code find_contribtargets_NEW(cpl_table *tab,
		const int *contribmax,    const double *distmax,
		const double *fluxextend, const double *zeropoint,
		const double *magcrit,    const double *magexclude,
		const double *platescale);


/******************************************************************************
 * Checks for a source with table index primindex weather another source
 * with table index ctindex is a contributing source or not.
 *
 * INPUT : cpl_table *tab           Table containing all object information
 * 		   const int *primindex     Table index of primary source
 * 		   const int *ctindex       Table index of testing source
 * 		   const double *magzero    Magnitude zeropoint
 * 		   const double *exptime    Exposure time in seconds
 * 		   const double *magexclude Magnitude difference for excluding objects
 * 		   const double *mgcrit     Magnitude contribution to be contrib target
 *
 * RETURN : 0  if object is a contributing target
 * 			1  if object is not a contributing target
 * 			-1 in case of error
 *****************************************************************************/

int check_contribtarget(cpl_table *tab, const char *object, const long *primindex,
		const long *ctindex, const double *magzero, const double *exptime,
		const double *magexclude, const double *magcrit, const double *fluxextend);

int check_contribtarget_sexdata(cpl_table *tab, const long *primindex,
		const long *ctindex, const double *magzero, const double *exptime,
		const double *magexclude, const double *magcrit,
		const double *fluxextend);

cpl_error_code check_errorstate(cpl_errorstate err_state);

cpl_error_code run_bulge_disc_fitting(cpl_parameterlist *gala_setup);

cpl_error_code check_table_bulge_disc(cpl_table *tab);

cpl_error_code prepare_table_bulge_disc(cpl_table *tab);

cpl_error_code create_bulge_disc_setup(cpl_parameterlist *gala_setup,
		const long *j);

cpl_error_code update_table_bulge_disc(cpl_table *tab, const char *galfitprefix);

cpl_error_code flag_table_bulge_disc(cpl_table *tab, int i,
		cpl_propertylist *header);

cpl_error_code create_constraintfile_bulge_disc(const char *constraintfile_bd,
		const double *re_max, const double *mag_min, const double *mag_max,
		cpl_table *tab, const long *i);

cpl_error_code quantify_residuals(cpl_table *tab, const char *object);

double check_sersic_residual(cpl_table *tab, const long *i,
		const char *object);

double check_2_component_residual(cpl_table *tab, const long *i,
		const char *object);

cpl_error_code run_3comp_fitting(cpl_parameterlist *gala_setup);

cpl_error_code create_3comp_setup(cpl_parameterlist *gala_setup,
		const long *j);

cpl_error_code run_4comp_fitting(cpl_parameterlist *gala_setup);

cpl_error_code create_4comp_setup(cpl_parameterlist *gala_setup,
		const long *j);

cpl_error_code run_5comp_fitting(cpl_parameterlist *gala_setup);

cpl_error_code create_5comp_setup(cpl_parameterlist *gala_setup,
		const long *j);

cpl_error_code distribute_fourier_jobs(cpl_parameterlist *gala_setup);

cpl_error_code GALFIT_fourier_modes(const int *idx,
		int ncomp, cpl_parameterlist *gala_setup);

cpl_error_code write_fourier_results(cpl_parameterlist *gala_setup);

cpl_array *read_fourier_results(const char *galfitim, const int *ncomp);

cpl_array *read_sersic_comp(const char *galfitim, const int *ncomp);

cpl_error_code attach_secondaries(cpl_table *tab,
		cpl_parameterlist *gala_setup,
		const char *setupfile, const int *idx);

cpl_error_code attach_contribtargets(cpl_table *tab,
		cpl_parameterlist *gala_setup,
		const char *setupfile, const long *idx,
		const double *exptime);

double read_exptime(const char *galfitim);

cpl_error_code read_sersic_results(const char *filename,
		cpl_array *sersic_res, int nstar);

cpl_array *read_sersic_comp(const char *galfitim, const int *ncomp);

cpl_array *read_ncomp_results(const char *galfitim, const int *ncomp);

cpl_array *read_header(cpl_propertylist *fitsheader);


#ifdef __cplusplus
}
#endif

/**@}*/



#endif /* GALA_UTILS_H */

#ifdef __cplusplus
}
#endif

/**@}*/
