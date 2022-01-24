#include <stdlib.h>
#include <stdio.h>

#define BUCKET 10000

struct node {
  int data;
  struct node* next;
}node;


int hash(int key) {
  int num = key % BUCKET;

  if (num < 0) {
    num = num + BUCKET;
  }
  return num;
}

int dupCheck(struct node* ptr, int num) { // returns 0 if dup, 1 if not
  
  struct node* help = ptr;
  while (help!= NULL) {
    if (help->data == num) {
      return 1; // this a dup number
    }
    help = help->next; //keeps traversing
  }

  return 0; // didnt reach if
}

//______________________________________________________________________
struct node* insert(int num, int check, struct node* help) { // mods and inserts
  //int i = hash(num);
  //struct node* front = NULL;
  //printf ("yeooo \n");
  if (check == 0) { // index is null
    help = malloc(sizeof(struct node));
    help->data = num; 
    help->next = NULL;
    printf("inserted\n");
    return help;
  }

  return help;
  
 
}
//______________________________________________________________________
void search(int num, struct node* ptr) { // searches for number in HT 
  int check = 0;
  if (ptr == NULL) {
     printf("absent\n"); //shouldnt be null if has value
  } else if (ptr != NULL) {
    while (ptr != NULL) {
       if (ptr->data == num) {
	 check = 1;
	 printf("present\n");
	 break;
       }
       ptr = ptr->next;
    }
    if (check == 0) { // reached end of list
      printf("absent\n");
    }
  }
}


int main(int argc, char** argv) {

  struct node** hashy = (struct node**) malloc(sizeof(struct node*) * BUCKET);
  // struct node* front = NULL;

  if (argc != 2) {
    return 0;
  }

  FILE* fp = fopen(argv[1],"r"); // reads
  if (fp == NULL) {
    return 0;
  }

  char c;
  int num;

  int i;
  for (i = 0; i < BUCKET; i++) {
    hashy[i] = NULL;
  }

  for (i = 0; i < BUCKET; i++) {
    //printf(hashy[i]);
  }

  while(fscanf(fp, "%c \t %d \t", &c,&num) != EOF) {
    // int x = hash(num);
    if (c == 'i') { // insert in hashtable
      //printf("%c\t%d\n",c,num);
      int key = hash(num);
      int check = 0; // null at index

      if (hashy[key] == NULL) {
	struct node* received = NULL;//= insert(num,check);
	hashy[key] = insert(num,check,received);
      } else if (hashy[key] != NULL) {
        check = 1;
	struct node* ptr = NULL;
	ptr = hashy[key];
	// dup check
	if (dupCheck(ptr,num) == 1) { // has dup
	  printf("duplicate\n");
	} else {
	  while (ptr->next != NULL) {
	    ptr = ptr-> next;
	  }
	  struct node* rabeya = malloc(sizeof(struct node));
	  rabeya->data = num;
	  ptr->next = rabeya;
	  rabeya->next = NULL;
	  printf("inserted\n");
	}
      }
    } //__________________________________________________________________
      else if (c == 's') {
	int key = hash(num);
	struct node* ptr = hashy[key];
	search(num,ptr);
      } 
  }

  return 0;					     
}
