/*
 * string_ops.c
 *
 *  Created on: Aug 4, 2011
 *      Author: barden
 */

/*!
 * \ingroup string_ops
 */

/**@{*/

/*!
 * \callgraph
 *
 * \file string_ops.c
 *
 * \author Marco Barden & ESO In-Kind Team Innsbruck
 * \since   02 Feb 2011
 * \date    17 Feb 2011
 */

#include "string_ops.h"

/**@{*/
void strtolower(char *str) {
    int i;

    for(i = 0; str[i]; i++) {
        str[i] = tolower(str[ i ]);
    }
}

void strtoupper(char *str) {
    int i;

    for(i = 0; str[i]; i++) {
        str[i] = toupper(str[ i ]);
    }
}

void initialise_string(char *str, const long n) {
    /*!
     * \brief
     *   Initialise a string variable.
     *
     * This function initialises a given string \em str of length \em n
     * with "\0".
     *
     * \b INPUT:
     * \param n    Length of string.
     *
     * \b OUTPUT:
     * \param str  String.
     *
     * \return     Nothing.
     */

    long i;

    for (i = 0; i < n; i++) {
        str[i] = '\0';
    }
}

void terminate_string(char *str) {
    /*!
     * \brief
     *   Put "\0" at end of string.
     *
     * This function places a "\0" at end of the input string.
     *
     * \note
     *   No checks are performed for writing beyond the boundary of allocated
     *   memory for the input string.
     *
     * \b INPUT & OUTPUT:
     * \param str  string.
     *
     * \b OUTPUT:
     * \return     Nothing.
     */

    char *p;                   /* character pointer */

    p = str + strlen(str);     /* set at nominal '\0' of input string */

    if (*p != '\0') {          /* if not terminated properly */
        *p = '\0';             /* place string termination character */
    }
}

char *strtrim(char *str) {
    /*!
     * \brief
     *   Remove leading and trailing blanks from string.
     *
     * This function removes all leading and trailing " " characters from
     * \em str using \c isspace().
     *
     * \b INPUT:
     * \param str  string.
     *
     * \b OUTPUT:
     * \return     string.
     */

    if (str != NULL && *str != 0) {
        int i = 0,                  /* counter for start position of string */
            j = 0,                  /* counter for end position of string */
            len = strlen(str);      /* length of input string */

        char *p, *q,       /* pointers for looping through the input string */
            *out = (char *)malloc(len + 1);           /* new output string */

        /* set pointers to beginning of input string */
        q = str;
        p = out;

        /* skip over leading spaces */
        while (isspace(*q)) {
            i++;
            q++;
        }
        /* i now has start position of string */

        /* skip over trailing spaces */
        q = str + len - 1;
        while (isspace(*q)) {
            j++;
            q--;
        }
        /* j now has end position of string */

        j = len - j - i;            /* count number of remaining characters */
        q = str + i;          /* set pointer to beginning of trimmed string */
        for (; j>0; j--) {
            *p = *q;                                     /* copy characters */
            p++;
            q++;
        }

        *p = '\0';                                      /* terminate string */

        return(out);
    } else {
        return(NULL);
    }
}

void strtrim_inplace(char *str) {
    /*!
     * \brief
     *   Remove leading and trailing blanks from string.
     *
     * This function removes all leading and trailing " " characters from
     * \em str using \c isspace(). In contrast to \c sm_strtrim() the action
     * is performed in place, i.e. the input gets overwritten.
     *
     * \b INPUT & OUTPUT:
     * \param str  string.
     *
     * \b OUTPUT:
     * \return     Nothing.
     */

    if (str != NULL && *str != 0) {
        int i = 0,                  /* counter for start position of string */
            j = 0,                    /* counter for end position of string */
            len = strlen(str);                    /* length of input string */

        char *p, *q;       /* pointers for looping through the input string */

        /* set pointers to beginning of input string */
        p = str;
        q = str;

        /* skip over leading spaces */
        while (isspace(*q)) {
            i++;
            q++;
        }
        /* i now has start position of string */

        /* skip over trailing spaces */
        q = str + len - 1;
        while (isspace(*q)) {
            j++;
            q--;
        }
        /* j now has end position of string */

        j = len - j - i;            /* count number of remaining characters */
        q = str + i;          /* set pointer to beginning of trimmed string */
        for (; j>0; j--) {
            *p = *q;                                     /* copy characters */
            p++;
            q++;
        }

        *p = '\0';                                      /* terminate string */
    }
}

