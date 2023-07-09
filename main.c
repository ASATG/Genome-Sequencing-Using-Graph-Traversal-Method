#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "genome.h"

dict *answer = NULL;

int main()
{
    char string1[10000];
    char string2[10000];
    char temp10[10000];
    int k;
    int d;
    scanf("%d %d\n", &k, &d);
    de_bruijn(&answer,k, d);
    
    dict *sn = NULL;
    startnode(answer, &sn);
    //printf("%s|%s", sn->key1, sn->key2);
    stack *top = NULL;
    push(&top, sn);
    char *ep = (char *)malloc(sizeof(char)*INT_MAX);
    dict * temp = answer;
    while(temp){
        value_node * temp2 = temp->value;
        while(temp2){
            int ans = check(answer,temp2->data1,temp2->data2);
            if(ans == 0){
                add_key(&answer,temp2->data1,temp2->data2);
            }
            temp2 = temp2->next;
        }
        temp = temp -> next;
    }
    while (top)
    {
        dict * st = (dict *)malloc(sizeof(dict));
        st = top->key;
        if(st->value != NULL){
            char * str1 = st->value->data1;
            char * str2 = st->value->data2;
            dict * temp = answer;
            while(temp){
                if(!strcmp(str1,temp->key1) && !strcmp(str2,temp->key2)){
                    push(&top,temp);
                    break;
                }
                temp = temp ->next;
            }
            st->value = st->value->next;
        }else{
          
           //printf("\n %s \n",st->key1);
            //strcat(ep,st->key1);
            pop(&top);
            
            if(top){
              char temp11[10000]="";
              strncpy(temp11, st->key1 + (k-2), 1);
              strcat(temp11, string1);
              strcpy(string1,temp11);
              
            }else{
              strcpy(temp10,st->key1);
              strcat(temp10, string1);
              strcpy(string1,temp10);
              
            }
            
            if(top){
              char temp12[10000]="";
              strncpy(temp12, st->key2 + (k-2), 1);
              strcat(temp12, string2);
              strcpy(string2,temp12);
              
            }else{
              strcpy(temp10,st->key2);
              strcat(temp10, string2);
              strcpy(string2,temp10);
              
            }
            
          
            
        }
    }
    int len = strlen(string1);
    int i=0;
    while(len){
      char temp13[10000]="";
      strncpy(temp13, string1 + i, len);
      char temp14[10000]="";
      i++;
      strncpy(temp14, string2 + 0, len);
      if(!strcmp(temp13,temp14)){
        break;
      }
      len--;
    }
    char stringanswer[10000]="";
    char temp15[10000]="";
    strncpy(temp15,string1,strlen(string1)-len);
    strcat(stringanswer,temp15);
    strcat(stringanswer,string2);
    printf("%s\n",stringanswer);
    
}
