/*
  Copyright (C) 2012 Joseph J. Pfeiffer, Jr., Ph.D. <pfeiffer@cs.nmsu.edu>

  This program can be distributed under the terms of the GNU GPLv3.
  See the file COPYING.

  There are a couple of symbols that need to be #defined before
  #including all the headers.
*/

#ifndef _PARAMS_H_
#define _PARAMS_H_


// The FUSE API has been changed a number of times.  So, our code
// needs to define the version of the API that we assume.  As of this
// writing, the most current API version is 26
#define FUSE_USE_VERSION 26

// need this to get pwrite().  I have to use setvbuf() instead of
// setlinebuf() later in consequence.
#define _XOPEN_SOURCE 500

// maintain bbfs state in here
#include <limits.h>
#include <stdio.h>


#define HASH_SIZE 20
#define FILE_SIZE 16


struct hashlist {
	unsigned char hash[HASH_SIZE+1];
	char block_name[PATH_MAX];
	int counter;
	int fd;
	struct hashlist *next;
	struct hashlist *prev;
};

typedef struct hashlist hash_t;

struct filelist {	
	char file_name[PATH_MAX];
	int counter;
	hash_t *hashtable[FILE_SIZE];
	struct filelist *next;
	struct filelist *prev;
};

typedef struct filelist file_t;


struct bb_state {
    FILE *logfile;
    char *rootdir;
	file_t *file_head;
	hash_t *hash_head;
};

	
#define BB_DATA ((struct bb_state *) fuse_get_context()->private_data)

#endif
