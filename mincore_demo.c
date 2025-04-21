//: ----------------------------------------------------------------------------
//: includes
//: ----------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <memory.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
//: ----------------------------------------------------------------------------
//: constants
//: ----------------------------------------------------------------------------
#ifndef STATUS_OK
#define STATUS_OK 0
#endif
#ifndef STATUS_ERROR
#define STATUS_ERROR -1
#endif

//: ----------------------------------------------------------------------------
//: check file page cache state
//: ----------------------------------------------------------------------------
int main(int argc, char **argv)
{
        int l_s;
        // -------------------------------------------------
        // args
        // -------------------------------------------------
        if (argc < 2)
        {
                fprintf(stderr, "usage: %s (file)\n", argv[0]);
                return STATUS_ERROR;
        }
        // -------------------------------------------------
        // open a file
        // -------------------------------------------------
        const char* l_file = argv[1];
        int l_fd = open(l_file, O_RDONLY);
        if(l_fd < 0)
        {
                fprintf(stderr, "error: open: %s\n", strerror(errno));
                return STATUS_ERROR;
        }
        // -------------------------------------------------
        // get file size
        // -------------------------------------------------
        struct stat l_stat = { 0 };
        l_s = fstat(l_fd, &l_stat);
        if(l_s != 0)
        {
                fprintf(stderr, "error: fstat: %s\n", strerror(errno));
                return STATUS_ERROR;
        }
        // -------------------------------------------------
        // mmap whole file
        // -------------------------------------------------
        void *l_map = NULL;
        l_map = mmap(NULL, l_stat.st_size, PROT_READ, MAP_SHARED, l_fd, 0);
        if(l_map == NULL)
        {
                fprintf(stderr, "error: mmap: %s\n", strerror(errno));
                return STATUS_ERROR;
        }
        // -------------------------------------------------
        // get system page size
        // create state vector
        // -------------------------------------------------
        const long l_ps = sysconf(_SC_PAGESIZE);
        int l_vec_size = (l_stat.st_size+l_ps-1) / l_ps;
        char *l_vec = NULL;
        l_vec = (char*)malloc(l_vec_size);
        if(l_vec == NULL)
        {
                fprintf(stderr, "error: malloc: %s\n", strerror(errno));
                return STATUS_ERROR;
        }
        // -------------------------------------------------
        // mincore on the file and printout percentage used
        // -------------------------------------------------
        l_s = mincore(l_map, l_stat.st_size, l_vec);
        if(l_s == -1)
        {
                fprintf(stderr, "error: mincore: %s\n", strerror(errno));
                return STATUS_ERROR;
        }
        // -------------------------------------------------
        // calc percentage in page cache
        // -------------------------------------------------
        int i = 0;
        int l_num_in_cache = 0;
        for(i = 0; i < l_vec_size; ++i)
        {
                if(((unsigned char*)l_vec)[i])
                {
                        ++l_num_in_cache;
                }
        }
        printf("%d\n", l_num_in_cache);
        printf("%d\n", l_vec_size);
        float l_pcnt;
        l_pcnt = ((float)l_num_in_cache / (float)l_vec_size) * 100.0;
        fprintf(stdout, "file: %s is %.2f%% in page cache\n", l_file, l_pcnt);
	return STATUS_OK;
}
