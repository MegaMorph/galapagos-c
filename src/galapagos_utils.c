/*!
 * \ingroup galapagos_utils
 */

/**@{*/

/*!
 * \callgraph
 *
 * \file galapagos_utils.c
 *
 * \brief Reading in an external file into a cpl_table.
 *
 * \author Marco and Andreas
 *
 * \date   05 Dez 2011
 */

#include <stdio.h>

#include <string.h>

#include <cpl.h>

#include <ctype.h>

#include <unistd.h>

#include "galapagos_utils.h"


cpl_error_code read_galasetup(cpl_parameterlist *gala_setup,
							  char *filename) {

	int i = 0;
	int f = 0;
	int g = 0;
	int h = 0;
	int length = 0;
	char line[FILENAME_MAX];
	char galafile[FILENAME_MAX]      = "galafile";
	char outdir[FILENAME_MAX]        = "outdir";
	char dosex[FILENAME_MAX]         = "dosex";
	char sexexe[FILENAME_MAX]        = "sexexe";
	char setup[FILENAME_MAX]         = "setup";
	char cat[FILENAME_MAX]           = "cat";
	char seg[FILENAME_MAX]           = "seg";
	char sex_par[FILENAME_MAX]       = "sex_par";
	char exptime[FILENAME_MAX]       = "exptime";
	char zerop[FILENAME_MAX]         = "zerop";
	char enlarge[FILENAME_MAX]       = "enlarge";
	char out_par[FILENAME_MAX]       = "out_par";
	char out_seg[FILENAME_MAX]       = "out_seg";
	char out_tab[FILENAME_MAX]       = "out_tab";
	char chkim[FILENAME_MAX]         = "chkim";
	char check[FILENAME_MAX]         = "check";
	char chktype[FILENAME_MAX]       = "chktype";
	char doskymap[FILENAME_MAX]      = "doskymap";
	char size[FILENAME_MAX]          = "size";
	char offset[FILENAME_MAX]        = "offset";
	char skymapname[FILENAME_MAX]    = "skymapname";
	char dostamps[FILENAME_MAX]      = "dostamps";
 	char stampfile[FILENAME_MAX]     = "stampfile";
	char stampname[FILENAME_MAX]     = "stampname";
	char stampfac[FILENAME_MAX]      = "stampfac";
	char dosky[FILENAME_MAX]         = "dosky";
	char outsky[FILENAME_MAX]        = "outsky";
	char nslope[FILENAME_MAX]        = "nslope";
	char bandsize[FILENAME_MAX]      = "bandsize";
	char isodist[FILENAME_MAX]       = "isodist";
	char startrad[FILENAME_MAX]      = "startrad";
	char expand[FILENAME_MAX]        = "expand";
	char path[FILENAME_MAX]          = "path";
	char object[FILENAME_MAX]        = "object";
 	char galfitset[FILENAME_MAX]     = "galfitset";
	char psf[FILENAME_MAX]           = "psf";
	char psffactor[FILENAME_MAX]     = "psffactor";
	char badpix[FILENAME_MAX]        = "badpix";
	char constraints[FILENAME_MAX]   = "constraints";
	char re_max[FILENAME_MAX]        = "re_max";
	char mag_min[FILENAME_MAX]       = "mag_min";
	char mag_max[FILENAME_MAX]       = "mag_max";
	char convbox[FILENAME_MAX]       = "convbox";
	char magzero[FILENAME_MAX]       = "magzero";
	char platescale[FILENAME_MAX]    = "platescale";
	char display[FILENAME_MAX]       = "display";
	char secenlarge[FILENAME_MAX]    = "secenlarge";
	char magexclude[FILENAME_MAX]    = "magexclude";
	char docat[FILENAME_MAX]         = "docat";
	char neighbortiles[FILENAME_MAX] = "neighbortiles";
	char cleantab[FILENAME_MAX]      = "cleantab";
	char sexcomb[FILENAME_MAX]       = "sexcomb";
	char fluxextend[FILENAME_MAX]    = "fluxextend";
	char distmax[FILENAME_MAX]       = "distmax";
	char magcrit[FILENAME_MAX]       = "magcrit";
	char contribmax[FILENAME_MAX]    = "contribmax";
	char dogalfit[FILENAME_MAX]      = "dogalfit";
	char dofourier[FILENAME_MAX]     = "dofourier";
	char ncomponents[FILENAME_MAX]   = "ncomponents";
	char *setpar[FILENAME_MAX];
	const char *strcont;
	char src[FILENAME_MAX];

    cpl_parameter *p;

    FILE *fp;

	// Check input file

	if (filecheck(filename) != CPL_ERROR_NONE) {
		cpl_msg_error(cpl_func, "filecheck() in gala_readsetup() failed");
		return CPL_ERROR_FILE_NOT_FOUND;
	}

    // Prepare parameterlist

	p = cpl_parameter_new_value("galafile",
							CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("outdir",
							CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);

	p = cpl_parameter_new_value("dosex",
							CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("sexexe",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("setup",
							CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("cat",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("seg",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("sex_par",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("exptime",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("zerop",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("enlarge",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("out_par",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("out_seg",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("out_tab",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("chkim",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("check",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("chktype",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);

	p = cpl_parameter_new_value("doskymap",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("size",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("offset",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("skymapname",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);

	p = cpl_parameter_new_value("dostamps",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("stampfile",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("stampname",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("stampfac",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);

	p = cpl_parameter_new_value("dosky",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("outsky",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("nslope",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("bandsize",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("isodist",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("startrad",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("expand",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);

	p = cpl_parameter_new_value("dogalfit",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("dofourier",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("ncomponents",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("path",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("object",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("galfitset",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("psf",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("psffactor",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("badpix",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("constraints",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("re_max",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("mag_min",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("mag_max",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("convbox",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("magzero",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("platescale",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("display",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("secenlarge",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("magexclude",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("fluxextend",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("distmax",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("magcrit",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("contribmax",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);

	p = cpl_parameter_new_value("docat",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("neighbortiles",
                            CPL_TYPE_DOUBLE, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("cleantab",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("sexcomb",
                            CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);

	setpar[0] = galafile;
	setpar[1] = outdir;

	setpar[2] = dosex;
	setpar[3] = sexexe;
	setpar[4] = setup;
	setpar[5] = cat;
	setpar[6] = seg;
	setpar[7] = sex_par;
	setpar[8] = exptime;
	setpar[9] = zerop;
	setpar[10] = enlarge;
	setpar[11] = out_par;
	setpar[12] = out_seg;
	setpar[13] = out_tab;
	setpar[14] = chkim;
	setpar[15] = check;
	setpar[16] = chktype;

	setpar[17] = doskymap;
	setpar[18] = size;
	setpar[19] = offset;
	setpar[20] = skymapname;

	setpar[21] = dostamps;
	setpar[22] = stampfile;
	setpar[23] = stampname;
	setpar[24] = stampfac;

	setpar[25] = dosky;
	setpar[26] = outsky;
	setpar[27] = nslope;
	setpar[28] = bandsize;
	setpar[29] = isodist;
	setpar[30] = startrad;
	setpar[31] = expand;

	setpar[32] = dogalfit;
	setpar[33] = dofourier;
	setpar[34] = ncomponents;
	setpar[35] = path;
	setpar[36] = object;
	setpar[37] = galfitset;
	setpar[38] = psf;
	setpar[39] = psffactor;
	setpar[40] = badpix;
	setpar[41] = constraints;
	setpar[42] = re_max;
	setpar[43] = mag_min;
	setpar[44] = mag_max;
	setpar[45] = convbox;
	setpar[46] = magzero;
	setpar[47] = platescale;
	setpar[48] = display;
	setpar[49] = secenlarge;
	setpar[50] = magexclude;
	setpar[51] = fluxextend;
	setpar[52] = distmax;
	setpar[53] = magcrit;
	setpar[54] = contribmax;

	setpar[55] = docat;
	setpar[56] = neighbortiles;
	setpar[57] = cleantab;
	setpar[58] = sexcomb;

    length = cpl_parameterlist_get_size(gala_setup);

	fp = fopen(filename, "r");

	while(fgets(line, FILENAME_MAX, fp) != NULL) {
		for(i = 0; i < length; i++) {
			get_param(gala_setup, line, fp, setpar[i]);
		}
	}

	fclose(fp);

	// control variables

	p = cpl_parameterlist_find (gala_setup, "setup");
	strcont = cpl_parameter_get_string (p);
	sprintf(src, "%s", strcont);
	f = countChar(src, ' ', '/');

	p = cpl_parameterlist_find (gala_setup, "cat");
	strcont = cpl_parameter_get_string (p);
	sprintf(src, "%s", strcont);
	g = countChar(src, ' ', '/');

	p = cpl_parameterlist_find (gala_setup, "seg");
	strcont = cpl_parameter_get_string (p);
	sprintf(src, "%s", strcont);
	h = countChar(src, ' ', '/');

	if(f != g || f != h) {
		cpl_msg_error (cpl_func, "%s",
					   "Mismatching number of SExtractor setup files,"
					   "catalog files and segmentation image files!");
		return CPL_ERROR_INCOMPATIBLE_INPUT;
	}

	// Extend parameterlist for image, weightimage,
	// directory and suffix to be filled by
	// su_read_sexsetup()

	p = cpl_parameter_new_value("image",
							CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("weightimage",
							CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("directory",
							CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);
	p = cpl_parameter_new_value("suffix",
							CPL_TYPE_STRING, "", "", "NN");
	cpl_parameterlist_append(gala_setup, p);

	if (check_gala_input(gala_setup) != CPL_ERROR_NONE) {
		cpl_msg_error(cpl_func, "User input is not valid!");
		return CPL_ERROR_ILLEGAL_INPUT;
	}

	return CPL_ERROR_NONE;
}


cpl_error_code gala_readexclude(cpl_table *exclude_tab, const char *exclude) {

	int i = 0;
	int a1;
	int a2;
	int con;
	char buf[FILENAME_MAX];

	FILE *fp;

    cpl_table_new_column(exclude_tab, "PATH", CPL_TYPE_STRING);
    cpl_table_new_column(exclude_tab, "X", CPL_TYPE_INT);
    cpl_table_new_column(exclude_tab, "Y", CPL_TYPE_INT);

	fp = fopen(exclude, "r");

	if (fp == NULL) {
		cpl_msg_error(cpl_func, "Exclude file not found %s.", exclude);
        return cpl_error_set_message(cpl_func, CPL_ERROR_FILE_NOT_FOUND,
                                     "%s not found", exclude);
	} else {
	    for (i = 0; feof(fp) == 0; i++) {
	    	con = fscanf(fp, "%s %d %d", buf, &a1, &a2);

// With num it is controlled and guaranteed that only and only the value
// which are read in with scanf are set into the cpl table.

	    	if (con > 0) {
				cpl_table_set_size(exclude_tab, i+1);
				cpl_table_set_string(exclude_tab, "PATH", i, buf);
				cpl_table_set(exclude_tab, "X", i, a1);
				cpl_table_set(exclude_tab, "Y", i, a2);
	    	} else {
	    		cpl_msg_error(cpl_func, "Exclude file not readable %s.",
	    				exclude);
	    	    fclose(fp);
	    	    return CPL_ERROR_UNSPECIFIED;
	    	}
	    }

	    fclose(fp);

	    return CPL_ERROR_NONE;
	}
}


//***************************************************************************
// Extracting the postage stamp parameters from the cpl_table information.
//***************************************************************************

cpl_error_code get_stamp_param(const int *i, int *xlo, int *xhi, int *ylo,
							   int *yhi, const int *x, const int *y,
							   const double *sizefac, cpl_table *tab,
							   FILE *fp) {

	int minor, major, len, debug = 0;
	double xfac, yfac, rad, ang, theta;
	double pi = 3.14159265;


	len =  cpl_table_get_nrow(tab);

	if(debug == 1) {
		printf("LEN : %d\n", len);
	}

	rad = cpl_table_get_double(tab, "A_IMAGE", *i, NULL) *
	      cpl_table_get_double(tab, "KRON_RADIUS", *i, NULL);

	if(debug == 1) {
		printf("rad : %f\n", rad);
	}

	ang = cpl_table_get_double(tab, "THETA_IMAGE", *i, NULL);
	ang = 2 * pi * ang / 360;

	if(debug == 1) {
		printf("ang : %f\n", ang);
	}

	xfac = rad * (fabs(sin(ang)) +
	       (1 - cpl_table_get_double(tab, "ELLIPTICITY", *i, NULL)) *
	       fabs(cos(ang)));

	if(xfac < 10) {
		xfac = 10;
	}

	xfac *= *sizefac;

	yfac = rad * (fabs(cos(ang)) +
	       (1 - cpl_table_get_double(tab, "ELLIPTICITY", *i, NULL)) *
	       fabs(sin(ang)));

	if(yfac < 10) {
		yfac = 10;
	}

	yfac *= *sizefac;

	major = 0.5 * (xfac + yfac + fabs(xfac - yfac));
	minor = 0.5 * (xfac + yfac - fabs(xfac - yfac));

	theta = cpl_table_get_double(tab, "THETA_IMAGE", *i, NULL);

	theta = fabs(theta);

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

	*xlo = round(cpl_table_get_double(tab, "X_IMAGE", *i, NULL) - xfac);
	*xhi = round(cpl_table_get_double(tab, "X_IMAGE", *i, NULL) + xfac);
	*ylo = round(cpl_table_get_double(tab, "Y_IMAGE", *i, NULL) - yfac);
	*yhi = round(cpl_table_get_double(tab, "Y_IMAGE", *i, NULL) + yfac);

	if(*xlo <= 0) {
	 	*xlo = 1;
	}
	if(*xhi > *x - 1) {
	    *xhi = *x - 1;
	}
	if(*ylo <= 0) {
	  	*ylo = 1;
	}
	if(*yhi > *y - 1) {
	    *yhi = *y - 1;
	}

	if(debug == 1) {
		printf("--------------------------------------------------------------\n");
		printf("XLO %d    :    %d\n", *i + 1, *xlo);
		printf("XHI %d    :    %d\n", *i + 1, *xhi);
		printf("YLO %d    :    %d\n", *i + 1, *ylo);
		printf("YHI %d    :    %d\n", *i + 1, *yhi);
	}

	// Write table with stamp coordinates

	cpl_table_set(tab, "STAMP_XLO", *i, *xlo);
	cpl_table_set(tab, "STAMP_XHI", *i, *xhi);
	cpl_table_set(tab, "STAMP_YLO", *i, *ylo);
	cpl_table_set(tab, "STAMP_YHI", *i, *yhi);

	fprintf(fp, "%6d    %6d    %6d    %6d\n",
			*xlo, *xhi, *ylo, *yhi);

	return CPL_ERROR_NONE;
}


// Creating stamp file. Output: char *outname

cpl_error_code create_stamp_file(char *outname, char *stampfile,
		char *outprefix, cpl_table *outtab, const int *i) {

	int number;
	char num[FILENAME_MAX];
	char str[FILENAME_MAX];
	char tile[FILENAME_MAX];
	char mkdir[FILENAME_MAX] = "mkdir";
    struct stat st;

	// Check if directory exists

 	sprintf(outname, "%s", cpl_table_get_string(outtab, "TILE_DIRECTORY", *i));

// 	printf("OUTNAME: %s\n", outname);

    if(stat(outname, &st) != 0) {
		sprintf(str, "%s %s", mkdir, outname);
//		printf("STR: %s\n", str);
		if(system(str) != 0) {
			printf("Problem with creating output directory.\n");
		} else {
			cpl_msg_error(cpl_func, "Unspecified problem with "
					"creating stamp folder %s.", outname);
		}
	}

 	sprintf(tile, "%s", cpl_table_get_string(outtab, "TILE", *i));

//	printf("OUTNAME: %s\n", outname);

	number = cpl_table_get(outtab, "NUMBER", *i, NULL);
	sprintf(num, "%d", number);

//	printf("i : %d\n", *i + 1);

	sprintf(outname, "%s%s%s%s%s%s%s%s%s%s", outname, "/", stampfile, "/",
			outprefix, "_", num, "_", tile, ".fits");

	return CPL_ERROR_NONE;
}


// Routine, die für die übergebenen Objektparameter eine Postage Stamp
// aus dem Image im ausschneidet und das Bild im File "outstamp" speichert.

cpl_error_code save_stamp(const char *outstamp, const char *header,
		int *xlo, int *xhi, int *ylo, int *yhi,
		cpl_image *im) {

	cpl_image *stampim = NULL;
	cpl_propertylist *hd;

    stampim = cpl_image_extract(im, *xlo, *ylo, *xhi, *yhi);

    hd = cpl_propertylist_load(header, 0);

	cpl_image_save(stampim, outstamp, CPL_BPP_IEEE_DOUBLE, hd, CPL_IO_CREATE);

    cpl_propertylist_delete(hd);
    cpl_image_delete(stampim);

	return CPL_ERROR_NONE;
}


cpl_error_code cut_post(cpl_parameterlist *gala_setup) {

	int x, y, xlo, xhi, ylo, yhi, i, row, rank;

	double sizefac;

	char cat[FILENAME_MAX],
		 directory[FILENAME_MAX],
		 tiledir[FILENAME_MAX],
	     stampfile[FILENAME_MAX],
	     stampname[FILENAME_MAX],
	     sexcomb[FILENAME_MAX],
	     image[FILENAME_MAX],
	     outdir[FILENAME_MAX],
	     stampparamfile[FILENAME_MAX],
	     stampparamfile2[FILENAME_MAX],
	     str[FILENAME_MAX], tmp[FILENAME_MAX],
	     out_tab[FILENAME_MAX],
	 	 paramfilesuffix[FILENAME_MAX] = "stampparameters.txt",
	 	 paramfilesuffix2[FILENAME_MAX] = "stampparameters.fits";

    struct stat st;

    cpl_parameter *p;
	cpl_image *testim = NULL;
	cpl_table *outtab = NULL;

	FILE *fp;

	// Load data from setup file

	p = cpl_parameterlist_find(gala_setup, "directory");
	sprintf(directory, "%s", cpl_parameter_get_string(p));
	sprintf(tiledir, "%s", cpl_parameter_get_string(p));
	p = cpl_parameterlist_find(gala_setup, "stampfile");
	sprintf(stampfile, "%s", cpl_parameter_get_string(p));
	p = cpl_parameterlist_find(gala_setup, "stampname");
	sprintf(stampname, "%s", cpl_parameter_get_string(p));
	p = cpl_parameterlist_find(gala_setup, "sexcomb");
	sprintf(sexcomb, "%s", cpl_parameter_get_string(p));
	p = cpl_parameterlist_find(gala_setup, "image");
	sprintf(image, "%s", cpl_parameter_get_string(p));
	p = cpl_parameterlist_find(gala_setup, "stampfac");
    sizefac = cpl_parameter_get_double(p);
	p = cpl_parameterlist_find(gala_setup, "outdir");
	sprintf(outdir, "%s", cpl_parameter_get_string(p));
	p = cpl_parameterlist_find(gala_setup, "out_tab");
	sprintf(out_tab, "%s", cpl_parameter_get_string(p));

	// Prepare directory for stamps and stamparameters

    strcat(directory, "/");
    strcat(directory, stampfile);
	sprintf(stampparamfile2, "%s%s%s", directory, "/", paramfilesuffix2);

    // Check if directory is existing - if not create

    if(stat(directory,&st) != 0) {
    	sprintf(str, "mkdir %s", directory);
    	if(system(str) != 0) {
    		cpl_msg_info(cpl_func, "Unspecified error when creating folder "
    				"for postage stamps.");
    	}
    }

    // Prepare file for stamptable

	sprintf(stampparamfile, "%s%s%s", directory, "/", paramfilesuffix);
//	printf("STAMPPARAMFILE: %s\n", stampparamfile);

	// Prepare file to load tile SExtractor output catalog

	sprintf(cat, "%s%s%s", tiledir, "/", out_tab);

	// Load image and table

	testim = cpl_image_load(image, CPL_TYPE_DOUBLE, 0, 0);
//	printf("IMAGE: %s\n", image);
//	printf("CAT: %s\n", cat);

	outtab = cpl_table_load(cat, 1, 0);

	row = cpl_table_get_nrow(outtab);

	cpl_table_new_column(outtab, "STAMP_XLO", CPL_TYPE_INT);
	cpl_table_new_column(outtab, "STAMP_XHI", CPL_TYPE_INT);
	cpl_table_new_column(outtab, "STAMP_YLO", CPL_TYPE_INT);
	cpl_table_new_column(outtab, "STAMP_YHI", CPL_TYPE_INT);

	x = cpl_image_get_size_x(testim);
	y = cpl_image_get_size_y(testim);

	if(x < 0 || y < 0) {
		cpl_msg_error(cpl_func, "In cust_post() : Image not found!");
	}

	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank == 0) {
		cpl_msg_info(cpl_func, "Cutting postage stamps.");
	}

	// Cut stamps

	fp = fopen(stampparamfile, "w");

    for(i = 0; i < row; i++) {

    	sprintf(tmp, "%s", cpl_table_get_string(outtab, "TILE_DIRECTORY", i));

    	if(strcmp(tiledir, tmp) == 0) {

    		get_stamp_param(&i, &xlo, &xhi, &ylo, &yhi, &x, &y,
    				    &sizefac, outtab, fp);
    		create_stamp_file(directory, stampfile, stampname, outtab, &i);
    		save_stamp(directory, image, &xlo, &xhi, &ylo, &yhi, testim);
    	}
    }

    cpl_table_save(outtab, NULL, NULL, cat, CPL_IO_CREATE);

    // Clean up

    cpl_image_delete(testim);
    cpl_table_delete(outtab);

	fclose(fp);

	return CPL_ERROR_NONE;
}


//**************************************************************************
// Calculation mean value and rms from an array
//
// Using Huber`s method mean and rms from an array is calculated.
//**************************************************************************

cpl_error_code sc_basic_clipmean(double *mean, double *rms,
                                 cpl_array *arr, const cpl_boolean clip) {

    cpl_array *mad_arr;    // median absolute difference

    double val_p, val_m, val = 0., mean_old, eps = 1e-4;

    int i, j,              // loop variables
        n,                 // size of arr
        nclip = 0, nclip_old = 0;         // total number of clipped elements

    // get size of array
    n = cpl_array_get_size(arr);

    // initialise array for median absolute difference
    mad_arr = cpl_array_new(n, CPL_TYPE_DOUBLE);

    // compute first guess for mean and rms using median absolute difference
    *mean = cpl_array_get_median(arr);
    for (i = 0; i < n; i++) {
        // compute MAD
        cpl_array_set_double(mad_arr, i,
                            fabs(cpl_array_get_double(arr, i, NULL) - *mean));
        if (cpl_array_is_valid(arr, i) == 0) {
            // remember invalid values from arr in mad_arr
            cpl_array_set_invalid(mad_arr, i);
        }
    }
    *rms = cpl_array_get_median(mad_arr) * 1.5;

    // now use Huber's method to improve estimate

    // reset mad_arr
    for (i = 0; i < n; i++) {
        cpl_array_set_double(mad_arr, i, cpl_array_get_double(arr, i, NULL));
        if (cpl_array_is_valid(arr, i) == 0) {
            // remember invalid values from arr in mad_arr
            cpl_array_set_invalid(mad_arr, i);
        }
    }

    // do at max 100 iterations (should converge much faster)
    for (j = 0, mean_old = *mean, nclip = 0, nclip_old = 0; j < 100; j++) {
        // re-compute outliers
        val_p = *mean + (1.5 * *rms);
        val_m = *mean - (1.5 * *rms);
        for (i = 0, *mean = 0; i < n; i++) {
            if (cpl_array_is_valid(mad_arr, i) == 1) {
                val = cpl_array_get_double(mad_arr, i, NULL);
                if (val > val_p) {
                    // set outliers invalid in original array
                    cpl_array_set_invalid(arr, i);
                    cpl_array_set_double(mad_arr, i, val_p);
                    nclip++;
                } else if (val < val_m) {
                    // set outliers invalid in original array
                    cpl_array_set_invalid(arr, i);
                    cpl_array_set_double(mad_arr, i, val_m);
                    nclip++;
                }
            }
        }
        *mean = cpl_array_get_mean(mad_arr);
        *rms = cpl_array_get_stdev(mad_arr)*1.134;

        if (fabs(mean_old / *mean - 1) < eps || nclip == nclip_old) {
            break;
        }
        mean_old = *mean;
        nclip_old = nclip;
    }

    if (clip == CPL_TRUE) {
        *mean = cpl_array_get_mean(arr);
        *rms = cpl_array_get_stdev(arr);
    }

    cpl_array_delete(mad_arr);

    return CPL_ERROR_NONE;
}

/**@}*/

/*!
 * \ingroup cpl_utils
 *
 * This module provides utilities for
 */


/**@{*/

/*!
 * \callgraph
 *
 * \file cpl_utils.c
 *
 * \brief Utilities for working with cpl_tables.
 *
 * \author Marco and Andreas
 *
 * \date   19 Dez 2011
 *
 * \par Synopsis:
 * \code
 *   #include <cpl_utils.h>
 * \endcode
 */

cpl_error_code cpl_table_copy (cpl_table *outtable, cpl_table *intable) {

	int i, j, an, a;

	const char *col_name;

	cpl_array *names;

	if (intable == NULL) {
		return cpl_error_set_message(cpl_func, CPL_ERROR_NULL_INPUT,
		                "No input table!");
	}

	names = cpl_array_new (0, CPL_TYPE_STRING);
	names = cpl_table_get_column_names (intable);
	an = cpl_table_get_nrow (intable);

	cpl_table_set_size (outtable, an);
	cpl_table_copy_structure (outtable, intable);

	a = cpl_array_get_size (names);
	if (a == 0) {
		return cpl_error_set_message(cpl_func, CPL_ERROR_INVALID_TYPE,
		                "Column names not available!");
	}

	if (cpl_table_compare_structure (outtable, intable) != 0) {
		return cpl_error_set_message(cpl_func, CPL_ERROR_UNSPECIFIED,
                "Structure copying failed!");
	}
	for (i = 0; i < cpl_array_get_size (names); i++) {
		col_name = cpl_array_get_string(names, i);
		printf ("%s\n", col_name);
		cpl_table_set_size (outtable, cpl_table_get_nrow (intable));
		for (j = 0; j < cpl_table_get_nrow (intable); j++) {
			cpl_table_set (outtable, col_name, j,
							   cpl_table_get (intable, col_name, j, NULL));
		}
	}
	return CPL_ERROR_NONE;
}

/**@}*/

/*!
 * \ingroup file_utils
 */

/**@{*/

/*!
 * \callgraph
 *
 * \file file_utils.c
 *
 * \brief Utility for checking SExtractor input file.
 *
 * \author Andreas Hiemer
 *
 * \date 19 Dec 2011
 */

cpl_error_code filecheck(const char *filename) {

	if(access(filename, 00) != 0) {
		cpl_msg_error (cpl_func, "%s", "Input file not found!");
     	return cpl_error_set_message(cpl_func, CPL_ERROR_FILE_NOT_FOUND,
     	                             "Input file not found!");
	} else if(access(filename, 04) != 0) {
		cpl_msg_error (cpl_func, "%s", "Input file not readable!");
     	return cpl_error_set_message(cpl_func, CPL_ERROR_INCOMPATIBLE_INPUT,
     	                             "Input file not readable!");
	} else {
		return CPL_ERROR_NONE;
	}
}


//*****************************************************************
// Read in GALAPAGOS Setup file
//*****************************************************************

cpl_error_code read_galafile(cpl_array *image, cpl_array *weight,
		cpl_array *directory, cpl_array *suffix, char *filename) {

	int i, j, ctr, count = 0;
	char line[FILENAME_MAX];
	char buffer[FILENAME_MAX];
	char *p1;
	char divide[FILENAME_MAX] = " ";
	FILE *fp;

	// Check input file

	if (filecheck(filename) != CPL_ERROR_NONE) {
		cpl_msg_error(cpl_func, "filecheck() in read_galafile() failed");
		return CPL_ERROR_FILE_NOT_FOUND;
	}

	fp = fopen(filename, "r");

	for(i = 0; (fgets(line, FILENAME_MAX, fp) != NULL); i++) {

		ctr = countChar(line, ' ', '/');

		if(ctr != 2) {
			cpl_msg_error(cpl_func, "Number of input files is not right! "
					"Or an error in file table occurred in line %d\n", i + 1);
			return CPL_ERROR_INCOMPATIBLE_INPUT;
		}

		count++;

		cpl_array_set_size(image, count);
		cpl_array_set_size(weight, count);
		cpl_array_set_size(directory, count);
		cpl_array_set_size(suffix, count);

		p1 = strtok(line, divide);
		for (j = 0; p1 != NULL; j++) {
			if(j == 0) {
				sprintf(buffer, "%s", p1);
				cpl_array_set_string(image, i, buffer);
			}
			if(j == 1) {
				sprintf(buffer, "%s", p1);
				cpl_array_set_string(weight, i, buffer);
			}
			if(j == 2) {
				sprintf(buffer, "%s", p1);
				cpl_array_set_string(directory, i, buffer);
			}
			if(j == 3) {
				sprintf(buffer, "%s", p1);
				strtok(buffer, ".");
				cpl_array_set_string(suffix, i, buffer);
				strtok(NULL, ".");
			}
			p1 = strtok(NULL, " ");
		}
	}

	fclose(fp);

	if(count == 0) {
		cpl_msg_info(cpl_func, "Empty input file for GALAPAGOS!\n");
		return CPL_ERROR_DATA_NOT_FOUND;
	}
	return CPL_ERROR_NONE;
}

//*******************************************************************
// Adjust and complete SExtractor setup file
//
// Completes GALAPAGOS input parameterlist with
// input image, weight image, directory and suffix dynamically
// to supply SExtractor with input parameters for every tile
//
// Author: Andreas
// Place: Doha University, Qatar
// Date: 2.5.2012
//********************************************************************

cpl_error_code adjust_galasetup(cpl_parameterlist *sex_setup,
		cpl_array *imagearray, cpl_array *weightarray,
		cpl_array *directory,  cpl_array *suffix,
		const int number) {

	const char *str;

	cpl_parameter *p;


	// Replace image and weight image path in case of multiple inputs

	p = cpl_parameterlist_find (sex_setup, "image");
	str = cpl_array_get_string (imagearray, number);
	cpl_parameter_set_string(p, str);

	p = cpl_parameterlist_find (sex_setup, "weightimage");
	str = cpl_array_get_string (weightarray, number);
	cpl_parameter_set_string(p, str);

	p = cpl_parameterlist_find (sex_setup, "directory");
	str = cpl_array_get_string (directory, number);
	cpl_parameter_set_string(p, str);

	p = cpl_parameterlist_find (sex_setup, "suffix");
	str = cpl_array_get_string (suffix, number);
	cpl_parameter_set_string(p, str);

	return CPL_ERROR_NONE;
}


//*******************************************************************
// Clean parameter list from useless or misleading parameters
//********************************************************************

cpl_error_code clean_galasetup(cpl_parameterlist *sex_setup) {

	char str[FILENAME_MAX] = "empty";

	cpl_parameter *p;


	// Replace image and weight image path in case of multiple inputs

	if((p = cpl_parameterlist_find (sex_setup, "image")) == CPL_ERROR_NONE) {
		cpl_parameter_set_string(p, str);
	}

	if((p = cpl_parameterlist_find (sex_setup, "weightimage")) == CPL_ERROR_NONE) {
		cpl_parameter_set_string(p, str);
	}

	if((p = cpl_parameterlist_find (sex_setup, "directory")) == CPL_ERROR_NONE) {
		cpl_parameter_set_string(p, str);
	}

	if((p = cpl_parameterlist_find (sex_setup, "suffix")) == CPL_ERROR_NONE) {
		cpl_parameter_set_string(p, str);
	}

	return CPL_ERROR_NONE;
}


/*!
 * Get the input for a specified parameter in the parameterlist.
 *
 * \b INPUT:
 *
 * \param sex_setup    cpl_parameterlist.
 *
 * \param fp     	   File point to file.
 *
 * \param line     	   Operating line in the input file.
 *
 * \param parname      Parameter name.
 *
 * \b OUTPUT:
 *
 * \param sex_setup    filled cpl_parameterlist.
 *
 * \return             HAS TO BE DISCUSSED!!
 *
 * This subfunction read in parameters from an external starting file for
 * galapagos. It turns special attention on the number of setup files in
 * the starting file. These additional setups are indicated in the starting
 * file by a "\" character at the beginning of the line, which will be
 * checked by the routine. This routine is also able to distinguish among
 * strings and double and case insensitive.
 */


int get_param(cpl_parameterlist *sex_setup, char *line, FILE *fp,
			  const char *parname) {

	int i;
	int n;
	double z;
	const char *name;
	char *p1;
	char buffer[FILENAME_MAX];
	char c = '\\';
	char *s;
	cpl_parameter *p;


	p = cpl_parameterlist_find(sex_setup, parname);
	name = cpl_parameter_get_name(p);
	n = strlen(parname);
	if(strncmp(name, line, n) == 0) {
		p1 = strtok(line, " ");

		// Better with for-loop over every token. This makes the program
		// more stable, e.g. when you have empty lines in the setup
		// file or '\' lines. Without it the program will crash in these cases.

		for (i = 0; p1 != NULL; i++) {
			if(i == 1) {

		// In this way the function is tuned to read in strings and doubles
		// but there is one disadvantage: If the double is 0 it will be
		// considered as a string, but its place in the parameterlist
		// is double an the program will get problems. What is to do???
		// Two separate functions?

				sprintf(buffer, "%s", p1);

				// separate handling for strings and doubles

				z = atof(buffer);
				if(z == 0) {

					// case insensitive

					for(s = p1; *s != '\0'; ++s) {
						*s = tolower(*s);
					}
					cpl_parameter_set_string(p, buffer);
				} else {
					cpl_parameter_set_double(p, z);
				}
			}
			p1 = strtok(NULL, " ");
		}

		while(fgets(line, FILENAME_MAX, fp) == memchr(line, c, 1)) {
			p1 = strtok(line, " ");
			for (i = 0; p1 != NULL; i++) {
				if(i == 1) {
					strcat(buffer, " ");
					strcat(buffer, p1);
					cpl_parameter_set_string(p, buffer);

					// separate control variable for each run
					// otherwise the control variables would add up and
					// the information would be meaningless

				}
				p1 = strtok(NULL, " ");
			}
		}
	}
	return 0;
}


//*******************************************************************
// Creates a combined catalog from all the SExtractor tiles
//
// Author: Andreas
// Place: Doha University, Qatar
// Date: 2.5.2012
//********************************************************************

cpl_error_code create_combcat(cpl_parameterlist *gala_setup,
		cpl_array *directory) {

	int i, number, combrow;
	char outdir[FILENAME_MAX];
	char outtab[FILENAME_MAX];
	char combcat[FILENAME_MAX];
	char tabfile[FILENAME_MAX];
	char str[FILENAME_MAX];
	char mkd[FILENAME_MAX] = "mkdir";
    struct stat st;
	cpl_table *combicat, *tiletab;
	cpl_parameter *p;
	cpl_propertylist *list;
	cpl_boolean sortval = CPL_FALSE;

	combicat = cpl_table_new(0);

	// Create output file for combcat

	p = cpl_parameterlist_find(gala_setup, "outdir");
	sprintf(outdir, "%s", cpl_parameter_get_string(p));
	p = cpl_parameterlist_find(gala_setup, "out_tab");
	sprintf(outtab, "%s", cpl_parameter_get_string(p));
	p = cpl_parameterlist_find(gala_setup, "sexcomb");
	sprintf(combcat, "%s", cpl_parameter_get_string(p));
	strcat(outdir, "/");

    if(stat(outdir, &st) != 0) {
		sprintf(str, "%s %s", mkd, outdir);
		if(system(str) != 0) {
			cpl_msg_error(cpl_func, "Unspecified problem with "
					"creating table folder %s.", outdir);
		}
	}

	strcat(outdir, combcat);

	// Load HDR SExtractor tables for every tile and insert in combcat

	number = cpl_array_get_size(directory);

	for(i = 0; i < number; i++) {

		// Load SExtractor output table from tile

		sprintf(tabfile, "%s%s%s", cpl_array_get_string(directory, i),
				"/", outtab);

		tiletab = cpl_table_load(tabfile, 1, 0);

		// Prepare combined catalog

		if(cpl_table_compare_structure(tiletab, combicat) != 0) {

			cpl_table_copy_structure(combicat, tiletab);
		}

		// Insert new tile catalog at the end of combined catalog

		combrow = (int)cpl_table_get_nrow(combicat);

		cpl_table_insert(combicat, tiletab, combrow);

		// Clean up

		cpl_table_delete(tiletab);
	}

	// Sort combined table according to magnitude

	list = cpl_propertylist_new();
	cpl_propertylist_append_bool(list, "MAG_BEST", sortval);
	cpl_table_sort(combicat, list);
	cpl_propertylist_delete(list);

	// Save combined catalog

	cpl_table_save(combicat, NULL, NULL, outdir, CPL_IO_CREATE);

	// Clean up

	cpl_table_delete(combicat);

	return CPL_ERROR_NONE;
}


//****************************************************************************
// Creating sky map
//
// This routine flags every detected object and gives the pixels inside of
// its KRON ellipse the value 1. Overlapping KRON ellipses stack. This means
// the overlapping area of two KRON ellipses gets a value of 2 and three
// overlapping KRON ellipses stack to pixel value 3. The sky is 0.
// value.
//
// INPUT: 		sky_setup :   Parameterlist containing setup information
//
// OUTPUT: 		skymap    :   Skymap image - save into skymap file
//
// ERRORS:      CPL_ERROR_FILE_NOT_FOUND
//				CPL_ERROR_DATA_NOT_FOUND
//				CPL_ERROR_NONE
//****************************************************************************

cpl_error_code create_skymap(cpl_parameterlist *gala_setup) {

	int i, x, y, xsize, ysize, row, xlo, xhi, ylo, yhi, q1 = 2, qq = 99,
			debug = 0, rank;
	double xc, yc, cxx, cxy, cyy, size, pixval, pixweight, Rad = 1,
	 	   R, aim, bim, theta, ghi, khi, offset;
	double pi = 3.14159265;
	char image[FILENAME_MAX];
	char cat[FILENAME_MAX];
	char skymapname[FILENAME_MAX];
	char mapdir[FILENAME_MAX];
	char weightimage[FILENAME_MAX];
	char directory[FILENAME_MAX];
	char outtab[FILENAME_MAX];
	cpl_image *skymap;
	cpl_table *tab;
	cpl_image *weight;
	cpl_parameter *p;
	cpl_errorstate error;
	time_t time1, time2;

    time(&time1);

	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Load data

    p = cpl_parameterlist_find(gala_setup, "image");
    sprintf(image, "%s", cpl_parameter_get_string(p));

	if(debug == 1) {
		printf("IMAGE IN SKYMAP: %s\n", image);
	}

    p = cpl_parameterlist_find(gala_setup, "directory");
    sprintf(directory, "%s", cpl_parameter_get_string(p));
    sprintf(mapdir, "%s", cpl_parameter_get_string(p));
    strcat(mapdir, "/");

    p = cpl_parameterlist_find(gala_setup, "out_tab");
    sprintf(outtab, "%s", cpl_parameter_get_string(p));

    strcat(directory, "/");
    strcat(directory, outtab);

	if(debug == 1) {
		printf("TABFILE: %s\n", directory);
	}

    p = cpl_parameterlist_find(gala_setup, "skymapname");
    sprintf(skymapname, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "size");
    size = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "offset");
    offset = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "weightimage");
    sprintf(weightimage, "%s", cpl_parameter_get_string(p));

    // Starting message

    if(rank == 0) {
    	cpl_msg_info(cpl_func, "Creating Skymaps.\n");
    }

	// Check input

    if(filecheck(image) != CPL_ERROR_NONE) {
    	cpl_msg_error(cpl_func, "Input image : %s not found!", image);
    	return CPL_ERROR_FILE_NOT_FOUND;
    }

    if(filecheck(directory) != CPL_ERROR_NONE) {
    	cpl_msg_error(cpl_func, "SExtractor output catalog : %s not found!",
    				  cat);
    	return CPL_ERROR_FILE_NOT_FOUND;
    }

    if(filecheck(weightimage) != CPL_ERROR_NONE) {
    	cpl_msg_error(cpl_func, "Weight image : %s not found!", weightimage);
    	return CPL_ERROR_FILE_NOT_FOUND;
    }

    if(size <= 0) {
    	size = 2;
    	cpl_msg_info (cpl_func, "Use default value for KRON ellipse "
    			"enlarging factor for skymap creation, size = 2.");
    }

    // Load data

    error = cpl_errorstate_get();

    if(error != CPL_ERROR_NONE) {
    	cpl_msg_error(cpl_func, "Errorstate was not CPL_ERROR_NONE "
    			"in create_skymap!"
    			"Is cleaned now!");
    	cpl_errorstate_set(CPL_ERROR_NONE);
    }

	skymap = cpl_image_load(image, CPL_TYPE_INT, 0, 0);

    xsize = cpl_image_get_size_x(skymap);
    ysize = cpl_image_get_size_y(skymap);

	if(xsize <= 0 || ysize <= 0) {
		cpl_msg_error(cpl_func, "In create_skymap() : Image not found!");
	}

    error = cpl_errorstate_get();

    if(error != CPL_ERROR_NONE) {
    	cpl_msg_error(cpl_func, "Errorstate occured while loading "
    			"skymap in create_skymap!"
    			"Is cleaned now!");
    	cpl_errorstate_set(CPL_ERROR_NONE);
    }

	weight = cpl_image_load(weightimage, CPL_TYPE_DOUBLE, 0, 0);

	if(cpl_image_get_size_x(weight) != xsize ||
			cpl_image_get_size_x(weight) <= 0) {

    	cpl_msg_error(cpl_func, "Weight image has size %d %d!"
    			"Trying other extension...\n",
    			(int)cpl_image_get_size_x(weight),
    			(int)cpl_image_get_size_y(weight));

		cpl_image_delete(weight);

		weight = cpl_image_load(weightimage, CPL_TYPE_DOUBLE, 0, 1);

		if(cpl_image_get_size_x(weight) != xsize) {

	    	cpl_msg_error(cpl_func, "Weight image has size %d %d!\n",
	    			(int)cpl_image_get_size_x(weight),
	    			(int)cpl_image_get_size_y(weight));
		} else {
			cpl_msg_error(cpl_func, "Weight image is found now!");
		}
	}

    error = cpl_errorstate_get();

    if(error != CPL_ERROR_NONE) {
    	cpl_msg_error(cpl_func, "Errorstate occured while loading "
    			"weight image in create_skymap!"
    			"Is cleaned now!");
    	cpl_errorstate_set(CPL_ERROR_NONE);
    }

	tab = cpl_table_load(directory, 1, 0);

    error = cpl_errorstate_get();

    if(error != CPL_ERROR_NONE) {
    	cpl_msg_error(cpl_func, "Errorstate occured while loading "
    			"table in create_skymap!"
    			"Is cleaned now!");
    	cpl_errorstate_set(CPL_ERROR_NONE);
    }

    row = (int)cpl_table_get_nrow(tab);

    if(row == 0) {
    	cpl_msg_error(cpl_func, "Zero length input table in "
    			"create_skymap()!");
        for(x = 1; x <= xsize; x++) {
        	for(y = 1; y <= ysize; y++) {
        		cpl_image_set(skymap, x, y, 0);
        	}
        }

    	for(x = 1; x < xsize; x++) {
    		for(y = 1; y < ysize; y++) {
    			pixweight = cpl_image_get(weight, x, y, &qq);
    			if(round(pixweight) == 0) {
    				cpl_image_set(skymap, x, y, -1);
    			}
    		}
    	}

    	strcat(mapdir, skymapname);

    	cpl_image_save(skymap, mapdir, CPL_BPP_32_SIGNED, NULL, CPL_IO_CREATE);

    	cpl_table_delete(tab);
    	cpl_image_delete(skymap);
    	cpl_image_delete(weight);

    	return CPL_ERROR_NONE;
    }

    for(x = 1; x <= xsize; x++) {
    	for(y = 1; y <= ysize; y++) {
    		cpl_image_set(skymap, x, y, 0);
    	}
    }

    for(i = 0; i < row; i++) {
    	xc  	=  cpl_table_get_double(tab, "X_IMAGE",     i, NULL);
    	yc      =  cpl_table_get_double(tab, "Y_IMAGE",     i, NULL);
		R       =  cpl_table_get_double(tab, "KRON_RADIUS", i, NULL);
		aim 	=  cpl_table_get_double(tab, "A_IMAGE",     i, NULL);
		bim 	=  cpl_table_get_double(tab, "B_IMAGE",     i, NULL);
		theta 	=  cpl_table_get_double(tab, "THETA_IMAGE", i, NULL);
		theta = 2 * pi * theta / 360;

		if(debug == 1) {
			printf("XC : %f\n", xc);
		}

		ghi = aim * R * size + offset;
		khi = bim * ((R * size) + (offset / aim));

		if(debug == 1) {
			printf("ghi:  %f   obj:  %d\n", ghi, i + 1);
		}

		cxx = (pow(cos(theta), 2)) / pow(ghi, 2) +
			  (pow(sin(theta), 2)) / pow(khi, 2);
		cyy = (pow(sin(theta), 2)) / pow(ghi, 2) +
			  (pow(cos(theta), 2)) / pow(khi, 2);
		cxy = 2 * cos(theta) * sin(theta) * (1 / pow(ghi, 2) - 1 / pow(khi, 2));

		get_loop_param(&i, &xlo, &xhi, &ylo, &yhi, &xsize, &ysize, &size, tab);

		for(x = xlo; x < xhi; x++) {
			for(y = ylo; y < yhi; y++) {
				if(cxx * ((x - xc) * (x - xc)) + cyy * ((y - yc) *
				  (y - yc)) + cxy * (x - xc) * (y - yc) < Rad * Rad) {
					pixval = cpl_image_get(skymap, x + 1, y + 1, &q1);
					cpl_image_set(skymap, x + 1, y + 1, pixval + 1);
				}
			}
		}
    }

    xsize = cpl_image_get_size_x(weight);
    ysize = cpl_image_get_size_y(weight);

	if(xsize <= 0 || ysize <= 0) {
		cpl_msg_error(cpl_func, "In create_skymap() : Weight image not found!");
	}

	for(x = 1; x < xsize; x++) {
		for(y = 1; y < ysize; y++) {
			pixweight = cpl_image_get(weight, x, y, &qq);
			if(round(pixweight) == 0) {
				cpl_image_set(skymap, x, y, -1);
			}
		}
	}

	strcat(mapdir, skymapname);

	if(debug == 1) {
		printf("SKYMAPFILE: %s\n", mapdir);
	}

	cpl_image_save(skymap, mapdir, CPL_BPP_32_SIGNED, NULL, CPL_IO_CREATE);

	cpl_table_delete(tab);
	cpl_image_delete(skymap);
	cpl_image_delete(weight);

	if(rank == 0) {
		cpl_msg_info(cpl_func, "Skymap done!\n");
	}
    time(&time2);
    printf("Skymap for %s done in %.2f seconds!\n", mapdir, difftime(time2, time1));

	return CPL_ERROR_NONE;
}

//***************************************************************************
// Extracting the postage stamp loop parameters from the cpl_table information.
//***************************************************************************

cpl_error_code get_loop_param(const int *i, int *xlo, int *xhi, int *ylo,
							   int *yhi, const int *x, const int *y,
							   const double *sizefac, cpl_table *tab) {

	int minor, major, xs, ys;
	double xfac, yfac, rad, ang, theta;
	double pi = 3.14159265;


	rad = cpl_table_get_double(tab, "A_IMAGE", *i, NULL) *
	      cpl_table_get_double(tab, "KRON_RADIUS", *i, NULL);

	ang = cpl_table_get_double(tab, "THETA_IMAGE", *i, NULL);
	ang = 2 * pi * ang / 360;

	xfac = rad * (fabs(sin(ang)) +
	       (1 - cpl_table_get_double(tab, "ELLIPTICITY", *i, NULL)) *
	       fabs(cos(ang)));

	if(xfac < 10) {
		xfac = 10;
	}

	xfac *= *sizefac;

	yfac = rad * (fabs(cos(ang)) +
	       (1 - cpl_table_get_double(tab, "ELLIPTICITY", *i, NULL)) *
	       fabs(sin(ang)));

	if(yfac < 10) {
		yfac = 10;
	}

	yfac *= *sizefac;

	major = 0.5 * (xfac + yfac + fabs(xfac - yfac));
	minor = 0.5 * (xfac + yfac - fabs(xfac - yfac));

	theta = cpl_table_get_double(tab, "THETA_IMAGE", *i, NULL);

	theta = fabs(theta);

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

	*xlo = round(cpl_table_get_double(tab, "X_IMAGE", *i, NULL) - xfac);
	*xhi = round(cpl_table_get_double(tab, "X_IMAGE", *i, NULL) + xfac);
	*ylo = round(cpl_table_get_double(tab, "Y_IMAGE", *i, NULL) - yfac);
	*yhi = round(cpl_table_get_double(tab, "Y_IMAGE", *i, NULL) + yfac);

	xs = *xhi - *xlo;
	ys = *yhi - *ylo;

	*xlo = *xlo - xs * (*sizefac - 1);
	*ylo = *ylo - ys * (*sizefac - 1);
	*xhi = *xhi + xs * (*sizefac - 1);
	*yhi = *yhi + ys * (*sizefac - 1);


	if(*xlo <= 0) {
	 	*xlo = 1;
	}
	if(*xhi > *x) {
	    *xhi = *x;
	}
	if(*ylo <= 0) {
	  	*ylo = 1;
	}
	if(*yhi > *y) {
	    *yhi = *y;
	}

	return CPL_ERROR_NONE;
}


//***************************************************************************
// Checks if user input is valid
//
// Check if user files are accessable and if input parameters make
// sense.
//
// Author: Andreas
// Date: 07.05.2012
//
// INPUT / OUTPUT: cpl_parameterlist *gala_setup     Parameterlist containing
//													 user input data
//
// ERRORS: CPL_ERROR_FILE_NOT_FOUND         Input file was not found
//		   CPL_ERROR_NONE                   No error occured
//***************************************************************************

cpl_error_code check_gala_input(cpl_parameterlist *gala_setup) {

	cpl_parameter *p;

	double exptime, zerop, enlarge, size, offset, stampfac, nslope,
		bandsize, isodist, expand, psffactor, convbox, platescale,
		secenlarge, magexclude;

	char gala_file[FILENAME_MAX];
	char sex_par[FILENAME_MAX];
	char out_par[FILENAME_MAX];
	char psf[FILENAME_MAX];

	p = cpl_parameterlist_find(gala_setup, "galafile");
	sprintf(gala_file, "%s", cpl_parameter_get_string(p));
	if(filecheck(gala_file) != CPL_ERROR_NONE) {
		cpl_msg_error(cpl_func, "GALAPAGOS input files %s not found!",
				gala_file);
		return CPL_ERROR_FILE_NOT_FOUND;
	}
	p = cpl_parameterlist_find(gala_setup, "sex_par");
	sprintf(sex_par, "%s", cpl_parameter_get_string(p));
	if(filecheck(sex_par) != CPL_ERROR_NONE) {
		cpl_msg_error(cpl_func, "SExtractor .param files %s not found!",
				sex_par);
		return CPL_ERROR_FILE_NOT_FOUND;
	}
	p = cpl_parameterlist_find(gala_setup, "out_par");
	sprintf(out_par, "%s", cpl_parameter_get_string(p));

	if(filecheck(out_par) != CPL_ERROR_NONE) {
		cpl_msg_error(cpl_func, "SExtractor out_param files %s not found!",
				out_par);
		return CPL_ERROR_FILE_NOT_FOUND;
	}
	p = cpl_parameterlist_find(gala_setup, "psf");
	sprintf(psf, "%s", cpl_parameter_get_string(p));
	if(filecheck(psf) != CPL_ERROR_NONE) {
		cpl_msg_error(cpl_func, "Psf files %s not found!",
				psf);
		return CPL_ERROR_FILE_NOT_FOUND;
	}
	p = cpl_parameterlist_find(gala_setup, "exptime");
	exptime = cpl_parameter_get_double(p);
	if(exptime <= 0) {
		cpl_msg_error(cpl_func, "Invalid input for exposure time %f s!"
				"Exptime = 1s is used.", exptime);
		exptime = 1;
	}
	p = cpl_parameterlist_find(gala_setup, "zerop");
	zerop = cpl_parameter_get_double(p);
	if(zerop <= 0) {
		cpl_msg_error(cpl_func, "Invalid input for magnitude zeropoint %f!"
				"Zeropoint = 1 is used.", zerop);
		zerop = 1;
	}
	p = cpl_parameterlist_find(gala_setup, "enlarge");
	enlarge = cpl_parameter_get_double(p);
	if(enlarge <= 0) {
		cpl_msg_error(cpl_func, "Invalid input for enlarging factor %f!"
				"Enlarge = 10 is used.", enlarge);
		enlarge = 10;
	}
	p = cpl_parameterlist_find(gala_setup, "size");
	size = cpl_parameter_get_double(p);
	if(size <= 0) {
		cpl_msg_error(cpl_func, "Invalid input for enlarging factor %f!"
				"Size = 3 is used.", size);
		size = 3;
	}
	p = cpl_parameterlist_find(gala_setup, "offset");
	offset = cpl_parameter_get_double(p);
	offset = round(offset);
	if(offset < 0) {
		cpl_msg_error(cpl_func, "Invalid input for offset factor %f!"
				"Offset = 20 is used.", offset);
		offset = 10;
	}
	p = cpl_parameterlist_find(gala_setup, "stampfac");
	stampfac = cpl_parameter_get_double(p);
	if(stampfac <= 0) {
		cpl_msg_error(cpl_func, "Invalid input for stamp enlarging factor %f!"
				"Stampfac = 2.5 is used.", stampfac);
		stampfac = 2.5;
	}
	p = cpl_parameterlist_find(gala_setup, "nslope");
	nslope = cpl_parameter_get_double(p);
	nslope = round(nslope);
	if(nslope <= 0) {
		cpl_msg_error(cpl_func, "Invalid input for nslope %f!"
				"Nslope = 15 is used.", nslope);
		nslope = 15;
	}
	p = cpl_parameterlist_find(gala_setup, "bandsize");
	bandsize = cpl_parameter_get_double(p);
	bandsize = round(bandsize);
	if(bandsize <= 0) {
		cpl_msg_error(cpl_func, "Invalid input for bandsize %f!"
				"Bandsize = 60 is used.", bandsize);
		bandsize = 60;
	}
	p = cpl_parameterlist_find(gala_setup, "isodist");
	isodist = cpl_parameter_get_double(p);
	isodist = round(isodist);
	if(isodist < 0) {
		cpl_msg_error(cpl_func, "Invalid input for isodist %f!"
				"Isodist = 30 is used.", isodist);
		isodist = 30;
	}
	p = cpl_parameterlist_find(gala_setup, "expand");
	expand = cpl_parameter_get_double(p);
	if(expand <= 0) {
		cpl_msg_error(cpl_func, "Invalid input for expanding factor %f!"
				"Expand = 3 is used.", expand);
		expand = 3;
	}
	p = cpl_parameterlist_find(gala_setup, "psffactor");
	psffactor = cpl_parameter_get_double(p);
	if(psffactor <= 0) {
		cpl_msg_error(cpl_func, "Invalid input for psffactor %f!"
				"Psffactor = 1 is used.", psffactor);
		psffactor = 1;
	}
	p = cpl_parameterlist_find(gala_setup, "convbox");
	convbox = cpl_parameter_get_double(p);
	if(convbox <= 0) {
		cpl_msg_error(cpl_func, "Invalid input for convbox %f!"
				"Convbox = 100 is used.", convbox);
		convbox = 100;
	}
	p = cpl_parameterlist_find(gala_setup, "platescale");
	platescale = cpl_parameter_get_double(p);
	if(platescale <= 0) {
		cpl_msg_error(cpl_func, "Invalid input for GALFIT platescale %f!"
				"Platescale = 0.03 is used.", platescale);
		platescale = 0.03;
	}
	p = cpl_parameterlist_find(gala_setup, "secenlarge");
	secenlarge = cpl_parameter_get_double(p);
	if(secenlarge <= 0) {
		cpl_msg_error(cpl_func, "Invalid input for expanding factor "
				"secenlarge %f! Secenlarge = 20 is used.", secenlarge);
		secenlarge = 3;
	}
	p = cpl_parameterlist_find(gala_setup, "magexclude");
	magexclude = cpl_parameter_get_double(p);
	if(magexclude <= 0) {
		cpl_msg_error(cpl_func, "Invalid input for magexclude %f!"
				"Magexclude = 5 is used.", magexclude);
		magexclude = 3;
	}

	return CPL_ERROR_NONE;
}


//********************************************************************
// Background estimation routine
//********************************************************************

cpl_error_code estimate_background(cpl_parameterlist *gala_setup) {

	int i, j, l, m, x, y, xsize, ysize, z, sexnum, slopecount, rank,
		xlo, xhi, ylo, yhi, mod, randmod, skycontrol, nslope, qq = 99,
		debug = 0;
	long int npix;

	double bandsize, expand, offset, stampfac, finalback,
		xc, yc, R, aim, bim, theta, ghi, khi, cxx, cxy, cyy,
		kha, gha, cxx1, cxy1, cyy1, pix, me, rms, slope, Rad = 1;

	double pi = 3.14159265;

	char image[FILENAME_MAX];
	char weightimage[FILENAME_MAX];
	char outdir[FILENAME_MAX];
	char out_tab[FILENAME_MAX];
	char suffix[FILENAME_MAX];
	char skymapname[FILENAME_MAX];
	char skymapfile[FILENAME_MAX];
	char outsky[FILENAME_MAX];
	char outskyfile[FILENAME_MAX];
	char cat_tile[FILENAME_MAX];
	char directory[FILENAME_MAX];
	char savefile[FILENAME_MAX];

	cpl_table *tab;
	cpl_image *backim;
	cpl_image *skymap;
	cpl_array *ringpix, *meanback, *slopecalc;
	cpl_parameter *p;
	cpl_boolean clip = CPL_FALSE;

	FILE *fp;

    p = cpl_parameterlist_find(gala_setup, "image");
    sprintf(image, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "weightimage");
    sprintf(weightimage, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "outdir");
    sprintf(outdir, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "out_tab");
    sprintf(out_tab, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "suffix");
    sprintf(suffix, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "skymapname");
    sprintf(skymapname, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "nslope");
    nslope = (int)cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "bandsize");
    bandsize = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "expand");
    expand = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "offset");
    offset = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "stampfac");
    stampfac = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "outsky");
    sprintf(outsky, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "directory");
    sprintf(directory, "%s", cpl_parameter_get_string(p));

    // Prepare filename paths

    sprintf(cat_tile, "%s%s%s", directory, "/", out_tab);
    sprintf(skymapfile, "%s%s%s", directory, "/", skymapname);

	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(debug == 1) {

		printf("IMAGE: %s done by process No %d.\n", image, rank);
		printf("DIRECTORY: %s done by process No %d.\n", directory, rank);
		printf("SKYMAPFILE: %s (process No %d)\n", skymapfile, rank);
		printf("SEXTABFILE: %s (process No %d)\n", cat_tile, rank);
		printf("SKYMAPFILE: %s (process No %d)\n", skymapfile, rank);
	}

    // Starting message

	if(rank == 0) {
		cpl_msg_info(cpl_func, "Working on background estimation.");
	}

	// Find global sky value and pixel scatter - write into file

    sprintf(savefile, "%s%s", directory, "/global_sky");

	global_sky(image, skymapfile, savefile);

	// Obtain objects parameters by SExtractor output catalog

	tab = cpl_table_load(cat_tile, 1, 0);

	if(tab == NULL) {
		cpl_msg_error(cpl_func, "Unspecified error in "
			"estimate_background_parallel()! "
			"Error with table loading from file %s "
			"by Thread No %d!", cat_tile, rank);
	}

//	cpl_table_dump(tab, 0, 5, NULL);

	backim = cpl_image_load(image, CPL_TYPE_DOUBLE, 0, 0);
	skymap = cpl_image_load(skymapfile, CPL_TYPE_DOUBLE, 0, 0);
	ringpix = cpl_array_new(0, CPL_TYPE_DOUBLE);
	xsize  = cpl_image_get_size_x(backim);
	ysize  = cpl_image_get_size_y(backim);
	z = cpl_table_get_nrow(tab);

	if(debug == 1) {
		printf("%d\n", z);
	}

	// Add additional column "BACKGROUND" to SExtractor output table

	cpl_table_new_column(tab, "GALA_BACKGROUND", CPL_TYPE_DOUBLE);

	// Start procedure for every object

	for(i = 0; i < z; i++) {

		// Prepare file containing sky

		sexnum = cpl_table_get(tab, "NUMBER", i, NULL);
	    sprintf(outskyfile, "%s%s%s%s%d", directory, "/", outsky, "_", sexnum);

		if(debug == 1) {
			printf("OUTSKYFILE: %s\n", outskyfile);
		}

	    // Continue procedure only if file is not existing yet

		if(access(outskyfile, 00) != 0) {

	    	// New object - "clean" background array

	    	meanback = cpl_array_new(0, CPL_TYPE_DOUBLE);
			slopecalc = cpl_array_new(nslope, CPL_TYPE_DOUBLE);

			// New object - reset control variables, reinitialize variables

			finalback = 0;
			slopecount = 0;

			// Get SExtractor parameters

			xc = cpl_table_get_double(tab, "X_IMAGE", i, NULL);
			yc = cpl_table_get_double(tab, "Y_IMAGE", i, NULL);


			if(debug == 1) {
				printf("X_IMAGE : %f\n", xc);
				printf("Y_IMAGE : %f\n", yc);
			}

			R       =  cpl_table_get_double(tab, "KRON_RADIUS", i, NULL);
			aim 	=  cpl_table_get_double(tab, "A_IMAGE", i, NULL);
			bim 	=  cpl_table_get_double(tab, "B_IMAGE", i, NULL);
			theta 	=  cpl_table_get_double(tab, "THETA_IMAGE", i, NULL);

			// Theta in radians

			theta = 2 * pi * theta / 360;

			// Calculate half-major axis und half-minor axis

			ghi = aim * R * expand + offset;
			khi = bim * ((R * expand) + (offset / aim));

			// Loop over annuli

			for(j = 0; slopecount < 3; j++) {

				// Reset count variable

				npix = 0;

				cpl_array_set_size(meanback, j + 1);

				// Within each loop, semi- major and semi-minor axis are
				// enlarged for band_size.

				if(j > 0) {
					ghi = ghi + bandsize;
					khi = khi + bandsize;
				}

				// Calculate inner ellipse parameters

				cxx = (pow(cos(theta), 2)) / pow(ghi, 2) +
						(pow(sin(theta), 2)) / pow(khi, 2);
				cyy = (pow(sin(theta), 2)) / pow(ghi, 2) +
						(pow(cos(theta), 2)) / pow(khi, 2);
				cxy = 2 * cos(theta) * sin(theta) *
						(1 / pow(ghi, 2) - 1 / pow(khi, 2));

				// Calculate outer ellipse parameters

				gha = ghi + bandsize;
				kha = khi + bandsize;

				cxx1 = cos(theta) * cos(theta) / pow(gha, 2) +
						sin(theta) * sin(theta) / pow(kha, 2);
				cyy1 = sin(theta) * sin(theta) / pow(gha, 2) +
						cos(theta) * cos(theta) / pow(kha, 2);
				cxy1 = 2 * cos(theta) * sin(theta) *
						(1 / pow(gha, 2) - 1 / pow(kha, 2));

				// Loop over every pixel in the postage stamp

				if(debug == 1) {

					printf("XC : %f\n", xc);
					printf("AIM : %f\n", aim);
					printf("R : %f\n", R);
					printf("expand : %f\n", expand);
					printf("offset : %f\n", offset);
					printf("stampfac : %f\n", stampfac);
					printf("j : %d\n", j);
					printf("bandsize : %f\n", bandsize);
				}


				xlo = round(xc - ((aim * R * expand + offset) * stampfac) -
					        j * bandsize);
				if(xlo <= 0) {
					xlo = 1;
				}
				xhi = round(xc + ((aim * R * expand + offset) * stampfac) +
					        j * bandsize);
				if(xhi >= xsize) {
					xhi = xsize - 1;
				}
				ylo = round(yc - ((aim * R * expand + offset) * stampfac) -
					        j * bandsize);
				if(ylo <= 0) {
					ylo = 1;
				}
				yhi = round(yc + ((aim * R * expand + offset) * stampfac) +
						    j * bandsize);
				if(yhi >= ysize) {
					yhi = ysize - 1;
				}

				// Acceleration of the procedure - take pixels randomly

				mod = round(sqrt(j + 1));
				randmod = (rand() % mod) + mod;

				if(debug == 1) {
					printf("XLO: %d\n", xlo);
				}

				for(x = xlo + 1; x <= xhi; x += randmod) {
					for(y = ylo + 1; y <= yhi; y += randmod) {

//				for(x = xlo; x < xhi; x++) {
//					for(y = ylo; y < yhi; y++) {

						// Comparison with skymap

						skycontrol = cpl_image_get(skymap, x, y, &qq);

						if(cxx * ((x - xc) * (x - xc)) + cyy * ((y - yc) *
						   (y - yc)) + cxy * (x - xc) * (y - yc) > Rad * Rad &&
					   	   cxx1 * ((x - xc) * (x - xc)) + cyy1 * ((y - yc) *
						   (y - yc)) + cxy1 * (x - xc) * (y - yc) < Rad * Rad
						   && skycontrol == 0) {

							// Count the number of pixels in each annuli

							cpl_array_set_size(ringpix, npix + 1);

							// Integrate over the pixel flux

							pix = cpl_image_get(backim, x, y, &qq);
							cpl_array_set(ringpix, npix, pix);
							npix++;
						}
					}
				}

				// Calculate the mean background flux :

				sc_basic_clipmean(&me, &rms, ringpix, clip);

				if(j < nslope) {
					cpl_array_set(slopecalc, j, me);

					if(debug == 1) {

					cpl_array_dump(slopecalc, 0, cpl_array_get_size(slopecalc),
																		NULL);
					}
				}

				if(debug == 1) {
					printf("-------------------- NEW RING --------------------\n");
					printf("Ring # %3.d    Mean Background : %f\n", j + 1, me);
				}

				// Sorting array containing the last nslope measuring points

				if(j >= nslope) {
					for(l = 0; l < nslope - 1; l++) {
						cpl_array_set(slopecalc, l,
										cpl_array_get(slopecalc, l + 1, NULL));
					}
					cpl_array_set(slopecalc, nslope - 1, me);

					if(debug == 1) {

						cpl_array_dump(slopecalc, 0, cpl_array_get_size(slopecalc),
									NULL);
					}

					// Calculate slope in nslope measuring points

					slope = calculate_slope(slopecalc, &nslope);

					if(debug == 1) {
						printf("ANNULUS  %d - %d      SLOPE   :    "
								"%f\n", j - nslope + 2, j + 1, slope);
					}

					// Avoid endless loops

					if(j > round(xsize / bandsize)) {
						slopecount = 3;
					}

					// Check if positive - then increment counting variable

					if(slope >= 0) {
						slopecount++;

						// If slope is positive for a second time -
						// return background value

						if(slopecount == 2) {
							for(m = 0; m < nslope; m++) {
								finalback += cpl_array_get(slopecalc, m, NULL);
							}

							// Final background as mean value of all nslope
							// measuring points

							finalback /= nslope;
						}
					}
				}
			}

			if(debug == 1) {
				printf("ESTIMATED BACKGROUND VALUE FOR OBJECT NUMBER  %d BY "
					"PROCESSOR No %d: %f\n", i + 1, rank, finalback);
			}

			// Write output

			fp = fopen(outskyfile, "w");

			fprintf(fp, "%f", finalback);

			fclose(fp);

			cpl_array_delete(meanback);
			cpl_array_delete(slopecalc);
	    }
	}

	// Clean up

	cpl_table_delete(tab);
	cpl_image_delete(backim);
	cpl_image_delete(skymap);
	cpl_array_delete(ringpix);

	return CPL_ERROR_NONE;
}


//********************************************************************
// Write background values into combined catalog
//
// INPUT: All required variables are read from a cpl_parameterlist.
//        Should contain an output directory "outdir" where the
//        combined catalog is located and its name "combcat".
//        Additionally a filename for the sky file "outsky" is
//        required.
//********************************************************************

cpl_error_code write_sky_output(cpl_parameterlist *gala_setup) {

	int debug = 0;

	long i, z;

	double sky;

	char combcatfile[FILENAME_MAX];
	char outdir[FILENAME_MAX];
	char cat_dir[FILENAME_MAX];
	char td[FILENAME_MAX];
	char skyfile[FILENAME_MAX];
	char outsky[FILENAME_MAX];
	char value[FILENAME_MAX];

	cpl_table *tab;
	cpl_parameter *p;

	FILE *fp;

	// Load parameters from parameter list

    p = cpl_parameterlist_find(gala_setup, "outdir");
    sprintf(outdir, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "sexcomb");
    sprintf(combcatfile, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "outsky");
    sprintf(outsky, "%s", cpl_parameter_get_string(p));

    // Prepare catalog filename

    sprintf(cat_dir, "%s%s%s", outdir, "/", combcatfile);

    // Load catalog

    tab = cpl_table_load(cat_dir, 1, 0);

	if(tab == NULL) {
		cpl_msg_error(cpl_func, "Unspecified error in "
				"write_sky_output()! "
				"Error with table loading from file %s! "
				"Use combined catalog routine.",
				cat_dir);

		cpl_table_delete(tab);

		return CPL_ERROR_DATA_NOT_FOUND;
	}

	// Check length and input

	z = (long)cpl_table_get_nrow(tab);

	if(z <= 0) {
		cpl_msg_error(cpl_func, "Unspecified error in "
				"write_sky_output()! "
				"Table %s contains no rows! Aborting...",
				cat_dir);

		cpl_table_delete(tab);

		return CPL_ERROR_DATA_NOT_FOUND;
	}

	// Add additional column "BACKGROUND" to SExtractor output table

	cpl_table_new_column(tab, "GALA_BACKGROUND", CPL_TYPE_DOUBLE);

	// Loop over every object

	for(i = 0; i < z; i++) {

		// Prepare output path for sky file

		sprintf(td, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", i));
		sprintf(skyfile, "%s%s%s%s%d", td, "/", outsky, "_",
				cpl_table_get_int(tab, "NUMBER", i, NULL));

		// Check if file is existing

		if(access(skyfile, 00) == 0) {

			// Read sky value from file

    		fp = fopen(skyfile, "r");

    		fgets(value, FILENAME_MAX, fp) ;

    		fclose(fp);

    		// Convert into double

    		sky = atof(value);

    		if(debug == 1) {

    			printf("MASTER : Setze den Wert %f in den an Position %ld "
    					"in Table in "
    					"die Spalte GALA_BACKGROUND!\n", sky, i);
    		}

    		// Set value into table

    		if(cpl_table_set_double(tab, "GALA_BACKGROUND", i, sky) != CPL_ERROR_NONE) {
    			cpl_msg_error(cpl_func, "Error while write sky values into table in the "
    					"function write_sky_output()!");
    		}

		} else {
			cpl_msg_error(cpl_func, "In write_sky_output(): File containing "
					"sky value for object %s not found!", skyfile);
		}
	}

	// Save table

	if(cpl_table_save(tab, NULL, NULL, cat_dir, CPL_IO_CREATE) != CPL_ERROR_NONE) {
		cpl_msg_error(cpl_func, "Unspecified problem when saving table in "
				"write_sky_output()!");
	}

	// Clean up

	cpl_table_delete(tab);

	return CPL_ERROR_NONE;
}


double global_sky (const char *imagefile, const char *mapfile, const char *savefile) {

	int debug = 0,
		xsize,
		ysize,
		xsize_map,
		ysize_map,
		x,
		y,
		q = 9,
		qq = 99,
		rank;

	long npix = 0,
		 pixmax = 1000000;

	double mean,
		   rms;

	cpl_array *arr;

	cpl_boolean clip = CPL_TRUE;

	cpl_image *image,
			  *map;

	FILE *fp;

	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank == 0) {
		cpl_msg_info(cpl_func, "Estimating global sky and pixel scatter.");
	}

	/* Check access and load skymap and STAGES science image */

	if(access(imagefile, 00) != 0) {
		cpl_msg_error(cpl_func, "Imagefile %s is not accessable! Aborting...",
				imagefile);
		cpl_end();
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	if(access(mapfile, 00) != 0) {
		cpl_msg_error(cpl_func, "Mapfile %s is not accessable! Aborting...",
				mapfile);
		cpl_end();
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	image = cpl_image_load(imagefile, CPL_TYPE_DOUBLE, 0, 0);

	map = cpl_image_load(mapfile, CPL_TYPE_INT, 0, 0);

	/* Check input */

	xsize = cpl_image_get_size_x(image);
	ysize = cpl_image_get_size_y(image);
	if(xsize <= 0 || ysize <= 0) {
		cpl_msg_error(cpl_func, "Image %s has no size! Aborting...", imagefile);
		cpl_image_delete(image);
		cpl_image_delete(map);
		cpl_memory_dump();
		cpl_end();
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	xsize_map = cpl_image_get_size_x(map);
	ysize_map = cpl_image_get_size_y(map);
	if(xsize_map <= 0 || ysize_map <= 0) {
		cpl_msg_error(cpl_func, "Skymap %s has no size! Aborting...", mapfile);
		cpl_image_delete(image);
		cpl_image_delete(map);
		cpl_memory_dump();
		cpl_end();
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	if(xsize != xsize_map || ysize != ysize_map) {
		cpl_msg_error(cpl_func, "Mismatching size for skymap and image!!! "
				"Check input!");
	}

	/* Determine global sky value */

	arr = cpl_array_new(pixmax, CPL_TYPE_DOUBLE);

	srand((unsigned)time(NULL));

	while(npix < pixmax) {

		/* Find an arbitrary pixel position in the image */

		x = (rand() % xsize) + 1;
		y = (rand() % ysize) + 1;

		if(debug == 1) {
			printf("PIXEL POSITION (X,Y) : (%d,%d)\n", x, y);
		}

		/* Check skymap value */

		if(cpl_image_get(map, x, y, &q) == 0) {

			/* Sky map has 0 value - set pixel value in array */

			cpl_array_set_double(arr, npix, cpl_image_get(image, x, y, &qq));

			npix++;
		}
	}

	/* Compute mean and rms */

	sc_basic_clipmean(&mean, &rms, arr, clip);

	/* Write value into file */

	fp = fopen(savefile, "w");

	fprintf(fp, "%f\n", mean);
	fprintf(fp, "%f\n", rms);

	fclose(fp);

	/* Clean up */

	cpl_array_delete(arr);

	cpl_image_delete(image);

	cpl_image_delete(map);

	return mean;
}

//****************************************************************************
// Estimating slope for nslope measuring points
//****************************************************************************

double calculate_slope(cpl_array *slopecalc, const int *nslope) {
	int i;
	double left = 0, right = 0, xmean, slope, tmp;

	tmp = (double)*nslope;

	xmean = ((tmp + 1) / 2);

	for(i = 0; i < *nslope; i++) {
		if(i + 1 < xmean) {
			left += cpl_array_get_double(slopecalc, i, NULL);
		}
		if(i + 1 > xmean) {
			right += cpl_array_get_double(slopecalc, i, NULL);
		}
	}

	if(left > right) {
		slope = -1;
	}

	if(left == right) {
		slope = 0;
	}

	if(left < right) {
		slope = 1;
	}

	return slope;
}


//***************************************************************************
// Run GALFIT - new cluster version
//***************************************************************************

cpl_error_code run_galfit_parallel_NEW(cpl_parameterlist *gala_setup) {

	struct fitlist *obj;

	int xsize,
		k,
		start,
		rank,
		numprocs,
		contribmax,
		nobj = 0,
		synch = 0,
		jobsdone = 0,
		debug = 0,
		sent = 0,
		tfdone = 0;

	long i,
		 j = -2,
		 ip,
		 nrow,
		 njobs,
		 nloop = 0,
		 slaverank[2],
		 smsg[2];

	double secenlarge,
		   frac,
		   offset,
		   magexclude,
		   distmax,
		   platescale,
		   fluxextend,
		   magzero,
		   magcrit,
		   re_max,
		   mag_min,
		   mag_max,
		   time = 0,
		   time2 = 0,
		   stime1 = 0,
		   stime2 = 0,
		   stime3 = 0,
		   stime4 = 0,
		   stime5 = 0,
		   stime6 = 0,
		   stime7 = 0,
		   stime8 = 0,
		   stime9 = 0,
		   stime10 = 0,
		   masktime = 0,
		   setuptime = 0,
		   constrainttime = 0,
		   waittime = 0,
		   galatime = 0,
		   galfittime = 0,
	   	   waittimeh = 0,
	   	   galatimeh = 0,
	   	   galfittimeh = 0,
	   	   masktimeh = 0,
	   	   setuptimeh = 0,
	   	   constrainttimeh = 0;

	char tabfile[FILENAME_MAX],
		 outdir[FILENAME_MAX],
	 	 combtab[FILENAME_MAX],
	 	 object[FILENAME_MAX],
	 	 imgblock[FILENAME_MAX],
	 	 directory[FILENAME_MAX],
	 	 badpix[FILENAME_MAX],
	 	 out_seg[FILENAME_MAX],
	 	 segimage[FILENAME_MAX],
		 weightimage[FILENAME_MAX],
		 maskfilecontrol[FILENAME_MAX],
		 stampfile[FILENAME_MAX],
		 stampname[FILENAME_MAX],
		 constraints[FILENAME_MAX],
	 	 constraintfile[FILENAME_MAX],
		 galfitset[FILENAME_MAX],
		 galsetfile[FILENAME_MAX],
		 galfitfile[FILENAME_MAX],
		 str[FILENAME_MAX],
		 path[FILENAME_MAX],
		 copyfile[FILENAME_MAX],
		 timefile[FILENAME_MAX],
	     tfile[FILENAME_MAX];

	char fitfile[FILENAME_MAX],
	     fitlog[FILENAME_MAX],
	     curr_dir[FILENAME_MAX];



	char *buf = NULL;

	size_t size = 0;

	FILE *fp,
		 *fp_t;

	cpl_array *done, *fitdata;

	cpl_errorstate error,
				   errornone = CPL_ERROR_NONE;

	cpl_parameter *p;

	cpl_propertylist *header;

	cpl_table *tab;

	cpl_image *weight,
			  *seg;

	MPI_Status status;

	// Clear errorstate

	error = cpl_errorstate_get();

	if(error != CPL_ERROR_NONE) {

		cpl_msg_error(cpl_func, "Errorstate existed before "
				"run_GALFIT_parallel() !!!! Is cleaned now...");

		cpl_errorstate_set(errornone);
	}

	// Find out process rank

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// find out number of processes

	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	// Get setup data

    p = cpl_parameterlist_find(gala_setup, "outdir");
    sprintf(outdir, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "sexcomb");
    sprintf(combtab, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "secenlarge");
    secenlarge = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magexclude");
    magexclude = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "offset");
    offset = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "contribmax");
    contribmax = (int)cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "distmax");
    distmax = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "platescale");
    platescale = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "fluxextend");
    fluxextend = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magzero");
    magzero = cpl_parameter_get_double(p);

	p = cpl_parameterlist_find(gala_setup, "magcrit");
	magcrit = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "object");
    sprintf(object, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "badpix");
    sprintf(badpix, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "out_seg");
    sprintf(out_seg, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "stampname");
    sprintf(stampname, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "stampfile");
    sprintf(stampfile, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "constraints");
    sprintf(constraints, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "re_max");
    re_max = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "mag_min");
    mag_min = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "mag_max");
    mag_max = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "galfitset");
    sprintf(galfitset, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "path");
    sprintf(path, "%s", cpl_parameter_get_string(p));

    // MASTER job

    if(rank == 0) {

    	// Find current working directory

    	sprintf(curr_dir, "%s", getcwd(buf, size));

    	// Load table

    	sprintf(tabfile, "%s%s%s", outdir, "/", combtab);

    	if(access(tabfile, 00) != 0) {
    		cpl_msg_error(cpl_func, "Output table is not accessable "
    				"in run_GALFIT_parallel(). Aborting...");
    		return CPL_ERROR_DATA_NOT_FOUND;
    	}

		tab = cpl_table_load(tabfile, 1, 0);

		// Check length and input

		nrow = (long)cpl_table_get_nrow(tab);

		if(nrow <= 0) {
    		cpl_msg_error(cpl_func, "Output table is empty "
    				"not accessable in run_GALFIT_parallel(). "
    				"Has zero length. Aborting...");
    		cpl_table_delete(tab);
    		return CPL_ERROR_DATA_NOT_FOUND;
		}

		// Check if background values are written into table

		if(cpl_table_has_column(tab, "GALA_BACKGROUND") != 1) {
			cpl_msg_error(cpl_func, "Sky values not available in "
					"table in run_GALFIT_parallel! Aborting...");
			cpl_table_delete(tab);
    		return CPL_ERROR_DATA_NOT_FOUND;
		}

        // Starting message

    	cpl_msg_info(cpl_func, "Starting GALFIT for %ld objects.", nrow);

		// Prepare table for GALFIT output

		cpl_table_new_column(tab, "X_GALFIT", CPL_TYPE_DOUBLE);
		cpl_table_new_column(tab, "XERR_GALFIT", CPL_TYPE_DOUBLE);
		cpl_table_new_column(tab, "Y_GALFIT", CPL_TYPE_DOUBLE);
		cpl_table_new_column(tab, "YERR_GALFIT", CPL_TYPE_DOUBLE);
		cpl_table_new_column(tab, "MAG_GALFIT", CPL_TYPE_DOUBLE);
		cpl_table_new_column(tab, "MAGERR_GALFIT", CPL_TYPE_DOUBLE);
		cpl_table_new_column(tab, "RE_GALFIT", CPL_TYPE_DOUBLE);
   		cpl_table_new_column(tab, "REERR_GALFIT", CPL_TYPE_DOUBLE);
		cpl_table_new_column(tab, "SERSIC_GALFIT", CPL_TYPE_DOUBLE);
		cpl_table_new_column(tab, "SERSICERR_GALFIT", CPL_TYPE_DOUBLE);
		cpl_table_new_column(tab, "AR_GALFIT", CPL_TYPE_DOUBLE);
		cpl_table_new_column(tab, "ARERR_GALFIT", CPL_TYPE_DOUBLE);
		cpl_table_new_column(tab, "ELLIPTICITY_GALFIT", CPL_TYPE_DOUBLE);
		cpl_table_new_column(tab, "ELLIPTICITYERR_GALFIT", CPL_TYPE_DOUBLE);
		cpl_table_new_column(tab, "PA_GALFIT", CPL_TYPE_DOUBLE);
		cpl_table_new_column(tab, "PAERR_GALFIT", CPL_TYPE_DOUBLE);
		cpl_table_new_column(tab, "CHISQ_GALFIT", CPL_TYPE_DOUBLE);
		cpl_table_new_column(tab, "CHI2NU_GALFIT", CPL_TYPE_DOUBLE);

		// Flag every row which has been treated by GALFIT as "fitted"
		// 1: Fit has been started
		// 0: No fit has been started yet

		cpl_table_new_column(tab, "FIT_DONE", CPL_TYPE_INT);

		// Flag every fit accord to GALFIT - see galfit -help for
		// details
		// 0 : Good fit
		// 1 : Maximum number of iterations reached.
		// 2 : Suspected numerical convergence error in current solution.
		// 3 : 1 and 2 together

		cpl_table_new_column(tab, "FLAGS_GALFIT", CPL_TYPE_STRING);

		// Identify secondaries for every object

		find_secondaries_NEW(tab, &offset, &secenlarge, &magexclude);

		// Identify contributing sources

		find_contribtargets_NEW(tab, &contribmax, &distmax, &fluxextend,
				&magzero, &magcrit, &magexclude, &platescale);

		// Save table and a copy of table

		sprintf(copyfile, "%s%s", outdir, "/combcat_copy.fits");

		cpl_table_save(tab, NULL, NULL, tabfile, CPL_IO_CREATE);
    	cpl_table_save(tab, NULL, NULL, copyfile, CPL_IO_CREATE);

    	// Create a fitting list

    	nrow = (long)cpl_table_get_nrow(tab);

    	if(debug == 1) {
    		printf("MASTER : Der Table in run_GALFIT_parallel hat %ld rows!\n", nrow);
    	}

    	// Allocate memory for array with doen indices

    	done = cpl_array_new(nrow, CPL_TYPE_INT);
    	for(i = 0; i < nrow; i++) {
    		cpl_array_set_int(done, i, 0);
    	}

		// Allocate memory for "nrow" objects

		obj = calloc(nrow, sizeof(struct fitlist));

		if(obj == NULL) {
			printf("Error when allocating memory!\n");
		} else {
			if(debug == 1) {
				printf("MASTER : Habe Speicher fuer %ld Objekte in einer Fitlist"
					"allociert!\n", nrow);
			}
		}

		// Fill struct array...
		// Object : Array of structs (type fitlist) for every object
		// Tab : SExtractor output table for current tile
		// Secdir : Directory containing secondary tables
		// Secname : Secondary filename

		create_fittinglist_NEW(obj, tab);

		if(debug == 1) {
			printf("MASTER : Habe die Fittingliste kreiert!\n");
		}

    	// Send message to slaves that table is prepared now with additional
    	// columns and that secondary tables exist now

    	for(k = 1; k < numprocs; k++) {

    		start = 1;

    		MPI_Send(&start, sizeof(int), MPI_INT, k, 41, MPI_COMM_WORLD);

    		if(debug == 1) {
    			printf("MASTER : Habe an slave %d die STARTMESSAGE gesendet!\n", k);
    		}

    	}

		if(debug == 1) {
			printf("JOBSDONE : %d\n", jobsdone);
		}

		/* Measure time */

    	time = MPI_Wtime();

    	sprintf(timefile, "%s%s", outdir, "/timefile_idl");

    	while(jobsdone != 1) {

    		if(sent % 10 == 0) {

    			time2 = MPI_Wtime() - time;

    			printf("MASTER : Habe %d jobs verteilt.\n", sent);
    			printf("ZEIT seit GALFIT start: %f\n", time2);

    			fp_t = fopen(timefile, "a");
    			fprintf(fp_t, "%f, $\n", time2);
    			fclose(fp_t);

    		}

    		// Reset variable for counting number of jobs to do

    		njobs = 0;
    		nloop++;

    		// Receive a message from slave who needs a job

    		if(debug == 1) {
    			printf("MASTER im while - LOOP : Warte auf Nachrichten von "
    				"den Slaves !!!\n");
    		}

    		MPI_Recv(&slaverank, 2*sizeof(long), MPI_LONG, MPI_ANY_SOURCE,
    								42, MPI_COMM_WORLD, &status);

    		/* remove galfit debug files "fit.log" and "galfit.*" */

    		// ACHTUNG!!! Hard gecodet CHECK ob current working directory
    		sprintf(fitlog, "%s%s", curr_dir, "/fit.log");
    		if(access(fitlog, 00) == 0) {
    			remove(fitlog);
    		}
    		if(sent % 100 == 0 && sent > 10) {
    			sprintf(fitfile, "%s%s%s", "rm ", curr_dir, "/galfit.*");
    			if(system(fitfile) != 0) {
    				cpl_msg_error(cpl_func, "System call in galapagos_utils() "
    						"failed!");
    			}
    		}


    		/* update array with done and undone objects */
    		if(slaverank[1] >= 0) {
    			cpl_array_set_int(done, slaverank[1], 1);
    		}

    		if(debug == 1) {
    			printf("MASTER im while - LOOP : Habe folgende Nachricht von "
    				"Slave %ld erhalten : %ld\n", slaverank[0], slaverank[1]);
    		}

			// Actualize fittinglist

			update_fittinglist_NEW(obj, done, &nrow);

    		// Send a message to slave containing the list number of
    		// object in SExtractor table for the slave to work on

			for(j = 0; j < nrow; j++) {

				if(obj[j].dofit == 0) {

					// Remember object number

					ip = j;

					// Send job to the slave

					MPI_Send(&j, sizeof(long), MPI_LONG, slaverank[0], 43,
							MPI_COMM_WORLD);

					sent++;

					// "-2" means : Objects is sent but fit is not
					// complete yet

					obj[ip].dofit = -1;

					break;
				}
			}

			// Terminating condition for the loop : no more jobs to do

			for(j = 0; j < nrow; j++) {

				if(obj[j].dofit == -1) {

					njobs++;
				}
			}

			printf("MASTER : Jobs done : %ld\n", njobs);

			// Terminating condition : No more jobs to do -> jobsdone = 1

			if(njobs == nrow - 1) {

				jobsdone = 1;
			}

			if(debug == 1) {
				printf("MASTER : Bin in Loop Nummer %ld und "
					"habe noch %ld Jobs zu tun!\n", nloop, njobs);
			}
    	}

    	// Terminating condition for slaves to tell that there are no more jobs

    	// Find out number of processes to send every slave a terminating
    	// message

    	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    	for(k = 1; k < numprocs; k++) {

    		j = -1;

    		MPI_Send(&j, sizeof(long), MPI_LONG, k, 43, MPI_COMM_WORLD);
    	}

		/* remove galfit debug files "fit.log" and "galfit.*" */
		sprintf(fitfile, "%s%s%s", "rm ", curr_dir, "/galfit.*");

		if(system(fitfile) != 0) {
			cpl_msg_error(cpl_func, "System call in galapagos_utils() "
				"failed!");
		}

    	// Clean up

    	cpl_array_delete(done);
    	cpl_table_delete(tab);

    	time = MPI_Wtime() - time;

    	printf("\n\n\n-------------------------------------\n");
    	printf("Effective time for GALFIT procedure by MASTER is "
    			"%lf seconds.\n", time);
    	printf("\n-------------------------------------\n\n\n");


    // Slave

    } else {

    	// Receive a starting message from master when output table is ready

		MPI_Recv(&start, sizeof(int), MPI_INT, 0, 41, MPI_COMM_WORLD, &status);

		// SOLLTE HIER NOCH EIN if(start == 99) UM ALLES HERUM ??

		// Find out process rank

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		if(debug == 1) {
			printf("SLAVE %d: Habe eine Startmessage erhalten!\n", rank);
		}

    	while ((j != -1) && (start == 1)) {

    		// Find out process rank

    		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    		/* Measure time */
        	stime1 = MPI_Wtime();

			// Send a message to MASTER that slaves needs a job (JOB TAG = 1)

    		smsg[0] = rank;
    		smsg[1] = j;

			MPI_Send(&smsg, 2*sizeof(long), MPI_LONG, 0, 42, MPI_COMM_WORLD);

			if(debug == 1) {
				printf("SLAVE %d: Habe meinen rank zurueckgesendet!\n", rank);
				printf("SLAVE %d: Warte jetzt auf eine Nachricht vom MASTER!\n", rank);
			}

			// Receive job ID for MASTER (JOB TAG = 3)

			MPI_Comm_rank(MPI_COMM_WORLD, &rank);

			MPI_Recv(&j, sizeof(long), MPI_LONG, 0, 43, MPI_COMM_WORLD, &status);

			stime2 = MPI_Wtime();

			waittimeh = (stime2 - stime1);

			waittime += waittimeh;

			MPI_Comm_rank(MPI_COMM_WORLD, &rank);

			if(debug == 1) {
				printf("Slave %d hat einen Jobauftrag empfangen : Job Nummer %ld\n", rank, j);
			}

			MPI_Comm_rank(MPI_COMM_WORLD, &rank);


			if(j != -1) {

				// Load table

				sprintf(tabfile, "%s%s", outdir, "/combcat_copy.fits");

				if(access(tabfile, 00) == 0) {

					tab = cpl_table_load(tabfile, 1, 0);

					nrow = (long)cpl_table_get_nrow(tab);

					if(nrow <= 0) {
						cpl_msg_error(cpl_func, "Table loaded by slave in "
								"run_GALFIT_parallel() is not found or empty!");
					}

				} else {
					cpl_msg_error(cpl_func, "Tile catalog not available for run_GALFIT()."
							"File containing table %s was not found.", tabfile);
					return CPL_ERROR_DATA_NOT_FOUND;
				}


				// Identify GALFIT output path

				sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", j));
				sprintf(imgblock, "%s%s%s%ld%s", directory, "/", object, j + 1, ".fits");

				if (access(imgblock, 00) != 0) {

    				// Creating a bad pixel mask for GALFIT

    				// Prepare file paths

		    		/* Measure time */
		        	stime5 = MPI_Wtime();

    				if (strcmp(badpix, "n") != 0 && strcmp(badpix, "no") != 0 &&
    						strcmp(badpix, "none") != 0) {

//    					sprintf(segimage, "%s%s%s", directory, "/", out_seg);
    					sprintf(segimage, "%s%s", directory, out_seg);
    					sprintf(weightimage, "%s", cpl_table_get_string(tab, "WEIGHTIMAGE", j));


    					/* load weight image and check error */
    					cpl_errorstate_set(errornone);

    					weight = cpl_image_load_window(weightimage, CPL_TYPE_DOUBLE, 0, 0,
    								cpl_table_get_int(tab, "STAMP_XLO", j, NULL),
    								cpl_table_get_int(tab, "STAMP_YLO", j, NULL),
    								cpl_table_get_int(tab, "STAMP_XHI", j, NULL),
    								cpl_table_get_int(tab, "STAMP_YHI", j, NULL));

    					xsize = cpl_image_get_size_x(weight);

    					if(xsize <= 0) {
    						cpl_image_delete(weight);
    						cpl_errorstate_set(errornone);

        					weight = cpl_image_load_window(weightimage,
        								CPL_TYPE_DOUBLE, 0, 0,
        								cpl_table_get_int(tab, "STAMP_XLO", j, NULL),
        								cpl_table_get_int(tab, "STAMP_YLO", j, NULL),
        								cpl_table_get_int(tab, "STAMP_XHI", j, NULL),
        								cpl_table_get_int(tab, "STAMP_YHI", j, NULL));
    					}

    					error = cpl_errorstate_get();
    					if(error != CPL_ERROR_NONE) {
    						cpl_msg_error(cpl_func, "Unspecified error when loading "
    								"weightimage %s.", weightimage);
    					}

    					/* load segmentation image and check error */
    					cpl_errorstate_set(errornone);

    					seg = cpl_image_load_window(segimage, CPL_TYPE_INT, 0, 0,
									cpl_table_get_int(tab, "STAMP_XLO", j, NULL),
									cpl_table_get_int(tab, "STAMP_YLO", j, NULL),
									cpl_table_get_int(tab, "STAMP_XHI", j, NULL),
									cpl_table_get_int(tab, "STAMP_YHI", j, NULL));

    					error = cpl_errorstate_get();
    					if(error != CPL_ERROR_NONE) {
    						cpl_msg_error(cpl_func, "Unspecified error when loading "
    								"segmentation image %s.", segimage);
    					}

    					/* check if mask is existing - only if not create */
    					sprintf(maskfilecontrol, "%s%s%s%s%ld%s", directory, "/",
    							badpix, "_", j + 1, ".fits");

    					if(access(maskfilecontrol, 00) != 0) {

    						// XXX output is not perfectly identical yet

    						if(create_mask_NEW(badpix, &secenlarge,
    								&offset, tab, weight, seg, &j)
    								!= CPL_ERROR_NONE) {
    							cpl_msg_error(cpl_func, "create_mask() failed!");
							}
    					}

    					cpl_image_delete(weight);
    					cpl_image_delete(seg);
    				}

		    		/* Measure time */
		        	stime6 = MPI_Wtime();

					masktimeh = (stime6 - stime5);

					masktime += masktimeh;

    				// Build up GALFIT constraint file

		    		/* Measure time */
		        	stime7 = MPI_Wtime();

    				if (strcmp(constraints, "n") != 0 &&
    						strcmp(constraints, "no") != 0 &&
    						strcmp(constraints, "none") != 0) {

    					// Check if constraintfile is existing - only if not create

    					sprintf(constraintfile, "%s%s%s%s%ld", directory, "/",
    							constraints, "_", j + 1);

    					if(access(constraintfile, 00) != 0) {
    						if (create_constraintfile_NEW(constraintfile, &re_max, &mag_min,
    								&mag_max, tab, &j) != CPL_ERROR_NONE) {
    							cpl_msg_error(cpl_func, "create_constraintfile() failed!");
    						}
    					}
    				}

		    		/* Measure time */
		        	stime8 = MPI_Wtime();
					constrainttimeh = (stime8 - stime7);
					constrainttime += constrainttimeh;

		    		/* Measure time */
		        	stime9 = MPI_Wtime();

    				// Check if setup file is existing - only if not create

    				sprintf(galsetfile, "%s%s%s%s%ld", directory, "/", galfitset,
    							"_", j + 1);

//    				if(access(galsetfile, 00) != 0) {
    					if(create_GALFIT_setup_NEW(gala_setup, &j) !=
    							CPL_ERROR_NONE) {
    						cpl_msg_error(cpl_func, "create_GALFIT_setup() failed!");
    					}
//    				}

    		    	/* Measure time */
    		        stime10 = MPI_Wtime();
					setuptimeh = (stime10 - stime9);
					setuptime += setuptimeh;

    				// Start GALFIT

    				// Check if galfit imgblock is existing - only if not create

    				sprintf(galfitfile, "%s%s%s%ld%s", directory, "/", object,
    							j + 1, ".fits");

    				if(debug == 1) {
    					printf("GALFIT Setup %s created for OBJECT %ld !\n", galfitfile, j);
    				}

					stime3 = MPI_Wtime();

					galatimeh = (stime3 - stime2);

					galatime += galatimeh;

    				if(access(galfitfile, 00) != 0) {

    					sprintf(str, "%s %s %s", path, galsetfile, "> /dev/null");

    					if(debug == 1) {
    						cpl_msg_info(cpl_func, "Slave %d is running GALFIT with %s.", rank, str);
    					}

						if(system(str) != 0) {
							cpl_msg_error(cpl_func, "System call in galapagos_utils() "
	    						"failed! Is the GALFIT module linked correctly?");
						}

						nobj++;
    				}

    				stime4 = MPI_Wtime();

    				galfittimeh = (stime4 - stime3);

    				if(access(imgblock, 00) == 0) {
    					header = cpl_propertylist_load(imgblock, 2);
    						// read fits header

    					fitdata = read_header(header);

    					printf("--------------------------------------------\n");
    					printf("PROCESSOR %d fitted object %d successfully in "
    							"%f seconds.\n"
    							"XC: %f\n"
    							"YC: %f\n"
    							"MAG: %f\n"
    							"RE: %f\n"
    							"N: %f\n"
    							"AR: %f\n"
    							"PA: %f\n", rank, (int)j+1, galfittimeh,
    							cpl_array_get_double(fitdata, 0, NULL),
    							cpl_array_get_double(fitdata, 1, NULL),
    							cpl_array_get_double(fitdata, 2, NULL),
    							cpl_array_get_double(fitdata, 3, NULL),
    							cpl_array_get_double(fitdata, 4, NULL),
    							cpl_array_get_double(fitdata, 5, NULL),
    							cpl_array_get_double(fitdata, 6, NULL));
    					printf("--------------------------------------------\n");

    					cpl_array_delete(fitdata);
    					cpl_propertylist_delete(header);
    				}

					galfittime += galfittimeh;

				}

				// Clean up

				cpl_table_delete(tab);
			}

			// xxx Write timefile for output

			MPI_Comm_rank(MPI_COMM_WORLD, &rank);

			sprintf(tfile, "%s%s%d", outdir, "/tfile_slave", rank);

			frac = (double)(j+1)/nrow;

			if(rank == 1 || rank == 2 || rank == 3) {
				printf("\n------------ -----------------------------\n"
					"SLAVE %d : %d Objekte verarbeitet.\n"
					"SLAVE %d : %f of all objects are done.\n"
					"WAITTIME : %f\n"
					"GALATIME :%f\n"
					"FITTIME : %f\n"
					"MASKTIME : %f\n"
					"CONSTRAINTTIME : %f\n"
					"SETUPTIME : %f\n"
					"--------------------------------------\n\n",
					rank, nobj, rank, frac, waittime, galatime, galfittime,
					masktime, constrainttime, setuptime);
			}

			if(frac > 0.1 && tfdone == 0) {

				fp = fopen(tfile, "w");

				fprintf(fp, "TIME DISTRIBUTION AFTER %ld OBJECTS "
						"BY SLAVE %d:\n", j, rank);
				fprintf(fp, "WAITTIME : %f\n", waittime);
				fprintf(fp, "GALAPAGOS TIME : %f\n", galatime);
				fprintf(fp, "DAVON MASK TIME : %f\n", masktime);
				fprintf(fp, "DAVON CONSTRAINT TIME : %f\n", constrainttime);
				fprintf(fp, "DAVON SETUP TIME : %f\n", setuptime);
				fprintf(fp, "GALFIT TIME : %f\n", galfittime);
				fprintf(fp, "SLAVE %d : %d Objekte verarbeitet.\n\n\n",
						rank, nobj);

				fclose(fp);

				tfdone = 1;
			}


			if(frac > 0.3 && tfdone == 1) {

				fp = fopen(tfile, "a");

				fprintf(fp, "TIME DISTRIBUTION AFTER %ld OBJECTS "
						"BY SLAVE %d:\n", j, rank);
				fprintf(fp, "WAITTIME : %f\n", waittime);
				fprintf(fp, "GALAPAGOS TIME : %f\n", galatime);
				fprintf(fp, "DAVON MASK TIME : %f\n", masktime);
				fprintf(fp, "DAVON CONSTRAINT TIME : %f\n", constrainttime);
				fprintf(fp, "DAVON SETUP TIME : %f\n", setuptime);
				fprintf(fp, "GALFIT TIME : %f\n", galfittime);
				fprintf(fp, "SLAVE %d : %d Objekte verarbeitet.\n\n\n",
						rank, nobj);

				fclose(fp);

				tfdone = 2;
			}

			if(frac > 0.6 && tfdone == 2) {

				fp = fopen(tfile, "a");

				fprintf(fp, "TIME DISTRIBUTION AFTER %ld OBJECTS "
						"BY SLAVE %d:\n", j, rank);
				fprintf(fp, "WAITTIME : %f\n", waittime);
				fprintf(fp, "GALAPAGOS TIME : %f\n", galatime);
				fprintf(fp, "DAVON MASK TIME : %f\n", masktime);
				fprintf(fp, "DAVON CONSTRAINT TIME : %f\n", constrainttime);
				fprintf(fp, "DAVON SETUP TIME : %f\n", setuptime);
				fprintf(fp, "GALFIT TIME : %f\n", galfittime);
				fprintf(fp, "SLAVE %d : %d Objekte verarbeitet.\n\n\n",
						rank, nobj);

				fclose(fp);

				tfdone = 3;
			}

			if(frac > 0.8 && tfdone == 3) {

				fp = fopen(tfile, "a");

				fprintf(fp, "TIME DISTRIBUTION AFTER %ld OBJECTS "
						"BY SLAVE %d:\n", j, rank);
				fprintf(fp, "WAITTIME : %f\n", waittime);
				fprintf(fp, "GALAPAGOS TIME : %f\n", galatime);
				fprintf(fp, "DAVON MASK TIME : %f\n", masktime);
				fprintf(fp, "DAVON CONSTRAINT TIME : %f\n", constrainttime);
				fprintf(fp, "DAVON SETUP TIME : %f\n", setuptime);
				fprintf(fp, "GALFIT TIME : %f\n", galfittime);
				fprintf(fp, "SLAVE %d : %d Objekte verarbeitet.\n\n\n",
						rank, nobj);

				fclose(fp);

				tfdone = 4;
			}

			if(frac > 0.9 && tfdone == 4) {

				fp = fopen(tfile, "a");

				fprintf(fp, "TIME DISTRIBUTION AFTER %ld OBJECTS "
						"BY SLAVE %d:\n", j, rank);
				fprintf(fp, "WAITTIME : %f\n", waittime);
				fprintf(fp, "GALAPAGOS TIME : %f\n", galatime);
				fprintf(fp, "DAVON MASK TIME : %f\n", masktime);
				fprintf(fp, "DAVON CONSTRAINT TIME : %f\n", constrainttime);
				fprintf(fp, "DAVON SETUP TIME : %f\n", setuptime);
				fprintf(fp, "GALFIT TIME : %f\n", galfittime);
				fprintf(fp, "SLAVE %d : %d Objekte verarbeitet.\n\n\n",
						rank, nobj);

				fclose(fp);

				tfdone = 5;
			}
    	}
    }

	/* Go on when all slaves have finished their jobs */

    if(rank == 0) {
    	printf("MASTER: Warte auf Nachrichten von den Slaves dass "
			"alle ihre Jobs beendet haben!\n");
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

	/* Go on when all slaves have finished their jobs */

    if(rank == 0) {

    	printf("MASTER: Alle slaves sind da. Jobs beendet!\n");

    	/* remove remaining GALFIT debug files */
		if(access(fitlog, 00) == 0) {
			remove(fitlog);
		}

		if(system(fitfile) != 0) {
			cpl_msg_error(cpl_func, "System call in galapagos_utils() "
					"failed!");
		}

		/* prepare combined catalog filename */
    	sprintf(tabfile, "%s%s%s", outdir, "/", combtab);

    	/* Add results and remove helpfiles */
    	tab = cpl_table_load(tabfile, 1, 0);

    	/* Add results from previous fit to table */
    	update_table_NEW(tab, object);
    	cpl_table_save(tab, NULL, NULL, tabfile, CPL_IO_CREATE);

    	/* Save a copy of table */
    	sprintf(copyfile, "%s%s", outdir, "/combcat_copy.fits");
    	cpl_table_save(tab, NULL, NULL, copyfile, CPL_IO_CREATE);

    	/* clean up*/
    	cpl_table_delete(tab);
    }

	return CPL_ERROR_NONE;
}



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
//			CPL_ERROR_NONE             No error occurred
//****************************************************************************

cpl_error_code find_secondaries_NEW(cpl_table *tab, const double *offset,
		const double *secenlarge, const double *magexclude) {

	int k,
		secmax = 10;

	long i,
		 j,
		 count = 0,
		 z = 0;

	double xc,
	       yc,
	       theta,
	       R,
	       kho,
	       gho,
	       objmag,
	       xcs,
	       ycs,
	       dist,
	       aims,
	       bims,
	       Rloop,
	       ghi,
	       khi,
	       thetas,
	       loopmag,
	       magdiff,
	       pi = 3.14159265;

	char tile[FILENAME_MAX],
		 tile_s[FILENAME_MAX];

	cpl_boolean overlap = CPL_FALSE;

	cpl_array *secindices;


	// Starting message

	cpl_msg_info(cpl_func, "Identifying secondaries now.");

	// Check input table

	z = (long)cpl_table_get_nrow(tab);

	if(z == 0) {
		cpl_msg_error (cpl_func, "Input table in find_secondaries() is empty!");
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	// Write secondary tables indices in an array

	cpl_table_new_column_array(tab, "SECONDARY_INDICES",
			CPL_TYPE_INT, secmax);

	// Loop over table - find secondaries for every object

	for(i = 0; i < z; i++) {

		// Prepare an array containing secondary table indices

		secindices = cpl_array_new(10, CPL_TYPE_INT);

		// Initialize with -1

		for(k = 0; k < secmax; k++) {
			cpl_array_set(secindices, k, -1);
		}

		// Reset counting variable for secondaries

		count = 0;

		// Get object positions and tiles

		xc    = cpl_table_get_double(tab, "X_IMAGE",     i, NULL);
		yc    = cpl_table_get_double(tab, "Y_IMAGE",     i, NULL);
		theta = cpl_table_get_double(tab, "THETA_IMAGE", i, NULL);
		theta = (theta / 360) * 2 * pi;
		sprintf(tile, "%s", cpl_table_get_string(tab, "TILE", i));

		// Enlarge ellipses for identifying secondaries

		R     = cpl_table_get_double(tab, "KRON_RADIUS", i, NULL);
		gho   = cpl_table_get_double(tab, "A_IMAGE", i, NULL)* R *
				*secenlarge + *offset;
		kho   = cpl_table_get_double(tab, "B_IMAGE", i, NULL)* R *
				*secenlarge + *offset;

		// Magnitude criterion

		objmag = cpl_table_get_double(tab, "MAG_BEST", i, NULL);

		// Check other objects

		for(j = 0; j < z; j++) {

			if(j != i) {

				// Check if objects are on the same tile

				sprintf(tile_s, "%s", cpl_table_get_string(tab, "TILE", j));

				if(strcmp(tile, tile_s) == 0) {

					// Check neighboring sources

					xcs   = cpl_table_get_double(tab, "X_IMAGE", j, NULL);
					ycs   = cpl_table_get_double(tab, "Y_IMAGE", j, NULL);
					aims  = cpl_table_get_double(tab, "A_IMAGE", j, NULL);
					bims  = cpl_table_get_double(tab, "B_IMAGE", j, NULL);
					Rloop = cpl_table_get_double(tab, "KRON_RADIUS", j, NULL);

					// Calculate half-major and half-minor axis

					ghi = aims * Rloop;
					khi = bims * Rloop;

					thetas = cpl_table_get_double(tab, "THETA_IMAGE", j, NULL);
					thetas = 2 * pi * thetas / 360;

					loopmag = cpl_table_get_double(tab, "MAG_BEST", j, NULL);
					magdiff = loopmag - objmag;

					// Check for overlapping ellipses

					dist = sqrt(pow((xcs - xc), 2) + pow((ycs - yc), 2));

					if(dist <= ghi + gho) {

						overlap = ellipse_overlap(&xc, &yc, &gho, &kho, &theta,
							&xcs, &ycs, &ghi, &khi, &thetas);

						// Write secondary table index (!!!) in array

						if(overlap == CPL_TRUE && magdiff < *magexclude) {

							cpl_array_set(secindices, count, j + 1);

							if(count < 10) {
								count++;
							} else {
								cpl_msg_error(cpl_func, "Too many secondaries "
										"in find_secondaries() for object index "
										"%ld !!! Some secondaries are not "
										"included.", i);
							}
						}
					}
				}
			}
		}

		// Insert array into table

		cpl_table_set_array(tab, "SECONDARY_INDICES", i, secindices);

		// Clean up

		cpl_array_delete(secindices);
	}

	return CPL_ERROR_NONE;
}


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
		const double *a2, const double *b2, const double *phi2) {

	double relphi1, ellrad1, relphi2, ellrad2, dist;
	cpl_boolean overlap;

	dist = sqrt(pow(*x1 - *x2, 2) + pow(*y1 - *y2, 2));

	relphi1 = rel_pos_ang(&*x2, &*y2, &*x1, &*y1, &*phi1);
	ellrad1 = ell_rad(&*a1, &*b1, &relphi1);

	relphi2 = rel_pos_ang(&*x1, &*y1, &*x2, &*y2, &*phi2);
	ellrad2 = ell_rad(&*a2, &*b2, &relphi2);

	if(ellrad1 + ellrad2 >= dist) {
		overlap = CPL_TRUE;
	} else {
		overlap = CPL_FALSE;
	}
	return overlap;
}

double ell_rad(const double *a, const double *b, const double *phi) {

	double r;

	r = 1./sqrt(pow(cos(*phi), 2.)/ pow(*a, 2) +
			pow(sin(*phi), 2.)/ pow(*b, 2));

	return r;
}


//****************************************************************************
// Check if point is inside of an ellipse or not
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
		const double *xc, const double *yc, const double *a,
		const double *b, const double *theta) {

	double xpoint, ypoint, val;

	//  Coordinate transformation:

	xpoint = (*xp - *xc) * cos(*theta) + (*yp - *yc) * sin(*theta);
	ypoint = (*xp - *xc) * (-1)*sin(*theta) + (*yp - *yc) * cos(*theta);

	// Calculate if point is inside

	val = ((xpoint * xpoint) / (*a * *a)) + ((ypoint * ypoint) / (*b * *b));

	if(val <= 1) {
		return CPL_TRUE;
	} else {
		return CPL_FALSE;
	}
}


// XXX Check if working correctly - should do, but...
// XXX Contrib targets werden momentan maskiert!!! SOLL NICHT SEIN!

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
		                       cpl_image *seg, const long *i) {

	int b, xlo, xhi, ylo, yhi, number, secnumber, val, segval,
		status, qq = 99, secmax, ctnumber, ctmax, debug = 0;
	long a, row;
	double x, y, xc, yc, R, aim, bim, theta, gh, kh, cxx, cxy, cyy,
		weightval;
	double pi = 3.14159265;
	char maskfilei[FILENAME_MAX];
	char directory[FILENAME_MAX];
	char tile[FILENAME_MAX];
	char tile2[FILENAME_MAX];
	cpl_table *helptab;
	cpl_image *mask;
	cpl_propertylist *list;
	cpl_boolean sortval = CPL_TRUE;
	const cpl_array *help;
	cpl_array *secindices,
			  *ctindices;


	if(debug == 1) {
		cpl_msg_info(cpl_func, "Creating mask now for table element number %ld "
				"from STAGES tile %s", *i, cpl_table_get_string(tab, "TILE",
						*i));
	}

	// Get mask size parameters

	xlo = cpl_table_get(tab, "STAMP_XLO", *i, NULL);
	xhi = cpl_table_get(tab, "STAMP_XHI", *i, NULL);
	ylo = cpl_table_get(tab, "STAMP_YLO", *i, NULL);
	yhi = cpl_table_get(tab, "STAMP_YHI", *i, NULL);

	//	1st step: Helping table with primary, secondary and tertiaries flagged

	helptab = cpl_table_duplicate(tab);

	cpl_table_new_column(helptab, "STATUS", CPL_TYPE_INT);
	row = (long)cpl_table_get_nrow(helptab);

	if(row == 0) {
		cpl_msg_error(cpl_func, "Zerolength input table for create_mask()!");
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	// Give a STATUS to every object
	// 1 means primary
	// 2 means secondary - NOT masked out
	// 3 means tertiary - masked out

	for(a = 0; a < row; a++) {
		cpl_table_set(helptab, "STATUS", a, 3);
	}

	// Flag primary

	cpl_table_set(helptab, "STATUS", *i, 1);

	// Flag secondaries

	help = cpl_table_get_array(tab, "SECONDARY_INDICES", *i);

	secindices = cpl_array_duplicate(help);

	secmax = cpl_array_get_size(secindices);

	for(a = 0; a < secmax; a++) {
		secnumber = cpl_array_get(secindices, a, NULL);
		for(b = 0; b < row; b++) {
			if(b + 1 == secnumber) {
				cpl_table_set(helptab, "STATUS", b, 2);
			}
		}
	}

	// Flag contrib targets

	help = cpl_table_get_array(tab, "POT_CT_INDICES", *i);

	ctindices = cpl_array_duplicate(help);

	ctmax = cpl_array_get_size(ctindices);

	for(a = 0; a < ctmax; a++) {
		ctnumber = cpl_array_get(ctindices, a, NULL);
		for(b = 0; b < row; b++) {
			if(b + 1 == ctnumber) {
				cpl_table_set(helptab, "STATUS", b, 2);
			}
		}
	}

	// Delete every object which is not on the same tile from helptab

	cpl_table_unselect_all(helptab);

	sprintf(tile, "%s", cpl_table_get_string(tab, "TILE", *i));

	for(a = 0; a < row; a++) {
		sprintf(tile2, "%s", cpl_table_get_string(tab, "TILE", a));
		if(strcmp(tile, tile2) != 0) {
			cpl_table_select_row(helptab, a);
		}
	}

	cpl_table_erase_selected(helptab);

	cpl_table_unselect_all(helptab);

	if(debug == 1) {
		printf("Der Helptab hat nach löschen aller Objekt die nicht auf dem "
				"Tile sind noch %d rows.\n", (int)cpl_table_get_nrow(helptab));
	}

	// Sort helping tab descending from tertiaries to primaries

	list = cpl_propertylist_new();
	cpl_propertylist_append_bool(list, "STATUS", sortval);
	cpl_table_sort(helptab, list);
	cpl_propertylist_delete(list);

	// Delete every object having no overlap with current stamp from helptab
	// for speed up

	cpl_table_unselect_all(helptab);

    for(a = 0; a < row; a++) {

    	status = cpl_table_get_int(helptab, "STATUS", a, NULL);

    	if(status == 3) {

        	xc     = cpl_table_get_double(helptab, "X_IMAGE",     a, NULL);
        	yc     = cpl_table_get_double(helptab, "Y_IMAGE",     a, NULL);
        	R      = cpl_table_get_double(helptab, "KRON_RADIUS", a, NULL);
        	aim    = cpl_table_get_double(helptab, "A_IMAGE",     a, NULL);
        	bim    = cpl_table_get_double(helptab, "B_IMAGE",     a, NULL);

    		gh = aim * R * *secenlarge + *offset;
    		kh = bim * ((R * *secenlarge) + (*offset / aim));

    		if(xc + gh < xlo) {
    			cpl_table_select_row(helptab, a);
    		}

    		if(xc - gh > xhi) {
    			cpl_table_select_row(helptab, a);
    		}

    		if(yc + gh < ylo) {
    			cpl_table_select_row(helptab, a);
    		}

    		if(yc - gh > yhi) {
    			cpl_table_select_row(helptab, a);
    		}
    	}
    }

    cpl_table_erase_selected(helptab);

	row = (int)cpl_table_get_nrow(helptab);

	if(debug == 1) {
		printf("Im Helptab sind nach Löschen aller unbedeutenden Quellen "
			"noch %ld Objekte!", row);
	}

	// Create new mask image for every postage stamp

	mask = cpl_image_new(xhi - xlo + 1, yhi - ylo + 1, CPL_TYPE_INT);

	// Identify objects and treat them according to their flag (status)

    for(a = 0; a < row; a++) {

    	number = cpl_table_get_int(helptab,    "NUMBER",      a, NULL);

    	if(debug == 1) {
    		printf("NUMBER CURRENT OBJECT : %d\n", number);
    	}

    	xc     = cpl_table_get_double(helptab, "X_IMAGE",     a, NULL);
    	yc     = cpl_table_get_double(helptab, "Y_IMAGE",     a, NULL);
    	R      = cpl_table_get_double(helptab, "KRON_RADIUS", a, NULL);
    	aim    = cpl_table_get_double(helptab, "A_IMAGE",     a, NULL);
    	bim    = cpl_table_get_double(helptab, "B_IMAGE",     a, NULL);
    	theta  = cpl_table_get_double(helptab, "THETA_IMAGE", a, NULL);
    	theta  = 2 * pi * theta / 360;
    	status = cpl_table_get_int(helptab, "STATUS", a, NULL);

    	if(debug == 1) {
    		printf("STATUS CURRENT OBJECT : %d\n", status);
    	}

		gh = aim * R * *secenlarge + *offset;
		kh = bim * ((R * *secenlarge) + (*offset / aim));

    	cxx = (pow(cos(theta), 2)) / pow(gh, 2) +
    			(pow(sin(theta), 2)) / pow(kh, 2);
    	cyy = (pow(sin(theta), 2)) / pow(gh, 2) +
    			(pow(cos(theta), 2)) / pow(kh, 2);
    	cxy = 2 * cos(theta) * sin(theta) *
    			(1 / pow(gh, 2) - 1 / pow(kh, 2));

    	// Loop over mask image

    	for(x = xlo; x <= xhi; x++) {
    		for(y = ylo; y <= yhi; y++) {
    			if(cxx * ((x - xc) * (x - xc)) + cyy * ((y - yc) *
    				(y - yc)) + cxy * (x - xc) * (y - yc) < 1) {

    				// Identify object on mask, status == 3 -> tertiary
    				// -> exclude from fit

    				if(status == 3) {
    					cpl_image_set(mask, x - xlo + 1, y - ylo + 1, 1);
    				}

    				// Identify object on mask, status == 2 -> secondary
    				// -> include into fit

    				if(status == 2) {
    					val = cpl_image_get(mask, x - xlo + 1, y - ylo + 1,
    							&qq);

    					// If overlapping tertiary is present use
    					// segmentation image value at tertiary

    					if(val == 1) {
    						segval = cpl_image_get(seg, x - xlo + 1, y - ylo + 1, &qq);

    						// Exclude tertiary segmentation pixels
    						// if nonzero and not from secondary object

    						if(segval != number && segval > 0) {
    							cpl_image_set(mask, x - xlo, y - ylo, 1);
    						} else {
    							cpl_image_set(mask, x - xlo + 1, y - ylo + 1,
    									0);
    						}
    					}
    				}

    				// Treat primary and insert segmentation image for
    				// faint objects (< magexclude)

    				if(status == 1) {
    					val = cpl_image_get(mask, x - xlo + 1, y - ylo + 1,
    							&qq);

    					// Magnitude excluded object was flagged as tertiary
    					// before

    					if(val == 1) {
    						segval = cpl_image_get(seg, x - xlo + 1,
    								y - ylo + 1, &qq);
    						if(segval != number && segval > 0) {
    							cpl_image_set(mask, x - xlo + 1, y - ylo + 1,
    									1);
    						} else {
    							cpl_image_set(mask, x - xlo + 1, y - ylo + 1,
    									0);
    						}
    					}
    				}
    			}

				// Exclude pixel with exposure time 0

				weightval = cpl_image_get(weight, x - xlo + 1, y - ylo + 1, &qq);
				if(weightval == 0) {
					cpl_image_set(mask, x - xlo + 1, y - ylo + 1, 10);
				}
    		}
    	}
    }

    sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", *i));

	sprintf(maskfilei, "%s%s%s%s%ld%s", directory, "/", badpix, "_", *i + 1,
			".fits");

	cpl_image_save(mask, maskfilei, CPL_BPP_32_SIGNED, NULL, CPL_IO_CREATE);

	cpl_image_delete(mask);
	cpl_table_delete(helptab);
	cpl_array_delete(secindices);
	cpl_array_delete(ctindices);

	return CPL_ERROR_NONE;
}


cpl_error_code create_GALFIT_setup_NEW(cpl_parameterlist *gala_setup,
								   const long *i) {

	int num, j, xsize, ysize, lv, secnum = 0, xlo, ylo, count, ctnum = 0,
			xlo_sec, ylo_sec, debug = 0;
	long k, nrow;
	double psffactor, background, convbox, magzero, platescale, xsec, ysec,
		   eli, mag, fr, aim, bim, theta, xc, yc, fluxextend, xfit, yfit,
		   magexclude, magcrit, xcgalfit = 0, ycgalfit = 0, maggalfit = 0,
		   regalfit = 0, ngalfit = 0, argalfit = 0, pagalfit = 0, exptime;
	char out_tab[FILENAME_MAX];
	char object[FILENAME_MAX];
	char galfitset[FILENAME_MAX];
	char psf[FILENAME_MAX];
	char badpix[FILENAME_MAX];
	char constraints[FILENAME_MAX];
	char display[FILENAME_MAX];
	char directory[FILENAME_MAX];
	char stampfile[FILENAME_MAX];
	char stampname[FILENAME_MAX];
	char tabfile[FILENAME_MAX];
	char stamp[FILENAME_MAX];
	char galsetfile[FILENAME_MAX];
	char galfitim[FILENAME_MAX];
	char maskfile[FILENAME_MAX];
	char outsky[FILENAME_MAX];
	char constraintfile[FILENAME_MAX];
	char fitfile[FILENAME_MAX];
	char imagefile[FILENAME_MAX];
	char xp[FILENAME_MAX];
	char yp[FILENAME_MAX];
	char mg[FILENAME_MAX];
	char re[FILENAME_MAX];
	char n[FILENAME_MAX];
	char ar[FILENAME_MAX];
	char pa[FILENAME_MAX];
	char str[FILENAME_MAX];
	char outdir[FILENAME_MAX];
	char *ptr;
	cpl_parameter *p;
	cpl_propertylist *header, *fitsheader;
	cpl_table *tab;
	FILE *fp_gs;
	cpl_boolean skyfix = CPL_TRUE;
	cpl_array *secindices, *ctindices;
	const cpl_array *help;

	// Starting message

	if(debug == 1) {
		cpl_msg_info(cpl_func, "Creating GALFIT setup for "
			"object index %ld.", *i);
	}

	// Check previous errorstate

    p = cpl_parameterlist_find(gala_setup, "out_tab");
    sprintf(out_tab, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "directory");
    sprintf(directory, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "stampfile");
    sprintf(stampfile, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "stampname");
    sprintf(stampname, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "object");
    sprintf(object, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "galfitset");
    sprintf(galfitset, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "psf");
    sprintf(psf, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "psffactor");
    psffactor = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "badpix");
    sprintf(badpix, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "outsky");
    sprintf(outsky, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "constraints");
    sprintf(constraints, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "convbox");
    convbox = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magzero");
    magzero = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magexclude");
    magexclude = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magcrit");
    magcrit = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "platescale");
    platescale = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "display");
    sprintf(display, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "fluxextend");
    fluxextend = cpl_parameter_get_double(p);

	p = cpl_parameterlist_find(gala_setup, "outdir");
	sprintf(outdir, "%s", cpl_parameter_get_string(p));


	// Prepare file paths

	sprintf(tabfile, "%s%s", outdir, "/combcat_copy.fits");

	if(access(tabfile, 00) != 0) {
		cpl_msg_error(cpl_func, "In create_GALFIT_SETUP() : "
				"Table was not accessable! Aborting...");
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	// Load table

	tab = cpl_table_load(tabfile, 1, 0);

	nrow = (long) cpl_table_get_nrow(tab);

	if(nrow <= 0) {
		cpl_msg_error(cpl_func, "In create_GALFIT_setup() : "
				"Input table is empty or not readable. Aborting...");
		cpl_table_delete(tab);
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	// Get SExtractor number of current object

	num = cpl_table_get(tab, "NUMBER", *i, NULL);

	// image header and exposure time

	sprintf(imagefile, "%s%s%s%s%s%s%d%s%s%s",
			cpl_table_get_string(tab, "TILE_DIRECTORY", *i),
			"/", stampfile, "/", stampname, "_", num, "_",
			cpl_table_get_string(tab, "TILE", *i), ".fits");

	if(debug == 1) {
		printf("IMAGEFILE in create_GALFIT_setup() : %s\n", imagefile);
	}

	header = cpl_propertylist_load(imagefile, 0); // read fits header
	if (header == NULL) {
	    // image header not found
		cpl_propertylist_delete(header);
		cpl_table_delete(tab);
		cpl_msg_error(cpl_func, "Stamp file not found in "
				"create_GALFIT_setup(). Aborting...");
	    return cpl_error_set_message(cpl_func, CPL_ERROR_FILE_NOT_FOUND,
	                                     "%s not found", imagefile);
	}

	exptime = cpl_propertylist_get_double(header, "EXPTIME");

	if(debug == 1) {
		printf("EXPTIME in create_GALFIT_setup() : %f\n", exptime);
	}

	if(exptime <= 0) {
		cpl_msg_error(cpl_func, "Exptime not found in "
				"create_GALFIT_setup()!!!");
	}

	cpl_propertylist_delete(header);

	// Prepare filename paths and input data for setup file

	sprintf(stamp, "%s", imagefile);

	xsize = cpl_table_get_int(tab, "STAMP_XHI",*i, NULL) -
			cpl_table_get_int(tab, "STAMP_XLO",*i, NULL) + 1;
	ysize = cpl_table_get_int(tab, "STAMP_YHI",*i, NULL) -
			cpl_table_get_int(tab, "STAMP_YLO",*i, NULL) + 1;

	if(debug == 1) {
		printf("STAMP SIZES x : %d  y : %d\n", xsize, ysize);
	}

	if(xsize <= 0 || ysize <= 0) {
		cpl_msg_error(cpl_func, "In create_GALFIT_setup() : Stamp image not found!");
	}

	sprintf(galsetfile, "%s%s%s%s%ld",
			cpl_table_get_string(tab, "TILE_DIRECTORY", *i), "/", galfitset, "_", *i + 1);

	if(debug == 1) {
		printf("GALFIT-Setup FILE : %s\n", galsetfile);
	}

	sprintf(galfitim, "%s%s%s%ld%s", cpl_table_get_string(tab, "TILE_DIRECTORY", *i),
			"/", object, *i + 1, ".fits");

	if(debug == 1) {
		printf("GALFIT imageblock FILE : %s\n", galfitim);
	}

	if (strcmp(badpix, "n") != 0 && strcmp(badpix, "no") != 0 &&
			strcmp(badpix, "none") != 0) {
		sprintf(maskfile, "%s%s%s%s%ld%s", cpl_table_get_string(tab, "TILE_DIRECTORY", *i),
				"/", badpix, "_", *i + 1, ".fits");

		// Check if accessable

		if(access(maskfile, 00) != 0) {
			cpl_msg_error(cpl_func, "Mask file is not "
					"accessable in create_GALFIT_Setup() for setup "
					"%ld !!! GALFIT will be started anyway but "
					"without mask.", *i + 1);
		}

		if(debug == 1) {
			printf("GALFIT mask FILE : %s\n", maskfile);
		}

	} else {
		sprintf(maskfile, "%s", "none");
	}

	if (strcmp(constraints, "n") != 0 && strcmp(constraints, "no") != 0 &&
			strcmp(constraints, "none") != 0) {
		sprintf(constraintfile, "%s%s%s%s%ld",
				cpl_table_get_string(tab, "TILE_DIRECTORY", *i), "/",
				constraints, "_", *i + 1);

		// Check if accessable

		if(access(constraintfile, 00) != 0) {
			cpl_msg_error(cpl_func, "Constraint file is not "
					"accessable in create_GALFIT_Setup() for setup "
					"%ld !!! GALFIT will be started anyway but "
					"without constraints.", *i + 1);
		}

		if(debug == 1) {
			printf("GALFIT constraint FILE : %s\n", constraintfile);
		}

	} else {
		sprintf(constraintfile, "%s", "none");
	}

	// Read object data from table

	background  =  cpl_table_get_double(tab, "GALA_BACKGROUND", *i, NULL);
	xc      	=  cpl_table_get_double(tab, "X_IMAGE", *i, NULL);
	yc    	    =  cpl_table_get_double(tab, "Y_IMAGE", *i, NULL);
	aim 		=  cpl_table_get_double(tab, "A_IMAGE", *i, NULL);
	bim 		=  cpl_table_get_double(tab, "B_IMAGE", *i, NULL);
	theta 		=  cpl_table_get_double(tab, "THETA_IMAGE", *i, NULL);
	mag     	=  cpl_table_get_double(tab, "MAG_BEST", *i, NULL);
	if(isnan(mag) != 0) {
		mag = 20;
		cpl_msg_error(cpl_func, "SExtractor magnitude error for object %ld.\n",
				*i);
	}
	fr     	    =  cpl_table_get_double(tab, "FLUX_RADIUS", *i, NULL);
	if(fr <= 0) {
		cpl_msg_error(cpl_func, "SExtractor parameter error for object %ld.\n",
				*i);
		fr = 1;
	}
	xlo         =  cpl_table_get_int(tab, "STAMP_XLO", *i, NULL);
	ylo         =  cpl_table_get_int(tab, "STAMP_YLO", *i, NULL);
	xfit  = xc - xlo;
	yfit  = yc - ylo;
	// xxx correct? oder noch if < -180 -> theta += 180 hinzufügen?
	theta = theta - 90;

	// Write GALFIT setup file

	fp_gs = fopen(galsetfile, "w");

	fprintf(fp_gs, "===================================================\n");
	fprintf(fp_gs, "# IMAGE and GALFIT CONTROL PARAMETERS\n");
	fprintf(fp_gs, "A) %s\n", stamp);
	fprintf(fp_gs, "B) %s\n", galfitim);
	fprintf(fp_gs, "C) none\n");
	fprintf(fp_gs, "D) %s\n", psf);
	fprintf(fp_gs, "E) %f\n", psffactor);
	fprintf(fp_gs, "F) %s\n", maskfile);
	fprintf(fp_gs, "G) %s\n", constraintfile);
	fprintf(fp_gs, "H) %d   %d   %d   %d\n", 1, xsize, 1, ysize);
	fprintf(fp_gs, "I) %d   %d\n", (int)convbox, (int)convbox);
	fprintf(fp_gs, "J) %.4f\n", magzero);
	fprintf(fp_gs, "K) %.5f %.5f\n", platescale, platescale);
	fprintf(fp_gs, "O) %s\n", display);
	fprintf(fp_gs, "P) 0\n\n");

	fprintf(fp_gs, "# sky\n");
	fprintf(fp_gs, "0) sky\n");

	if(skyfix == CPL_TRUE) {
		if(isnan(background) == 0) {
			fprintf(fp_gs, "1) %.3f 0\n", background);
		} else {
			fprintf(fp_gs, "1) 0 1\n");
		}
		fprintf(fp_gs, "2) %f 0\n", 0.);
		fprintf(fp_gs, "3) %f 0\n", 0.);
	} else {
		fprintf(fp_gs, "1) %.3f 1\n", background);
		fprintf(fp_gs, "2) %f 1\n", 0.);
		fprintf(fp_gs, "3) %f 1\n", 0.);
	}
	fprintf(fp_gs, "Z) 0\n\n");

	fprintf(fp_gs, "# Sersic function\n");
	fprintf(fp_gs, "0) sersic\n");
	fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xfit, yfit);
	fprintf(fp_gs, "3) %.2f 1\n", mag);
	fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));
	fprintf(fp_gs, "5) %.2f 1\n", 2.5);
	fprintf(fp_gs, "9) %.4f 1\n", bim / aim);
	fprintf(fp_gs, "10) %.2f 1\n", theta);
	fprintf(fp_gs, "Z) 0\n\n");

	// Add secondaries

	help = cpl_table_get_array(tab, "SECONDARY_INDICES", *i);

	secindices = cpl_array_duplicate(help);

	for(j = 0; j < cpl_array_get_size(secindices); j++) {
		if(cpl_array_get(secindices, j, NULL) > 0) {
			secnum++;
		}
	}

	// If secondaries exist, amplify GALFIT setup file for each secondary

	for(lv = 0; lv < secnum; lv++) {

		k = (long)cpl_array_get(secindices, lv, NULL);

		if(k <= 0) {
			cpl_msg_error(cpl_func, "An internal error occured in "
					"create_GALFIT_setup(). Secondary has negative "
					"table index!");
			break;
		}

		sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", *i));
		sprintf(fitfile, "%s%s%s%ld%s", directory, "/", object, k, ".fits");

		xlo_sec = cpl_table_get_int(tab, "STAMP_XLO", k-1, NULL);
		ylo_sec = cpl_table_get_int(tab, "STAMP_YLO", k-1, NULL);

		// If fit for secondary exists

		if(access(fitfile, 00) == 0) {

			// Read data from fit

			fitsheader = cpl_propertylist_load(fitfile, 2);

			if(fitsheader == NULL) {

				if(debug == 1) {
					cpl_msg_error(cpl_func, "Unspecified problem with loading Header in "
						"create_GALFIT_setup() from %s. "
						"Possibly GALFIT crashed for this object.", fitfile);
				}

				fprintf(fp_gs, "# Sersic function\n");
				fprintf(fp_gs, "0) sersic\n");

				xsec  = xfit + cpl_table_get_double(tab, "X_IMAGE", k - 1, NULL) - xc;
				ysec  = yfit + cpl_table_get_double(tab, "Y_IMAGE", k - 1, NULL) - yc;
				fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xsec, ysec);

				mag = cpl_table_get_double(tab, "MAG_BEST", k - 1, NULL);
				fprintf(fp_gs, "3) %.2f 1\n", mag);

				fr = cpl_table_get_double(tab, "FLUX_RADIUS", k - 1, NULL);

				fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));

				fprintf(fp_gs, "5) %.2f 1\n", 2.5);

				eli = cpl_table_get_double(tab, "ELLIPTICITY", k - 1, NULL);
				fprintf(fp_gs, "9) %.4f 1\n", 1 - eli);

				theta = cpl_table_get_double(tab, "THETA_IMAGE", k - 1, NULL);

				if(theta >= 0) {
					theta = theta - 90;
				} else {
					theta = 90 + theta;
				}
				fprintf(fp_gs, "10) %.2f 1\n", theta);

				fprintf(fp_gs, "Z) 0\n\n");

			} else {

				fprintf(fp_gs, "# Sersic function\n");
				fprintf(fp_gs, "0) sersic\n");

				count = 0;

				if(cpl_propertylist_has(fitsheader, "2_XC") == 1) {
					sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_XC"));
					sprintf(xp, "%s", cpl_propertylist_get_string(fitsheader, "2_XC"));
				} else {
					cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
					sprintf(xp, "%s", "1");
				}
				remove_chr(xp);
				ptr = strtok(xp, " ");
				while(ptr != NULL) {
					if(count == 0) {
						xcgalfit = atof(ptr);
					}
					ptr = strtok(NULL, " ");
					count ++;
				}
				count = 0;

				if(cpl_propertylist_has(fitsheader, "2_YC") == 1) {
					sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_YC"));
					sprintf(yp, "%s", cpl_propertylist_get_string(fitsheader, "2_YC"));
				} else {
					cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
					sprintf(yp, "%s", "1");
				}
				remove_chr(yp);
				ptr = strtok(yp, " ");
				while(ptr != NULL) {
					if(count == 0) {
						ycgalfit = atof(ptr);
					}
					ptr = strtok(NULL, " ");
					count ++;
				}
				count = 0;

				/*coordinate transformation*/
				xcgalfit = xlo_sec + xcgalfit - xlo;
				ycgalfit = ylo_sec + ycgalfit - ylo;

				fprintf(fp_gs, "1) %.2f %.2f 0 0\n", xcgalfit, ycgalfit);

				if(cpl_propertylist_has(fitsheader, "2_MAG") == 1) {
					sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_MAG"));
					sprintf(mg, "%s", cpl_propertylist_get_string(fitsheader, "2_MAG"));
				} else {
					cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
					sprintf(mg, "%s", "20");
				}
				remove_chr(mg);
				ptr = strtok(mg, " ");
				while(ptr != NULL) {
					if(count == 0) {
						maggalfit = atof(ptr);
					}
					ptr = strtok(NULL, " ");
					count ++;
				}
				count = 0;

				fprintf(fp_gs, "3) %.2f 0\n", maggalfit);

				if(cpl_propertylist_has(fitsheader, "2_RE") == 1) {
					sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_RE"));
					sprintf(re, "%s", cpl_propertylist_get_string(fitsheader, "2_RE"));
				} else {
					cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
					sprintf(re, "%s", "20");
				}
				remove_chr(re);
				ptr = strtok(re, " ");
				while(ptr != NULL) {
					if(count == 0) {
						regalfit = atof(ptr);
					}
					ptr = strtok(NULL, " ");
					count ++;
				}
				count = 0;

				fprintf(fp_gs, "4) %.2f 0\n", regalfit);

				if(cpl_propertylist_has(fitsheader, "2_N") == 1) {
					sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_N"));
					sprintf(n, "%s", cpl_propertylist_get_string(fitsheader, "2_N"));
				} else {
					cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
					sprintf(n, "%s", "2.5");
				}
				remove_chr(n);
				ptr = strtok(n, " ");
				while(ptr != NULL) {
					if(count == 0) {
						ngalfit = atof(ptr);
					}
					ptr = strtok(NULL, " ");
					count ++;
				}
				count = 0;

				fprintf(fp_gs, "5) %.2f 0\n", ngalfit);

				if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
					sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
					sprintf(ar, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
				} else {
					cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
					sprintf(ar, "%s", "0.8");
				}
				remove_chr(ar);
				ptr = strtok(ar, " ");
				while(ptr != NULL) {
					if(count == 0) {
						argalfit = atof(ptr);
					}
					ptr = strtok(NULL, " ");
					count ++;
				}
				count = 0;

				fprintf(fp_gs, "9) %.2f 0\n", argalfit);

				if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
					sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
					sprintf(pa, "%s", cpl_propertylist_get_string(fitsheader, "2_PA"));
				} else {
					cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
					sprintf(pa, "%s", "0");
				}
				remove_chr(pa);
				ptr = strtok(pa, " ");
				while(ptr != NULL) {
					if(count == 0) {
						pagalfit = atof(ptr);
					}
					ptr = strtok(NULL, " ");
					count ++;
				}
				count = 0;

				fprintf(fp_gs, "10) %.2f 0\n", pagalfit);

				fprintf(fp_gs, "Z) 0\n\n");

			}

			cpl_propertylist_delete(fitsheader);

			// If fit for secondary does not exist take SExtractor parameters

		} else {

			fprintf(fp_gs, "# Sersic function\n");
			fprintf(fp_gs, "0) sersic\n");

			xsec  = xfit + cpl_table_get_double(tab, "X_IMAGE", k - 1, NULL) - xc;
			ysec  = yfit + cpl_table_get_double(tab, "Y_IMAGE", k - 1, NULL) - yc;
			fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xsec, ysec);

			mag = cpl_table_get_double(tab, "MAG_BEST", k - 1, NULL);
			fprintf(fp_gs, "3) %.2f 1\n", mag);

			fr = cpl_table_get_double(tab, "FLUX_RADIUS", k - 1, NULL);

			fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));

			fprintf(fp_gs, "5) %.2f 1\n", 2.5);

			eli = cpl_table_get_double(tab, "ELLIPTICITY", k - 1, NULL);
			fprintf(fp_gs, "9) %.4f 1\n", 1 - eli);

			theta = cpl_table_get_double(tab, "THETA_IMAGE", k - 1, NULL);

			if(theta >= 0) {
				theta = theta - 90;
			} else {
				theta = 90 + theta;
			}
			fprintf(fp_gs, "10) %.2f 1\n", theta);

			fprintf(fp_gs, "Z) 0\n\n");
		}
	}

	cpl_array_delete(secindices);

	// Include also potential contrib targets

	help = cpl_table_get_array(tab, "POT_CT_INDICES", *i);

	ctindices = cpl_array_duplicate(help);

	// Get number of contribs

	for(j = 0; j < cpl_array_get_size(ctindices); j++) {
		if(cpl_array_get(ctindices, j, NULL) > 0) {
			ctnum++;
		}
	}

	for(lv = 0; lv < ctnum; lv++) {

		k = (long)cpl_array_get(ctindices, lv, NULL) - 1;

		if(k < 0) {
			cpl_msg_error(cpl_func, "An internal error occured in "
					"create_GALFIT_setup(). Secondary has negative "
					"table index!");
			break;
		}

//		if(debug == 1) {
			cpl_msg_info(cpl_func, "Check potential contrib target No %ld "
				"for object No %ld.\n", k + 1, *i + 1);
//		}

		sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", k));
		sprintf(fitfile, "%s%s%s%ld%s", directory, "/", object, k + 1, ".fits");

		// If fit for contrib target exists

		if(access(fitfile, 00) == 0) {

			printf("FITFILE %s is found!\n", fitfile);

			if(check_contribtarget(tab, object, &*i, &k, &magzero, &exptime,
					&magexclude, &magcrit, &fluxextend) == 0) {

				printf("%s identified as contrib target!\n", fitfile);

				// Read data from fit

				fitsheader = cpl_propertylist_load(fitfile, 2);

				fprintf(fp_gs, "# Sersic function\n");
				fprintf(fp_gs, "0) sersic\n");

				count = 0;

				if(cpl_propertylist_has(fitsheader, "2_XC") == 1) {
					sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_XC"));
					sprintf(xp, "%s", cpl_propertylist_get_string(fitsheader, "2_XC"));
				} else {
					cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
					sprintf(xp, "%s", "1");
				}
				remove_chr(xp);
				ptr = strtok(xp, " ");
				while(ptr != NULL) {
					if(count == 0) {
						xcgalfit = atof(ptr);
					}
					ptr = strtok(NULL, " ");
					count ++;
				}
				count = 0;

				if(cpl_propertylist_has(fitsheader, "2_YC") == 1) {
					sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_YC"));
					sprintf(yp, "%s", cpl_propertylist_get_string(fitsheader, "2_YC"));
				} else {
					cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
					sprintf(yp, "%s", "1");
				}
				remove_chr(yp);
				ptr = strtok(yp, " ");
				while(ptr != NULL) {
					if(count == 0) {
						ycgalfit = atof(ptr);
					}
					ptr = strtok(NULL, " ");
					count ++;
				}
				count = 0;

				//xxx

				/* transform into local stamp coordinates */
				xcgalfit  = (double)cpl_table_get_int(tab, "STAMP_XLO", k, NULL)
						+xcgalfit-
						(double)cpl_table_get_int(tab, "STAMP_XLO", *i, NULL);

				ycgalfit  = (double)cpl_table_get_int(tab, "STAMP_YLO", k, NULL)
						+ycgalfit-
						(double)cpl_table_get_int(tab, "STAMP_YLO", *i, NULL);

				fprintf(fp_gs, "1) %.2f %.2f 0 0\n", xcgalfit, ycgalfit);

				if(cpl_propertylist_has(fitsheader, "2_MAG") == 1) {
					sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_MAG"));
					sprintf(mg, "%s", cpl_propertylist_get_string(fitsheader, "2_MAG"));
				} else {
					cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
					sprintf(mg, "%s", "20");
				}
				remove_chr(mg);
				ptr = strtok(mg, " ");
				while(ptr != NULL) {
					if(count == 0) {
						maggalfit = atof(ptr);
					}
					ptr = strtok(NULL, " ");
					count ++;
				}
				count = 0;

				fprintf(fp_gs, "3) %.2f 0\n", maggalfit);

				if(cpl_propertylist_has(fitsheader, "2_RE") == 1) {
					sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_RE"));
					sprintf(re, "%s", cpl_propertylist_get_string(fitsheader, "2_RE"));
				} else {
					cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
					sprintf(re, "%s", "20");
				}
				remove_chr(re);
				ptr = strtok(re, " ");
				while(ptr != NULL) {
					if(count == 0) {
						regalfit = atof(ptr);
					}
					ptr = strtok(NULL, " ");
					count ++;
				}
				count = 0;

				fprintf(fp_gs, "4) %.2f 0\n", regalfit);

				if(cpl_propertylist_has(fitsheader, "2_N") == 1) {
					sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_N"));
					sprintf(n, "%s", cpl_propertylist_get_string(fitsheader, "2_N"));
				} else {
					cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
					sprintf(n, "%s", "2.5");
				}
				remove_chr(n);
				ptr = strtok(n, " ");
				while(ptr != NULL) {
					if(count == 0) {
						ngalfit = atof(ptr);
					}
					ptr = strtok(NULL, " ");
					count ++;
				}
				count = 0;

				fprintf(fp_gs, "5) %.2f 0\n", ngalfit);

				if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
					sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
					sprintf(ar, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
				} else {
					cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
					sprintf(ar, "%s", "0.8");
				}
				remove_chr(ar);
				ptr = strtok(ar, " ");
				while(ptr != NULL) {
					if(count == 0) {
						argalfit = atof(ptr);
					}
					ptr = strtok(NULL, " ");
					count ++;
				}
				count = 0;

				fprintf(fp_gs, "9) %.2f 0\n", argalfit);

				if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
					sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
					sprintf(pa, "%s", cpl_propertylist_get_string(fitsheader, "2_PA"));
				} else {
					cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
					sprintf(pa, "%s", "0");
				}
				remove_chr(pa);
				ptr = strtok(pa, " ");
				while(ptr != NULL) {
					if(count == 0) {
						pagalfit = atof(ptr);
					}
					ptr = strtok(NULL, " ");
					count ++;
				}
				count = 0;

				fprintf(fp_gs, "10) %.2f 0\n", pagalfit);
				fprintf(fp_gs, "Z) 0\n\n");

				cpl_propertylist_delete(fitsheader);

			} else {

				printf("%s identified as NO contrib target!\n", fitfile);
			}

		} else {

			printf("FITFILE %s contrib target NOT ACCESSABLE!\n", fitfile);

			if(check_contribtarget_sexdata(tab, &*i, &k, &magzero, &exptime,
					&magexclude, &magcrit, &fluxextend) == 0) {

				fprintf(fp_gs, "# Sersic function\n");
				fprintf(fp_gs, "0) sersic\n");

				xsec  = cpl_table_get_double(tab, "X_IMAGE", k, NULL) - xlo;
				ysec  = cpl_table_get_double(tab, "Y_IMAGE", k, NULL) - ylo;
				fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xsec, ysec);

				mag = cpl_table_get_double(tab, "MAG_BEST", k, NULL);
				fprintf(fp_gs, "3) %.2f 1\n", mag);

				fr = cpl_table_get_double(tab, "FLUX_RADIUS", k, NULL);
				fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));

				fprintf(fp_gs, "5) %.2f 1\n", 2.5);

				eli = cpl_table_get_double(tab, "ELLIPTICITY", k, NULL);
				fprintf(fp_gs, "9) %.4f 1\n", 1 - eli);

				theta = cpl_table_get_double(tab, "THETA_IMAGE", k, NULL);
				if(theta >= 0) {
					theta = theta - 90;
				} else {
				theta = 90 + theta;
				}
				fprintf(fp_gs, "10) %.2f 1\n", theta);

				fprintf(fp_gs, "Z) 0\n\n");
			}
		}
	}

	cpl_array_delete(ctindices);

	fclose(fp_gs);
	cpl_table_delete(tab);

	return CPL_ERROR_NONE;
}



int readfits_header(const char *imagefile) {

	int flag = 0;
	char flagstring[FILENAME_MAX];
	char *ptr;
	cpl_propertylist *header;

	if(access(imagefile, 00) == 0) {
		header = cpl_propertylist_load(imagefile, 2);
		if (header == NULL) {

			// image not found

			cpl_propertylist_delete(header);
			cpl_msg_error(cpl_func, "Header file not found!");
			return -1;
		}

		if(cpl_propertylist_has(header, "FLAGS") == 1) {

			sprintf(flagstring, "%s", cpl_propertylist_get_string(header, "FLAGS"));

			ptr = strtok(flagstring, " ");

			while(ptr != NULL) {

				if(strcmp(ptr, "1") == 0) {

					flag = 1;

				}

				if(strcmp(ptr, "2") == 0) {

					flag += 2;

				}

				ptr = strtok(NULL, " ");
			}
		} else {
			cpl_msg_error(cpl_func, "In readfits_header() : "
					"Property FLAGS is not available in "
					"imagefile %s.", imagefile);
			flag = 0;
		}

		cpl_propertylist_delete(header);

	} else {
		cpl_msg_error(cpl_func, "In readfits_header() : "
				"Imagefile %s was not accessable.", imagefile);
		return -1;
	}

	return flag;
}


cpl_error_code merge_tables(cpl_array *imagearray, cpl_array *directory,
		cpl_parameterlist *gala_setup) {

	int i, j, xsize, ysize, ntiles, as, nrow, ctabno, ntabno,
		ctabrow, tabrow, nneighbor, debug = 0;
	double xc, yc, dist, rebinfactor = 5;
	char tabfile[FILENAME_MAX];
	char colname[FILENAME_MAX];
	char ctabfile[FILENAME_MAX];
	char ntabfile[FILENAME_MAX];
	char imagefile[FILENAME_MAX];
	char cleantabfile[FILENAME_MAX];
	char cleantabname[FILENAME_MAX];
	char out_tab[FILENAME_MAX];
	char combtabfile[FILENAME_MAX];
	char outdir[FILENAME_MAX];
	char combtabname[FILENAME_MAX];
	char str[FILENAME_MAX];
	struct stat st;
	cpl_array *borderpix;
	cpl_image *image;
	cpl_matrix *neighbormx;
	cpl_parameter *p;
	cpl_propertylist *centralheader, *list;
	cpl_table *combtab, *borderpixtab, *tab, *ctab, *ntab, *doubletab;
	cpl_wcs *wcs;


	// extract data from parameterlist

	p = cpl_parameterlist_find(gala_setup, "out_tab");
	sprintf(out_tab, "%s", cpl_parameter_get_string(p));

	p = cpl_parameterlist_find(gala_setup, "neighbortiles");
	nneighbor = (int)cpl_parameter_get_double(p);

	p = cpl_parameterlist_find(gala_setup, "outdir");
	sprintf(outdir, "%s", cpl_parameter_get_string(p));

//	p = cpl_parameterlist_find(gala_setup, "cleantab");
//	sprintf(cleantabname, "%s", cpl_parameter_get_string(p));

	sprintf(cleantabname, "%s", "cleantab.fits");

	p = cpl_parameterlist_find(gala_setup, "sexcomb");
	sprintf(combtabname, "%s", cpl_parameter_get_string(p));

	sprintf(combtabfile, "%s%s%s", outdir, "/", combtabname);

	//starting message

	cpl_msg_info(cpl_func, "Cleaning tables from overlapping neighbor "
			"detections and merging tables.");

	// Check if directory for contrib target tables is already existing -
	// if not create

    if(stat(outdir, &st) != 0) {
		sprintf(str, "%s %s", "mkdir", outdir);
		if (system(str) != 0) {
			printf("Problem with creating output directory for contrib targets."
					"\n");
		}
	}

	// identify number of neighbor tiles

	ntiles = cpl_array_get_size(imagearray);

	// If only one image is present

	if(ntiles <= 1 || nneighbor == 0) {

		cpl_msg_info(cpl_func, "No overlapping tiles present. "
				"saving table into file %s and "
				"going to next step now.", combtabfile);

		sprintf(tabfile, "%s%s%s", cpl_array_get_string(directory, 0),
				"/", out_tab);

		tab = cpl_table_load(tabfile, 1, 0);

		// Save just a copy of table into combined catalog directory

		cpl_table_save(tab, NULL, NULL, combtabfile, CPL_IO_CREATE);

		cpl_table_delete(tab);

		return CPL_ERROR_NONE;
	}

	// prepare combined catalog

	combtab = cpl_table_new(0);

	// prepare catalog for arrays with image boundary information

	borderpixtab = cpl_table_new(1);

	// CALCULATE DISTANCE TO THE EDGE FOR EVERY ELEMENT AND SORT TABLES

	for(i = 0; i < ntiles; i++) {

		// load cpl_tables

		sprintf(tabfile, "%s%s%s", cpl_array_get_string(directory, i),
				"/", out_tab);

		tab = cpl_table_load(tabfile, 1, 0);

		if(cpl_table_unselect_all(tab) != CPL_ERROR_NONE) {
			cpl_msg_error(cpl_func, "Input table is a NULL pointer.");
		}

		// check how many elements to loop over

		nrow = (int)cpl_table_get_nrow(tab);

		// label each tab element according to its tile

		if(cpl_table_has_column(tab, "TILE") == 0) {
			cpl_table_new_column(tab, "TILE", CPL_TYPE_STRING);
		}

		// prepare combined catalog

		if(cpl_table_compare_structure(combtab, tab) == 1 && i == 0) {
			cpl_table_copy_structure(combtab, tab);
		}

		if(cpl_table_has_column(tab, "DIST_TO_EDGE") == 0) {

			cpl_table_new_column(tab, "DIST_TO_EDGE", CPL_TYPE_DOUBLE);
			cpl_table_new_column(combtab, "DIST_TO_EDGE", CPL_TYPE_DOUBLE);

			// load input image

			image = cpl_image_load(cpl_array_get_string(imagearray, i),
					CPL_TYPE_DOUBLE, 0, 0);

			// prepare borderpixel array

			borderpix = cpl_array_new(0, CPL_TYPE_INT);

			// get information of border pixels

			if(construct_aquarium(borderpix, image, &rebinfactor) !=
					CPL_ERROR_NONE) {
				cpl_msg_error(cpl_func, "Unspecified problem with handling"
						"image boundaries.");
				return CPL_ERROR_UNSPECIFIED;
			}

			// set border pixel array from every tile into a table

			sprintf(colname, "%s%d", "tile", i);
			as = cpl_array_get_size(borderpix);

			cpl_table_new_column_array(borderpixtab, colname, CPL_TYPE_INT, as);

			cpl_table_set_array(borderpixtab, colname, 0, borderpix);

			// calculate distance to the border for every object in every tile

			for(j = 0; j < nrow; j++) {

				// reset image dimensions

				xsize = cpl_image_get_size_x(image);
				ysize = cpl_image_get_size_y(image);

				xc = cpl_table_get_double(tab, "X_IMAGE", j, NULL);
				yc = cpl_table_get_double(tab, "Y_IMAGE", j, NULL);

				dist = calc_dist_to_edge(&xc, &yc, borderpix, &xsize, &ysize,
						&rebinfactor);
				if(dist == -1) {
					cpl_msg_error(cpl_func, "Unspecified problem with"
							"calculating object distances to the edge.");
				}

				cpl_table_set(tab, "DIST_TO_EDGE", j, dist);
			}

			cpl_array_delete(borderpix);
			cpl_image_delete(image);
		}

		cpl_table_save(tab, NULL, NULL, tabfile, CPL_IO_CREATE);

		cpl_table_delete(tab);
	}

	// CONSTRUCT NEIGHBOR MATRIX

	neighbormx = identify_neighbortiles(imagearray);

//	if(debug == 1) {
		printf("NEIGHBORMATRIX\n");
		cpl_matrix_dump(neighbormx, NULL);
//	}

	// CLEAN TABLES

	for(i = 0; i < ntiles; i++) {

		// load table from central tile

		ctabno = (int)cpl_matrix_get(neighbormx, i, 0);
		sprintf(ctabfile, "%s%s%s", cpl_array_get_string(directory, ctabno - 1),
				"/", out_tab);
		if(access(ctabfile, 00) != 0) {
			cpl_msg_error(cpl_func, "File access error in merge_tables()! Table "
					"file not accessable.");
		}
		ctab = cpl_table_load(ctabfile, 1, 0);
		ctabrow = (int)cpl_table_get_nrow(ctab);
		if(debug == 1) {
			printf(" %d. Katalog  %s\n", i + 1, ctabfile);
			printf("CTAB ROW ANFANG: %d\n", ctabrow);
		}

		// prepare central image path

		sprintf(imagefile, "%s", cpl_array_get_string(imagearray, ctabno - 1));
		if(access(imagefile, 00) != 0) {
			cpl_msg_error(cpl_func, "File access error in merge_tables()! Image "
					"file not accessable.");
		}

		// read central image fits header

		centralheader = cpl_propertylist_load(imagefile, 0);
		if (centralheader == NULL) {

			// image not found

			cpl_propertylist_delete(centralheader);
			cpl_msg_error(cpl_func, "Header file not found!");
		}

		// create wcs structure from central image header

		wcs = cpl_wcs_new_from_propertylist(centralheader);
		if (wcs == NULL) {
			printf("Unable to parse header\n");
		}
		if (cpl_error_get_code() == CPL_ERROR_NO_WCS) {
			cpl_msg_warning(cpl_func, "WCSLIB not found - skip cpl_wcs tests") ;
		}

		// loop over neighbors - nneighbor is a user specified number

		for(j = 1; j <= nneighbor; j++) {

			// load tables from neighbor tiles

			ntabno = (int)cpl_matrix_get(neighbormx, i, j);
			sprintf(ntabfile, "%s%s%s",
					cpl_array_get_string(directory, ntabno - 1), "/", out_tab);
			if(access(ntabfile, 00) != 0) {
				cpl_msg_error(cpl_func, "File access error in merge_tables()! Table "
						"file %s not accessable.", ntabfile);
			} else {
				if(debug == 1) {
					printf(" %d. Nachbarkatalog  %s\n", j, ntabfile);
				}
				ntab = cpl_table_load(ntabfile, 1, 0);

				// attach both catalogs

				doubletab = cpl_table_duplicate(ctab);
				tabrow = cpl_table_get_nrow(doubletab);
				cpl_table_insert(doubletab, ntab, tabrow);

				// clean all three catalogs from double detected objects objects

				nrow = cpl_table_get_nrow(ctab);
				if(debug == 1) {
					printf("NROW 	DAVOR: %d\n", nrow);
				}

				clear_catalogue(ctab, ntab, doubletab, wcs);

				nrow = cpl_table_get_nrow(ctab);
				if(debug == 1) {
					printf("NROW   DANACH: %d\n", nrow);
				}
				nrow = cpl_table_get_nrow(ntab);

				cpl_table_delete(ntab);
				cpl_table_delete(doubletab);
			}
		}

		// DEBUG : CHECK NUMBER OF DELETED ROWS

		ctabrow = cpl_table_get_nrow(ctab);
		if(debug == 1) {
			printf("CTAB ROW ENDE: %d\n", ctabrow);
		}

		// sort clean tab again according to magnitude

		list = cpl_propertylist_new();
		cpl_propertylist_append_bool(list, "MAG_BEST", CPL_FALSE);
		cpl_table_sort(ctab, list);
		cpl_propertylist_delete(list);

		// Save cleaned table for every tile

		sprintf(cleantabfile, "%s%s%s",
				cpl_array_get_string(directory, ctabno - 1), "/", cleantabname);

		cpl_table_save(ctab, NULL, NULL, cleantabfile, CPL_IO_CREATE);

		// to get complete combined catalog insert all ctabs in the
		// loop in the combined catalog

		cpl_table_insert(combtab, ctab, cpl_table_get_nrow(combtab));

		cpl_propertylist_delete(centralheader);
		cpl_table_delete(ctab);
		cpl_wcs_delete(wcs);
	}

	// save combtab

//	cpl_table_dump(combtab, 0, 10, NULL);
	if(debug == 1) {
		printf("ROW IN COMBTAB %d\n", (int)cpl_table_get_nrow(combtab));
	}

	// sort combtab according to magnitude

	list = cpl_propertylist_new();
	cpl_propertylist_append_bool(list, "MAG_BEST", CPL_FALSE);
	cpl_table_sort(combtab, list);
	cpl_propertylist_delete(list);

	// save combtab

	cpl_table_save(combtab, NULL, NULL, combtabfile, CPL_IO_CREATE);

	cpl_matrix_delete(neighbormx);
	cpl_table_delete(borderpixtab);
	cpl_table_delete(combtab);

	return CPL_ERROR_NONE;
}



cpl_error_code *construct_aquarium(cpl_array *borderpix, cpl_image *image,
		const double *rebinfactor) {

	int i, j, xsize, ysize, checkval, q = 99, debug = 0;
	long int k = 0;
	double median, pixval;
	cpl_image *aquarium, *filterimage, *rebinaquarium;
	cpl_mask *kernel;


	// Prepare kernel for image filtering

    kernel = cpl_mask_new(3, 3);
    cpl_mask_not(kernel);

    // Get image dimensions

	xsize = cpl_image_get_size_x(image);
	ysize = cpl_image_get_size_y(image);

	// Weightfilter: The filtered weight image
	// Aquarium: Image with fix borders defined by weight image

	filterimage = cpl_image_new(xsize, ysize, CPL_TYPE_DOUBLE);
	aquarium    = cpl_image_new(xsize, ysize, CPL_TYPE_INT);

	// Calculate weight image median

    median = cpl_image_get_median(image);

    // Set border pixels in image to an extreme value

    for(i = 1; i <= xsize; i++) {
        for(j = 1; j <= ysize; j++) {
        	pixval = cpl_image_get(image, i, j, &q);
        	if(pixval == median) {
        		cpl_image_set(image, i, j, -5*median);
        	}
        }
    }

    // Filter procedure

	if(debug == 1) {
		cpl_msg_info(cpl_func, "Working on image filtering.");
	}

    cpl_image_filter_mask(filterimage, image, kernel, CPL_FILTER_MEDIAN,
                                               CPL_BORDER_FILTER);

	// Construct an "aquarium" for the SExtractor objects

	if(debug == 1) {
		cpl_msg_info(cpl_func, "Working on aquarium for SExtractor objects.");
	}

    for(i = 1; i <= xsize; i++) {
        for(j = 1; j <= ysize; j++) {
        	pixval = cpl_image_get(filterimage, i, j, &q);
        	if(pixval == -5*median) {
        		cpl_image_set(aquarium, i, j, 0);
        	} else {
        		cpl_image_set(aquarium, i, j, 1);
        	}
        }
    }

    // Rebin image for time optimization

    rebinaquarium = cpl_image_rebin(aquarium, 1, 1, *rebinfactor, *rebinfactor);

    // Control size of rebinned image

	xsize = cpl_image_get_size_x(rebinaquarium);
	ysize = cpl_image_get_size_y(rebinaquarium);

	// Set array size variable k to 0 to start a new loop for a new tile

	k = 0;

	// Loop over "aquarium"

    for(i = 1; i <= ysize; i++) {
        for(j = 1; j <= xsize; j++) {

        	// Get pixel values

        	checkval = cpl_image_get(rebinaquarium, j, i, &q);

        	// If pixel is 0, write 1d pixel position in an array

        	if(checkval == 0) {
        		cpl_array_set_size(borderpix, k + 1);
        		cpl_array_set_int(borderpix, k, j + (i - 1) * xsize);
            	k++;
        	}
        }
    }

    // Clean up

    cpl_mask_delete(kernel);
	cpl_image_delete(filterimage);
	cpl_image_delete(aquarium);
	cpl_image_delete(rebinaquarium);

	return CPL_ERROR_NONE;
}


double calc_dist_to_edge(double *xc, double *yc, cpl_array *borderpix,
		int *xsize, int *ysize, const double *rebinfactor) {

	int j, xzeropix, yzeropix;
	long int arsize;
	double tmp, dist, min;
	cpl_array *distarray;

	// Control input

	if(*xsize <= 0 || *yc <= 0 || *rebinfactor <= 0) {
		return -1;
	}

	// Get rebinned image and 0 pixel array dimensions

	*xsize /= *rebinfactor;
	*ysize /= *rebinfactor;
	arsize = (int)cpl_array_get_size(borderpix);

	// Reset calculation variables from former loops

	tmp = DBL_MAX;

	// Prepare new array containing distance from object to each 0 pixel

	distarray = cpl_array_new(0, CPL_TYPE_DOUBLE);

	// Adjust size of distance array

	cpl_array_set_size(distarray, arsize);

	// Adjust coordinates to the rebinned image

	*xc /= *rebinfactor;
	*yc /= *rebinfactor;

	// Loop over every 0 border pixel

	for(j = 0; j < arsize; j++) {

		// Calculate x-position from 1d array with 0 pixel positions

		xzeropix = cpl_array_get_int(borderpix, j, NULL) % *xsize;
		if(xzeropix == 0) {
			xzeropix = *xsize;
		}

		// Calculate y-position from 1d array with 0 pixel positions

		yzeropix = round(cpl_array_get_int(borderpix, j, NULL) / *xsize + 0.5);

		// Calculate distance from object center to every 0 pixel

		dist = *rebinfactor * sqrt(pow((*xc - xzeropix), 2) +
				                  pow((*yc - yzeropix), 2));

		// Faster Version without cpl_array ???

		if(dist < tmp) {
			tmp = dist;
		}

		// Set distance to every 0 pixel into a distance array

		cpl_array_set_double(distarray, j, dist);
	}

	// Calculate minimum distance

	min = cpl_array_get_min(distarray);

	// Clean up

	cpl_array_delete(distarray);

	return min;
}


// Look if a point is inside an ellipse or not

cpl_boolean ellpoint(const double *xc, const double *yc, const double *xp,
		const double *yp, const double* a, const double *b,
		const double *theta) {

	double xpt, ypt, xs;

	// Coordinate transformation:

	xpt = (*xp - *xc) * cos(*theta) + (*yp - *yc) * sin(*theta);
	ypt = (*xp - *xc) * (-1) * sin(*theta) + (*yp - *yc) * cos(*theta);

	// Intersection point xs from connection line between point and
	// ellipse center and the ellipse:

	xs = sqrt ((*b * *b) /
			((ypt * ypt) / (xpt * xpt) + (*b * *b) / (*a * *a)));

	// Comparison of x - coordinates is sufficient to give evidence if the point
	//	is inside or outside of the ellipse.

	if (fabs(xpt) > fabs(xs)) {
//		printf ("Point is outside of the ellipse!\n");
		return CPL_FALSE;
	} else {
//		printf ("Point is inside the ellipse!\n");
		return CPL_TRUE;
	}
}


//**************************************************************************
// Delete objects from two overlapping tiles from the original catalogues
// according to their distance to the border
//
// The routines loops over the merged catalog from the two neighboring tiles
// starting with the most distant one from the border, looking if there are
// overlapping objects from the neighboring catalog inside its SExtractor
// KRON ellipse. If this criteria is fulfilled, it will alternatingly remove
// all objects within this ellipse on the neighboring tile.
// The routine uses the wcs library to convert object coordinates from a
// neighboring tile.
//
// INPUT:   cpl_table *combcat      Simple attached catalog from two neighbor
//								    tiles
////		cpl_table *centraltab   Central tile table
//			cpl_table *neighbortab  Neighbor tile table
//          cpl_wcs *wcs            WCS from current image header
//
// OUTPUT:  cpl_table *combcat      Combined catalog with ambigious detections
//                                  on overlapping tiles removed
//			cpl_table *centraltab   Central tile table with critical objects
//								    removed
//			cpl_table *neighbortab  Neighbor tile table with critical objects
//                                  removed

cpl_error_code clear_catalogue(cpl_table *centraltab,
		cpl_table *neighbortab, cpl_table *combtab, cpl_wcs *wcs) {

	int i, j, cont, combrow, nrow;
	double a, b, theta, R, xt, yt, ra, dec, xneighbor, yneighbor;
	double pi = 3.14159265;
	char tile[FILENAME_MAX];
	char ntile[FILENAME_MAX];
	char centraltile[FILENAME_MAX];
	char neighbortile[FILENAME_MAX];
	cpl_array *status;
	cpl_matrix *primmatrix, *matrix;
	cpl_propertylist *list;
	cpl_table *cleancentraltab, *cleanneighbortab;

	// prepare separate output tables for primary tile and neighbor tile

	if(cpl_table_compare_structure(centraltab, neighbortab) == 1) {
		cpl_msg_error(cpl_func, "Error with neighboring tables. "
				"Input tables for clear_catalogue() are not correct. "
				"Central table and neighboring tables do not have "
				"the same structure.");
	}

	if(cpl_table_compare_structure(centraltab, combtab) == 1) {
		cpl_msg_error(cpl_func, "Error with tables. Input tables "
				"for clear_catalogue() are not correct. "
				"Central table and combined tables do not have "
				"the same structure.");
	}

	// sort tables according to distance to the border

	list = cpl_propertylist_new();
	cpl_propertylist_append_bool(list, "DIST_TO_EDGE", CPL_TRUE);
	cpl_table_sort(centraltab, list);
	cpl_propertylist_delete(list);

	list = cpl_propertylist_new();
	cpl_propertylist_append_bool(list, "DIST_TO_EDGE", CPL_TRUE);
	cpl_table_sort(neighbortab, list);
	cpl_propertylist_delete(list);

	list = cpl_propertylist_new();
	cpl_propertylist_append_bool(list, "DIST_TO_EDGE", CPL_TRUE);
	cpl_table_sort(combtab, list);
	cpl_propertylist_delete(list);

	cpl_table_unselect_all(centraltab);
	cpl_table_unselect_all(neighbortab);
	cpl_table_unselect_all(combtab);

	// transform all pixel coordinates into one coordinate system

	cpl_table_new_column(combtab, "X_TRANSFORMED", CPL_TYPE_DOUBLE);
	cpl_table_new_column(combtab, "Y_TRANSFORMED", CPL_TYPE_DOUBLE);

	combrow = cpl_table_get_nrow(combtab);

	for(i = 0; i < combrow; i++) {

		matrix = cpl_matrix_new(1, 2);
		ra  = cpl_table_get_double(combtab, "ALPHA_J2000", i, NULL);
		dec = cpl_table_get_double(combtab, "DELTA_J2000", i, NULL);
		cpl_matrix_set(matrix, 0, 0, ra);
		cpl_matrix_set(matrix, 0, 1, dec);
		cpl_wcs_convert(wcs, matrix, &primmatrix, &status,
				CPL_WCS_WORLD2PHYS);
		xt = cpl_matrix_get(primmatrix, 0, 0);
		yt = cpl_matrix_get(primmatrix, 0, 1);
		cpl_table_set_double(combtab, "X_TRANSFORMED", i, xt);
		cpl_table_set_double(combtab, "Y_TRANSFORMED", i, yt);
		cpl_matrix_delete(primmatrix);
		cpl_matrix_delete(matrix);
		cpl_array_delete(status);
	}

	// loop over every object in merged catalog

	for(i = 0; i < combrow; i++) {

		// loop only over unselected objects

		if(cpl_table_is_selected(combtab, i) == 0) {

			cont = 0;

			// get object parameters in primary tile

			xt    = cpl_table_get_double(combtab, "X_TRANSFORMED", i, NULL);
			yt    = cpl_table_get_double(combtab, "Y_TRANSFORMED", i, NULL);
			R     = cpl_table_get_double(combtab, "KRON_RADIUS", i, NULL);
			a     = R * cpl_table_get_double(combtab, "A_IMAGE", i, NULL);
			b     = R * cpl_table_get_double(combtab, "B_IMAGE", i, NULL);
			theta = cpl_table_get_double(combtab, "THETA_IMAGE", i, NULL);
			theta = 2 * pi * (theta / 360);
			sprintf(tile, "%s", cpl_table_get_string(combtab, "TILE", i));

//			printf("xt: %f\n", xt);
//			printf("yt: %f\n", yt);
//			printf("R: %f\n", R);
//			printf("a: %f\n", a);
//			printf("b: %f\n", b);
//			printf("theta: %f\n", theta);
//			printf("tile: %s\n\n", tile);

			// loop over every other object to check if objects from
			// neighboring tile are inside SExtractor ellipse

			for(j = i + 1; j < combrow; j++) {

				// get object parameters in other tile

				sprintf(ntile, "%s", cpl_table_get_string(combtab, "TILE", j));

				// look if there are objects in ellipse in the other tile

				if(strcmp(tile, ntile) != 0) {
					cont++;

					// get transformed coordinates

					xneighbor = cpl_table_get_double(combtab, "X_TRANSFORMED",
							j, NULL);
					yneighbor = cpl_table_get_double(combtab, "Y_TRANSFORMED",
							j, NULL);
//					printf("-----LOOP ----%d   %d---------------\n", i, j);
//					printf("xt: %f\n", xt);
//					printf("yt: %f\n", yt);
//					printf("a: %f\n", a);
//					printf("b: %f\n", b);
//					printf("theta: %f\n", theta);
//					printf("XNEIGHBOR: %f\n", xneighbor);
//					printf("YNEIGHBOR: %f\n", yneighbor);
//					printf("ntile: %s\n\n", ntile);

					// if object is inside ellipse remove from catalog

					if(ellpoint(&xneighbor, &yneighbor, &xt, &yt, &a, &b,
								&theta) == CPL_TRUE) {
						cpl_table_select_row(combtab, j);
						cont++;
					}
				}
			}
		}
	}

	// erase all selected objects

	cpl_table_erase_selected(combtab);

	// erase the helping column

	cpl_table_erase_column(combtab, "X_TRANSFORMED");
	cpl_table_erase_column(combtab, "Y_TRANSFORMED");

	// create new tables without double detections

	cpl_table_unselect_all(combtab);
	cpl_table_unselect_all(centraltab);
	combrow = cpl_table_get_nrow(combtab);
	sprintf(centraltile, "%s", cpl_table_get_string(centraltab, "TILE", 0));

	// extract all central tile elements from combined catalog

	for(i = 0; i < combrow; i++) {
		sprintf(tile, "%s", cpl_table_get_string(combtab, "TILE", i));
		if(strcmp(centraltile, tile) == 0) {
			cpl_table_select_row(combtab, i);
		}
	}

	// erase rows from original central catalog

	nrow = cpl_table_get_nrow(centraltab);

	for(i = 0; i < nrow; i++) {
		cpl_table_select_row(centraltab, i);
	}
	cpl_table_erase_selected(centraltab);

	// replace with new cleaned catalog

	cleancentraltab = cpl_table_extract_selected(combtab);
	cpl_table_insert(centraltab, cleancentraltab, 0);

	// do the same for neighbortab

	cpl_table_unselect_all(combtab);

	sprintf(neighbortile, "%s", cpl_table_get_string(neighbortab, "TILE", 0));

	for(i = 0; i < combrow; i++) {
		sprintf(tile, "%s", cpl_table_get_string(combtab, "TILE", i));
		if(strcmp(neighbortile, tile) == 0) {
			cpl_table_select_row(combtab, i);
		}
	}

	// erase rows from original central catalog

	nrow = cpl_table_get_nrow(neighbortab);

	for(i = 0; i < nrow; i++) {
		cpl_table_select_row(neighbortab, i);
	}
	cpl_table_erase_selected(neighbortab);

	cleanneighbortab = cpl_table_extract_selected(combtab);
	cpl_table_insert(neighbortab, cleanneighbortab, 0);

	cpl_table_unselect_all(combtab);

	cpl_table_delete(cleancentraltab);
	cpl_table_delete(cleanneighbortab);

	return CPL_ERROR_NONE;
}



cpl_matrix *identify_neighbortiles(cpl_array *imagearray) {

	int i, j, a, no, nimage, xnaxis1c, ynaxis2c, xnaxis1n, ynaxis2n,
		xmidc, ymidc, xmidn, ymidn;
	double angdist, rac, decc, ran, decn;
	cpl_matrix *neighbormatrix;
	char imagefile[FILENAME_MAX];
	cpl_array *status, *statusn;
	cpl_table *disttab;
	cpl_matrix *wcsmatrix, *pixmatrix;
	cpl_propertylist *centralheader, *neighborheader, *sortlist;
	cpl_wcs *wcs, *wcsneighbor;

	// get number of tiles

	nimage = (int)cpl_array_get_size(imagearray);

	// initialize matrix

	neighbormatrix = cpl_matrix_new(nimage, nimage);

	// loop over every tile

	for(i = 0; i < nimage; i++) {

		// reset table position counting variable

		a = 0;

		// set central image intern number in first matrix column

		cpl_matrix_set(neighbormatrix, i, 0, i + 1);

		// prepare central image path

		sprintf(imagefile, "%s", cpl_array_get_string(imagearray, i));

		// read fits header

		centralheader = cpl_propertylist_load(imagefile, 0);
		if (centralheader == NULL) {

			// image not found

			cpl_propertylist_delete(centralheader);
			cpl_msg_error(cpl_func, "Header file not found!");
		}

		// create wcs structure from image header

		wcs = cpl_wcs_new_from_propertylist(centralheader);
		if (wcs == NULL) {
			printf("Unable to parse header\n");
		}
		if (cpl_error_get_code() == CPL_ERROR_NO_WCS) {
			cpl_msg_warning(cpl_func, "WCSLIB not found - skip cpl_wcs tests") ;
		}

		// get central pixel position - transform in world coordinates

		xnaxis1c = cpl_propertylist_get_int(centralheader, "NAXIS1");
		ynaxis2c = cpl_propertylist_get_int(centralheader, "NAXIS2");

		if(xnaxis1c <= 0 || ynaxis2c <= 0) {
			cpl_msg_error(cpl_func, "Image header not readable - "
					"unspecified problem with image header.");
		}

		xmidc = round(xnaxis1c/2);
		ymidc = round(ynaxis2c/2);

		pixmatrix = cpl_matrix_new(1, 2);

		cpl_matrix_set(pixmatrix, 0, 0, xmidc);
		cpl_matrix_set(pixmatrix, 0, 1, ymidc);

		cpl_wcs_convert(wcs, pixmatrix, &wcsmatrix, &status,
				CPL_WCS_PHYS2WORLD);

		rac = cpl_matrix_get(wcsmatrix, 0, 0);
		decc = cpl_matrix_get(wcsmatrix, 0, 1);

		// clean up

		cpl_array_delete(status);
		cpl_matrix_delete(pixmatrix);
		cpl_matrix_delete(wcsmatrix);
		cpl_propertylist_delete(centralheader);
		cpl_wcs_delete(wcs);

		// prepare table containing distances to each neighbor image

		disttab = cpl_table_new(nimage - 1);
		cpl_table_new_column(disttab, "IMAGE", CPL_TYPE_STRING);
		cpl_table_new_column(disttab, "IMAGE No", CPL_TYPE_INT);
		cpl_table_new_column(disttab, "DISTANCE", CPL_TYPE_DOUBLE);

		// loop over other tiles to identify neighbors

		for(j = 0; j < nimage; j++) {

			if(i != j) {

				// read fits header

				sprintf(imagefile, "%s", cpl_array_get_string(imagearray, j));

				neighborheader = cpl_propertylist_load(imagefile, 0);

				if (neighborheader == NULL) {

					// image not found

					cpl_propertylist_delete(neighborheader);
					cpl_msg_error(cpl_func, "Header file not found!");
				}

				// create wcs structure from image header

				wcsneighbor = cpl_wcs_new_from_propertylist(neighborheader);
				if (wcsneighbor == NULL) {
					printf("Unable to parse header\n");
				}
				if (cpl_error_get_code() == CPL_ERROR_NO_WCS) {
					cpl_msg_warning(cpl_func,
							"WCSLIB not found - skip cpl_wcs tests") ;
				}

				// get central pixel position - transform in world coordinates

				xnaxis1n = cpl_propertylist_get_int(neighborheader, "NAXIS1");
				ynaxis2n = cpl_propertylist_get_int(neighborheader, "NAXIS2");

				if(xnaxis1n <= 0 || ynaxis2n <= 0) {
					cpl_msg_error(cpl_func, "Image header not readable - "
							"unspecified problem with image header.");
				}

				xmidn = round(xnaxis1n/2);
				ymidn = round(ynaxis2n/2);

				pixmatrix = cpl_matrix_new(1, 2);

				cpl_matrix_set(pixmatrix, 0, 0, xmidn);
				cpl_matrix_set(pixmatrix, 0, 1, ymidn);

				cpl_wcs_convert(wcsneighbor, pixmatrix, &wcsmatrix, &statusn,
						CPL_WCS_PHYS2WORLD);

				ran = cpl_matrix_get(wcsmatrix, 0, 0);
				decn = cpl_matrix_get(wcsmatrix, 0, 1);

				//xxx bogenmaß und gradmaß - passt das mit den 3600?
				angdist = 3600 * acos(sin(decc) * sin(decn) +
						cos(decc) * cos(decn) * cos(ran - rac));

				// write results for each central tile in a table

				cpl_table_set_string(disttab, "IMAGE", a, imagefile);
				cpl_table_set(disttab, "IMAGE No", a, j + 1);
				cpl_table_set(disttab, "DISTANCE", a, angdist);

				a++;

				cpl_array_delete(statusn);
				cpl_matrix_delete(pixmatrix);
				cpl_matrix_delete(wcsmatrix);
				cpl_propertylist_delete(neighborheader);
				cpl_wcs_delete(wcsneighbor);
			}
		}

		// sort result table according to distance

		sortlist = cpl_propertylist_new();
		cpl_propertylist_append_bool(sortlist, "DISTANCE", CPL_FALSE);
		cpl_table_sort(disttab, sortlist);
		cpl_propertylist_delete(sortlist);


		// write image numbers in distance matrix with
		// increasing distance

		for(j = 0; j < nimage - 1; j++) {
			no = cpl_table_get_int(disttab, "IMAGE No", j, NULL);
			cpl_matrix_set(neighbormatrix, i, j + 1, no);
		}

		cpl_table_delete(disttab);
	}

	return neighbormatrix;
}


// Complete a table with GALFIT output parameters

cpl_error_code gala_complete_table(cpl_table *tab, const int *i,
		const char *galfitfile) {

	unsigned line;
	int xlo, ylo;
	double xcgalfit, ycgalfit, maggalfit, regalfit, ngalfit, argalfit,
		pagalfit, elgalfit;
	char xp[FILENAME_MAX];
	char yp[FILENAME_MAX];
	char mag[FILENAME_MAX];
	char re[FILENAME_MAX];
	char n[FILENAME_MAX];
	char ar[FILENAME_MAX];
	char pa[FILENAME_MAX];
	char errormsg[FILENAME_MAX];
	char errorwhere[FILENAME_MAX];
	char errorfunc[FILENAME_MAX];
	cpl_propertylist *header;
	cpl_errorstate error, errornone = CPL_ERROR_NONE;


	// Check previous errorstate

	error = cpl_errorstate_get();

	if(error != CPL_ERROR_NONE) {

		printf("\n\n\n -------- ERRORSTATES in gala_complete_table() "
				"BEGINNING ---------\n\n");

		sprintf(errormsg, "%s", cpl_error_get_message());
		line = cpl_error_get_line();

		printf("ERRORMESSAGE : %s\n", errormsg);
		printf("LINE : %d\n", line);

		sprintf(errorwhere, "%s", cpl_error_get_where());
		printf("ERRORwhere : %s\n", errorwhere);

		sprintf(errorfunc, "%s", cpl_error_get_function());
		printf("ERRORfunc : %s\n", errorfunc);

		// Delete previous errorstates to see if new errors
		// occur in this function

		cpl_msg_error(cpl_func, "Error already before "
				"update_fittinglist(). IS DELETED NOW!");

		cpl_errorstate_set(errornone);
	}



	xlo = cpl_table_get_int(tab, "STAMP_XLO", *i, NULL);
	ylo = cpl_table_get_int(tab, "STAMP_YLO", *i, NULL);

	// get results from output GALFIT image block header file

	header = cpl_propertylist_load(galfitfile, 2);

	if(header == NULL) {
		cpl_msg_error(cpl_func, "In gala_complete_table() : "
				"Header not found !!!");
	}

	sprintf(xp, "%s", cpl_propertylist_get_string(header, "2_XC"));
	xcgalfit = xlo + atof(xp) - 1;
	cpl_table_set_double(tab, "X_GALFIT", *i, xcgalfit);

	sprintf(yp, "%s", cpl_propertylist_get_string(header, "2_YC"));
	ycgalfit = ylo + atof(yp) - 1;
	cpl_table_set_double(tab, "Y_GALFIT", *i, ycgalfit);

	sprintf(mag, "%s", cpl_propertylist_get_string(header, "2_MAG"));
	maggalfit = atof(mag);
	cpl_table_set_double(tab, "MAG_GALFIT", *i, maggalfit);

	sprintf(re, "%s", cpl_propertylist_get_string(header, "2_RE"));
	regalfit = atof(re);
	cpl_table_set_double(tab, "RE_GALFIT", *i, regalfit);

	sprintf(n, "%s", cpl_propertylist_get_string(header, "2_N"));
	ngalfit = atof(n);
	cpl_table_set_double(tab, "SERSIC_GALFIT", *i, ngalfit);

	sprintf(ar, "%s", cpl_propertylist_get_string(header, "2_AR"));
	argalfit = atof(ar);
	cpl_table_set_double(tab, "AR_GALFIT", *i, argalfit);
	elgalfit = 1 - argalfit;
	cpl_table_set_double(tab, "ELLIPTICITY_GALFIT", *i, elgalfit);

	sprintf(pa, "%s", cpl_propertylist_get_string(header, "2_PA"));
	pagalfit = atof(pa);
	cpl_table_set_double(tab, "PA_GALFIT", *i, pagalfit);

	// Flag every row which has been treated by GALFIT now as "Fit done"
	// with index 1
	// This is necessary for preparing the GALFIT setup file with
	// secondaries which have an existing fit or not

	cpl_table_set_int(tab, "FIT_DONE", *i, 1);

	cpl_propertylist_delete(header);

	error = cpl_errorstate_get();

	if(error != CPL_ERROR_NONE) {

		printf("\n\n\n -------- ERRORSTATES in gala_complete_table() "
				"END ---------\n\n");

		sprintf(errormsg, "%s", cpl_error_get_message());
		line = cpl_error_get_line();

		printf("ERRORMESSAGE : %s\n", errormsg);
		printf("LINE : %d\n", line);

		sprintf(errorwhere, "%s", cpl_error_get_where());
		printf("ERRORwhere : %s\n", errorwhere);

		sprintf(errorfunc, "%s", cpl_error_get_function());
		printf("ERRORfunc : %s\n", errorfunc);

		// Delete previous errorstates to see if new errors
		// occur in this function

		cpl_msg_error(cpl_func, "Error IN "
				"gala_complete_table(). IS DELETED NOW!");

		cpl_errorstate_set(errornone);
	}

	return CPL_ERROR_NONE;
}


// Creating a constraint file for the element number i in a table
// including secondary objects

cpl_error_code create_constraintfile_NEW(const char *constraintfile,
		const double *re_max, const double *mag_min, const double *mag_max,
		cpl_table *tab, const long *i) {

	int a = 0, lv, xstamp, ystamp, xstampsec, ystampsec, component,
		row, nsec = 0, secsize, k, ctsize, debug = 0, one = 1;
	long secidx = 0, ctidx, e;
	FILE *fp;
	const cpl_array *help;
	cpl_array *secindices,
			  *ctindices,
			  *secondary;


	// Check input

	row = cpl_table_get_nrow(tab);

	if(row <= 0) {
		cpl_msg_error(cpl_func, "In create_constraintfile() : "
				"Tab is empty or not accessable!!! Aborting...");
	}

	// get stamp sizes

	xstamp = cpl_table_get_int(tab, "STAMP_XHI", *i, NULL) -
			cpl_table_get_int(tab, "STAMP_XLO", *i, NULL);
	ystamp = cpl_table_get_int(tab, "STAMP_YHI", *i, NULL) -
			cpl_table_get_int(tab, "STAMP_YLO", *i, NULL);

	// Check number of secondaries

	help = cpl_table_get_array(tab, "SECONDARY_INDICES", *i);

	secindices = cpl_array_duplicate(help);

	secsize = (int)cpl_array_get_size(secindices);

	for(k = 0; k < secsize; k++) {
		secidx = (long)cpl_array_get(secindices, k, NULL);
		if(secidx >= 0) {
			nsec++;
		}
	}

	help = cpl_table_get_array(tab, "POT_CT_INDICES", *i);

	ctindices = cpl_array_duplicate(help);

	ctsize = (int)cpl_array_get_size(ctindices);

	for(k = 0; k < ctsize; k++) {
		ctidx = (long)cpl_array_get(ctindices, k, NULL);
		if(ctidx >= 0) {
			nsec++;
		}
	}

	// New array for all secondaries incl contrib targets

	secondary = cpl_array_new(nsec, CPL_TYPE_INT);

	for(k = 0; k < secsize; k++) {
		secidx = (long)cpl_array_get(secindices, k, NULL);
		if(secidx >= 0) {
			cpl_array_set(secondary, a, secidx);
			a++;
		}
	}

	for(k = 0; k < ctsize; k++) {
		ctidx = (long)cpl_array_get(ctindices, k, NULL);
		if(secidx >= 0) {
			cpl_array_set(secondary, a, ctidx);
			a++;
		}
	}

	// write constraint file

	fp = fopen(constraintfile, "w");

	fprintf(fp, "# Component/    parameter   constraint  Comment\n# operation"
			"                  values\n");
	fprintf(fp, "           2 n 0.2 to 20\n           2 re 0.3 to %.3f\n"
			"           2 q 0.0001  to 1.\n           2 mag %.3f %.3f\n"
			"           2 mag 0 to 40\n           2 pa -360 to 360\n           "
			"2 x         -%d          %d\n           2 y         -%d          "
			"%d\n", *re_max, *mag_min, *mag_max, one, xstamp, one, ystamp);

	// attach constraints for secondaries

	for(lv = 0; lv < nsec; lv++) {
		component = 3 + lv;
		e = cpl_array_get(secondary, lv, NULL) - 1;

		if(e >= 0) {

			xstampsec = cpl_table_get_int(tab, "STAMP_XHI", e, NULL) -
					cpl_table_get_int(tab, "STAMP_XLO", e, NULL);
			ystampsec = cpl_table_get_int(tab, "STAMP_YHI", e, NULL) -
					cpl_table_get_int(tab, "STAMP_YLO", e, NULL);
			fprintf(fp, "           %d n 0.2 to 8\n"
					"           %d re 0.3 to %.3f\n"
					"           %d q 0.0001  to 1.\n"
					"           %d mag %.3f %.3f\n"
					"           %d mag 0 to 40\n"
					"           %d pa -360 to 360\n"
					"           %d x         -%d          %d\n"
					"           %d y         -%d          %d\n",
					component, component, *re_max, component, component,
					*mag_min, *mag_max, component, component, component,
					100*xstampsec, 100*xstampsec, component, 100*ystampsec,
					100*ystampsec);
		} else {
			if(debug == 1) {
				cpl_msg_error(cpl_func, "Internal error in "
					"create_constraintfile(). Constraints for secondary "
					"not written correctly.");
			}
		}
	}

	fclose(fp);

	cpl_array_delete(secondary);
	cpl_array_delete(secindices);
	cpl_array_delete(ctindices);

	return CPL_ERROR_NONE;
}


// Create a fitting list for every tile
// List containing information about fitting parameters for GALFIT

cpl_error_code create_fittinglist_NEW(struct fitlist *object, cpl_table *tab) {

	int a, i, j, k, nrow, nsec, count, secsize, ctsize;
	long secidx, ctidx, idx;
	double primmag, secmag, magdiff;
	const cpl_array *help = NULL;
	cpl_array *secindices = NULL,
			  *ctindices = NULL,
			  *secondary = NULL;

	// Check input

	nrow = cpl_table_get_nrow(tab);

	if(nrow <= 0) {
		cpl_msg_error(cpl_func, "In create_fittinglist(): Table is "
				"empty or not accessable. Aborting...");
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	for(i = 0; i < nrow; i++) {

		// Reset counting variable for brighter secondaries

		count = 0;
		nsec = 0;
		a = 0;

		// Check number of secondaries

		help = cpl_table_get_array(tab, "SECONDARY_INDICES", i);

		secindices = cpl_array_duplicate(help);

		secsize = cpl_array_get_size(secindices);

		for(k = 0; k < secsize; k++) {
			secidx = (long)cpl_array_get(secindices, k, NULL);
			if(secidx >= 0) {
				nsec++;
			}
		}

		help = cpl_table_get_array(tab, "POT_CT_INDICES", i);

		ctindices = cpl_array_duplicate(help);

		ctsize = (int)cpl_array_get_size(ctindices);

		for(k = 0; k < ctsize; k++) {
			ctidx = (long)cpl_array_get(ctindices, k, NULL);
			if(ctidx >= 0) {
				nsec++;
			}
		}

		// New array for all secondaries incl contrib targets

		secondary = cpl_array_new(nsec, CPL_TYPE_INT);

		for(k = 0; k < secsize; k++) {
			secidx = (long)cpl_array_get(secindices, k, NULL);
			if(secidx >= 0) {
				cpl_array_set(secondary, a, secidx);
				a++;
			}
		}

		for(k = 0; k < ctsize; k++) {
			ctidx = (long)cpl_array_get(ctindices, k, NULL);
			if(ctidx >= 0) {
				cpl_array_set(secondary, a, ctidx);
				a++;
			}
		}

		// If no secondaries are present fitting is allowed (0)

		if(a == 0) {
			object[i].dofit = 0;
			object[i].n = 0;
		} else {
			object[i].n = a;

			// Get primary magnitude to check if fitting is allowed

			primmag = cpl_table_get_double(tab, "MAG_BEST", i, NULL);

			// Compare magnitudes and write down secondary SExtractor numbers

			for(j = 0; j < a; j++) {

				idx = (long)cpl_array_get(secondary, j, NULL);
				if(idx <= 0) {
					cpl_msg_error(cpl_func, "Internal error in "
							"create_fittinglist(). Object index has an "
							"error value.");
				} else {
					secmag = cpl_table_get_double(tab, "MAG_BEST",
							idx - 1, NULL);

					// If secondary is brighter fitting is permitted

					magdiff = primmag - secmag;

					if((magdiff > 0) && (object[i].dofit == 0)) {
						object[i].dofit = 1;
					}

					if(magdiff > 0) {
						object[i]. brightsecs[count] = idx;
						count++;
					}
					object[i].secondaries[j] = idx;
				}
			}
		}

		cpl_array_delete(secindices);
		cpl_array_delete(secondary);
		cpl_array_delete(ctindices);
	}

	return CPL_ERROR_NONE;

}


// Actualizing fittinglist after every object

cpl_error_code update_fittinglist_NEW(struct fitlist *obj, cpl_array *done,
		const long *nrow) {

	int debug = 1,
		j;
	long i, doneo = 0, freeo = 0, restricted = 0, brightsecnum;
	double frac;


	// xxx MAYBE TO DEBUG!!

//	printf("In update_fittinglist: Object %ld is done now!\n", *num);

	// Count the done and restricted objects

	for(i = 0; i < *nrow; i++) {
		if(obj[i].dofit == -1) {
			doneo++;
		}
		if(obj[i].dofit == 1) {
			restricted++;
		}
		if(obj[i].dofit == 0) {
			freeo++;
		}
	}

	printf("MASTER : Objects done : %ld\n", doneo);
	printf("MASTER : Objects restricted : %ld\n", restricted);
	printf("MASTER : Objects free : %ld\n", freeo);

	// Give rerstricted objects free at the end of the fitting procedure
	// when more than 99% are done and still too much restricted objects
	// are left because of GALFIT crashes

	frac = (double)freeo / *nrow;

	if(debug == 1) {
		printf("Der Anteil der freien Objekte ist : %f\n", frac);
	}

	if(frac < 0.05) {
		for(i = 0; i < *nrow; i++) {
			if(obj[i].dofit == 1) {
				obj[i].dofit = 0;
			}
		}
		return CPL_ERROR_NONE;
	}

	// Loop over blocked objects to see if fit for brighter
	// secondaries is existing

	for(i = 0; i < *nrow; i++) {
		if(obj[i].dofit == 1) {

			// Look at their brighter secondaries

			for(j = 0; j < 10; j++) {

				// xxx neue version - schauen obs passt.

				brightsecnum = obj[i].brightsecs[j] - 1;

				// xxx schauen ob das was falsch macht

				if(brightsecnum == -1) {
					obj[i].dofit = 0;
					break;
				}

				if(cpl_array_get_int(done, brightsecnum, NULL) != 1) {

					obj[i].dofit = 1;

					break;

				} else {

					obj[i].dofit = 0;
				}
			}
		}
	}

	return CPL_ERROR_NONE;
}



// Find table index according to SExtractor catalog number

int find_tabindex(cpl_table *tab, const int *number) {

	int i = 0, nrow = 0, index = 0, sexnum = 0;

	nrow = cpl_table_get_nrow(tab);

	for(i = 0; i < nrow; i++) {
		sexnum = cpl_table_get_int(tab, "NUMBER", i, NULL);
		if(sexnum == *number) {
			index = i;
			break;
		}
	}

	return index;
}

// Add data from a new GALFIT imgblock to a table

cpl_error_code update_table_NEW(cpl_table *tab, const char *galfitprefix) {

	int count, i, nrow;
	double xcgalfit, xcerrgalfit, ycgalfit, ycerrgalfit, maggalfit, magerrgalfit,
		regalfit, reerrgalfit, ngalfit, nerrgalfit, argalfit = 0, arerrgalfit = 0,
		elgalfit, pagalfit, paerrgalfit, chisq, chired, erval = 99999.;
	char imgblock[FILENAME_MAX];
	char directory[FILENAME_MAX];
	char xp[FILENAME_MAX];
	char yp[FILENAME_MAX];
	char mag[FILENAME_MAX];
	char re[FILENAME_MAX];
	char n[FILENAME_MAX];
	char ar[FILENAME_MAX];
	char pa[FILENAME_MAX];
	char *ptr;
	cpl_propertylist *header;
	cpl_errorstate error, errornone = CPL_ERROR_NONE;

	unsigned line;
	char errormsg[FILENAME_MAX];
	char errorwhere[FILENAME_MAX];
	char errorfunc[FILENAME_MAX];


	// Clear errorstate to see if error arised in current function

	error = cpl_errorstate_get();

	if(error != CPL_ERROR_NONE) {

		cpl_msg_error(cpl_func, "Errorstate already existed before "
				"run_GALFIT_parallel() !!!!");

		cpl_errorstate_set(errornone);
	}

	// Starting info

	cpl_msg_info(cpl_func, "Filling conbined table with "
			"fit results...");

	// Check if table is valid

	nrow = cpl_table_get_nrow(tab);

	if(nrow < 0) {
		cpl_msg_error(cpl_func, "Update_table(): "
				"Error with input table!");
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	// Check if neccessary columns exist

	if(cpl_table_has_column(tab, "FLAGS_GALFIT") == 0) {
		cpl_table_new_column(tab, "FLAGS_GALFIT", CPL_TYPE_STRING);
	}

	if(cpl_table_has_column(tab, "CHISQ_GALFIT") == 0) {
		cpl_table_new_column(tab, "CHISQ_GALFIT", CPL_TYPE_DOUBLE);
	}

	if(cpl_table_has_column(tab, "CHI2NU_GALFIT") == 0) {
		cpl_table_new_column(tab, "CHI2NU_GALFIT", CPL_TYPE_DOUBLE);
	}

	// Start update procedure

	for(i = 0; i < nrow; i++) {

		// Check at first if error occured

		error = cpl_errorstate_get();

		if(error != CPL_ERROR_NONE) {
			cpl_msg_error(cpl_func, "Error occured in update_table()!!!");
			printf("Error occured in update_table()!!!\n");

			sprintf(errormsg, "%s", cpl_error_get_message());
			line = cpl_error_get_line();

			printf("ERRORMESSAGE : %s\n", errormsg);
			printf("LINE : %d\n", line);

			sprintf(errorwhere, "%s", cpl_error_get_where());
			printf("ERRORwhere : %s\n", errorwhere);

			sprintf(errorfunc, "%s", cpl_error_get_function());
			printf("ERRORfunc : %s\n", errorfunc);
		}

		sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", i));
		sprintf(imgblock, "%s%s%s%d%s", directory, "/", galfitprefix, i + 1, ".fits");

		if(access(imgblock, 00) == 0) {

			// get results from output GALFIT image block header file

			header = cpl_propertylist_load(imgblock, 2);

			sprintf(xp, "%s", cpl_propertylist_get_string(header, "2_XC"));
			remove_chr(xp);
			ptr = strtok(xp, " ");
			while(ptr != NULL) {
				if(count == 0) {
					xcgalfit = atof(ptr);
					cpl_table_set_double(tab, "X_GALFIT", i, xcgalfit);
				}
				if(count == 2) {
					if(strncmp(ptr, "nan", 3) == 0 || strncmp(ptr, "*", 1) == 0) {
						cpl_table_set_double(tab, "XERR_GALFIT", i, erval);
					} else {
						xcerrgalfit = atof(ptr);
						cpl_table_set_double(tab, "XERR_GALFIT", i, xcerrgalfit);
					}
				}
				ptr = strtok(NULL, " ");
				count ++;
			}
			count = 0;

			sprintf(yp, "%s", cpl_propertylist_get_string(header, "2_YC"));
			remove_chr(yp);
			ptr = strtok(yp, " ");
			while(ptr != NULL) {
				if(count == 0) {
					ycgalfit = atof(ptr);
					cpl_table_set_double(tab, "Y_GALFIT", i, ycgalfit);
				}
				if(count == 2) {
					if(strncmp(ptr, "nan", 3) == 0  || strncmp(ptr, "*", 1) == 0) {
						cpl_table_set_double(tab, "YERR_GALFIT", i, erval);
					} else {
						ycerrgalfit = atof(ptr);
						cpl_table_set_double(tab, "YERR_GALFIT", i, ycerrgalfit);
					}
				}
				ptr = strtok(NULL, " ");
				count ++;
			}
			count = 0;

			sprintf(mag, "%s", cpl_propertylist_get_string(header, "2_MAG"));
			remove_chr(mag);
			ptr = strtok(mag, " ");
			while(ptr != NULL) {
				if(count == 0) {
					maggalfit = atof(ptr);
					cpl_table_set_double(tab, "MAG_GALFIT", i, maggalfit);
				}
				if(count == 2) {
					if(strncmp(ptr, "nan", 3) == 0 || strncmp(ptr, "*", 1) == 0) {
						cpl_table_set_double(tab, "MAGERR_GALFIT", i, erval);
					} else {
						magerrgalfit = atof(ptr);
						cpl_table_set_double(tab, "MAGERR_GALFIT", i, magerrgalfit);
					}
				}
				ptr = strtok(NULL, " ");
				count ++;
			}
			count = 0;

			sprintf(re, "%s", cpl_propertylist_get_string(header, "2_RE"));
			remove_chr(re);
			ptr = strtok(re, " ");
			while(ptr != NULL) {
				if(count == 0) {
					regalfit = atof(ptr);
					cpl_table_set_double(tab, "RE_GALFIT", i, regalfit);
				}
				if(count == 2) {
					if(strncmp(ptr, "nan", 3) == 0 || strncmp(ptr, "*", 1) == 0) {
						cpl_table_set_double(tab, "REERR_GALFIT", i, erval);
					} else {
						reerrgalfit = atof(ptr);
						cpl_table_set_double(tab, "REERR_GALFIT", i, reerrgalfit);
					}
				}
				ptr = strtok(NULL, " ");
				count ++;
			}
			count = 0;

			sprintf(n, "%s", cpl_propertylist_get_string(header, "2_N"));
			remove_chr(n);
			ptr = strtok(n, " ");
			while(ptr != NULL) {
				if(count == 0) {
					ngalfit = atof(ptr);
					cpl_table_set_double(tab, "SERSIC_GALFIT", i, ngalfit);
				}
				if(count == 2) {
					if(strncmp(ptr, "nan", 3) == 0 || strncmp(ptr, "*", 1) == 0) {
						cpl_table_set_double(tab, "SERSICERR_GALFIT", i, erval);
					} else {
						nerrgalfit = atof(ptr);
						cpl_table_set_double(tab, "SERSICERR_GALFIT", i, nerrgalfit);
					}
				}
				ptr = strtok(NULL, " ");
				count ++;
			}
			count = 0;

			sprintf(ar, "%s", cpl_propertylist_get_string(header, "2_AR"));
			remove_chr(ar);
			ptr = strtok(ar, " ");
			while(ptr != NULL) {
				if(count == 0) {
					argalfit = atof(ptr);
					cpl_table_set_double(tab, "AR_GALFIT", i, argalfit);
				}
				if(count == 2) {
					if(strncmp(ptr, "nan", 3) == 0 || strncmp(ptr, "*", 1) == 0) {
						cpl_table_set_double(tab, "ARERR_GALFIT", i, erval);
					} else {
						arerrgalfit = atof(ptr);
						cpl_table_set_double(tab, "ARERR_GALFIT", i, arerrgalfit);
					}
				}
				ptr = strtok(NULL, " ");
				count ++;
			}
			count = 0;

			elgalfit = 1 - argalfit;
			cpl_table_set_double(tab, "ELLIPTICITY_GALFIT", i, elgalfit);
			cpl_table_set_double(tab, "ELLIPTICITYERR_GALFIT", i, arerrgalfit);

			sprintf(pa, "%s", cpl_propertylist_get_string(header, "2_PA"));
			remove_chr(pa);
			ptr = strtok(pa, " ");
			while(ptr != NULL) {
				if(count == 0) {
					pagalfit = atof(ptr);
					cpl_table_set_double(tab, "PA_GALFIT", i, pagalfit);
				}
				if(count == 2) {
					if(strncmp(ptr, "nan", 3) == 0 || strncmp(ptr, "*", 1) == 0) {
						cpl_table_set_double(tab, "PAERR_GALFIT", i, erval);
					} else {
						paerrgalfit = atof(ptr);
						cpl_table_set_double(tab, "PAERR_GALFIT", i, paerrgalfit);
					}
				}
				ptr = strtok(NULL, " ");
				count ++;
			}
			count = 0;

			chisq = cpl_propertylist_get_double(header, "CHISQ");
			cpl_table_set_double(tab, "CHISQ_GALFIT", i, chisq);

			chired = cpl_propertylist_get_double(header, "CHI2NU");
			cpl_table_set_double(tab, "CHI2NU_GALFIT", i, chired);

			// Flag every row which has been treated by GALFIT now as "Fit done"
			// with index 1
			// This is necessary for preparing the GALFIT setup file with
			// secondaries which have an existing fit or not

			cpl_table_set_int(tab, "FIT_DONE", i, 1);

			flag_table(tab, i, header);

			cpl_propertylist_delete(header);
		}
	}

	error = cpl_errorstate_get();

	if(error != CPL_ERROR_NONE) {

		printf("\n\n\n -------- ERRORSTATES AFTER update_table() ---------\n\n");
		cpl_msg_error(cpl_func, "UNCERTAIN ERROR STATE in update_table()\n");
		sprintf(errormsg, "%s", cpl_error_get_message());
		line = cpl_error_get_line();

		printf("ERRORMESSAGE : %s\n", errormsg);
		printf("LINE : %d\n", line);

		sprintf(errorwhere, "%s", cpl_error_get_where());
		printf("ERRORwhere : %s\n", errorwhere);

		sprintf(errorfunc, "%s", cpl_error_get_function());
		printf("ERRORfunc : %s\n", errorfunc);
	}

	return CPL_ERROR_NONE;
}


cpl_error_code flag_table(cpl_table *tab, int i, cpl_propertylist *header) {

	int galfitflag = 0;
	char flagstring[FILENAME_MAX];
	char *ptr;

	if(cpl_table_has_column(tab, "FLAGS_GALFIT") == 0) {
		cpl_table_new_column(tab, "FLAGS_GALFIT", CPL_TYPE_STRING);
	}

	if(cpl_propertylist_has(header, "FLAGS") != 1) {
		cpl_msg_info(cpl_func, "GALFIT FLAGS are not available!");
		cpl_table_set_string(tab, "FLAGS_GALFIT", i, "NONE");
		return CPL_ERROR_NONE;
	}

	sprintf(flagstring, "%s", cpl_propertylist_get_string(header, "FLAGS"));

	ptr = strtok(flagstring, " ");

	while(ptr != NULL) {

		if(strcmp(ptr, "1") == 0) {

			galfitflag = 1;

		}

		if(strcmp(ptr, "2") == 0) {

			galfitflag += 2;

		}

		ptr = strtok(NULL, " ");
	}

	if(galfitflag == 0) {

		cpl_table_set_string(tab, "FLAGS_GALFIT", i, "GOOD");

	}

	if(galfitflag == 1) {

		cpl_table_set_string(tab, "FLAGS_GALFIT", i, "1");

	}

	if(galfitflag == 2) {

		cpl_table_set_string(tab, "FLAGS_GALFIT", i, "2");

	}

	if(galfitflag == 3) {

		cpl_table_set_string(tab, "FLAGS_GALFIT", i, "3");

	}

	return CPL_ERROR_NONE;
}


/* Fit the data (x_i, y_i) to the linear relationship

   Y = c0 + c1 x

   returning,

   c0, c1  --  coefficients

   This fit can be used in the case where the errors for the data are
   uknown, but assumed equal for all points. The resulting
   variance-covariance matrix estimates the error in the coefficients
   from the observed variance of the points around the best fit line.
*/

cpl_error_code fit_linear (cpl_array *slopecalc,
                const int *n,
                double *c0, double *c1)
{
  double m_x = 0, m_y = 0, m_dx2 = 0, m_dxdy = 0;

  int i;

  for (i = 0; i < *n; i++)
    {
      m_x += (i - m_x) / (i + 1.0);
      m_y += (cpl_array_get_double(slopecalc, i, NULL) - m_y) / (i + 1.0);
    }

  for (i = 0; i < *n; i++)
    {
      const double dx = i - m_x;
      const double dy = cpl_array_get_double(slopecalc, i, NULL) - m_y;

      m_dx2 += (dx * dx - m_dx2) / (i + 1.0);
      m_dxdy += (dx * dy - m_dxdy) / (i + 1.0);
    }

  /* In terms of y = a + b x */

    double b = m_dxdy / m_dx2;
    double a = m_y - m_x * b;

    *c0 = a;
    *c1 = b;

  return CPL_ERROR_NONE;
}


double rel_pos_ang(const double *tgt_x, const double *tgt_y,
		const double *ctr_x, const double *ctr_y, const double *ctr_pa) {

	double alpha, dist;
	double pi = 3.14159265;

	dist = sqrt(pow((*tgt_x-*ctr_x), 2.)+ pow((*tgt_y-*ctr_y), 2.));
	alpha = asin(((*tgt_y-*ctr_y))/dist);
	if(*tgt_x < *ctr_x && *tgt_y < *ctr_y) {
		alpha = -alpha - pi;
	}
	if(*tgt_x < *ctr_x && *tgt_y >= *ctr_y) {
		alpha = pi - alpha;
	}
	alpha -= *ctr_pa;
	if(alpha > 2*pi) {
		alpha -= 2*pi;
	}

	return alpha;
}


double gamma(double x) {
// rough approximation of Gamma function

	static double pi;
	pi = 4 * atan(1);
	static double e;
	e = exp(1);
	int i;
	double sum = 0;
	static double c[5];
	c[0] = 1;
	c[1] = 1.0/12;
	c[2] = 1.0/288;
	c[3] = -139.0/51840;
	c[4] = -571.0/2488320;
	for(i=0;i<5;i++) sum += c[i]/pow(x, i);
	return sum *= pow(x,x-0.5) * pow(e,-x) * sqrt(2*pi);
}


double sersic_flux(const double *r, const double *phi, const double *q,
		const double *f0, const double *re, const double *n) {

	double a, f, _phi, _r, kap;

	a = pow(cos(*phi), 2.);
	_phi = pow(sin((*phi)), 2.) / pow(*q, 2.);
	_phi = sqrt(a +_phi);
	_r = *r*_phi;
	kap = 2* *n - 1/3;
	f = *f0*exp(-kap*(pow((_r/ *re), (1./ *n))-1.));

	return f;
}


//****************************************************************************
// Find potentially contrib(uting) targets.
//
// Not every source that has an impact on a current primary source might be
// detected within the process of secondary identification. Especially for a
// small object in the environment of a large elliptical galaxy with a flat
// light profile and a high Sersic index the situation becomes very probable.
//
// This function will check the light contribution to the current primary
// produced by foreign sources that have not been detected as secondary sources
// in a previous process by using their GALFIT imageblock profiles. If
// this light contribution is exceeding a user defined threshold "magcrit"
// and the source producing this contribution has not yet been detected as
// a secondary - i.e. is is not present in the secondary table of the current
// primary - its parameters will be added to a separate contrib target table.
//
// This contrib target table can be used for the further treatment of this
// sources and their impact.
//
// The user also has to define a maximum number of allowed contrib targets.
// If the routine might detect more than this allowed number of sources the
// contrib targets will be removed from the contrib target table according to
// their magnitude.
//
// INPUT: contribpath     Directory where the contrib targets have to be saved
//        tab             Table containg information about every object
//        secondarypath   Directory containg secondary tables
//        imgblock        Directory containg imageblocks and filename prefix
//        distmax         Radius for a surrounding area where contrib targets
//                        should be searched for (user parameter for setup file)
//        magcrit         Critical magnitude - cut below which objects are
//                        considered as contributing (user parameter)
//        contribmax      Maximum number of contrib sources (user parameter)
//
// OUTPUT: A directory containing tables with contrib targets for every object
//
// ERRORS: CPL_ERROR_DATA_NOT_FOUND  If input table is empty or not accessable
//                                   If directory with secondary tables is not
//                                   found
//         CPL_ERROR_NONE            No error occured
//****************************************************************************

cpl_error_code find_contribtargets_NEW(cpl_table *tab,
		const int *contribmax,    const double *distmax,
		const double *fluxextend, const double *zeropoint,
		const double *magcrit,    const double *magexclude,
		const double *platescale) {

	int k,
		secrow,
		count = 0,
		flag = 0,
		debug = 0;

	long i,
		 j,
		 z,
		 secidx;

	double p_x,
		   p_y,
		   p_m,
		   p_ra,
		   p_dec,
		   x,
		   y,
		   r,
		   ra2,
		   dec2,
		   angdist,
		   magbest,
		   n,
		   re,
		   q,
		   pa,
		   ftoto,
		   kap,
		   fo,
		   phi,
		   flux,
		   crit,
		   magdiff,
		   exptime,
		   pi = 3.14159265;

	char image[FILENAME_MAX],
		 itile[FILENAME_MAX],
		 jtile[FILENAME_MAX];

	cpl_array *contribindices,
			  *secindices;
	const cpl_array *help;

	cpl_propertylist *header;

	// Starting message

	cpl_msg_info(cpl_func, "Identifying contributing sources...");

	// Check input table

	z = (long)cpl_table_get_nrow(tab);

	if(z == 0) {
		cpl_msg_error (cpl_func, "Input table in find_secondaries() is empty!");
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	// Prepare a column for contrib target indices

	cpl_table_new_column_array(tab, "POT_CT_INDICES", CPL_TYPE_INT, *contribmax);

    // Check every object

	for(i = 0; i < z; i++) {


		printf("Checking contrib targets for object %ld\n", i);


		// Prepare an array containing contributing targets

		contribindices = cpl_array_new(*contribmax, CPL_TYPE_INT);

		// Initialise array with -1

		for(j = 0; j < *contribmax; j++) {
			cpl_array_set(contribindices, j, -1);
		}

		// Reset counting variable for contributing targets

		count = 0;

		// Get primary data

		p_x   = cpl_table_get_double(tab, "X_IMAGE", i, NULL);
		p_y   = cpl_table_get_double(tab, "Y_IMAGE", i, NULL);
		p_m   = cpl_table_get_double(tab, "MAG_BEST", i, NULL);
		p_ra  = cpl_table_get_double(tab, "ALPHA_J2000", i, NULL);
		p_ra  = (p_ra/360)*2*pi;
		p_dec = cpl_table_get_double(tab, "DELTA_J2000", i, NULL);
		p_dec = (p_dec/360)*2*pi;

		sprintf(itile, "%s", cpl_table_get_string(tab, "TILE", i));

		// Check ALL sources for flux contribution

		for(j = 0; j < z; j++) {

			// Reset flag variable for contributing targets
			// already identified as secondaries

			flag = 0;

			if(j != i) {

				// Get data from brighter sources

				x  = cpl_table_get_double(tab, "X_IMAGE", j, NULL);
				y  = cpl_table_get_double(tab, "Y_IMAGE", j, NULL);
				ra2  = cpl_table_get_double(tab, "ALPHA_J2000", j, NULL);
				ra2 = (ra2/360)*2*pi;
				dec2 = cpl_table_get_double(tab, "DELTA_J2000", j, NULL);
				dec2 = (dec2/360)*2*pi;

				sprintf(jtile, "%s", cpl_table_get_string(tab, "TILE", j));

				if(strcmp(itile, jtile) == 0) {

					// Calculate angular distance

					angdist = acos(sin(p_dec)*sin(dec2)+cos(p_dec)
							*cos(dec2)*cos(ra2-p_ra));
					angdist = (angdist*360*60*60)/(2*pi);

					// Take only objects into account with a defined distance

					if(angdist < *distmax) {

						magbest = cpl_table_get_double(tab, "MAG_BEST", j, NULL);

						// Use a high Sersic Index

						n = 4;
						re = cpl_table_get_double(tab, "FLUX_RADIUS", j, NULL);
						re = pow(re, *fluxextend);
						q = 1 - cpl_table_get_double(tab, "ELLIPTICITY", j, NULL);
						pa = cpl_table_get_double(tab, "THETA_IMAGE", j, NULL);

						// Load image header to get exposure time

						sprintf(image, "%s", cpl_table_get_string(tab, "IMAGE", j));

						header = cpl_propertylist_load(image, 0); // read fits header
						if (header == NULL) {
							// image header not found
							cpl_msg_error(cpl_func, "Header not found in "
									"find_contribtargets()!");
						}

						exptime = cpl_propertylist_get_double(header, "EXPTIME");

						if(exptime <= 0) {
							cpl_msg_error(cpl_func, "Exposure time is 0 or negative "
									"in find_contribtargets()!!! Image header "
								"probably not found!!!");
						}

						cpl_propertylist_delete(header);

						// Calculate magnitude influence

						ftoto = pow(10., (-0.4*(magbest-*zeropoint)))*exptime;
						kap = 2*n - 1/3;
						fo = ftoto/(2*pi*pow(re, 2.)*exp(kap)*n*
								pow(kap, (-2.*n))*gamma(2.*n)*q);

		//				printf("fo : %f\n", fo);

						phi = rel_pos_ang(&p_x, &p_y, &x, &y, &pa);

	//					printf("fo : %f\n", fo);
	//					printf("r : %f\n", r);
	//					printf("re : %f\n", re);
	//					printf("q : %f\n", q);
	//					printf("n : %f\n", n);
	//					printf("phi: %f\n", phi);

						// Flux contribution to the current primary

						r = angdist / *platescale;

						flux = sersic_flux(&r, &phi, &q, &fo, &re, &n);

	//					printf("flux : %f\n", flux);

						crit = -2.5*log10(flux);

						// Exclude magnitude downgraded tertiaries

						magdiff = magbest - p_m;

						if(crit < *magcrit && magdiff < *magexclude) {

							// Look if contributing source was already
							// marked as a secondary source

							// Look if object is already contained in secondaries

							help = cpl_table_get_array(tab, "SECONDARY_INDICES", i);

							secindices = cpl_array_duplicate(help);

							// Get number of secondaries

							secrow = (int)cpl_array_get_size(secindices);

							for(k = 0; k < secrow; k++) {

								secidx = (long)cpl_array_get_int(secindices, k, NULL);

								// If object not treated as secondary yet

								if(secidx == j + 1) {

									flag = 1;
									break;
								}
							}

							if(flag != 1) {

								// Contributing source found

								if(debug == 1) {
									printf("Contributing source found for object "
										"No %ld : CT No %ld\n", i + 1, j + 1);
								}

								// Mark fit as "undone" in table

								if(cpl_table_get_int(tab, "FIT_DONE", i, NULL) != 0) {
									cpl_table_set_int(tab, "FIT_DONE", i, 0);
								}

								// Set contrib target indices in array

								cpl_array_set(contribindices, count, j + 1);
								count++;
							}

							cpl_array_delete(secindices);
						}
					}
				}
			}
		}

		// Insert array into table column

		cpl_table_set_array(tab, "POT_CT_INDICES", i, contribindices);

		// Clean up

		cpl_array_delete(contribindices);
	}

	return CPL_ERROR_NONE;
}



//****************************************************************************
// Find potentially contrib(uting) targets.
//
// Not every source that has an impact on a current primary source might be
// detected within the process of secondary identification. Especially for a
// small object in the environment of a large elliptical galaxy with a flat
// light profile and a high Sersic index the situation becomes very probable.
//
// This function will check the light contribution to the current primary
// produced by foreign sources that have not been detected as secondary sources
// in a previous process by using their GALFIT imageblock profiles. If
// this light contribution is exceeding a user defined threshold "magcrit"
// and the source producing this contribution has not yet been detected as
// a secondary - i.e. is is not present in the secondary table of the current
// primary - its parameters will be added to a separate contrib target table.
//
// This contrib target table can be used for the further treatment of this
// sources and their impact.
//
// The user also has to define a maximum number of allowed contrib targets.
// If the routine might detect more than this allowed number of sources the
// contrib targets will be removed from the contrib target table according to
// their magnitude.
//
// INPUT: contribpath     Directory where the contrib targets have to be saved
//        tab             Table containg information about every object
//        secondarypath   Directory containg secondary tables
//        imgblock        Directory containg imageblocks and filename prefix
//        distmax         Radius for a surrounding area where contrib targets
//                        should be searched for (user parameter for setup file)
//        magcrit         Critical magnitude - cut below which objects are
//                        considered as contributing (user parameter)
//        contribmax      Maximum number of contrib sources (user parameter)
//
// OUTPUT: A directory containing tables with contrib targets for every object
//
// ERRORS: CPL_ERROR_DATA_NOT_FOUND  If input table is empty or not accessable
//                                   If directory with secondary tables is not
//                                   found
//         CPL_ERROR_NONE            No error occured
//****************************************************************************

cpl_error_code find_contribtargets_parallel(cpl_table *tab,
		const int *contribmax,    const double *distmax,
		const double *fluxextend, const double *zeropoint,
		const double *magcrit,    const double *magexclude,
		const double *platescale) {

	int rank,
		slaveid,
		numprocs,
		div,
		secrow,
		count = 0,
		flag = 0,
		debug = 0;

	long i = 0,
		 j = 0,
		 k = 0,
		 l = 0,
		 m = 0,
		 z,
		 secidx,
		 slaverank[3],
		 smsg[3];

	double p_x,
		   p_y,
		   p_m,
		   p_ra,
		   p_dec,
		   x,
		   y,
		   r,
		   ra2,
		   dec2,
		   angdist,
		   magbest,
		   n,
		   re,
		   q,
		   pa,
		   ftoto,
		   kap,
		   fo,
		   phi,
		   flux,
		   crit,
		   magdiff,
		   exptime,
		   pi = 3.14159265;

	char image[FILENAME_MAX],
		 itile[FILENAME_MAX],
		 jtile[FILENAME_MAX];

	cpl_array *contribindices,
			  *secindices;
	const cpl_array *help;

	cpl_propertylist *header;

	MPI_Status status;


	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	/* find out number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	/* Check input table */

	z = (long)cpl_table_get_nrow(tab);

	if(z == 0) {
		cpl_msg_error (cpl_func, "PROCESSOR %d: Input table in find_secondaries() is empty!",
				rank);
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	/* MASTER JOB */

	if(rank == 0) {

		/* Starting message */

		cpl_msg_info(cpl_func, "Identifying contributing sources...");

		/* Check if column exists */

		if(cpl_table_has_column(tab, "FIT_DONE") != 1) {
			cpl_table_new_column(tab, "FIT_DONE", CPL_TYPE_INT);
		}

		/* Prepare a column for contrib target indices */

		cpl_table_new_column_array(tab, "POT_CT_INDICES", CPL_TYPE_INT, *contribmax);

	    /* Check every object */

		for(i = 0; i < z; i++) {

			printf("Checking contrib targets for object %ld\n", i);

			/* Calculate salve rank */

			div = numprocs - 1;

			slaveid = (i%div)+1;

			/* Send message to slave */

			MPI_Send(&i, sizeof(long), MPI_LONG, slaveid, 1,
					MPI_COMM_WORLD);

			/* Receive rank and contrib target indices from slave */

    		MPI_Recv(&slaverank, 3*sizeof(long), MPI_LONG, MPI_ANY_SOURCE,
    								2, MPI_COMM_WORLD, &status);

    		/* Prepare an array containing contributing targets */

    		contribindices = cpl_array_new(*contribmax, CPL_TYPE_INT);

    		/* Initialise array with -1 */

    		for(j = 0; j < *contribmax; j++) {
    			cpl_array_set(contribindices, j, slaverank[j + 1]);
    		}

    		/* Insert array into table column */

    		cpl_table_set_array(tab, "POT_CT_INDICES", i, contribindices);

    		/* Clean up */

    		cpl_array_delete(contribindices);

			// Mark fit as "undone" in table

			if(cpl_table_get_int(tab, "FIT_DONE", k, NULL) != 0) {
				cpl_table_set_int(tab, "FIT_DONE", k, 0);
			}

		}

	/* SLAVE JOB */

	} else {

		/* Find out process rank */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		while(k < z) {

			/* Initialize parameters */

			smsg[0] = rank;
			smsg[1] = -1;
			smsg[2] = -1;

			/* Receive job ID for MASTER (JOB TAG = 1) */

			MPI_Recv(&k, sizeof(long), MPI_LONG, 0, 1, MPI_COMM_WORLD, &status);

			// Reset counting variable for contributing targets

			count = 0;

			// Get primary data

			p_x   = cpl_table_get_double(tab, "X_IMAGE", k, NULL);
			p_y   = cpl_table_get_double(tab, "Y_IMAGE", k, NULL);
			p_m   = cpl_table_get_double(tab, "MAG_BEST", k, NULL);
			p_ra  = cpl_table_get_double(tab, "ALPHA_J2000", k, NULL);
			p_ra  = (p_ra/360)*2*pi;
			p_dec = cpl_table_get_double(tab, "DELTA_J2000", k, NULL);
			p_dec = (p_dec/360)*2*pi;

			sprintf(itile, "%s", cpl_table_get_string(tab, "TILE", k));

			// Check ALL sources for flux contribution

			for(l = 0; l < z; l++) {

				if(count >= *contribmax) {
					break;
				}

				// Reset flag variable for contributing targets
				// already identified as secondaries

				flag = 0;

				if(l != k) {

					// Get data from brighter sources

					x  = cpl_table_get_double(tab, "X_IMAGE", l, NULL);
					y  = cpl_table_get_double(tab, "Y_IMAGE", l, NULL);
					ra2  = cpl_table_get_double(tab, "ALPHA_J2000", l, NULL);
					ra2 = (ra2/360)*2*pi;
					dec2 = cpl_table_get_double(tab, "DELTA_J2000", l, NULL);
					dec2 = (dec2/360)*2*pi;

					sprintf(jtile, "%s", cpl_table_get_string(tab, "TILE", l));

					if(strcmp(itile, jtile) == 0) {

						// Calculate angular distance

						angdist = acos(sin(p_dec)*sin(dec2)+cos(p_dec)
								*cos(dec2)*cos(ra2-p_ra));
						angdist = (angdist*360*60*60)/(2*pi);

						// Take only objects into account with a defined distance

						if(angdist < *distmax) {

							magbest = cpl_table_get_double(tab, "MAG_BEST", l, NULL);

							// Use a high Sersic Index

							n = 4;
							re = cpl_table_get_double(tab, "FLUX_RADIUS", l, NULL);
							re = pow(re, *fluxextend);
							q = 1 - cpl_table_get_double(tab, "ELLIPTICITY", l, NULL);
							pa = cpl_table_get_double(tab, "THETA_IMAGE", l, NULL);

							// Load image header to get exposure time

							sprintf(image, "%s", cpl_table_get_string(tab, "IMAGE", l));

							header = cpl_propertylist_load(image, 0); // read fits header
							if (header == NULL) {
								// image header not found
								cpl_msg_error(cpl_func, "Header not found in "
										"find_contribtargets()!");
							}

							exptime = cpl_propertylist_get_double(header, "EXPTIME");

							if(exptime <= 0) {
								cpl_msg_error(cpl_func, "Exposure time is 0 or negative "
									"in find_contribtargets()!!! Image header "
									"probably not found!!!");
							}

							cpl_propertylist_delete(header);

							// Calculate magnitude influence

							ftoto = pow(10., (-0.4*(magbest-*zeropoint)))*exptime;
							kap = 2*n - 1/3;
							fo = ftoto/(2*pi*pow(re, 2.)*exp(kap)*n*
									pow(kap, (-2.*n))*gamma(2.*n)*q);

				//			printf("fo : %f\n", fo);

							phi = rel_pos_ang(&p_x, &p_y, &x, &y, &pa);

			//				printf("fo : %f\n", fo);
			//				printf("r : %f\n", r);
			//				printf("re : %f\n", re);
			//				printf("q : %f\n", q);
			//				printf("n : %f\n", n);
			//				printf("phi: %f\n", phi);

							// Flux contribution to the current primary

							r = angdist / *platescale;

							flux = sersic_flux(&r, &phi, &q, &fo, &re, &n);

			//				printf("flux : %f\n", flux);

							crit = -2.5*log10(flux);

							// Exclude magnitude downgraded tertiaries

							magdiff = magbest - p_m;

							if(crit < *magcrit && magdiff < *magexclude) {

								// Look if contributing source was already
								// marked as a secondary source

								// Look if object is already contained in secondaries

								help = cpl_table_get_array(tab, "SECONDARY_INDICES", k);

								secindices = cpl_array_duplicate(help);

								// Get number of secondaries

								secrow = (int)cpl_array_get_size(secindices);

								for(m = 0; m < secrow; m++) {

									secidx = (long)cpl_array_get_int(secindices, m, NULL);

									// If object not treated as secondary yet

									if(secidx == l + 1) {

										flag = 1;
										break;
									}

									if(flag != 1) {

										// Contributing source found

										if(debug == 1) {
											printf("Contributing source found for object "
												"No %ld : CT No %ld\n", k + 1, l + 1);
										}

									// Set contrib target indices in array

									smsg[count + 1] = l + 1;

									count++;
									}
								}

								cpl_array_delete(secindices);
							}
						}
					}
				}
			}

			MPI_Send(&smsg, 3*sizeof(long), MPI_LONG, 0, 2, MPI_COMM_WORLD);
		}
	}

	return CPL_ERROR_NONE;
}



cpl_error_code check_errorstate(cpl_errorstate err_state) {

	unsigned line;
	int rank;
	char errormsg[FILENAME_MAX];
	char errorwhere[FILENAME_MAX];
	char errorfunc[FILENAME_MAX];

	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    err_state = cpl_errorstate_get();

    if(err_state != CPL_ERROR_NONE) {
    	cpl_msg_error(cpl_func, "Unspecified error in reading setup "
    			"procedure occured in thread No %d !!!\n", rank);

		sprintf(errormsg, "%s", cpl_error_get_message());
		line = cpl_error_get_line();

		printf("ERRORMESSAGE : %s\n", errormsg);
		printf("LINE : %d\n", line);

		sprintf(errorwhere, "%s", cpl_error_get_where());
		printf("ERRORwhere : %s\n", errorwhere);

		sprintf(errorfunc, "%s", cpl_error_get_function());
		printf("ERRORfunc : %s\n", errorfunc);

    	cpl_errorstate_set(CPL_ERROR_NONE);
    }

	return CPL_ERROR_NONE;
}


/*********************************************************************
 * Run bulge-disc fitting with more Sérsic components
 **********************************************************************/

cpl_error_code run_bulge_disc_fitting(cpl_parameterlist *gala_setup) {

	int numprocs = 0,
		rank = 0,
		debug = 1,
		synch = 0,
		slaverank,
		k,
		ncomponents;

	long j = 0,
		 nrow;

	double re_max,
		   mag_min,
		   mag_max;

	char tabfile[FILENAME_MAX],
		 outdir[FILENAME_MAX],
		 combcatname[FILENAME_MAX],
		 object[FILENAME_MAX],
		 imgblock_bd[FILENAME_MAX],
		 galfitset[FILENAME_MAX],
		 str[FILENAME_MAX],
		 directory[FILENAME_MAX],
		 constraints[FILENAME_MAX],
		 constraintfile_bd[FILENAME_MAX],
		 galsetfile[FILENAME_MAX],
		 path[FILENAME_MAX];

	cpl_table *tab;

	cpl_parameter *p;

	MPI_Status status;

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	/* find out number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	/* Load variables from setup parameterlist */

    p = cpl_parameterlist_find(gala_setup, "outdir");
    sprintf(outdir, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "sexcomb");
    sprintf(combcatname, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "object");
    sprintf(object, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "constraints");
    sprintf(constraints, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "path");
    sprintf(path, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "re_max");
    re_max = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "mag_min");
    mag_min = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "mag_max");
    mag_max = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "galfitset");
    sprintf(galfitset, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "ncomponents");
    ncomponents = (int)cpl_parameter_get_double(p);

    if(debug == 1) {
    	printf("NCOMPONENTS in run_bulge_disc_fitting: %d\n", ncomponents);
    }


    /* MASTER job */

    if(rank == 0) {

    	/* Prepare path variable for loading table */

    	sprintf(tabfile, "%s%s%s", outdir, "/", combcatname);

    	if(access(tabfile, 00) != 0) {
    		cpl_msg_error(cpl_func, "Tabfile %s is not accessable in "
    				"bulge_disc_fitting(). Aborting...", tabfile);
    		return CPL_ERROR_DATA_NOT_FOUND;
    	}

    	/* Load combined GALAPAGOS catalog */

    	tab = cpl_table_load(tabfile, 1, 0);

    	/* Check table */

    	nrow = (long)cpl_table_get_nrow(tab);

    	printf("MASTER : Habe table mit %ld rows geladen!\n", nrow);

    	if(nrow <= 0){
    		cpl_msg_error(cpl_func, "Table %s is empty or not accessable "
    				"in bulge_disc_fitting(). Aborting...", tabfile);
    		return CPL_ERROR_DATA_NOT_FOUND;
		}

    	if(check_table_bulge_disc(tab) != CPL_ERROR_NONE) {
    		cpl_msg_error(cpl_func, "An unspecified error occurred in "
    				"check_table_bulge_disc()!");
    	}

        /* Starting message */

    	cpl_msg_info(cpl_func, "Starting GALFIT bulge-disc fitting for "
    			"%ld objects.", nrow);

    	/* Prepare table for bulge-disc fitting */

    	if(prepare_table_bulge_disc(tab) != CPL_ERROR_NONE) {
    		cpl_msg_error(cpl_func, "An unspecified error occurred in "
    				"prepare_table_bulge_disc()!");
    	}

    	/* Save prepared table */

    	cpl_table_save(tab, NULL, NULL, tabfile, CPL_IO_CREATE);

    	/* Clean up */

    	cpl_table_delete(tab);

    	/* Send jobs to slaves */

    	for(j = 0; j < nrow; j++) {

    		/* Receive a message from slave who needs a job */

    		if(debug == 1) {
    			printf("MASTER im for - LOOP : Warte auf Nachrichten von "
    				"den Slaves !!!\n");
    		}

    		MPI_Recv(&slaverank, sizeof(int), MPI_INT, MPI_ANY_SOURCE,
    								51, MPI_COMM_WORLD, &status);

    		if(debug == 1) {
    			printf("MASTER im for - LOOP : Habe folgende Nachricht von "
    				"einem Slave erhalten : %d\n", slaverank);
    		}

			/* Send job to the slave */

			printf("\nMASTER : Bin in Loop Nummer %ld und sende "
				"job %ld an den Slave %d.\n\n\n", j, j, slaverank);


			MPI_Send(&j, sizeof(long), MPI_INT, slaverank, 52,
					MPI_COMM_WORLD);

    	}

    	/* Termination message */

    	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    	for(k = 1; k < numprocs; k++) {

    		j = -1;

			/* Send job to the slave */

			printf("\nMASTER : Send nun die ending message an den slave"
					"%d.\n\n\n", k);

    		MPI_Send(&j, sizeof(long), MPI_INT, k, 52, MPI_COMM_WORLD);
    	}

    /* Slave job */

    } else {

		/* Load table and check size*/

		sprintf(tabfile, "%s%s%s", outdir, "/", combcatname);

		if(access(tabfile, 00) == 0) {

			tab = cpl_table_load(tabfile, 1, 0);

			nrow = (long)cpl_table_get_nrow(tab);

			if(nrow <= 0) {
				cpl_msg_error(cpl_func, "Table loaded by slave %d in "
						"run_GALFIT_parallel() is not found or empty!",
						rank);

				printf("Der aktuelle Wert von j ist : %ld\n", j);

				return CPL_ERROR_DATA_NOT_FOUND;
			}

		} else {
			cpl_msg_error(cpl_func, "Table file not accessable by "
					"slave in run_GALFIT_parallel()!");

			return CPL_ERROR_DATA_NOT_FOUND;
		}

		/* Receive job as long as MASTER sends */

    	while (j != -1) {

    		/* Find out process rank */

    		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    		/* Send a message to MASTER that slave needs a job */

    		MPI_Send(&rank, sizeof(int), MPI_INT, 0, 51, MPI_COMM_WORLD);

    		if(debug == 1) {
    			printf("SLAVE %d: Habe meinen rank zurueckgesendet!\n", rank);
    			printf("SLAVE %d: Warte jetzt auf eine Nachricht vom MASTER!\n", rank);
    		}

    		/* Receive job ID for MASTER */

    		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    		MPI_Recv(&j, sizeof(long), MPI_INT, 0, 52, MPI_COMM_WORLD, &status);

    		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    		if(debug == 1) {
    			printf("Slave %d hat einen Jobauftrag empfangen : Job Nummer %ld\n", rank, j);
    		}

    		/* If MASTER did not send termination message start GALFIT procedure */

    		if(j != -1) {

				/* Identify GALFIT output path */

				sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", j));
				sprintf(imgblock_bd, "%s%s%s%ld%s", directory, "/", object, j + 1, "_2.fits");

				/* Do GALFIT procedure only if imagebloc ist not existing yet */

				if(access(imgblock_bd, 00) != 0) {

					/* Check if constraints should be used */

    				if(strcmp(constraints, "n") != 0 &&
    						strcmp(constraints, "no") != 0 &&
    						strcmp(constraints, "none") != 0) {

    					/* Check if constraintfile is existing - only if not create */

    					sprintf(constraintfile_bd, "%s%s%s%s%ld%s", directory, "/",
    							constraints, "_", j + 1, "_2");

    					if(create_constraintfile_bulge_disc(constraintfile_bd, &re_max,
    							&mag_min, &mag_max, tab, &j) != CPL_ERROR_NONE) {
    						cpl_msg_error(cpl_func,
    								"create_constraintfile_bulge_disc() failed!");
    					}
    				}

					/* Create bulge-disc GALFIT setup files with two components */

					if(create_bulge_disc_setup(gala_setup, &j) != CPL_ERROR_NONE) {
						cpl_msg_error(cpl_func,
								"create_bulge_disc_setup() failed!");
					}

    				if(debug == 1) {
    					printf("GALFIT bulge disc setup created for OBJECT %ld !\n", j);
    				}

    				/* Prepare GALFIT string */

        			sprintf(galsetfile, "%s%s%s%s%ld%s", directory, "/", galfitset,
        						"_", j + 1, "_2");

    				sprintf(str, "%s %s %s", path, galsetfile, "> /dev/null");

    				if(debug == 1) {
    					cpl_msg_info(cpl_func, "Slave %d is running GALFIT with %s.", rank, str);
    				}

    				/* Start GALFIT */

					if(system(str) != 0) {
						cpl_msg_error(cpl_func, "In run_bulge-disc_fitting(): System call "
								"return value which is not 0. What does that mean?");
    				}
				}
    		}
		}

    	/* Clean up */

    	cpl_table_delete(tab);
    }

	/* Go on when all slaves have finished their jobs */

    if(rank == 0) {
    	printf("MASTER: Warte auf Nachrichten von den Slaves dass "
			"alle ihre Jobs beendet haben!\n");
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

	/* Go on when all slaves have finished their jobs */

    if(rank == 0) {
    	printf("MASTER: Alle slaves sind da. Jobs beendet!\n");

    	/* Add results and remove helpfiles */

    	tab = cpl_table_load(tabfile, 1, 0);

    	/* Add results from previous fit to table and save*/

    	if(update_table_bulge_disc(tab, object) != CPL_ERROR_NONE) {
    		cpl_msg_error(cpl_func, "update_table_bulge_disc() failed.");
    	}

    	if(quantify_residuals(tab, object) != CPL_ERROR_NONE) {
    		cpl_msg_error(cpl_func, "quantify_residuals() failed.");
    	}

		cpl_table_save(tab, NULL, NULL, tabfile, CPL_IO_CREATE);

		printf("\nMASTER : TABLE gepeichert!!!!.\n");

		/* Clean up */

		cpl_table_delete(tab);
    }

	return CPL_ERROR_NONE;
}


cpl_error_code check_table_bulge_disc(cpl_table *tab) {

	/* Check if background values are written into table */

	if(cpl_table_has_column(tab, "GALA_BACKGROUND") != 1) {
		cpl_msg_error(cpl_func, "Sky values not available in "
				"table in bulge_disc_fitting()! Aborting...");
		cpl_table_delete(tab);
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	/* Check if single sersic values are written into table */

	if(cpl_table_has_column(tab, "X_GALFIT") != 1) {
		cpl_msg_error(cpl_func, "Sky values not available in "
				"table in bulge_disc_fitting()! Aborting...");
		cpl_table_delete(tab);
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	if(cpl_table_has_column(tab, "Y_GALFIT") != 1) {
		cpl_msg_error(cpl_func, "Sky values not available in "
				"table in bulge_disc_fitting()! Aborting...");
		cpl_table_delete(tab);
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	if(cpl_table_has_column(tab, "MAG_GALFIT") != 1) {
		cpl_msg_error(cpl_func, "Sky values not available in "
				"table in bulge_disc_fitting()! Aborting...");
		cpl_table_delete(tab);
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	if(cpl_table_has_column(tab, "RE_GALFIT") != 1) {
		cpl_msg_error(cpl_func, "Sky values not available in "
				"table in bulge_disc_fitting()! Aborting...");
		cpl_table_delete(tab);
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	if(cpl_table_has_column(tab, "SERSIC_GALFIT") != 1) {
		cpl_msg_error(cpl_func, "Sky values not available in "
				"table in bulge_disc_fitting()! Aborting...");
		cpl_table_delete(tab);
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	if(cpl_table_has_column(tab, "AR_GALFIT") != 1) {
		cpl_msg_error(cpl_func, "Sky values not available in "
				"table in bulge_disc_fitting()! Aborting...");
		cpl_table_delete(tab);
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	if(cpl_table_has_column(tab, "PA_GALFIT") != 1) {
		cpl_msg_error(cpl_func, "Sky values not available in "
				"table in bulge_disc_fitting()! Aborting...");
		cpl_table_delete(tab);
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	return CPL_ERROR_NONE;
}


cpl_error_code prepare_table_bulge_disc(cpl_table *tab) {

	cpl_table_new_column(tab, "X_C1_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "X_C1_ERR_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "Y_C1_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "Y_C1_ERR_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "MAG_C1_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "MAG_C1_ERR_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "RE_C1_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "RE_C1_ERR_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "SERSIC_C1_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "SERSIC_C1_ERR_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "AR_C1_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "AR_C1_ERR_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "ELLIPTICITY_C1_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "ELLIPTICITY_C1_ERR_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "PA_C1_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "PA_C1_ERR_GALFIT", CPL_TYPE_DOUBLE);

	cpl_table_new_column(tab, "X_C2_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "X_C2_ERR_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "Y_C2_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "Y_C2_ERR_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "MAG_C2_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "MAG_C2_ERR_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "RE_C2_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "RE_C2_ERR_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "SERSIC_C2_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "SERSIC_C2_ERR_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "AR_C2_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "AR_C2_ERR_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "ELLIPTICITY_C2_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "ELLIPTICITY_C2_ERR_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "PA_C2_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "PA_C2_ERR_GALFIT", CPL_TYPE_DOUBLE);

	cpl_table_new_column(tab, "FLAGS_GALFIT_BULGE_DISC", CPL_TYPE_STRING);
	cpl_table_new_column(tab, "CHISQ_BULGE_DISC_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "CHI2NU_BULGE_DISC_GALFIT", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "RESIDUAL_SERSIC", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "RESIDUAL_2COMP", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "GALAXY_TYPE", CPL_TYPE_STRING);

	return CPL_ERROR_NONE;
}


cpl_error_code create_bulge_disc_setup(cpl_parameterlist *gala_setup,
		const long *j) {

	int ncomponents = 2;

	int i,
		rank,
		num,
		secnum = 0,
		ctnum = 0,
		lv,
		xsize,
		ysize,
		count,
		debug = 0;

	long k,
		 nrow;

	double background, exptime, xc, yc, aim, bim, xlo, ylo, theta, mag, fr,
		xfit, yfit, convbox, platescale, magzero, fluxextend, psffactor,
		magexclude, magcrit, xsec, ysec, eli, xcgalfit = 0, ycgalfit = 0,
		maggalfit = 0, regalfit = 0, ngalfit = 0, argalfit = 0, pagalfit = 0;

	char outdir[FILENAME_MAX],
		 tabfile[FILENAME_MAX],
		 imagefile[FILENAME_MAX],
		 stampfile[FILENAME_MAX],
	     stampname[FILENAME_MAX],
	     galsetfile[FILENAME_MAX],
	 	 object[FILENAME_MAX],
	 	 galfitset[FILENAME_MAX],
	 	 galfitim[FILENAME_MAX],
	 	 stamp[FILENAME_MAX],
	 	 badpix[FILENAME_MAX],
	 	 maskfile[FILENAME_MAX],
	 	 constraints[FILENAME_MAX],
	     constraintfile[FILENAME_MAX],
	     psf[FILENAME_MAX],
	     display[FILENAME_MAX],
	     directory[FILENAME_MAX],
	     fitfile[FILENAME_MAX],
	     xp[FILENAME_MAX],
	     yp[FILENAME_MAX],
	     mg[FILENAME_MAX],
	     re[FILENAME_MAX],
	     n[FILENAME_MAX],
	     ar[FILENAME_MAX],
	     pa[FILENAME_MAX],
	     str[FILENAME_MAX],
	     combcatname[FILENAME_MAX];

	char *ptr;

	FILE *fp_gs;

	cpl_array *secindices, *ctindices;
	const cpl_array *help;

	cpl_table *tab;

	cpl_parameter *p;

	cpl_propertylist *header, *fitsheader;

	cpl_boolean skyfix = CPL_FALSE;

	/* Check input variable */

	if(*j == -1) {

		/* do nothing */

		return CPL_ERROR_NONE;
	}

	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	/* Load variables from setup parameterlist */

	p = cpl_parameterlist_find(gala_setup, "outdir");
	sprintf(outdir, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "stampfile");
    sprintf(stampfile, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "stampname");
    sprintf(stampname, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "object");
    sprintf(object, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "galfitset");
    sprintf(galfitset, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "badpix");
    sprintf(badpix, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "constraints");
    sprintf(constraints, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "psf");
    sprintf(psf, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "psffactor");
    psffactor = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "convbox");
    convbox = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magzero");
    magzero = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "platescale");
    platescale = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "fluxextend");
    fluxextend = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magexclude");
    magexclude = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magcrit");
    magcrit = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "display");
    sprintf(display, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "sexcomb");
    sprintf(combcatname, "%s", cpl_parameter_get_string(p));

	/* Read values from a table (read-only!!!) copy */

	sprintf(tabfile, "%s%s%s", outdir, "/", combcatname);

	if(access(tabfile, 00) != 0) {
		cpl_msg_error(cpl_func, "In create_bulge_disc_setup() : "
				"Table %s was not accessable! Aborting...", tabfile);
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	/* Load table and check*/

	tab = cpl_table_load(tabfile, 1, 0);

	nrow = (long) cpl_table_get_nrow(tab);

	if(nrow <= 0) {
		cpl_msg_error(cpl_func, "In create_bulge_disc_setup() : "
				"Input table %s is empty or not readable. Aborting...",
				tabfile);
		cpl_table_delete(tab);
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	/* Get SExtractor number of current object */

	num = cpl_table_get(tab, "NUMBER", *j, NULL);

	/* image header and exposure time */

	sprintf(imagefile, "%s%s%s%s%s%s%d%s%s%s",
			cpl_table_get_string(tab, "TILE_DIRECTORY", *j),
			"/", stampfile, "/", stampname, "_", num, "_",
			cpl_table_get_string(tab, "TILE", *j), ".fits");

	if(debug == 1) {
		printf("IMAGEFILE in create_bulge_disc_setup() : %s\n", imagefile);
	}

	header = cpl_propertylist_load(imagefile, 0); // read fits header
	if (header == NULL) {
	    /* image header not found */
		cpl_propertylist_delete(header);
		cpl_table_delete(tab);
		cpl_msg_error(cpl_func, "Stamp file not found in "
				"create_bulge_disc_setup(). Aborting...");
	    return cpl_error_set_message(cpl_func, CPL_ERROR_FILE_NOT_FOUND,
	                                     "%s not found", imagefile);
	}

	exptime = cpl_propertylist_get_double(header, "EXPTIME");

	if(debug == 1) {
		printf("EXPTIME in create_bulge_disc_setup() : %f\n", exptime);
	}

	if(exptime <= 0) {
		cpl_msg_error(cpl_func, "Exptime not found in "
				"create_bulge_disc_setup()!!!");
	}

	// Prepare filename paths and input data for setup file

	sprintf(stamp, "%s", imagefile);

	xsize = cpl_table_get_int(tab, "STAMP_XHI",*j, NULL) -
			cpl_table_get_int(tab, "STAMP_XLO",*j, NULL) + 1;
	ysize = cpl_table_get_int(tab, "STAMP_YHI",*j, NULL) -
			cpl_table_get_int(tab, "STAMP_YLO",*j, NULL) + 1;

	if(debug == 1) {
		printf("STAMP SIZES x : %d  y : %d\n", xsize, ysize);
	}

	if(xsize <= 0 || ysize <= 0) {
		cpl_msg_error(cpl_func, "In create_GALFIT_setup() : Stamp image not found!");
	}

	sprintf(galsetfile, "%s%s%s%s%ld%s",
			cpl_table_get_string(tab, "TILE_DIRECTORY", *j), "/", galfitset, "_", *j + 1, "_2");

	if(debug == 1) {
		printf("GALFIT-Setup FILE : %s\n", galsetfile);
	}

	sprintf(galfitim, "%s%s%s%ld%s", cpl_table_get_string(tab, "TILE_DIRECTORY", *j),
			"/", object, *j + 1, "_2.fits");

	if(debug == 1) {
		printf("GALFIT imageblock FILE : %s\n", galfitim);
	}

	if(strcmp(badpix, "n") != 0 && strcmp(badpix, "no") != 0 &&
			strcmp(badpix, "none") != 0) {
		sprintf(maskfile, "%s%s%s%s%ld%s", cpl_table_get_string(tab, "TILE_DIRECTORY", *j),
					"/", badpix, "_", *j + 1, ".fits");

		// Check if accessable

		if(access(maskfile, 00) != 0) {
			cpl_msg_error(cpl_func, "Mask file is not "
					"accessable in create_GALFIT_Setup() for setup "
					"%ld !!! GALFIT will be started anyway but "
					"without mask.", *j + 1);
		}

		if(debug == 1) {
			printf("GALFIT mask FILE : %s\n", maskfile);
		}

	} else {
		sprintf(maskfile, "%s", "none");
	}

	if (strcmp(constraints, "n") != 0 && strcmp(constraints, "no") != 0 &&
			strcmp(constraints, "none") != 0) {
		sprintf(constraintfile, "%s%s%s%s%ld%s",
				cpl_table_get_string(tab, "TILE_DIRECTORY", *j), "/",
				constraints, "_", *j + 1, "_2");

		// Check if accessable

		if(access(constraintfile, 00) != 0) {
			cpl_msg_error(cpl_func, "Constraint file is not "
				"accessable in create_GALFIT_Setup() for setup "
				"%ld !!! GALFIT will be started anyway but "
				"without constraints.", *j + 1);
		}

		if(debug == 1) {
			printf("GALFIT constraint FILE : %s\n", constraintfile);
		}

	} else {
		sprintf(constraintfile, "%s", "none");
	}

	// Read object data from table

	background  =  cpl_table_get_double(tab, "GALA_BACKGROUND", *j, NULL);
	xc      	=  cpl_table_get_double(tab, "X_IMAGE", *j, NULL);
	yc    	    =  cpl_table_get_double(tab, "Y_IMAGE", *j, NULL);
	aim 		=  cpl_table_get_double(tab, "A_IMAGE", *j, NULL);
	bim 		=  cpl_table_get_double(tab, "B_IMAGE", *j, NULL);
	theta 		=  cpl_table_get_double(tab, "THETA_IMAGE", *j, NULL);
	mag     	=  cpl_table_get_double(tab, "MAG_BEST", *j, NULL);
	fr     	    =  cpl_table_get_double(tab, "FLUX_RADIUS", *j, NULL);
	xlo         =  cpl_table_get_int(tab, "STAMP_XLO", *j, NULL);
	ylo         =  cpl_table_get_int(tab, "STAMP_YLO", *j, NULL);
	xfit  = xc - xlo;
	yfit  = yc - ylo;
	theta = theta - 90;

	// Write GALFIT setup file

	fp_gs = fopen(galsetfile, "w");

	if(fp_gs == NULL) {
		cpl_msg_error(cpl_func, "In create_bulge_disc_setup(): An internal "
				"error occurred. Unable to open file %s", galsetfile);
	} else {
		printf("Slave %d : Opened file %s successfully!\n", rank, galsetfile);
	}

	fprintf(fp_gs, "===================================================\n");
	fprintf(fp_gs, "# IMAGE and GALFIT CONTROL PARAMETERS\n");
	fprintf(fp_gs, "A) %s\n", stamp);
	fprintf(fp_gs, "B) %s\n", galfitim);
	fprintf(fp_gs, "C) none\n");
	fprintf(fp_gs, "D) %s\n", psf);
	fprintf(fp_gs, "E) %f\n", psffactor);
	fprintf(fp_gs, "F) %s\n", maskfile);
	fprintf(fp_gs, "G) %s\n", constraintfile);
	fprintf(fp_gs, "H) %d   %d   %d   %d\n", 1, xsize, 1, ysize);
	fprintf(fp_gs, "I) %d   %d\n", (int)convbox, (int)convbox);
	fprintf(fp_gs, "J) %.4f\n", magzero);
	fprintf(fp_gs, "K) %.5f %.5f\n", platescale, platescale);
	fprintf(fp_gs, "O) %s\n", display);
	fprintf(fp_gs, "P) 0\n\n");

	fprintf(fp_gs, "# sky\n");
	fprintf(fp_gs, "0) sky\n");

	if(skyfix == CPL_TRUE) {
		fprintf(fp_gs, "1) %.3f 0\n", background);
		fprintf(fp_gs, "2) %f 0\n", 0.);
		fprintf(fp_gs, "3) %f 0\n", 0.);
	} else {
		fprintf(fp_gs, "1) %.3f 1\n", background);
		fprintf(fp_gs, "2) %f 1\n", 0.);
		fprintf(fp_gs, "3) %f 1\n", 0.);
	}
	fprintf(fp_gs, "Z) 0\n\n");

	if(ncomponents == 2) {

		fprintf(fp_gs, "# Sersic function component 1\n");
		fprintf(fp_gs, "0) sersic\n");
		fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xfit, yfit);
		fprintf(fp_gs, "3) %.2f 1\n", mag + 0.7526);
		fprintf(fp_gs, "4) %.2f 1\n", (pow(fr, fluxextend)) / 2);
		fprintf(fp_gs, "5) %.2f 1\n", 4.);
		fprintf(fp_gs, "9) %.4f 1\n", 1.);
		fprintf(fp_gs, "10) %.2f 1\n", theta + 1);
		fprintf(fp_gs, "Z) 0\n\n");

		fprintf(fp_gs, "# Sersic function component 2\n");
		fprintf(fp_gs, "0) sersic\n");
		fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xfit, yfit);
		fprintf(fp_gs, "3) %.2f 1\n", mag + 0.7526);
		fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));
		fprintf(fp_gs, "5) %.2f 1\n", 1.);
		fprintf(fp_gs, "9) %.4f 1\n", bim / aim);
		fprintf(fp_gs, "10) %.2f 1\n", theta - 1);
		fprintf(fp_gs, "Z) 0\n\n");


		// Add secondaries

		help = cpl_table_get_array(tab, "SECONDARY_INDICES", *j);

		secindices = cpl_array_duplicate(help);

		if(debug == 1) {
			printf("SECONDARY_NUMBER_ARRAY:\n");
			cpl_array_dump(secindices, 0,
					cpl_array_get_size(secindices), NULL);

			printf("NUMBER OF SECONDARIES: %d\n",
					(int)cpl_array_get_size(secindices));
		}

		for(i = 0; i < cpl_array_get_size(secindices); i++) {
			if(cpl_array_get(secindices, i, NULL) > 0) {
				secnum++;
			}
		}

		// If secondaries exist, amplify GALFIT setup file for each secondary

		for(lv = 0; lv < secnum; lv++) {

			k = (long)cpl_array_get(secindices, lv, NULL);

			if(k <= 0) {
				cpl_msg_error(cpl_func, "An internal error occured in "
					"create_GALFIT_setup(). Secondary has negative "
					"table index!");
				break;
			}

			sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", *j));
			sprintf(fitfile, "%s%s%s%ld%s", directory, "/", object, k, ".fits");

			// If fit for secondary exists

			if(access(fitfile, 00) == 0) {

				if(readfits_header(fitfile) >= 0) {

					// Read data from fit

					fitsheader = cpl_propertylist_load(fitfile, 2);

//					if(fitsheader == NULL) {

						if(debug == 1) {
							cpl_msg_error(cpl_func, "Unspecified problem with loading Header in "
									"create_GALFIT_setup() from %s. "
									"Possibly GALFIT crashed for this object.", fitfile);
						}

						fprintf(fp_gs, "# Sersic function\n");
						fprintf(fp_gs, "0) sersic\n");

						xsec  = xfit + cpl_table_get_double(tab, "X_IMAGE", k - 1, NULL) - xc;
						ysec  = yfit + cpl_table_get_double(tab, "Y_IMAGE", k - 1, NULL) - yc;
						fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xsec, ysec);

						mag = cpl_table_get_double(tab, "MAG_BEST", k - 1, NULL);
						fprintf(fp_gs, "3) %.2f 1\n", mag);

						fr = cpl_table_get_double(tab, "FLUX_RADIUS", k - 1, NULL);

						fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));

						fprintf(fp_gs, "5) %.2f 1\n", 2.5);

						eli = cpl_table_get_double(tab, "ELLIPTICITY", k - 1, NULL);
						fprintf(fp_gs, "9) %.4f 1\n", 1 - eli);

						theta = cpl_table_get_double(tab, "THETA_IMAGE", k - 1, NULL);

						if(theta >= 0) {
							theta = theta - 90;
						} else {
							theta = 90 + theta;
						}
						fprintf(fp_gs, "10) %.2f 1\n", theta);

						fprintf(fp_gs, "Z) 0\n\n");

//					} else {
//
//						fprintf(fp_gs, "# Sersic function\n");
//						fprintf(fp_gs, "0) sersic\n");
//
//						count = 0;
//
//						if(cpl_propertylist_has(fitsheader, "2_XC") == 1) {
//							sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_XC"));
//							sprintf(xp, "%s", cpl_propertylist_get_string(fitsheader, "2_XC"));
//						} else {
//							cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
//							sprintf(xp, "%s", "1");
//						}
//						remove_chr(xp);
//						ptr = strtok(xp, " ");
//						while(ptr != NULL) {
//							if(count == 0) {
//								xcgalfit = atof(ptr);
//							}
//							ptr = strtok(NULL, " ");
//							count ++;
//						}
//						count = 0;
//
//						if(cpl_propertylist_has(fitsheader, "2_YC") == 1) {
//							sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_YC"));
//							sprintf(yp, "%s", cpl_propertylist_get_string(fitsheader, "2_YC"));
//						} else {
//							cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
//							sprintf(yp, "%s", "1");
//						}
//						remove_chr(yp);
//						ptr = strtok(yp, " ");
//						while(ptr != NULL) {
//							if(count == 0) {
//								ycgalfit = atof(ptr);
//							}
//							ptr = strtok(NULL, " ");
//							count ++;
//						}
//						count = 0;
//
//						fprintf(fp_gs, "1) %.2f %.2f 0 0\n", xfit+xcgalfit-xc,
//								yfit+ycgalfit-yc);
//
//						if(cpl_propertylist_has(fitsheader, "2_MAG") == 1) {
//							sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_MAG"));
//							sprintf(mg, "%s", cpl_propertylist_get_string(fitsheader, "2_MAG"));
//						} else {
//							cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
//							sprintf(mg, "%s", "20");
//						}
//						remove_chr(mg);
//						ptr = strtok(mg, " ");
//						while(ptr != NULL) {
//							if(count == 0) {
//								maggalfit = atof(ptr);
//							}
//							ptr = strtok(NULL, " ");
//							count ++;
//						}
//						count = 0;
//
//						fprintf(fp_gs, "3) %.2f 0\n", maggalfit);
//
//						if(cpl_propertylist_has(fitsheader, "2_RE") == 1) {
//							sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_RE"));
//							sprintf(re, "%s", cpl_propertylist_get_string(fitsheader, "2_RE"));
//						} else {
//							cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
//							sprintf(re, "%s", "20");
//						}
//						remove_chr(re);
//						ptr = strtok(re, " ");
//						while(ptr != NULL) {
//							if(count == 0) {
//								regalfit = atof(ptr);
//							}
//							ptr = strtok(NULL, " ");
//							count ++;
//						}
//						count = 0;
//
//						fprintf(fp_gs, "4) %.2f 0\n", regalfit);
//
//						if(cpl_propertylist_has(fitsheader, "2_N") == 1) {
//							sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_N"));
//							sprintf(n, "%s", cpl_propertylist_get_string(fitsheader, "2_N"));
//						} else {
//							cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
//							sprintf(n, "%s", "2.5");
//						}
//						remove_chr(n);
//						ptr = strtok(n, " ");
//						while(ptr != NULL) {
//							if(count == 0) {
//								ngalfit = atof(ptr);
//							}
//							ptr = strtok(NULL, " ");
//							count ++;
//						}
//						count = 0;
//
//						fprintf(fp_gs, "5) %.2f 0\n", ngalfit);
//
//						if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
//							sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
//							sprintf(ar, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
//						} else {
//							cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
//							sprintf(ar, "%s", "0.8");
//						}
//						remove_chr(ar);
//						ptr = strtok(ar, " ");
//						while(ptr != NULL) {
//							if(count == 0) {
//								argalfit = atof(ptr);
//							}
//							ptr = strtok(NULL, " ");
//							count ++;
//						}
//						count = 0;
//
//						fprintf(fp_gs, "9) %.2f 0\n", argalfit);
//
//						if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
//							sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
//							sprintf(pa, "%s", cpl_propertylist_get_string(fitsheader, "2_PA"));
//						} else {
//							cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
//							sprintf(pa, "%s", "0");
//						}
//						remove_chr(pa);
//						ptr = strtok(pa, " ");
//						while(ptr != NULL) {
//							if(count == 0) {
//								pagalfit = atof(ptr);
//							}
//							ptr = strtok(NULL, " ");
//							count ++;
//						}
//						count = 0;
//
//						fprintf(fp_gs, "10) %.2f 0\n", pagalfit);
//
//						fprintf(fp_gs, "Z) 0\n\n");
//
//					}

					cpl_propertylist_delete(fitsheader);
				}

				// If fit for secondary does not exist take SExtractor parameters

			} else {

				fprintf(fp_gs, "# Sersic function\n");
				fprintf(fp_gs, "0) sersic\n");

				xsec  = xfit + cpl_table_get_double(tab, "X_IMAGE", k - 1, NULL) - xc;
				ysec  = yfit + cpl_table_get_double(tab, "Y_IMAGE", k - 1, NULL) - yc;
				fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xsec, ysec);

				mag = cpl_table_get_double(tab, "MAG_BEST", k - 1, NULL);
				fprintf(fp_gs, "3) %.2f 1\n", mag);

				fr = cpl_table_get_double(tab, "FLUX_RADIUS", k - 1, NULL);

				fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));

				fprintf(fp_gs, "5) %.2f 1\n", 2.5);

				eli = cpl_table_get_double(tab, "ELLIPTICITY", k - 1, NULL);
				fprintf(fp_gs, "9) %.4f 1\n", 1 - eli);

				theta = cpl_table_get_double(tab, "THETA_IMAGE", k - 1, NULL);

				if(theta >= 0) {
					theta = theta - 90;
				} else {
					theta = 90 + theta;
				}
				fprintf(fp_gs, "10) %.2f 1\n", theta);

				fprintf(fp_gs, "Z) 0\n\n");
			}
		}

		cpl_array_delete(secindices);

		// Include also potential contrib targets

		help = cpl_table_get_array(tab, "POT_CT_INDICES", *j);

		ctindices = cpl_array_duplicate(help);

		if(debug == 1) {
			printf("CONTRIB_TARGET_ARRAY:\n");
			cpl_array_dump(ctindices, 0,
					cpl_array_get_size(ctindices), NULL);

			printf("NUMBER OF POTENTIAL CONTRIB_TARGETS: %d\n",
					(int)cpl_array_get_size(ctindices));
		}

		// Get number of contribs

		for(i = 0; i < cpl_array_get_size(ctindices); i++) {
			if(cpl_array_get(ctindices, i, NULL) >= 0) {
				ctnum++;
			}
		}

		for(lv = 0; lv < ctnum; lv++) {

			k = cpl_array_get(ctindices, lv, NULL) - 1;

			if(k < 0) {
				cpl_msg_error(cpl_func, "An internal error occured in "
					"create_GALFIT_setup(). Secondary has negative "
					"table index!");
				break;
			}

			sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", k));
			sprintf(fitfile, "%s%s%s%ld%s", directory, "/", object, k + 1, ".fits");

			// If fit for contrib target exists

			if(access(fitfile, 00) == 0) {

				if(check_contribtarget(tab, object, &*j, &k, &magzero, &exptime,
						&magexclude, &magcrit, &fluxextend) == 0) {

					// Read data from fit

					if((fitsheader = cpl_propertylist_load(fitfile, 2)) != CPL_ERROR_NONE ||
							fitsheader == NULL) {

						if(debug == 1) {
							cpl_msg_error(cpl_func, "Unspecified problem with loading Header in "
								"create_GALFIT_setup() from %s. "
								"Possibly GALFIT crashed for this object.", fitfile);
						}

						fprintf(fp_gs, "# Sersic function\n");
						fprintf(fp_gs, "0) sersic\n");

						xsec  = cpl_table_get_double(tab, "X_IMAGE", k, NULL) - xlo;
						ysec  = cpl_table_get_double(tab, "Y_IMAGE", k, NULL) - ylo;
						fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xsec, ysec);

						mag = cpl_table_get_double(tab, "MAG_BEST", k, NULL);
						fprintf(fp_gs, "3) %.2f 1\n", mag);

						fr = cpl_table_get_double(tab, "FLUX_RADIUS", k, NULL);
						fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));

						fprintf(fp_gs, "5) %.2f 1\n", 2.5);

						eli = cpl_table_get_double(tab, "ELLIPTICITY", k, NULL);
						fprintf(fp_gs, "9) %.4f 1\n", 1 - eli);

						theta = cpl_table_get_double(tab, "THETA_IMAGE", k, NULL);
						if(theta >= 0) {
							theta = theta - 90;
						} else {
						theta = 90 + theta;
						}
						fprintf(fp_gs, "10) %.2f 1\n", theta);

						fprintf(fp_gs, "Z) 0\n\n");

					} else {

						fprintf(fp_gs, "# Sersic function\n");
						fprintf(fp_gs, "0) sersic\n");

						count = 0;

						if(cpl_propertylist_has(fitsheader, "2_XC") == 1) {
							sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_XC"));
							sprintf(xp, "%s", cpl_propertylist_get_string(fitsheader, "2_XC"));
						} else {
							cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
							sprintf(xp, "%s", "1");
						}
						remove_chr(xp);
						ptr = strtok(xp, " ");
						while(ptr != NULL) {
							if(count == 0) {
								xcgalfit = atof(ptr);
							}
							ptr = strtok(NULL, " ");
							count ++;
						}
						count = 0;

						if(cpl_propertylist_has(fitsheader, "2_YC") == 1) {
							sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_YC"));
							sprintf(yp, "%s", cpl_propertylist_get_string(fitsheader, "2_YC"));
						} else {
							cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
							sprintf(yp, "%s", "1");
						}
						remove_chr(yp);
						ptr = strtok(yp, " ");
						while(ptr != NULL) {
							if(count == 0) {
								ycgalfit = atof(ptr);
							}
							ptr = strtok(NULL, " ");
							count ++;
						}
						count = 0;

						fprintf(fp_gs, "1) %.2f %.2f 0 0\n", xcgalfit, ycgalfit);

						if(cpl_propertylist_has(fitsheader, "2_MAG") == 1) {
							sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_MAG"));
							sprintf(mg, "%s", cpl_propertylist_get_string(fitsheader, "2_MAG"));
						} else {
							cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
							sprintf(mg, "%s", "20");
						}
						remove_chr(mg);
						ptr = strtok(mg, " ");
						while(ptr != NULL) {
							if(count == 0) {
								maggalfit = atof(ptr);
							}
							ptr = strtok(NULL, " ");
							count ++;
						}
						count = 0;

						fprintf(fp_gs, "3) %.2f 0\n", maggalfit);

						if(cpl_propertylist_has(fitsheader, "2_RE") == 1) {
							sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_RE"));
							sprintf(re, "%s", cpl_propertylist_get_string(fitsheader, "2_RE"));
						} else {
						cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
							sprintf(re, "%s", "20");
						}
						remove_chr(re);
						ptr = strtok(re, " ");
						while(ptr != NULL) {
							if(count == 0) {
								regalfit = atof(ptr);
							}
							ptr = strtok(NULL, " ");
							count ++;
						}
						count = 0;

						fprintf(fp_gs, "4) %.2f 0\n", regalfit);

						if(cpl_propertylist_has(fitsheader, "2_N") == 1) {
							sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_N"));
							sprintf(n, "%s", cpl_propertylist_get_string(fitsheader, "2_N"));
						} else {
							cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
							sprintf(n, "%s", "2.5");
						}
						remove_chr(n);
						ptr = strtok(n, " ");
						while(ptr != NULL) {
							if(count == 0) {
								ngalfit = atof(ptr);
							}
							ptr = strtok(NULL, " ");
							count ++;
						}
						count = 0;

						fprintf(fp_gs, "5) %.2f 0\n", ngalfit);

						if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
							sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
							sprintf(ar, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
						} else {
							cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
							sprintf(ar, "%s", "0.8");
						}
						remove_chr(ar);
						ptr = strtok(ar, " ");
						while(ptr != NULL) {
							if(count == 0) {
								argalfit = atof(ptr);
							}
							ptr = strtok(NULL, " ");
							count ++;
						}
						count = 0;

						fprintf(fp_gs, "9) %.2f 0\n", argalfit);

						if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
							sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
							sprintf(pa, "%s", cpl_propertylist_get_string(fitsheader, "2_PA"));
						} else {
							cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
							sprintf(pa, "%s", "0");
						}
						remove_chr(pa);
						ptr = strtok(pa, " ");
						while(ptr != NULL) {
							if(count == 0) {
								pagalfit = atof(ptr);
							}
							ptr = strtok(NULL, " ");
							count ++;
						}
						count = 0;

						fprintf(fp_gs, "10) %.2f 0\n", pagalfit);
						fprintf(fp_gs, "Z) 0\n\n");
					}

					cpl_propertylist_delete(fitsheader);
				}
			} else {

				if(check_contribtarget_sexdata(tab, &*j, &k, &magzero, &exptime,
						&magexclude, &magcrit, &fluxextend) == 0) {

					fprintf(fp_gs, "# Sersic function\n");
					fprintf(fp_gs, "0) sersic\n");

					xsec  = cpl_table_get_double(tab, "X_IMAGE", k, NULL) - xlo;
					ysec  = cpl_table_get_double(tab, "Y_IMAGE", k, NULL) - ylo;
					fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xsec, ysec);

					mag = cpl_table_get_double(tab, "MAG_BEST", k, NULL);
					fprintf(fp_gs, "3) %.2f 1\n", mag);

					fr = cpl_table_get_double(tab, "FLUX_RADIUS", k, NULL);
					fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));

					fprintf(fp_gs, "5) %.2f 1\n", 2.5);

					eli = cpl_table_get_double(tab, "ELLIPTICITY", k, NULL);
					fprintf(fp_gs, "9) %.4f 1\n", 1 - eli);

					theta = cpl_table_get_double(tab, "THETA_IMAGE", k, NULL);
					if(theta >= 0) {
						theta = theta - 90;
					} else {
					theta = 90 + theta;
					}
					fprintf(fp_gs, "10) %.2f 1\n", theta);

					fprintf(fp_gs, "Z) 0\n\n");
				}
			}
		}

		cpl_array_delete(ctindices);

	} else {
		cpl_msg_error(cpl_func, "More than 2 components are not possible at "
				"the moment.");
	}

	fclose(fp_gs);

	/* Clean up */

	cpl_propertylist_delete(header);
	cpl_table_delete(tab);

	return CPL_ERROR_NONE;
}


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


int check_contribtarget(cpl_table *tab, const char *object,
		const long *primindex, const long *ctindex,
		const double *magzero, const double *exptime,
		const double *magexclude, const double *magcrit,
		const double *fluxextend) {

	int nrow, debug = 0, count = 0;
	double xp = 0, yp = 0, xct = 0, yct = 0, r = 0, pa = 0, rect = 0, nct = 0,
			arct = 0, ftot = 0, kap = 0, f0 = 0, magct = 0, phi = 0, flux = 0,
			crit = 0, magp = 0, magdiff = 0, pact = 0;
	double pi = 3.14159265;
	char xcts[FILENAME_MAX];
	char ycts[FILENAME_MAX];
	char pacts[FILENAME_MAX];
	char rects[FILENAME_MAX];
	char ncts[FILENAME_MAX];
	char arcts[FILENAME_MAX];
	char magcts[FILENAME_MAX];
	char ptile[FILENAME_MAX];
	char stile[FILENAME_MAX];
	char objectfile[FILENAME_MAX];
	char *ptr;

	cpl_propertylist *fitsheader;

	/* Starting message */

	if(debug == 1) {
		cpl_msg_info(cpl_func, "Checking contrib targets for object with "
				"table index %ld", *primindex);
	}

	if(debug == 1) {
		printf("CTINDEX : %ld\n", *ctindex);
		printf("MAGZERO : %f\n", *magzero);
		printf("EXPTIME : %f\n", *exptime);
		printf("MAGEXCLUDE : %f\n", *magexclude);
		printf("MAGCRIT : %f\n", *magcrit);
		printf("MFLUXEXTEND : %f\n", *fluxextend);
	}

	/* Check input */

	nrow = cpl_table_get_nrow(tab);

	if(nrow <= 0) {
		cpl_msg_error(cpl_func, "In check_contribtarget(): Table is empty! "
				"Aborting...");
		return -1;
	}

	if(*exptime < 0 || *primindex < 0 || *ctindex < 0 || *primindex > nrow ||
			*ctindex > nrow) {
		cpl_msg_error(cpl_func, "In check_contribtarget(): Unspecified error! "
				"Aborting...");
		return -1;
	}

	// Check if objects are on the same tile

	sprintf(ptile, "%s", cpl_table_get_string(tab, "TILE", *primindex));
	sprintf(stile, "%s", cpl_table_get_string(tab, "TILE", *ctindex));

	if(strcmp(ptile, stile) != 0) {
		cpl_msg_error(cpl_func, "In check_contribtargets(): Internal error. "
				"Objects are not on the same tile. Potential contrib target will "
				"not be included.");
		return 1;
	}

	// Get primary data

	if(debug == 1) {
		printf("INDEX PRIMARY : %d\n", cpl_table_get_int(tab, "NUMBER", *primindex, NULL));
		printf("INDEX CONTRIB TARGET : %d\n", cpl_table_get_int(tab, "NUMBER", *ctindex, NULL));
	}

	xp    = cpl_table_get_double(tab, "X_IMAGE", *primindex, NULL);
	yp    = cpl_table_get_double(tab, "Y_IMAGE", *primindex, NULL);
	magp  = cpl_table_get_double(tab, "MAG_BEST", *primindex, NULL);

	// Get contrib target data

	sprintf(objectfile, "%s%s%s%ld%s",
			cpl_table_get_string(tab, "TILE_DIRECTORY", *ctindex),
			"/", object, *ctindex + 1, ".fits");

	if(access(objectfile, 00) == 0) {

		if(debug == 1) {
			printf("Access for objectfile %s was possible. Checking contrib target data.\n",
					objectfile);
		}

		// Read data from fit

		fitsheader = cpl_propertylist_load(objectfile, 2);

		count = 0;

		if(cpl_propertylist_has(fitsheader, "2_XC") == 1) {
			sprintf(xcts, "%s", cpl_propertylist_get_string(fitsheader, "2_XC"));
		} else {
			cpl_msg_error(cpl_func, "Property not available in check_contribtarget()!!");
			sprintf(xcts, "%s", "1");
		}
		remove_chr(xcts);
		ptr = strtok(xcts, " ");
		while(ptr != NULL) {
			if(count == 0) {
				xct = atof(ptr);
			}
			ptr = strtok(NULL, " ");
			count ++;
		}
		count = 0;

		if(cpl_propertylist_has(fitsheader, "2_YC") == 1) {
			sprintf(ycts, "%s", cpl_propertylist_get_string(fitsheader, "2_YC"));
		} else {
			cpl_msg_error(cpl_func, "Property not available in check_contribtarget()!!");
			sprintf(ycts, "%s", "1");
		}
		remove_chr(ycts);
		ptr = strtok(ycts, " ");
		while(ptr != NULL) {
			if(count == 0) {
				yct = atof(ptr);
			}
			ptr = strtok(NULL, " ");
			count ++;
		}
		count = 0;

		xct = cpl_table_get_double(tab, "X_IMAGE", *ctindex, NULL);
		yct = cpl_table_get_double(tab, "Y_IMAGE",  *ctindex, NULL);

		if(cpl_propertylist_has(fitsheader, "2_MAG") == 1) {
			sprintf(magcts, "%s", cpl_propertylist_get_string(fitsheader, "2_MAG"));
		} else {
			cpl_msg_error(cpl_func, "Property not available in check_contribtarget()!!");
			sprintf(magcts, "%s", "20");
		}
		remove_chr(magcts);
		ptr = strtok(magcts, " ");
		while(ptr != NULL) {
			if(count == 0) {
				magct = atof(ptr);
			}
			ptr = strtok(NULL, " ");
			count ++;
		}
		count = 0;

		if(cpl_propertylist_has(fitsheader, "2_RE") == 1) {
			sprintf(rects, "%s", cpl_propertylist_get_string(fitsheader, "2_RE"));
		} else {
			cpl_msg_error(cpl_func, "Property not available in check_contribtarget()!!");
			sprintf(rects, "%s", "20");
		}
		remove_chr(rects);
		ptr = strtok(rects, " ");
		while(ptr != NULL) {
			if(count == 0) {
				rect = atof(ptr);
			}
			ptr = strtok(NULL, " ");
			count ++;
		}
		count = 0;

		if(cpl_propertylist_has(fitsheader, "2_N") == 1) {
			sprintf(ncts, "%s", cpl_propertylist_get_string(fitsheader, "2_N"));
		} else {
			cpl_msg_error(cpl_func, "Property not available in check_contribtarget()!!");
			sprintf(ncts, "%s", "2.5");
		}
		remove_chr(ncts);
		ptr = strtok(ncts, " ");
		while(ptr != NULL) {
			if(count == 0) {
				nct = atof(ptr);
			}
			ptr = strtok(NULL, " ");
			count ++;
		}
		count = 0;

		if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
			sprintf(arcts, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
		} else {
			cpl_msg_error(cpl_func, "Property not available in check_contribtarget()!!");
			sprintf(arcts, "%s", "0.8");
		}
		remove_chr(arcts);
		ptr = strtok(arcts, " ");
		while(ptr != NULL) {
			if(count == 0) {
				arct = atof(ptr);
			}
			ptr = strtok(NULL, " ");
			count ++;
		}
		count = 0;

		if(cpl_propertylist_has(fitsheader, "2_PA") == 1) {
			sprintf(pacts, "%s", cpl_propertylist_get_string(fitsheader, "2_PA"));
		} else {
			cpl_msg_error(cpl_func, "Property not available in check_contribtarget()!!");
			sprintf(pacts, "%s", "0");
		}
		remove_chr(pacts);
		ptr = strtok(pacts, " ");
		while(ptr != NULL) {
			if(count == 0) {
				pact = atof(ptr);
			}
			ptr = strtok(NULL, " ");
			count ++;
		}
		count = 0;

		cpl_propertylist_delete(fitsheader);

	} else {

		cpl_msg_error(cpl_func, "In check_contribtarget(): Access for object file "
				"%s was not possible. Estimating data from SExtractor information.",
				objectfile);

		// Get contrib target data from table

		xct   = cpl_table_get_double(tab, "X_IMAGE", *ctindex, NULL);
		yct   = cpl_table_get_double(tab, "Y_IMAGE",  *ctindex, NULL);
		pact = cpl_table_get_double(tab, "THETA_IMAGE", *ctindex, NULL);
		pact = pact - 90;

		rect = cpl_table_get_double(tab, "FLUX_RADIUS", *ctindex, NULL);
		rect = pow(rect, *fluxextend);

		nct = 2.5;

		arct = 1 - cpl_table_get_double(tab, "ELLIPTICITY", *ctindex, NULL);

		magct = cpl_table_get_double(tab, "MAG_BEST", *ctindex, NULL);
	}


//	sprintf(pas, "%f", pact);
//	if(strcmp(pas, "nan") == 0) {
//		pa = cpl_table_get_double(tab, "THETA_IMAGE", *ctindex, NULL);
//		pa = pa - 90;
//	}
//	sprintf(res, "%f", rect);
//	if(strcmp(res, "nan") == 0) {
//		re = cpl_table_get_double(tab, "FLUX_RADIUS", *ctindex, NULL);
//		re = pow(re, *fluxextend);
//	}
//	sprintf(ns, "%f", nct);
//	if(strcmp(ns, "nan") == 0) {
//		n = 2.5;
//	}
//	sprintf(qs, "%f", arct);
//	if(strcmp(qs, "nan") == 0) {
//		q = 1 - cpl_table_get_double(tab, "ELLIPTICITY", *ctindex, NULL);
//	}
//
//	sprintf(mags, "%f", magct);
//	if(strcmp(mags, "nan") == 0) {
//		magct = cpl_table_get_double(tab, "MAG_BEST", *ctindex, NULL);
//	}

	if(debug == 1) {
		printf("XP : %f\n", xp);
		printf("YP : %f\n", yp);
		printf("XCT : %f\n", xct);
		printf("YCT : %f\n", yct);
		printf("MAGP : %f\n", magp);
		printf("MAGCT : %f\n", magct);
		printf("PA : %f\n", pact);
		printf("RE : %f\n", rect);
		printf("N : %f\n", nct);
		printf("AR : %f\n", arct);
	}

	// Calculate parameters

	r = sqrt(pow(xp - xct, 2) + pow(yp - yct, 2));
	ftot = pow(10., (-0.4*(magct-*magzero)))**exptime;
	kap = 2*nct - 1/3;
	f0 = ftot/(2*pi*pow(rect, 2.)*exp(kap)*nct*pow(kap, (-2.*nct))*gamma(2.*nct)*arct);

	if(debug == 1) {
		printf("kap : %f\n", kap);
		printf("r : %f\n", r);
		printf("ftot : %f\n", ftot);
		printf("f0 : %f\n", f0);
	}

	// Calculate relative position angle

	phi = rel_pos_ang(&xp, &yp, &xct, &yct, &pa);

	if(debug == 1) {
		printf("phi : %f\n", phi);
	}

	// Calculate flux at primary position

	flux = sersic_flux(&r, &phi, &arct, &f0, &rect, &nct);

	if(debug == 1) {
		printf("flux : %f\n", flux);
	}

	crit = -2.5*log10(flux);

	if(debug == 1) {
		printf("crit : %f\n", crit);
	}

	printf("In check_contribtarget(): Der MAGNITUDENBEITRAG des potentiellen Contrib Targets %ld "
			"crit fuer das Objekt %ld betraegt: %f\n", *ctindex + 1, *primindex + 1, crit);

	// Calculate magnitude difference

	magdiff = magct - magp;

	if(debug == 1) {
		printf("magdiff : %f\n", magdiff);
	}

	if(debug == 1) {
		printf("magexclude : %f\n", *magexclude);
		printf("magcrit : %f\n", *magcrit);
	}

//	if(debug == 1) {
		if(magdiff < *magexclude && crit < *magcrit) {
			printf("Object %ld hat Contrib test bestanden!\n", *ctindex);
		} else {
			printf("Object %ld ist beim Contrib test durchgefallen!\n",
					*ctindex);
		}
//	}

	if(magdiff < *magexclude && crit < *magcrit) {
		return 0;
	} else {
		return 1;
	}
}


int check_contribtarget_sexdata(cpl_table *tab, const long *primindex,
		const long *ctindex, const double *magzero, const double *exptime,
		const double *magexclude, const double *magcrit,
		const double *fluxextend) {

	int nrow, debug = 0;
	double xp = 0, yp = 0, xct = 0, yct = 0, r = 0, pa = 0, re = 0, n = 0,
			q = 0, ftot = 0, kap = 0, f0 = 0, magct = 0, phi = 0, flux = 0,
			crit = 0, magp = 0, magdiff = 0;
	double pi = 3.14159265;
	char ptile[FILENAME_MAX];
	char stile[FILENAME_MAX];

	/* Starting message */

	if(debug == 1) {
		cpl_msg_info(cpl_func, "Checking contrib targets for object with "
				"table index %ld", *primindex);
	}

	/* Check input */

	nrow = cpl_table_get_nrow(tab);

	if(nrow < 0) {
		return -1;
	}

	if(*exptime < 0 || *primindex < 0 || *ctindex < 0 || *primindex > nrow ||
			*ctindex > nrow) {
		return -1;
	}

	if(debug == 1) {
		printf("MAGZERO : %f\n", *magzero);
		printf("EXPTIME : %f\n", *exptime);
	}

	// Check if objects are on the same tile

	sprintf(ptile, "%s", cpl_table_get_string(tab, "TILE", *primindex));
	sprintf(stile, "%s", cpl_table_get_string(tab, "TILE", *ctindex));

	if(strcmp(ptile, stile) != 0) {
		return 1;
	}

	// Get primary data

	if(debug == 1) {
		printf("NUMBER PRIMARY : %d\n", cpl_table_get_int(tab, "NUMBER", *primindex, NULL));
		printf("NUMBER CONTRIB TARGET : %d\n", cpl_table_get_int(tab, "NUMBER", *ctindex, NULL));
	}

	xp    = cpl_table_get_double(tab, "X_IMAGE", *primindex, NULL);
	yp    = cpl_table_get_double(tab, "Y_IMAGE", *primindex, NULL);
	magp  = cpl_table_get_double(tab, "MAG_BEST", *primindex, NULL);

	// Get contrib target data

	xct   = cpl_table_get_double(tab, "X_IMAGE", *ctindex, NULL);
	yct   = cpl_table_get_double(tab, "Y_IMAGE",  *ctindex, NULL);
	pa = cpl_table_get_double(tab, "THETA_IMAGE", *ctindex, NULL);
	pa = pa - 90;

	re = cpl_table_get_double(tab, "FLUX_RADIUS", *ctindex, NULL);
	re = pow(re, *fluxextend);

	n = 2.5;

	q = 1 - cpl_table_get_double(tab, "ELLIPTICITY", *ctindex, NULL);

	magct = cpl_table_get_double(tab, "MAG_BEST", *ctindex, NULL);

	// Calculate parameters

	r = sqrt(pow(xp - xct, 2) + pow(yp - yct, 2));
	ftot = pow(10., (-0.4*(magct-*magzero)))**exptime;
	kap = 2*n - 1/3;
	f0 = ftot/(2*pi*pow(re, 2.)*exp(kap)*n*pow(kap, (-2.*n))*gamma(2.*n)*q);

	if(debug == 1) {
		printf("kap : %f\n", kap);
		printf("r : %f\n", r);
		printf("ftot : %f\n", ftot);
		printf("f0 : %f\n", f0);
	}

	// Calculate relative position angle

	phi = rel_pos_ang(&xp, &yp, &xct, &yct, &pa);

	if(debug == 1) {
		printf("phi : %f\n", phi);
	}

	// Calculate flux at primary position

	flux = sersic_flux(&r, &phi, &q, &f0, &re, &n);

	if(debug == 1) {
		printf("flux : %f\n", flux);
	}

	crit = -2.5*log10(flux);

	if(debug == 1) {
		printf("crit : %f\n", crit);
	}

	// Calculate magnitude difference

	magdiff = magct - magp;

	if(debug == 1) {
		printf("magdiff : %f\n", magdiff);
	}

	if(debug == 1) {
		printf("magexclude : %f\n", *magexclude);
		printf("magcrit : %f\n", *magcrit);
	}

	if(debug == 1) {
		if(magdiff < *magexclude && crit < *magcrit) {
			printf("Object %ld hat Contrib test bestanden!\n", *ctindex);
		} else {
			printf("Object %ld ist beim Contrib test durchgefallen!\n",
					*ctindex);
		}
	}

	if(magdiff < *magexclude && crit < *magcrit) {
		return 0;
	} else {
		return 1;
	}
}


cpl_error_code update_table_bulge_disc(cpl_table *tab, const char *galfitprefix) {

	int count, i, nrow;
	double xcgalfit, xcerrgalfit, ycgalfit, ycerrgalfit, maggalfit, magerrgalfit,
		regalfit, reerrgalfit, ngalfit, nerrgalfit, argalfit = 0, arerrgalfit = 0,
		elgalfit, pagalfit, paerrgalfit, chisq, chired, erval = 99999.;
	char imgblock[FILENAME_MAX];
	char directory[FILENAME_MAX];
	char xp[FILENAME_MAX];
	char yp[FILENAME_MAX];
	char mag[FILENAME_MAX];
	char re[FILENAME_MAX];
	char n[FILENAME_MAX];
	char ar[FILENAME_MAX];
	char pa[FILENAME_MAX];
	char *ptr;
	cpl_propertylist *header;


	// Check if table is valid

	nrow = cpl_table_get_nrow(tab);

	if(nrow < 0) {
		cpl_msg_error(cpl_func, "In update_table_bulge_disc(): "
				"Error with input table!");
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	// Add column for GALFIT flags

	if(cpl_table_has_column(tab, "FLAGS_GALFIT_BULGE_DISC") == 0) {
		cpl_table_new_column(tab, "FLAGS_GALFIT_BULGE_DISC", CPL_TYPE_STRING);
	}

	// Start update procedure

	for(i = 0; i < nrow; i++) {

		sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", i));
		sprintf(imgblock, "%s%s%s%d%s", directory, "/", galfitprefix, i + 1, "_2.fits");

		if(access(imgblock, 00) == 0) {

			// get results from output GALFIT image block header file

			header = cpl_propertylist_load(imgblock, 2);

			/* X_IMAGE components */

			sprintf(xp, "%s", cpl_propertylist_get_string(header, "2_XC"));
			remove_chr(xp);
			ptr = strtok(xp, " ");
			while(ptr != NULL) {
				if(count == 0) {
					xcgalfit = atof(ptr);
					cpl_table_set_double(tab, "X_C1_GALFIT", i, xcgalfit);
					}
				if(count == 2) {
					if(strncmp(ptr, "nan", 3) == 0 || strncmp(ptr, "*", 1) == 0) {
						cpl_table_set_double(tab, "X_C1_ERR_GALFIT", i, erval);
					} else {
						xcerrgalfit = atof(ptr);
						cpl_table_set_double(tab, "X_C1_ERR_GALFIT", i, xcerrgalfit);
					}
				}
				ptr = strtok(NULL, " ");
				count ++;
			}
			count = 0;

			sprintf(xp, "%s", cpl_propertylist_get_string(header, "3_XC"));
			remove_chr(xp);
			ptr = strtok(xp, " ");
			while(ptr != NULL) {
				if(count == 0) {
					xcgalfit = atof(ptr);
					cpl_table_set_double(tab, "X_C2_GALFIT", i, xcgalfit);
					}
				if(count == 2) {
					if(strncmp(ptr, "nan", 3) == 0 || strncmp(ptr, "*", 1) == 0) {
						cpl_table_set_double(tab, "X_C2_ERR_GALFIT", i, erval);
					} else {
						xcerrgalfit = atof(ptr);
						cpl_table_set_double(tab, "X_C2_ERR_GALFIT", i, xcerrgalfit);
					}
				}
				ptr = strtok(NULL, " ");
				count ++;
			}
			count = 0;

			/* Y_IMAGE components */

			sprintf(yp, "%s", cpl_propertylist_get_string(header, "2_YC"));
			remove_chr(yp);
			ptr = strtok(yp, " ");
			while(ptr != NULL) {
				if(count == 0) {
					ycgalfit = atof(ptr);
					cpl_table_set_double(tab, "Y_C1_GALFIT", i, ycgalfit);
				}
				if(count == 2) {
					if(strncmp(ptr, "nan", 3) == 0  || strncmp(ptr, "*", 1) == 0) {
						cpl_table_set_double(tab, "Y_C1_ERR_GALFIT", i, erval);
					} else {
						ycerrgalfit = atof(ptr);
						cpl_table_set_double(tab, "Y_C1_ERR_GALFIT", i, ycerrgalfit);
					}
				}
				ptr = strtok(NULL, " ");
				count ++;
			}
			count = 0;

			sprintf(yp, "%s", cpl_propertylist_get_string(header, "3_YC"));
			remove_chr(yp);
			ptr = strtok(yp, " ");
			while(ptr != NULL) {
				if(count == 0) {
					ycgalfit = atof(ptr);
					cpl_table_set_double(tab, "Y_C2_GALFIT", i, ycgalfit);
				}
				if(count == 2) {
					if(strncmp(ptr, "nan", 3) == 0  || strncmp(ptr, "*", 1) == 0) {
						cpl_table_set_double(tab, "Y_C2_ERR_GALFIT", i, erval);
					} else {
						ycerrgalfit = atof(ptr);
						cpl_table_set_double(tab, "Y_C2_ERR_GALFIT", i, ycerrgalfit);
					}
				}
				ptr = strtok(NULL, " ");
				count ++;
			}
			count = 0;

			/* Magnitudes */

			sprintf(mag, "%s", cpl_propertylist_get_string(header, "2_MAG"));
			remove_chr(mag);
			ptr = strtok(mag, " ");
			while(ptr != NULL) {
				if(count == 0) {
					maggalfit = atof(ptr);
					cpl_table_set_double(tab, "MAG_C1_GALFIT", i, maggalfit);
				}
				if(count == 2) {
					if(strncmp(ptr, "nan", 3) == 0 || strncmp(ptr, "*", 1) == 0) {
						cpl_table_set_double(tab, "MAG_C1_ERR_GALFIT", i, erval);
					} else {
						magerrgalfit = atof(ptr);
						cpl_table_set_double(tab, "MAG_C1_ERR_GALFIT", i, magerrgalfit);
					}
				}
				ptr = strtok(NULL, " ");
				count ++;
			}
			count = 0;

			sprintf(mag, "%s", cpl_propertylist_get_string(header, "3_MAG"));
			remove_chr(mag);
			ptr = strtok(mag, " ");
			while(ptr != NULL) {
				if(count == 0) {
					maggalfit = atof(ptr);
					cpl_table_set_double(tab, "MAG_C2_GALFIT", i, maggalfit);
				}
				if(count == 2) {
					if(strncmp(ptr, "nan", 3) == 0 || strncmp(ptr, "*", 1) == 0) {
						cpl_table_set_double(tab, "MAG_C2_ERR_GALFIT", i, erval);
					} else {
						magerrgalfit = atof(ptr);
						cpl_table_set_double(tab, "MAG_C2_ERR_GALFIT", i, magerrgalfit);
					}
				}
				ptr = strtok(NULL, " ");
				count ++;
			}
			count = 0;

			/* Half-light radii */

			sprintf(re, "%s", cpl_propertylist_get_string(header, "2_RE"));
			remove_chr(re);
			ptr = strtok(re, " ");
			while(ptr != NULL) {
				if(count == 0) {
					regalfit = atof(ptr);
					cpl_table_set_double(tab, "RE_C1_GALFIT", i, regalfit);
				}
				if(count == 2) {
					if(strncmp(ptr, "nan", 3) == 0 || strncmp(ptr, "*", 1) == 0) {
						cpl_table_set_double(tab, "RE_C1_ERR_GALFIT", i, erval);
					} else {
						reerrgalfit = atof(ptr);
						cpl_table_set_double(tab, "RE_C1_ERR_GALFIT", i, reerrgalfit);
					}
				}
				ptr = strtok(NULL, " ");
				count ++;
			}
			count = 0;

			sprintf(re, "%s", cpl_propertylist_get_string(header, "3_RE"));
			remove_chr(re);
			ptr = strtok(re, " ");
			while(ptr != NULL) {
				if(count == 0) {
					regalfit = atof(ptr);
					cpl_table_set_double(tab, "RE_C2_GALFIT", i, regalfit);
				}
				if(count == 2) {
					if(strncmp(ptr, "nan", 3) == 0 || strncmp(ptr, "*", 1) == 0) {
						cpl_table_set_double(tab, "RE_C2_ERR_GALFIT", i, erval);
					} else {
						reerrgalfit = atof(ptr);
						cpl_table_set_double(tab, "RE_C2_ERR_GALFIT", i, reerrgalfit);
					}
				}
				ptr = strtok(NULL, " ");
				count ++;
			}
			count = 0;

			/* Sersics */

			sprintf(n, "%s", cpl_propertylist_get_string(header, "2_N"));
			remove_chr(n);
			ptr = strtok(n, " ");
			while(ptr != NULL) {
				if(count == 0) {
					ngalfit = atof(ptr);
					cpl_table_set_double(tab, "SERSIC_C1_GALFIT", i, ngalfit);
				}
				if(count == 2) {
					if(strncmp(ptr, "nan", 3) == 0 || strncmp(ptr, "*", 1) == 0) {
						cpl_table_set_double(tab, "SERSIC_C1_ERR_GALFIT", i, erval);
					} else {
						nerrgalfit = atof(ptr);
						cpl_table_set_double(tab, "SERSIC_C1_ERR_GALFIT", i, nerrgalfit);
					}
				}
				ptr = strtok(NULL, " ");
				count ++;
			}
			count = 0;

			sprintf(n, "%s", cpl_propertylist_get_string(header, "3_N"));
			remove_chr(n);
			ptr = strtok(n, " ");
			while(ptr != NULL) {
				if(count == 0) {
					ngalfit = atof(ptr);
					cpl_table_set_double(tab, "SERSIC_C2_GALFIT", i, ngalfit);
				}
				if(count == 2) {
					if(strncmp(ptr, "nan", 3) == 0 || strncmp(ptr, "*", 1) == 0) {
						cpl_table_set_double(tab, "SERSIC_C2_ERR_GALFIT", i, erval);
					} else {
						nerrgalfit = atof(ptr);
						cpl_table_set_double(tab, "SERSIC_C2_ERR_GALFIT", i, nerrgalfit);
					}
				}
				ptr = strtok(NULL, " ");
				count ++;
			}
			count = 0;

			/* Axis ratio */

			sprintf(ar, "%s", cpl_propertylist_get_string(header, "2_AR"));
			remove_chr(ar);
			ptr = strtok(ar, " ");
			while(ptr != NULL) {
				if(count == 0) {
					argalfit = atof(ptr);
					cpl_table_set_double(tab, "AR_C1_GALFIT", i, argalfit);
				}
				if(count == 2) {
					if(strncmp(ptr, "nan", 3) == 0 || strncmp(ptr, "*", 1) == 0) {
						cpl_table_set_double(tab, "AR_C1_ERR_GALFIT", i, erval);
					} else {
						arerrgalfit = atof(ptr);
						cpl_table_set_double(tab, "AR_C1_ERR_GALFIT", i, arerrgalfit);
					}
				}
				ptr = strtok(NULL, " ");
				count ++;
			}
			count = 0;

			/* Ellipticity */

			elgalfit = 1 - argalfit;
			cpl_table_set_double(tab, "ELLIPTICITY_C1_GALFIT", i, elgalfit);
			cpl_table_set_double(tab, "ELLIPTICITY_C1_ERR_GALFIT", i, arerrgalfit);

			/* Axis ratio */

			sprintf(ar, "%s", cpl_propertylist_get_string(header, "3_AR"));
			remove_chr(ar);
			ptr = strtok(ar, " ");
			while(ptr != NULL) {
				if(count == 0) {
					argalfit = atof(ptr);
					cpl_table_set_double(tab, "AR_C2_GALFIT", i, argalfit);
				}
				if(count == 2) {
					if(strncmp(ptr, "nan", 3) == 0 || strncmp(ptr, "*", 1) == 0) {
						cpl_table_set_double(tab, "AR_C2_ERR_GALFIT", i, erval);
					} else {
						arerrgalfit = atof(ptr);
						cpl_table_set_double(tab, "AR_C2_ERR_GALFIT", i, arerrgalfit);
					}
				}
				ptr = strtok(NULL, " ");
				count ++;
			}
			count = 0;

			/* Ellipticity */

			elgalfit = 1 - argalfit;
			cpl_table_set_double(tab, "ELLIPTICITY_C2_GALFIT", i, elgalfit);
			cpl_table_set_double(tab, "ELLIPTICITY_C2_ERR_GALFIT", i, arerrgalfit);

			/* Position angle */

			sprintf(pa, "%s", cpl_propertylist_get_string(header, "2_PA"));
			remove_chr(pa);
			ptr = strtok(pa, " ");
			while(ptr != NULL) {
				if(count == 0) {
					pagalfit = atof(ptr);
					cpl_table_set_double(tab, "PA_C1_GALFIT", i, pagalfit);
				}
				if(count == 2) {
					if(strncmp(ptr, "nan", 3) == 0 || strncmp(ptr, "*", 1) == 0) {
						cpl_table_set_double(tab, "PA_C1_ERR_GALFIT", i, erval);
					} else {
						paerrgalfit = atof(ptr);
						cpl_table_set_double(tab, "PA_C1_ERR_GALFIT", i, paerrgalfit);
					}
				}
				ptr = strtok(NULL, " ");
				count ++;
			}
			count = 0;

			sprintf(pa, "%s", cpl_propertylist_get_string(header, "3_PA"));
			remove_chr(pa);
			ptr = strtok(pa, " ");
			while(ptr != NULL) {
				if(count == 0) {
					pagalfit = atof(ptr);
					cpl_table_set_double(tab, "PA_C2_GALFIT", i, pagalfit);
				}
				if(count == 2) {
					if(strncmp(ptr, "nan", 3) == 0 || strncmp(ptr, "*", 1) == 0) {
						cpl_table_set_double(tab, "PA_C2_ERR_GALFIT", i, erval);
					} else {
						paerrgalfit = atof(ptr);
						cpl_table_set_double(tab, "PA_C2_ERR_GALFIT", i, paerrgalfit);
					}
				}
				ptr = strtok(NULL, " ");
				count ++;
			}
			count = 0;

			/* Chi^2 and chi^2 nu */

			chisq = cpl_propertylist_get_double(header, "CHISQ");
			cpl_table_set_double(tab, "CHISQ_BULGE_DISC_GALFIT", i, chisq);

			chired = cpl_propertylist_get_double(header, "CHI2NU");
			cpl_table_set_double(tab, "CHI2NU_BULGE_DISC_GALFIT", i, chired);

			// Flag every row which has been treated by GALFIT now as "Fit done"
			// with index 1
			// This is necessary for preparing the GALFIT setup file with
			// secondaries which have an existing fit or not

			flag_table_bulge_disc(tab, i, header);

			cpl_propertylist_delete(header);

		} else {

			cpl_msg_error(cpl_func, "In update_table_bulge_disc(): "
				"Fitfile %s was not found. GALFIT possibly crashed "
				"for this object.", imgblock);

			cpl_table_set_double(tab, "X_C1_GALFIT", i, erval);
			cpl_table_set_double(tab, "Y_C1_GALFIT", i, erval);
			cpl_table_set_double(tab, "X_C2_GALFIT", i, erval);
			cpl_table_set_double(tab, "Y_C2_GALFIT", i, erval);
			cpl_table_set_double(tab, "MAG_C1_GALFIT", i, erval);
			cpl_table_set_double(tab, "MAG_C2_GALFIT", i, erval);
			cpl_table_set_double(tab, "RE_C1_GALFIT", i, erval);
			cpl_table_set_double(tab, "RE_C2_GALFIT", i, erval);
			cpl_table_set_double(tab, "SERSIC_C1_GALFIT", i, erval);
			cpl_table_set_double(tab, "SERSIC_C2_GALFIT", i, erval);
			cpl_table_set_double(tab, "AR_C1_GALFIT", i, erval);
			cpl_table_set_double(tab, "AR_C2_GALFIT", i, erval);
			cpl_table_set_double(tab, "ELLIPICITY_C1_GALFIT", i, erval);
			cpl_table_set_double(tab, "ELLIPTICITY_C2_GALFIT", i, erval);
			cpl_table_set_double(tab, "PA_C1_GALFIT", i, erval);
			cpl_table_set_double(tab, "PA_C2_GALFIT", i, erval);

			cpl_table_set_double(tab, "X_C1_ERR_GALFIT", i, erval);
			cpl_table_set_double(tab, "Y_C1_ERR_GALFIT", i, erval);
			cpl_table_set_double(tab, "X_C2_ERR_GALFIT", i, erval);
			cpl_table_set_double(tab, "Y_C2_ERR_GALFIT", i, erval);
			cpl_table_set_double(tab, "MAG_C1_ERR_GALFIT", i, erval);
			cpl_table_set_double(tab, "MAG_C_ERR2_GALFIT", i, erval);
			cpl_table_set_double(tab, "RE_C1_ERR_GALFIT", i, erval);
			cpl_table_set_double(tab, "RE_C2_ERR_GALFIT", i, erval);
			cpl_table_set_double(tab, "SERSIC_C1_ERR_GALFIT", i, erval);
			cpl_table_set_double(tab, "SERSIC_C1_ERR_GALFIT", i, erval);
			cpl_table_set_double(tab, "AR_C1_ERR_GALFIT", i, erval);
			cpl_table_set_double(tab, "AR_C2_ERR_GALFIT", i, erval);
			cpl_table_set_double(tab, "ELLIPICITY_C1_ERR_GALFIT", i, erval);
			cpl_table_set_double(tab, "ELLIPTICITY_C1_ERR_GALFIT", i, erval);
			cpl_table_set_double(tab, "PA_C1_ERR_GALFIT", i, erval);
			cpl_table_set_double(tab, "PA_C2_ERR_GALFIT", i, erval);

			cpl_table_set_double(tab, "CHISQ_BULGE_DISC_GALFIT", i, erval);
			cpl_table_set_double(tab, "CHI2NU_BULGE_DISC_GALFIT", i, erval);
		}
	}

	return CPL_ERROR_NONE;
}


cpl_error_code flag_table_bulge_disc(cpl_table *tab, int i, cpl_propertylist *header) {

	int galfitflag = 0;
	char flagstring[FILENAME_MAX];
	char *ptr;

	if(cpl_table_has_column(tab, "FLAGS_GALFIT_BULGE_DISC") == 0) {
		cpl_table_new_column(tab, "FLAGS_GALFIT_BULGE_DISC", CPL_TYPE_STRING);
	}

	if(cpl_propertylist_has(header, "FLAGS") != 1) {
		cpl_table_set_string(tab, "FLAGS_GALFIT", i, "NONE");
		return CPL_ERROR_NONE;
	}

	sprintf(flagstring, "%s", cpl_propertylist_get_string(header, "FLAGS"));

	ptr = strtok(flagstring, " ");

	while(ptr != NULL) {

		if(strcmp(ptr, "1") == 0) {

			galfitflag = 1;

		}

		if(strcmp(ptr, "2") == 0) {

			galfitflag += 2;

		}

		ptr = strtok(NULL, " ");
	}

	if(galfitflag == 0) {

		cpl_table_set_string(tab, "FLAGS_GALFIT", i, "GOOD");

	}

	if(galfitflag == 1) {

		cpl_table_set_string(tab, "FLAGS_GALFIT", i, "1");

	}

	if(galfitflag == 2) {

		cpl_table_set_string(tab, "FLAGS_GALFIT", i, "2");

	}

	if(galfitflag == 3) {

		cpl_table_set_string(tab, "FLAGS_GALFIT", i, "3");

	}

	return CPL_ERROR_NONE;
}


cpl_error_code create_constraintfile_bulge_disc(const char *constraintfile_bd,
		const double *re_max, const double *mag_min, const double *mag_max,
		cpl_table *tab, const long *i) {

	int a = 0, lv, xstamp, ystamp, xstampsec, ystampsec, component,
		row, nsec = 0, secsize, k, ctsize, debug = 0, one = 1;
	long secidx = 0, ctidx, e;
	FILE *fp;
	const cpl_array *help;
	cpl_array *secindices,
			  *ctindices,
			  *secondary;


	// Check input

	row = cpl_table_get_nrow(tab);

	if(row <= 0) {
		cpl_msg_error(cpl_func, "In create_constraintfile() : "
				"Tab is empty or not accessable!!! Aborting...");
	}

	// get stamp sizes

	xstamp = cpl_table_get_int(tab, "STAMP_XHI", *i, NULL) -
			cpl_table_get_int(tab, "STAMP_XLO", *i, NULL);
	ystamp = cpl_table_get_int(tab, "STAMP_YHI", *i, NULL) -
			cpl_table_get_int(tab, "STAMP_YLO", *i, NULL);

	// Check number of secondaries

	help = cpl_table_get_array(tab, "SECONDARY_INDICES", *i);

	secindices = cpl_array_duplicate(help);

	secsize = cpl_array_get_size(secindices);

	for(k = 0; k < secsize; k++) {
		secidx = (long)cpl_array_get(secindices, k, NULL);
		if(secidx >= 0) {
			nsec++;
		}
	}

	help = cpl_table_get_array(tab, "POT_CT_INDICES", *i);

	ctindices = cpl_array_duplicate(help);

	ctsize = cpl_array_get_size(ctindices);

	for(k = 0; k < ctsize; k++) {
		ctidx = (long)cpl_array_get(ctindices, k, NULL);
		if(ctidx >= 0) {
			nsec++;
		}
	}

	// New array for all secondaries incl contrib targets

	secondary = cpl_array_new(nsec, CPL_TYPE_INT);

	for(k = 0; k < secsize; k++) {
		secidx = (long)cpl_array_get(secindices, k, NULL);
		if(secidx >= 0) {
			cpl_array_set(secondary, a, secidx);
			a++;
		}
	}

	for(k = 0; k < ctsize; k++) {
		ctidx = (long)cpl_array_get(ctindices, k, NULL);
		if(secidx >= 0) {
			cpl_array_set(secondary, a, ctidx);
			a++;
		}
	}

	// write constraint file

	fp = fopen(constraintfile_bd, "w");

	fprintf(fp, "# Component/    parameter   constraint  Comment\n# operation"
			"                  values\n");
	fprintf(fp, "           2 n 0.2 to 8\n           2 re 0.3 to %.3f\n"
			"           2 q 0.0001  to 1.\n           2 mag %.3f %.3f\n"
			"           2 mag 0 to 40\n           2 pa -360 to 360\n           "
			"2 x         -%d          %d\n           2 y         -%d          "
			"%d\n", *re_max, *mag_min, *mag_max, xstamp, xstamp, ystamp, ystamp);

	fprintf(fp, "# Component/    parameter   constraint  Comment\n# operation"
			"                  values\n");
	fprintf(fp, "           3 n 0.2 to 8\n           3 re 0.3 to %.3f\n"
			"           3 q 0.0001  to 1.\n           3 mag %.3f %.3f\n"
			"           3 mag 0 to 40\n           3 pa -360 to 360\n           "
			"3 x         %d          %d\n           3 y         %d          "
			"%d\n", *re_max, *mag_min, *mag_max, one, xstamp, one, ystamp);

	// attach constraints for secondaries

	for(lv = 0; lv < nsec; lv++) {
		component = 4 + lv;
		e = cpl_array_get(secondary, lv, NULL) - 1;

		if(e >= 0) {

			xstampsec = cpl_table_get_int(tab, "STAMP_XHI", e, NULL) -
					cpl_table_get_int(tab, "STAMP_XLO", e, NULL);
			ystampsec = cpl_table_get_int(tab, "STAMP_YHI", e, NULL) -
					cpl_table_get_int(tab, "STAMP_YLO", e, NULL);
			fprintf(fp, "           %d n 0.2 to 8\n"
					"           %d re 0.3 to %.3f\n"
					"           %d q 0.0001  to 1.\n"
					"           %d mag %.3f %.3f\n"
					"           %d mag 0 to 40\n"
					"           %d pa -360 to 360\n"
					"           %d x         -%d          %d\n"
					"           %d y         -%d          %d\n",
					component, component, *re_max, component, component,
					*mag_min, *mag_max, component, component, component,
					100*xstampsec, 100*xstampsec, component, 100*ystampsec,
					100*ystampsec);
		} else {
			if(debug == 1) {
				cpl_msg_error(cpl_func, "Internal error in "
					"create_constraintfile(). Constraints for secondary "
					"not written correctly.");
			}
		}
	}

	fclose(fp);

	cpl_array_delete(secondary);
	cpl_array_delete(secindices);
	cpl_array_delete(ctindices);

	return CPL_ERROR_NONE;
}

cpl_error_code quantify_residuals(cpl_table *tab, const char *object) {

	long i,
		 nrow;

	double res_sersic,
		   res_2comp;

	char sersic[FILENAME_MAX] = "SERSIC",
	     bd[FILENAME_MAX] = "2_COMPONENTS";


	/* Check input */

	nrow = (long)cpl_table_get_nrow(tab);

	if(nrow <= 0) {
		cpl_msg_error(cpl_func, "Table loaded by slave in "
				"run_GALFIT_parallel() is not found or empty!");

		return CPL_ERROR_DATA_NOT_FOUND;
	}

	if(cpl_table_has_column(tab, "RESIDUAL_SERSIC") != 1) {
		cpl_msg_error(cpl_func, "An internal error occurred in "
				"quantify_residuals(). The column RESIDUAL_SERSIC "
				"did not exist yet! Check if previous bulge_disc runs "
				"are correct.");
		cpl_table_new_column(tab, "RESIDUAL_SERSIC", CPL_TYPE_DOUBLE);
	}

	if(cpl_table_has_column(tab, "RESIDUAL_2COMP") != 1) {
		cpl_msg_error(cpl_func, "An internal error occurred in "
				"quantify_residuals(). The column RESIDUAL_SERSIC "
				"did not exist yet! Check if previous bulge_disc runs "
				"are correct.");
		cpl_table_new_column(tab, "RESIDUAL_2COMP", CPL_TYPE_DOUBLE);
	}

	if(cpl_table_has_column(tab, "GALAXY_TYPE") != 1) {
		cpl_msg_error(cpl_func, "An internal error occurred in "
				"quantify_residuals(). The column RESIDUAL_SERSIC "
				"did not exist yet! Check if previous bulge_disc runs "
				"are correct.");
		cpl_table_new_column(tab, "GALAXY_TYPE", CPL_TYPE_STRING);
	}

	/* Check every object */

	for(i = 0; i < nrow; i++) {

		/* Measure Sersic residual*/

		res_sersic = check_sersic_residual(tab, &i, object);

		/* Measure 2 component residual*/

		res_2comp = check_2_component_residual(tab, &i, object);

		/* Write result into table */

		cpl_table_set_double(tab, "RESIDUAL_SERSIC", i, res_sersic);
		cpl_table_set_double(tab, "RESIDUAL_2COMP", i, res_2comp);

		if(res_sersic <= res_2comp) {
			cpl_table_set_string(tab, "GALAXY_TYPE", i, sersic);
		} else {
			cpl_table_set_string(tab, "GALAXY_TYPE", i, bd);
		}
	}

	return CPL_ERROR_NONE;
}


double check_sersic_residual(cpl_table *tab, const long *i,
		const char *object) {

	int x, y, xsize, ysize, qq = 99, debug = 0;

	long npix = 0;

	double xc, yc, aim, bim, theta, cxx, cxy, cyy, pix, sum = 0;

	double pi = 3.14159265;

	char objectfile[FILENAME_MAX];

	cpl_image *residual;

	double val = 0;


	/* Prepare residual map filename */

	sprintf(objectfile, "%s%s%s%ld%s",
			cpl_table_get_string(tab, "TILE_DIRECTORY", *i), "/",
			object, *i + 1, ".fits");

	/* Check if accessable */

	if(access(objectfile, 00) == 0) {

		/* Load residual map */

		residual = cpl_image_load(objectfile, CPL_TYPE_DOUBLE, 0, 3);

		/* Get residual map size */

		xsize = cpl_image_get_size_x(residual);
		ysize = cpl_image_get_size_y(residual);

		/* Check if residual map is valid */

		if(xsize != -1) {

			/* Get residual data */

			xc = cpl_table_get_int(tab, "STAMP_XHI", *i, NULL) -
				cpl_table_get_double(tab, "X_IMAGE", *i, NULL) + 0.5;

			yc = cpl_table_get_int(tab, "STAMP_YHI", *i, NULL) -
				cpl_table_get_double(tab, "Y_IMAGE", *i, NULL) + 0.5;

			aim = cpl_table_get_double(tab, "A_IMAGE", *i, NULL) *
				cpl_table_get_double(tab, "KRON_RADIUS", *i, NULL);

			bim = cpl_table_get_double(tab, "B_IMAGE", *i, NULL) *
				cpl_table_get_double(tab, "KRON_RADIUS", *i, NULL);

			theta = cpl_table_get_double(tab, "THETA_IMAGE", *i, NULL);

			theta = 2 * pi * theta / 360;

			/* Calculate inner ellipse parameters */

			cxx = (pow(cos(theta), 2)) / pow(aim, 2) +
				(pow(sin(theta), 2)) / pow(bim, 2);
			cyy = (pow(sin(theta), 2)) / pow(aim, 2) +
				(pow(cos(theta), 2)) / pow(bim, 2);
			cxy = 2 * cos(theta) * sin(theta) *
				(1 / pow(aim, 2) - 1 / pow(bim, 2));

			/* Sum up pixels in the ellipse */

			for(x = 1; x <= xsize; x++) {
				for(y = 1; y <= ysize; y++) {

					if(cxx * ((x - xc) * (x - xc)) + cyy * ((y - yc) *
						(y - yc)) + cxy * (x - xc) * (y - yc) < 1) {

						pix = cpl_image_get(residual, x, y, &qq);

						sum += fabs(pix);

						npix++;
					}
				}
			}

			if(debug == 1) {
				printf("SUM : %f\n", sum);
				printf("NPIX : %ld\n", npix);
			}

			/* IMPORTANT : Normalize value per pixel */

			val = sum / npix;

			if(debug == 1) {
				printf("VALUE PER PIXEL : %f\n", val);
			}
		} else {
			val = 99999.;
		}

		cpl_image_delete(residual);

	} else {
		cpl_msg_error(cpl_func, "GALFIT object %s was not accessable! "
				"Possibly GALFIT crashed for this object.",
				objectfile);
		val = 99999.;
	}

	return val;
}


double check_2_component_residual(cpl_table *tab, const long *i,
		const char *object) {

	int x, y, xsize, ysize, qq = 99, debug = 0;

	long npix = 0;

	double xc, yc, aim, bim, theta, cxx, cxy, cyy, pix, sum = 0;

	double pi = 3.14159265;

	char objectfile[FILENAME_MAX];

	cpl_image *residual;

	double val = 0;


	/* Prepare residual map filename */

	sprintf(objectfile, "%s%s%s%ld%s",
			cpl_table_get_string(tab, "TILE_DIRECTORY", *i), "/",
			object, *i + 1, "_2.fits");

	/* Check if accessable */

	if(access(objectfile, 00) == 0) {

		/* Load residual map */

		residual = cpl_image_load(objectfile, CPL_TYPE_DOUBLE, 0, 3);

		/* Get residual map size */

		xsize = cpl_image_get_size_x(residual);
		ysize = cpl_image_get_size_y(residual);

		/* Check if residual map is valid */

		if(xsize != -1) {

			/* Get residual data */

			xc = cpl_table_get_int(tab, "STAMP_XHI", *i, NULL) -
				cpl_table_get_double(tab, "X_IMAGE", *i, NULL) + 0.5;

			yc = cpl_table_get_int(tab, "STAMP_YHI", *i, NULL) -
				cpl_table_get_double(tab, "Y_IMAGE", *i, NULL) + 0.5;

			aim = cpl_table_get_double(tab, "A_IMAGE", *i, NULL) *
				cpl_table_get_double(tab, "KRON_RADIUS", *i, NULL);

			bim = cpl_table_get_double(tab, "B_IMAGE", *i, NULL) *
				cpl_table_get_double(tab, "KRON_RADIUS", *i, NULL);

			theta = cpl_table_get_double(tab, "THETA_IMAGE", *i, NULL);

			theta = 2 * pi * theta / 360;

			/* Calculate inner ellipse parameters */

			cxx = (pow(cos(theta), 2)) / pow(aim, 2) +
				(pow(sin(theta), 2)) / pow(bim, 2);
			cyy = (pow(sin(theta), 2)) / pow(aim, 2) +
				(pow(cos(theta), 2)) / pow(bim, 2);
			cxy = 2 * cos(theta) * sin(theta) *
				(1 / pow(aim, 2) - 1 / pow(bim, 2));

			/* Sum up pixels in the ellipse */

			for(x = 1; x <= xsize; x++) {
				for(y = 1; y <= ysize; y++) {

					if(cxx * ((x - xc) * (x - xc)) + cyy * ((y - yc) *
						(y - yc)) + cxy * (x - xc) * (y - yc) < 1) {

						pix = cpl_image_get(residual, x, y, &qq);

						sum += fabs(pix);

						npix++;
					}
				}
			}

			if(debug == 1) {
				printf("SUM : %f\n", sum);
				printf("NPIX : %ld\n", npix);
			}

			/* IMPORTANT : Normalize value per pixel */

			val = sum / npix;

			if(debug == 1) {
				printf("VALUE PER PIXEL : %f\n", val);
			}
		} else {
			val = 99999.;
		}
		cpl_image_delete(residual);

	} else {
		cpl_msg_error(cpl_func, "GALFIT object %s was not accessable! "
				"Possibly GALFIT crashed for this object.",
				objectfile);
		val = 99999.;
	}

	return val;
}


/*********************************************************************
 * Run 3 component fitting with more Sérsic components
 **********************************************************************/

cpl_error_code run_3comp_fitting(cpl_parameterlist *gala_setup) {

	int numprocs = 0,
		rank = 0,
		debug = 1,
		synch = 0,
		slaverank,
		k,
		ncomponents;

	long j = 0,
		 nrow;

	char tabfile[FILENAME_MAX],
		 outdir[FILENAME_MAX],
		 combcatname[FILENAME_MAX],
		 object[FILENAME_MAX],
		 imgblock_bd[FILENAME_MAX],
		 galfitset[FILENAME_MAX],
		 str[FILENAME_MAX],
		 directory[FILENAME_MAX],
		 constraints[FILENAME_MAX],
		 galsetfile[FILENAME_MAX],
		 path[FILENAME_MAX];

	cpl_table *tab;

	cpl_parameter *p;

	MPI_Status status;

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	/* find out number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	/* Load variables from setup parameterlist */

    p = cpl_parameterlist_find(gala_setup, "outdir");
    sprintf(outdir, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "sexcomb");
    sprintf(combcatname, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "object");
    sprintf(object, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "constraints");
    sprintf(constraints, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "path");
    sprintf(path, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "galfitset");
    sprintf(galfitset, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "ncomponents");
    ncomponents = (int)cpl_parameter_get_double(p);

    if(debug == 1) {
    	printf("NCOMPONENTS in run_3comp_fitting: %d\n", ncomponents);
    }


    /* MASTER job */

    if(rank == 0) {

    	/* Prepare path variable for loading table */

    	sprintf(tabfile, "%s%s%s", outdir, "/", combcatname);

    	if(access(tabfile, 00) != 0) {
    		cpl_msg_error(cpl_func, "Tabfile %s is not accessable in "
    				"3 component_fitting(). Aborting...", tabfile);
    		return CPL_ERROR_DATA_NOT_FOUND;
    	}

    	/* Load combined GALAPAGOS catalog */

    	tab = cpl_table_load(tabfile, 1, 0);

    	/* Check table */

    	nrow = (long)cpl_table_get_nrow(tab);

    	printf("MASTER : Habe table mit %ld rows geladen!\n", nrow);

    	if(nrow <= 0){
    		cpl_msg_error(cpl_func, "Table %s is empty or not accessable "
    				"in run_3comp_fitting(). Aborting...", tabfile);
    		return CPL_ERROR_DATA_NOT_FOUND;
		}

        /* Starting message */

    	cpl_msg_info(cpl_func, "Starting GALFIT 3 component fitting for "
    			"%ld objects.", nrow);

    	cpl_table_delete(tab);

    	/* Send jobs to slaves */

    	for(j = 0; j < nrow; j++) {

    		/* Receive a message from slave who needs a job */

    		if(debug == 1) {
    			printf("MASTER im for - LOOP : Warte auf Nachrichten von "
    				"den Slaves !!!\n");
    		}

    		MPI_Recv(&slaverank, sizeof(int), MPI_INT, MPI_ANY_SOURCE,
    								51, MPI_COMM_WORLD, &status);

    		if(debug == 1) {
    			printf("MASTER im for - LOOP : Habe folgende Nachricht von "
    				"einem Slave erhalten : %d\n", slaverank);
    		}

			/* Send job to the slave */

			printf("\nMASTER : Bin in Loop Nummer %ld und sende "
				"job %ld an den Slave %d.\n\n\n", j, j, slaverank);


			MPI_Send(&j, sizeof(long), MPI_INT, slaverank, 52,
					MPI_COMM_WORLD);

    	}

    	/* Termination message */

    	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    	for(k = 1; k < numprocs; k++) {

    		j = -1;

			/* Send job to the slave */

			printf("\nMASTER : Send nun die ending message an den slave"
					"%d.\n\n\n", k);

    		MPI_Send(&j, sizeof(long), MPI_INT, k, 52, MPI_COMM_WORLD);
    	}

    /* Slave job */

    } else {

		/* Load table and check size*/

		sprintf(tabfile, "%s%s%s", outdir, "/", combcatname);

		if(access(tabfile, 00) == 0) {

			tab = cpl_table_load(tabfile, 1, 0);

			nrow = (long)cpl_table_get_nrow(tab);

			if(nrow <= 0) {
				cpl_msg_error(cpl_func, "Table loaded by slave %d in "
						"run_3comp_fitting() is not found or empty!",
						rank);

				printf("Der aktuelle Wert von j ist : %ld\n", j);

				return CPL_ERROR_DATA_NOT_FOUND;
			}

		} else {
			cpl_msg_error(cpl_func, "Table file not accessable by "
					"slave in run_3comp_fitting()!");

			return CPL_ERROR_DATA_NOT_FOUND;
		}

		/* Receive job as long as MASTER sends */

    	while (j != -1) {

    		/* Find out process rank */

    		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    		/* Send a message to MASTER that slave needs a job */

    		MPI_Send(&rank, sizeof(int), MPI_INT, 0, 51, MPI_COMM_WORLD);

    		if(debug == 1) {
    			printf("SLAVE %d: Habe meinen rank zurueckgesendet!\n", rank);
    			printf("SLAVE %d: Warte jetzt auf eine Nachricht vom MASTER!\n", rank);
    		}

    		/* Receive job ID for MASTER */

    		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    		MPI_Recv(&j, sizeof(long), MPI_INT, 0, 52, MPI_COMM_WORLD, &status);

    		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    		if(debug == 1) {
    			printf("Slave %d hat einen Jobauftrag empfangen : Job Nummer %ld\n", rank, j);
    		}

    		/* If MASTER did not send termination message start GALFIT procedure */

    		if(j != -1) {

				/* Identify GALFIT output path */

				sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", j));
				sprintf(imgblock_bd, "%s%s%s%ld%s", directory, "/", object, j + 1, "_3.fits");

				/* Do GALFIT procedure only if imagebloc ist not existing yet */

				if(access(imgblock_bd, 00) != 0) {

					/* Check if constraints should be used */

//    				if(strcmp(constraints, "n") != 0 &&
//    						strcmp(constraints, "no") != 0 &&
//    						strcmp(constraints, "none") != 0) {
//
//    					/* Check if constraintfile is existing - only if not create */
//
//    					sprintf(constraintfile_bd, "%s%s%s%s%ld%s", directory, "/",
//    							constraints, "_", j + 1, "_3");
//
//    					if(create_constraintfile_bulge_disc(constraintfile_bd, &re_max,
//    							&mag_min, &mag_max, tab, &j) != CPL_ERROR_NONE) {
//    						cpl_msg_error(cpl_func,
//    								"create_constraintfile_bulge_disc() failed!");
//    					}
//    				}

					/* Create bulge-disc GALFIT setup files with two components */

					if(create_3comp_setup(gala_setup, &j) != CPL_ERROR_NONE) {
						cpl_msg_error(cpl_func,
								"create_3comp_setup() failed!");
					}

    				if(debug == 1) {
    					printf("GALFIT 3 component setup created for OBJECT %ld !\n", j);
    				}

    				/* Prepare GALFIT string */

        			sprintf(galsetfile, "%s%s%s%s%ld%s", directory, "/", galfitset,
        						"_", j + 1, "_3");

    				sprintf(str, "%s %s %s", path, galsetfile, "> /dev/null");

    				if(debug == 1) {
    					cpl_msg_info(cpl_func, "Slave %d is running GALFIT with %s.", rank, str);
    				}

    				/* Start GALFIT */

					if(system(str) != 0) {
						cpl_msg_error(cpl_func, "In run_3comp_fitting(): System call "
								"return value which is not 0. What does that mean?");
    				}
				}
    		}
		}

    	/* Clean up */

    	cpl_table_delete(tab);
    }

	/* Go on when all slaves have finished their jobs */

    if(rank == 0) {
    	printf("MASTER: Warte auf Nachrichten von den Slaves dass "
			"alle ihre Jobs beendet haben!\n");
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

	/* Go on when all slaves have finished their jobs */

//    if(rank == 0) {
//    	printf("MASTER: Alle slaves sind da. Jobs beendet!\n");
//
//    	/* Add results and remove helpfiles */
//
//    	tab = cpl_table_load(tabfile, 1, 0);
//
//    	/* Add results from previous fit to table and save*/
//
//    	if(update_table_3comp(tab, object) != CPL_ERROR_NONE) {
//    		cpl_msg_error(cpl_func, "update_table_bulge_disc() failed.");
//    	}
//
//    	if(quantify_residuals(tab, object) != CPL_ERROR_NONE) {
//    		cpl_msg_error(cpl_func, "quantify_residuals() failed.");
//    	}
//
//		cpl_table_save(tab, NULL, NULL, tabfile, CPL_IO_CREATE);
//
//		printf("\nMASTER : TABLE gepeichert!!!!.\n");
//
//		/* Clean up */
//
//		cpl_table_delete(tab);
//    }

	return CPL_ERROR_NONE;
}


cpl_error_code create_3comp_setup(cpl_parameterlist *gala_setup,
		const long *j) {

		int i,
		rank,
		num,
		secnum = 0,
		ctnum = 0,
		lv,
		xsize,
		ysize,
		count,
		debug = 0;

	long k,
		 nrow;

	double background, exptime, xc, yc, aim, bim, xlo, ylo, theta, mag, fr,
		xfit, yfit, convbox, platescale, magzero, fluxextend, psffactor,
		magexclude, magcrit, xsec, ysec, eli, xcgalfit = 0, ycgalfit = 0,
		maggalfit = 0, regalfit = 0, ngalfit = 0, argalfit = 0, pagalfit = 0;

	char outdir[FILENAME_MAX],
		 tabfile[FILENAME_MAX],
		 imagefile[FILENAME_MAX],
		 stampfile[FILENAME_MAX],
	     stampname[FILENAME_MAX],
	     galsetfile[FILENAME_MAX],
	 	 object[FILENAME_MAX],
	 	 galfitset[FILENAME_MAX],
	 	 galfitim[FILENAME_MAX],
	 	 stamp[FILENAME_MAX],
	 	 badpix[FILENAME_MAX],
	 	 maskfile[FILENAME_MAX],
	 	 constraints[FILENAME_MAX],
	     constraintfile[FILENAME_MAX],
	     psf[FILENAME_MAX],
	     display[FILENAME_MAX],
	     directory[FILENAME_MAX],
	     fitfile[FILENAME_MAX],
	     xp[FILENAME_MAX],
	     yp[FILENAME_MAX],
	     mg[FILENAME_MAX],
	     re[FILENAME_MAX],
	     n[FILENAME_MAX],
	     ar[FILENAME_MAX],
	     pa[FILENAME_MAX],
	     combcatname[FILENAME_MAX];

	char *ptr;

	FILE *fp_gs;

	cpl_array *secindices, *ctindices;
	const cpl_array *help;

	cpl_table *tab;

	cpl_parameter *p;

	cpl_propertylist *header, *fitsheader;

	cpl_boolean skyfix = CPL_FALSE;

	/* Check input variable */

	if(*j == -1) {

		/* do nothing */

		return CPL_ERROR_NONE;
	}

	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	/* Load variables from setup parameterlist */

	p = cpl_parameterlist_find(gala_setup, "outdir");
	sprintf(outdir, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "stampfile");
    sprintf(stampfile, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "stampname");
    sprintf(stampname, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "object");
    sprintf(object, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "galfitset");
    sprintf(galfitset, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "badpix");
    sprintf(badpix, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "constraints");
    sprintf(constraints, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "psf");
    sprintf(psf, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "psffactor");
    psffactor = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "convbox");
    convbox = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magzero");
    magzero = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "platescale");
    platescale = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "fluxextend");
    fluxextend = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magexclude");
    magexclude = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magcrit");
    magcrit = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "display");
    sprintf(display, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "sexcomb");
    sprintf(combcatname, "%s", cpl_parameter_get_string(p));

	/* Read values from a table (read-only!!!) copy */

	sprintf(tabfile, "%s%s%s", outdir, "/", combcatname);

	if(access(tabfile, 00) != 0) {
		cpl_msg_error(cpl_func, "In create_3comp_setup() : "
				"Table %s was not accessable! Aborting...", tabfile);
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	/* Load table and check*/

	tab = cpl_table_load(tabfile, 1, 0);

	nrow = (long) cpl_table_get_nrow(tab);

	if(nrow <= 0) {
		cpl_msg_error(cpl_func, "In create_3comp_setup() : "
				"Input table %s is empty or not readable. Aborting...",
				tabfile);
		cpl_table_delete(tab);
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	/* Get SExtractor number of current object */

	num = cpl_table_get(tab, "NUMBER", *j, NULL);

	/* image header and exposure time */

	sprintf(imagefile, "%s%s%s%s%s%s%d%s%s%s",
			cpl_table_get_string(tab, "TILE_DIRECTORY", *j),
			"/", stampfile, "/", stampname, "_", num, "_",
			cpl_table_get_string(tab, "TILE", *j), ".fits");

	if(debug == 1) {
		printf("IMAGEFILE in create_3comp_setup() : %s\n", imagefile);
	}

	header = cpl_propertylist_load(imagefile, 0); // read fits header
	if (header == NULL) {
	    /* image header not found */
		cpl_propertylist_delete(header);
		cpl_table_delete(tab);
		cpl_msg_error(cpl_func, "Stamp file not found in "
				"create_3comp_setup(). Aborting...");
	    return cpl_error_set_message(cpl_func, CPL_ERROR_FILE_NOT_FOUND,
	                                     "%s not found", imagefile);
	}

	exptime = cpl_propertylist_get_double(header, "EXPTIME");

	if(debug == 1) {
		printf("EXPTIME in create_3comp_setup() : %f\n", exptime);
	}

	if(exptime <= 0) {
		cpl_msg_error(cpl_func, "Exptime not found in "
				"create_3comp_setup()!!!");
	}

	// Prepare filename paths and input data for setup file

	sprintf(stamp, "%s", imagefile);

	xsize = cpl_table_get_int(tab, "STAMP_XHI",*j, NULL) -
			cpl_table_get_int(tab, "STAMP_XLO",*j, NULL) + 1;
	ysize = cpl_table_get_int(tab, "STAMP_YHI",*j, NULL) -
			cpl_table_get_int(tab, "STAMP_YLO",*j, NULL) + 1;

	if(debug == 1) {
		printf("STAMP SIZES x : %d  y : %d\n", xsize, ysize);
	}

	if(xsize <= 0 || ysize <= 0) {
		cpl_msg_error(cpl_func, "In create_3comp_setup() : Stamp image not found!");
	}

	sprintf(galsetfile, "%s%s%s%s%ld%s",
			cpl_table_get_string(tab, "TILE_DIRECTORY", *j), "/", galfitset, "_", *j + 1, "_3");

	if(debug == 1) {
		printf("GALFIT-Setup FILE : %s\n", galsetfile);
	}

	sprintf(galfitim, "%s%s%s%ld%s", cpl_table_get_string(tab, "TILE_DIRECTORY", *j),
			"/", object, *j + 1, "_3.fits");

	if(debug == 1) {
		printf("GALFIT imageblock FILE : %s\n", galfitim);
	}

	if(strcmp(badpix, "n") != 0 && strcmp(badpix, "no") != 0 &&
			strcmp(badpix, "none") != 0) {
		sprintf(maskfile, "%s%s%s%s%ld%s", cpl_table_get_string(tab, "TILE_DIRECTORY", *j),
					"/", badpix, "_", *j + 1, ".fits");

		// Check if accessable

		if(access(maskfile, 00) != 0) {
			cpl_msg_error(cpl_func, "Mask file is not "
					"accessable in create_3comp_Setup() for setup "
					"%ld !!! GALFIT will be started anyway but "
					"without mask.", *j + 1);
		}

		if(debug == 1) {
			printf("GALFIT mask FILE : %s\n", maskfile);
		}

	} else {
		sprintf(maskfile, "%s", "none");
	}

	if (strcmp(constraints, "n") != 0 && strcmp(constraints, "no") != 0 &&
			strcmp(constraints, "none") != 0) {
		sprintf(constraintfile, "%s%s%s%s%ld%s",
				cpl_table_get_string(tab, "TILE_DIRECTORY", *j), "/",
				constraints, "_", *j + 1, "_3");

		// Check if accessable

		if(access(constraintfile, 00) != 0) {
			cpl_msg_error(cpl_func, "Constraint file is not "
				"accessable in create_3comp_Setup() for setup "
				"%ld !!! GALFIT will be started anyway but "
				"without constraints.", *j + 1);
		}

		if(debug == 1) {
			printf("GALFIT constraint FILE : %s\n", constraintfile);
		}

	} else {
		sprintf(constraintfile, "%s", "none");
	}

	// Read object data from table

	background  =  cpl_table_get_double(tab, "GALA_BACKGROUND", *j, NULL);
	xc      	=  cpl_table_get_double(tab, "X_IMAGE", *j, NULL);
	yc    	    =  cpl_table_get_double(tab, "Y_IMAGE", *j, NULL);
	aim 		=  cpl_table_get_double(tab, "A_IMAGE", *j, NULL);
	bim 		=  cpl_table_get_double(tab, "B_IMAGE", *j, NULL);
	theta 		=  cpl_table_get_double(tab, "THETA_IMAGE", *j, NULL);
	mag     	=  cpl_table_get_double(tab, "MAG_BEST", *j, NULL);
	fr     	    =  cpl_table_get_double(tab, "FLUX_RADIUS", *j, NULL);
	xlo         =  cpl_table_get_int(tab, "STAMP_XLO", *j, NULL);
	ylo         =  cpl_table_get_int(tab, "STAMP_YLO", *j, NULL);
	xfit  = xc - xlo;
	yfit  = yc - ylo;
	theta = theta - 90;

	// Write GALFIT setup file

	fp_gs = fopen(galsetfile, "w");

	if(fp_gs == NULL) {
		cpl_msg_error(cpl_func, "In create_3comp_setup(): An internal "
				"error occurred. Unable to open file %s", galsetfile);
	} else {
		printf("Slave %d : Opened file %s successfully!\n", rank, galsetfile);
	}

	fprintf(fp_gs, "===================================================\n");
	fprintf(fp_gs, "# IMAGE and GALFIT CONTROL PARAMETERS\n");
	fprintf(fp_gs, "A) %s\n", stamp);
	fprintf(fp_gs, "B) %s\n", galfitim);
	fprintf(fp_gs, "C) none\n");
	fprintf(fp_gs, "D) %s\n", psf);
	fprintf(fp_gs, "E) %f\n", psffactor);
	fprintf(fp_gs, "F) %s\n", maskfile);
	fprintf(fp_gs, "G) %s\n", constraintfile);
	fprintf(fp_gs, "H) %d   %d   %d   %d\n", 1, xsize, 1, ysize);
	fprintf(fp_gs, "I) %d   %d\n", (int)convbox, (int)convbox);
	fprintf(fp_gs, "J) %.4f\n", magzero);
	fprintf(fp_gs, "K) %.5f %.5f\n", platescale, platescale);
	fprintf(fp_gs, "O) %s\n", display);
	fprintf(fp_gs, "P) 0\n\n");

	fprintf(fp_gs, "# sky\n");
	fprintf(fp_gs, "0) sky\n");

	if(skyfix == CPL_TRUE) {
		fprintf(fp_gs, "1) %.3f 0\n", background);
		fprintf(fp_gs, "2) %f 0\n", 0.);
		fprintf(fp_gs, "3) %f 0\n", 0.);
	} else {
		fprintf(fp_gs, "1) %.3f 1\n", background);
		fprintf(fp_gs, "2) %f 1\n", 0.);
		fprintf(fp_gs, "3) %f 1\n", 0.);
	}
	fprintf(fp_gs, "Z) 0\n\n");

	fprintf(fp_gs, "# Sersic function component 1\n");
	fprintf(fp_gs, "0) sersic\n");
	fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xfit, yfit);
	fprintf(fp_gs, "3) %.2f 1\n", mag + 0.7526);
	fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));
	fprintf(fp_gs, "5) %.2f 1\n", 2.5);
	fprintf(fp_gs, "9) %.4f 1\n", bim / aim);
	fprintf(fp_gs, "10) %.2f 1\n", theta);
	fprintf(fp_gs, "Z) 0\n\n");

	fprintf(fp_gs, "# Sersic function component 2\n");
	fprintf(fp_gs, "0) sersic\n");
	fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xfit, yfit);
	fprintf(fp_gs, "3) %.2f 1\n", mag + 1.1928);
	fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend) / 2);
	fprintf(fp_gs, "5) %.2f 1\n", 2.5);
	fprintf(fp_gs, "9) %.4f 1\n", 1.);
	fprintf(fp_gs, "10) %.2f 1\n", -10.);
	fprintf(fp_gs, "Z) 0\n\n");

	fprintf(fp_gs, "# Sersic function component 3\n");
	fprintf(fp_gs, "0) sersic\n");
	fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xfit, yfit);
	fprintf(fp_gs, "3) %.2f 1\n", mag + 1.9454);
	fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend) / 4);
	fprintf(fp_gs, "5) %.2f 1\n", 2.5);
	fprintf(fp_gs, "9) %.4f 1\n", 1.);
	fprintf(fp_gs, "10) %.2f 1\n", 10.);
	fprintf(fp_gs, "Z) 0\n\n");


	// Add secondaries

	help = cpl_table_get_array(tab, "SECONDARY_INDICES", *j);

	secindices = cpl_array_duplicate(help);

	if(debug == 1) {
		printf("SECONDARY_NUMBER_ARRAY:\n");
		cpl_array_dump(secindices, 0,
				cpl_array_get_size(secindices), NULL);
		printf("NUMBER OF SECONDARIES: %d\n",
				(int)cpl_array_get_size(secindices));
	}

	for(i = 0; i < cpl_array_get_size(secindices); i++) {
		if(cpl_array_get(secindices, i, NULL) > 0) {
			secnum++;
		}
	}

	// If secondaries exist, amplify GALFIT setup file for each secondary

	for(lv = 0; lv < secnum; lv++) {

		k = (long)cpl_array_get(secindices, lv, NULL);

		if(k <= 0) {
			cpl_msg_error(cpl_func, "An internal error occured in "
				"create_3comp_setup(). Secondary has negative "
				"table index!");
			break;
		}

		sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", *j));
		sprintf(fitfile, "%s%s%s%ld%s", directory, "/", object, k, ".fits");

		// If fit for secondary exists

		if(access(fitfile, 00) == 0) {

			if(readfits_header(fitfile) >= 0) {

				// Read data from fit

				if((fitsheader = cpl_propertylist_load(fitfile, 2)) != CPL_ERROR_NONE
						|| fitsheader == NULL) {

					if(debug == 1) {
						cpl_msg_error(cpl_func, "Unspecified problem with loading Header in "
								"create_3comp_setup() from %s. "
								"Possibly GALFIT crashed for this object.", fitfile);
					}

					fprintf(fp_gs, "# Sersic function\n");
					fprintf(fp_gs, "0) sersic\n");

					xsec  = xfit + cpl_table_get_double(tab, "X_IMAGE", k - 1, NULL) - xc;
					ysec  = yfit + cpl_table_get_double(tab, "Y_IMAGE", k - 1, NULL) - yc;
					fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xsec, ysec);

					mag = cpl_table_get_double(tab, "MAG_BEST", k - 1, NULL);
					fprintf(fp_gs, "3) %.2f 1\n", mag);

					fr = cpl_table_get_double(tab, "FLUX_RADIUS", k - 1, NULL);

					fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));

					fprintf(fp_gs, "5) %.2f 1\n", 2.5);

					eli = cpl_table_get_double(tab, "ELLIPTICITY", k - 1, NULL);
					fprintf(fp_gs, "9) %.4f 1\n", 1 - eli);

					theta = cpl_table_get_double(tab, "THETA_IMAGE", k - 1, NULL);

					if(theta >= 0) {
						theta = theta - 90;
					} else {
						theta = 90 + theta;
					}
					fprintf(fp_gs, "10) %.2f 1\n", theta);

					fprintf(fp_gs, "Z) 0\n\n");

				} else {

					fprintf(fp_gs, "# Sersic function\n");
					fprintf(fp_gs, "0) sersic\n");

					count = 0;

					if(cpl_propertylist_has(fitsheader, "2_XC") == 1) {
						sprintf(xp, "%s", cpl_propertylist_get_string(fitsheader, "2_XC"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_3comp_setup()!!");
						sprintf(xp, "%s", "1");
					}
					remove_chr(xp);
					ptr = strtok(xp, " ");
					while(ptr != NULL) {
						if(count == 0) {
							xcgalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					if(cpl_propertylist_has(fitsheader, "2_YC") == 1) {
						sprintf(yp, "%s", cpl_propertylist_get_string(fitsheader, "2_YC"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_3comp_setup()!!");
						sprintf(yp, "%s", "1");
					}
					remove_chr(yp);
					ptr = strtok(yp, " ");
					while(ptr != NULL) {
						if(count == 0) {
							ycgalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "1) %.2f %.2f 0 0\n", xcgalfit, ycgalfit);

					if(cpl_propertylist_has(fitsheader, "2_MAG") == 1) {
						sprintf(mg, "%s", cpl_propertylist_get_string(fitsheader, "2_MAG"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_3comp_setup()!!");
						sprintf(mg, "%s", "20");
					}
					remove_chr(mg);
					ptr = strtok(mg, " ");
					while(ptr != NULL) {
						if(count == 0) {
							maggalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "3) %.2f 0\n", maggalfit);

					if(cpl_propertylist_has(fitsheader, "2_RE") == 1) {
						sprintf(re, "%s", cpl_propertylist_get_string(fitsheader, "2_RE"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_3comp_setup()!!");
						sprintf(re, "%s", "20");
					}
					remove_chr(re);
					ptr = strtok(re, " ");
					while(ptr != NULL) {
						if(count == 0) {
							regalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "4) %.2f 0\n", regalfit);

					if(cpl_propertylist_has(fitsheader, "2_N") == 1) {
						sprintf(n, "%s", cpl_propertylist_get_string(fitsheader, "2_N"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_3comp_setup()!!");
						sprintf(n, "%s", "2.5");
					}
					remove_chr(n);
					ptr = strtok(n, " ");
					while(ptr != NULL) {
						if(count == 0) {
							ngalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "5) %.2f 0\n", ngalfit);

					if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
						sprintf(ar, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_3comp_setup()!!");
						sprintf(ar, "%s", "0.8");
					}
					remove_chr(ar);
					ptr = strtok(ar, " ");
					while(ptr != NULL) {
						if(count == 0) {
							argalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "9) %.2f 0\n", argalfit);

					if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
						sprintf(pa, "%s", cpl_propertylist_get_string(fitsheader, "2_PA"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_3comp_setup()!!");
						sprintf(pa, "%s", "0");
					}
					remove_chr(pa);
					ptr = strtok(pa, " ");
					while(ptr != NULL) {
						if(count == 0) {
							pagalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "10) %.2f 0\n", pagalfit);

					fprintf(fp_gs, "Z) 0\n\n");

				}

				cpl_propertylist_delete(fitsheader);
			}

			// If fit for secondary does not exist take SExtractor parameters

		} else {

			fprintf(fp_gs, "# Sersic function\n");
			fprintf(fp_gs, "0) sersic\n");

			xsec  = xfit + cpl_table_get_double(tab, "X_IMAGE", k - 1, NULL) - xc;
			ysec  = yfit + cpl_table_get_double(tab, "Y_IMAGE", k - 1, NULL) - yc;
			fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xsec, ysec);

			mag = cpl_table_get_double(tab, "MAG_BEST", k - 1, NULL);
			fprintf(fp_gs, "3) %.2f 1\n", mag);

			fr = cpl_table_get_double(tab, "FLUX_RADIUS", k - 1, NULL);

			fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));

			fprintf(fp_gs, "5) %.2f 1\n", 2.5);

			eli = cpl_table_get_double(tab, "ELLIPTICITY", k - 1, NULL);
			fprintf(fp_gs, "9) %.4f 1\n", 1 - eli);

			theta = cpl_table_get_double(tab, "THETA_IMAGE", k - 1, NULL);

			if(theta >= 0) {
				theta = theta - 90;
			} else {
				theta = 90 + theta;
			}
			fprintf(fp_gs, "10) %.2f 1\n", theta);

			fprintf(fp_gs, "Z) 0\n\n");
		}
	}

	cpl_array_delete(secindices);

	// Include also potential contrib targets

	help = cpl_table_get_array(tab, "POT_CT_INDICES", *j);

	ctindices = cpl_array_duplicate(help);

	if(debug == 1) {
		printf("CONTRIB_TARGET_ARRAY:\n");
		cpl_array_dump(ctindices, 0,
				cpl_array_get_size(ctindices), NULL);

		printf("NUMBER OF POTENTIAL CONTRIB_TARGETS: %d\n",
				(int)cpl_array_get_size(ctindices));
	}

	// Get number of contribs

	for(i = 0; i < cpl_array_get_size(ctindices); i++) {
		if(cpl_array_get(ctindices, i, NULL) >= 0) {
			ctnum++;
		}
	}

	for(lv = 0; lv < ctnum; lv++) {

		k = cpl_array_get(ctindices, lv, NULL) - 1;

		if(k < 0) {
			cpl_msg_error(cpl_func, "An internal error occured in "
				"create_3comp_setup(). Secondary has negative "
				"table index!");
			break;
		}

		sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", k));
		sprintf(fitfile, "%s%s%s%ld%s", directory, "/", object, k + 1, ".fits");

		// If fit for contrib target exists

		if(access(fitfile, 00) == 0) {

			if(check_contribtarget(tab, object, &*j, &k, &magzero, &exptime,
					&magexclude, &magcrit, &fluxextend) == 0) {

				// Read data from fit

				if((fitsheader = cpl_propertylist_load(fitfile, 2)) != CPL_ERROR_NONE ||
						fitsheader == NULL) {

					if(debug == 1) {
						cpl_msg_error(cpl_func, "Unspecified problem with loading Header in "
							"create_3comp_setup() from %s. "
							"Possibly GALFIT crashed for this object.", fitfile);
					}

					fprintf(fp_gs, "# Sersic function\n");
					fprintf(fp_gs, "0) sersic\n");

					xsec  = cpl_table_get_double(tab, "X_IMAGE", k, NULL) - xlo;
					ysec  = cpl_table_get_double(tab, "Y_IMAGE", k, NULL) - ylo;
					fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xsec, ysec);

					mag = cpl_table_get_double(tab, "MAG_BEST", k, NULL);
					fprintf(fp_gs, "3) %.2f 1\n", mag);

					fr = cpl_table_get_double(tab, "FLUX_RADIUS", k, NULL);
					fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));

					fprintf(fp_gs, "5) %.2f 1\n", 2.5);

					eli = cpl_table_get_double(tab, "ELLIPTICITY", k, NULL);
					fprintf(fp_gs, "9) %.4f 1\n", 1 - eli);

					theta = cpl_table_get_double(tab, "THETA_IMAGE", k, NULL);
					if(theta >= 0) {
						theta = theta - 90;
					} else {
					theta = 90 + theta;
					}
					fprintf(fp_gs, "10) %.2f 1\n", theta);

					fprintf(fp_gs, "Z) 0\n\n");

				} else {

					fprintf(fp_gs, "# Sersic function\n");
					fprintf(fp_gs, "0) sersic\n");

					count = 0;

					if(cpl_propertylist_has(fitsheader, "2_XC") == 1) {
						sprintf(xp, "%s", cpl_propertylist_get_string(fitsheader, "2_XC"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_3comp_setup()!!");
						sprintf(xp, "%s", "1");
					}
					remove_chr(xp);
					ptr = strtok(xp, " ");
					while(ptr != NULL) {
						if(count == 0) {
							xcgalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					if(cpl_propertylist_has(fitsheader, "2_YC") == 1) {
						sprintf(yp, "%s", cpl_propertylist_get_string(fitsheader, "2_YC"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_3comp_setup()!!");
						sprintf(yp, "%s", "1");
					}
					remove_chr(yp);
					ptr = strtok(yp, " ");
					while(ptr != NULL) {
						if(count == 0) {
							ycgalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "1) %.2f %.2f 0 0\n", xcgalfit, ycgalfit);

					if(cpl_propertylist_has(fitsheader, "2_MAG") == 1) {
						sprintf(mg, "%s", cpl_propertylist_get_string(fitsheader, "2_MAG"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_3comp_setup()!!");
						sprintf(mg, "%s", "20");
					}
					remove_chr(mg);
					ptr = strtok(mg, " ");
					while(ptr != NULL) {
						if(count == 0) {
							maggalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "3) %.2f 0\n", maggalfit);

					if(cpl_propertylist_has(fitsheader, "2_RE") == 1) {
						sprintf(re, "%s", cpl_propertylist_get_string(fitsheader, "2_RE"));
					} else {
					cpl_msg_error(cpl_func, "Property not available in create_3comp_setup()!!");
						sprintf(re, "%s", "20");
					}
					remove_chr(re);
					ptr = strtok(re, " ");
					while(ptr != NULL) {
						if(count == 0) {
							regalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "4) %.2f 0\n", regalfit);

					if(cpl_propertylist_has(fitsheader, "2_N") == 1) {
						sprintf(n, "%s", cpl_propertylist_get_string(fitsheader, "2_N"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_3comp_setup()!!");
						sprintf(n, "%s", "2.5");
					}
					remove_chr(n);
					ptr = strtok(n, " ");
					while(ptr != NULL) {
						if(count == 0) {
							ngalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "5) %.2f 0\n", ngalfit);

					if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
						sprintf(ar, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_3comp_setup()!!");
						sprintf(ar, "%s", "0.8");
					}
					remove_chr(ar);
					ptr = strtok(ar, " ");
					while(ptr != NULL) {
						if(count == 0) {
							argalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "9) %.2f 0\n", argalfit);

					if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
						sprintf(pa, "%s", cpl_propertylist_get_string(fitsheader, "2_PA"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_3comp_setup()!!");
						sprintf(pa, "%s", "0");
					}
					remove_chr(pa);
					ptr = strtok(pa, " ");
					while(ptr != NULL) {
						if(count == 0) {
							pagalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "10) %.2f 0\n", pagalfit);
					fprintf(fp_gs, "Z) 0\n\n");
				}

				cpl_propertylist_delete(fitsheader);
			}

		} else {

			if(check_contribtarget_sexdata(tab, &*j, &k, &magzero, &exptime,
					&magexclude, &magcrit, &fluxextend) == 0) {

				fprintf(fp_gs, "# Sersic function\n");
				fprintf(fp_gs, "0) sersic\n");

				xsec  = cpl_table_get_double(tab, "X_IMAGE", k, NULL) - xlo;
				ysec  = cpl_table_get_double(tab, "Y_IMAGE", k, NULL) - ylo;
				fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xsec, ysec);

				mag = cpl_table_get_double(tab, "MAG_BEST", k, NULL);
				fprintf(fp_gs, "3) %.2f 1\n", mag);

				fr = cpl_table_get_double(tab, "FLUX_RADIUS", k, NULL);
				fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));

				fprintf(fp_gs, "5) %.2f 1\n", 2.5);

				eli = cpl_table_get_double(tab, "ELLIPTICITY", k, NULL);
				fprintf(fp_gs, "9) %.4f 1\n", 1 - eli);

				theta = cpl_table_get_double(tab, "THETA_IMAGE", k, NULL);
				if(theta >= 0) {
					theta = theta - 90;
				} else {
				theta = 90 + theta;
				}
				fprintf(fp_gs, "10) %.2f 1\n", theta);

				fprintf(fp_gs, "Z) 0\n\n");
			}
		}
	}

	cpl_array_delete(ctindices);

	fclose(fp_gs);

	/* Clean up */

	cpl_propertylist_delete(header);
	cpl_table_delete(tab);

	return CPL_ERROR_NONE;
}


/*********************************************************************
 * Run 4 component fitting with more Sérsic components
 **********************************************************************/

cpl_error_code run_4comp_fitting(cpl_parameterlist *gala_setup) {

	int numprocs = 0,
		rank = 0,
		debug = 1,
		synch = 0,
		slaverank,
		k;

	long j = 0,
		 l = 0,
		 nrow;

	char tabfile[FILENAME_MAX],
		 outdir[FILENAME_MAX],
		 combcatname[FILENAME_MAX],
		 object[FILENAME_MAX],
		 imgblock_bd[FILENAME_MAX],
		 galfitset[FILENAME_MAX],
		 str[FILENAME_MAX],
		 directory[FILENAME_MAX],
		 constraints[FILENAME_MAX],
		 galsetfile[FILENAME_MAX],
		 path[FILENAME_MAX];

	cpl_table *tab;

	cpl_parameter *p;

	MPI_Status status;

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	/* find out number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	/* Load variables from setup parameterlist */

    p = cpl_parameterlist_find(gala_setup, "outdir");
    sprintf(outdir, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "sexcomb");
    sprintf(combcatname, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "object");
    sprintf(object, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "constraints");
    sprintf(constraints, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "path");
    sprintf(path, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "galfitset");
    sprintf(galfitset, "%s", cpl_parameter_get_string(p));


    /* MASTER job */

    if(rank == 0) {

    	/* Prepare path variable for loading table */

    	sprintf(tabfile, "%s%s%s", outdir, "/", combcatname);

    	if(access(tabfile, 00) != 0) {
    		cpl_msg_error(cpl_func, "Tabfile %s is not accessable in "
    				"4 component_fitting(). Aborting...", tabfile);
    		return CPL_ERROR_DATA_NOT_FOUND;
    	}

    	/* Load combined GALAPAGOS catalog */

    	tab = cpl_table_load(tabfile, 1, 0);

    	/* Check table */

    	nrow = (long)cpl_table_get_nrow(tab);

    	printf("MASTER : Habe table mit %ld rows geladen!\n", nrow);

    	if(nrow <= 0){
    		cpl_msg_error(cpl_func, "Table %s is empty or not accessable "
    				"in 4comp_fitting(). Aborting...", tabfile);
    		return CPL_ERROR_DATA_NOT_FOUND;
		}

        /* Starting message */

    	cpl_msg_info(cpl_func, "Starting GALFIT 4 component fitting for "
    			"%ld objects.", nrow);

    	cpl_table_delete(tab);

    	/* Send jobs to slaves */

    	for(l = 0; l < nrow; l++) {

    		/* Receive a message from slave who needs a job */

    		if(debug == 1) {
    			printf("MASTER im for - LOOP : Warte auf Nachrichten von "
    				"den Slaves !!!\n");
    		}

    		MPI_Recv(&slaverank, sizeof(int), MPI_INT, MPI_ANY_SOURCE,
    								51, MPI_COMM_WORLD, &status);


    		printf("MASTER im for - LOOP : Habe folgende Nachricht von "
    			"einem Slave erhalten : %d\n", slaverank);

    		printf("---------------------------------------");


			/* Send job to the slave */

			printf("\nMASTER : Bin in Loop Nummer %ld und sende "
				"job %ld an den Slave %d.\n\n\n", j, j, slaverank);


			MPI_Send(&l, sizeof(long), MPI_INT, slaverank, 52,
					MPI_COMM_WORLD);

    	}

    	/* Termination message */

    	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    	for(k = 1; k < numprocs; k++) {

    		l = -1;

			/* Send job to the slave */

			printf("\nMASTER : Send nun die ending message an den slave"
					"%d.\n\n\n", k);

    		MPI_Send(&l, sizeof(long), MPI_INT, k, 52, MPI_COMM_WORLD);
    	}

    /* Slave job */

    } else {

		/* Load table and check size*/

		sprintf(tabfile, "%s%s%s", outdir, "/", combcatname);

		if(access(tabfile, 00) == 0) {

			tab = cpl_table_load(tabfile, 1, 0);

			nrow = (long)cpl_table_get_nrow(tab);

			if(nrow <= 0) {
				cpl_msg_error(cpl_func, "Table loaded by slave %d in "
						"run_GALFIT_4comp_fitting() is not found or empty!",
						rank);

				printf("Der aktuelle Wert von j ist : %ld\n", j);

				return CPL_ERROR_DATA_NOT_FOUND;
			}

		} else {
			cpl_msg_error(cpl_func, "Table file not accessable by "
					"slave in run_GALFIT_4comp_fitting()!");

			return CPL_ERROR_DATA_NOT_FOUND;
		}

		/* Receive job as long as MASTER sends */

    	while (j != -1) {

    		/* Find out process rank */

    		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    		/* Send a message to MASTER that slave needs a job */

    		MPI_Send(&rank, sizeof(int), MPI_INT, 0, 51, MPI_COMM_WORLD);

    		if(debug == 1) {
    			printf("SLAVE %d: Habe meinen rank zurueckgesendet!\n", rank);
    			printf("SLAVE %d: Warte jetzt auf eine Nachricht vom MASTER!\n", rank);
    		}

    		/* Receive job ID for MASTER */

    		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    		MPI_Recv(&j, sizeof(long), MPI_INT, 0, 52, MPI_COMM_WORLD, &status);

    		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    		if(debug == 1) {
    			printf("Slave %d hat einen Jobauftrag empfangen : Job Nummer %ld\n", rank, j);
    		}

    		/* If MASTER did not send termination message start GALFIT procedure */

    		if(j != -1) {

				/* Identify GALFIT output path */

				sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", j));
				sprintf(imgblock_bd, "%s%s%s%ld%s", directory, "/", object, j + 1, "_4.fits");

				/* Do GALFIT procedure only if imagebloc ist not existing yet */

				if(access(imgblock_bd, 00) != 0) {

					/* Check if constraints should be used */

//    				if(strcmp(constraints, "n") != 0 &&
//    						strcmp(constraints, "no") != 0 &&
//    						strcmp(constraints, "none") != 0) {
//
//    					/* Check if constraintfile is existing - only if not create */
//
//    					sprintf(constraintfile_bd, "%s%s%s%s%ld%s", directory, "/",
//    							constraints, "_", j + 1, "_3");
//
//    					if(create_constraintfile_3comp(constraintfile_bd, &re_max,
//    							&mag_min, &mag_max, tab, &j) != CPL_ERROR_NONE) {
//    						cpl_msg_error(cpl_func,
//    								"create_constraintfile_3comp() failed!");
//    					}
//    				}

					/* Create bulge-disc GALFIT setup files with two components */

					if(create_4comp_setup(gala_setup, &j) != CPL_ERROR_NONE) {
						cpl_msg_error(cpl_func,
								"create_4comp_setup() failed!");
					}

    				if(debug == 1) {
    					printf("GALFIT 4 component setup created for OBJECT %ld !\n", j);
    				}

    				/* Prepare GALFIT string */

        			sprintf(galsetfile, "%s%s%s%s%ld%s", directory, "/", galfitset,
        						"_", j + 1, "_4");

    				sprintf(str, "%s %s %s", path, galsetfile, "> /dev/null");

    				if(debug == 1) {
    					cpl_msg_info(cpl_func, "Slave %d is running GALFIT with %s.", rank, str);
    				}

    				/* Start GALFIT */

					if(system(str) != 0) {
						cpl_msg_error(cpl_func, "In run_4comp_fitting(): System call "
								"return value which is not 0. What does that mean?");
    				}
				}
    		}
		}

    	/* Clean up */

    	cpl_table_delete(tab);
    }

	/* Go on when all slaves have finished their jobs */

    if(rank == 0) {
    	printf("MASTER: Warte auf Nachrichten von den Slaves dass "
			"alle ihre Jobs beendet haben!\n");
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

	/* Go on when all slaves have finished their jobs */

//    if(rank == 0) {
//    	printf("MASTER: Alle slaves sind da. Jobs beendet!\n");
//
//    	/* Add results and remove helpfiles */
//
//    	tab = cpl_table_load(tabfile, 1, 0);
//
//    	/* Add results from previous fit to table and save*/
//
//    	if(update_table_3comp(tab, object) != CPL_ERROR_NONE) {
//    		cpl_msg_error(cpl_func, "update_table_3comp() failed.");
//    	}
//
//    	if(quantify_residuals(tab, object) != CPL_ERROR_NONE) {
//    		cpl_msg_error(cpl_func, "quantify_residuals() failed.");
//    	}
//
//		cpl_table_save(tab, NULL, NULL, tabfile, CPL_IO_CREATE);
//
//		printf("\nMASTER : TABLE gepeichert!!!!.\n");
//
//		/* Clean up */
//
//		cpl_table_delete(tab);
//    }

	return CPL_ERROR_NONE;
}


cpl_error_code create_4comp_setup(cpl_parameterlist *gala_setup,
		const long *j) {

		int i,
		rank,
		num,
		secnum = 0,
		ctnum = 0,
		lv,
		xsize,
		ysize,
		count,
		debug = 0;

	long k,
		 nrow;

	double background, exptime, xc, yc, aim, bim, xlo, ylo, theta, mag, fr,
		xfit, yfit, convbox, platescale, magzero, fluxextend, psffactor,
		magexclude, magcrit, xsec, ysec, eli, xcgalfit = 0, ycgalfit = 0,
		maggalfit = 0, regalfit = 0, ngalfit = 0, argalfit = 0, pagalfit = 0;

	char outdir[FILENAME_MAX],
		 tabfile[FILENAME_MAX],
		 imagefile[FILENAME_MAX],
		 stampfile[FILENAME_MAX],
	     stampname[FILENAME_MAX],
	     galsetfile[FILENAME_MAX],
	 	 object[FILENAME_MAX],
	 	 galfitset[FILENAME_MAX],
	 	 galfitim[FILENAME_MAX],
	 	 stamp[FILENAME_MAX],
	 	 badpix[FILENAME_MAX],
	 	 maskfile[FILENAME_MAX],
	 	 constraints[FILENAME_MAX],
	     constraintfile[FILENAME_MAX],
	     psf[FILENAME_MAX],
	     display[FILENAME_MAX],
	     directory[FILENAME_MAX],
	     fitfile[FILENAME_MAX],
	     xp[FILENAME_MAX],
	     yp[FILENAME_MAX],
	     mg[FILENAME_MAX],
	     re[FILENAME_MAX],
	     n[FILENAME_MAX],
	     ar[FILENAME_MAX],
	     pa[FILENAME_MAX],
	     combcatname[FILENAME_MAX];

	char *ptr;

	FILE *fp_gs;

	cpl_array *secindices, *ctindices;
	const cpl_array *help;

	cpl_table *tab;

	cpl_parameter *p;

	cpl_propertylist *header, *fitsheader;

	cpl_boolean skyfix = CPL_FALSE;

	/* Check input variable */

	if(*j == -1) {

		/* do nothing */

		return CPL_ERROR_NONE;
	}

	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	/* Load variables from setup parameterlist */

	p = cpl_parameterlist_find(gala_setup, "outdir");
	sprintf(outdir, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "stampfile");
    sprintf(stampfile, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "stampname");
    sprintf(stampname, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "object");
    sprintf(object, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "galfitset");
    sprintf(galfitset, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "badpix");
    sprintf(badpix, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "constraints");
    sprintf(constraints, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "psf");
    sprintf(psf, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "psffactor");
    psffactor = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "convbox");
    convbox = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magzero");
    magzero = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "platescale");
    platescale = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "fluxextend");
    fluxextend = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magexclude");
    magexclude = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magcrit");
    magcrit = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "display");
    sprintf(display, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "sexcomb");
    sprintf(combcatname, "%s", cpl_parameter_get_string(p));

	/* Read values from a table (read-only!!!) copy */

	sprintf(tabfile, "%s%s%s", outdir, "/", combcatname);

	if(access(tabfile, 00) != 0) {
		cpl_msg_error(cpl_func, "In create_4comp_setup() : "
				"Table %s was not accessable! Aborting...", tabfile);
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	/* Load table and check*/

	tab = cpl_table_load(tabfile, 1, 0);

	nrow = (long) cpl_table_get_nrow(tab);

	if(nrow <= 0) {
		cpl_msg_error(cpl_func, "In create_4comp_setup() : "
				"Input table %s is empty or not readable. Aborting...",
				tabfile);
		cpl_table_delete(tab);
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	/* Get SExtractor number of current object */

	num = cpl_table_get(tab, "NUMBER", *j, NULL);

	/* image header and exposure time */

	sprintf(imagefile, "%s%s%s%s%s%s%d%s%s%s",
			cpl_table_get_string(tab, "TILE_DIRECTORY", *j),
			"/", stampfile, "/", stampname, "_", num, "_",
			cpl_table_get_string(tab, "TILE", *j), ".fits");

	if(debug == 1) {
		printf("IMAGEFILE in create_4comp_setup() : %s\n", imagefile);
	}

	header = cpl_propertylist_load(imagefile, 0); // read fits header
	if (header == NULL) {
	    /* image header not found */
		cpl_propertylist_delete(header);
		cpl_table_delete(tab);
		cpl_msg_error(cpl_func, "Stamp file not found in "
				"create_4comp_setup(). Aborting...");
	    return cpl_error_set_message(cpl_func, CPL_ERROR_FILE_NOT_FOUND,
	                                     "%s not found", imagefile);
	}

	exptime = cpl_propertylist_get_double(header, "EXPTIME");

	if(debug == 1) {
		printf("EXPTIME in create_4comp_setup() : %f\n", exptime);
	}

	if(exptime <= 0) {
		cpl_msg_error(cpl_func, "Exptime not found in "
				"create_4comp_setup()!!!");
	}

	// Prepare filename paths and input data for setup file

	sprintf(stamp, "%s", imagefile);

	xsize = cpl_table_get_int(tab, "STAMP_XHI",*j, NULL) -
			cpl_table_get_int(tab, "STAMP_XLO",*j, NULL) + 1;
	ysize = cpl_table_get_int(tab, "STAMP_YHI",*j, NULL) -
			cpl_table_get_int(tab, "STAMP_YLO",*j, NULL) + 1;

	if(debug == 1) {
		printf("STAMP SIZES x : %d  y : %d\n", xsize, ysize);
	}

	if(xsize <= 0 || ysize <= 0) {
		cpl_msg_error(cpl_func, "In create_4comp_setup() : Stamp image not found!");
	}

	sprintf(galsetfile, "%s%s%s%s%ld%s",
			cpl_table_get_string(tab, "TILE_DIRECTORY", *j), "/", galfitset, "_", *j + 1, "_4");

	if(debug == 1) {
		printf("GALFIT-Setup FILE : %s\n", galsetfile);
	}

	sprintf(galfitim, "%s%s%s%ld%s", cpl_table_get_string(tab, "TILE_DIRECTORY", *j),
			"/", object, *j + 1, "_4.fits");

	if(debug == 1) {
		printf("GALFIT imageblock FILE : %s\n", galfitim);
	}

	if(strcmp(badpix, "n") != 0 && strcmp(badpix, "no") != 0 &&
			strcmp(badpix, "none") != 0) {
		sprintf(maskfile, "%s%s%s%s%ld%s", cpl_table_get_string(tab, "TILE_DIRECTORY", *j),
					"/", badpix, "_", *j + 1, ".fits");

		// Check if accessable

		if(access(maskfile, 00) != 0) {
			cpl_msg_error(cpl_func, "Mask file is not "
					"accessable in create_4comp_Setup() for setup "
					"%ld !!! GALFIT will be started anyway but "
					"without mask.", *j + 1);
		}

		if(debug == 1) {
			printf("GALFIT mask FILE : %s\n", maskfile);
		}

	} else {
		sprintf(maskfile, "%s", "none");
	}

	if (strcmp(constraints, "n") != 0 && strcmp(constraints, "no") != 0 &&
			strcmp(constraints, "none") != 0) {
		sprintf(constraintfile, "%s%s%s%s%ld%s",
				cpl_table_get_string(tab, "TILE_DIRECTORY", *j), "/",
				constraints, "_", *j + 1, "_4");

		// Check if accessable

		if(access(constraintfile, 00) != 0) {
			cpl_msg_error(cpl_func, "Constraint file is not "
				"accessable in create_4comp_Setup() for setup "
				"%ld !!! GALFIT will be started anyway but "
				"without constraints.", *j + 1);
		}

		if(debug == 1) {
			printf("GALFIT constraint FILE : %s\n", constraintfile);
		}

	} else {
		sprintf(constraintfile, "%s", "none");
	}

	// Read object data from table

	background  =  cpl_table_get_double(tab, "GALA_BACKGROUND", *j, NULL);
	xc      	=  cpl_table_get_double(tab, "X_IMAGE", *j, NULL);
	yc    	    =  cpl_table_get_double(tab, "Y_IMAGE", *j, NULL);
	aim 		=  cpl_table_get_double(tab, "A_IMAGE", *j, NULL);
	bim 		=  cpl_table_get_double(tab, "B_IMAGE", *j, NULL);
	theta 		=  cpl_table_get_double(tab, "THETA_IMAGE", *j, NULL);
	mag     	=  cpl_table_get_double(tab, "MAG_BEST", *j, NULL);
	fr     	    =  cpl_table_get_double(tab, "FLUX_RADIUS", *j, NULL);
	xlo         =  cpl_table_get_int(tab, "STAMP_XLO", *j, NULL);
	ylo         =  cpl_table_get_int(tab, "STAMP_YLO", *j, NULL);
	xfit  = xc - xlo;
	yfit  = yc - ylo;
	theta = theta - 90;

	// Write GALFIT setup file

	fp_gs = fopen(galsetfile, "w");

	if(fp_gs == NULL) {
		cpl_msg_error(cpl_func, "In create_4comp_setup(): An internal "
				"error occurred. Unable to open file %s", galsetfile);
	} else {
		printf("Slave %d : Opened file %s successfully!\n", rank, galsetfile);
	}

	fprintf(fp_gs, "===================================================\n");
	fprintf(fp_gs, "# IMAGE and GALFIT CONTROL PARAMETERS\n");
	fprintf(fp_gs, "A) %s\n", stamp);
	fprintf(fp_gs, "B) %s\n", galfitim);
	fprintf(fp_gs, "C) none\n");
	fprintf(fp_gs, "D) %s\n", psf);
	fprintf(fp_gs, "E) %f\n", psffactor);
	fprintf(fp_gs, "F) %s\n", maskfile);
	fprintf(fp_gs, "G) %s\n", constraintfile);
	fprintf(fp_gs, "H) %d   %d   %d   %d\n", 1, xsize, 1, ysize);
	fprintf(fp_gs, "I) %d   %d\n", (int)convbox, (int)convbox);
	fprintf(fp_gs, "J) %.4f\n", magzero);
	fprintf(fp_gs, "K) %.5f %.5f\n", platescale, platescale);
	fprintf(fp_gs, "O) %s\n", display);
	fprintf(fp_gs, "P) 0\n\n");

	fprintf(fp_gs, "# sky\n");
	fprintf(fp_gs, "0) sky\n");

	if(skyfix == CPL_TRUE) {
		fprintf(fp_gs, "1) %.3f 0\n", background);
		fprintf(fp_gs, "2) %f 0\n", 0.);
		fprintf(fp_gs, "3) %f 0\n", 0.);
	} else {
		fprintf(fp_gs, "1) %.3f 1\n", background);
		fprintf(fp_gs, "2) %f 1\n", 0.);
		fprintf(fp_gs, "3) %f 1\n", 0.);
	}
	fprintf(fp_gs, "Z) 0\n\n");

	fprintf(fp_gs, "# Sersic function component 1\n");
	fprintf(fp_gs, "0) sersic\n");
	fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xfit, yfit);
	fprintf(fp_gs, "3) %.2f 1\n", mag + 1.);
	fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));
	fprintf(fp_gs, "5) %.2f 1\n", 2.5);
	fprintf(fp_gs, "9) %.4f 1\n", bim / aim);
	fprintf(fp_gs, "10) %.2f 1\n", theta);
	fprintf(fp_gs, "Z) 0\n\n");

	fprintf(fp_gs, "# Sersic function component 2\n");
	fprintf(fp_gs, "0) sersic\n");
	fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xfit, yfit);
	fprintf(fp_gs, "3) %.2f 1\n", mag + 1.3072);
	fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend) / 2);
	fprintf(fp_gs, "5) %.2f 1\n", 2.5);
	fprintf(fp_gs, "9) %.4f 1\n", 1.);
	fprintf(fp_gs, "10) %.2f 1\n", -10.);
	fprintf(fp_gs, "Z) 0\n\n");

	fprintf(fp_gs, "# Sersic function component 3\n");
	fprintf(fp_gs, "0) sersic\n");
	fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xfit, yfit);
	fprintf(fp_gs, "3) %.2f 1\n", mag + 1.7475);
	fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend) / 4);
	fprintf(fp_gs, "5) %.2f 1\n", 2.5);
	fprintf(fp_gs, "9) %.4f 1\n", 1.);
	fprintf(fp_gs, "10) %.2f 1\n", 10.);
	fprintf(fp_gs, "Z) 0\n\n");

	fprintf(fp_gs, "# Sersic function component 4\n");
	fprintf(fp_gs, "0) sersic\n");
	fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xfit, yfit);
	fprintf(fp_gs, "3) %.2f 1\n", mag + 2.5);
	fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend) / 6);
	fprintf(fp_gs, "5) %.2f 1\n", 2.5);
	fprintf(fp_gs, "9) %.4f 1\n", 1.);
	fprintf(fp_gs, "10) %.2f 1\n", 20.);
	fprintf(fp_gs, "Z) 0\n\n");


	// Add secondaries

	help = cpl_table_get_array(tab, "SECONDARY_INDICES", *j);

	secindices = cpl_array_duplicate(help);

	if(debug == 1) {
		printf("SECONDARY_NUMBER_ARRAY:\n");
		cpl_array_dump(secindices, 0,
				cpl_array_get_size(secindices), NULL);
		printf("NUMBER OF SECONDARIES: %d\n",
				(int)cpl_array_get_size(secindices));
	}

	for(i = 0; i < cpl_array_get_size(secindices); i++) {
		if(cpl_array_get(secindices, i, NULL) > 0) {
			secnum++;
		}
	}

	// If secondaries exist, amplify GALFIT setup file for each secondary

	for(lv = 0; lv < secnum; lv++) {

		k = (long)cpl_array_get(secindices, lv, NULL);

		if(k <= 0) {
			cpl_msg_error(cpl_func, "An internal error occured in "
				"create_4comp_setup(). Secondary has negative "
				"table index!");
			break;
		}

		sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", *j));
		sprintf(fitfile, "%s%s%s%ld%s", directory, "/", object, k, ".fits");

		// If fit for secondary exists

		if(access(fitfile, 00) == 0) {

			if(readfits_header(fitfile) >= 0) {

				// Read data from fit

				if((fitsheader = cpl_propertylist_load(fitfile, 2)) != CPL_ERROR_NONE
						|| fitsheader == NULL) {

					if(debug == 1) {
						cpl_msg_error(cpl_func, "Unspecified problem with loading Header in "
								"create_4comp_setup() from %s. "
								"Possibly GALFIT crashed for this object.", fitfile);
					}

					fprintf(fp_gs, "# Sersic function\n");
					fprintf(fp_gs, "0) sersic\n");

					xsec  = xfit + cpl_table_get_double(tab, "X_IMAGE", k - 1, NULL) - xc;
					ysec  = yfit + cpl_table_get_double(tab, "Y_IMAGE", k - 1, NULL) - yc;
					fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xsec, ysec);

					mag = cpl_table_get_double(tab, "MAG_BEST", k - 1, NULL);
					fprintf(fp_gs, "3) %.2f 1\n", mag);

					fr = cpl_table_get_double(tab, "FLUX_RADIUS", k - 1, NULL);

					fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));

					fprintf(fp_gs, "5) %.2f 1\n", 2.5);

					eli = cpl_table_get_double(tab, "ELLIPTICITY", k - 1, NULL);
					fprintf(fp_gs, "9) %.4f 1\n", 1 - eli);

					theta = cpl_table_get_double(tab, "THETA_IMAGE", k - 1, NULL);

					if(theta >= 0) {
						theta = theta - 90;
					} else {
						theta = 90 + theta;
					}
					fprintf(fp_gs, "10) %.2f 1\n", theta);

					fprintf(fp_gs, "Z) 0\n\n");

				} else {

					fprintf(fp_gs, "# Sersic function\n");
					fprintf(fp_gs, "0) sersic\n");

					count = 0;

					if(cpl_propertylist_has(fitsheader, "2_XC") == 1) {
						sprintf(xp, "%s", cpl_propertylist_get_string(fitsheader, "2_XC"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_4comp_setup()!!");
						sprintf(xp, "%s", "1");
					}
					remove_chr(xp);
					ptr = strtok(xp, " ");
					while(ptr != NULL) {
						if(count == 0) {
							xcgalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					if(cpl_propertylist_has(fitsheader, "2_YC") == 1) {
						sprintf(yp, "%s", cpl_propertylist_get_string(fitsheader, "2_YC"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_4comp_setup()!!");
						sprintf(yp, "%s", "1");
					}
					remove_chr(yp);
					ptr = strtok(yp, " ");
					while(ptr != NULL) {
						if(count == 0) {
							ycgalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "1) %.2f %.2f 0 0\n", xcgalfit, ycgalfit);

					if(cpl_propertylist_has(fitsheader, "2_MAG") == 1) {
						sprintf(mg, "%s", cpl_propertylist_get_string(fitsheader, "2_MAG"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_4comp_setup()!!");
						sprintf(mg, "%s", "20");
					}
					remove_chr(mg);
					ptr = strtok(mg, " ");
					while(ptr != NULL) {
						if(count == 0) {
							maggalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "3) %.2f 0\n", maggalfit);

					if(cpl_propertylist_has(fitsheader, "2_RE") == 1) {
						sprintf(re, "%s", cpl_propertylist_get_string(fitsheader, "2_RE"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_4comp_setup()!!");
						sprintf(re, "%s", "20");
					}
					remove_chr(re);
					ptr = strtok(re, " ");
					while(ptr != NULL) {
						if(count == 0) {
							regalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "4) %.2f 0\n", regalfit);

					if(cpl_propertylist_has(fitsheader, "2_N") == 1) {
						sprintf(n, "%s", cpl_propertylist_get_string(fitsheader, "2_N"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_4comp_setup()!!");
						sprintf(n, "%s", "2.5");
					}
					remove_chr(n);
					ptr = strtok(n, " ");
					while(ptr != NULL) {
						if(count == 0) {
							ngalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "5) %.2f 0\n", ngalfit);

					if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
						sprintf(ar, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_4comp_setup()!!");
						sprintf(ar, "%s", "0.8");
					}
					remove_chr(ar);
					ptr = strtok(ar, " ");
					while(ptr != NULL) {
						if(count == 0) {
							argalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "9) %.2f 0\n", argalfit);

					if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
						sprintf(pa, "%s", cpl_propertylist_get_string(fitsheader, "2_PA"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_4comp_setup()!!");
						sprintf(pa, "%s", "0");
					}
					remove_chr(pa);
					ptr = strtok(pa, " ");
					while(ptr != NULL) {
						if(count == 0) {
							pagalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "10) %.2f 0\n", pagalfit);

					fprintf(fp_gs, "Z) 0\n\n");

				}

				cpl_propertylist_delete(fitsheader);
			}

			// If fit for secondary does not exist take SExtractor parameters

		} else {

			fprintf(fp_gs, "# Sersic function\n");
			fprintf(fp_gs, "0) sersic\n");

			xsec  = xfit + cpl_table_get_double(tab, "X_IMAGE", k - 1, NULL) - xc;
			ysec  = yfit + cpl_table_get_double(tab, "Y_IMAGE", k - 1, NULL) - yc;
			fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xsec, ysec);

			mag = cpl_table_get_double(tab, "MAG_BEST", k - 1, NULL);
			fprintf(fp_gs, "3) %.2f 1\n", mag);

			fr = cpl_table_get_double(tab, "FLUX_RADIUS", k - 1, NULL);

			fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));

			fprintf(fp_gs, "5) %.2f 1\n", 2.5);

			eli = cpl_table_get_double(tab, "ELLIPTICITY", k - 1, NULL);
			fprintf(fp_gs, "9) %.4f 1\n", 1 - eli);

			theta = cpl_table_get_double(tab, "THETA_IMAGE", k - 1, NULL);

			if(theta >= 0) {
				theta = theta - 90;
			} else {
				theta = 90 + theta;
			}
			fprintf(fp_gs, "10) %.2f 1\n", theta);

			fprintf(fp_gs, "Z) 0\n\n");
		}
	}

	cpl_array_delete(secindices);

	// Include also potential contrib targets

	help = cpl_table_get_array(tab, "POT_CT_INDICES", *j);

	ctindices = cpl_array_duplicate(help);

	if(debug == 1) {
		printf("CONTRIB_TARGET_ARRAY:\n");
		cpl_array_dump(ctindices, 0,
				cpl_array_get_size(ctindices), NULL);

		printf("NUMBER OF POTENTIAL CONTRIB_TARGETS: %d\n",
				(int)cpl_array_get_size(ctindices));
	}

	// Get number of contribs

	for(i = 0; i < cpl_array_get_size(ctindices); i++) {
		if(cpl_array_get(ctindices, i, NULL) >= 0) {
			ctnum++;
		}
	}

	for(lv = 0; lv < ctnum; lv++) {

		k = cpl_array_get(ctindices, lv, NULL) - 1;

		if(k < 0) {
			cpl_msg_error(cpl_func, "An internal error occured in "
				"create_4comp_setup(). Secondary has negative "
				"table index!");
			break;
		}

		sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", k));
		sprintf(fitfile, "%s%s%s%ld%s", directory, "/", object, k + 1, ".fits");

		// If fit for contrib target exists

		if(access(fitfile, 00) == 0) {

			if(check_contribtarget(tab, object, &*j, &k, &magzero, &exptime,
					&magexclude, &magcrit, &fluxextend) == 0) {

				// Read data from fit

				if((fitsheader = cpl_propertylist_load(fitfile, 2)) != CPL_ERROR_NONE ||
						fitsheader == NULL) {

					if(debug == 1) {
						cpl_msg_error(cpl_func, "Unspecified problem with loading Header in "
							"create_4comp_setup() from %s. "
							"Possibly GALFIT crashed for this object.", fitfile);
					}

					fprintf(fp_gs, "# Sersic function\n");
					fprintf(fp_gs, "0) sersic\n");

					xsec  = cpl_table_get_double(tab, "X_IMAGE", k, NULL) - xlo;
					ysec  = cpl_table_get_double(tab, "Y_IMAGE", k, NULL) - ylo;
					fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xsec, ysec);

					mag = cpl_table_get_double(tab, "MAG_BEST", k, NULL);
					fprintf(fp_gs, "3) %.2f 1\n", mag);

					fr = cpl_table_get_double(tab, "FLUX_RADIUS", k, NULL);
					fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));

					fprintf(fp_gs, "5) %.2f 1\n", 2.5);

					eli = cpl_table_get_double(tab, "ELLIPTICITY", k, NULL);
					fprintf(fp_gs, "9) %.4f 1\n", 1 - eli);

					theta = cpl_table_get_double(tab, "THETA_IMAGE", k, NULL);
					if(theta >= 0) {
						theta = theta - 90;
					} else {
					theta = 90 + theta;
					}
					fprintf(fp_gs, "10) %.2f 1\n", theta);

					fprintf(fp_gs, "Z) 0\n\n");

				} else {

					fprintf(fp_gs, "# Sersic function\n");
					fprintf(fp_gs, "0) sersic\n");

					count = 0;

					if(cpl_propertylist_has(fitsheader, "2_XC") == 1) {
						sprintf(xp, "%s", cpl_propertylist_get_string(fitsheader, "2_XC"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_4comp_setup()!!");
						sprintf(xp, "%s", "1");
					}
					remove_chr(xp);
					ptr = strtok(xp, " ");
					while(ptr != NULL) {
						if(count == 0) {
							xcgalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					if(cpl_propertylist_has(fitsheader, "2_YC") == 1) {
						sprintf(yp, "%s", cpl_propertylist_get_string(fitsheader, "2_YC"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_4comp_setup()!!");
						sprintf(yp, "%s", "1");
					}
					remove_chr(yp);
					ptr = strtok(yp, " ");
					while(ptr != NULL) {
						if(count == 0) {
							ycgalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "1) %.2f %.2f 0 0\n", xcgalfit, ycgalfit);

					if(cpl_propertylist_has(fitsheader, "2_MAG") == 1) {
						sprintf(mg, "%s", cpl_propertylist_get_string(fitsheader, "2_MAG"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_4comp_setup()!!");
						sprintf(mg, "%s", "20");
					}
					remove_chr(mg);
					ptr = strtok(mg, " ");
					while(ptr != NULL) {
						if(count == 0) {
							maggalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "3) %.2f 0\n", maggalfit);

					if(cpl_propertylist_has(fitsheader, "2_RE") == 1) {
						sprintf(re, "%s", cpl_propertylist_get_string(fitsheader, "2_RE"));
					} else {
					cpl_msg_error(cpl_func, "Property not available in create_4comp_setup()!!");
						sprintf(re, "%s", "20");
					}
					remove_chr(re);
					ptr = strtok(re, " ");
					while(ptr != NULL) {
						if(count == 0) {
							regalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "4) %.2f 0\n", regalfit);

					if(cpl_propertylist_has(fitsheader, "2_N") == 1) {
						sprintf(n, "%s", cpl_propertylist_get_string(fitsheader, "2_N"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_4comp_setup()!!");
						sprintf(n, "%s", "2.5");
					}
					remove_chr(n);
					ptr = strtok(n, " ");
					while(ptr != NULL) {
						if(count == 0) {
							ngalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "5) %.2f 0\n", ngalfit);

					if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
						sprintf(ar, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_4comp_setup()!!");
						sprintf(ar, "%s", "0.8");
					}
					remove_chr(ar);
					ptr = strtok(ar, " ");
					while(ptr != NULL) {
						if(count == 0) {
							argalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "9) %.2f 0\n", argalfit);

					if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
						sprintf(pa, "%s", cpl_propertylist_get_string(fitsheader, "2_PA"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_4comp_setup()!!");
						sprintf(pa, "%s", "0");
					}
					remove_chr(pa);
					ptr = strtok(pa, " ");
					while(ptr != NULL) {
						if(count == 0) {
							pagalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "10) %.2f 0\n", pagalfit);
					fprintf(fp_gs, "Z) 0\n\n");
				}

				cpl_propertylist_delete(fitsheader);
			}

		} else {

			if(check_contribtarget_sexdata(tab, &*j, &k, &magzero, &exptime,
					&magexclude, &magcrit, &fluxextend) == 0) {

				fprintf(fp_gs, "# Sersic function\n");
				fprintf(fp_gs, "0) sersic\n");

				xsec  = cpl_table_get_double(tab, "X_IMAGE", k, NULL) - xlo;
				ysec  = cpl_table_get_double(tab, "Y_IMAGE", k, NULL) - ylo;
				fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xsec, ysec);

				mag = cpl_table_get_double(tab, "MAG_BEST", k, NULL);
				fprintf(fp_gs, "3) %.2f 1\n", mag);

				fr = cpl_table_get_double(tab, "FLUX_RADIUS", k, NULL);
				fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));

				fprintf(fp_gs, "5) %.2f 1\n", 2.5);

				eli = cpl_table_get_double(tab, "ELLIPTICITY", k, NULL);
				fprintf(fp_gs, "9) %.4f 1\n", 1 - eli);

				theta = cpl_table_get_double(tab, "THETA_IMAGE", k, NULL);
				if(theta >= 0) {
					theta = theta - 90;
				} else {
				theta = 90 + theta;
				}
				fprintf(fp_gs, "10) %.2f 1\n", theta);

				fprintf(fp_gs, "Z) 0\n\n");
			}
		}
	}

	cpl_array_delete(ctindices);

	fclose(fp_gs);

	/* Clean up */

	cpl_propertylist_delete(header);
	cpl_table_delete(tab);

	return CPL_ERROR_NONE;
}



/*********************************************************************
 * Run 5 component fitting with more Sérsic components
 **********************************************************************/

cpl_error_code run_5comp_fitting(cpl_parameterlist *gala_setup) {

	int numprocs = 0,
		rank = 0,
		debug = 1,
		synch = 0,
		slaverank,
		k;

	long j = 0,
		 l = 0,
		 nrow;

	char tabfile[FILENAME_MAX],
		 outdir[FILENAME_MAX],
		 combcatname[FILENAME_MAX],
		 object[FILENAME_MAX],
		 imgblock_bd[FILENAME_MAX],
		 galfitset[FILENAME_MAX],
		 str[FILENAME_MAX],
		 directory[FILENAME_MAX],
		 constraints[FILENAME_MAX],
		 galsetfile[FILENAME_MAX],
		 path[FILENAME_MAX];

	cpl_table *tab;

	cpl_parameter *p;

	MPI_Status status;

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	/* find out number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	/* Load variables from setup parameterlist */

    p = cpl_parameterlist_find(gala_setup, "outdir");
    sprintf(outdir, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "sexcomb");
    sprintf(combcatname, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "object");
    sprintf(object, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "constraints");
    sprintf(constraints, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "path");
    sprintf(path, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "galfitset");
    sprintf(galfitset, "%s", cpl_parameter_get_string(p));


    /* MASTER job */

    if(rank == 0) {

    	/* Prepare path variable for loading table */

    	sprintf(tabfile, "%s%s%s", outdir, "/", combcatname);

    	if(access(tabfile, 00) != 0) {
    		cpl_msg_error(cpl_func, "Tabfile %s is not accessable in "
    				"5 component_fitting(). Aborting...", tabfile);
    		return CPL_ERROR_DATA_NOT_FOUND;
    	}

    	/* Load combined GALAPAGOS catalog */

    	tab = cpl_table_load(tabfile, 1, 0);

    	/* Check table */

    	nrow = (long)cpl_table_get_nrow(tab);

    	printf("MASTER : Habe table mit %ld rows geladen!\n", nrow);

    	if(nrow <= 0){
    		cpl_msg_error(cpl_func, "Table %s is empty or not accessable "
    				"in 5comp_fitting(). Aborting...", tabfile);
    		return CPL_ERROR_DATA_NOT_FOUND;
		}

        /* Starting message */

    	cpl_msg_info(cpl_func, "Starting GALFIT 5 component fitting for "
    			"%ld objects.", nrow);

    	cpl_table_delete(tab);

    	/* Send jobs to slaves */

    	for(l = 0; l < nrow; l++) {

    		/* Receive a message from slave who needs a job */

    		if(debug == 1) {
    			printf("MASTER im for - LOOP : Warte auf Nachrichten von "
    				"den Slaves !!!\n");
    		}

    		MPI_Recv(&slaverank, sizeof(int), MPI_INT, MPI_ANY_SOURCE,
    								51, MPI_COMM_WORLD, &status);

    		if(debug == 1) {
    			printf("MASTER im for - LOOP : Habe folgende Nachricht von "
    				"einem Slave erhalten : %d\n", slaverank);
    		}

			/* Send job to the slave */

			printf("\nMASTER : Bin in Loop Nummer %ld und sende "
				"job %ld an den Slave %d.\n\n\n", j, j, slaverank);


			MPI_Send(&l, sizeof(long), MPI_INT, slaverank, 52,
					MPI_COMM_WORLD);

    	}

    	/* Termination message */

    	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    	for(k = 1; k < numprocs; k++) {

    		l = -1;

			/* Send job to the slave */

			printf("\nMASTER : Send nun die ending message an den slave"
					"%d.\n\n\n", k);

    		MPI_Send(&l, sizeof(long), MPI_INT, k, 52, MPI_COMM_WORLD);
    	}

    /* Slave job */

    } else {

		/* Load table and check size*/

		sprintf(tabfile, "%s%s%s", outdir, "/", combcatname);

		if(access(tabfile, 00) == 0) {

			tab = cpl_table_load(tabfile, 1, 0);

			nrow = (long)cpl_table_get_nrow(tab);

			if(nrow <= 0) {
				cpl_msg_error(cpl_func, "Table loaded by slave %d in "
						"run_GALFIT_5comp_fitting() is not found or empty!",
						rank);

				printf("Der aktuelle Wert von j ist : %ld\n", j);

				return CPL_ERROR_DATA_NOT_FOUND;
			}

		} else {
			cpl_msg_error(cpl_func, "Table file not accessable by "
					"slave in run_GALFIT_5comp_fitting()!");

			return CPL_ERROR_DATA_NOT_FOUND;
		}

		/* Receive job as long as MASTER sends */

    	while (j != -1) {

    		/* Find out process rank */

    		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    		/* Send a message to MASTER that slave needs a job */

    		MPI_Send(&rank, sizeof(int), MPI_INT, 0, 51, MPI_COMM_WORLD);

    		if(debug == 1) {
    			printf("SLAVE %d: Habe meinen rank zurueckgesendet!\n", rank);
    			printf("SLAVE %d: Warte jetzt auf eine Nachricht vom MASTER!\n", rank);
    		}

    		/* Receive job ID for MASTER */

    		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    		MPI_Recv(&j, sizeof(long), MPI_INT, 0, 52, MPI_COMM_WORLD, &status);

    		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    		if(debug == 1) {
    			printf("Slave %d hat einen Jobauftrag empfangen : Job Nummer %ld\n", rank, j);
    		}

    		/* If MASTER did not send termination message start GALFIT procedure */

    		if(j != -1) {

				/* Identify GALFIT output path */

				sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", j));
				sprintf(imgblock_bd, "%s%s%s%ld%s", directory, "/", object, j + 1, "_5.fits");

				/* Do GALFIT procedure only if imagebloc ist not existing yet */

				if(access(imgblock_bd, 00) != 0) {

					/* Check if constraints should be used */

//    				if(strcmp(constraints, "n") != 0 &&
//    						strcmp(constraints, "no") != 0 &&
//    						strcmp(constraints, "none") != 0) {
//
//    					/* Check if constraintfile is existing - only if not create */
//
//    					sprintf(constraintfile_bd, "%s%s%s%s%ld%s", directory, "/",
//    							constraints, "_", j + 1, "_3");
//
//    					if(create_constraintfile_3comp(constraintfile_bd, &re_max,
//    							&mag_min, &mag_max, tab, &j) != CPL_ERROR_NONE) {
//    						cpl_msg_error(cpl_func,
//    								"create_constraintfile_3comp() failed!");
//    					}
//    				}

					/* Create bulge-disc GALFIT setup files with two components */

					if(create_5comp_setup(gala_setup, &j) != CPL_ERROR_NONE) {
						cpl_msg_error(cpl_func,
								"create_5comp_setup() failed!");
					}

    				if(debug == 1) {
    					printf("GALFIT 5 component setup created for OBJECT %ld !\n", j);
    				}

    				/* Prepare GALFIT string */

        			sprintf(galsetfile, "%s%s%s%s%ld%s", directory, "/", galfitset,
        						"_", j + 1, "_5");

    				sprintf(str, "%s %s %s", path, galsetfile, "> /dev/null");

    				if(debug == 1) {
    					cpl_msg_info(cpl_func, "Slave %d is running GALFIT with %s.", rank, str);
    				}

    				/* Start GALFIT */

					if(system(str) != 0) {
						cpl_msg_error(cpl_func, "In run_5comp_fitting(): System call "
								"return value which is not 0. What does that mean?");
    				}
				}
    		}
		}

    	/* Clean up */

    	cpl_table_delete(tab);
    }

	/* Go on when all slaves have finished their jobs */

    if(rank == 0) {
    	printf("MASTER: Warte auf Nachrichten von den Slaves dass "
			"alle ihre Jobs beendet haben!\n");
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

	/* Go on when all slaves have finished their jobs */

//    if(rank == 0) {
//    	printf("MASTER: Alle slaves sind da. Jobs beendet!\n");
//
//    	/* Add results and remove helpfiles */
//
//    	tab = cpl_table_load(tabfile, 1, 0);
//
//    	/* Add results from previous fit to table and save*/
//
//    	if(update_table_3comp(tab, object) != CPL_ERROR_NONE) {
//    		cpl_msg_error(cpl_func, "update_table_3comp() failed.");
//    	}
//
//    	if(quantify_residuals(tab, object) != CPL_ERROR_NONE) {
//    		cpl_msg_error(cpl_func, "quantify_residuals() failed.");
//    	}
//
//		cpl_table_save(tab, NULL, NULL, tabfile, CPL_IO_CREATE);
//
//		printf("\nMASTER : TABLE gepeichert!!!!.\n");
//
//		/* Clean up */
//
//		cpl_table_delete(tab);
//    }

	return CPL_ERROR_NONE;
}


cpl_error_code create_5comp_setup(cpl_parameterlist *gala_setup,
		const long *j) {

		int i,
		rank,
		num,
		secnum = 0,
		ctnum = 0,
		lv,
		xsize,
		ysize,
		count,
		debug = 0;

	long k,
		 nrow;

	double background, exptime, xc, yc, aim, bim, xlo, ylo, theta, mag, fr,
		xfit, yfit, convbox, platescale, magzero, fluxextend, psffactor,
		magexclude, magcrit, xsec, ysec, eli, xcgalfit = 0, ycgalfit = 0,
		maggalfit = 0, regalfit = 0, ngalfit = 0, argalfit = 0, pagalfit = 0;

	char outdir[FILENAME_MAX],
		 tabfile[FILENAME_MAX],
		 imagefile[FILENAME_MAX],
		 stampfile[FILENAME_MAX],
	     stampname[FILENAME_MAX],
	     galsetfile[FILENAME_MAX],
	 	 object[FILENAME_MAX],
	 	 galfitset[FILENAME_MAX],
	 	 galfitim[FILENAME_MAX],
	 	 stamp[FILENAME_MAX],
	 	 badpix[FILENAME_MAX],
	 	 maskfile[FILENAME_MAX],
	 	 constraints[FILENAME_MAX],
	     constraintfile[FILENAME_MAX],
	     psf[FILENAME_MAX],
	     display[FILENAME_MAX],
	     directory[FILENAME_MAX],
	     fitfile[FILENAME_MAX],
	     xp[FILENAME_MAX],
	     yp[FILENAME_MAX],
	     mg[FILENAME_MAX],
	     re[FILENAME_MAX],
	     n[FILENAME_MAX],
	     ar[FILENAME_MAX],
	     pa[FILENAME_MAX],
	     combcatname[FILENAME_MAX];

	char *ptr;

	FILE *fp_gs;

	cpl_array *secindices, *ctindices;
	const cpl_array *help;

	cpl_table *tab;

	cpl_parameter *p;

	cpl_propertylist *header, *fitsheader;

	cpl_boolean skyfix = CPL_FALSE;

	/* Check input variable */

	if(*j == -1) {

		/* do nothing */

		return CPL_ERROR_NONE;
	}

	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	/* Load variables from setup parameterlist */

	p = cpl_parameterlist_find(gala_setup, "outdir");
	sprintf(outdir, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "stampfile");
    sprintf(stampfile, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "stampname");
    sprintf(stampname, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "object");
    sprintf(object, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "galfitset");
    sprintf(galfitset, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "badpix");
    sprintf(badpix, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "constraints");
    sprintf(constraints, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "psf");
    sprintf(psf, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "psffactor");
    psffactor = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "convbox");
    convbox = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magzero");
    magzero = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "platescale");
    platescale = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "fluxextend");
    fluxextend = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magexclude");
    magexclude = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magcrit");
    magcrit = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "display");
    sprintf(display, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "sexcomb");
    sprintf(combcatname, "%s", cpl_parameter_get_string(p));

	/* Read values from a table (read-only!!!) copy */

	sprintf(tabfile, "%s%s%s", outdir, "/", combcatname);

	if(access(tabfile, 00) != 0) {
		cpl_msg_error(cpl_func, "In create_5comp_setup() : "
				"Table %s was not accessable! Aborting...", tabfile);
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	/* Load table and check*/

	tab = cpl_table_load(tabfile, 1, 0);

	nrow = (long) cpl_table_get_nrow(tab);

	if(nrow <= 0) {
		cpl_msg_error(cpl_func, "In create_5comp_setup() : "
				"Input table %s is empty or not readable. Aborting...",
				tabfile);
		cpl_table_delete(tab);
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	/* Get SExtractor number of current object */

	num = cpl_table_get(tab, "NUMBER", *j, NULL);

	/* image header and exposure time */

	sprintf(imagefile, "%s%s%s%s%s%s%d%s%s%s",
			cpl_table_get_string(tab, "TILE_DIRECTORY", *j),
			"/", stampfile, "/", stampname, "_", num, "_",
			cpl_table_get_string(tab, "TILE", *j), ".fits");

	if(debug == 1) {
		printf("IMAGEFILE in create_5comp_setup() : %s\n", imagefile);
	}

	header = cpl_propertylist_load(imagefile, 0); // read fits header
	if (header == NULL) {
	    /* image header not found */
		cpl_propertylist_delete(header);
		cpl_table_delete(tab);
		cpl_msg_error(cpl_func, "Stamp file not found in "
				"create_5comp_setup(). Aborting...");
	    return cpl_error_set_message(cpl_func, CPL_ERROR_FILE_NOT_FOUND,
	                                     "%s not found", imagefile);
	}

	exptime = cpl_propertylist_get_double(header, "EXPTIME");

	if(debug == 1) {
		printf("EXPTIME in create_5comp_setup() : %f\n", exptime);
	}

	if(exptime <= 0) {
		cpl_msg_error(cpl_func, "Exptime not found in "
				"create_5comp_setup()!!!");
	}

	// Prepare filename paths and input data for setup file

	sprintf(stamp, "%s", imagefile);

	xsize = cpl_table_get_int(tab, "STAMP_XHI",*j, NULL) -
			cpl_table_get_int(tab, "STAMP_XLO",*j, NULL) + 1;
	ysize = cpl_table_get_int(tab, "STAMP_YHI",*j, NULL) -
			cpl_table_get_int(tab, "STAMP_YLO",*j, NULL) + 1;

	if(debug == 1) {
		printf("STAMP SIZES x : %d  y : %d\n", xsize, ysize);
	}

	if(xsize <= 0 || ysize <= 0) {
		cpl_msg_error(cpl_func, "In create_5comp_setup() : Stamp image not found!");
	}

	sprintf(galsetfile, "%s%s%s%s%ld%s",
			cpl_table_get_string(tab, "TILE_DIRECTORY", *j), "/", galfitset, "_", *j + 1, "_5");

	if(debug == 1) {
		printf("GALFIT-Setup FILE : %s\n", galsetfile);
	}

	sprintf(galfitim, "%s%s%s%ld%s", cpl_table_get_string(tab, "TILE_DIRECTORY", *j),
			"/", object, *j + 1, "_5.fits");

	if(debug == 1) {
		printf("GALFIT imageblock FILE : %s\n", galfitim);
	}

	if(strcmp(badpix, "n") != 0 && strcmp(badpix, "no") != 0 &&
			strcmp(badpix, "none") != 0) {
		sprintf(maskfile, "%s%s%s%s%ld%s", cpl_table_get_string(tab, "TILE_DIRECTORY", *j),
					"/", badpix, "_", *j + 1, ".fits");

		// Check if accessable

		if(access(maskfile, 00) != 0) {
			cpl_msg_error(cpl_func, "Mask file is not "
					"accessable in create_5comp_Setup() for setup "
					"%ld !!! GALFIT will be started anyway but "
					"without mask.", *j + 1);
		}

		if(debug == 1) {
			printf("GALFIT mask FILE : %s\n", maskfile);
		}

	} else {
		sprintf(maskfile, "%s", "none");
	}

	if (strcmp(constraints, "n") != 0 && strcmp(constraints, "no") != 0 &&
			strcmp(constraints, "none") != 0) {
		sprintf(constraintfile, "%s%s%s%s%ld%s",
				cpl_table_get_string(tab, "TILE_DIRECTORY", *j), "/",
				constraints, "_", *j + 1, "_5");

		// Check if accessable

		if(access(constraintfile, 00) != 0) {
			cpl_msg_error(cpl_func, "Constraint file is not "
				"accessable in create_5comp_Setup() for setup "
				"%ld !!! GALFIT will be started anyway but "
				"without constraints.", *j + 1);
		}

		if(debug == 1) {
			printf("GALFIT constraint FILE : %s\n", constraintfile);
		}

	} else {
		sprintf(constraintfile, "%s", "none");
	}

	// Read object data from table

	background  =  cpl_table_get_double(tab, "GALA_BACKGROUND", *j, NULL);
	xc      	=  cpl_table_get_double(tab, "X_IMAGE", *j, NULL);
	yc    	    =  cpl_table_get_double(tab, "Y_IMAGE", *j, NULL);
	aim 		=  cpl_table_get_double(tab, "A_IMAGE", *j, NULL);
	bim 		=  cpl_table_get_double(tab, "B_IMAGE", *j, NULL);
	theta 		=  cpl_table_get_double(tab, "THETA_IMAGE", *j, NULL);
	mag     	=  cpl_table_get_double(tab, "MAG_BEST", *j, NULL);
	fr     	    =  cpl_table_get_double(tab, "FLUX_RADIUS", *j, NULL);
	xlo         =  cpl_table_get_int(tab, "STAMP_XLO", *j, NULL);
	ylo         =  cpl_table_get_int(tab, "STAMP_YLO", *j, NULL);
	xfit  = xc - xlo;
	yfit  = yc - ylo;
	theta = theta - 90;

	// Write GALFIT setup file

	fp_gs = fopen(galsetfile, "w");

	if(fp_gs == NULL) {
		cpl_msg_error(cpl_func, "In create_5comp_setup(): An internal "
				"error occurred. Unable to open file %s", galsetfile);
	} else {
		printf("Slave %d : Opened file %s successfully!\n", rank, galsetfile);
	}

	fprintf(fp_gs, "===================================================\n");
	fprintf(fp_gs, "# IMAGE and GALFIT CONTROL PARAMETERS\n");
	fprintf(fp_gs, "A) %s\n", stamp);
	fprintf(fp_gs, "B) %s\n", galfitim);
	fprintf(fp_gs, "C) none\n");
	fprintf(fp_gs, "D) %s\n", psf);
	fprintf(fp_gs, "E) %f\n", psffactor);
	fprintf(fp_gs, "F) %s\n", maskfile);
	fprintf(fp_gs, "G) %s\n", constraintfile);
	fprintf(fp_gs, "H) %d   %d   %d   %d\n", 1, xsize, 1, ysize);
	fprintf(fp_gs, "I) %d   %d\n", (int)convbox, (int)convbox);
	fprintf(fp_gs, "J) %.4f\n", magzero);
	fprintf(fp_gs, "K) %.5f %.5f\n", platescale, platescale);
	fprintf(fp_gs, "O) %s\n", display);
	fprintf(fp_gs, "P) 0\n\n");

	fprintf(fp_gs, "# sky\n");
	fprintf(fp_gs, "0) sky\n");

	if(skyfix == CPL_TRUE) {
		fprintf(fp_gs, "1) %.3f 0\n", background);
		fprintf(fp_gs, "2) %f 0\n", 0.);
		fprintf(fp_gs, "3) %f 0\n", 0.);
	} else {
		fprintf(fp_gs, "1) %.3f 1\n", background);
		fprintf(fp_gs, "2) %f 1\n", 0.);
		fprintf(fp_gs, "3) %f 1\n", 0.);
	}
	fprintf(fp_gs, "Z) 0\n\n");

	fprintf(fp_gs, "# Sersic function component 1\n");
	fprintf(fp_gs, "0) sersic\n");
	fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xfit, yfit);
	fprintf(fp_gs, "3) %.2f 1\n", mag + 1.193);
	fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));
	fprintf(fp_gs, "5) %.2f 1\n", 2.5);
	fprintf(fp_gs, "9) %.4f 1\n", bim / aim);
	fprintf(fp_gs, "10) %.2f 1\n", theta);
	fprintf(fp_gs, "Z) 0\n\n");

	fprintf(fp_gs, "# Sersic function component 2\n");
	fprintf(fp_gs, "0) sersic\n");
	fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xfit, yfit);
	fprintf(fp_gs, "3) %.2f 1\n", mag + 1.4351);
	fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend) / 2);
	fprintf(fp_gs, "5) %.2f 1\n", 2.5);
	fprintf(fp_gs, "9) %.4f 1\n", 1.);
	fprintf(fp_gs, "10) %.2f 1\n", -10.);
	fprintf(fp_gs, "Z) 0\n\n");

	fprintf(fp_gs, "# Sersic function component 3\n");
	fprintf(fp_gs, "0) sersic\n");
	fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xfit, yfit);
	fprintf(fp_gs, "3) %.2f 1\n", mag + 1.7475);
	fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend) / 4);
	fprintf(fp_gs, "5) %.2f 1\n", 2.5);
	fprintf(fp_gs, "9) %.4f 1\n", 1.);
	fprintf(fp_gs, "10) %.2f 1\n", 10.);
	fprintf(fp_gs, "Z) 0\n\n");

	fprintf(fp_gs, "# Sersic function component 4\n");
	fprintf(fp_gs, "0) sersic\n");
	fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xfit, yfit);
	fprintf(fp_gs, "3) %.2f 1\n", mag + 2.188);
	fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend) / 6);
	fprintf(fp_gs, "5) %.2f 1\n", 2.5);
	fprintf(fp_gs, "9) %.4f 1\n", 1.);
	fprintf(fp_gs, "10) %.2f 1\n", 20.);
	fprintf(fp_gs, "Z) 0\n\n");

	fprintf(fp_gs, "# Sersic function component 5\n");
	fprintf(fp_gs, "0) sersic\n");
	fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xfit, yfit);
	fprintf(fp_gs, "3) %.2f 1\n", mag + 2.94);
	fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend) / 8);
	fprintf(fp_gs, "5) %.2f 1\n", 2.5);
	fprintf(fp_gs, "9) %.4f 1\n", 1.);
	fprintf(fp_gs, "10) %.2f 1\n", 30.);
	fprintf(fp_gs, "Z) 0\n\n");



	// Add secondaries

	help = cpl_table_get_array(tab, "SECONDARY_INDICES", *j);

	secindices = cpl_array_duplicate(help);

	if(debug == 1) {
		printf("SECONDARY_NUMBER_ARRAY:\n");
		cpl_array_dump(secindices, 0,
				cpl_array_get_size(secindices), NULL);
		printf("NUMBER OF SECONDARIES: %d\n",
				(int)cpl_array_get_size(secindices));
	}

	for(i = 0; i < cpl_array_get_size(secindices); i++) {
		if(cpl_array_get(secindices, i, NULL) > 0) {
			secnum++;
		}
	}

	// If secondaries exist, amplify GALFIT setup file for each secondary

	for(lv = 0; lv < secnum; lv++) {

		k = (long)cpl_array_get(secindices, lv, NULL);

		if(k <= 0) {
			cpl_msg_error(cpl_func, "An internal error occured in "
				"create_5comp_setup(). Secondary has negative "
				"table index!");
			break;
		}

		sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", *j));
		sprintf(fitfile, "%s%s%s%ld%s", directory, "/", object, k, ".fits");

		// If fit for secondary exists

		if(access(fitfile, 00) == 0) {

			if(readfits_header(fitfile) >= 0) {

				// Read data from fit

				if((fitsheader = cpl_propertylist_load(fitfile, 2)) != CPL_ERROR_NONE
						|| fitsheader == NULL) {

					if(debug == 1) {
						cpl_msg_error(cpl_func, "Unspecified problem with loading Header in "
								"create_5comp_setup() from %s. "
								"Possibly GALFIT crashed for this object.", fitfile);
					}

					fprintf(fp_gs, "# Sersic function\n");
					fprintf(fp_gs, "0) sersic\n");

					xsec  = xfit + cpl_table_get_double(tab, "X_IMAGE", k - 1, NULL) - xc;
					ysec  = yfit + cpl_table_get_double(tab, "Y_IMAGE", k - 1, NULL) - yc;
					fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xsec, ysec);

					mag = cpl_table_get_double(tab, "MAG_BEST", k - 1, NULL);
					fprintf(fp_gs, "3) %.2f 1\n", mag);

					fr = cpl_table_get_double(tab, "FLUX_RADIUS", k - 1, NULL);

					fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));

					fprintf(fp_gs, "5) %.2f 1\n", 2.5);

					eli = cpl_table_get_double(tab, "ELLIPTICITY", k - 1, NULL);
					fprintf(fp_gs, "9) %.4f 1\n", 1 - eli);

					theta = cpl_table_get_double(tab, "THETA_IMAGE", k - 1, NULL);

					if(theta >= 0) {
						theta = theta - 90;
					} else {
						theta = 90 + theta;
					}
					fprintf(fp_gs, "10) %.2f 1\n", theta);

					fprintf(fp_gs, "Z) 0\n\n");

				} else {

					fprintf(fp_gs, "# Sersic function\n");
					fprintf(fp_gs, "0) sersic\n");

					count = 0;

					if(cpl_propertylist_has(fitsheader, "2_XC") == 1) {
						sprintf(xp, "%s", cpl_propertylist_get_string(fitsheader, "2_XC"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_5comp_setup()!!");
						sprintf(xp, "%s", "1");
					}
					remove_chr(xp);
					ptr = strtok(xp, " ");
					while(ptr != NULL) {
						if(count == 0) {
							xcgalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					if(cpl_propertylist_has(fitsheader, "2_YC") == 1) {
						sprintf(yp, "%s", cpl_propertylist_get_string(fitsheader, "2_YC"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_5comp_setup()!!");
						sprintf(yp, "%s", "1");
					}
					remove_chr(yp);
					ptr = strtok(yp, " ");
					while(ptr != NULL) {
						if(count == 0) {
							ycgalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "1) %.2f %.2f 0 0\n", xcgalfit, ycgalfit);

					if(cpl_propertylist_has(fitsheader, "2_MAG") == 1) {
						sprintf(mg, "%s", cpl_propertylist_get_string(fitsheader, "2_MAG"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_5comp_setup()!!");
						sprintf(mg, "%s", "20");
					}
					remove_chr(mg);
					ptr = strtok(mg, " ");
					while(ptr != NULL) {
						if(count == 0) {
							maggalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "3) %.2f 0\n", maggalfit);

					if(cpl_propertylist_has(fitsheader, "2_RE") == 1) {
						sprintf(re, "%s", cpl_propertylist_get_string(fitsheader, "2_RE"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_5comp_setup()!!");
						sprintf(re, "%s", "20");
					}
					remove_chr(re);
					ptr = strtok(re, " ");
					while(ptr != NULL) {
						if(count == 0) {
							regalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "4) %.2f 0\n", regalfit);

					if(cpl_propertylist_has(fitsheader, "2_N") == 1) {
						sprintf(n, "%s", cpl_propertylist_get_string(fitsheader, "2_N"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_5comp_setup()!!");
						sprintf(n, "%s", "2.5");
					}
					remove_chr(n);
					ptr = strtok(n, " ");
					while(ptr != NULL) {
						if(count == 0) {
							ngalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "5) %.2f 0\n", ngalfit);

					if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
						sprintf(ar, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_5comp_setup()!!");
						sprintf(ar, "%s", "0.8");
					}
					remove_chr(ar);
					ptr = strtok(ar, " ");
					while(ptr != NULL) {
						if(count == 0) {
							argalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "9) %.2f 0\n", argalfit);

					if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
						sprintf(pa, "%s", cpl_propertylist_get_string(fitsheader, "2_PA"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_5comp_setup()!!");
						sprintf(pa, "%s", "0");
					}
					remove_chr(pa);
					ptr = strtok(pa, " ");
					while(ptr != NULL) {
						if(count == 0) {
							pagalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "10) %.2f 0\n", pagalfit);

					fprintf(fp_gs, "Z) 0\n\n");

				}

				cpl_propertylist_delete(fitsheader);
			}

			// If fit for secondary does not exist take SExtractor parameters

		} else {

			fprintf(fp_gs, "# Sersic function\n");
			fprintf(fp_gs, "0) sersic\n");

			xsec  = xfit + cpl_table_get_double(tab, "X_IMAGE", k - 1, NULL) - xc;
			ysec  = yfit + cpl_table_get_double(tab, "Y_IMAGE", k - 1, NULL) - yc;
			fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xsec, ysec);

			mag = cpl_table_get_double(tab, "MAG_BEST", k - 1, NULL);
			fprintf(fp_gs, "3) %.2f 1\n", mag);

			fr = cpl_table_get_double(tab, "FLUX_RADIUS", k - 1, NULL);

			fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));

			fprintf(fp_gs, "5) %.2f 1\n", 2.5);

			eli = cpl_table_get_double(tab, "ELLIPTICITY", k - 1, NULL);
			fprintf(fp_gs, "9) %.4f 1\n", 1 - eli);

			theta = cpl_table_get_double(tab, "THETA_IMAGE", k - 1, NULL);

			if(theta >= 0) {
				theta = theta - 90;
			} else {
				theta = 90 + theta;
			}
			fprintf(fp_gs, "10) %.2f 1\n", theta);

			fprintf(fp_gs, "Z) 0\n\n");
		}
	}

	cpl_array_delete(secindices);

	// Include also potential contrib targets

	help = cpl_table_get_array(tab, "POT_CT_INDICES", *j);

	ctindices = cpl_array_duplicate(help);

	if(debug == 1) {
		printf("CONTRIB_TARGET_ARRAY:\n");
		cpl_array_dump(ctindices, 0,
				cpl_array_get_size(ctindices), NULL);

		printf("NUMBER OF POTENTIAL CONTRIB_TARGETS: %d\n",
				(int)cpl_array_get_size(ctindices));
	}

	// Get number of contribs

	for(i = 0; i < cpl_array_get_size(ctindices); i++) {
		if(cpl_array_get(ctindices, i, NULL) >= 0) {
			ctnum++;
		}
	}

	for(lv = 0; lv < ctnum; lv++) {

		k = cpl_array_get(ctindices, lv, NULL) - 1;

		if(k < 0) {
			cpl_msg_error(cpl_func, "An internal error occured in "
				"create_5comp_setup(). Secondary has negative "
				"table index!");
			break;
		}

		sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", k));
		sprintf(fitfile, "%s%s%s%ld%s", directory, "/", object, k + 1, ".fits");

		// If fit for contrib target exists

		if(access(fitfile, 00) == 0) {

			if(check_contribtarget(tab, object, &*j, &k, &magzero, &exptime,
					&magexclude, &magcrit, &fluxextend) == 0) {

				// Read data from fit

				if((fitsheader = cpl_propertylist_load(fitfile, 2)) != CPL_ERROR_NONE ||
						fitsheader == NULL) {

					if(debug == 1) {
						cpl_msg_error(cpl_func, "Unspecified problem with loading Header in "
							"create_5comp_setup() from %s. "
							"Possibly GALFIT crashed for this object.", fitfile);
					}

					fprintf(fp_gs, "# Sersic function\n");
					fprintf(fp_gs, "0) sersic\n");

					xsec  = cpl_table_get_double(tab, "X_IMAGE", k, NULL) - xlo;
					ysec  = cpl_table_get_double(tab, "Y_IMAGE", k, NULL) - ylo;
					fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xsec, ysec);

					mag = cpl_table_get_double(tab, "MAG_BEST", k, NULL);
					fprintf(fp_gs, "3) %.2f 1\n", mag);

					fr = cpl_table_get_double(tab, "FLUX_RADIUS", k, NULL);
					fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));

					fprintf(fp_gs, "5) %.2f 1\n", 2.5);

					eli = cpl_table_get_double(tab, "ELLIPTICITY", k, NULL);
					fprintf(fp_gs, "9) %.4f 1\n", 1 - eli);

					theta = cpl_table_get_double(tab, "THETA_IMAGE", k, NULL);
					if(theta >= 0) {
						theta = theta - 90;
					} else {
					theta = 90 + theta;
					}
					fprintf(fp_gs, "10) %.2f 1\n", theta);

					fprintf(fp_gs, "Z) 0\n\n");

				} else {

					fprintf(fp_gs, "# Sersic function\n");
					fprintf(fp_gs, "0) sersic\n");

					count = 0;

					if(cpl_propertylist_has(fitsheader, "2_XC") == 1) {
						sprintf(xp, "%s", cpl_propertylist_get_string(fitsheader, "2_XC"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_5comp_setup()!!");
						sprintf(xp, "%s", "1");
					}
					remove_chr(xp);
					ptr = strtok(xp, " ");
					while(ptr != NULL) {
						if(count == 0) {
							xcgalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					if(cpl_propertylist_has(fitsheader, "2_YC") == 1) {
						sprintf(yp, "%s", cpl_propertylist_get_string(fitsheader, "2_YC"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_5comp_setup()!!");
						sprintf(yp, "%s", "1");
					}
					remove_chr(yp);
					ptr = strtok(yp, " ");
					while(ptr != NULL) {
						if(count == 0) {
							ycgalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "1) %.2f %.2f 0 0\n", xcgalfit, ycgalfit);

					if(cpl_propertylist_has(fitsheader, "2_MAG") == 1) {
						sprintf(mg, "%s", cpl_propertylist_get_string(fitsheader, "2_MAG"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_5comp_setup()!!");
						sprintf(mg, "%s", "20");
					}
					remove_chr(mg);
					ptr = strtok(mg, " ");
					while(ptr != NULL) {
						if(count == 0) {
							maggalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "3) %.2f 0\n", maggalfit);

					if(cpl_propertylist_has(fitsheader, "2_RE") == 1) {
						sprintf(re, "%s", cpl_propertylist_get_string(fitsheader, "2_RE"));
					} else {
					cpl_msg_error(cpl_func, "Property not available in create_5comp_setup()!!");
						sprintf(re, "%s", "20");
					}
					remove_chr(re);
					ptr = strtok(re, " ");
					while(ptr != NULL) {
						if(count == 0) {
							regalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "4) %.2f 0\n", regalfit);

					if(cpl_propertylist_has(fitsheader, "2_N") == 1) {
						sprintf(n, "%s", cpl_propertylist_get_string(fitsheader, "2_N"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_5comp_setup()!!");
						sprintf(n, "%s", "2.5");
					}
					remove_chr(n);
					ptr = strtok(n, " ");
					while(ptr != NULL) {
						if(count == 0) {
							ngalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "5) %.2f 0\n", ngalfit);

					if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
						sprintf(ar, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_5comp_setup()!!");
						sprintf(ar, "%s", "0.8");
					}
					remove_chr(ar);
					ptr = strtok(ar, " ");
					while(ptr != NULL) {
						if(count == 0) {
							argalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "9) %.2f 0\n", argalfit);

					if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
						sprintf(pa, "%s", cpl_propertylist_get_string(fitsheader, "2_PA"));
					} else {
						cpl_msg_error(cpl_func, "Property not available in create_5comp_setup()!!");
						sprintf(pa, "%s", "0");
					}
					remove_chr(pa);
					ptr = strtok(pa, " ");
					while(ptr != NULL) {
						if(count == 0) {
							pagalfit = atof(ptr);
						}
						ptr = strtok(NULL, " ");
						count ++;
					}
					count = 0;

					fprintf(fp_gs, "10) %.2f 0\n", pagalfit);
					fprintf(fp_gs, "Z) 0\n\n");
				}

				cpl_propertylist_delete(fitsheader);
			}

		} else {

			if(check_contribtarget_sexdata(tab, &*j, &k, &magzero, &exptime,
					&magexclude, &magcrit, &fluxextend) == 0) {

				fprintf(fp_gs, "# Sersic function\n");
				fprintf(fp_gs, "0) sersic\n");

				xsec  = cpl_table_get_double(tab, "X_IMAGE", k, NULL) - xlo;
				ysec  = cpl_table_get_double(tab, "Y_IMAGE", k, NULL) - ylo;
				fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xsec, ysec);

				mag = cpl_table_get_double(tab, "MAG_BEST", k, NULL);
				fprintf(fp_gs, "3) %.2f 1\n", mag);

				fr = cpl_table_get_double(tab, "FLUX_RADIUS", k, NULL);
				fprintf(fp_gs, "4) %.2f 1\n", pow(fr, fluxextend));

				fprintf(fp_gs, "5) %.2f 1\n", 2.5);

				eli = cpl_table_get_double(tab, "ELLIPTICITY", k, NULL);
				fprintf(fp_gs, "9) %.4f 1\n", 1 - eli);

				theta = cpl_table_get_double(tab, "THETA_IMAGE", k, NULL);
				if(theta >= 0) {
					theta = theta - 90;
				} else {
				theta = 90 + theta;
				}
				fprintf(fp_gs, "10) %.2f 1\n", theta);

				fprintf(fp_gs, "Z) 0\n\n");
			}
		}
	}

	cpl_array_delete(ctindices);

	fclose(fp_gs);

	/* Clean up */

	cpl_propertylist_delete(header);
	cpl_table_delete(tab);

	return CPL_ERROR_NONE;
}


/*******************************************************************

Run GALFIT fourier modes.

********************************************************************/

cpl_error_code run_galfit_fourier_modes(cpl_parameterlist *gala_setup) {

	int j,
		synch,
		my_rank,   /* rank of process */
	 	numprocs;

	MPI_Status status;             // MPI status

	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* find out number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	/* Starting message */
	if(my_rank == 0) {
		cpl_msg_info(cpl_func, "Running GALFIT Fourier Modes.");
	}

	/* Distribute Fourier modes fitting jobs */
	distribute_fourier_jobs(gala_setup);

    /* synchronize processes */
    if(my_rank == 0) {
    	for(j = 1; j < numprocs; j++) {
    		synch = 1;
    		MPI_Send(&synch, sizeof(int), MPI_INT, j, 25, MPI_COMM_WORLD);
    	}
    } else {
    		MPI_Recv(&synch, sizeof(int), MPI_INT, 0, 25, MPI_COMM_WORLD, &status);
    }
    MPI_Barrier(MPI_COMM_WORLD);

	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    /* Write Fourier results into table */
    if(my_rank == 0) {
    	write_fourier_results(gala_setup);
    }

    /* synchronize processes */
    if(my_rank == 0) {
    	for(j = 1; j < numprocs; j++) {
    		synch = 1;
    		MPI_Send(&synch, sizeof(int), MPI_INT, j, 25, MPI_COMM_WORLD);
    	}
    } else {
    		MPI_Recv(&synch, sizeof(int), MPI_INT, 0, 25, MPI_COMM_WORLD, &status);
    }
    MPI_Barrier(MPI_COMM_WORLD);

	return CPL_ERROR_NONE;
}


/*******************************************************************

Distribute the GALFIT jobs with n components among the processors.
The corresponding table indices are read from the array objindices.

********************************************************************/

cpl_error_code distribute_fourier_jobs(cpl_parameterlist *gala_setup) {

	int my_rank;   /* rank of process */
	int slaverank; /* rank of slave */
	int np;         /* number of processes */
	int a;
	int i = 0;     /* looping variable */
	int j = 0;     /* looping variable */
	int k = 0;     /* looping variable */
	int idx;       /* object index in table */
	int ncomp = 1;

	long nrow;

	char tabfile[FILENAME_MAX],
		 outdir[FILENAME_MAX],
		 combcatname[FILENAME_MAX];

	cpl_parameter *p;

	cpl_table *tab;


	MPI_Status status;


	/* find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* find out number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	/* MASTER job */
	if(my_rank == 0) {

		/* check number of jobs */

		/* Load variables from setup parameterlist */

	    p = cpl_parameterlist_find(gala_setup, "outdir");
	    sprintf(outdir, "%s", cpl_parameter_get_string(p));

	    p = cpl_parameterlist_find(gala_setup, "sexcomb");
	    sprintf(combcatname, "%s", cpl_parameter_get_string(p));

		/* Read values from a table (read-only!!!) copy */

		sprintf(tabfile, "%s%s%s", outdir, "/", combcatname);

		if(access(tabfile, 00) != 0) {
			cpl_msg_error(cpl_func, "In distribute_fourier_mode_jobs() : "
					"Table %s was not accessable! Aborting...", tabfile);
			return CPL_ERROR_DATA_NOT_FOUND;
		}

		/* Load table and check*/

		tab = cpl_table_load(tabfile, 1, 0);

		nrow = (long) cpl_table_get_nrow(tab);

		if(nrow <= 0) {
			cpl_msg_error(cpl_func, "In create_5comp_setup() : "
					"Input table %s is empty or not readable. Aborting...",
					tabfile);
			cpl_table_delete(tab);
			return CPL_ERROR_DATA_NOT_FOUND;
		}

	    cpl_table_delete(tab);

	    /* Starting message */

		cpl_msg_info(cpl_func, "Distributing %ld GALFIT Fourier mode "
				"jobs.", nrow);

		/* distribute jobs among all slaves */
    	for(i = 0; i < nrow; i++) {

    		/* receive a meassge from a slave which needs a job */
    		MPI_Recv(&slaverank, sizeof(int), MPI_INT, MPI_ANY_SOURCE,
				11, MPI_COMM_WORLD, &status);

    		a = i;

			/* send job ID to slave */
    		MPI_Send(&a, sizeof(int), MPI_INT, slaverank, 22,
					MPI_COMM_WORLD);
    	}

    	MPI_Comm_size(MPI_COMM_WORLD, &np);

    	for(k = 1; k < np; k++) {

    		idx = -1;

			/* send job ID to slave */
    		MPI_Send(&idx, sizeof(int), MPI_INT, k, 22,
					MPI_COMM_WORLD);
    	}

	/* SLAVE job */
	} else {

		/* accept jobs as long as there are  indices in the fitlist */
		while(j != -1) {

			/* send a message to MASTER that a job is needed */
			MPI_Send(&my_rank, sizeof(int), MPI_INT, 0, 11, MPI_COMM_WORLD);

			/* receive job ID from MASTER */
			MPI_Recv(&j, sizeof(int), MPI_INT, 0, 22, MPI_COMM_WORLD, &status);

			if(j != -1) {

				printf("\n\nSLAVE %d : Fitting Fourier modes for object %d\n",
						my_rank, j + 1);

				/* start the fitting job */
				if(j >= 0) {

					GALFIT_fourier_modes(&j, ncomp, gala_setup);

				}

				printf("SLAVE %d : Fitting Fourier modes for object %d DONE !!\n\n",
						my_rank, j + 1);

//				/* check errorstate */
//				printf("-------------ERRORSTATE DUMP %d ------------------\n", j);
//				cpl_errorstate_dump(err_state, CPL_FALSE, cpl_errorstate_dump_one);
//				sleep(20);
			}
		}
	}

	return CPL_ERROR_NONE;
}


cpl_error_code GALFIT_fourier_modes(const int *idx,
		int ncomp, cpl_parameterlist *gala_setup) {

	int num,
		xsize,
		ysize,
		j,
		lv,
		ctnum = 0,
		count;

	long k,
		 nrow,
		 idxl;

	double background,
		   re,
		   n,
		   ar,
		   theta,
		   mag,
		   xfit,
		   yfit,
		   convbox,
		   psffactor,
		   magzero,
		   platescale,
		   exptime,
		   fluxextend,
		   magexclude,
		   magcrit,
		   xcgalfit = 0,
		   ycgalfit = 0,
		   maggalfit = 0,
		   regalfit = 0,
		   ngalfit = 0,
		   argalfit = 0,
		   pagalfit = 0;

	char stamp[FILENAME_MAX],
		 constraintfile[FILENAME_MAX],
		 galfitim[FILENAME_MAX],
		 tabfile[FILENAME_MAX],
		 fitfile[FILENAME_MAX],
		 sexcomb[FILENAME_MAX],
		 outdir[FILENAME_MAX],
		 stampfile[FILENAME_MAX],
		 stampname[FILENAME_MAX],
		 galfitset[FILENAME_MAX],
		 object[FILENAME_MAX],
		 display[FILENAME_MAX],
		 psf[FILENAME_MAX],
		 badpix[FILENAME_MAX],
		 maskfile[FILENAME_MAX],
		 directory[FILENAME_MAX],
		 filename[FILENAME_MAX],
		 path[FILENAME_MAX],
		 str[FILENAME_MAX],
		 xp[FILENAME_MAX],
		 yp[FILENAME_MAX],
		 mg[FILENAME_MAX],
		 r[FILENAME_MAX],
		 sersic[FILENAME_MAX],
		 axr[FILENAME_MAX],
		 pa[FILENAME_MAX],
		 fitlog[FILENAME_MAX],
		 act[FILENAME_MAX],
	     curr_dir[FILENAME_MAX];

	char *buf = NULL;

	char *ptr;

	size_t size = 0;

	cpl_array *ncomp_results, *ctindices;
	const cpl_array *help;

	cpl_boolean skyfix = CPL_TRUE;

	cpl_errorstate errornone = CPL_ERROR_NONE;

	cpl_errorstate error;

	cpl_parameter *p;

	cpl_propertylist *fitsheader;

	cpl_table *tab;

	FILE *fp_gs;


	/* Check errorstate */
	error = cpl_errorstate_get();
	if(error != CPL_ERROR_NONE) {
		cpl_msg_info(cpl_func, "Errorstate already existed before "
				"create_fourier_mode_setup(). Is cleaned now...");
		cpl_errorstate_set(errornone);
	}

	/* Starting message */
	cpl_msg_info(cpl_func, "Creating GALFIT Fourier Mode setup for "
			"object index %d.", *idx);

    p = cpl_parameterlist_find(gala_setup, "sexcomb");
    sprintf(sexcomb, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "outdir");
    sprintf(outdir, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "stampfile");
    sprintf(stampfile, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "stampname");
    sprintf(stampname, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "outdir");
    sprintf(outdir, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "galfitset");
    sprintf(galfitset, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "object");
    sprintf(object, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "convbox");
    convbox = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magzero");
    magzero = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magcrit");
    magcrit = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magexclude");
    magexclude = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "fluxextend");
    fluxextend = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "platescale");
    platescale = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "display");
    sprintf(display, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "psf");
    sprintf(psf, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "psffactor");
    psffactor = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "badpix");
    sprintf(badpix, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "path");
    sprintf(path, "%s", cpl_parameter_get_string(p));


	/* Load table */
    sprintf(tabfile, "%s%s%s", outdir, "/", sexcomb);
	tab = cpl_table_load(tabfile, 1, 0);

	nrow = (long) cpl_table_get_nrow(tab);

	if(nrow <= 0) {
		cpl_msg_error(cpl_func, "In create_GALFIT_setup_1comp() : "
				"Input table %s is empty or not readable. Aborting...",
				tabfile);
		cpl_table_delete(tab);
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", *idx));
	sprintf(fitfile, "%s%s%s%d%s", directory, "/", object, *idx + 1, ".fits");

	/* Check if single Sersic fit is existing */
	if(access(fitfile, 00) != 0) {
		cpl_msg_info(cpl_func, "Single Sersic fit for "
				"object index %d is not existing! Aborting...", *idx);
		cpl_table_delete(tab);
		return CPL_ERROR_NONE;
	}

	/* Get SExtractor number of current object */
	num = cpl_table_get(tab, "NUMBER", *idx, NULL);

	/* stampfile */
	sprintf(stamp, "%s%s%s%s%s%s%d%s%s%s",
			cpl_table_get_string(tab, "TILE_DIRECTORY", *idx),
			"/", stampfile, "/", stampname, "_", num, "_",
			cpl_table_get_string(tab, "TILE", *idx), ".fits");

	/* GALFIT imageblock filename */
	sprintf(galfitim, "%s%s%s%d%s", directory, "/", object,
			*idx + 1, "_Fourier.fits");

	/* GALFIT mask filename */
	sprintf(maskfile, "%s%s%s%s%d%s",
			cpl_table_get_string(tab, "TILE_DIRECTORY", *idx),
			"/", badpix, "_", *idx + 1, ".fits");

	/* GALFIT constraint filename */
	sprintf(constraintfile, "%s", "none");

	/* Read object data from table */
	background  =  cpl_table_get_double(tab, "GALA_BACKGROUND", *idx, NULL);

	/* Prepare filename paths and input data for setup file */
	xsize = cpl_table_get_int(tab, "STAMP_XHI",*idx, NULL) -
			cpl_table_get_int(tab, "STAMP_XLO",*idx, NULL) + 1;
	ysize = cpl_table_get_int(tab, "STAMP_YHI",*idx, NULL) -
			cpl_table_get_int(tab, "STAMP_YLO",*idx, NULL) + 1;
	if(xsize <= 0 || ysize <= 0) {
		cpl_msg_error(cpl_func, "In create_GALFIT_fourier_mode_setup() "
				": Stamp image not found!");
	}

	ncomp_results = read_ncomp_results(fitfile, &ncomp);

	xfit  = cpl_array_get_double(ncomp_results, 0, NULL);
	yfit  = cpl_array_get_double(ncomp_results, 1, NULL);
	mag   = cpl_array_get_double(ncomp_results, 2, NULL);
	re    = cpl_array_get_double(ncomp_results, 3, NULL);
	n     = cpl_array_get_double(ncomp_results, 4, NULL);
	ar    = cpl_array_get_double(ncomp_results, 5, NULL);
	theta = cpl_array_get_double(ncomp_results, 6, NULL);


	/* Write GALFIT setup file */
	sprintf(filename, "%s%s%s%s%d%s", directory, "/", galfitset, "_",
			*idx + 1, "_Fourier");

	fp_gs = fopen(filename, "w");

	/* header */
	fprintf(fp_gs, "===================================================\n");
	fprintf(fp_gs, "# IMAGE and GALFIT CONTROL PARAMETERS\n");
	fprintf(fp_gs, "A) %s\n", stamp);
	fprintf(fp_gs, "B) %s\n", galfitim);
	fprintf(fp_gs, "C) none\n");
	fprintf(fp_gs, "D) %s\n", psf);
	fprintf(fp_gs, "E) %f\n", psffactor);
	fprintf(fp_gs, "F) %s\n", maskfile);
	fprintf(fp_gs, "G) %s\n", constraintfile);
	fprintf(fp_gs, "H) %d   %d   %d   %d\n", 1, xsize, 1, ysize);
	fprintf(fp_gs, "I) %d   %d\n", (int)convbox, (int)convbox);
	fprintf(fp_gs, "J) %.4f\n", magzero);
	fprintf(fp_gs, "K) %.5f %.5f\n", platescale, platescale);
	fprintf(fp_gs, "O) %s\n", display);
	fprintf(fp_gs, "P) 0\n\n");

	/* sky */
	fprintf(fp_gs, "# sky\n");
	fprintf(fp_gs, "0) sky\n");
	if(skyfix == CPL_TRUE) {  /* fit sky value or leave free */
		if(isnan(background) == 0) {
			fprintf(fp_gs, "1) %.3f 0\n", background);
		} else {
			fprintf(fp_gs, "1) 0 1\n");
		}
		fprintf(fp_gs, "2) %f 0\n", 0.);
		fprintf(fp_gs, "3) %f 0\n", 0.);
	} else {
		fprintf(fp_gs, "1) %.3f 1\n", background);
		fprintf(fp_gs, "2) %f 1\n", 0.);
		fprintf(fp_gs, "3) %f 1\n", 0.);
	}
	fprintf(fp_gs, "Z) 0\n\n");

	/* 1st Sersic component */
	fprintf(fp_gs, "# Sersic function\n");
	fprintf(fp_gs, "0) sersic\n");
	fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xfit, yfit);
	fprintf(fp_gs, "3) %.2f 1\n", mag);
	fprintf(fp_gs, "4) %.2f 1\n", re);
	fprintf(fp_gs, "5) %.2f 1\n", n);
	fprintf(fp_gs, "9) %.4f 1\n", ar);
	fprintf(fp_gs, "10) %.2f 1\n", theta);
	fprintf(fp_gs, "Z) 0\n\n");
	fprintf(fp_gs, "#  Azimuthal fourier modes\n");
	fprintf(fp_gs, "F1)  0.01  0.01  1  1\n");

	fclose(fp_gs);

	/* attach secondaries to the setup file */
	if(cpl_table_has_column(tab, "SECONDARY_INDICES") == 1) {

		attach_secondaries(tab, gala_setup, filename, &*idx);

	} else {

		cpl_msg_info(cpl_func, "Secondary indices are not avaiable "
				"in table and are not included in the setup files!");
	}

	// Include also potential contrib targets

	help = cpl_table_get_array(tab, "POT_CT_INDICES", *idx);

	ctindices = cpl_array_duplicate(help);

	// Get number of contribs

	ctnum = 0;

	for(j = 0; j < (int)cpl_array_get_size(ctindices); j++) {
		if(cpl_array_get(ctindices, j, NULL) > 0) {
			ctnum++;
		}
	}

	for(lv = 0; lv < ctnum; lv++) {

		k = (long)cpl_array_get(ctindices, lv, NULL) - 1;

		if(k < 0) {
			cpl_msg_error(cpl_func, "An internal error occurred in "
				"attach_contribtargets(). CT has negative "
				"table index! Number of ct object %d : "
				"%d. Lv : %d  Secondary Index : %ld\n", *idx, ctnum, lv, k);
			break;
		}

//		if(debug == 1) {
			cpl_msg_info(cpl_func, "Check potential contrib target No %ld "
				"for object No %d.\n", k + 1, *idx + 1);
//		}

		sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", k));
		sprintf(fitfile, "%s%s%s%ld%s", directory, "/", object, k + 1, ".fits");

		// If fit for contrib target exists

		if(access(fitfile, 00) == 0) {

			idxl = (long)*idx;

//			printf("Vor check_contribtarget() :\n"
//					"idxl : %ld\n"
//					"k : %ld\n"
//					"magzero : %f\n"
//					"magexclude : %f\n"
//					"magcrit : %f\n"
//					"fluxextend : %f\n", idxl, k, magzero, magexclude,
//					magcrit, fluxextend);

			exptime = read_exptime(stamp);

			if(exptime <= 0) {
				cpl_msg_error(cpl_func, "Exptime is 0 or negative in "
						"run_GALFIT_fourier_modes()! Internal error "
						"for object %s!", stamp);
				break;
			}

			if(check_contribtarget(tab, object, &idxl, &k, &magzero,
					&exptime, &magexclude, &magcrit, &fluxextend) == 0) {

				printf("%s identified as contrib target!\n", fitfile);

				// Read data from fit

				fitsheader = cpl_propertylist_load(fitfile, 2);

				fp_gs = fopen(filename, "a");

				fprintf(fp_gs, "# Sersic function\n");
				fprintf(fp_gs, "0) sersic\n");

				count = 0;

				if(cpl_propertylist_has(fitsheader, "2_XC") == 1) {
					sprintf(str, "%s",
							cpl_propertylist_get_string(fitsheader, "2_XC"));
					sprintf(xp, "%s",
							cpl_propertylist_get_string(fitsheader, "2_XC"));
				} else {
					cpl_msg_error(cpl_func, "Property not available "
							"in create_GALFIT_setup()!!");
					sprintf(xp, "%s", "1");
				}
				remove_chr(xp);
				ptr = strtok(xp, " ");
				while(ptr != NULL) {
					if(count == 0) {
						xcgalfit = atof(ptr);
					}
					ptr = strtok(NULL, " ");
					count ++;
				}
				count = 0;

				if(cpl_propertylist_has(fitsheader, "2_YC") == 1) {
					sprintf(str, "%s",
							cpl_propertylist_get_string(fitsheader, "2_YC"));
					sprintf(yp, "%s",
							cpl_propertylist_get_string(fitsheader, "2_YC"));
				} else {
					cpl_msg_error(cpl_func, "Property not available in "
							"create_GALFIT_setup()!!");
					sprintf(yp, "%s", "1");
				}
				remove_chr(yp);
				ptr = strtok(yp, " ");
				while(ptr != NULL) {
					if(count == 0) {
						ycgalfit = atof(ptr);
					}
					ptr = strtok(NULL, " ");
					count ++;
				}
				count = 0;

				/* transform into local stamp coordinates */
				xcgalfit  = (double)cpl_table_get_int(tab, "STAMP_XLO", k, NULL)
						+xcgalfit-
						(double)cpl_table_get_int(tab, "STAMP_XLO", *idx, NULL);

				ycgalfit  = (double)cpl_table_get_int(tab, "STAMP_YLO", k, NULL)
						+ycgalfit-
						(double)cpl_table_get_int(tab, "STAMP_YLO", *idx, NULL);

				fprintf(fp_gs, "1) %.2f %.2f 1 1\n", xcgalfit, ycgalfit);

				if(cpl_propertylist_has(fitsheader, "2_MAG") == 1) {
					sprintf(str, "%s",
							cpl_propertylist_get_string(fitsheader, "2_MAG"));
					sprintf(mg, "%s",
							cpl_propertylist_get_string(fitsheader, "2_MAG"));
				} else {
					cpl_msg_error(cpl_func, "Property not available in "
							"create_GALFIT_setup()!!");
					sprintf(mg, "%s", "20");
				}
				remove_chr(mg);
				ptr = strtok(mg, " ");
				while(ptr != NULL) {
					if(count == 0) {
						maggalfit = atof(ptr);
					}
					ptr = strtok(NULL, " ");
					count ++;
				}
				count = 0;

				fprintf(fp_gs, "3) %.2f 0\n", maggalfit);

				if(cpl_propertylist_has(fitsheader, "2_RE") == 1) {
					sprintf(str, "%s",
							cpl_propertylist_get_string(fitsheader, "2_RE"));
					sprintf(r, "%s",
							cpl_propertylist_get_string(fitsheader, "2_RE"));
				} else {
					cpl_msg_error(cpl_func, "Property not available in "
							"create_GALFIT_setup()!!");
					sprintf(r, "%s", "20");
				}
				remove_chr(r);
				ptr = strtok(r, " ");
				while(ptr != NULL) {
					if(count == 0) {
						regalfit = atof(ptr);
					}
					ptr = strtok(NULL, " ");
					count ++;
				}
				count = 0;

				fprintf(fp_gs, "4) %.2f 0\n", regalfit);

				if(cpl_propertylist_has(fitsheader, "2_N") == 1) {
					sprintf(str, "%s",
							cpl_propertylist_get_string(fitsheader, "2_N"));
					sprintf(sersic, "%s",
							cpl_propertylist_get_string(fitsheader, "2_N"));
				} else {
					cpl_msg_error(cpl_func, "Property not available in "
							"create_GALFIT_setup()!!");
					sprintf(sersic, "%s", "2.5");
				}
				remove_chr(sersic);
				ptr = strtok(sersic, " ");
				while(ptr != NULL) {
					if(count == 0) {
						ngalfit = atof(ptr);
					}
					ptr = strtok(NULL, " ");
					count ++;
				}
				count = 0;

				fprintf(fp_gs, "5) %.2f 0\n", ngalfit);

				if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
					sprintf(str, "%s",
							cpl_propertylist_get_string(fitsheader, "2_AR"));
					sprintf(axr, "%s",
							cpl_propertylist_get_string(fitsheader, "2_AR"));
				} else {
					cpl_msg_error(cpl_func, "Property not available in "
							"create_GALFIT_setup()!!");
					sprintf(axr, "%s", "0.8");
				}
				remove_chr(axr);
				ptr = strtok(axr, " ");
				while(ptr != NULL) {
					if(count == 0) {
						argalfit = atof(ptr);
					}
					ptr = strtok(NULL, " ");
					count ++;
				}
				count = 0;

				fprintf(fp_gs, "9) %.2f 0\n", argalfit);

				if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
					sprintf(str, "%s",
							cpl_propertylist_get_string(fitsheader, "2_AR"));
					sprintf(pa, "%s",
							cpl_propertylist_get_string(fitsheader, "2_PA"));
				} else {
					cpl_msg_error(cpl_func, "Property not available in "
							"create_GALFIT_setup()!!");
					sprintf(pa, "%s", "0");
				}
				remove_chr(pa);
				ptr = strtok(pa, " ");
				while(ptr != NULL) {
					if(count == 0) {
						pagalfit = atof(ptr);
					}
					ptr = strtok(NULL, " ");
					count ++;
				}
				count = 0;

				fprintf(fp_gs, "10) %.2f 0\n", pagalfit);
				fprintf(fp_gs, "Z) 0\n\n");

				fclose(fp_gs);

				cpl_propertylist_delete(fitsheader);

			} else {

				printf("%s identified as NO contrib target!\n", fitfile);
			}
		}
	}

	cpl_array_delete(ctindices);


	// xxx to debug!
	/* attach contributing sources to the setup file */
//	if(cpl_table_has_column(tab, "POT_CT_INDICES") == 1) {
//
//		idxl = (long) idx;
//
//		/* read exposure time from header */
//		exptime = read_exptime(galfitim);
//		if(exptime <= 0) {
//			cpl_msg_error(cpl_func, "In run_GALFIT_fourier_modeS() : "
//					"Exptime not found. Aborting...");
//		}
//
//
//		attach_contribtargets(tab, gala_setup, filename,
//				&idxl, &exptime);
//
//	} else {
//
//		cpl_msg_info(cpl_func, "Contrib target indices are not avaiable "
//			"in table and are not included in the setup files!");
//	}


	cpl_array_delete(ncomp_results);
	cpl_table_delete(tab);

	/* Start GALFIT Fourier Modes */

	if(access(galfitim, 00) != 0) {

		sprintf(str, "%s %s %s", path, filename, "> /dev/null");

		if(system(str) != 0) {
			cpl_msg_error(cpl_func, "System call in galapagos_utils() "
				"failed!");
		}
	}

	/* Clean up */

	/* Find current working directory */

	sprintf(curr_dir, "%s", getcwd(buf, size));

	sprintf(fitlog, "%s%s", curr_dir, "/fit.log");
//	sprintf(fitlog, "%s", "/home/andi/STAGES/Fourier/Code/fit.log");
//	sprintf(fitlog, "%s", "/home/andi/workspace/GALAPAGOS_04_13"
//	    			    				"/src/Debug/fit.log");
	if(access(fitlog, 00) == 0) {
		remove(fitlog);
	}

//   	sprintf(fitfile, "%s", "/home/andi/workspace/GALAPAGOS_04_13"
//	    			    				"/src/Debug/galfit.01");
//   	sprintf(act, "%s", "/home/andi/workspace/GALAPAGOS_04_13"
//	    			    				"/src/Debug/galfit.*");

   	sprintf(fitfile, "%s%s", curr_dir, "/galfit.01");
   	sprintf(act, "%s%s%s", "rm ", curr_dir, "/galfit.*");

   	if(access(fitfile, 00) == 0) {
		if(system(act) != 0) {
			cpl_msg_error(cpl_func, "System call in galapagos_utils() "
				"failed!");
		}
	}

//  sprintf(fitfile, "%s", "/home/andi/STAGES/Fourier/Code/galfit.01");
//  sprintf(act, "%s", "rm /home/andi/STAGES/Fourier/Code/galfit.*");
//  if(access(fitfile, 00) == 0) {
//		system(act);
//	}

	return CPL_ERROR_NONE;
}


/*******************************************************************

Read fit results from an n component fit into an array.
0: x
1: y
2: mag
3: re
4: n
5: ar
6: pa

********************************************************************/

cpl_array *read_ncomp_results(const char *galfitim, const int *ncomp) {

	int i;

	double xcgalfit,
		   ycgalfit,
		   maggalfit,
		   regalfit,
		   ngalfit,
		   argalfit,
		   pagalfit;

	char nx[FILENAME_MAX],
	       ny[FILENAME_MAX],
	       nmag[FILENAME_MAX],
	       nre[FILENAME_MAX],
	       nn[FILENAME_MAX],
	       nar[FILENAME_MAX],
	       npa[FILENAME_MAX],
	       str[FILENAME_MAX];

	char *ptr;


	cpl_array *results;

	cpl_propertylist *header;

	cpl_errorstate errstate;


	/* check input */
	if(access(galfitim, 00) != 0) {
		cpl_msg_error(cpl_func, "In read_resfile() : Residual file "
				"%s not found. Aborting...", galfitim);
	}

	/* initialize results array */
	results = cpl_array_new(7 * *ncomp, CPL_TYPE_DOUBLE);
	for(i = 0; i < 7 * *ncomp; i++) {
		cpl_array_set_int(results, i, 0);
	}

	/* load header */
	cpl_errorstate_set(CPL_ERROR_NONE);

	header = cpl_propertylist_load(galfitim, 2);

	errstate = cpl_errorstate_get();

	if(errstate != CPL_ERROR_NONE) {
		cpl_msg_error(cpl_func, "In read_fit_stars() : Unspecified "
				"problem with loading fitsheader for %s.", galfitim);
		cpl_propertylist_delete(header);
		for(i = 0; i < 7 * *ncomp; i++) {
			cpl_array_set_int(results, i, 99999);
		}
		return results;
	}

	for(i = 1; i <= *ncomp; i++) {

		sprintf(nx, "%d%s", i + 1, "_XC");

		if(cpl_propertylist_has(header, nx) == 1) {
			sprintf(str, "%s", cpl_propertylist_get_string(header, nx));
		} else {
			cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
			sprintf(str, "%s", "99999");
		}
		remove_chr(str);

		ptr = strtok(str, " ");
		xcgalfit = atof(ptr);
		ptr = strtok(NULL, " ");

		cpl_array_set_double(results, (i - 1) * 7, xcgalfit);


		sprintf(ny, "%d%s", i + 1, "_YC");

		if(cpl_propertylist_has(header, ny) == 1) {
			sprintf(str, "%s", cpl_propertylist_get_string(header, ny));
		} else {
			cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
			sprintf(str, "%s", "99999");
		}
		remove_chr(str);

		ptr = strtok(str, " ");
		ycgalfit = atof(ptr);
		ptr = strtok(NULL, " ");

		cpl_array_set_double(results, (i - 1) * 7 + 1, ycgalfit);


		sprintf(nmag, "%d%s", i + 1, "_MAG");

		if(cpl_propertylist_has(header, nmag) == 1) {
			sprintf(str, "%s", cpl_propertylist_get_string(header, nmag));
		} else {
			cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
			sprintf(str, "%s", "99999");
		}
		remove_chr(str);

		ptr = strtok(str, " ");
		maggalfit = atof(ptr);
		ptr = strtok(NULL, " ");

		cpl_array_set_double(results, (i - 1) * 7 + 2, maggalfit);


		sprintf(nre, "%d%s", i + 1, "_RE");

		if(cpl_propertylist_has(header, nre) == 1) {
			sprintf(str, "%s", cpl_propertylist_get_string(header, nre));
		} else {
			cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
			sprintf(str, "%s", "99999");
		}
		remove_chr(str);

		ptr = strtok(str, " ");
		regalfit = atof(ptr);
		ptr = strtok(NULL, " ");

		cpl_array_set_double(results, (i - 1) * 7 + 3, regalfit);


		sprintf(nn, "%d%s", i + 1, "_N");

		if(cpl_propertylist_has(header, nn) == 1) {
			sprintf(str, "%s", cpl_propertylist_get_string(header, nn));
		} else {
			cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
			sprintf(str, "%s", "99999");
		}
		remove_chr(str);

		ptr = strtok(str, " ");
		ngalfit = atof(ptr);
		ptr = strtok(NULL, " ");

		cpl_array_set_double(results, (i - 1) * 7 + 4, ngalfit);


		sprintf(nar, "%d%s", i + 1, "_AR");

		if(cpl_propertylist_has(header, nn) == 1) {
			sprintf(str, "%s", cpl_propertylist_get_string(header, nar));
		} else {
			cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
			sprintf(str, "%s", "99999");
		}
		remove_chr(str);

		ptr = strtok(str, " ");
		argalfit = atof(ptr);
		ptr = strtok(NULL, " ");

		cpl_array_set_double(results, (i - 1) * 7 + 5, argalfit);


		sprintf(npa, "%d%s", i + 1, "_PA");

		if(cpl_propertylist_has(header, npa) == 1) {
			sprintf(str, "%s", cpl_propertylist_get_string(header, npa));
		} else {
			cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
			sprintf(str, "%s", "99999");
		}
		remove_chr(str);

		ptr = strtok(str, " ");
		pagalfit = atof(ptr);
		ptr = strtok(NULL, " ");

		cpl_array_set_double(results, (i - 1) * 7 + 6, pagalfit);
	}

	errstate = cpl_errorstate_get();

	if(errstate != CPL_ERROR_NONE) {
		cpl_msg_error(cpl_func, "In read_fit_stars() : Unspecified "
				"problem with reading fitsheader for %s.", galfitim);
	}

	cpl_propertylist_delete(header);

	return results;
}


/*******************************************************************

Write Fourier fit results into combined catalog.

Result array structure for every object:
0: F1
1: F1PA
2: F3
3: F3PA
4: F4
5: F4PA
6: F5
7: F5PA

********************************************************************/

cpl_error_code write_fourier_results(cpl_parameterlist *gala_setup) {

	int ncomp = 1;

	long i,
		 nrow;

	char tabfile[FILENAME_MAX],
		 fitfile[FILENAME_MAX],
		 sexcomb[FILENAME_MAX],
		 outdir[FILENAME_MAX],
		 object[FILENAME_MAX],
		 directory[FILENAME_MAX];

	cpl_array *results, *sersic_comp;

	cpl_parameter *p;

	cpl_table *tab;

	cpl_errorstate error;


    p = cpl_parameterlist_find(gala_setup, "sexcomb");
    sprintf(sexcomb, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "outdir");
    sprintf(outdir, "%s", cpl_parameter_get_string(p));

    p = cpl_parameterlist_find(gala_setup, "object");
    sprintf(object, "%s", cpl_parameter_get_string(p));

	/* Load table */
    sprintf(tabfile, "%s%s%s", outdir, "/", sexcomb);

    /* Starting message */
    if(access(tabfile, 00) != 0) {
    	cpl_msg_info(cpl_func, "No combined catalog "
    			"found.");
    	return CPL_ERROR_NONE;

    } else {
    	cpl_msg_info(cpl_func, "Writing GALFIT Fourier "
    			"parameters into combined catalog.");
    }

	tab = cpl_table_load(tabfile, 1, 0);

	nrow = (long) cpl_table_get_nrow(tab);

	if(nrow <= 0) {
		cpl_msg_error(cpl_func, "In write Fourier_modes_results() : "
				"Input table %s is empty or not readable. Aborting...",
				tabfile);
		cpl_table_delete(tab);
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	cpl_table_new_column(tab, "X_GALFIT_FM", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "Y_GALFIT_FM", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "MAG_GALFIT_FM", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "RE_GALFIT_FM", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "SERSIC_GALFIT_FM", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "AR_GALFIT_FM", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "PA_GALFIT_FM", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "CHISQ_GALFIT_FM", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "CHI2NU_GALFIT_FM", CPL_TYPE_DOUBLE);

	cpl_table_new_column(tab, "2_F1", CPL_TYPE_DOUBLE);
	cpl_table_new_column(tab, "2_F1PA", CPL_TYPE_DOUBLE);

	for(i = 0; i < nrow; i++) {

	    error = cpl_errorstate_get();

	    if(error != CPL_ERROR_NONE) {
	    	cpl_msg_error(cpl_func, "Errorstate was not CPL_ERROR_NONE "
	    			"in write_fourier_results()!"
	    			"Is cleaned now!");
	    	cpl_errorstate_dump(error, CPL_FALSE, cpl_errorstate_dump_one);
	    	cpl_errorstate_set(CPL_ERROR_NONE);
	    }


		sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", i));
		sprintf(fitfile, "%s%s%s%ld%s", directory, "/", object, i + 1,
				"_Fourier.fits");

		sersic_comp = read_sersic_comp(fitfile, &ncomp);

		cpl_table_set_double(tab, "X_GALFIT_FM", i,
				cpl_array_get_double(sersic_comp, 0, NULL));
		cpl_table_set_double(tab, "Y_GALFIT_FM", i,
				cpl_array_get_double(sersic_comp, 1, NULL));
		cpl_table_set_double(tab, "MAG_GALFIT_FM", i,
				cpl_array_get_double(sersic_comp, 2, NULL));
		cpl_table_set_double(tab, "RE_GALFIT_FM", i,
				cpl_array_get_double(sersic_comp, 3, NULL));
		cpl_table_set_double(tab, "SERSIC_GALFIT_FM", i,
				cpl_array_get_double(sersic_comp, 4, NULL));
		cpl_table_set_double(tab, "AR_GALFIT_FM", i,
				cpl_array_get_double(sersic_comp, 5, NULL));
		cpl_table_set_double(tab, "PA_GALFIT_FM", i,
				cpl_array_get_double(sersic_comp, 6, NULL));
		cpl_table_set_double(tab, "CHISQ_GALFIT_FM", i,
				cpl_array_get_double(sersic_comp, 7, NULL));
		cpl_table_set_double(tab, "CHI2NU_GALFIT_FM", i,
				cpl_array_get_double(sersic_comp, 8, NULL));

		results = read_fourier_results(fitfile, &ncomp);

		cpl_table_set_double(tab, "2_F1", i,
				cpl_array_get_double(results, 0, NULL));
		cpl_table_set_double(tab, "2_F1PA", i,
				cpl_array_get_double(results, 1, NULL));

		cpl_array_delete(results);
		cpl_array_delete(sersic_comp);
	}

	cpl_table_save(tab, NULL, NULL, tabfile, CPL_IO_CREATE);

	cpl_table_delete(tab);

	return CPL_ERROR_NONE;
}

/*******************************************************************

Read fit results from a Fourier mode fit into an array.
0: XC
1: YC
2: MAG
3: RE
4: SERSIC
5: AR
6: PA

********************************************************************/

cpl_array *read_sersic_comp(const char *galfitim, const int *ncomp) {

	int i;

	double f_galfit;

	char f[FILENAME_MAX],
		 str[FILENAME_MAX];

	char *ptr;

	cpl_array *results;

	cpl_propertylist *header;

	cpl_errorstate errstate;

	/* check input */
	if(access(galfitim, 00) != 0) {
		cpl_msg_info(cpl_func, "In read_Fourier_results() : GALFIT "
				"imageblock %s not found. GALFIT probably crashed "
				"for that object.", galfitim);

		/* initialize results array */
		results = cpl_array_new(9 * *ncomp, CPL_TYPE_DOUBLE);
		for(i = 0; i < 9 * *ncomp; i++) {
			cpl_array_set_double(results, i, 99999);
		}

		return results;
	}

	/* initialize results array */
	results = cpl_array_new(9 * *ncomp, CPL_TYPE_DOUBLE);
	for(i = 0; i < 9 * *ncomp; i++) {
		cpl_array_set_double(results, i, 0);
	}

	/* load header */
	cpl_errorstate_set(CPL_ERROR_NONE);

	header = cpl_propertylist_load(galfitim, 2);

	errstate = cpl_errorstate_get();

	if(errstate != CPL_ERROR_NONE) {
		cpl_msg_error(cpl_func, "In read_fourier_results() : Unspecified "
				"problem with loading fitsheader for %s.", galfitim);
		cpl_propertylist_delete(header);
		for(i = 0; i < 10 * *ncomp; i++) {
			cpl_array_set_int(results, i, 99999);
		}
		return results;
	}

	for(i = 1; i <= *ncomp; i++) {

		/* XC */
		sprintf(f, "%d%s", i + 1, "_XC");

		if(cpl_propertylist_has(header, f) == 1) {
			sprintf(str, "%s", cpl_propertylist_get_string(header, f));
		} else {
			cpl_msg_error(cpl_func, "Property not available in "
					"create_GALFIT_setup()!!");
			sprintf(str, "%s", "99999");
		}
		remove_chr(str);

		ptr = strtok(str, " ");
		f_galfit = atof(ptr);
		ptr = strtok(NULL, " ");

		cpl_array_set_double(results, (i - 1) * 9, f_galfit);


		/* YC */
		sprintf(f, "%d%s", i + 1, "_YC");

		if(cpl_propertylist_has(header, f) == 1) {
			sprintf(str, "%s", cpl_propertylist_get_string(header, f));
		} else {
			cpl_msg_error(cpl_func, "Property not available in "
					"create_GALFIT_setup()!!");
			sprintf(str, "%s", "99999");
		}
		remove_chr(str);

		ptr = strtok(str, " ");
		f_galfit = atof(ptr);
		ptr = strtok(NULL, " ");

		cpl_array_set_double(results, (i - 1) * 9 + 1, f_galfit);

		/* MAG */
		sprintf(f, "%d%s", i + 1, "_MAG");

		if(cpl_propertylist_has(header, f) == 1) {
			sprintf(str, "%s", cpl_propertylist_get_string(header, f));
		} else {
			cpl_msg_error(cpl_func, "Property not available in "
					"create_GALFIT_setup()!!");
			sprintf(str, "%s", "99999");
		}
		remove_chr(str);

		ptr = strtok(str, " ");
		f_galfit = atof(ptr);
		ptr = strtok(NULL, " ");

		cpl_array_set_double(results, (i - 1) * 9 + 2, f_galfit);

		/* RE */
		sprintf(f, "%d%s", i + 1, "_RE");

		if(cpl_propertylist_has(header, f) == 1) {
			sprintf(str, "%s", cpl_propertylist_get_string(header, f));
		} else {
			cpl_msg_error(cpl_func, "Property not available in "
					"create_GALFIT_setup()!!");
			sprintf(str, "%s", "99999");
		}
		remove_chr(str);

		ptr = strtok(str, " ");
		f_galfit = atof(ptr);
		ptr = strtok(NULL, " ");

		cpl_array_set_double(results, (i - 1) * 9 + 3, f_galfit);

		/* SERSIC */
		sprintf(f, "%d%s", i + 1, "_N");

		if(cpl_propertylist_has(header, f) == 1) {
			sprintf(str, "%s", cpl_propertylist_get_string(header, f));
		} else {
			cpl_msg_error(cpl_func, "Property not available in "
					"create_GALFIT_setup()!!");
			sprintf(str, "%s", "99999");
		}
		remove_chr(str);

		ptr = strtok(str, " ");
		f_galfit = atof(ptr);
		ptr = strtok(NULL, " ");

		cpl_array_set_double(results, (i - 1) * 9 + 4, f_galfit);

		/* AR */
		sprintf(f, "%d%s", i + 1, "_AR");

		if(cpl_propertylist_has(header, f) == 1) {
			sprintf(str, "%s", cpl_propertylist_get_string(header, f));
		} else {
			cpl_msg_error(cpl_func, "Property not available in "
					"create_GALFIT_setup()!!");
			sprintf(str, "%s", "99999");
		}
		remove_chr(str);

		ptr = strtok(str, " ");
		f_galfit = atof(ptr);
		ptr = strtok(NULL, " ");

		cpl_array_set_double(results, (i - 1) * 9 + 5, f_galfit);

		/* PA */
		sprintf(f, "%d%s", i + 1, "_PA");

		if(cpl_propertylist_has(header, f) == 1) {
			sprintf(str, "%s", cpl_propertylist_get_string(header, f));
		} else {
			cpl_msg_error(cpl_func, "Property not available in "
					"create_GALFIT_setup()!!");
			sprintf(str, "%s", "99999");
		}
		remove_chr(str);

		ptr = strtok(str, " ");
		f_galfit = atof(ptr);
		ptr = strtok(NULL, " ");

		cpl_array_set_double(results, (i - 1) * 9 + 6, f_galfit);

		/* CHISQ */
		sprintf(f, "%s", "CHISQ");

		if(cpl_propertylist_has(header, f) == 1) {

			f_galfit = cpl_propertylist_get_double(header, f);

		} else {
			cpl_msg_error(cpl_func, "Property not available in "
					"create_GALFIT_setup()!!");
			f_galfit = 99999;
		}

		cpl_array_set_double(results, (i - 1) * 9 + 7, f_galfit);

		/* CHISQ_NU */
		sprintf(f, "%s", "CHI2NU");

		if(cpl_propertylist_has(header, f) == 1) {

			f_galfit = cpl_propertylist_get_double(header, f);

		} else {
			cpl_msg_error(cpl_func, "Property not available in "
					"create_GALFIT_setup()!!");
			f_galfit = 99999;
		}

		cpl_array_set_double(results, (i - 1) * 9 + 8, f_galfit);

	}

	cpl_propertylist_delete(header);

	return results;
}

/*******************************************************************

Read fit results from a Fourier mode fit into an array.
0: F1
1: F1PA
2: F3
3: F3PA
4: F4
5: F4PA
6: F5
7: F5PA

********************************************************************/

cpl_array *read_fourier_results(const char *galfitim, const int *ncomp) {

	int i;

	double f_galfit;

	char f[FILENAME_MAX],
		 str[FILENAME_MAX];

	char *ptr;

	cpl_array *results;

	cpl_propertylist *header;

	cpl_errorstate errstate;

	/* check input */
	if(access(galfitim, 00) != 0) {
		cpl_msg_info(cpl_func, "In read_Fourier_results() : GALFIT "
				"imageblock %s not found. GALFIT probably crashed "
				"for that object.", galfitim);

		/* initialize results array */
		results = cpl_array_new(10 * *ncomp, CPL_TYPE_DOUBLE);
		for(i = 0; i < 2 * *ncomp; i++) {
			cpl_array_set_double(results, i, 99999);
		}

		return results;
	}

	/* initialize results array */
	results = cpl_array_new(2 * *ncomp, CPL_TYPE_DOUBLE);
	for(i = 0; i < 2 * *ncomp; i++) {
		cpl_array_set_double(results, i, 0);
	}

	/* load header */
	cpl_errorstate_set(CPL_ERROR_NONE);

	header = cpl_propertylist_load(galfitim, 2);

	errstate = cpl_errorstate_get();

	if(errstate != CPL_ERROR_NONE) {
		cpl_msg_error(cpl_func, "In read_fourier_results() : Unspecified "
				"problem with loading fitsheader for %s.", galfitim);
		cpl_propertylist_delete(header);
		for(i = 0; i < 2 * *ncomp; i++) {
			cpl_array_set_int(results, i, 99999);
		}
		return results;
	}

	for(i = 1; i <= *ncomp; i++) {

		/* Fourier mode 1 amplitude */
		sprintf(f, "%d%s", i + 1, "_F1");

		if(cpl_propertylist_has(header, f) == 1) {
			sprintf(str, "%s", cpl_propertylist_get_string(header, f));
		} else {
			cpl_msg_error(cpl_func, "Property not available in "
					"create_GALFIT_setup()!!");
			sprintf(str, "%s", "99999");
		}
		remove_chr(str);

		ptr = strtok(str, " ");
		f_galfit = atof(ptr);
		ptr = strtok(NULL, " ");

		cpl_array_set_double(results, (i - 1) * 2, f_galfit);

		/* Fourier mode 1 angle */
		sprintf(f, "%d%s", i + 1, "_F1PA");

		if(cpl_propertylist_has(header, f) == 1) {
			sprintf(str, "%s", cpl_propertylist_get_string(header, f));
		} else {
			cpl_msg_error(cpl_func, "Property not available in "
					"create_GALFIT_setup()!!");
			sprintf(str, "%s", "99999");
		}
		remove_chr(str);

		ptr = strtok(str, " ");
		f_galfit = atof(ptr);
		ptr = strtok(NULL, " ");

		cpl_array_set_double(results, (i - 1) * 2 + 1, f_galfit);
	}

	cpl_propertylist_delete(header);

	return results;
}


/********************************************************************

Attach secondaries to the setup file.

 *******************************************************************/

cpl_error_code attach_secondaries(cpl_table *tab,
		cpl_parameterlist *gala_setup,
		const char *setupfile, const int *idx) {

	int j,
		lv,
		nstar = 0,
		secnum = 0,
		debug = 0;

	long k;

	double xc,
	       yc,
	       xlo,
	       ylo,
	       xfit,
	       yfit,
	       xsec,
	       ysec,
	       mag,
	       fr,
	       fluxextend,
	       eli,
	       theta;

	char directory[FILENAME_MAX],
	 	 fitfile[FILENAME_MAX],
	 	 object[FILENAME_MAX];

	cpl_array *secindices,
			  *sersic_res;
	const cpl_array *help;

	cpl_parameter *p;
	cpl_propertylist *header;
	cpl_errorstate errstate;

	FILE *fp;


	/* read GALFIT imageblock filename from parameterlist */
    p = cpl_parameterlist_find(gala_setup, "object");
    sprintf(object, "%s", cpl_parameter_get_string(p));

	/* read GALFIT fluxextend parameter from parameterlist */
    p = cpl_parameterlist_find(gala_setup, "fluxextend");
    fluxextend = cpl_parameter_get_double(p);

    /* prepare object coordinates on stamp*/
	xc   =  cpl_table_get_double(tab, "X_IMAGE", *idx, NULL);
	yc   =  cpl_table_get_double(tab, "Y_IMAGE", *idx, NULL);
	xlo  =  cpl_table_get_int(tab, "STAMP_XLO", *idx, NULL);
	ylo  =  cpl_table_get_int(tab, "STAMP_YLO", *idx, NULL);
	xfit = xc - xlo;
	yfit = yc - ylo;

    /* read secondary indices array from table */
	help = cpl_table_get_array(tab, "SECONDARY_INDICES", *idx);
	secindices = cpl_array_duplicate(help);

	/* determine number of secondaries */
	for(j = 0; j < cpl_array_get_size(secindices); j++) {
		if(cpl_array_get(secindices, j, NULL) > 0) {
			secnum++;
		}
	}

	/* if no secondaries are present - no more work to do */
	if(secnum == 0) {

		/* clean up */
		cpl_array_delete(secindices);

		return CPL_ERROR_NONE;
	}

	/*specify current tile directory */
	sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", *idx));

	/* open setup file filepointer */
	fp = fopen(setupfile, "a");

	/* attach every secondary source */
	for(lv = 0; lv < secnum; lv++) {

		/* find secondary table index */
		k = (long)cpl_array_get(secindices, lv, NULL);

		/* check if valid number */
		if(k <= 0) {
			cpl_msg_error(cpl_func, "An internal error occurred in "
				"attach_secondaries(). Secondary has negative "
				"table index! Number of secondaries object %d : "
				"%d. Lv : %d  Secondary Index : %ld\n", *idx, secnum, lv, k);
			break;
		}

		/* prepare filename for secondary fitfile */
		sprintf(fitfile, "%s%s%s%ld%s", directory, "/", object, k, ".fits");

		/* check if fit exists */
		if(access(fitfile, 00) == 0) {

			/* reset error state to check if fits header is loaded properly */
			cpl_errorstate_set(CPL_ERROR_NONE);

			/*load header */
			header = cpl_propertylist_load(fitfile, 2);

			/*check error state */
			errstate = cpl_errorstate_get();

			/* read results from fit if no error occurred */
			if(errstate == CPL_ERROR_NONE) {

				/* Prepare array containing 1 component fit results */
				sersic_res = cpl_array_new(7, CPL_TYPE_DOUBLE);

				/* read Sersic fit information */
				read_sersic_results(fitfile, sersic_res, nstar);

				if(debug == 1) {
					printf("SECONDARY POSITION IN PRIMARY STAMP FOR FOURIER MODE "
						"FITTING OF: %s\n"
						"SECONDARYFILE: %s\n"
						"A: %f\nB: %f\nxsec_old: %f\n",
						setupfile, fitfile,
						(double)cpl_table_get_int(tab, "STAMP_XLO", k - 1, NULL),
						(double)cpl_table_get_int(tab, "STAMP_XLO", *idx, NULL),
						cpl_array_get_double(sersic_res, 0, NULL));
				}

				/* attach setup file */
				fprintf(fp, "\n# Sersic function secondary %d\n", lv + 1);
				fprintf(fp, "0) sersic\n");

				/* transform into local stamp coordinates */
				xsec  = (double)cpl_table_get_int(tab, "STAMP_XLO", k - 1, NULL)
						+cpl_array_get_double(sersic_res, 0, NULL)-
						(double)cpl_table_get_int(tab, "STAMP_XLO", *idx, NULL);

				ysec  = (double)cpl_table_get_int(tab, "STAMP_YLO", k - 1, NULL)
						+cpl_array_get_double(sersic_res, 1, NULL)-
						(double)cpl_table_get_int(tab, "STAMP_YLO", *idx, NULL);

				fprintf(fp, "1) %.2f %.2f 1 1\n", xsec, ysec);

				fprintf(fp, "3) %.2f 1\n",
					cpl_array_get_double(sersic_res, 2, NULL));
				fprintf(fp, "4) %.2f 1\n",
					cpl_array_get_double(sersic_res, 3, NULL));
				fprintf(fp, "5) %.2f 1\n",
					cpl_array_get_double(sersic_res, 4, NULL));
				fprintf(fp, "9) %.4f 1\n",
					cpl_array_get_double(sersic_res, 5, NULL));
				fprintf(fp, "10) %.2f 1\n",
					cpl_array_get_double(sersic_res, 6, NULL));
				fprintf(fp, "Z) 0\n\n");

//				fprintf(fp, "#  Azimuthal fourier modes\n");
//				fprintf(fp, "F1)  0.01  0.01  1  1\n");
//				fprintf(fp, "F3)  0.01  0.01  1  1\n");
//				fprintf(fp, "F4)  0.01  0.01  1  1\n");
//				fprintf(fp, "F5)  0.01  0.01  1  1\n");
//				fprintf(fp, "F6)  0.01  0.01  1  1\n");

				cpl_array_delete(sersic_res);

			/* if error occurred use SExtractor information for secondary */
			} else {

				/* attach setup file */
				fprintf(fp, "\n# Sersic function\n");
				fprintf(fp, "0) sersic\n");

				/* transform into local stamp coordinates */
				xsec  = xfit +
						cpl_table_get_double(tab, "X_IMAGE", k - 1, NULL) - xc;
				ysec  = yfit +
						cpl_table_get_double(tab, "Y_IMAGE", k - 1, NULL) - yc;
				if(isnan(xsec) == 0 && isnan(ysec) == 0) {
					fprintf(fp, "1) %.2f %.2f 1 1\n", xsec, ysec);
				} else {
					cpl_msg_error(cpl_func, "Error for secondary "
							"position in attach_secondaries()!");
					fprintf(fp, "1) %.2f %.2f 1 1\n", 99999.999, 99999.999);
				}

				mag = cpl_table_get_double(tab, "MAG_BEST", k - 1, NULL);
				fprintf(fp, "3) %.2f 1\n", mag);

				fr = cpl_table_get_double(tab, "FLUX_RADIUS", k - 1, NULL);
				if(isnan(fr) == 0) {
					if(fr > 0) {
						fprintf(fp, "4) %.2f 1\n", pow(fr, fluxextend));
					} else {
						fr = fabs(fr);
						fprintf(fp, "4) %.2f 1\n", pow(fr, fluxextend));
					}
				} else {
					fprintf(fp, "4) %.2f 1\n", 99999.999);
				}

				fprintf(fp, "5) %.2f 1\n", 2.5);

				eli = cpl_table_get_double(tab, "ELLIPTICITY", k - 1, NULL);
				fprintf(fp, "9) %.4f 1\n", 1 - eli);

				theta = cpl_table_get_double(tab, "THETA_IMAGE", k - 1, NULL);

				if(theta >= 0) {
					theta = theta - 90;
				} else {
					theta = 90 + theta;
				}
				fprintf(fp, "10) %.2f 1\n", theta);

				fprintf(fp, "Z) 0\n\n");

//				fprintf(fp, "#  Azimuthal fourier modes\n");
//				fprintf(fp, "F1)  0.01  0.01  1  1\n");
//				fprintf(fp, "F3)  0.01  0.01  1  1\n");
//				fprintf(fp, "F4)  0.01  0.01  1  1\n");
//				fprintf(fp, "F5)  0.01  0.01  1  1\n");
//				fprintf(fp, "F6)  0.01  0.01  1  1\n");
			}

			/* clean up */
			cpl_propertylist_delete(header);

		/* if fit is not accessable use SExtractor information for secondary */
		} else {

			/* attach setup file */
			fprintf(fp, "# Sersic function\n");
			fprintf(fp, "0) sersic\n");

			/* transform into local stamp coordinates */
			xsec  = xfit +
					cpl_table_get_double(tab, "X_IMAGE", k - 1, NULL) - xc;
			ysec  = yfit +
					cpl_table_get_double(tab, "Y_IMAGE", k - 1, NULL) - yc;
			if(isnan(xsec) == 0 && isnan(ysec) == 0) {
				fprintf(fp, "1) %.2f %.2f 1 1\n", xsec, ysec);
			} else {
				cpl_msg_error(cpl_func, "Error for secondary "
						"position in attach_secondaries()!");
				fprintf(fp, "1) %.2f %.2f 1 1\n", 99999.999, 99999.999);
			}

			mag = cpl_table_get_double(tab, "MAG_BEST", k - 1, NULL);
			fprintf(fp, "3) %.2f 1\n", mag);

			fr = cpl_table_get_double(tab, "FLUX_RADIUS", k - 1, NULL);

			if(isnan(fr) == 0) {
				if(fr > 0) {
					fprintf(fp, "4) %.2f 1\n", pow(fr, fluxextend));
				} else {
					fr = fabs(fr);
					fprintf(fp, "4) %.2f 1\n", pow(fr, fluxextend));
				}
			} else {
				fprintf(fp, "4) %.2f 1\n", 99999.999);
			}

			fprintf(fp, "5) %.2f 1\n", 2.5);

			eli = cpl_table_get_double(tab, "ELLIPTICITY", k - 1, NULL);
			fprintf(fp, "9) %.4f 1\n", 1 - eli);

			theta = cpl_table_get_double(tab, "THETA_IMAGE", k - 1, NULL);

			if(theta >= 0) {
				theta = theta - 90;
			} else {
				theta = 90 + theta;
			}
			fprintf(fp, "10) %.2f 1\n", theta);

			fprintf(fp, "Z) 0\n\n");

//			fprintf(fp, "#  Azimuthal fourier modes\n");
//			fprintf(fp, "F1)  0.01  0.01  1  1\n");
//			fprintf(fp, "F3)  0.01  0.01  1  1\n");
//			fprintf(fp, "F4)  0.01  0.01  1  1\n");
//			fprintf(fp, "F5)  0.01  0.01  1  1\n");
//			fprintf(fp, "F6)  0.01  0.01  1  1\n");
		}
	}

	/* clean up */
	cpl_array_delete(secindices);
	fclose(fp);

	return CPL_ERROR_NONE;
}



/********************************************************************

Attach contrib targets to the setup file. Check if they are valid.

 *******************************************************************/

cpl_error_code attach_contribtargets(cpl_table *tab,
		cpl_parameterlist *gala_setup,
		const char *setupfile, const long *idx,
		const double *exptime) {

	int j,
		nstar = 0,
		lv,
		ctnum = 0;

	long k;

	double xc,
	       yc,
	       xlo,
	       ylo,
	       xfit,
	       yfit,
	       xsec,
	       ysec,
	       mag,
	       fr,
	       fluxextend,
	       eli,
	       theta,
	       magzero,
	       magcrit,
	       magexclude;

	char directory[FILENAME_MAX],
	 	 fitfile[FILENAME_MAX],
	 	 object[FILENAME_MAX];

	cpl_array *ctindices,
			  *sersic_res;
	const cpl_array *help;

	cpl_parameter *p;
	cpl_propertylist *header;
	cpl_errorstate errstate;

	FILE *fp;


	/* read GALFIT imageblock filename from parameterlist */
    p = cpl_parameterlist_find(gala_setup, "object");
    sprintf(object, "%s", cpl_parameter_get_string(p));

	/* read GALFIT fluxextend parameter from parameterlist */
    p = cpl_parameterlist_find(gala_setup, "fluxextend");
    fluxextend = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magexclude");
    fluxextend = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magzero");
    fluxextend = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(gala_setup, "magcrit");
    fluxextend = cpl_parameter_get_double(p);

    /* prepare object coordinates on stamp*/
	xc   =  cpl_table_get_double(tab, "X_IMAGE", *idx, NULL);
	yc   =  cpl_table_get_double(tab, "Y_IMAGE", *idx, NULL);
	xlo  =  cpl_table_get_int(tab, "STAMP_XLO", *idx, NULL);
	ylo  =  cpl_table_get_int(tab, "STAMP_YLO", *idx, NULL);
	xfit = xc - xlo;
	yfit = yc - ylo;

    /* read secondary indices array from table */
	help = cpl_table_get_array(tab, "POT_CT_INDICES", *idx);
	ctindices = cpl_array_duplicate(help);

	/* determine number of secondaries */
	for(j = 0; j < cpl_array_get_size(ctindices); j++) {
		if(cpl_array_get(ctindices, j, NULL) > 0) {
			ctnum++;
		}
	}

	/* if no secondaries are present - no more work to do */
	if(ctnum == 0) {

		/* clean up */
		cpl_array_delete(ctindices);

		return CPL_ERROR_NONE;
	}

	/*specify current tile directory */
	sprintf(directory, "%s", cpl_table_get_string(tab, "TILE_DIRECTORY", *idx));

	/* open setup file filepointer */
	fp = fopen(setupfile, "a");

	/* attach every secondary source */
	for(lv = 0; lv < ctnum; lv++) {

		/* find secondary table index */
		k = (long)cpl_array_get(ctindices, lv, NULL) - 1;

		/* check if valid number */
		if(k <= 0) {
			cpl_msg_error(cpl_func, "An internal error occurred in "
				"attach_contribtargets(). CT has negative "
				"table index! Number of ct object %ld : "
				"%d. Lv : %d  Secondary Index : %ld\n", *idx, ctnum, lv, k);
			break;
		}

		/* prepare filename for secondary fitfile */
		sprintf(fitfile, "%s%s%s%ld%s", directory, "/", object, k + 1, ".fits");

		/* check if fit exists */
		if(access(fitfile, 00) == 0) {

			/* reset error state to check if fits header is loaded properly */
			cpl_errorstate_set(CPL_ERROR_NONE);

			/*load header */
			header = cpl_propertylist_load(fitfile, 2);

			/*check error state */
			errstate = cpl_errorstate_get();

			/* read results from fit if no error occurred */
			if(errstate == CPL_ERROR_NONE) {

				if(check_contribtarget(tab, object, &*idx, &k, &magzero, &*exptime,
					&magexclude, &magcrit, &fluxextend) == 0) {

					/* Prepare array containing 1 component fit results */
					sersic_res = cpl_array_new(7, CPL_TYPE_DOUBLE);

					/* read Sersic fit information */
					read_sersic_results(fitfile, sersic_res, nstar);

					/* attach setup file */
					fprintf(fp, "# Sersic function secondary %d\n", lv + 1);
					fprintf(fp, "0) sersic\n");

					/* transform into local stamp coordinates */
					xsec  = cpl_table_get_double(tab, "STAMP_XLO", k, NULL) -
							cpl_table_get_double(tab, "STAMP_XLO", *idx, NULL) +
							cpl_array_get_double(sersic_res, 0, NULL);

					ysec  = cpl_table_get_double(tab, "STAMP_YLO", k, NULL) -
							cpl_table_get_double(tab, "STAMP_YLO", *idx, NULL) +
							cpl_array_get_double(sersic_res, 1, NULL);

					fprintf(fp, "1) %.2f %.2f 0 0\n", xsec, ysec);

					fprintf(fp, "3) %.2f 0\n",
							cpl_array_get_double(sersic_res, 2, NULL));
					fprintf(fp, "4) %.2f 0\n",
							cpl_array_get_double(sersic_res, 3, NULL));
					fprintf(fp, "5) %.2f 0\n",
							cpl_array_get_double(sersic_res, 4, NULL));
					fprintf(fp, "9) %.4f 0\n",
							cpl_array_get_double(sersic_res, 5, NULL));
					fprintf(fp, "10) %.2f 0\n",
							cpl_array_get_double(sersic_res, 6, NULL));
					fprintf(fp, "Z) 0\n\n");

					cpl_array_delete(sersic_res);
				}

			/* if error occurred use SExtractor information for secondary */
			} else {

				if(check_contribtarget_sexdata(tab, &*idx, &k, &magzero, &*exptime,
						&magexclude, &magcrit, &fluxextend) == 0) {

					/* attach setup file */
					fprintf(fp, "# Sersic function\n");
					fprintf(fp, "0) sersic\n");

					/* transform into local stamp coordinates */
					xsec  = xfit +
						cpl_table_get_double(tab, "X_IMAGE", k, NULL) - xc;
					ysec  = yfit +
						cpl_table_get_double(tab, "Y_IMAGE", k, NULL) - yc;
					fprintf(fp, "1) %.2f %.2f 1 1\n", xsec, ysec);

					mag = cpl_table_get_double(tab, "MAG_BEST", k, NULL);
					fprintf(fp, "3) %.2f 1\n", mag);

					fr = cpl_table_get_double(tab, "FLUX_RADIUS", k, NULL);

					fprintf(fp, "4) %.2f 1\n", pow(fr, fluxextend));

					fprintf(fp, "5) %.2f 1\n", 2.5);

					eli = cpl_table_get_double(tab, "ELLIPTICITY", k, NULL);
					fprintf(fp, "9) %.4f 1\n", 1 - eli);

					theta = cpl_table_get_double(tab, "THETA_IMAGE", k, NULL);

					if(theta >= 0) {
						theta = theta - 90;
					} else {
						theta = 90 + theta;
					}
					fprintf(fp, "10) %.2f 1\n", theta);

					fprintf(fp, "Z) 0\n\n");
				}
			}

			/* clean up */
			cpl_propertylist_delete(header);

		/* if fit is not accessable use SExtractor information for secondary */
		} else {

			if(check_contribtarget_sexdata(tab, &*idx, &k, &magzero, &*exptime,
					&magexclude, &magcrit, &fluxextend) == 0) {

				/* attach setup file */
				fprintf(fp, "# Sersic function\n");
				fprintf(fp, "0) sersic\n");

				/* transform into local stamp coordinates */
				xsec  = xfit +
					cpl_table_get_double(tab, "X_IMAGE", k, NULL) - xc;
				ysec  = yfit +
					cpl_table_get_double(tab, "Y_IMAGE", k, NULL) - yc;
				fprintf(fp, "1) %.2f %.2f 1 1\n", xsec, ysec);

				mag = cpl_table_get_double(tab, "MAG_BEST", k, NULL);
				fprintf(fp, "3) %.2f 1\n", mag);

				fr = cpl_table_get_double(tab, "FLUX_RADIUS", k, NULL);

				fprintf(fp, "4) %.2f 1\n", pow(fr, fluxextend));

				fprintf(fp, "5) %.2f 1\n", 2.5);

				eli = cpl_table_get_double(tab, "ELLIPTICITY", k, NULL);
				fprintf(fp, "9) %.4f 1\n", 1 - eli);

				theta = cpl_table_get_double(tab, "THETA_IMAGE", k, NULL);

				if(theta >= 0) {
					theta = theta - 90;
				} else {
					theta = 90 + theta;
				}
				fprintf(fp, "10) %.2f 1\n", theta);

				fprintf(fp, "Z) 0\n\n");
			}
		}
	}

	/* clean up */
	cpl_array_delete(ctindices);
	fclose(fp);

	return CPL_ERROR_NONE;
}


/********************************************************************

Read exposure time from header.

 *******************************************************************/

double read_exptime(const char *galfitim) {

	double exptime = 0;

	cpl_propertylist *header;

	header = cpl_propertylist_load(galfitim, 0);
	if (header == NULL) {
		// image header not found
		cpl_msg_error(cpl_func, "Header not found in "
			"find_contribtargets()!");
	} else {

		if(cpl_propertylist_has(header, "EXPTIME") != 1) {
			cpl_msg_error(cpl_func, "Header %s (0) contains no EXPTIME "
				"in read_exptime()! Checking further extensions.",
				galfitim);
		} else {
			exptime = cpl_propertylist_get_double(header, "EXPTIME");
		}
	}

	cpl_propertylist_delete(header);

	if(exptime <= 0) {
		cpl_msg_error(cpl_func, "Exposure time is 0 or negative "
								"in find_contribtargets()!!! Image header "
								"probably not found!!!");

		header = cpl_propertylist_load(galfitim, 1);
		if (header == NULL) {
			// image header not found
			cpl_msg_error(cpl_func, "Header not found in "
				"find_contribtargets()!");
		} else {

			if(cpl_propertylist_has(header, "EXPTIME") != 1) {
				cpl_msg_error(cpl_func, "Header %s (1) contains no EXPTIME "
					"in read_exptime()! Checking further extensions.",
					galfitim);
			} else {
				exptime = cpl_propertylist_get_double(header, "EXPTIME");
			}
		}

		cpl_propertylist_delete(header);
	}

	if(exptime <= 0) {
		cpl_msg_error(cpl_func, "Exposure time is 0 or negative "
								"in find_contribtargets()!!! Image header "
								"probably not found!!!");

		header = cpl_propertylist_load(galfitim, 2);
		if (header == NULL) {
			// image header not found
			cpl_msg_error(cpl_func, "Header not found in "
				"find_contribtargets()!");
		} else {

			if(cpl_propertylist_has(header, "EXPTIME") != 1) {
				cpl_msg_error(cpl_func, "Header %s (2) contains no EXPTIME "
					"in read_exptime()! No EXPTIME present!", galfitim);
			} else {
				exptime = cpl_propertylist_get_double(header, "EXPTIME");
			}
		}

		cpl_propertylist_delete(header);
	}

	return exptime;
}


/*******************************************************************

Read Sersic results from 1 component fit.

********************************************************************/

cpl_error_code read_sersic_results(const char *filename,
		cpl_array *sersic_res, int nstar) {

	int count,
		star = 0;

	double xcgalfit = 0, ycgalfit = 0, maggalfit = 0,
			   regalfit = 0, ngalfit = 0, argalfit = 0, pagalfit = 0;

	char xp[FILENAME_MAX];
	char yp[FILENAME_MAX];
	char mg[FILENAME_MAX];
	char re[FILENAME_MAX];
	char n[FILENAME_MAX];
	char ar[FILENAME_MAX];
	char pa[FILENAME_MAX];
	char *ptr;

	cpl_propertylist *fitsheader;


	if(access(filename, 00) != 0) {
		cpl_msg_error(cpl_func, "In read_sersic_results() : "
				"Imagefile %s was not accessable! Aborting...",
				filename);
		return CPL_ERROR_DATA_NOT_FOUND;
	}

	if(nstar != 0) {
		cpl_msg_error(cpl_func, "In read_sersic_results(): Star counting "
				"variable was not set to 0. Resetting to 0.");
		nstar = 0;
	}

	/* Read data from fit */

	fitsheader = cpl_propertylist_load(filename, 2);

	/* Read x coordinate */

	count = 0;

	if(cpl_propertylist_has(fitsheader, "2_XC") == 1) {
		sprintf(xp, "%s", cpl_propertylist_get_string(fitsheader, "2_XC"));
	} else {
		cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
		sprintf(xp, "%s", "99999");
	}
	remove_chr(xp);

	if(star == 1) {
		nstar++;
	}

	ptr = strtok(xp, " ");
	while(ptr != NULL) {
		if(count == 0) {
			xcgalfit = atof(ptr);
		}
		ptr = strtok(NULL, " ");
		count ++;
	}

	if((isnan(xcgalfit) == 0) && (xcgalfit >= 0)) {
		cpl_array_set_double(sersic_res, 0, xcgalfit);
	} else {
		cpl_msg_error(cpl_func, "In read_sersic_results() : "
				"XC is not a number! For object %s!",
				filename);
		cpl_array_set_double(sersic_res, 0, 99999.999);
	}


	/* Read y coordinate */

	count = 0;

	if(cpl_propertylist_has(fitsheader, "2_YC") == 1) {
		sprintf(yp, "%s", cpl_propertylist_get_string(fitsheader, "2_YC"));
	} else {
		cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
		sprintf(yp, "%s", "99999");
	}
	remove_chr(yp);

	if(star == 1) {
		nstar++;
	}

	ptr = strtok(yp, " ");
	while(ptr != NULL) {
		if(count == 0) {
			ycgalfit = atof(ptr);
		}
		ptr = strtok(NULL, " ");
		count ++;
	}

	if((isnan(ycgalfit) == 0) && (ycgalfit >= 0)) {
		cpl_array_set_double(sersic_res, 1, ycgalfit);
	} else {
		cpl_msg_error(cpl_func, "In read_sersic_results() : "
				"YC is not a number! For object %s!",
				filename);
		cpl_array_set_double(sersic_res, 1, 99999.999);
	}


	/* Read magnitude */

	count = 0;

	if(cpl_propertylist_has(fitsheader, "2_MAG") == 1) {
		sprintf(mg, "%s", cpl_propertylist_get_string(fitsheader, "2_MAG"));
	} else {
		cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
		sprintf(mg, "%s", "99999");
	}
	remove_chr(mg);

	if(star == 1) {
		nstar++;
	}

	ptr = strtok(mg, " ");
	while(ptr != NULL) {
		if(count == 0) {
			maggalfit = atof(ptr);
		}
		ptr = strtok(NULL, " ");
		count ++;
	}

	if((isnan(maggalfit) == 0) && (maggalfit >= 0)) {
		cpl_array_set_double(sersic_res, 2, maggalfit);
	} else {
		cpl_msg_error(cpl_func, "In read_sersic_results() : "
				"MAG is not a number! For object %s!",
				filename);
		cpl_array_set_double(sersic_res, 2, 99999.999);
	}


	/* Read re */

	count = 0;

	if(cpl_propertylist_has(fitsheader, "2_RE") == 1) {
		sprintf(re, "%s", cpl_propertylist_get_string(fitsheader, "2_RE"));
	} else {
		cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
		sprintf(re, "%s", "99999");
	}
	remove_chr(re);

	if(star == 1) {
		nstar++;
	}

	ptr = strtok(re, " ");
	while(ptr != NULL) {
		if(count == 0) {
			regalfit = atof(ptr);
		}
		ptr = strtok(NULL, " ");
		count ++;
	}

	if((isnan(regalfit) == 0) && (regalfit >= 0)) {
		cpl_array_set_double(sersic_res, 3, regalfit);
	} else {
		cpl_msg_error(cpl_func, "In read_sersic_results() : "
				"RE is not a number! For object %s!",
				filename);
		cpl_array_set_double(sersic_res, 3, 99999.999);
	}


	/* Read n */

	count = 0;

	if(cpl_propertylist_has(fitsheader, "2_N") == 1) {
		sprintf(n, "%s", cpl_propertylist_get_string(fitsheader, "2_N"));
	} else {
		cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
		sprintf(n, "%s", "99999");
	}

	remove_chr(n);

	if(star == 1) {
		nstar++;
	}

	ptr = strtok(n, " ");
	while(ptr != NULL) {
		if(count == 0) {
			ngalfit = atof(ptr);
		}
		ptr = strtok(NULL, " ");
		count ++;
	}

	if((isnan(ngalfit) == 0) && (ngalfit >= 0)) {
		cpl_array_set_double(sersic_res, 4, ngalfit);
	} else {
		cpl_msg_error(cpl_func, "In read_sersic_results() : "
				"N is not a number! For object %s!",
				filename);
		cpl_array_set_double(sersic_res, 4, 99999.999);
	}


	/* Read ar */

	count = 0;

	if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
		sprintf(ar, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
	} else {
		cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
		sprintf(ar, "%s", "99999");
	}
	remove_chr(ar);

	if(star == 1) {
		nstar++;
	}

	ptr = strtok(ar, " ");
	while(ptr != NULL) {
		if(count == 0) {
			argalfit = atof(ptr);
		}
		ptr = strtok(NULL, " ");
		count ++;
	}

	if((isnan(argalfit) == 0) && (argalfit >= 0)) {
		cpl_array_set_double(sersic_res, 5, argalfit);
	} else {
		cpl_msg_error(cpl_func, "In read_sersic_results() : "
				"AR is not a number! For object %s!",
				filename);
		cpl_array_set_double(sersic_res, 5, 99999.999);
	}


	/* Read pa */

	count = 0;

	if(cpl_propertylist_has(fitsheader, "2_PA") == 1) {
		sprintf(pa, "%s", cpl_propertylist_get_string(fitsheader, "2_PA"));
	} else {
		cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
		sprintf(pa, "%s", "99999");
	}
	remove_chr(pa);

	ptr = strtok(pa, " ");
	while(ptr != NULL) {
		if(count == 0) {
			pagalfit = atof(ptr);
		}
		ptr = strtok(NULL, " ");
		count ++;
	}
	count = 0;

	if((isnan(pagalfit)) == 0) {
		cpl_array_set_double(sersic_res, 6, pagalfit);
	} else {
		cpl_msg_error(cpl_func, "In read_sersic_results() : "
				"PA is not a number! For object %s!",
				filename);
		cpl_array_set_double(sersic_res, 6, 99999.999);
	}


	cpl_propertylist_delete(fitsheader);

	return CPL_ERROR_NONE;
}


cpl_array *read_header(cpl_propertylist *fitsheader) {

	int count = 0;

	double xcgalfit = 0, ycgalfit = 0, maggalfit = 0,
		   regalfit = 0, ngalfit = 0, argalfit = 0, pagalfit = 0;

	char xp[FILENAME_MAX];
	char yp[FILENAME_MAX];
	char mg[FILENAME_MAX];
	char re[FILENAME_MAX];
	char n[FILENAME_MAX];
	char ar[FILENAME_MAX];
	char pa[FILENAME_MAX];
	char str[FILENAME_MAX];
	char *ptr;

	cpl_array *fitdata;

	fitdata = cpl_array_new(7, CPL_TYPE_DOUBLE);

	if(cpl_propertylist_has(fitsheader, "2_XC") == 1) {
		sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_XC"));
		sprintf(xp, "%s", cpl_propertylist_get_string(fitsheader, "2_XC"));
	} else {
		cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
		sprintf(xp, "%s", "1");
	}
	remove_chr(xp);
	ptr = strtok(xp, " ");
	while(ptr != NULL) {
		if(count == 0) {
			xcgalfit = atof(ptr);
		}
		ptr = strtok(NULL, " ");
		count ++;
	}
	count = 0;


	if(cpl_propertylist_has(fitsheader, "2_YC") == 1) {
		sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_YC"));
		sprintf(yp, "%s", cpl_propertylist_get_string(fitsheader, "2_YC"));
	} else {
		cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
		sprintf(yp, "%s", "1");
	}
	remove_chr(yp);
	ptr = strtok(yp, " ");
	while(ptr != NULL) {
		if(count == 0) {
			ycgalfit = atof(ptr);
		}
		ptr = strtok(NULL, " ");
		count ++;
	}
	count = 0;


	if(cpl_propertylist_has(fitsheader, "2_MAG") == 1) {
		sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_MAG"));
		sprintf(mg, "%s", cpl_propertylist_get_string(fitsheader, "2_MAG"));
	} else {
		cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
		sprintf(mg, "%s", "20");
	}
	remove_chr(mg);
	ptr = strtok(mg, " ");
	while(ptr != NULL) {
		if(count == 0) {
			maggalfit = atof(ptr);
		}
		ptr = strtok(NULL, " ");
		count ++;
	}
	count = 0;


	if(cpl_propertylist_has(fitsheader, "2_RE") == 1) {
		sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_RE"));
		sprintf(re, "%s", cpl_propertylist_get_string(fitsheader, "2_RE"));
	} else {
		cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
		sprintf(re, "%s", "20");
	}
	remove_chr(re);
	ptr = strtok(re, " ");
	while(ptr != NULL) {
		if(count == 0) {
			regalfit = atof(ptr);
		}
		ptr = strtok(NULL, " ");
		count ++;
	}
	count = 0;


	if(cpl_propertylist_has(fitsheader, "2_N") == 1) {
		sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_N"));
		sprintf(n, "%s", cpl_propertylist_get_string(fitsheader, "2_N"));
	} else {
		cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
		sprintf(n, "%s", "2.5");
	}
	remove_chr(n);
	ptr = strtok(n, " ");
	while(ptr != NULL) {
		if(count == 0) {
			ngalfit = atof(ptr);
		}
		ptr = strtok(NULL, " ");
		count ++;
	}
	count = 0;


	if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
		sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
		sprintf(ar, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
	} else {
		cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
		sprintf(ar, "%s", "0.8");
	}
	remove_chr(ar);
	ptr = strtok(ar, " ");
	while(ptr != NULL) {
		if(count == 0) {
			argalfit = atof(ptr);
		}
		ptr = strtok(NULL, " ");
		count ++;
	}
	count = 0;


	if(cpl_propertylist_has(fitsheader, "2_AR") == 1) {
		sprintf(str, "%s", cpl_propertylist_get_string(fitsheader, "2_AR"));
		sprintf(pa, "%s", cpl_propertylist_get_string(fitsheader, "2_PA"));
	} else {
		cpl_msg_error(cpl_func, "Property not available in create_GALFIT_setup()!!");
		sprintf(pa, "%s", "0");
	}
	remove_chr(pa);
	ptr = strtok(pa, " ");
	while(ptr != NULL) {
		if(count == 0) {
			pagalfit = atof(ptr);
		}
		ptr = strtok(NULL, " ");
		count ++;
	}
	count = 0;

	cpl_array_set_double(fitdata, 0, xcgalfit);
	cpl_array_set_double(fitdata, 1, ycgalfit);
	cpl_array_set_double(fitdata, 2, maggalfit);
	cpl_array_set_double(fitdata, 3, regalfit);
	cpl_array_set_double(fitdata, 4, ngalfit);
	cpl_array_set_double(fitdata, 5, argalfit);
	cpl_array_set_double(fitdata, 6, pagalfit);

	return fitdata;
}



/**@}*/
