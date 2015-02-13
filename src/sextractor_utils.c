/*!
 * \ingroup sextractor_utils
 */

/**@{*/

/*!
 * \callgraph
 *
 * \file sextractor_utils.c
 *
 * \brief Utilities for interfacing with SExtractor.
 *
 * \author Marco Barden
 */

#include "galapagos_utils.h"
#include "sextractor_utils.h"
#include <math.h>

cpl_table *su_reqcols(void) {
    static cpl_table *tab;

    tab = cpl_table_new(0);

    cpl_table_new_column(tab, "NUMBER",      CPL_TYPE_INT);
    cpl_table_new_column(tab, "X_IMAGE",     CPL_TYPE_DOUBLE);
    cpl_table_new_column(tab, "Y_IMAGE",     CPL_TYPE_DOUBLE);
    cpl_table_new_column(tab, "CXX_IMAGE",   CPL_TYPE_DOUBLE);
    cpl_table_new_column(tab, "CYY_IMAGE",   CPL_TYPE_DOUBLE);
    cpl_table_new_column(tab, "CXY_IMAGE",   CPL_TYPE_DOUBLE);
    cpl_table_new_column(tab, "THETA_IMAGE", CPL_TYPE_DOUBLE);
    cpl_table_new_column(tab, "THETA_WORLD", CPL_TYPE_DOUBLE);
    cpl_table_new_column(tab, "ELLIPTICITY", CPL_TYPE_DOUBLE);
    cpl_table_new_column(tab, "KRON_RADIUS", CPL_TYPE_DOUBLE);
    cpl_table_new_column(tab, "A_IMAGE",     CPL_TYPE_DOUBLE);
    cpl_table_new_column(tab, "B_IMAGE",     CPL_TYPE_DOUBLE);
    cpl_table_new_column(tab, "ALPHA_J2000", CPL_TYPE_DOUBLE);
    cpl_table_new_column(tab, "DELTA_J2000", CPL_TYPE_DOUBLE);
    cpl_table_new_column(tab, "BACKGROUND",  CPL_TYPE_DOUBLE);

    return tab;
}

cpl_type su_reqcoltypes(const char *col) {
    char str[FILENAME_MAX];

    cpl_type coltype;

    sprintf(str, "%s", col);
    strtoupper(str);

    if        (strcmp(str, "NUMBER") == 0) {
        // INT columns
        coltype = CPL_TYPE_INT;
    } else if (strcmp(str, "STRINGCOL") == 0) {
        // STRING columns
        coltype = CPL_TYPE_STRING;
    } else {
        // COUBLE columns
        coltype = CPL_TYPE_DOUBLE;
    }

    return coltype;
}

cpl_error_code su_read_par(cpl_table *tab, const char *parfile,
                           const cpl_table *addcols, cpl_boolean addreqcols) {
    FILE *fp;

    char line[FILENAME_MAX];

    const char *col_name = NULL;

    cpl_type col_type;

    cpl_table *reqcols = su_reqcols();       // required columns

    cpl_array *col_names = NULL;

    int i,
        n_add;                               // # of additional columns

    // add required columns
    if (addreqcols == CPL_TRUE) {
        tab = cpl_table_duplicate(reqcols);
    }

    // add additional columns
    if (addcols != NULL) {
        col_names = cpl_table_get_column_names(addcols);
        n_add = cpl_table_get_ncol(addcols);

        for (i = 0; i < n_add; i++) {      // loop over all additional columns
            // get column name & type
            col_name = cpl_array_get_string(col_names, i);
            col_type = cpl_table_get_column_type(addcols, col_name);

            // add column if not exist
            if (cpl_table_has_column(tab, col_name) == 0) {
                cpl_table_new_column(tab, col_name, col_type);
            }
        }
    }

    // read param-file
    fp = fopen(parfile, "r");

    if (fp == NULL) {
        cpl_table_delete(reqcols);
        cpl_array_delete(col_names);
        return cpl_error_set_message(cpl_func, CPL_ERROR_FILE_NOT_FOUND,
                                     "%s not found", parfile);
    }

    initialise_string(line, FILENAME_MAX);

    // read individual lines in param-file
    while (fgets(line, FILENAME_MAX - 1, fp) != NULL) {
        // Skip comments and empty lines
        if ((line[0] == '#') || (strlen(line) == 0) || (line[0] == '\n')) {
            continue;
        }

        strtrim_inplace(line);
        strtoupper(line);
        if (cpl_table_has_column(tab, line) == 0) {
            cpl_table_new_column(tab, line, su_reqcoltypes(line));
        }
    }

    fclose(fp);

    // clean-up
    cpl_table_delete(reqcols);
    cpl_array_delete(col_names);

    return CPL_ERROR_NONE;
}


