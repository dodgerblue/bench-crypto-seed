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
	block_chunks - size of intermediate buffer (block_chunks * %d)\n \
	way - 0 encrypt, 1 decrypt\n \
	where lib_id may be one of the following:\n\n", name, MY_BLOCKSIZE);

	for (i = 0; i < 3; i ++) {
		printf("\t%u - %s\n", apis[i].id, apis[i].description);
	}
}

int process_chunk(void *handle, int lib_id, unsigned int way, int fin, char *bufin, int fout, char *bufout, size_t blocks) {
	ssize_t brw;

	brw = read(fin, bufin, blocks * MY_BLOCKSIZE);
	if (brw == -1) {
		fprintf(stderr, "Unable to read chunk from file\n");
		return 1;
	}

	if (way == 0)
		apis[lib_id].encrypt(handle, bufin, bufout, blocks);
	else
		apis[lib_id].decrypt(handle, bufin, bufout, blocks);

	brw = write(fout, bufout, blocks * MY_BLOCKSIZE);
	if (brw == -1) {
		fprintf(stderr, "Unable to write chunk to file\n");
		return 1;
	}

	return 0;
}

int main(int argc, char *argv[]) {
	int fin, fout;
	char *bufin, *bufout;
	unsigned int lib_id, block_chunks, way;
	void *handle;
	off_t file_size, blocks, i;

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

	bufin = (char *) malloc(block_chunks * MY_BLOCKSIZE);
	if (bufin == NULL) {
		fprintf(stderr, "Unable to alloc in buffer memory\n");
		goto out_no_memory_bufin;
	}

	bufout = (char *) malloc(block_chunks * MY_BLOCKSIZE);
	if (bufout == NULL) {
		fprintf(stderr, "Unable to alloc out buffer memory\n");
		goto out_no_memory_bufout;
	}

	apis[lib_id].init(&handle);

	for (i = 0; i + (off_t) block_chunks < blocks; i += block_chunks)
		if (process_chunk(handle, lib_id, way, fin, bufin, fout, bufout, block_chunks))
			goto out_fail_process;

	i = blocks - i;
	if (i)
		if (process_chunk(handle, lib_id, way, fin, bufin, fout, bufout, i))
			goto out_fail_process;

	free(bufout);
	free(bufin);

	close(fout);
	close(fin);

	return 0;

out_fail_process:
	free(bufout);
out_no_memory_bufout:
	free(bufin);
out_no_memory_bufin:
out_invalid_file_size:
out_lseek:
	close(fout);
out_open_fout:
	close(fin);
out_open_fin:
out_invalid_args:
	return 1;
}
