#include<stdio.h>
#include<sys/stat.h>

int main(int argc, char*argv[]) {

  
//     struct stat { /* when _DARWIN_FEATURE_64_BIT_INODE is NOT defined */
//          dev_t    st_dev;    /* device inode resides on */
//          ino_t    st_ino;    /* inode's number */
//          mode_t   st_mode;   /* inode protection mode */
//          nlink_t  st_nlink;  /* number of hard links to the file */
//          uid_t    st_uid;    /* user-id of owner */
//          gid_t    st_gid;    /* group-id of owner */
//          dev_t    st_rdev;   /* device type, for special file inode */
//          struct timespec st_atimespec;  /* time of last access */
//          struct timespec st_mtimespec;  /* time of last data modification */
//          struct timespec st_ctimespec;  /* time of last file status change */
//          off_t    st_size;   /* file size, in bytes */
//          quad_t   st_blocks; /* blocks allocated for file */
//          u_long   st_blksize;/* optimal file sys I/O ops blocksize */
//          u_long   st_flags;  /* user defined flags for file */
//          u_long   st_gen;    /* file generation number */
//      };
  

  struct stat fst;
  stat(argv[1], &fst);

  printf("inode number : %llu\n", fst.st_ino);
  printf("mode         : %o\n", fst.st_mode);

  return 0;
}
