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



struct my_struct * add_user(char *name,struct my_struct *users,int freq) {// for add new entry
    struct my_struct *s;

    HASH_FIND_STR(users, name, s);  /* check that name already in the hash */
    if (s==NULL) {
      s = (struct my_struct*)malloc(sizeof(struct my_struct));
        strncpy(s->name, name,1000);
        s->id =freq;
        HASH_ADD_STR( users, name, s );
    }
    else{
    	s->id=s->id+freq;
    }
    return users;
    
}

struct my_struct *find_user(char* name,struct my_struct *users) {/* find a entry*/
    struct my_struct *s;

    HASH_FIND_STR( users, name, s); /* s: output pointer */
    return s;
}

int fre_sort(struct my_struct *a, struct my_struct *b) {/* helping function for sort_by_fre*/
    return ( b->id - a->id );
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

	
	char str[256];
	int freq;
	
	while(scanf("%s\t%d",str,&freq)==2){
	
		users=add_user(str,users,freq);
			
	}
	users=sort_by_fre(users);
	print_all(users);
return users;
}

int main(){
	
	struct my_struct *users = NULL;
	users=insert1(users);
	
	return 0;
	}
