/*!
 * \ingroup galapagos
 */

/**@{*/

/*!
 * \file gala_sextractor.h
 *
 * \brief Header file for SExtractor execution block.
 *
 * \author Marco Barden
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GALA_SEXTRACTOR_H
#define GALA_SEXTRACTOR_H

#include <string.h>
#include <math.h>
#include <sys/stat.h>
#include <mpi.h>
#include <cpl.h>

#include "sextractor_utils.h"
#include "string_ops.h"
#include "galapagos_utils.h"

#include <libgen.h>

/*!
 * \brief Execute SExtractor code.
 *
 * Execute SExtractor from within GALAPAGOS using a CPL_PARAMETERLIST
 * \em sex_setup for setting up the process.
 *
 * \b INPUT:
 * \param sex_setup     setup for SExtractor CPL_PARAMETERLIST
 *
 * \b OUTPUT:
 * - returns CPL_ERROR_CODE
 *
 * \note:
 * It is possible to "feed" ::gala_sextractor () with as many setups as
 * desired. Therefore it is necessary to fill the sex_setup file with
 * path strings to each .sex .cat and .seg setup file. Each path string must
 * be isolated by a space character. Only if there is a space character
 * between each setup file, gala_sextractor will recognize the path stings
 * and be able to work with the input files. Of the number of .sex, .cat
 * and .seg file has to be equal - otherwise an error will be returned.
 */
cpl_error_code gala_sextractor(cpl_parameterlist *sex_setup);

#endif /* GALA_SEXTRACTOR_H */

#ifdef __cplusplus
}
#endif

/**@}*/
