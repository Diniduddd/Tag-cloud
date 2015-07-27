#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/wait.h>

int main(int argc, char *argv[]){ // the argv[1] should be the file containing the paths and argv[2]should be the file contain the stop words
	if (argc < 3)
	{
		perror("need a file to read: e.g. ./streams scores.txt");
		exit(1);
	}

	FILE *fp2;
	fp2 = fopen(argv[1], "r"); //open the file containing the paths
	if (fp2== NULL) 
	{
		perror(NULL);
		exit(1);	
	}
	
	char str[1000000];
	
	
	
	
	int mfriin[2],mfriout[2]; // pipe for the globle word frequncy counter
		
		if(pipe(mfriin))
		{
		perror("Create pipe");

			}
		if(pipe(mfriout))
		{
		perror("Create pipe");

			}
		
		pid_t pid = fork();
		if(pid==0){			// the globle word frequncy counter
			close(mfriin[1]);
			close(mfriout[0]);
			
			dup2(mfriin[0],0);
			dup2(mfriout[1],1);
			
			close(mfriin[0]);
			close(mfriout[1]);
			
			execl("mainadd", "mainadd",  NULL);
			
			
		}
	
	
	while(fgets(str,1000000,fp2)!=NULL){
		str[strlen(str)-1]='\0';
		int mainp[2]; // pipe for communicate between the pipe from derectry processes and globle frequncy counter 
		
		if(pipe(mainp))
		{
		perror("Create pipe");
		return -1;
			}
		
		pid_t pid = fork();
		
		if(pid==0){ // the derectry process or the proceses created for once a derectry
			int tagrim[2],friin[2],friout[2];
			
			
		if(pipe(tagrim))// for get output from process which remove tags
		{
		perror("Create pipe");
		
			}
		if(pipe(friin))  // for give input from derectry word frequncy counters
		{
		perror("Create pipe");
		
			}
		if(pipe(friout))	 // for get output from derectry word frequncy counters
		{
		perror("Create pipe");
		
			}
			
			
		pid=fork();
		
		if(pid==0){ // process which remove html tags 
			close(tagrim[0]);
			
			dup2(tagrim[1],1);
			
			close(tagrim[1]);
			char s1[500]="awk \'/<body/{p=1; s=$0} p && /<\\/body>/{print $0 FS s; s=\"\"; p=0} p\' ";
			char s2[500]=" | sed \'s/<[^>]*>//g\' | sed \'s/\\&[^;]*;//g\'";
			char s3[50]="/*.html";
			strcat(s1,str);
			strcat(s1,s3);
			strcat(s1,s2);
	
			//perror(s1);
	
			execl("/bin/sh","sh","-c",s1,NULL);	
		
		
		
		
		}
		
		pid=fork();
		
		if(pid>0){ // connect the pipe lines
			close(tagrim[1]);
			close(friin[0]);
			close(friout[1]);
			dup2(friin[1],tagrim[0]);
			close(friin[1]);
			
			dup2(friout[0],mainp[1]);
			
			close(friout[0]);
			
		}
		
		if(pid==0){ //process for count word frequncy for one derecry
			close(friin[1]);
			close(friout[0]);
			
			
			dup2(friin[0],0);
			dup2(friout[1],1);
			
			close(friin[0]);
			close(friout[1]);
			
			execl("hash", "hash", argv[2], NULL);
		}
			
	return 0;	// end of processes for a derectry
	}
	
	if(pid>0){//connect globle frequncy counter with sub frequncy counters
		
		dup2(mainp[0],mfriin[1]);
		
	}	
		
	}
	
	wait(0);// wait untill over ever every entry
	int png[2];
	if(pipe(png))// for comunicate with programme which create the png file
		{
		perror("Create pipe");
		return -1;
			}
	pid=fork();
	if(pid==0){ // process which create the png file
		close(png[1]);
		dup2(png[0],0);
		close(png[0]);
		execl("size", "size", argv[2], NULL);
	
	}
	if(pid>0){
		close(png[0]);
		dup2(png[1],mfriout[0]);
		close(png[1]);
	}
	
	return 0;
}
