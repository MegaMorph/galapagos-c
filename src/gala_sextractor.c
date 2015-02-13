/*!
 * \ingroup galapagos
 */

/**@{*/

/*!
 * \callgraph
 *
 * \file gala_sextractor.c
 *
 * \brief GALAPAGOS routine for executing SExtractor.
 *
 * \author Marco Barden
 */

#include "gala_sextractor.h"

cpl_error_code gala_sextractor(cpl_parameterlist *sex_setup) {

    cpl_table *sextab = NULL,
              *reqcols = NULL,
              *tab1 = NULL,
              *tab2 = NULL,
              *outtab = NULL;

    cpl_array *col_names = NULL,
    		  *sexsetupar = NULL,
    		  *catar = NULL,
    		  *segar = NULL;

    cpl_parameter *p;

    cpl_boolean flag = CPL_FALSE,
                chk = CPL_TRUE,
                outonly = CPL_TRUE,
                dryrun = CPL_FALSE,
                sortval = CPL_FALSE,
                magsort = CPL_TRUE;

    cpl_propertylist *list;

    FILE *fp = NULL, *fp_r = NULL;

    char seg1[FILENAME_MAX],
    	 seg2[FILENAME_MAX],
    	 cat1[FILENAME_MAX],
    	 cat2[FILENAME_MAX],
    	 sexsetup[FILENAME_MAX],
         cat[FILENAME_MAX],
         seg[FILENAME_MAX],
         sex_par[FILENAME_MAX],
         outpar[FILENAME_MAX],
         image[FILENAME_MAX],
         outseg[FILENAME_MAX],
         out_tab[FILENAME_MAX],
         sexexe[FILENAME_MAX],
         weight[FILENAME_MAX],
         check[FILENAME_MAX],
         chkst[FILENAME_MAX],
         chktype[FILENAME_MAX],
         directory[FILENAME_MAX],
         tile[FILENAME_MAX],
         tmp[FILENAME_MAX],
         str[FILENAME_MAX],
         tiletab[FILENAME_MAX],
         checkdir[FILENAME_MAX],
    	 outsegdir[FILENAME_MAX];

    char *p1, *p2, *p3;
    char tiledir[FILENAME_MAX] = "mkdir ";

    int multi = 0, n, i, k, l, m, j, debug = 0;

    double enlarge,
    	   zerop;

    struct stat st;

    /*************************************************************************
     * extract setup parameters
     ************************************************************************/

    p = cpl_parameterlist_find(sex_setup, "setup");
    sprintf(sexsetup, "%s", cpl_parameter_get_string(p));
    p = cpl_parameterlist_find(sex_setup, "cat");
    sprintf(cat, "%s", cpl_parameter_get_string(p));
    p = cpl_parameterlist_find(sex_setup, "seg");
    sprintf(seg, "%s", cpl_parameter_get_string(p));
    p = cpl_parameterlist_find(sex_setup, "sex_par");
    sprintf(sex_par, "%s", cpl_parameter_get_string(p));
    p = cpl_parameterlist_find(sex_setup, "out_par");
    sprintf(outpar, "%s", cpl_parameter_get_string(p));
    p = cpl_parameterlist_find(sex_setup, "image");
    sprintf(image, "%s", cpl_parameter_get_string(p));
    p = cpl_parameterlist_find(sex_setup, "out_seg");
    sprintf(outseg, "%s", cpl_parameter_get_string(p));
    p = cpl_parameterlist_find(sex_setup, "out_tab");
    sprintf(out_tab, "%s", cpl_parameter_get_string(p));
    p = cpl_parameterlist_find(sex_setup, "sexexe");
    sprintf(sexexe, "%s", cpl_parameter_get_string(p));
    p = cpl_parameterlist_find(sex_setup, "weightimage");
    sprintf(weight, "%s", cpl_parameter_get_string(p));
    p = cpl_parameterlist_find(sex_setup, "check");
    sprintf(check, "%s", cpl_parameter_get_string(p));
    p = cpl_parameterlist_find(sex_setup, "chktype");
    sprintf(chktype, "%s", cpl_parameter_get_string(p));
    p = cpl_parameterlist_find(sex_setup, "enlarge");
    enlarge = cpl_parameter_get_double(p);
    p = cpl_parameterlist_find(sex_setup, "zerop");
    zerop = cpl_parameter_get_double(p);
    p = cpl_parameterlist_find(sex_setup, "chkim");
    sprintf(chkst, "%s", cpl_parameter_get_string(p));
    p = cpl_parameterlist_find(sex_setup, "suffix");
    sprintf(tile, "%s", cpl_parameter_get_string(p));
    strtok(tile, ".");
    strtok(NULL, ".");
    p = cpl_parameterlist_find(sex_setup, "directory");
    sprintf(directory, "%s", cpl_parameter_get_string(p));
    if(strcmp(chkst, "yes") == 0) {
    	chk = CPL_TRUE;
    } else {
    	chk = CPL_FALSE;
    }

    //separate the path string and read into cpl_array

    sexsetupar = cpl_array_new (0, CPL_TYPE_STRING);
    catar = cpl_array_new (0, CPL_TYPE_STRING);
    segar = cpl_array_new (0, CPL_TYPE_STRING);

    p1 = strtok(sexsetup, " ");
    for (i = 0; p1 != NULL; i++) {
    	cpl_array_set_size(sexsetupar, i + 1);
    	cpl_array_set_string(sexsetupar, i, p1);
   		p1 = strtok(NULL, " ");
    }

    p2 = strtok(cat, " ");
    for (i = 0; p2 != NULL; i++) {
    	cpl_array_set_size(catar, i + 1);
    	cpl_array_set_string(catar, i, p2);
   		p2 = strtok(NULL, " ");
    }

    p3 = strtok(seg, " ");
    for (i = 0; p3 != NULL; i++) {
    	cpl_array_set_size(segar, i + 1);
    	cpl_array_set_string(segar, i, p3);
   		p3 = strtok(NULL, " ");
    }

    // Check user input

    k = cpl_array_get_size(sexsetupar);
    l = cpl_array_get_size(catar);
    m = cpl_array_get_size(segar);

    if (k != l || k != m) {
    	return cpl_error_set_message(cpl_func, CPL_ERROR_INCOMPATIBLE_INPUT ,
    	                             "Mismatching number of input files!");
    }

    for(i = 0; i < k; i++) {
    	sprintf(tmp, "%s", cpl_array_get_string(sexsetupar, i));
    	if(filecheck(tmp) != CPL_ERROR_NONE) {
    		cpl_msg_error(cpl_func, "SExtractor input files %s not found!",
    				tmp);
    		return CPL_ERROR_FILE_NOT_FOUND;
    	}
    }

    // get required columns
    reqcols = su_reqcols();

    // see if check image requested
    sprintf(str, "%s", chktype);
    strtolower(str);
    if (strcmp(str, "none") == 0) {
        chk = CPL_FALSE;
    }

    /*************************************************************************
     * identify setup: get number of input files
     ************************************************************************/

    multi = cpl_array_get_size(sexsetupar);

    if (multi == 0) {
        // no input files
        cpl_table_delete(outtab);
        cpl_table_delete(sextab);
        cpl_table_delete(reqcols);
        cpl_array_delete(col_names);

        return cpl_error_set_message(cpl_func, CPL_ERROR_FILE_NOT_FOUND,
                                     "No (%s) SExtractor setup-files found",
                                     sexsetup);
    }

    /*************************************************************************
     * create parameter-file for output
     ************************************************************************/

    // write required column names
    col_names = cpl_table_get_column_names(reqcols);
    n = cpl_array_get_size(col_names);

    // Multiple processes must be synchronized

    fp = fopen(outpar, "w");
    if(fp == NULL) {
    	cpl_table_delete(outtab);
    	cpl_table_delete(sextab);
    	cpl_table_delete(reqcols);
    	cpl_array_delete(col_names);
    	return cpl_error_set_message(cpl_func, CPL_ERROR_FILE_NOT_FOUND,
    	                                    "%s not found", outpar);
    }

    for (i = 0; i < n; i++) {
    	fprintf(fp, "%s\n", cpl_array_get_string(col_names, i));
    }

    // XXX Nochmal überdenken für mehrere Bilder gleichzeitig!

//    if(*id < *numprocs) {
//    	MPI_Barrier(MPI_COMM_WORLD);
//    }
//
//	// Synchronize processors
//
//    printf("Prozess Nummer %d : Bin vor der 1. Synchronisation!\n");
//
//	if(*id == 0) {
//		file_done = 1;
//		for(i = 1; i < *numprocs; i++) {
//			MPI_Send(&file_done, sizeof(int), MPI_INT, i, 111, MPI_COMM_WORLD);
//		}
//	} else {
//		if(access(outpar, 00) != 0) {
//			MPI_Recv(&file_done, sizeof(int), MPI_INT, 0, 111, MPI_COMM_WORLD, &status);
//		}
//	}
//
//    printf("Prozess Nummer %d : Bin HINTER der 1. Synchronisation!\n");

    // write additional requested column names
    fp_r = fopen(sex_par, "r");

    if (fp_r == NULL) {
        // SExtractor parameter-file not found
        cpl_table_delete(outtab);
        cpl_table_delete(sextab);
        cpl_table_delete(reqcols);
        cpl_array_delete(col_names);

        return cpl_error_set_message(cpl_func, CPL_ERROR_FILE_NOT_FOUND,
                                     "%s not found", sex_par);
    }

    initialise_string(str, FILENAME_MAX);
    while (fgets(str, FILENAME_MAX - 1, fp_r) != NULL) {
        strtrim_inplace(str);
        strtoupper(str);
        // do not duplicate entries
        for (j = 0, flag = CPL_FALSE; j < n; j++) {
            if (strcmp(str, cpl_array_get_string(col_names, j)) == 0) {
                flag = CPL_TRUE;
                break;
            }
        }
        if (flag == CPL_FALSE) {
            fprintf(fp, "%s\n", str);
        }
    }

    fclose(fp);

//	// Synchronize processors
//
//    printf("Prozess Nummer %d : Bin vor der 2. Synchronisation!\n");
//
//	if(*id == 0) {
//		file_done = 2;
//		for(i = 1; i < *numprocs; i++) {
//			MPI_Send(&file_done, sizeof(int), MPI_INT, i, 112, MPI_COMM_WORLD);
//		}
//	} else {
//		if(access(outpar, 00) != 0) {
//			MPI_Recv(&file_done, sizeof(int), MPI_INT, 0, 112, MPI_COMM_WORLD, &status);
//		}
//	}
//
//    printf("Prozess Nummer %d : Bin HINTER der 2. Synchronisation!\n");

    // XXX s.o.
//    if(*id < *numprocs) {
//    	MPI_Barrier(MPI_COMM_WORLD);
//    }

    fclose(fp_r);

    /*************************************************************************
     * run SExtractor for each setup file and merge tables
     ************************************************************************/

    tab1 = cpl_table_new(0);

    sprintf (cat1, "%s%s", directory, cpl_array_get_string (catar, 0));
	sprintf (seg1, "%s%s", directory, cpl_array_get_string (segar, 0));
	sprintf (sexsetup, "%s", cpl_array_get_string (sexsetupar, 0));

    fp = fopen(sexsetup, "r");
    if (fp != NULL) {
    	fclose(fp);
    } else {
        return cpl_error_set_message(cpl_func, CPL_ERROR_FILE_NOT_FOUND,
                "%s not found", sexsetup);         // file does not exist
    }

    // Create output directories for every tile according to setup file

    strcat(tiledir, directory);

    if(stat(directory,&st) != 0) {
        if(system(tiledir) != 0) {
			cpl_msg_error(cpl_func, "System call in gala_sextractor() "
					"failed!\n");
		}
    }

    // Check if directory name is valid. How?

    if(stat(directory,&st) != 0) {
    	cpl_msg_error(cpl_func, "Could not create directory %s!\n",
    			directory);
    	return CPL_ERROR_ILLEGAL_INPUT;
    }

    // Prepare path for segmentation image file

    sprintf(outsegdir, "%s%s", directory, outseg);

    i = 0;

//    printf("PROCESS %d : START GALA_RUN_SEXTRACTOR()!\n" *id);
//    if(access(outpar, 00) != 0) {
//    	printf("Habe Zugang zu outpar : %s\n", outpar);
//    } else {
//    	printf("Habe KEINEN Zugang zu outpar : %s\n", outpar);
//    }

	gala_run_sextractor(tab1, sexexe, sexsetup, cat1, outpar, image,
						seg1, weight, check, chktype, &zerop, chk, dryrun,
						&i);

    for (i = 1; i < multi; i++) {
    	tab2 = cpl_table_new(0);

    	sprintf (cat2, "%s%s", directory, cpl_array_get_string (catar, i));
    	sprintf (seg2, "%s%s", directory, cpl_array_get_string (segar, i));
    	sprintf (sexsetup, "%s", cpl_array_get_string (sexsetupar, i));

    	fp = fopen(sexsetup, "r");
        if (fp != NULL) {
        	fclose(fp);
        } else {
            return cpl_error_set_message(cpl_func, CPL_ERROR_FILE_NOT_FOUND,
                    "%s not found", sexsetup);        // file does not exist
        }

        gala_run_sextractor(tab2, sexexe, sexsetup, cat2, outpar, image,
    						seg2, weight, check, chktype, &zerop, chk, dryrun, &i);

        if(debug == 1) {

        	printf("VOR MERGING TABLES : nROW TAB1 : %d\nnROW TAB2 : %d\n",
        			(int)cpl_table_get_nrow(tab1),
        			(int)cpl_table_get_nrow(tab2));

        	printf("SEG1 %s  SEG2 %s OUTSEGDIR %s CAT1 %s CAT2 %s\n",
        			seg1, seg2, outsegdir, cat1, cat2);
        }

    	gala_merge_tables (tab1, tab2, seg1, seg2, outsegdir,
    				   	   cat1, cat2, &enlarge, outonly);

        if(debug == 1) {

        	printf("NACH MERGING TABLES : nROW TAB1 : %d\nnROW TAB2 : %d\n",
        			(int)cpl_table_get_nrow(tab1),
        			(int)cpl_table_get_nrow(tab2));
        }

    	cpl_table_delete (tab2);
    }

    // clean-up

    if (outonly == CPL_TRUE) {
    	remove(cat1);
    	remove(cat2);
    	remove(seg1);
    }

//**************************************************************************
// 	Administrate output
//**************************************************************************

    // To identify tiles for later operations
    // Flag each object according to its tile and save tile table

    cpl_table_new_column(tab1, "IMAGE", CPL_TYPE_STRING);
    cpl_table_new_column(tab1, "WEIGHTIMAGE", CPL_TYPE_STRING);
    cpl_table_new_column(tab1, "TILE", CPL_TYPE_STRING);
    cpl_table_new_column(tab1, "TILE_DIRECTORY", CPL_TYPE_STRING);

    for(i = 0; i < cpl_table_get_nrow(tab1); i++) {
    	cpl_table_set_string(tab1, "IMAGE", i, image);
    	cpl_table_set_string(tab1, "WEIGHTIMAGE", i, weight);
    	cpl_table_set_string(tab1, "TILE", i, tile);
    	cpl_table_set_string(tab1, "TILE_DIRECTORY", i, directory);
    }

    // Prepare output file for sextractor table and checkimage

    strcat(directory, "/");
    sprintf(tiletab, "%s%s", directory, out_tab);
    sprintf(checkdir, "%s%s", directory, check);

	// Sort table according to magnitude

    if(magsort == CPL_TRUE) {

    	list = cpl_propertylist_new();
    	cpl_propertylist_append_bool(list, "MAG_BEST", sortval);
    	cpl_table_sort(tab1, list);
    	cpl_propertylist_delete(list);
    }

    // Save every table into the according output directory for each tile

    cpl_table_save(tab1, NULL, NULL, tiletab, CPL_IO_CREATE);

    if(debug == 1) {
    	printf("\nOutput catalogue was saved to : %s\n\n", tiletab);
    }

    // Create checkimage for every tile

    if(debug == 1) {
    	cpl_msg_info(cpl_func, "Creating checkimage for %s.", image);
    }

    create_checkimage(checkdir, tiletab, image);

    rename(seg1, outseg);

    /*************************************************************************
     * remove files
     ************************************************************************/

    cpl_table_delete(tab1);
    cpl_table_delete(sextab);
    cpl_array_delete(sexsetupar);
    cpl_array_delete(segar);
    cpl_array_delete(catar);
    cpl_table_delete(reqcols);
    cpl_array_delete(col_names);

    return CPL_ERROR_NONE;
}