cpl_error_code su_read_sextab(cpl_table *tab, const char *datafile) {
    FILE *fp;

    cpl_array *col_names = NULL;

    cpl_type col_type;

    char line[FILENAME_MAX];
    char *str = NULL;
    const char *col_name = NULL;

    int i, j,
        n_col;

    // read param-file

    fp = fopen(datafile, "r");

    if (fp == NULL) {
        cpl_array_delete(col_names);
        return cpl_error_set_message(cpl_func, CPL_ERROR_FILE_NOT_FOUND,
                                     "%s not found", datafile);
    }

    initialise_string(line, FILENAME_MAX);

    n_col = cpl_table_get_ncol(tab);
    col_names = cpl_table_get_column_names(tab);

    // read individual lines in param-file
    j = 0;
    while (fgets(line, FILENAME_MAX - 1, fp) != NULL) {
        // Skip comments and empty lines
        if ((line[0] == '#') || (strlen(line) == 0) || (line[0] == '\n')) {
            continue;
        }

        cpl_table_set_size(tab, j+1);

        // get first token
        str = strtok(line, "\t ");
        for (i = 0; str != NULL && i < n_col; i++) {

        	// Remove leading and trailing blanks from string.

            strtrim_inplace(str);

            // get column name and corresponding column data type
            col_name = cpl_array_get_string(col_names, i);
            col_type = su_reqcoltypes(col_name);

            switch(col_type) {
            case CPL_TYPE_STRING:
                cpl_table_set_string(tab, col_name, j, str);
                break;
            case CPL_TYPE_INT:
                cpl_table_set_int(tab, col_name, j, atoi(str));
                break;
            default:
                cpl_table_set_double(tab, col_name, j, atof(str));
                break;
            }

            str = strtok(NULL, "\t ");
        }

        if (i != n_col) {
            cpl_array_delete(col_names);
            return cpl_error_set_message(cpl_func,
                                         CPL_ERROR_INCOMPATIBLE_INPUT,
                                         "SExtractor Table: %s must have "
                                         "same number of columns as "
                                         ".param-file.", datafile);
        }
        j++;
    }

    fclose(fp);

    cpl_array_delete(col_names);

    return CPL_ERROR_NONE;
}


