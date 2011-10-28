/*-------------------------------------------------------------------------
 * rdbmsDbInfoTable_enums.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsDbInfoTable_enums.h,v 1.3 2007/09/13 14:20:43 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSDBINFOTABLE_ENUMS_H
#define RDBMSDBINFOTABLE_ENUMS_H

#ifdef __cplusplus
extern "C" {
#endif

 /*
 * NOTES on enums
 * ==============
 *
 * Value Mapping
 * -------------
 * If the values for your data type don't exactly match the
 * possible values defined by the mib, you should map them
 * below. For example, a boolean flag (1/0) is usually represented
 * as a TruthValue in a MIB, which maps to the values (1/2).
 *
 */
/*************************************************************************
 *************************************************************************
 *
 * enum definitions for table rdbmsDbInfoTable
 *
 *************************************************************************
 *************************************************************************/

/*************************************************************
 * constants for enums for the MIB node
 * rdbmsDbInfoSizeUnits (INTEGER / ASN_INTEGER)
 *
 * since a Textual Convention may be referenced more than once in a
 * MIB, protect againt redefinitions of the enum values.
 */
#ifndef RDBMSDBINFOSIZEUNITS_ENUMS
#define RDBMSDBINFOSIZEUNITS_ENUMS

#define RDBMSDBINFOSIZEUNITS_BYTES  1
#define RDBMSDBINFOSIZEUNITS_KBYTES  2
#define RDBMSDBINFOSIZEUNITS_MBYTES  3
#define RDBMSDBINFOSIZEUNITS_GBYTES  4
#define RDBMSDBINFOSIZEUNITS_TBYTES  5


#endif /* RDBMSDBINFOSIZEUNITS_ENUMS */

    /*
     * TODO:140:o: Define interal representation of rdbmsDbInfoSizeUnits enums.
     * (used for value mapping; see notes at top of file)
     */
#define INTERNAL_RDBMSDBINFOSIZEUNITS_BYTES  1
#define INTERNAL_RDBMSDBINFOSIZEUNITS_KBYTES  2
#define INTERNAL_RDBMSDBINFOSIZEUNITS_MBYTES  3
#define INTERNAL_RDBMSDBINFOSIZEUNITS_GBYTES  4
#define INTERNAL_RDBMSDBINFOSIZEUNITS_TBYTES  5



#ifdef __cplusplus
}
#endif

#endif /* RDBMSDBINFOTABLE_ENUMS_H */
