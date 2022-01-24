#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <math.h>
//SUBMIT
long HITS = 0;
long MISS = 0;
long WRITE = 0;
long READ = 0;

// int items



struct cache { // kinda like a hashmap in a way
  int valid;
  int* tag;
  int* block;
  int age;
//  struct cache*front;
  //struct cache*rear;
  struct cache*next;
};

struct node {
  int data;
  // int v;
  // int t;
  // int b;
  struct node * next;
}node;

int numC(long num) { // counts number in a number

  unsigned long temp = num;
  int count = 0;

  while (temp!= 0) {
    temp/=10;
    count++;
  }
  return count;

}

void reverse(struct node** head) {
  if (*head == NULL) {return;}

  struct node* prev = NULL;
  struct node* curr = *head;
  struct node* help = NULL;

  while (curr!= NULL) {
    help = curr->next;
    curr->next = prev;
    prev = curr;
    curr = help;
  }
  *head = prev;

}

int* binaryConverter(unsigned long num) { // node bc unknown number of binarys
  // keep modding and adding to array
  struct node* head = (struct node*)malloc(sizeof(struct node));
  head->data = -1;
  struct node* ptr = head;
  int i;
  int count = 0;

  //printf("here\n");
  // int size = numC(num);

  unsigned long temp =num;
  int mod;

  //  printf("hereee\n");

  //for(i = 0; i < size; i++) {

  while (temp!=0) {
    //   if (temp <=0) {break;}
    struct node* temper = (struct node*)malloc(sizeof(struct node));
      mod = temp%2;
      temp/=2;
      if (head->data == -1) {
	       head->data = mod;
      } else {
	       temper->data = mod;
	       ptr->next = temper;
	        ptr = ptr->next;
      }
  }

  reverse(&head);

  ptr = head;

  while(ptr != NULL) {
    count++;
    //  printf("%d",ptr->data);
    ptr = ptr->next;
  }

  //printf("\n\n");

  count = 48 - count;
  // printf("\ncount %d\n",count);
  ptr = head;

  int *arr = (int*)malloc(sizeof(arr) * 48);

  for (i = 0; i < count; i++) { // fills with 0 in front
    arr[i] = 0;
  }

  for (i = count; i < 48; i++) {
    while (ptr != NULL) {
      arr[i] = ptr->data;
      ptr = ptr->next;
      break;
    }
    //   printf("%d",arr[i]);
  }


  for (i = 0; i < 48; i++) { // fills with 0 in front
    //  printf("%d",arr[i]);
  }

  // printf("\n");

  return arr;

}

int letterConverter(char x) { // this methos is if letter in address
  // gets hex value of number
  //printf ("here: %c\n",x);
  if (x == 'a' || x == 'A') { return 10; }
  if (x == 'b' || x == 'B') { return 11; }
  if (x == 'c' || x == 'C') { return 12; }
  if (x == 'd' || x == 'D') { return 13; }
  if (x == 'e' || x == 'E') { return 14; }
  if (x == 'f' || x == 'F') { return 15; }

  return 0;
}


unsigned long exponentiate(long x, long y) {
  long i;
  long j = 1;

  for (i = 0; i < y; i++) {
    j *= x;
  }

  return(j);

}

int btod(int* arr, int size) {
  int i;
  int j = 0;
  int ret = 0;


  for (i = size-1; i>=0; i--) {
    //  printf("%d\t",i);
    ret += arr[i]*(exponentiate(2,j));
    j++;
  }
  // printf("%d\n",ret);
  return ret;
}


