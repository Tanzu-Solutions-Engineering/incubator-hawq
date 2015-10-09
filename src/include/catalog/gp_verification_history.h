/*-------------------------------------------------------------------------
 *
 * gp_verification_history.h
 *    record status information on online verification requests
 *    gpverify utility adds and deletes records in this table
 *
 * Copyright (c) 2006-2011, Greenplum Inc.
 *
 * $Id: $
 * $Change: $
 * $DateTime: $
 * $Author: $
 *-------------------------------------------------------------------------
 */
#ifndef _GP_VERIFY_HIS_H_
#define _GP_VERIFY_HIS_H_

#include "catalog/genbki.h"

/*
 * Defines for gp_verification_history table
 */
#define GpVerificationHistoryRelationName		"gp_verification_history"

#define MASTER_DBID 1
#define MASTER_CONTENT_ID (-1)

/* TIDYCAT_BEGINDEF

   CREATE TABLE gp_verification_history
   with (camelcase=GpVerificationHistory, shared=true, oid=false, relid=6429, reltype_oid=6430, content=MASTER_ONLY)
   (

   vertoken             name       ,    -- token of the verification request, 63 characters or less
   vertype              smallint   ,    -- 0=FULL (i.e. all files and directories), 1=FILE, 2=DIRECTORY
   vercontent           smallint   ,    -- -1= all primary mirror pairs, >=0 specific primary/mirror pair

   verstarttime         timestamp with time zone,  --time the request is started
   verstate             smallint   ,     -- 0=Started, 1=Suspended, 2=Aborted, 3=Failed, 4=Succeeded
  
   verdone              boolean    ,     --0 if started or suspeneded, 1 if aborted or failed or successful completion
   verendtime           timestamp with time zone,  --time the request is completely done processing, only valid id verdone is true, latest end time for this token on any primary/mirror pair

   vermismatch          boolean         --were mismatches found on any primary/mirror pair for this token
  
   );

   create unique index on gp_verification_history(vertoken) with (indexid=6431);  

   TIDYCAT_ENDDEF
*/
/* TIDYCAT_BEGIN_CODEGEN 

   WARNING: DO NOT MODIFY THE FOLLOWING SECTION: 
   Generated by tidycat.pl version 33
   on Wed Aug 15 14:59:02 2012
*/


/*
 TidyCat Comments for gp_verification_history:
  Table is shared, so catalog.c:IsSharedRelation is updated.
  Table does not have an Oid column.
  Table has static type (see pg_types.h).
  Table contents are only maintained on MASTER.
  Table has weird hack for timestamp column.
 
*/

/*
 * The CATALOG definition has to refer to the type of "verstarttime" et al as
 * "timestamptz" (lower case) so that bootstrap mode recognizes it.  But
 * the C header files define this type as TimestampTz.	Since the field is
 * potentially-null and therefore cannot be accessed directly from C code,
 * there is no particular need for the C struct definition to show the
 * field type as TimestampTz --- instead we just make it Datum.
 */

#define timestamptz Datum

/* ----------------
 *		gp_verification_history definition.  cpp turns this into
 *		typedef struct FormData_gp_verification_history
 * ----------------
 */
#define GpVerificationHistoryRelationId	6429

CATALOG(gp_verification_history,6429) BKI_SHARED_RELATION BKI_WITHOUT_OIDS
{

	NameData	vertoken;		/* token of the verification request, 63 characters or less */
	int2		vertype;		/* 0=FULL (i.e. all files and directories), 1=FILE, 2=DIRECTORY */
	int2		vercontent;		/* -1= all primary mirror pairs, >=0 specific primary/mirror pair */

	timestamptz	verstarttime;	/*time the request is started */
	int2		verstate;		/* 0=Started, 1=Suspended, 2=Aborted, 3=Failed, 4=Succeeded */

  	bool		verdone;		/*0 if started or suspeneded, 1 if aborted or failed or successful completion */
	timestamptz	verendtime;		/*time the request is completely done processing, only valid id verdone is true, latest end time for this token on any primary/mirror pair */

	bool		vermismatch;	/*were mismatches found on any primary/mirror pair for this token */
} FormData_gp_verification_history;

#undef timestamptz


/* ----------------
 *		Form_gp_verification_history corresponds to a pointer to a tuple with
 *		the format of gp_verification_history relation.
 * ----------------
 */
typedef FormData_gp_verification_history *Form_gp_verification_history;


/* ----------------
 *		compiler constants for gp_verification_history
 * ----------------
 */
#define Natts_gp_verification_history				8
#define Anum_gp_verification_history_vertoken		1
#define Anum_gp_verification_history_vertype		2
#define Anum_gp_verification_history_vercontent		3
#define Anum_gp_verification_history_verstarttime	4
#define Anum_gp_verification_history_verstate		5
#define Anum_gp_verification_history_verdone		6
#define Anum_gp_verification_history_verendtime		7
#define Anum_gp_verification_history_vermismatch	8


/* TIDYCAT_END_CODEGEN */

#endif /*_GP_VERIFY_HIS_H_*/