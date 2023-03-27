#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>

#define MAX_STRING 6000
#define MIN_STRING 200

int read_file(int i, char buff[MAX_STRING], unsigned short byte)
{// function to read act file
    int a=0,b=0,output=0;
    char buffer[MIN_STRING];
    FILE *act_file = fopen(buff,"rb"); // open input act file
    
    fseek(act_file, i, SEEK_SET );
    fread(&a, 1, 1, act_file);

    if(byte==2){
    fseek(act_file, i+1, SEEK_SET );
    fread(&b, 1, 1, act_file);
    }

    fclose(act_file);
    
    if(byte==2){
    sprintf(buffer,"%.2x%.2x",a,b); // store 1st double byte as text.
    } else { sprintf(buffer,"%.2x",a); }
    output = (int)strtol(buffer, NULL, 16); // convert text to intiger
    return output;
}


void shutdown()
{
    printf("Example usage: ./drs [path to folder to search] [how many bytes encoded supports 1 or 2] [decimal relative search parameters.]\nDRS tool made by msmalik681 to relative search all files in a directory.\n");
    exit(0);
}


int main(int argc, char *argv[])
{

if(argc<3){ shutdown(); }

struct stat statbuf;
DIR *dir;
char buff[MAX_STRING];
struct dirent *file;
dir = opendir(argv[1]);
FILE *log_file;
log_file=fopen("log.txt", "w");
fprintf(log_file,"msmalik681 DRS tool results from last search\n");
fclose(log_file);

while ((file = readdir(dir)) != NULL)
{
    if (!strcmp (file->d_name, ".") || !strcmp (file->d_name, "..") ){ continue; }

    sprintf(buff,"%s/%s/", argv[1],file->d_name);
    if(stat(buff, &statbuf) == 0){ continue; }

    sprintf(buff,"%s/%s", argv[1],file->d_name);
    
        char string[MIN_STRING];
        // strcpy(string,argv[1]);
        char buffer[MIN_STRING],text[MAX_STRING];
        int i=0,j=0,k=0,a=0,b=0,diff=0;
        unsigned short hit=0, byte = atoi(argv[2]);
        if(!( byte==1 || byte==2 )){ shutdown(); }// just in case non valid byte

        FILE *input_file;
        input_file = fopen(buff,"rb"); // open input act file
        fseek(input_file, 0, SEEK_END); // jump to end of file
        int eof=0;
        eof = ftell(input_file);
        fclose(input_file);
        printf("\rWorking. . . ");

        for(i=0;i<eof;i++) // read only i+argsx2 so you don't go over eof
        {
            k=3;

            for(j=i;k<argc;j=j+byte)
            {
                if(j+byte>eof){
                hit=0; break;
                }
                hit=1;
                a = read_file(j,buff,byte);
                b = read_file((j+byte),buff,byte);
                // check condition to identify which is largest number
                diff = a>b?a-b:b-a;

                if(atoi(argv[k])==diff){
                    k++; continue;
                }
                
                hit=0;
                break;
            }


            if(hit)
            {
                printf("file: %s offset: %d\n",file->d_name,i);
                FILE *log_file;
                log_file=fopen("log.txt", "a");
                fprintf(log_file, "file: %s offset: %d\n",file->d_name,i);
                fclose(log_file);
            } 
        }




    }
    closedir(dir);

printf("Finsihed search.\nDRS tool made by msmalik681.\n");

}