cpl_error_code gala_run_sextractor(cpl_table *outtab, const char *sexexe,
		const char *sexsetup, const char *cat, const char *outpar,
		const char *image, const char *seg, const char *weight,
		const char *check, const char *chktype, const double *zerop,
		cpl_boolean chk, cpl_boolean dryrun, const int *multi) {

	cpl_propertylist *header;

	int i, n, rank, debug = 0;
	double med_val,
		   zp_eff,
		   exptime;
    char str[FILENAME_MAX];
    char *strp = NULL;

	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

// image header and magnitude zeropoint

    header = cpl_propertylist_load(image, 0); // read fits header
    if (header == NULL) {
        // image not found
        cpl_propertylist_delete(header);
        printf("In run_sextractor(): Image header "
        		"not found for image %s!\n", image);

        return cpl_error_set_message(cpl_func, CPL_ERROR_FILE_NOT_FOUND,
                                     "%s not found", image);
    }

//    if (exptime == -1) {
        exptime = cpl_propertylist_get_double(header, "EXPTIME");
//    }
    zp_eff = *zerop + 2.5*log10(exptime);

    cpl_msg_info(cpl_func, "Using exptime: %lfs (zp=%lf) for: %s",
                 exptime, zp_eff, image);

// check image

	if (chk == CPL_TRUE) {
		cpl_msg_info(cpl_func, "Starting SExtractor check image: %s\n", image);
		initialise_string(str, FILENAME_MAX);
		strp = rem_ext(check, '.', '/');
		sprintf(str, "%s %s -c %s -CATALOG_NAME %s -CATALOG_TYPE ASCII "
                "-PARAMETERS_NAME %s -WEIGHT_IMAGE %s "
                "-WEIGHT_TYPE MAP_WEIGHT -MAG_ZEROPOINT %lf "
                "-CHECKIMAGE_TYPE %s -CHECKIMAGE_NAME %s.%iTEST.fits",
                sexexe, image, sexsetup, cat, outpar, weight,
                zp_eff, chktype, strp, *multi);
		free(strp);

		if(debug == 1) {
			printf("SExtractor CHECK IMAGE startet mit : %s\n", str);
		}

		if (dryrun == CPL_FALSE) {
			if (system(str) != 0) {
				cpl_propertylist_delete(header);

				return cpl_error_set_message(cpl_func, CPL_ERROR_UNSPECIFIED,
                                             "Problem with SExtractor");
			}
		}
	}

// SExtractor run

	cpl_msg_info(cpl_func, "Starting %s SExtractor run: %s\n", sexsetup, image);
	initialise_string(str, FILENAME_MAX);

	sprintf(str, "%s %s -c %s -CATALOG_NAME %s -CATALOG_TYPE ASCII "
			"-PARAMETERS_NAME %s -WEIGHT_IMAGE %s "
            "-WEIGHT_TYPE MAP_WEIGHT -MAG_ZEROPOINT %lf "
            "-CHECKIMAGE_TYPE segmentation -CHECKIMAGE_NAME %s",
            sexexe, image, sexsetup, cat, outpar, weight, zp_eff, seg);

	if(debug == 1) {
		printf("SExtractor start mit : %s\n", str);
	}

	if (dryrun == CPL_FALSE) {
		if (system(str) != 0) {
			cpl_propertylist_delete(header);

			return cpl_error_set_message(cpl_func, CPL_ERROR_UNSPECIFIED,
                                         "Problem with SExtractor");
		}
	}


//read in catalogue

	if (su_read_par(outtab, outpar, NULL, CPL_FALSE) != CPL_ERROR_NONE) {
		cpl_propertylist_delete(header);

		return cpl_error_set_message(cpl_func, CPL_ERROR_UNSPECIFIED,
	                                     "su_read_par() failed");
	}

	if (su_read_sextab(outtab, cat) != CPL_ERROR_NONE) {
		cpl_propertylist_delete(header);
		printf("error with tab\n");

		return cpl_error_set_message(cpl_func, CPL_ERROR_UNSPECIFIED,
	                                     "su_read_sextab() failed");
	}

// replace bad kron_radii

	med_val = cpl_table_get_column_median(outtab, "KRON_RADIUS");
	if (med_val == 0) {
		cpl_propertylist_delete(header);

		return cpl_error_set_message(cpl_func, CPL_ERROR_ILLEGAL_INPUT,
	                                     "Kron_radius is always 0 in cold_cat: "
	                                     "%s", cat);
	}

	n = cpl_table_get_nrow(outtab);
	for (i = 0; i < n; i++) {
		if (cpl_table_get_double(outtab, "KRON_RADIUS", i, NULL) == 0) {
			cpl_table_set_double(outtab, "KRON_RADIUS", i, med_val);
		}
	}

	cpl_propertylist_delete (header);

	return CPL_ERROR_NONE;

	}