/**@}*/







///*!
// * \ingroup galapagos
// */
//
///**@{*/
//
///*!
// * \callgraph
// *
// * \file gala_sextractor.c
// *
// * \brief GALAPAGOS routine for executing SExtractor.
// *
// * \author Marco Barden
// */
//
//#include "gala_sextractor.h"
//
//cpl_error_code gala_sextractor(cpl_parameterlist *sex_setup, const int *rank) {
//
//    cpl_table *sextab = NULL,
//              *reqcols = NULL,
//              *tab1 = NULL,
//              *tab2 = NULL,
//              *outtab = NULL;
//
//    cpl_array *col_names = NULL,
//    		  *sexsetupar = NULL,
//    		  *catar = NULL,
//    		  *segar = NULL;
//
//    cpl_parameter *p;
//
//    cpl_boolean flag = CPL_FALSE,
//                chk = CPL_TRUE,
//                outonly = CPL_TRUE,
//                dryrun = CPL_FALSE,
//                sortval = CPL_FALSE,
//                magsort = CPL_TRUE;
//
//    cpl_propertylist *list;
//
//    FILE *fp, *fp_r;
//
//    char seg1[FILENAME_MAX],
//    	 seg2[FILENAME_MAX],
//    	 cat1[FILENAME_MAX],
//    	 cat2[FILENAME_MAX],
//    	 sexsetup[FILENAME_MAX],
//         cat[FILENAME_MAX],
//         seg[FILENAME_MAX],
//         sex_par[FILENAME_MAX],
//         outpar[FILENAME_MAX],
//         image[FILENAME_MAX],
//         outseg[FILENAME_MAX],
//         out_tab[FILENAME_MAX],
//         sexexe[FILENAME_MAX],
//         weight[FILENAME_MAX],
//         check[FILENAME_MAX],
//         chkst[FILENAME_MAX],
//         chktype[FILENAME_MAX],
//         directory[FILENAME_MAX],
//         tile[FILENAME_MAX],
//         tmp[FILENAME_MAX];
//
//    char str[FILENAME_MAX], tiletab[FILENAME_MAX], checkdir[FILENAME_MAX],
//    	outsegdir[FILENAME_MAX];
//
//    char *p1, *p2, *p3;
//    char tiledir[FILENAME_MAX] = "mkdir ";
//
//    int multi = 0, n, i, k, l, m, j;
//
//    double enlarge;
//
//    struct stat st;
//
//    /*************************************************************************
//     * extract setup parameters
//     ************************************************************************/
//
//    // Rank wohl besser übergeben ??
//
//	/* find out process rank */
////	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
////	/* find out number of processes */
////	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
//
//    p = cpl_parameterlist_find(sex_setup, "setup");
//    sprintf(sexsetup, "%s", cpl_parameter_get_string(p));
//    p = cpl_parameterlist_find(sex_setup, "cat");
//    sprintf(cat, "%s", cpl_parameter_get_string(p));
//    p = cpl_parameterlist_find(sex_setup, "seg");
//    sprintf(seg, "%s", cpl_parameter_get_string(p));
//    p = cpl_parameterlist_find(sex_setup, "sex_par");
//    sprintf(sex_par, "%s", cpl_parameter_get_string(p));
//    p = cpl_parameterlist_find(sex_setup, "out_par");
//    sprintf(outpar, "%s", cpl_parameter_get_string(p));
//    p = cpl_parameterlist_find(sex_setup, "image");
//    sprintf(image, "%s", cpl_parameter_get_string(p));
//    p = cpl_parameterlist_find(sex_setup, "out_seg");
//    sprintf(outseg, "%s", cpl_parameter_get_string(p));
//    p = cpl_parameterlist_find(sex_setup, "out_tab");
//    sprintf(out_tab, "%s", cpl_parameter_get_string(p));
//    p = cpl_parameterlist_find(sex_setup, "sexexe");
//    sprintf(sexexe, "%s", cpl_parameter_get_string(p));
//    p = cpl_parameterlist_find(sex_setup, "weightimage");
//    sprintf(weight, "%s", cpl_parameter_get_string(p));
//    p = cpl_parameterlist_find(sex_setup, "check");
//    sprintf(check, "%s", cpl_parameter_get_string(p));
//    p = cpl_parameterlist_find(sex_setup, "chktype");
//    sprintf(chktype, "%s", cpl_parameter_get_string(p));
//    p = cpl_parameterlist_find(sex_setup, "enlarge");
//    enlarge = cpl_parameter_get_double(p);
//    p = cpl_parameterlist_find(sex_setup, "chkim");
//    sprintf(chkst, "%s", cpl_parameter_get_string(p));
//    p = cpl_parameterlist_find(sex_setup, "suffix");
//    sprintf(tile, "%s", cpl_parameter_get_string(p));
//    strtok(tile, ".");
//    strtok(NULL, ".");
//    p = cpl_parameterlist_find(sex_setup, "directory");
//    sprintf(directory, "%s", cpl_parameter_get_string(p));
//    if(strcmp(chkst, "yes") == 0) {
//    	chk = CPL_TRUE;
//    } else {
//    	chk = CPL_FALSE;
//    }
//
//    //separate the path string and read into cpl_array
//
//    sexsetupar = cpl_array_new (0, CPL_TYPE_STRING);
//    catar = cpl_array_new (0, CPL_TYPE_STRING);
//    segar = cpl_array_new (0, CPL_TYPE_STRING);
//
//    p1 = strtok(sexsetup, " ");
//    for (i = 0; p1 != NULL; i++) {
//    	cpl_array_set_size(sexsetupar, i + 1);
//    	cpl_array_set_string(sexsetupar, i, p1);
//   		p1 = strtok(NULL, " ");
//    }
//
//    p2 = strtok(cat, " ");
//    for (i = 0; p2 != NULL; i++) {
//    	cpl_array_set_size(catar, i + 1);
//    	cpl_array_set_string(catar, i, p2);
//   		p2 = strtok(NULL, " ");
//    }
//
//    p3 = strtok(seg, " ");
//    for (i = 0; p3 != NULL; i++) {
//    	cpl_array_set_size(segar, i + 1);
//    	cpl_array_set_string(segar, i, p3);
//   		p3 = strtok(NULL, " ");
//    }
//
//    // Check user input
//
//    k = cpl_array_get_size(sexsetupar);
//    l = cpl_array_get_size(catar);
//    m = cpl_array_get_size(segar);
//
//    if (k != l || k != m) {
//    	return cpl_error_set_message(cpl_func, CPL_ERROR_INCOMPATIBLE_INPUT ,
//    	                             "Mismatching number of input files!");
//    }
//
//    for(i = 0; i < k; i++) {
//    	sprintf(tmp, "%s", cpl_array_get_string(sexsetupar, i));
//    	if(filecheck(tmp) != CPL_ERROR_NONE) {
//    		cpl_msg_error(cpl_func, "SExtractor input files %s not found!",
//    				tmp);
//    		return CPL_ERROR_FILE_NOT_FOUND;
//    	}
//    }
//
//    // get required columns
//    reqcols = su_reqcols();
//
//    // see if check image requested
//    sprintf(str, "%s", chktype);
//    strtolower(str);
//    if (strcmp(str, "none") == 0) {
//        chk = CPL_FALSE;
//    }
//
//    /*************************************************************************
//     * identify setup: get number of input files
//     ************************************************************************/
//
//    multi = cpl_array_get_size(sexsetupar);
//
//    if (multi == 0) {
//        // no input files
//        cpl_table_delete(outtab);
//        cpl_table_delete(sextab);
//        cpl_table_delete(reqcols);
//        cpl_array_delete(col_names);
//
//        return cpl_error_set_message(cpl_func, CPL_ERROR_FILE_NOT_FOUND,
//                                     "No (%s) SExtractor setup-files found",
//                                     sexsetup);
//    }
//
//    /*************************************************************************
//     * create parameter-file for output
//     ************************************************************************/
//
//    // write required column names
//    col_names = cpl_table_get_column_names(reqcols);
//    n = cpl_array_get_size(col_names);
//
//    // Multiple processes must be synchronized
//
//    if(rank == 0) {
//
//    	fp = fopen(outpar, "w");
//    	if(fp == NULL) {
//    		cpl_table_delete(outtab);
//    		cpl_table_delete(sextab);
//    		cpl_table_delete(reqcols);
//    		cpl_array_delete(col_names);
//    		return cpl_error_set_message(cpl_func, CPL_ERROR_FILE_NOT_FOUND,
//    	                                     "%s not found", outpar);
//    	}
//
//    	for (i = 0; i < n; i++) {
//    		fprintf(fp, "%s\n", cpl_array_get_string(col_names, i));
//    	}
//    }
//
//    MPI_Barrier(MPI_COMM_WORLD);
//
//    // write additional requested column names
//    fp_r = fopen(sex_par, "r");
//
//    if (fp_r == NULL) {
//        // SExtractor parameter-file not found
//        cpl_table_delete(outtab);
//        cpl_table_delete(sextab);
//        cpl_table_delete(reqcols);
//        cpl_array_delete(col_names);
//
//        return cpl_error_set_message(cpl_func, CPL_ERROR_FILE_NOT_FOUND,
//                                     "%s not found", sex_par);
//    }
//
//    initialise_string(str, FILENAME_MAX);
//    while (fgets(str, FILENAME_MAX - 1, fp_r) != NULL) {
//        strtrim_inplace(str);
//        strtoupper(str);
//        // do not duplicate entries
//        for (j = 0, flag = CPL_FALSE; j < n; j++) {
//            if (strcmp(str, cpl_array_get_string(col_names, j)) == 0) {
//                flag = CPL_TRUE;
//                break;
//            }
//        }
//        if (flag == CPL_FALSE && rank == 0) {
//            fprintf(fp, "%s\n", str);
//        }
//    }
//
//    if(rank == 0) {
//    	fclose(fp);
//    }
//
//    MPI_Barrier(MPI_COMM_WORLD);
//
//    fclose(fp_r);
//
//    /*************************************************************************
//     * run SExtractor for each setup file and merge tables
//     ************************************************************************/
//
//    tab1 = cpl_table_new(0);
//
//    sprintf (cat1, "%s", cpl_array_get_string (catar, 0));
//    printf("cat1 :  %s\n", cat1);
//    printf("ARRAY\n");
//    cpl_array_dump(catar, 0, 20, NULL);
//	sprintf (seg1, "%s", cpl_array_get_string (segar, 0));
//	sprintf (sexsetup, "%s", cpl_array_get_string (sexsetupar, 0));
//
//    fp = fopen(sexsetup, "r");
//    if (fp != NULL) {
//    	fclose(fp);
//    } else {
//        return cpl_error_set_message(cpl_func, CPL_ERROR_FILE_NOT_FOUND,
//                "%s not found", sexsetup);         // file does not exist
//    }
//
//    // Create output directories for every tile according to setup file
//
//    strcat(tiledir, directory);
//
//    if(stat(directory,&st) != 0) {
//        system(tiledir);
//    }
//
//    // Check if directory name is valid. How?
//
//    if(stat(directory,&st) != 0) {
//    	cpl_msg_error(cpl_func, "Could not create directory %s!\n",
//    			directory);
//    	return CPL_ERROR_ILLEGAL_INPUT;
//    }
//
//    // Prepare path for segmentation image file
//
//    sprintf(outsegdir, "%s%s", directory, outseg);
//
//    printf("rank : %d   directory : %s\n", *rank, directory);
//
//    i = 0;
//	gala_run_sextractor(tab1, sexexe, sexsetup, cat1, outpar, image,
//						seg1, weight, check, chktype, chk, dryrun, &i,
//						&*rank);
//
////    for (i = 1; i < multi; i++) {
////    	tab2 = cpl_table_new(0);
////
////    	sprintf (cat2, "%s", cpl_array_get_string (catar, i));
////    	sprintf (seg2, "%s", cpl_array_get_string (segar, i));
////    	sprintf (sexsetup, "%s", cpl_array_get_string (sexsetupar, i));
////
////    	fp = fopen(sexsetup, "r");
////        if (fp != NULL) {
////        	fclose(fp);
////        } else {
////            return cpl_error_set_message(cpl_func, CPL_ERROR_FILE_NOT_FOUND,
////                    "%s not found", sexsetup);        // file does not exist
////        }
////
////        gala_run_sextractor(tab2, sexexe, sexsetup, cat2, outpar, image,
////    						seg2, weight, check, chktype, chk, dryrun, &i,
////							&rank);
////
////    	gala_merge_tables (tab1, tab2, seg1, seg2, outsegdir,
////    				   	   cat1, cat2, &enlarge, outonly);
////
////    	cpl_table_delete (tab2);
////    }
////
//////    cpl_table_dump(tab1, 0, 100, NULL);
//
////**************************************************************************
//// 	Administrate output
////**************************************************************************
//
//    // To identify tiles for later operations
//    // Flag each object according to its tile and save tile table
//
//    cpl_table_new_column(tab1, "TILE", CPL_TYPE_STRING);
//    cpl_table_new_column(tab1, "TILE_DIRECTORY", CPL_TYPE_STRING);
//
//    for(i = 0; i < cpl_table_get_nrow(tab1); i++) {
//    	cpl_table_set_string(tab1, "TILE", i, tile);
//    	cpl_table_set_string(tab1, "TILE_DIRECTORY", i, directory);
//    }
//
//    // Prepare output file for sextractor table and checkimage
//
//    strcat(directory, "/");
//    sprintf(tiletab, "%s%s", directory, out_tab);
//    sprintf(checkdir, "%s%s", directory, check);
//
//	// Sort table according to magnitude
//
//    if(magsort == CPL_TRUE) {
//
//    	list = cpl_propertylist_new();
//    	cpl_propertylist_append_bool(list, "MAG_BEST", sortval);
//    	cpl_table_sort(tab1, list);
//    	cpl_propertylist_delete(list);
//    }
//
//    // Save every table into the according output directory for each tile
//
//    cpl_table_save(tab1, NULL, NULL, tiletab, CPL_IO_CREATE);
//
//    printf("\nOutput catalogue was saved to : %s\n\n", tiletab);
//
////    // Create checkimage for every tile
////
////    cpl_msg_info(cpl_func, "Creating checkimage for %s\n.", image);
////
////    create_checkimage(checkdir, tiletab, image);
////
////    rename(seg1, outseg);
//
//    /*************************************************************************
//     * remove files
//     ************************************************************************/
//
//    cpl_table_delete(tab1);
//    cpl_table_delete(sextab);
//    cpl_array_delete(sexsetupar);
//    cpl_array_delete(segar);
//    cpl_array_delete(catar);
//    cpl_table_delete(reqcols);
//    cpl_array_delete(col_names);
//
//    return CPL_ERROR_NONE;
//}
//
///**@}*/
