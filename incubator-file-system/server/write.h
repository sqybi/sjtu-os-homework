#ifndef _WRITE_H
#define _WRITE_H

/*
 * Write into the block placed in *block_num*.
 * The content to write is placed in *block*.
 * If success return 0, else return -1.
 */
int write_block( int block_num, char *block );

#endif

