/* $Header:   L:/pvcs/1000/psos332/archives/inc/XMININT.H_v   2.1   01 Aug 1996 14:52:14   BKYMER  $ */
#ifndef WITHIN_X_MIN_INTERVAL_H
#define WITHIN_X_MIN_INTERVAL_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name:  WITHIN_X_MIN_INTERVAL 

   Filename: xminint.h


 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
       0             1/23/96       Mark L      Initial version

 ------------------------------- DESCRIPTION -----------------------------------

   This header contains all the information needed by within_x_min_interval.c 

 ------------------------------ INCLUDE FILES ----------------------------------
*/


/*
 --------------------------------- DEFINES -------------------------------------
*/


/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

BOOLEAN WithinXMinInterval (UINT8          x_minutes,
			                            struct t_date  last_reset_date_ptr,
                               struct t_time  last_reset_time_ptr,
                               struct t_date  reset_date_ptr,
                               struct t_time  reset_time_ptr);

#endif /* WITHIN_X_MIN_INTERVAL_H */
