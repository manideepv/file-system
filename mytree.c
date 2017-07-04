//In the current program the names of each file and the directory are printed.
//when no arguments are given the program starts from the current working directory.
//when one argument i.e directory name is given, then that is considered as the root.
//reference: linux man 

#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<dirent.h>
#include<limits.h>
#include<stdbool.h>

void list_dir_files(char * directory_name,int depth)
{
    DIR * d;
    d = opendir (directory_name); //opens folder

    if (d==NULL) 
    {
        printf ("Cannot open directory '%s\n", directory_name);
        return;
    }

    while (true) 
    {
        struct dirent * entry;
        entry = readdir (d);
        char * d_name;

        if (entry==NULL)
        {
            break; //no more folders
        }
        d_name = entry->d_name;
        if (strcmp (d_name, "..") != 0 && strcmp (d_name, ".") != 0 && entry->d_type!=DT_DIR){

	    //printf ("%s/%s\n", directory_name, d_name);
            int i=0;
            for(i=0;i<depth;++i)
                printf("  ");
            printf("|__%s\n",d_name);//print only if file name or dir name is not . or ..
}
        if (entry->d_type == DT_DIR) //if its a directory continue recursion
        {
            if (strcmp (d_name, "..") != 0 && strcmp (d_name, ".") != 0) 
            {
                char path[PATH_MAX];
                sprintf (path, "%s/%s", directory_name, d_name);
                int i=0;
                for(i=0;i<=depth;++i)
                    printf("  ");  
                printf ("|%s\n", d_name);
                list_dir_files (path,depth+1);
            }
	}
    }
    closedir (d);
}

int main (int argc,char *argv[])
{
    char dir[1000];
    if(argc==1)
    {   
        getcwd(dir,sizeof(dir));
    }
    else
    {   
        strcpy(dir,argv[1]);
    }
    printf("%s\n",dir);
    list_dir_files(dir,0);
    return 0;
}
