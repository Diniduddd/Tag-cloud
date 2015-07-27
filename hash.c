#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "uthash.h"/* third party library*/




struct my_struct {
   char name[1000];		/* key */
    int id;                    
    
    UT_hash_handle hh;         /* makes this structure hashable */
};



struct my_struct * add_user(char *name,struct my_struct *users) {// for add new entry
    struct my_struct *s;

    HASH_FIND_STR(users, name, s);  /* check that name already in the hash */
    if (s==NULL) {
      s = (struct my_struct*)malloc(sizeof(struct my_struct));
        strncpy(s->name, name,1000);
        s->id =1;
        HASH_ADD_STR( users, name, s );
    }
    else{
    	s->id=s->id+1;
    }
    return users;
    
}

struct my_struct *find_user(char* name,struct my_struct *users) {/* find a entry*/
    struct my_struct *s;

    HASH_FIND_STR( users, name, s); /* s: output pointer */
    return s;
}

int fre_sort(struct my_struct *a, struct my_struct *b) {/* helping function for sort_by_fre*/
    return (a->id - b->id);
}
struct my_struct * sort_by_fre(struct my_struct *users) {/* for sort by frequency*/
    HASH_SORT(users, fre_sort);
    return users;
}
void print_all(struct my_struct *users){/* print all values*/
	
  struct my_struct *current_user, *tmp;

  HASH_ITER(hh, users, current_user, tmp) {
   
  printf("%s\t%d\n",current_user->name,current_user->id);
  }
  
}

struct my_struct * delete_user(char * name,struct my_struct *users){/* for delete a entry*/
	struct my_struct * s=NULL;
	s=find_user(name,users);
	if(s!=NULL){
	HASH_DEL(users,s);
	free(s);
	}
	
	return users;
}


struct my_struct * remv(FILE *fp,struct my_struct *users	){/* for remove stop words*/ 

	char token[356];
	
	
	while(fscanf(fp,"%s",token)>=1){
			
		users=delete_user(token,users);
	}
	

	return users;
}


struct my_struct * insert1(struct my_struct *users){/* insert word to hash table*/

	
	char s[256] = " \t\r\n,.?!;:-_\"()",str[1000000];
	char *token;
	
	while(fgets(str,1000000,stdin)!=NULL){
			

		char * ch1=malloc(sizeof(char)*1000);
		char * ch2=malloc(sizeof(char)*1000);
		token = strtok(str, s);
		
		if(token!=NULL){
			strcpy(ch1,token);
		
			while(1){
				int i=0;
				strcpy(ch1,token);
				
				while(ch1[i]){
					ch2[i]=tolower(ch1[i]);
					i++;
				}
				ch2[i]='\0';
				users=add_user(ch2,users);
		
			
				token = strtok(NULL, s);
				if(token==NULL)break;
			}
		
		}
	}
return users;
}

int main(int argc, char *argv[]){
    
   
   struct my_struct *users = NULL;
 	FILE *fp2;
	

	if (argc < 2)
	{
		perror("need a file to read: e.g. ./streams scores.txt");
		exit(1);
	}

	
	fp2 = fopen(argv[1], "r");
	if (fp2== NULL) 
	{
		perror(NULL);
		exit(1);	
	}
	
	users=insert1(users);
	
	users= remv(fp2,users);
	users=sort_by_fre(users);
	print_all(users);


	
   fclose(fp2);
  
   return(0);
}