cpl_error_code gala_merge_tables (cpl_table *tab1, cpl_table *tab2,
		const char *seg1, const char *seg2, const char *outseg,
		const char *cat1, const char *cat2, double *enlarge,
		cpl_boolean outonly) {

	int n1, n2, nx, ny, npix, offset, num, i, j, debug = 0;
	int *p1, *p2;
	double run1_x, run1_y, run2_x, run2_y, a, b, theta, R;
	double pi = 3.14159265;

	cpl_propertylist *hd1;
	cpl_propertylist *hd2;
	cpl_propertylist *list;

	cpl_boolean sortval = CPL_FALSE,
			    inside;

	cpl_image *seg_im1;
	cpl_image *seg_im2;

	cpl_errorstate err_state;

    // get error state
    err_state = cpl_errorstate_get();

    //calculate ellipse parameters

    cpl_table_new_column(tab1, "CXX_NORM", CPL_TYPE_DOUBLE);
    cpl_table_copy_data_double(tab1, "CXX_NORM",
                        cpl_table_get_data_double(tab1, "CXX_IMAGE"));
    cpl_table_divide_columns(tab1, "CXX_NORM", "KRON_RADIUS");
    cpl_table_divide_columns(tab1, "CXX_NORM", "KRON_RADIUS");
    cpl_table_new_column(tab1, "CYY_NORM", CPL_TYPE_DOUBLE);
    cpl_table_copy_data_double(tab1, "CYY_NORM",
                        cpl_table_get_data_double(tab1, "CYY_IMAGE"));
    cpl_table_divide_columns(tab1, "CYY_NORM", "KRON_RADIUS");
    cpl_table_divide_columns(tab1, "CYY_NORM", "KRON_RADIUS");
    cpl_table_new_column(tab1, "CXY_NORM", CPL_TYPE_DOUBLE);
    cpl_table_copy_data_double(tab1, "CXY_NORM",
                        cpl_table_get_data_double(tab1, "CXY_IMAGE"));
    cpl_table_divide_columns(tab1, "CXY_NORM", "KRON_RADIUS");
    cpl_table_divide_columns(tab1, "CXY_NORM", "KRON_RADIUS");

    cpl_table_new_column(tab2, "CXX_NORM", CPL_TYPE_DOUBLE);
    cpl_table_copy_data_double(tab2, "CXX_NORM",
                        cpl_table_get_data_double(tab2, "CXX_IMAGE"));
    cpl_table_divide_columns(tab2, "CXX_NORM", "KRON_RADIUS");
    cpl_table_divide_columns(tab2, "CXX_NORM", "KRON_RADIUS");
    cpl_table_new_column(tab2, "CYY_NORM", CPL_TYPE_DOUBLE);
    cpl_table_copy_data_double(tab2, "CYY_NORM",
                        cpl_table_get_data_double(tab2, "CYY_IMAGE"));
    cpl_table_divide_columns(tab2, "CYY_NORM", "KRON_RADIUS");
    cpl_table_divide_columns(tab2, "CYY_NORM", "KRON_RADIUS");
    cpl_table_new_column(tab2, "CXY_NORM", CPL_TYPE_DOUBLE);
    cpl_table_copy_data_double(tab2, "CXY_NORM",
                        cpl_table_get_data_double(tab2, "CXY_IMAGE"));
    cpl_table_divide_columns(tab2, "CXY_NORM", "KRON_RADIUS");
    cpl_table_divide_columns(tab2, "CXY_NORM", "KRON_RADIUS");

    //load segmentation images and header

    seg_im1 = cpl_image_load(seg1, CPL_TYPE_INT, 0, 0);
    hd1 = cpl_propertylist_load(seg1, 0); // read fits header

    seg_im2 = cpl_image_load(seg2, CPL_TYPE_INT, 0, 0);
    hd2 = cpl_propertylist_load(seg2, 0); // read fits header

   // Loop over each element in tab2 and compare its distance to each
   // element in tab 1:

    n1 = cpl_table_get_nrow(tab1);
    n2 = cpl_table_get_nrow(tab2);

	cpl_table_unselect_all(tab2);

    for (i = 0; i < n2; i++) {
        for (j = 0; j < n1; j++) {

            a      = cpl_table_get_double(tab1, "A_IMAGE",     j, NULL);
            b      = cpl_table_get_double(tab1, "B_IMAGE",     j, NULL);
            R      = cpl_table_get_double(tab1, "KRON_RADIUS", j, NULL);
            theta  = cpl_table_get_double(tab1, "THETA_IMAGE", j, NULL);
			theta = 2 * pi * theta / 360;
            run2_x = cpl_table_get_double(tab2, "X_IMAGE",     i, NULL);
            run2_y = cpl_table_get_double(tab2, "Y_IMAGE",     i, NULL);
            run1_x = cpl_table_get_double(tab1, "X_IMAGE",     j, NULL);
            run1_y = cpl_table_get_double(tab1, "Y_IMAGE",     j, NULL);

            // Every object detected in the next hotter run with its center
            // placed within an elliptic radius specified by "enlarge"
            // will be removed from the catalog

            a = a * R * *enlarge;
            b = b * R * *enlarge;

            inside = point_ellipse(&run2_x, &run2_y, &run1_x, &run1_y, &a,
            		&b, &theta);

            if (inside == CPL_TRUE) {
                cpl_table_select_row(tab2, i);
            }
        }
    }

    cpl_table_erase_selected(tab2);

    n2 = cpl_table_get_nrow(tab2);
    if (n2 == 0) {
    	cpl_msg_info(cpl_func, "All objects contained in cold catalogue");
    	return CPL_ERROR_NONE;
    }

    //renumber remaining catalogue elements and add segmentation images

    if(debug == 1) {
    	cpl_msg_info(cpl_func, "Working on segmentation image.");
    }

    offset = cpl_table_get_column_max(tab1, "NUMBER") + 1;

    // get number of pixels
    nx = cpl_image_get_size_x(seg_im2);
    ny = cpl_image_get_size_y(seg_im2);
    npix = nx * ny;

    p1 = cpl_image_get_data_int(seg_im1);
    p2 = cpl_image_get_data_int(seg_im2);

    for (i = 0; i < n2; i++) {

    	num = cpl_table_get_int(tab2, "NUMBER", i, NULL);

    	for (j = 0; j < npix; j++) {
    		if (*(p2+j) == num) {
    			// prefer hot pixels in output segmentation map
    			*(p1+j) = offset + i;
    		}
    	}

//    	printf("Object done!! %d\n", i + 1);

    	cpl_table_set_int(tab2, "NUMBER", i, offset + i);
    }

    cpl_image_save(seg_im1, outseg, CPL_BPP_32_SIGNED, hd1,
                   CPL_IO_CREATE);

    cpl_table_insert(tab1, tab2, n1);

	// Sort table according to magnitude

	list = cpl_propertylist_new();
	cpl_propertylist_append_bool(list, "MAG_BEST", sortval);
	cpl_table_sort(tab1, list);
	cpl_propertylist_delete(list);

    remove(seg2);

    if(outonly == CPL_TRUE) {
    	remove(cat2);
    }

    cpl_propertylist_delete(hd1);
    cpl_propertylist_delete(hd2);
    cpl_image_delete(seg_im1);
    cpl_image_delete(seg_im2);


    if ((err_state = cpl_errorstate_get()) != CPL_ERROR_NONE) {
    	return cpl_error_set_message(cpl_func, CPL_ERROR_UNSPECIFIED,
    			                     "Undefined error");
    }

    return CPL_ERROR_NONE;
}