unsigned long converter(char* x) { // converts address to number and then converts number to binary
  // for example, A is 10, B is 11, C is 12 base 16 starting from right
  int arrsize = 0;
  int i;

  while (x[arrsize] != '\0') {
    arrsize++;
  }

  char * array = (char*)malloc(sizeof(char) * arrsize);
  // i need a backwards loop to allocate char in arr
  for (i = 0; i <arrsize; i++) { // allocates forward
    array[i] = x[i];
  }


  for (i = 0; i <arrsize; i++) { // prints forward
    //   printf("%c\t",array[i]);
  }

  // printf("\n");

  //backwards array
  int j = 0;
  char * back = (char*)malloc(sizeof(char) * arrsize);
  for (i = arrsize-1; i >= 0; i--) { // allocates forward
    back[i] = array[j];
    j++;
  }

  int val;

  for (i = 0; i <arrsize; i++) { // converts each char to int back
    //  printf("%c\t",back[i]);
    // method for letters a-f
    if ((back[i] >= 'a' && back[i] <= 'z') || (back[i] >= 'A' && back[i] <= 'Z')) {
      // printf("here: %c\n",back[i]);
      val = letterConverter(back[i]);
    } else {
      val = (int)(back[i] -'0');
    }
    // printf ("%lu\t", val);
    back[i] = val;
  }


  for (i = 0; i <arrsize; i++) { // prints forward
    //printf("%d\t",back[i]);
  }

  //printf("\n");
  unsigned long ret = 0;

  for (i = 0; i < arrsize; i++) {
    ret += (back[i])*exponentiate(16,i); // gets full decimal value
    // printf ("here %lu\n",ret);
  }
  //i need loop to convert


  return ret;
  // i need a loop here to exponentiate by 16

  // printf("arrsize: %d\n",arrsize);

  return 0;


}

int binaryC(int val) { //converts kb to binary
  //1 kb is 1024 bytes
  val*=1024;
  return val;
}

int logX(int x) {
  // for offset
  int i;
  for (i = 0; i < x; i++) {
    if ((x>>i) == 1) {
      break;
    }
  }

 return i;
}

int getBit(int csize, int bsize, int check, int prop) { // if check = 1 tag, check = 2 set, check = 3 oofset

  int num1 = csize;
  int num2 = bsize;
  //num1 = binaryC(csize);
  // printf("cache %d\n",num1);

  int lines = num1/num2;
  int temp = lines;

  int count = 0;
  while (temp != 1) { // this is to find exponent
    temp/=2;
    count++; // count has exponent
  }

  int bit;
  // depending on assoc num decides set bits
  if (check == 1) { // return number of bits in tag
    //tag = address size - exponent of set - offset bits
    int offset = logX(bsize);

    bit = 48 - prop - offset;
    // printf ("%d\n",bit);
    return bit;
  } else if (check == 2) { // set index bits
    // get lines first, if assoc has value, work with that
    int temp = num1/(bsize*prop);

    bit = logX(temp);
    // printf("temp %d\n",bit);
    // printf("baby: %d\n",temp);
    return bit;
    // run a counter??
    //log2(block/assoc)
  } else if (check == 3) { // offset bits (shoutout cardi)
    // log_2(blocksize)
    bit = logX(bsize);
    return bit;
  }

  // these should all add up to 48

  return 0;

}


struct cache*insert(struct cache*help,int*tag,int*block) { // shoud be baby[i]
  // valid tag wil always be set

  help = malloc(sizeof(struct cache));
  help->valid = 1;
  help->tag = tag;
  help->block = block;
  help->next = NULL;
  return help;
}

struct cache* fifo(struct cache* temp) { // swaps
  struct cache* ptr = temp;
  struct cache* prev = NULL;
  while (ptr->next != NULL) {
    ptr->valid = ptr->next->valid;
    ptr->tag = ptr->next->tag;
    ptr->block = ptr->next->block;
    prev = ptr;
    ptr = ptr->next;
  }
  return prev;
}

void printArray(int*arr,int x) {
  //printf("\nArray\n");
  int i;
  for(i=0;i<x;i++) {
    printf("%d",arr[i]);
  }
  printf("\n");

}

