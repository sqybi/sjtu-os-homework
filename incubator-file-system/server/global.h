#ifndef _GLOBAL_H
#define _GLOBAL_H

/*
 * All global vairables here.
 * Each file should include this header (by include server.h), and each
 * global vairable is declared in table.c.
 */

/*
 * In table.c, there is a defination _TABLE, which clear the defination
 * of EXTERN. Otherwise, EXTERN is declared as "extern".
 */
#ifdef _TABLE
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN int vdisk_is_open;
    /* Indicates whether virtual disk has been opened */
EXTERN int vdisk_fildes;
    /* File descriptor of the virtual disk (after opened) */

#endif

