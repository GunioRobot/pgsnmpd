/*-------------------------------------------------------------------------
 * rdbmsSrvParamTable_oids.h
 *
 *      RDBMSMIB mib module.
 *
 *      Copyright (c) 2004-2007, PostgreSQL Global Development Group
 *      Author: Joshua Tolley
 *
 * $Id: rdbmsSrvParamTable_oids.h,v 1.2 2007/09/13 14:20:44 h-saito Exp $
 *
 *-------------------------------------------------------------------------
 */

#ifndef RDBMSSRVPARAMTABLE_OIDS_H
#define RDBMSSRVPARAMTABLE_OIDS_H

#ifdef __cplusplus
extern "C" {
#endif


/* column number definitions for table rdbmsSrvParamTable */
#define RDBMSSRVPARAMTABLE_OID              1,3,6,1,2,1,39,1,7
#define COLUMN_RDBMSSRVPARAMNAME		1
#define COLUMN_RDBMSSRVPARAMSUBINDEX		2
#define COLUMN_RDBMSSRVPARAMID		3
#define COLUMN_RDBMSSRVPARAMCURRVALUE		4
#define COLUMN_RDBMSSRVPARAMCOMMENT		5

#define RDBMSSRVPARAMTABLE_MIN_COL		COLUMN_RDBMSSRVPARAMID
#define RDBMSSRVPARAMTABLE_MAX_COL		COLUMN_RDBMSSRVPARAMCOMMENT


#ifdef __cplusplus
}
#endif

#endif /* RDBMSSRVPARAMTABLE_OIDS_H */
