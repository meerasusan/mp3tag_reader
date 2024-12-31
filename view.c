/*
NAME : MEERA SUSAN TOMMY
PROJECT : MP3 TAG READER 
CONTENTS : 1. VIEW()
		   2. PRINT()
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"main.h"
char *frame_id[6]={"TIT2","TPE1","TALB","TYER","TCON","COMM"};
char f_data[6][50];
int view(char *fname)
{
	FILE *fptr = fopen(fname,"r");//file opened in read mode
	if(fptr == NULL)//fptr -> NULL
	{
		printf("ERROR : file did not open\n");
		return 0;
	}
	fseek(fptr,10,SEEK_SET);// moving the curser 10 positions after the header
	unsigned char tag[5],size[5];
	for(int i=0;i<6;i++)
	{
		fread(tag,sizeof(unsigned char),4,fptr);
		tag[4] = '\0';
		if(!strcmp(tag,frame_id[i]))//tag & frame_id match
		{
			fread(size,sizeof(unsigned char),4,fptr);//reading size
			size[4]='\0';
			int sz = (size[0]<<24) | (size[1]<<16) | (size[2]<<8) | (size[3]);//tag size is stored in big indian -> convert to little endian
			char data[sz];
			fseek(fptr,3,SEEK_CUR);//traversing throung flag-> 3 bytes
			fread(data,sizeof(char),sz-1,fptr);//reading contents
			data[sz-1]='\0';
			strcpy(f_data[i],data);//storing each data to an array
		}
	}
	print();//print details
	fclose(fptr);//file closed

}
void print()
{
	printf("\n-------------------------------VIEW DETAILS-------------------------------\n\n");
	printf("--------------------------------------------------------------------------\n");
	printf("TITLE     :\t%s\n",f_data[0]);
	printf("ARTIST    :\t%s\n",f_data[1]);
	printf("ALBUM     :\t%s\n",f_data[2]);
	printf("YEAR      :\t%s\n",f_data[3]);
	printf("MUSIC     :\t%s\n",f_data[4]);
	printf("COMMENT   :\t%s\n",f_data[5]);
	printf("--------------------------------------------------------------------------\n");
}

