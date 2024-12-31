/*
NAME : MEERA SUSAN TOMMY
DISCRIPTION : MP3 PROJECT
CONTENTS : 
MAIN()
ERROR_USAGE()
VALIDATION()
 */
#include<stdio.h>
#include<string.h>
#include"main.h"
int main(int argc,char *argv[])
{
	if(argc == 1)//when no CLAs passed
	{
		error_usage();//prints error & ussage message
		return 0;
	}
	if(argc == 2)//when there is one arg
	{
		if(strcmp(argv[1],"--help")==0)//& it is help
		{
			printf("---------------------------------------------------------HELP MENU---------------------------------------------------------\n\n");
			printf("1. -v -> to view mp3 file contents\n2. -e -> to edit mp3 file contents\n\t2.1. -t -> to edit song title\n\t2.2. -a -> to edit arrtist name\n\t2.3. -A -> to edit album name\n\t2.4. -y -> to edit year\n\t2.5. -m -> to edit content\n\t2.6. -c -> to edit comment\n\n");
			printf("--------------------------------------------------------------------------------------------------------------------------\n\n");
		}
		else
			error_usage();//if not help : prints error msg
	}

	if(argc == 3)//if 2 arguments
	{
		if(strcmp(argv[1],"-v")==0)// view agument passed correctly
		{
			if(validation(argv[2]))
				view(argv[2]);
		}
		else         //wrong argument
			error_usage();
	}

	if(argc == 5)//if 3 arguments
	{
		if(strcmp(argv[1],"-e")==0)// edit
		{
			if(!strcmp(argv[2],"-t") || !strcmp(argv[2],"-a") || !strcmp(argv[2],"-A") || !strcmp(argv[2],"-y") || !strcmp(argv[2],"-m") || !strcmp(argv[2],"-c"))
			{
				if(validation(argv[4]))//if validation completed
					edit(argv[4],argv[2],argv[3]);
			}
			else// wrong 2nd argument ussage
				error_usage();
		}
		else// wrong 1st argument usage
			error_usage();
	}

	return 0;
}
void error_usage()
{
	printf("--------------------------------------------------------------------------------------------------------------------------\n\n");
	printf("ERROR :  ./a.out : INVALID ARGUMENTS\nUSAGE :\nTo view please pass like: ./a.out -v mp3filename\nTo edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\nTo get help pass like: ./a.out --help\n");
	printf("--------------------------------------------------------------------------------------------------------------------------\n\n");
}

int validation(char *file_name)
{
	if(strstr(file_name,".mp3")==0)
	{
		printf("ERROR: The file is not mp3\n");
		return 0;
	}

	FILE *fptr = fopen(file_name,"r");//file openned in read mode to validate
	if(!fptr)//file not openned
	{
		printf("ERROR : MP3 file was not able to open\n");
		return 0;
	}
	char buffer[5];
	fread(buffer,1,3,fptr);//to get first 3bytes "ID3"
	if(strcmp(buffer,"ID3")==0)// if file is ID3
	{
		printf("INFO: Tag is ID3\n");
	}
	else //if not ID3
	{
		printf("ERROR : Tag not IDE\n");
		return 0;
	}
	char ver;
	fread(&ver,sizeof(char),1,fptr);//Get the version
	printf("INFO : version is 2.%c\n",ver + '0');
	fclose(fptr);//file closed
	return 1;
}

