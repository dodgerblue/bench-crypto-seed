#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "util.h"

extern struct crypto_api_t apis[];

void print_usage(char *name) {
	int i;

	printf("Usage: %s <way> <lib_id> <block_chunks> <infile> <outfile> \n\
	block_chunks - size of intermediate buffer (block_chunks * %d) \
	way - 0 encrypt, 1 decrypt \
	where lib_id may be one of the following:\n\n", name, MY_BLOCKSIZE);

	for (i = 0; i < 3; i ++) {
		printf("\t%u - %s\n", apis[i].id, apis[i].description);
	}
}

int main(int argc, char *argv[]) {
	int fin, fout;
	char *buffer;
	unsigned int lib_id, block_chunks, way;
	void *handle;
	off_t file_size, blocks;

	if (argc != 6) {
		print_usage(argv[0]);
		goto out_invalid_args;
	}

	way = atoi(argv[1]); // NO CHECK
	lib_id = atoi(argv[2]); // NO CHECK!
	block_chunks = atoi(argv[3]); // NO CHECK!

	fin = open(argv[4], O_RDONLY);
	if (fin == -1) {
		fprintf(stderr, "Unable for open infile %s\n", argv[4]);
		goto out_open_fin;
	}

	fout = open(argv[5], O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fout == -1) {
		fprintf(stderr, "Unable to open outfile %s\n", argv[5]);
		goto out_open_fout;
	}

	file_size = lseek(fin, 0, SEEK_END);
	if (file_size == -1) {
		fprintf(stderr, "Error seeking\n");
		goto out_lseek;
	}

	if (lseek(fin, 0, SEEK_SET) == -1) {
		fprintf(stderr, "Error seeking\n");
		goto out_lseek;
	}

	if (file_size % MY_BLOCKSIZE) {
		fprintf(stderr, "File size is not multiple of %d\n", MY_BLOCKSIZE);
		goto out_invalid_file_size;
	}

	blocks = file_size / MY_BLOCKSIZE;

	buffer = malloc(block_chunks * MY_BLOCKSIZE);
	if (buffer == NULL) {
		fprintf(stderr, "Unable to alloc buffer memory\n");
		goto out_no_memory;
	}

	return 0;

out_no_memory:
out_invalid_file_size:
out_lseek:
	close(fout);
out_open_fout:
	close(fin);
out_open_fin:
out_invalid_args:
	return 1;
}
