#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include "fileop.h"
#include "md5.h"

int main(void)
{
	int flag,c,x;
	flag=0;
		
	char *qwerty=malloc(sizeof(char)*33);
	char buffer[1024] ;
	char *record,*line,*fuser,*fpass,*temp;
	char str[200],string[512],var[200];

	FILE *file;
	file= fopen("md5.txt","r+");
	

	FILE *fd = fopen("data.csv", "r+");
	if (fd == NULL) 
	{
	    printf("Failed to open file\n");
	    return -1;
	}

	printf("Enter the username:\t ");
	scanf("%s",string);
	printf("Enter the password:\t ");
	scanf("%s",str);
	
	md5encryption(str);
	
	file=fopen("md5.txt","r");
	x=0;		
	if(file){
    		while ((c = getc(file)) != EOF){
			qwerty[x]=c;
			x++;
		}
		qwerty[32]='\0';
	}

	sprintf(str,"%s",qwerty);

	while((line=fgets(buffer,sizeof(buffer),fd))!=NULL)
	{
	     fuser = strtok(line,",");
	     fpass = strtok(NULL,",");    
	     if((strcmp(fuser,string)==0) && (strcmp(fpass,str)==0))
	     {
			flag=1;
			break;
	     }
	     else if((strcmp(fuser,string)==0) && (strcmp(fpass,str)!=0))
	     {

			flag=2;         
			break;
	     }

	 }
	 if(flag==1){
	
		printf("Welcome to Project-1\n");
	 	printf("Directory created with name:  %s\n",string);
		getusername(string);
		mainheader();
	}
	else if(flag==2)
	{
		printf("Wrong password ");
	}

	else
	{
		printf("New username found\n");
		printf("Enter new Username:\t");
		scanf("%s",string);
		printf("Enter new Password:\t");
		scanf("%s",str);
		md5encryption(str);
		file=fopen("md5.txt","r");
		x=0;		
		if (file) {
    			while ((c = getc(file)) != EOF){
				qwerty[x]=c;
				x++;
			}	
			qwerty[32]='\0';
		}
		
		sprintf(temp,"%s,%s,\n",string,qwerty);
		fputs(temp,fd);
		printf("Directory created with name :\t %s",string);
		printf("\n");
		mkdir(("%s",string),0700);
		system("ls");
	}
	return 0;
}
