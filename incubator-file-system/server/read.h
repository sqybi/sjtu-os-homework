#ifndef _READ_H
#define _READ_H

/*
 * Read from the block placed in *block_num*.
 * The result will be returned in *block*.
 * If success return 0, else return -1.
 */
int read_block( int block_num, char *block );

#endif