int cmpArray(int*a,int*b,int size) {
  // return 1 if the same, 0 if not
  int i;

//  printf("\nTag in cache: ");
  for(i = 0; i < size;i++) {
    //eturn 0;
  //  printf("%d",a[i]);

  }
  //printf("\nAddress Tag: ");
  for(i = 0; i < size;i++) {
    //eturn 0;
    //printf("%d",b[i]);

  }

//  int i;
  for(i = 0; i < size;i++) {
    if(a[i] != b[i]) { // tag doesnt match, MISS
      return 0;
    }
  }
  return 1;
}

void removeOldest(struct cache* head) {// goes through baby[key], finds oldest and removes

// I NEED A LOOP THAT GOES THROUGH AND COMPARES PTR AND PTR->NEXT AGE,
//IF NEXT AGE IS GREATER STORE IN TMP VARIABLE, AFTER YOU FINS OLDEST age
// START AGAIN, IF TMP MATCHES ANY AGE, REMOVE
struct cache* ptr = head;
int oldest;
while (ptr->next!=NULL) {
  if (ptr->age>ptr->next->age) {
    oldest = ptr->age;
  } else {
    oldest = ptr->next->age;
  }
  ptr= ptr->next;
}
struct cache*prev= NULL;
while (ptr->next!=NULL) {
  if (head->age == oldest) {
    struct cache*tmp = head;
    head = head->next;
    free(tmp);
  } else if (ptr->next == NULL) { // last cache
    prev->next = NULL;
    ptr = ptr->next;
  } else { // in btwn

    prev = ptr->next;
  }
  prev = ptr;
  ptr = ptr->next;
}
//if(oldest==1) {}
//printf("%d\n",oldest );


}

// FOR LRU, GO THROUGH HT AND FIND

void incrAge(struct cache* ager)  { // increments age in givien set when not nule
//printf("%s\n","here" );
  struct cache*ptr = ager;
//   printf("cache age %d\n",ptr->age);
  while(ptr!= NULL) {
    ptr->age++;
  //  printf("cache age %d\n",ptr->age);
    ptr = ptr->next;
  }
}

