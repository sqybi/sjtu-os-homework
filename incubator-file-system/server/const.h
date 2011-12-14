#ifndef _CONST_H
#define _CONST_H

/*
 * Define all constants used in the server.
 */

#define VDISK_FILENAME "virtualdisk1.ivd"
    /* The virtual disk file used by IFS server */
#define BLOCK_SIZE 512
    /* Size of a single block */
#define BLOCK_IN_VDISK 409600
    /* Number of blocks in a virtual disk file. */
#define VDISK_FILESIZE (BLOCK_SIZE * BLOCK_IN_VDISK)
    /*
     * Notice that the size of a virtual disk file is:
     *   (BLOCK_IN_VDISK * BLOCK_SIZE) bytes.
     * This will be checked while opening a virtual disk file.
     */

#endif

