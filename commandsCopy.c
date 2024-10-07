#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>




//This array store all open file to close it in exit function		
int file[155];
int in=0;

//This help function print all command an how to use it 
void help(){
	
	printf("ls: List all file/directory in current remote directory\n");
	printf("ls dir1: List all file/directiry for dir1 or specifec directory\n");
	printf("ls *.c : List all .c text files\n");
	printf("cat: print all content of text file in screen\n");
	printf("cat *.txt: print all .txt text files in screen\n");
	printf("exit: Close all open files then quit the program\n");
}

void ls(char *a){

	char str[100];
	int i=0;
	int num=0;
	char *p;
	char m[100];
	int f=0;

	//This part check if there is directory list it otherwise list a current directory also add checking error
	if(*a==0){
		int check=0;
		 DIR *d;
       		 struct dirent *de;
             		 d=opendir(".");
			if(d==0){
				printf("Faild of open directory\n");
			}else{

               			 while(de=readdir(d)){
                       			 printf("%s\n",de->d_name);
                		}
			}
	}else{
		
		 DIR *d;
                 struct dirent *de;
                         d=opendir(a);
                         if(d==0){
                                printf("Faild of open directory\n");
                        }else{

                                 while(de=readdir(d)){
                                         printf("%s\n",de->d_name);
                                }
                        }
	}
}
void cat(char *a){
	
	int  fd;
	int s=0;
	char buf[100];

	//open the file and read content 
	fd=open(a,O_RDONLY);
	
	//store the file into aray for close it in exit function 
	file[in]=fd;
	in++;
	
//This part check if file is opened thant read content and print it into screen otherwise print error masage
        if(fd!=-1){
		
		while(s=read(fd,buf,sizeof(buf)-1) > 0){
			if('a'<*buf<'z'){
				printf("%s",buf);
			}
		}
		printf("\n");
	}else{
		printf("%s: No such file or directory.\n",a);
	}

}

void exist(){
	int i=0;
	int check=0;
	//This while loop close all file ussing aray which open it into cat function 
	while(file[i]!=0){
			
		check=close(file[i]);
		

		i++;
	}

	printf("Exitting...\n");
	exit(1);
}
