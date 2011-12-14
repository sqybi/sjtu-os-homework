#include "server.h"

/*
 * Open the virtual hard disk device.
 * If success then return 0, else return -1.
 */
int dev_open( void )
{
    struct stat vdisk_filinf;
    int i;

    /* avoid re-open */
    if (vdisk_is_open)
    {
        err("dev_open() error: virtual disk has been opened before!\n");
        return -1;
    }

    /* open file */
    if ((vdisk_fildes = open(VDISK_FILENAME, O_RDWR)) == -1)
    {
        err("def_open() error: open() call fault.\n");
        return -1;
    }

    /* check the virtual disk size, extend file if size not enough */
    if (fstat(vdisk_fildes, vdisk_filinf) == -1)
    {
        err("def_open() error: fstat() call fault.\n");
        close(vdisk_fildes);
        return -1;
    }
    if (vdisk_filinf.st_size < VDISK_FILESIZE)
    {
        lseek(vdisk_fildes, 0, SEEK_END); /* move to EOF */
        for (i = 0; i != VDISK_FILESIZE - vdisk_filinf.st_size; ++i)
            if (write(vdisk_fildes, (void *) '\0', 1) == -1)
            {
                err("def_open() error: error when adding blocks in virtual disk.\n");
                close(vdisk_fildes);
                return -1;
            }
    }

    /* mark as opened */
    vdisk_is_open = 1;

    return 0;
}