cpl_boolean isnumber(char *str) {
    /*!
     * \brief
     *   Check if string contains number.
     *
     * This function checks whether \em str contains a valid number. A leading
     * "+" or "-" is treated as a sign. Also a single "." is identified as a
     * decimal point.
     *
     * \note
     *   Surrounding spaces are not treated.
     *
     * \b INPUT:
     * \param str  String.
     *
     * \b OUTPUT:
     * \return     CPL_TRUE if \em str is number, CPL_FALSE else.
     */

    int i, d;
    int flt = 0; /* string contains ".", i.e. float number */

    /* include "-" and "+" as sign */

    if (str && *str) {
        if (str[0] == '+' || str[0] == '-') {
            i = 1;
        } else {
            i = 0;
        }

        for (;(unsigned)i < strlen(str); i++) {
            d = isdigit(str[i]);

            if (d == 0 && flt == 1) {
                return CPL_FALSE;
            }

            if (flt == 0 && str[i] != '.' && d == 0) {
                return CPL_FALSE;
            }

            if (flt == 0 && str[i] == '.') {
                flt = 1;
            }
        }
        return CPL_TRUE;
    } else {
        return CPL_FALSE;
    }
}

cpl_boolean isinteger(char *str) {
    /*!
     * \brief
     *   Check if string contains an integer only.
     *
     * This function checks whether \em str contains a valid integer. A
     * leading "+" or "-" is treated as a sign.
     *
     * \note
     *   Surrounding spaces are not treated.
     *
     * \b INPUT:
     * \param str  String.
     *
     * \b OUTPUT:
     * \return     CPL_TRUE if \em str is integer, CPL_FALSE else.
     */

     int i;
     int falseflag=0;

    /* include "-" and "+" as sign */

    if (str && *str) {
        if (str[0] == '+' || str[0] == '-') {
            i = 1;
        } else {
            i = 0;
        }

        for (;(unsigned)i < strlen(str); i++) {
            if (isdigit(str[i]) == 0)
            {
                falseflag=1;
            }
        }
    }

    if (falseflag==1)
    {
        return CPL_FALSE;
    }
    else
    {
        return CPL_TRUE;
    }

}

char *rem_ext (const char *str, const char dot, const char sep) {
    /*!
     * \brief
     *   Remove extension from file.
     *
     * Given a string \em str, an extension separator \em dot and a path
     * separator \em sep (0 means to ignore), remove \em sep from \em str.
     *
     * \note
     *   The returned string must be freed manually.
     *
     * \b INPUT:
     * \param str  String.
     * \param dot  "." character.
     * \param sep  path separator (e.g. "/").
     *
     * \b OUTPUT:
     * \return     String without extension.
     */

    char *retstr, *lastdot, *lastsep;

    // Error checks and allocate string.
    if (str == NULL) {
        return NULL;
    }
    if ((retstr = malloc(strlen(str)+1)) == NULL) {
        return NULL;
    }

    // Make a copy and find the relevant characters.
    strcpy(retstr, str);
    lastdot = strrchr(retstr, dot);
    lastsep = (sep == 0) ? NULL : strrchr(retstr, sep);

    // If it has an extension separator.

    if (lastdot != NULL) {
        // and it's before the extenstion separator.
        if (lastsep != NULL) {
            if (lastsep < lastdot) {
                // then remove it.
                *lastdot = '\0';
            }
        } else {
            // Has extension separator with no path separator.
            *lastdot = '\0';
        }
    }

    // Return the modified string.
    return retstr;
}


/*!
 * \brief
 *   Count specified characters in a \em string.
 *
 * This routine checks the number of characters in a \em string. It is now
 * modified to check two successive characters. \em Chr is considered to be the
 * first and \em chr2 the second. Only if these two characters follow each
 * other the number of characters \em ctr is increased by one.
 *
 * \b INPUT:
 * \param txt  String.
 * \param chr  Character to check.
 * \param chr2 Character to check.
 *
 * \return     Number of character pairs found in the string.
 */

int countChar(char* txt, char chr, char chr2) {
  unsigned int i, ctr = 0;
  for (i = 0; i < strlen(txt); i++)
      ctr += (txt[i] == chr && txt[i + 1] == chr2);
  return ctr;
}


cpl_error_code remove_chr(char *xp) {

	char *ptr;

	if(strncmp(xp, "*", 1) == 0) {
		ptr = strtok(xp, "*");
		sprintf(xp, "%s", ptr);
		ptr = strtok(NULL, " ");
	}

	if(strncmp(xp, "[", 1) == 0) {
		ptr = strtok(xp, "[");
		sprintf(xp, "%s", ptr);
		ptr = strtok(NULL, " ");
	}

	if(strncmp(xp, "'", 1) == 0) {
		ptr = strtok(xp, "'");
		sprintf(xp, "%s", ptr);
		ptr = strtok(NULL, " ");
	}

	return CPL_ERROR_NONE;
}

/**@}*/
