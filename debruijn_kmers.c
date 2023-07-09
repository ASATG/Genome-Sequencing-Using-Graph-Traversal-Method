#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct value_node{
  char* data;
  struct value_node* next;
}value_node;

typedef struct dict{
  char* key;
  value_node* value;
  struct dict* next;
}dict;

void prefix(char** pre,char* window,int len){
   strncpy(*pre,window+0,len);
}

void suffix(char** suf,char* window,int len){
  strncpy(*suf,window+1,len);
}
void slice(char** window,char* text,int start,int k){
  strncpy(*window,text+start,k);
}

void add_value(dict** answer,char* pre,char* suf){
  dict* temp=*answer;
    while(strcmp(temp->key,pre)){
      temp=temp->next;
    } 
  
  if(temp->value==NULL){
    value_node* temp1= (value_node*)malloc(sizeof(value_node));
    temp1->data = suf;
    temp1->next=NULL;
    temp->value=temp1;
  }
  else{
    value_node* temp2 = temp->value;
    while(temp2->next){
      temp2=temp2->next;
    }
    value_node* temp1= (value_node*)malloc(sizeof(value_node));
    temp1->data = suf;
    temp1->next=NULL;
    temp2->next=temp1;
  }  
}

void add_key_value(dict** answer,char* pre,char* suf){
  if(*answer==NULL){
    dict* temp=(dict*)malloc(sizeof(dict));
    temp->key=pre;
    temp->value=NULL;
    add_value(&temp,pre,suf);
    temp->next=NULL;
    *answer=temp;
  }
  else{
    dict* curr=*answer;
    while(curr->next){
      curr=curr->next;
    }
    dict* temp=(dict*)malloc(sizeof(dict));
    temp->key=pre;
    temp->value=NULL;
    add_value(&temp,pre,suf);
    temp->next=NULL;
    curr->next=temp;
  }
  
}

dict* swapkey(dict* ptr1, dict* ptr2)
{
    dict* temp = ptr2->next;
    ptr2->next = ptr1;
    ptr1->next = temp;
    return ptr2;
}
 
void bubbleSortkey(dict** head, int count)
{
    dict** h;
    int i, j, swapped;
 
    for (i = 0; i <= count; i++) {
 
        h = head;
        swapped = 0;
 
        for (j = 0; j < count - i - 1; j++) {
 
            dict* p1 = *h;
            dict* p2 = p1->next;
 
            if (strcmp(p1->key,p2->key)>0) {
                *h = swapkey(p1, p2);
                swapped = 1;
            }
 
            h = &(*h)->next;
        }
        if (swapped == 0)
            break;
    }
}
 
 
value_node* swapvalue(value_node* ptr1, value_node* ptr2)
{
    value_node* temp = ptr2->next;
    ptr2->next = ptr1;
    ptr1->next = temp;
    return ptr2;
}
 
void bubbleSortvalue(value_node** head, int count)
{
    value_node** h;
    int i, j, swapped;
    for (i = 0; i <= count; i++) {
 
        h = head;
        swapped = 0;
 
        for (j = 0; j < count - i - 1; j++) {
 
            value_node* p1 = *h;
            value_node* p2 = p1->next;
 
            if (strcmp(p1->data,p2->data)>0) {
                *h = swapvalue(p1, p2);
                swapped = 1;
            }
        }
        if (swapped == 0)
            break;
    }
} 

int check(dict* answer,char* pre){
  dict* temp = answer;
  while(temp){
    if(!strcmp(temp->key,pre)){
      return 1;
    }
    temp=temp->next;
  }
  return 0;
}

void de_bruijn(){
  char* text[1000];
  dict* answer=NULL;
  int countkey=0;
  while(scanf("%s",text)!=EOF){
    int len = strlen(text);
    char* window = text;
    char* pre = malloc(len-1);
    char* suf = malloc(len-1);
    prefix(&pre,window,len-1);
    suffix(&suf,window,len-1);
    if(check(answer,pre)==0){
    add_key_value(&answer,pre,suf);
      countkey++;
    }
    else{
      add_value(&answer,pre,suf);
    }
  }
  bubbleSortkey(&answer,countkey);
  char* string[1000];
  
  dict* temp=answer;
  while(temp){
    
    strcat(string,temp->key);
    strcat(string," -> ");
    if(temp->value->next==NULL){
      strcat(string,temp->value->data);
      strcat(string,"\n");
    }
    else{
      value_node* c = temp->value;
      int countvalue=0;
      while(c){
        countvalue++;
        c=c->next;
      }
      bubbleSortvalue(&(temp->value),countvalue);
      strcat(string,temp->value->data);
      value_node* temp1 = temp->value->next;
      while(temp1){
        strcat(string,",");
        strcat(string,temp1->data);
        temp1 = temp1->next; 
      }
      strcat(string,"\n");
    }
    temp=temp->next;
  }
  printf("%s",string);
}


int main()
{
  de_bruijn();
  
}
