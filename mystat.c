//The following program prints file name, file size, number of blocks allocated, reference link count, file permissions and file inode using stat() function
// reference: linux man
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<limits.h>
#include<stdbool.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdint.h>

void print_file_stats(struct stat,char *file_name);
void print_permissions(struct stat);

int main(int argc, char* argv[])
{
    char file_name[1000];
    if(argc>1)
    {
        strcpy(file_name,argv[1]);
    }
    else
    {
        printf("File name not given\n");
        return 0;
    }
    struct stat buffer;
    int status;
    status = stat(file_name, &buffer);
    print_file_stats(buffer,file_name);
    
    return 0;
}

void print_file_stats(struct stat file_Statistics,char* file_name)
{   
    printf("Filename: %s\n",file_name); //filename
    printf("File size: %d bytes\n",file_Statistics.st_size); //file size in bytes
    printf("Number of blocks: %d\n",file_Statistics.st_blocks); //no of blocks
    printf("Number of links: %d\n",file_Statistics.st_nlink); // to print number of links
    print_permissions(file_Statistics); //to print permissions
    printf("File inode: %d\n",file_Statistics.st_ino);//file inode
      
}

void print_permissions(struct stat file_Statistics)
{
    //prints file permissions
    printf("File permissions:(%04o/",file_Statistics.st_mode & 07777);
    if(S_ISDIR(file_Statistics.st_mode))
      printf("d");
    else
      printf("-");
    //file permission of owner of file start here
    if((file_Statistics.st_mode & S_IRUSR))
      printf("r");
    else
      printf("-");
    if((file_Statistics.st_mode & S_IWUSR))
       printf("w");
    else
       printf("-");
    if((file_Statistics.st_mode & S_IXUSR))
      printf("x");
    else
      printf("-");
    //file permissions for group owner of file start here
    if((file_Statistics.st_mode & S_IRGRP))
      printf("r");
    else
      printf("-");
    if((file_Statistics.st_mode & S_IWGRP))
       printf("w");
    else
       printf("-");
    if((file_Statistics.st_mode & S_IXGRP))
       printf("x");
    else
       printf("-");
    //file permissions for other user start here
    if((file_Statistics.st_mode & S_IROTH))
      printf("r");
    else
      printf("-");
    if((file_Statistics.st_mode & S_IWOTH))
       printf("w");
    else
       printf("-");
    if((file_Statistics.st_mode & S_IXOTH))
      printf("x)");
    else
      printf("-)");
    printf("\n");
}