void read(struct cache** baby,int*tag,int*block,int tagsize,int key,int assoc,int lines,char*policy) {
// given baby and key
  struct cache*ptr = baby[key];
  struct cache*prev = NULL;
  //struct cache*help = baby[key];

  int count = 0;
  //int b = 0;
  while(ptr!=NULL) {
    int pp = cmpArray(ptr->tag,tag,tagsize);
    //printf("YERRRRR: %d\n",pp);

    if (pp == 1) {
      HITS++;
      return;
    }
  //  prev = ptr;
    prev = ptr;
    ptr = ptr->next;
  //  count++;
  }
  if (prev!=NULL) {}

  MISS++;
  READ++;
// ptr is null

  // printf("Count: %d\n",count );
  // PTR IS AT LAST NODE, EVIC HEAD
  // IN NEED A COUNTER TO ONLY EVEICT IF REACHES ASSOC:X
  //struct cache * tmp = baby[key];
  struct cache *help= insert(ptr,tag,block);
  help->age = 1;
  //incrAge(baby[key]);

  if (assoc>1 && assoc != lines) { //assoc:X
    if (baby[key]== NULL) {
      //printf("%s\n","here" );
      baby[key] = help;
      incrAge(baby[key]);
    } else if (baby[key]!= NULL){
      struct cache* bee = baby[key];
      while(bee->next!= NULL ) {
      //  printf("%s\n","hereeeeee" );
        bee = bee->next;
        count++;
        if (count == assoc-1 && (strcmp("fifo",policy)== 0)) { // evict, FIFO
          struct cache*tmp = baby[key];
          baby[key] = baby[key]->next;
          free(tmp);
        //  break;
        } else if (count == assoc-1 && (strcmp("lru",policy)== 0)) {
          // REMOVE OLDEST
          struct cache* head= baby[key];
          struct cache* ptr = baby[key];

          while(ptr->next!=NULL) { // turns into CLL
            ptr = ptr->next;
          }
      //  struct cache* tail = ptr;
          ptr->next = head;

          int oldest;
          struct cache*help = head;
        //  struct cache*prev = NULL;
          while (help->next != head) { //end of CLL
            if (help->age > help->next->age) {
              oldest = help->age;
            } else if (help->age < help->next->age) {
              oldest = help->next->age;
            }
            help = help->next;
          }

          struct cache* b = baby[key];
      //    struct cache* prev = tail;

          while (b->next != head) {
        //    prev = b;
            if (b->age == oldest) {

            }
            //prev = b;
            b=b->next;
          }

      //    printf("here: %d\n",oldest );
          break;
        }
      }
      //baby[key]->next = malloc(sizeof(struct cache));
      struct cache* helper = malloc(sizeof(struct cache));
      helper->valid = 1;
      helper->tag = tag;
      helper->block = block;
      helper->age = 1;
  //      printf("%s\n","here" );
      bee->next = helper;
      helper->next = NULL;
    //  printf("%s\n","here" );
    //  helper->next == NULL;
    }
  } else if (assoc == lines) { //assoc, 1 large set
    if (baby[key]== NULL) {
      baby[key] = help;
      incrAge(baby[key]);
    } else if (baby[key]!= NULL) {
      struct cache*bee = baby[key];
  //    struct cache*prev = NULL;
      while(bee->next != NULL) {
        prev = bee;
        bee = bee->next;
        count++;
        if(count == assoc-1 && (strcmp("fifo",policy)== 0)) { //evict,
          struct cache*tmp = baby[key];
          baby[key] = baby[key]->next;
          free(tmp); // this evicts
        } else if (count == assoc-1 && (strcmp("lru",policy)== 0)) {
          // REMOVE OLDEST
          // turn into CLL
          struct cache* head= baby[key];
          struct cache* ptr = baby[key];

          while(ptr->next!=NULL) { // turns into CLL
            ptr = ptr->next;
          }
      //  struct cache* tail = ptr;
          ptr->next = head;

          int oldest;
          struct cache*help = head;
        //  struct cache*prev = NULL;
          while (help->next != head) { //end of CLL
            if (help->age > help->next->age) {
              oldest = help->age;
            } else if (help->age < help->next->age) {
              oldest = help->next->age;
            }
            help = help->next;
          }

          struct cache* b = baby[key];
      //    struct cache* prev = tail;

          while (b->next != head) {
        //    prev = b;
            if (b->age == oldest) {

            }
            //prev = b;
            b=b->next;
          }

      //    printf("here: %d\n",oldest );
          break;

        }
      }
      struct cache* helper = malloc(sizeof(struct cache));
      helper->valid = 1;
      helper->tag = tag;
      helper->block = block;
      helper->age = 1;
  //      printf("%s\n","here" );
      bee->next = helper;
      helper->next = NULL;
      incrAge(baby[key]);
    }
  }
  //printf("b: %d\n",b );
  //ptr = help;

  //int count = 0;

  if(assoc == 1){
    baby[key] = help;
  } else {
  //  printf("%s\n","here" );
    ptr = help;
  }
  //}



}


void write(struct cache**ptr,int*t,int*b, int tagsize,int key,int assoc,int lines,char*policy) {
  WRITE++;
  read(ptr,t,b,tagsize,key,assoc,lines,policy);
}







//struct cache * evict



