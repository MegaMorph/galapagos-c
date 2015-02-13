// GALAPAGOS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <cpl.h>
#include <mpi.h>
#include "galapagos_utils.h"
#include "gala_sextractor.h"


int main(int argc, char *argv[]) {

	int  i = 0, j = 0,             // Loop variables
		 count,                    // Counting variable for input images
		 rank,                     // Processor ID
		 numprocs,                 // Number of processes
		 psdone = 1,               // Signal for slaves that postage stamps are done
		 sedone = 1,
		 synch = 1,
		 ncomponents;
	double time;
	char setup_file[FILENAME_MAX]; // Filename path string for setup file
	char gala_file[FILENAME_MAX];  // Filename path string for input files
	char dosex[FILENAME_MAX];      // Executable string HDR SExtractor
	char doskymap[FILENAME_MAX];   // Executable string Skymap
	char dostamps[FILENAME_MAX];   // Executable string Postage Stamp Cutting
	char docat[FILENAME_MAX];      // Executable string for Combined SExcatalog
	char dosky[FILENAME_MAX];      // Executable string for Background
	char dogalfit[FILENAME_MAX];   // Executable string for GALFIT
	char dofm[FILENAME_MAX];       // Executable string for GALFIT Fourier modes
	char execute[FILENAME_MAX] =
			"execute";  		   // Definition of execute string
	cpl_array *imagearray = NULL,  // Array containing input images
		      *weightarray = NULL, // Array containing weight images
		      *directory = NULL,   // Array for output directories for tiles
		      *suffix = NULL;      // Array containing suffixes for every tile
	cpl_parameterlist *gala_setup; // Parameterlist setup params for GALAPAGOS
	cpl_parameter *p;              // Cpl parameter to find objects on paramlist
    cpl_errorstate err_state;      // Cpl errorstate control
    MPI_Status status;             // MPI status


	/* start up MPI */
	MPI_Init(&argc, &argv);

	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	/* find out number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	/* initialize MPI */
    cpl_init(CPL_INIT_DEFAULT);

    /* starting message */

    if(rank == 0) {
    	cpl_msg_info(cpl_func, "Starting GALAPAGOS with %d processors.",
    			numprocs);
    }

    /* initialize errorstate */
    err_state = cpl_errorstate_get();

    /* initialize cpl_parameterlist */
	gala_setup = cpl_parameterlist_new();

/************************************************************************
				Read in GALAPAGOS setup
 ************************************************************************/

	/*get setup file path*/
    sprintf(setup_file, "%s", argv[1]);

    /* check if setup file exists with correct filename */
    if(access(setup_file, 00) != 0) {

    	/* if access is not possible print out an error message by MASTER */
    	if(rank == 0) {
    		cpl_msg_error(cpl_func, "setup file %s is not accessable!\n",
    				setup_file);
    		cpl_errorstate_dump(err_state, CPL_FALSE,
    				cpl_errorstate_dump_one);
    	}

    	/* clean up and finalize */
		cpl_parameterlist_delete(gala_setup);
		cpl_end();
		MPI_Finalize();
		return CPL_ERROR_FILE_NOT_FOUND;
    }

	/* read in setup file and control user input */
	if (read_galasetup(gala_setup, setup_file) != CPL_ERROR_NONE) {

    	/* if reading is not possible print out an error message by MASTER */
    	if(rank == 0) {
    		cpl_msg_error(cpl_func, "read_galasetup() failed");
    		cpl_errorstate_dump(err_state, CPL_FALSE, cpl_errorstate_dump_one);
    	}

    	/* clean up and finalize */
		cpl_parameterlist_delete(gala_setup);
		cpl_end();
		MPI_Finalize();
		return CPL_ERROR_INCOMPATIBLE_INPUT;
	}

    /* prepare arrays for GALAPAGOS input images, weight images,
       output directories and file prefixes */
	imagearray   = cpl_array_new(0, CPL_TYPE_STRING);
	weightarray  = cpl_array_new(0, CPL_TYPE_STRING);
	directory    = cpl_array_new(0, CPL_TYPE_STRING);
	suffix       = cpl_array_new(0, CPL_TYPE_STRING);

	/* read path for file containing input images and output directories */
	p = cpl_parameterlist_find(gala_setup, "galafile");
	sprintf(gala_file, "%s", cpl_parameter_get_string(p));

	/* read in GALAPAGOS input files and control user input */
	if (read_galafile(imagearray, weightarray, directory, suffix,
					  gala_file) != CPL_ERROR_NONE) {
		cpl_msg_error(cpl_func, "read_galasetup() failed");
		cpl_errorstate_dump(err_state, CPL_FALSE, cpl_errorstate_dump_one);
	}

	/* check number of input tiles */
	count = cpl_array_get_size(imagearray);

	/* check errorstate */
	check_errorstate(err_state);

/************************************************************************
			 Execute HDR SExtractor for every tile
 ************************************************************************/

	/* check if HDR SExtractor execution is desired */
	p = cpl_parameterlist_find(gala_setup, "dosex");
	sprintf(dosex, "%s", cpl_parameter_get_string(p));
	if(strcmp(dosex, execute) == 0 || strcmp(dosex, "yes") == 0 ||
			strcmp(dosex, "y") == 0) {

		/* initialize time */
		time = MPI_Wtime();

		/* run HDR SExtractor for every tile */
		for(i = 0; i < count; i++) {
			/* distribute tiles among the processors */
    		if(i % numprocs == rank) {

				/* prepare HDR SExtractor setup file for every tile */
				if (adjust_galasetup(gala_setup, imagearray, weightarray,
						directory, suffix, i) != CPL_ERROR_NONE) {
					cpl_msg_error(cpl_func, "su_read_sexsetup() failed");
					cpl_errorstate_dump(err_state, CPL_FALSE,
							cpl_errorstate_dump_one);
				}

				/* run HDR SExtractor */
				if (gala_sextractor(gala_setup) != CPL_ERROR_NONE) {
					cpl_msg_error(cpl_func, "gala_sextractor() failed");
					cpl_errorstate_dump(err_state, CPL_FALSE,
							cpl_errorstate_dump_one);
				}
			}
		}

		/* measure time */
		time = MPI_Wtime() - time;
		printf("Time from node %d for SExtractor is %lf seconds.\n",rank,time);

		/* check errorstate */
		check_errorstate(err_state);
	}

	/* synchronize processors */
	if(rank == 0) {
		for(i = 1; i < numprocs; i++) {
			MPI_Send(&sedone, sizeof(int), MPI_INT, i, 27, MPI_COMM_WORLD);
		}
	} else {
		MPI_Recv(&sedone, sizeof(int), MPI_INT, 0, 27, MPI_COMM_WORLD, &status);
	}
	MPI_Barrier(MPI_COMM_WORLD);



/************************************************************************
 				Execute GALAPAGOS skymap for every tile
 ************************************************************************/

	/* check if skymap is desired */
	p = cpl_parameterlist_find(gala_setup, "doskymap");
	sprintf(doskymap, "%s", cpl_parameter_get_string(p));
	if(strcmp(doskymap, execute) == 0 || strcmp(doskymap, "yes") == 0 ||
			strcmp(doskymap, "y") == 0) {

		/* find out process rank */
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		/* run HDR SExtractor for every tile */
		for(i = 0; i < count; i++){
			/* distribute tiles among the processors */
			if(i % numprocs == rank) {

				/* prepare skymap setup file for every tile */
				if (adjust_galasetup(gala_setup, imagearray, weightarray,
						directory, suffix, i) != CPL_ERROR_NONE) {
					cpl_msg_error(cpl_func, "su_read_sexsetup() failed");
					cpl_errorstate_dump(err_state, CPL_FALSE,
							cpl_errorstate_dump_one);
				}

				/* start skymap computation */
				if (create_skymap(gala_setup) != CPL_ERROR_NONE) {
					cpl_msg_error(cpl_func, "create_skymap() failed");
					cpl_errorstate_dump(err_state, CPL_FALSE,
							cpl_errorstate_dump_one);
				}
			}
		}

		/* check errorstate */
		check_errorstate(err_state);
    }

    /* synchronize processes before starting postage stamp cutting */
	if(rank == 0) {
		for(i = 1; i < numprocs; i++) {
			MPI_Send(&psdone, sizeof(int), MPI_INT, i, 24, MPI_COMM_WORLD);
		}
	} else {
		MPI_Recv(&psdone, sizeof(int), MPI_INT, 0, 24, MPI_COMM_WORLD, &status);
	}
	MPI_Barrier(MPI_COMM_WORLD);

/************************************************************************
					Execute Postage Stamp Cutting
 ************************************************************************/

	p = cpl_parameterlist_find(gala_setup, "dostamps");
	sprintf(dostamps, "%s", cpl_parameter_get_string(p));
	if(strcmp(dostamps, execute) == 0 || strcmp(dostamps, "yes") == 0 ||
			strcmp(dostamps, "y") == 0) {

		/* initialize time */
		time = MPI_Wtime();

		/* find out process rank */
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		/* run postage stamp cutting for every tile */
		for(i = 0; i < count; i++) {
			/* distribute tiles among the processors */
			if(i % numprocs == rank) {

				/* prepare postage stamp cutting setup file for every tile */
				if (adjust_galasetup(gala_setup, imagearray, weightarray,
						directory, suffix, i) != CPL_ERROR_NONE) {
    				cpl_msg_error(cpl_func, "su_read_sexsetup() failed");
    				cpl_errorstate_dump(err_state, CPL_FALSE,
							cpl_errorstate_dump_one);
					}

				/* start postage stamp cutting accordingly */
				if (cut_post(gala_setup) != CPL_ERROR_NONE) {
    				cpl_msg_error(cpl_func, "cut_post() failed");
    				cpl_errorstate_dump(err_state, CPL_FALSE,
    						cpl_errorstate_dump_one);
				}
    		}
		}

		/* measure time */
		time = MPI_Wtime() - time;
		printf("Time from node %d for Postage Stamps is %lf seconds.\n",rank,time);

		/* check errorstate */
//		check_errorstate(err_state);
	}

    /* synchronize processes before starting table merging or GALFIT */
	if(rank == 0) {
		for(i = 1; i < numprocs; i++) {
			MPI_Send(&psdone, sizeof(int), MPI_INT, i, 24, MPI_COMM_WORLD);
		}
	} else {
		MPI_Recv(&psdone, sizeof(int), MPI_INT, 0, 24, MPI_COMM_WORLD, &status);
	}
	MPI_Barrier(MPI_COMM_WORLD);


/************************************************************************
 					Merge tables from every tile
 ************************************************************************/

	/* check if table merging execution is desired */
    p = cpl_parameterlist_find(gala_setup, "docat");
    sprintf(docat, "%s", cpl_parameter_get_string(p));
    if(strcmp(docat, execute) == 0  || strcmp(docat, "yes") == 0 ||
    		strcmp(docat, "y") == 0) {

    	/* find out process rank */
    	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    	if(rank == 0) {

    		/* initialize time */
    		time = MPI_Wtime();

	    	/* merge all tables from HDR SExtractor */
	    	if (merge_tables(imagearray, directory, gala_setup) != CPL_ERROR_NONE) {
	    		cpl_msg_error(cpl_func, "merge_tables() failed");
    			cpl_errorstate_dump(err_state, CPL_FALSE, cpl_errorstate_dump_one);
	    	}

    		/* merge all tables from HDR SExtractor */
//    		if (create_combcat(gala_setup, directory) != CPL_ERROR_NONE) {
//    		   		cpl_msg_error(cpl_func, "create_combcat() failed");
//    			   	cpl_errorstate_dump(err_state, CPL_FALSE, cpl_errorstate_dump_one);
//    		}

			/* measure time */
			time = MPI_Wtime() - time;
			printf("Time from node %d for table merging is %lf seconds.\n",rank,time);
	   	}

    	/* check errorstate */
    	check_errorstate(err_state);
	}

	/* synchronize processes before starting skymap compilation */
	if(rank == 0) {
		for(i = 1; i < numprocs; i++) {
			MPI_Send(&psdone, sizeof(int), MPI_INT, i, 24, MPI_COMM_WORLD);
		}
	} else {
		MPI_Recv(&psdone, sizeof(int), MPI_INT, 0, 24, MPI_COMM_WORLD, &status);
	}
	MPI_Barrier(MPI_COMM_WORLD);


/************************************************************************
					Background Estimation
 ************************************************************************/

	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	/* find out number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	/* check number of input tiles */
	count = cpl_array_get_size(imagearray);

	/* check if background estimation is desired */
    p = cpl_parameterlist_find(gala_setup, "dosky");
    sprintf(dosky, "%s", cpl_parameter_get_string(p));
    if(strcmp(dosky, execute) == 0 || strcmp(dosky, "yes") == 0 ||
    		strcmp(dosky, "y") == 0) {

    	/* initialize time */
    	time = MPI_Wtime();

    	/* estimate background for every object in every tile */
    	for(i = 0; i < count; i++) {
    		/* distribute tiles among the processors */
    		if(i % numprocs == rank) {

    			/* prepare background estimation setup file for every tile */
    			if (adjust_galasetup(gala_setup, imagearray, weightarray,
    					directory, suffix, i) != CPL_ERROR_NONE) {
    					cpl_msg_error(cpl_func, "su_read_sexsetup() failed");
    					cpl_errorstate_dump(err_state, CPL_FALSE,
    						cpl_errorstate_dump_one);
    			}

    	    	/* start background estimation */
    	    	if(estimate_background(gala_setup) != CPL_ERROR_NONE) {
    	    		cpl_msg_error(cpl_func, "Background estimation failed.");
    	    		cpl_errorstate_dump(err_state, CPL_FALSE, cpl_errorstate_dump_one);
    	    	}
    		}
    	}

    	/* measure time */
    	time = MPI_Wtime() - time;

    	printf("Time from node FOR BACKGROUND ESTIMATION IS "
    			"%d is %lf seconds.\n",rank,time);

    	/* synchronize processes */
        MPI_Barrier(MPI_COMM_WORLD);

    	/* find out process rank */
    	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    	/* write sky values into combined catalog by MASTER */
	    if(rank == 0) {
	    	if(write_sky_output(gala_setup)!= CPL_ERROR_NONE) {
	    		cpl_msg_error(cpl_func, "Failed to write sky values "
	    				"into combined catalog!!!");
	    		cpl_errorstate_dump(err_state, CPL_FALSE,
	    				cpl_errorstate_dump_one);
	    	}
    	}
    }

    /* synchronize processes */
    if(rank == 0) {
    	for(j = 1; j < numprocs; j++) {
    		synch = 1;
    		MPI_Send(&synch, sizeof(int), MPI_INT, j, 25, MPI_COMM_WORLD);
    	}
    } else {
    		MPI_Recv(&synch, sizeof(int), MPI_INT, 0, 25, MPI_COMM_WORLD, &status);
    }
    MPI_Barrier(MPI_COMM_WORLD);


/************************************************************************
 					            GALFIT
 ************************************************************************/

    /* check if GALFIT is desired */
    p = cpl_parameterlist_find(gala_setup, "dogalfit");
    sprintf(dogalfit, "%s", cpl_parameter_get_string(p));
    if(strcmp(dogalfit, execute) == 0 || strcmp(dogalfit, "yes") == 0 ||
    		strcmp(dogalfit, "y") == 0) {

    	/* initialize time */
    	time = MPI_Wtime();

    	/* Run GALFIT parallel */
    	if(run_galfit_parallel_NEW(gala_setup) != CPL_ERROR_NONE) {
    		cpl_msg_error(cpl_func, "GALFIT failed.");
    		cpl_errorstate_dump(err_state, CPL_FALSE,
    		cpl_errorstate_dump_one);
    	}

       	/* measure time */
    	time = MPI_Wtime() - time;
    	printf("\n\n\n-------------------------------------\n");
    	printf("Time from node FOR GALFIT procedure is "
    			"%d is %lf seconds.\n",rank,time);
    	printf("\n-------------------------------------\n\n\n");

    	/* synchronize processors after every image */
    	MPI_Barrier(MPI_COMM_WORLD);
	}

    /* synchronize processes */
    if(rank == 0) {
    	for(j = 1; j < numprocs; j++) {
    		synch = 1;
    		MPI_Send(&synch, sizeof(int), MPI_INT, j, 25, MPI_COMM_WORLD);
    	}
    } else {
    		MPI_Recv(&synch, sizeof(int), MPI_INT, 0, 25, MPI_COMM_WORLD, &status);
    }
    MPI_Barrier(MPI_COMM_WORLD);



 /************************************************************************
        			      GALFIT Fourier mode fitting
  ************************************************************************/

	/* check ifFourier mode fitting is desired */
    p = cpl_parameterlist_find(gala_setup, "dofourier");
    sprintf(dofm, "%s", cpl_parameter_get_string(p));

    if(strcmp(dofm, execute) == 0 || strcmp(dofm, "yes") == 0 ||
    		strcmp(dofm, "y") == 0) {

    	/* Run GALFIT parallel */
    	if(run_galfit_fourier_modes(gala_setup) != CPL_ERROR_NONE) {
    		cpl_msg_error(cpl_func, "GALFIT fourier modes failed.");
    		cpl_errorstate_dump(err_state, CPL_FALSE,
    		cpl_errorstate_dump_one);
    	}
    }

    /* synchronize processes */
    if(rank == 0) {
    	for(j = 1; j < numprocs; j++) {
    		synch = 1;
    		MPI_Send(&synch, sizeof(int), MPI_INT, j, 25, MPI_COMM_WORLD);
    	}
    } else {
    		MPI_Recv(&synch, sizeof(int), MPI_INT, 0, 25, MPI_COMM_WORLD,
    				&status);
    }

    MPI_Barrier(MPI_COMM_WORLD);


 /************************************************************************
     			      GALFIT bulge -disc fitting
  ************************************************************************/

	/* check if bulge-disc fitting is desired */
    p = cpl_parameterlist_find(gala_setup, "ncomponents");
    ncomponents = (int)cpl_parameter_get_double(p);

    printf("IN GALAPAGOS.c : ncomponents = %d\n", ncomponents);

    if(ncomponents >= 2) {
    	/* Start bulge-disc fitting */
    	if(run_bulge_disc_fitting(gala_setup) != CPL_ERROR_NONE) {
    		cpl_msg_error(cpl_func, "GALFIT bulge-disc fitting failed.");
    		cpl_errorstate_dump(err_state, CPL_FALSE,
    		    		cpl_errorstate_dump_one);
    	}

        /* synchronize processes */
        if(rank == 0) {
        	for(j = 1; j < numprocs; j++) {
        		synch = 1;
        		MPI_Send(&synch, sizeof(int), MPI_INT, j, 25, MPI_COMM_WORLD);
        	}
        } else {
        		MPI_Recv(&synch, sizeof(int), MPI_INT, 0, 25, MPI_COMM_WORLD, &status);
        }
        MPI_Barrier(MPI_COMM_WORLD);

        if(ncomponents >= 3) {
        	/* Start 3 component fitting */
        	if(run_3comp_fitting(gala_setup) != CPL_ERROR_NONE) {
        		cpl_msg_error(cpl_func, "GALFIT 3comp fitting failed.");
        		cpl_errorstate_dump(err_state, CPL_FALSE,
        		    		cpl_errorstate_dump_one);
        	}

            /* synchronize processes */
            if(rank == 0) {
            	for(j = 1; j < numprocs; j++) {
            		synch = 1;
            		MPI_Send(&synch, sizeof(int), MPI_INT, j, 25, MPI_COMM_WORLD);
            	}
            } else {
            		MPI_Recv(&synch, sizeof(int), MPI_INT, 0, 25, MPI_COMM_WORLD, &status);
            }
            MPI_Barrier(MPI_COMM_WORLD);

            if(ncomponents >= 4) {
            	/* Start 4 component fitting */
            	if(run_4comp_fitting(gala_setup) != CPL_ERROR_NONE) {
            		cpl_msg_error(cpl_func, "GALFIT 4comp fitting failed.");
            		cpl_errorstate_dump(err_state, CPL_FALSE,
            		    		cpl_errorstate_dump_one);
            	}

                /* synchronize processes */
                if(rank == 0) {
                	for(j = 1; j < numprocs; j++) {
                		synch = 1;
                		MPI_Send(&synch, sizeof(int), MPI_INT, j, 25, MPI_COMM_WORLD);
                	}
                } else {
                		MPI_Recv(&synch, sizeof(int), MPI_INT, 0, 25, MPI_COMM_WORLD, &status);
                }
                MPI_Barrier(MPI_COMM_WORLD);

                if(ncomponents == 5) {
                	/* Start 5 component fitting */
                	if(run_5comp_fitting(gala_setup) != CPL_ERROR_NONE) {
                		cpl_msg_error(cpl_func, "GALFIT 5comp fitting failed.");
                		cpl_errorstate_dump(err_state, CPL_FALSE,
                		    		cpl_errorstate_dump_one);
                	}

                }
            }
        }
    }

    /* synchronize processes */
    if(rank == 0) {
    	for(j = 1; j < numprocs; j++) {
    		synch = 1;
    		MPI_Send(&synch, sizeof(int), MPI_INT, j, 25, MPI_COMM_WORLD);
    	}
    } else {
    		MPI_Recv(&synch, sizeof(int), MPI_INT, 0, 25, MPI_COMM_WORLD, &status);
    }
    MPI_Barrier(MPI_COMM_WORLD);

	/* clean up */
	cpl_array_delete(imagearray);
	cpl_array_delete(weightarray);
	cpl_array_delete(directory);
	cpl_array_delete(suffix);
	cpl_parameterlist_delete(gala_setup);

	/* memory check */
    cpl_memory_dump();

    /* shut down cpl environment */
	cpl_end();

	/* shut down MPI */
	MPI_Finalize();

	return EXIT_SUCCESS;
}
