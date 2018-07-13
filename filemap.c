#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/fiemap.h>
#include <linux/fs.h>

#ifndef FS_IOC_FIEMAP
#define FS_IOC_FIEMAP	_IOWR('f', 11, struct fiemap)
#endif

void usage(char **argv)
{
	fprintf(stderr, "%s [filename] ...\n", argv[0]);
}

struct fiemap *read_fiemap(int fd)
{
	struct fiemap *fiemap;
	int extents_size;

	if ((fiemap = (struct fiemap*)malloc(sizeof(struct fiemap))) == NULL) {
		fprintf(stderr, "malloc\n");	
		return NULL;
	}

	memset(fiemap, 0, sizeof(struct fiemap));

	fiemap->fm_start = 0;
	fiemap->fm_length = ~0;
	fiemap->fm_flags = 0;
	fiemap->fm_extent_count = 0;
	fiemap->fm_mapped_extents = 0;

	/* count how many extents there are */
	if (ioctl(fd, FS_IOC_FIEMAP, fiemap) < 0) {
		fprintf(stderr, "fiemap ioctl() failed\n");
		return NULL;
	}

	/* read in the extents */
	extents_size = sizeof(struct fiemap_extent) * 
		(fiemap->fm_mapped_extents);

	/* resize fiemaps for all extents */
	if ((fiemap = (struct fiemap*)realloc(fiemap,sizeof(struct fiemap) + 
					extents_size)) == NULL) {
		fprintf(stderr, "realloc fiemap\n");	
		return NULL;
	}

	memset(fiemap->fm_extents, 0, extents_size);
	fiemap->fm_extent_count = fiemap->fm_mapped_extents;
	fiemap->fm_mapped_extents = 0;

	if (ioctl(fd, FS_IOC_FIEMAP, fiemap) < 0) {
		fprintf(stderr, "ioctl() FS_IOC_FIEMAP failed\n");
		return NULL;
	}

	return fiemap;
}

void show_fiemap(struct fiemap *fiemap, char *filename)
{
	int i = 0;

	printf("File %s has %d extents :\n", filename, fiemap->fm_mapped_extents);
	printf("#\tLogical          Physical         Length           Flag\n");
	for (i = 0; i < fiemap->fm_mapped_extents; i++) {
		printf("%d:\t%-16.16llx %-16.16llx %-16.16llx %-4.4x\n", i,
				fiemap->fm_extents[i].fe_logical,
				fiemap->fm_extents[i].fe_physical,
				fiemap->fm_extents[i].fe_length,
				fiemap->fm_extents[i].fe_flags);
	}

	printf("\n");
}

int main(int argc, char **argv)
{
	int i = 0;

	if (argc < 2) {
		usage(argv);
		return 0;
	}

	for (i = 1; i < argc; i++) {
		int fd = 0;

		if ((fd = open(argv[i], O_RDONLY)) < 0) {
			perror("open file %s failed\n");
			perror(argv[i]);
			break;
		} else {
			struct fiemap *fiemap = NULL;

			if ((fiemap = read_fiemap(fd)) != NULL) {
				show_fiemap(fiemap, argv[i]);
				free(fiemap);
			}
			close(fd);
		}
	}

	return 0;
}

