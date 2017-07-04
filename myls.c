//The current program lists the files in a given directory.
//when just ./myls is given the file names in the current directory are printed.
//when ./myls -l is given the file name along with information in current directory is printed.
//when ./myls -l directoryname is given the files in given directory are printed.
// references: linux man

#include<locale.h>
#include<langinfo.h>
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
#include<pwd.h>
#include<grp.h>
#include<time.h>

void print_file_stats(struct stat,char *file_name);
void print_permissions(struct stat); 

int main(int argc,char *argv[])
{
    char cwd[1024];	
    bool details_reqd = false;
    if(argc==3)
    {
        details_reqd = true;    
    }
    else if(argc==2)
    {
        if(strcmp("-l",argv[1])==0)
        {
            details_reqd = true;
        }
    }
   
    if(argc==1)
    {
        getcwd(cwd,sizeof(cwd));
    }
    else
    {
        if(argc==2 && details_reqd == false)
     	    strcpy(cwd,argv[1]);
        else if(argc==3)
            strcpy(cwd,argv[2]);
        else
            getcwd(cwd,sizeof(cwd));
    }
    
    DIR *directory;
    directory = opendir(cwd);
    char *file_name;
    struct dirent *dp;
    while ((dp=readdir(directory)) != NULL) 
    {
        if ( !strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..") )
        {
            continue;
        }
        else 
        {
            file_name = dp->d_name;
            if(details_reqd==false)
                printf("%s  ",file_name);
            else
            {
                char fname[1000];
                sprintf(fname,"%s/%s",cwd,file_name);
                               
                struct stat buffer;
                int status;
                status = stat(fname, &buffer);
		print_file_stats(buffer,file_name);
	    }
        }
    }
    if(details_reqd==false)
       printf("\n");
    closedir(directory);
    return 0;
}

void print_file_stats(struct stat file_Statistics,char* file_name)
{   
    print_permissions(file_Statistics); //to print permissions
    printf("%d ",file_Statistics.st_nlink); // to print number of links
    //group name and user name
    struct passwd  *user;
    struct group   *grp;    
    if ((user = getpwuid(file_Statistics.st_uid)) != NULL) //user name
        printf("(%d/%s) ",file_Statistics.st_uid,user->pw_name);
    else
        printf("%d ", file_Statistics.st_uid);

    if ((grp = getgrgid(file_Statistics.st_gid)) != NULL) //group name
        printf("(%d/%s) ",file_Statistics.st_gid,grp->gr_name);
    else
        printf("%d ", file_Statistics.st_gid);
    printf("%8d ",file_Statistics.st_size); //file size in bytes
    printf("%11d",file_Statistics.st_ino);  // inode number
    printf("%7d ",file_Statistics.st_blocks); //no of blocks
    
    //time and date are printed.
    char date_time[300];
    struct time *time;
    time = localtime(&file_Statistics.st_mtime);
    strftime(date_time, sizeof(date_time), nl_langinfo(D_T_FMT),time);
    printf("%s ", date_time);
    printf("%s\n",file_name); //filename
}

void print_permissions(struct stat file_Statistics)
{
   
    //prints file permissions
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
      printf("x");
    else
      printf("-");
    printf(" ");
}