int main(int argc, char** argv) {
  /* code */
  int m = 0;
  if (argc < 5) {
    printf("ERROR\n");
    return 0;
  }

  int csize = atoi(argv[1]);
  int bsize = atoi(argv[2]);
  char* policy = argv[3];
  // set is cache divided by block divided by assoc
  int assoc = 1;

  char letter;
  char addy[100];

  FILE* fp = fopen(argv[5], "r");
  if (fp == NULL) {
    return 0;
  }
  int num1 = csize;
  int num2 = bsize;

  int lines = num1/num2;
  int temp = lines;

  char* prop = argv[4];
  if (strcmp("assoc",prop) == 0) { //equal, fully assoc, 1 set of line
    assoc = lines;
    //printf("full: %d\n",assoc);
  } else if (strcmp("direct",prop) == 0) {
    assoc = 1;
    //printf("direct: %d\n",assoc);
  } else { // has mult
    int z = 0;
    while (prop[z] != '\0') {
    // printf("%c\n",prop[z]);
      if(prop[z] == ':') {
	       assoc = (prop[z+1]-'0');
	        break;
      }
      z++;
    }
    //printf("MULT: %d\n",assoc);
  }

  int count = 0;
  while (temp!=1) { // this is to find exponent
    temp/=2;
    count++; // count has exponent
  }

  // char* bb = strstr(prop,"assoc:");

  int offBit = getBit(csize,bsize,3,0);
//  printf("\noffbit: %d\n",offBit);

  int setI;
  // if(bb!=0) { //assoc loaded
  setI = getBit(csize,bsize,2,assoc);
    // }
  // setI = count-setI;
//  printf("setbit: %d\n",setI);

  int tag = getBit(csize,bsize,1,setI); //setI
  //printf("tag: %d\n",tag);

  int sets = csize/bsize/assoc;
  //printf("Sets: %d\n",sets);

  //int lines = binaryC(csize)/bsize;
  //printf("Lines: %d\n",lines);

  struct cache** baby = (struct cache**)malloc(sizeof(struct cache*) * sets);
  int i;
  for (i = 0; i < sets; i++) { // sets all indexes to NULL
    baby[i] = NULL;
  }

/*
  int write = 0;
  int read = 0;
  int hit = 0;
  int miss = 0;
*/
//  int evicted = 0;
  while(fscanf(fp, "%c 0x%s\n", &letter, addy) != EOF && letter != '#') {

  //  printf("\n\nLETTER: %c",letter);
    //printf("\nADDY: %s\n",addy);

     unsigned long num = converter(addy);

     int i;
     int* arr = binaryConverter(num);
     for (i = 0; i < 48; i++) { // fills with 0 in front
    //   printf("%d",arr[i]);
     }

     //printf("\n");
     //TAG_____________________________________________________
     int *t = (int*)malloc(sizeof(int) * tag);
     for (i = 0; i < tag; i++) {
       t[i] = arr[i];
     }
  //   printf("\nTag: \n");
     for (i = 0; i < tag; i++) { // fills with 0 in front
    // printf("%d",t[i]);
     }
     //printf("\n");
     //SET__________________hh__________________________________
     int *s = (int*)malloc(sizeof(int) * setI);
     int w = tag;
     for (i = 0; i < setI; i++) {
       s[i] = arr[w];
       w++;
     }
    // freeS(s,setI);
     //printf("\nSet: \n");
     for (i = 0; i < setI; i++) { // fills with 0 in front
       //printf("%d",s[i]);
     }
    // printf("\n\n");
     //BLOCK__________________________________________________
     int *b = (int*)malloc(sizeof(int) *offBit );
     w = (tag+setI); // where offset starts
     for (i = 0; i < offBit; i++) {
       b[i] = arr[w];
       w++;
     }
     //printf("\nBlock: \n");
     for (i = 0; i < offBit; i++) { // fills with 0 in front
       //printf("%d",b[i]);
     }
     //printf("\n");
     //______________________________________________________
     //printf("assoc hehe: ");
     int key = btod(s,setI);// the key is the set index
    // printf("SETI: %d\n",key);

     // every time you write, memory must read

     if (letter == 'R') {
       read(baby,t,b,tag,key,assoc,lines,policy);
     } else if (letter == 'W') {
       write(baby,t,b,tag,key,assoc,lines,policy);
     }


// I NEED A METHOD FOR CONFLICT MISSES, IF EVICTED BEFORE, MISS++




//  printf("EVICTED: %d\n",evicted);

     m++;
  //  if (m==4) {break;}
  }
  // read = miss;
     printf("Memory reads: %lu\n",READ); // reads from memor when not in cache
     printf("Memory writes: %lu\n",WRITE);
     printf("Cache hits: %lu\n",HITS);
     printf("Cache misses: %lu\n",MISS);

  return 0;
}
