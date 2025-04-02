#include <sys/types.h>
#include <limits.h>
#include <db.h>
#include <fcntl.h>

int main(void)
{
    DBHANDLE db;
        if((db = db_open("db4", O_RDWR | O_CREAT | O_CREAT,FILE_MODE)) == NULL)
           printf("error in db");
}