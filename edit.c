/*
NAME : MEERA SUSAN TOMMY
PROJECT : MP3 TAG READER
CONTENTS : 1. EDIT()
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"main.h"
char *f_id[]={"TIT2","TPE1","TALB","TYER","TCON","COMM"};
char *content[]={"TITLE","ARTIST","ALBUM","YEAR","MUSIC","COMMENT"};
char *cla[] = {"-t","-a","-A","-y","-m","-c"};
int edit(char *fname,char *arg,char *e_info)
{
	FILE *fptr = fopen(fname,"r+");//file opened in read+write mode
	if(!fptr)// if fptr = NULL
	{
		printf("ERROR : EDIT MODE : file cannot be opened");
		return 0;
	}	
	fseek(fptr,10,SEEK_SET);// moving past the header
	unsigned char size[5],tag[5];
	for(int i=0;i<6;i++)// find the match
	{
		if(!strcmp(arg,cla[i]))//-t/-a/..../-c
		{
			fread(tag,sizeof(unsigned char),4,fptr);// read tag
			tag[4] = '\0';
			if(!strcmp(tag,f_id[i]))//if tags match with position
			{
				fread(size,sizeof(unsigned char),4,fptr);
				size[4]='\0';
				int sz = (size[0]<<24) | (size[1]<<16) | (size[2]<<8) | (size[3]);//tag size is stored in big indian -> convert to little endian
				char data[sz];

				strcpy(data,e_info);//copied i/p string to data
				fseek(fptr,3,SEEK_CUR);// 3 bytes flag -> avoiding
				fwrite(data,sizeof(char),sz-1,fptr);//write data to file.mp3
				printf("\n-----------------------------EDIT DETAILS------------------------------\n\n");
				printf("\n--------------------------CHANGE THE %s--------------------------\n\n",content[i]);
				printf("%s\t  : %s",content[i],e_info);
				printf("\n\n-----------------------%s CHANGED SUCCESSFULLY--------------------------\n",content[i]);
			}
			fclose(fptr);//close file pointer
			return 1;//return success
		}
		else  //if no match with arg -> traversing through file
		{
			fseek(fptr,4,SEEK_CUR);//traversing tag -> 4 bytes
			fread(size,sizeof(unsigned char),4,fptr);// checking size 
			size[4]='\0';
			int sz = (size[0]<<24) | (size[1]<<16) | (size[2]<<8) | (size[3]);//tag size is stored in big indian -> convert to little endian
			fseek(fptr,3,SEEK_CUR);//traversing flag
			fseek(fptr,sz-1,SEEK_CUR);// traversing content according to size
		}
	}
}

