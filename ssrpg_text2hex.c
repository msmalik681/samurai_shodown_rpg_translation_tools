#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define MAX_CHAR 1024

char *GetFile(char *file, char *input) {
    // open file
    char buff[6];
    FILE *fp = fopen( file, "r");
    int len = 20;
    // need malloc memory for line, if not, segmentation fault error will occurred.
    char *line = malloc(sizeof(char) * len);
    // check if file exist (and you can open it) or not
    if (fp == NULL) {
        printf("can open file !");
        return 0;
    }
    while(fgets(line, len, fp) != NULL) {
       if (strstr(line, input) != NULL) {
       	memcpy(buff, line , 4);
        char *out = malloc(5);
        out[0] = buff[0];
        out[1] = buff[1];
        out[2] = buff[2];
        out[3] = buff[3];
        out[4] = '\0';

       	free(line);
        return out;
	}
    }
    free(line);
    printf("error: no output for \"%s\"\n",input);
    exit(0);
}

int main(int argc, char *argv[])
{// msmalik681 tool to covert a string to hex values for samurai shodown RPG on the neo geo CD.

    char temp[5];
    strcpy(temp, strrchr(argv[1], '.') );
    if ( access(argv[1], F_OK) != 0 || strcasecmp(temp,".tbl") != 0 )  {
    printf("Error: Table file missing\nExample usage: ./ssrpg_text2hex ssrpg_table.tbl\nTool made by Msmalik681!\n");
    exit(0);
    }

	char input[MAX_CHAR];
    char output[MAX_CHAR]= "";
    char buff[3];
    int i =0;
    
    printf("Enter string to search: ");
    scanf("%s",input);

    while( strlen(input)%2 == 1 )
    {
    printf("Error: String must be a even number try again!:\n");
    printf("Enter string to search: ");
    scanf("%s",input);
    }


    for(i=i;i<strlen(input);i=i+2)
    {
        sprintf(buff,"%c%c",input[i],input[i+1]);
        if(!output){
            strcpy(output,GetFile(argv[1], buff));
        } else {
        strcat(output,GetFile(argv[1], buff));
        }
    }

    printf("Hex output: %s\nTool made by Msmalik681!\n",output);
	return 0;
}


    /*//file write a byte function

    unsigned char a=0x0F; //single byte value 15
    FILE *fp;   //file pointer

    fp = fopen("test.bin", "wb"); //open a file and set to pointer

    if(fp == NULL)
    {//error handling 
        printf("Error opening file\n");
        exit(1);
    }

    fwrite(&a, 1, 1, fp); //write 1 byte
    printf("1 byte written!\n"); //confirm finished 

    fclose(fp); //close the handeled file
    return 0;

    */