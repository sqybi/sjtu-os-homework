#include "server.h"

/*
 * Read from the block placed in *block_num*.
 * The result will be returned in *block*.
 * If success return 0, else return -1.
 */
int read_block( int block_num, char *block )
{
    int block_offset;

    /* calculate real offset in virtual disk file */
    block_offset = block_num * BLOCK_SIZE;

    /* move file offset pointer to the right place */
    if (lseek(vdisk_fildes, block_offset, SEEK_SET) == -1)
    {
        error("read_block() error: lseek() call fault when seeking.\n");
        return -1;
    }

    /* read a block */
    if (read(vdisk_fildes, (void *) block, BLOCK_SIZE) == -1)
    {
        error("read_block() error: read() call fault.\n");
        return -1;
    }

    return 0;
}

