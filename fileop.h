#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>


	char username[100];
	int beg, end, hasheven, hashodd, i = 1, val1 = 0;
   
int direc(char dirname[])
	{

    	mkdir((dirname),0700);
    	printf("Directory created with name: %s",dirname);
	}


void getusername(char string[])
	{
	strcpy(username , string);
	printf("%s\n" , username);
	}

int tiime()
	{
        time_t t = time(NULL);
        struct tm time_struct;
        time_struct = *localtime(&t);

        printf("Today : %d-%d-%d %d:%d:%d\n",time_struct.tm_mday, 		  time_struct.tm_mon + 1, time_struct.tm_year + 1900, 			  time_struct.tm_hour, time_struct.tm_min, time_struct.tm_sec);
	    return 0;
	}


int chdirec(char dirname[])
	{

	printf("Present working directory is: %s",dirname);
	
	}

int parentdirec()
	{
	   
	system("cd .. && ls" );
	    
	}

int fil(char filename[])
	{
   
	FILE *fp=fopen(("%s",filename),"w");
	fclose(fp);
	}

int searchdir(char sname[])
	{
  
            struct dirent *de;
             DIR *dr=opendir(sname);
            if(dr == NULL)
   	    {
       
     		printf("couldn't open current directory");
    	
   	     }

          while ((de = readdir(dr)) != NULL)
    	  {
                printf("%s\n", de->d_name);
      
     	  }
             closedir(dr);

	}
void dir_delete()
{   
      	        char dirname[200];    
	        char temp[200];
                scanf("%s",dirname);
                sprintf(temp,"rm -rf %s",dirname);
    //printf("%s",temp);
	            system(temp);
		system("ls");
}
void file_content()
{
        char filname[200];
        char temp2[200];
        scanf("%s",filname);
        sprintf(temp2,"cat %s",filname);
        system(temp2);
}

int decrypt(int val1,int hasheven,int hashodd,char username[],char msg[],char filname[])
 {
	  beg = username[0];
	    end = username[(strlen(username) - 1)];
	    hasheven = (beg + end) / 100;
	    hashodd = (beg + end) / 50;
        for (val1 = 0; val1 < (strlen(username)); val1++)
	 {
                if (val1 % 2 == 0) 
		{
               		 msg[val1] = msg[val1] - hasheven;
                	printf("%c", msg[val1]);
           	 }
		 else 
		{

	                msg[val1] =msg[val1] - hashodd;
	               printf("%c", msg[val1]);
	        }
	  }
	printf("\n");

 }

void read_file()
{
	 char c;
	 char msg[100];
         char filname[200];

        printf("enter filename");
        scanf("%s\t",filname);
        FILE *ft;   
        ft=fopen(("%s",filname),"r");
        
        if(ft==NULL)
        { 
	    printf("no file");
            exit(1);
        }

        else 
	{
	       int i=0;
	            c=fgetc(ft);
	            while(c!=EOF)
		   {
			msg[i]=c;
			 c=fgetc(ft);
			i++;
            	   }
		 
		decrypt(val1,hasheven,hashodd,username,msg,filname);
		fclose(ft);
	}
}
int encrypt(int val1,int hasheven,int hashodd,char username[], char msg[],char filname[]) 
{
	    beg = username[0];
	    end = username[(strlen(username) - 1)];
	    hasheven = (beg + end) / 100;
	    hashodd = (beg + end) / 50;
            for (val1 = 0; val1 < (strlen(msg)); val1++)
	     {
           	 if (val1 % 2 == 0) 
		{
	                msg[val1] = msg[val1] + hasheven;
	        }
		 else
		 {
                	msg[val1] = msg[val1] + hashodd;
              	 }
    	     }
		FILE *fo;
		fo=fopen(("%s",filname),"r+");
		
			fprintf(fo,"%s",msg);
			fclose(fo);
			
}




void write_to_file()
{
        char filname[200];
        char input[100];   
        printf("Enter filename");
        scanf("%s\t",filname);
        printf("Enter text to be written");
        getc(stdin);
        gets(input);
        
        FILE *fp;
        fp=fopen(("%s",filname),"w");
       
       
        if(fp==NULL)
        {
                         printf("Oops ! file not found");
        }
        else
        {     
                    fprintf(fp, "%s",input);
        }
	
        fclose(fp);
	encrypt( val1, hasheven,hashodd,username,input,filname);
	

}

int mainheader()
{

    int a;
    char dirname[200];
    char filname[200];
    char input[1000];
    char c;
    char msg[1000];
    while(1)
    {
    printf("1.Name of the owner\n");
    printf("2.Create directory \n");
    printf("3.Create File \n");
    printf("4.Search Directory \n");
    printf("5.List Directories \n");
    printf("6.Remove Directory\n");
    printf("7.Enter to view the file\n");
    printf("8.Enter to view current time\n");
    printf("9.Write in a file\n");
    printf("10.Read from a file\n");
    printf("11.Exit\n");
    scanf("%d",&a);

     switch (a) {
            
	    case 1:
		printf("Name of the owner is:\n");
		system("whoami");
		break;

	    case 2:

                printf("Enter directory name");
       		scanf("%s",dirname);
                direc(dirname);
                break;

            case 3:

                printf("Enter file name");
               
 		scanf("%s",filname);
                fil(filname);
                break;

            case 4:
                printf("Enter directory or file name to search");
               
                scanf("%s",dirname);
		searchdir(dirname);
                break;

            case 5:
                system("ls");
                break;

           
	    case 6:
                printf("Enter a directory name to be deleted");
        	dir_delete();
                break;

	    case 7:
		 printf("Enter a filename you need to see content of");
      		 file_content();
		 break;        

	    case 8:
		printf("The time is:");
		tiime();
		break;

	   case 9:
		     
		write_to_file();
		break;


        	case 10:

		read_file();	
       		break;

		case 11:
			exit(1);
			break;
		default:
			printf("No option matched!\n");
			break;

    }
   }
}
