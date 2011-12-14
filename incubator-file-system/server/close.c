#include "server.h"

/*
 * Close the virtual har disk device.
 * If success return 0, else return -1.
 */
int dev_close( void )
{
    /* check if virtual disk is not opened */
    if (!vdisk_is_open)
    {
        err("dev_close() error: virtual disk has not been opened yet!\n");
        return -1;
    }

    /* close file */
    if (close(vdisk_fildes) == -1)
    {
        err("dev_close() error: close() call fault.\n");
    }

    /* mark as closed */
    vdisk_is_open = 0;

    return 0;
}

