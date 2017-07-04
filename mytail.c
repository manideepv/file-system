//The current program prints out the last few lines of a file that has been given when ./mytail -n filename is given. where n is no of lines.
//reference: linux man

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

void read_file(FILE* file,int n);
void print_lines(FILE* file,off_t line_no);

int main(int argc,char *argv[])
{
    FILE *file;
    char *file_name;
    file_name = argv[2];
    int num_lines;
    num_lines = strtol(argv[1],NULL,10);
    num_lines = -num_lines;
    
    //open file for reading
    file = fopen(file_name,"r");
    if(file==NULL)
    {
        printf("Error in reading file\n");
        exit(1);
    }
    read_file(file,num_lines);
    return 0;
}

void read_file(FILE* file,int n)
{
  off_t fposition;
  fseek(file,0,SEEK_END); //end of file
  fposition= ftell(file);
  off_t indx,end= fposition;
  int lines_no= 0;
  char cbyte;

  for(indx=fposition; indx >= 0; indx --)
  {
    cbyte= fgetc(file);
    if (cbyte == '\n' && (end - indx) > 1)
    {
       lines_no ++;
       if(lines_no == n)
       {
           break;
       }
    }
    fposition--;
    fseek(file,fposition,SEEK_SET);
  }
  print_lines(file, fposition);
  fclose(file);
}

void print_lines(FILE* file,off_t line_no)
{
  int file_desc;
  file_desc= fileno(file);
  int read_n;
  char buffer[3000];
  lseek(file_desc,(line_no + 1),SEEK_SET);
  while((read_n= read(file_desc,buffer,3000)) > 0)
  {
    write(STDOUT_FILENO, buffer, read_n);
  }
}
