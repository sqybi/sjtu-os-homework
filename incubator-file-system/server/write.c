#include "server.h"

/*
 * Write into the block placed in *block_num*.
 * The content to write is placed in *block*.
 * If success return 0, else return -1.
 */
int write_block( int block_num, char *block )
{
    int block_offset;

    /* calculate real offset in virtual disk file */
    block_offset = block_num * BLOCK_SIZE;

    /* move file offset pointer to the right place */
    if (lseek(vdisk_fildes, block_offset, SEEK_SET) == -1)
    {
        error("write_block() error: lseek() call fault when seeking.\n");
        return -1;
    }

    /* write a block */
    if (write(vdisk_fildes, (void *) block, BLOCK_SIZE) == -1)
    {
        error("write_block() error: write() call fault.\n");
        return -1;
    }

    return 0;
}