// band_size = -1 for default band_size = 2

cpl_error_code create_checkimage(const char *file, const char *cat,
		const char *image) {

	int i, x, y, s, t, z, xlo, ylo, xhi, yhi, minor, major, debug = 0;

	double grh, klh, cxx, cxy, cyy, xc, theta, gh, kh, cxxg, cyyg, cxyg,
		   aim, bim, yc, R, Rad = 1, background, pi = 3.14159265, xfac, yfac,
		   rad, sizefac = 18, ang, band_size = 2;

	cpl_image *galaxy = NULL;
	cpl_table *tab;


	galaxy = cpl_image_load(image, CPL_TYPE_DOUBLE, 0, 0);
	tab = cpl_table_load(cat, 1, 0);

	s = cpl_image_get_size_x(galaxy);

	t = cpl_image_get_size_y(galaxy);

	z = cpl_table_get_nrow(tab);

	for(i = 0; i < z; i++) {
		cxx = cpl_table_get_double(tab,        "CXX_IMAGE",   i, NULL);
		cyy = cpl_table_get_double(tab,        "CYY_IMAGE",   i, NULL);
		cxy = cpl_table_get_double(tab,        "CXY_IMAGE",   i, NULL);
		xc  = cpl_table_get_double(tab,        "X_IMAGE",     i, NULL);
		yc  = cpl_table_get_double(tab,        "Y_IMAGE",     i, NULL);
		R   = cpl_table_get_double(tab,        "KRON_RADIUS", i, NULL);
		aim = cpl_table_get_double(tab,        "A_IMAGE",     i, NULL);
		bim = cpl_table_get_double(tab,        "B_IMAGE",     i, NULL);
		theta = cpl_table_get_double(tab,      "THETA_IMAGE", i, NULL);
		background = cpl_table_get_double(tab, "BACKGROUND",  i, NULL);
		if(background == 0) {
			background = 300;
		}

		// deg -> rad

		theta = 2 * pi * theta / 360;
		background = round(background);

		// Calculating semi-half major - and semi-half minor axis :
		// look at http://www.astromatic.net/forum/showthread.php?tid=347

		grh = aim * R;
		klh = bim * R;

		// Parameter inner ellpise annuli

		cxx = (cos(theta) * cos(theta)) / pow(grh, 2) +
			  (sin(theta) * sin(theta)) / pow(klh, 2);
		cyy = sin(theta) * sin(theta) / pow(grh, 2) +
			  cos(theta) * cos(theta) / pow(klh, 2);
		cxy = 2 * cos(theta) * sin(theta) * (1 / pow(grh, 2) - 1 / pow(klh, 2));

		// Checking band_size

		if(band_size == -1) {
			band_size = 2;
		}

		if(band_size < 0) {
	    	return cpl_error_set_message(cpl_func, CPL_ERROR_ILLEGAL_INPUT,
	    	                             "Illegal input for band_size!");
		}

		// Parameter outer ellipse annuli

		// Adding equal values to each major-axis to not strech the ellipse
		// but creating annuli with constant band sizes

		gh = grh + band_size;
		kh = klh + band_size;

		cxxg = cos(theta) * cos(theta) / pow(gh, 2) +
			   sin(theta) * sin(theta) / pow(kh, 2);
		cyyg = sin(theta) * sin(theta) / pow(gh, 2) +
			   cos(theta) * cos(theta) / pow(kh, 2);
		cxyg = 2 * cos(theta) * sin(theta) * (1 / pow(gh, 2) - 1 / pow(kh, 2));

		// Loop in every postage stamp

		rad = cpl_table_get_double(tab, "A_IMAGE", i, NULL) *
		      cpl_table_get_double(tab, "KRON_RADIUS", i, NULL);

		ang = cpl_table_get_double(tab, "THETA_IMAGE", i, NULL);
		ang = 2 * pi * ang / 360;

		xfac = rad * (fabs(sin(ang) +
		       (1 - cpl_table_get_double(tab, "ELLIPTICITY", i, NULL)) *
		       fabs(cos(ang)))) * sizefac;

		yfac = rad * (fabs(cos(ang) +
		       (1 - cpl_table_get_double(tab, "ELLIPTICITY", i, NULL)) *
		       fabs(sin(ang)))) * sizefac;

		major = 0.5 * (xfac + yfac + fabs(xfac - yfac));
		minor = 0.5 * (xfac + yfac - fabs(xfac - yfac));


		if(theta > 180) {
		    theta = theta - 180;
		}
		if(theta > 90) {
			theta = theta - 180;
		}
		if(fabs(theta) < 45) {
		    xfac = major;
		    yfac = minor;
		} else {
		    xfac = minor;
		    yfac = major;
		}

		xlo = round(cpl_table_get_double(tab, "X_IMAGE", i, NULL) - xfac);
		xhi = round(cpl_table_get_double(tab, "X_IMAGE", i, NULL) + xfac);
		ylo = round(cpl_table_get_double(tab, "Y_IMAGE", i, NULL) - yfac);
		yhi = round(cpl_table_get_double(tab, "Y_IMAGE", i, NULL) + yfac);

		if(xlo < 0) {
		     xlo = 1;
		}
		if(xhi > s) {
		    xhi = s;
		}
		if(ylo < 0) {
		    ylo = 1;
		}
		if(yhi > t) {
		    yhi = t;
		}

		for(x = xlo; x < xhi; x++) {
			for(y = ylo; y < yhi; y++) {

				if(cxx * ((x - xc) * (x - xc)) + cyy * ((y - yc) * (y - yc)) +
				   cxy * (x - xc) * (y - yc) > Rad * Rad &&
				   cxxg * ((x - xc) * (x - xc)) + cyyg * ((y - yc) * (y - yc))+
				   cxyg * (x - xc) * (y - yc) < Rad * Rad) {

				   cpl_image_set(galaxy, x, y, 30 * background);
				}
			}
		}
	}

	if(debug == 1) {
		printf("File in create checkimage : %s\n", file);
	}

	cpl_image_save(galaxy, file, CPL_BPP_IEEE_DOUBLE, NULL, CPL_IO_CREATE);

	cpl_table_delete(tab);
	cpl_image_delete(galaxy);

	return CPL_ERROR_NONE;
}

/**@}*/
