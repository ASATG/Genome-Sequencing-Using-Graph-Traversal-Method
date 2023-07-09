#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "genome.h"


void push(stack **top, dict *key)
{
    stack *keynode = (stack *)malloc(sizeof(stack));
    keynode->key = key;
    keynode->next = NULL;
    if (*top == NULL)
    {
        *top = keynode;
        return;
    }
    keynode->next = *top;
    *top = keynode;
    return;
}

dict **pop(stack **top)
{
    if (*top == NULL)
    {
        return NULL;
    }
    dict *ret = (*top)->key;
    *top = (*top)->next;
    dict *new = (dict *)malloc(sizeof(dict *));
    new = &ret;
    return new;
}

//dict *answer = NULL;

void prefix(char **pre, char *window, int len)
{
    strncpy(*pre, window + 0, len);
}

void suffix(char **suf, char *window, int len)
{
    strncpy(*suf, window + 1, len);
}
void slice(char **window, char *text, int start, int k)
{
    strncpy(*window, text + start, k);
}

void add_value(dict **answer, char *pre1, char *pre2, char *suf1, char *suf2)
{
    dict *temp = *answer;
    while (strcmp(temp->key1, pre1) && strcmp(temp->key2, pre2))
    {
        temp = temp->next;
    }

    if (temp->value == NULL)
    {
        value_node *temp1 = (value_node *)malloc(sizeof(value_node));
        temp1->data1 = suf1;
        temp1->data2 = suf2;
        temp1->next = NULL;
        temp->value = temp1;
    }
    else
    {
        value_node *temp2 = temp->value;
        while (temp2->next)
        {
            temp2 = temp2->next;
        }
        value_node *temp1 = (value_node *)malloc(sizeof(value_node));
        temp1->data1 = suf1;
        temp1->data2 = suf2;
        temp1->next = NULL;
        temp2->next = temp1;
    }
}

void add_key_value(dict **answer, char *pre1, char *pre2, char *suf1, char *suf2)
{
    if (*answer == NULL)
    {
        dict *temp = (dict *)malloc(sizeof(dict));
        temp->key1 = pre1;
        temp->key2 = pre2;
        temp->value = NULL;
        add_value(&temp, pre1, pre2, suf1, suf2);
        temp->next = NULL;
        *answer = temp;
    }
    else
    {
        dict *curr = *answer;
        while (curr->next)
        {
            curr = curr->next;
        }
        dict *temp = (dict *)malloc(sizeof(dict));
        temp->key1 = pre1;
        temp->key2 = pre2;
        temp->value = NULL;
        add_value(&temp, pre1, pre2, suf1, suf2);
        temp->next = NULL;
        curr->next = temp;
    }
}

void add_key(dict **answer, char *pre1, char *pre2){
    if (*answer == NULL)
    {
        dict *temp = (dict *)malloc(sizeof(dict));
        temp->key1 = pre1;
        temp->key2 = pre2;
        temp->value = NULL;
        temp->next = NULL;
        *answer = temp;
    }
    else
    {
        dict *curr = *answer;
        while (curr->next)
        {
            curr = curr->next;
        }
        dict *temp = (dict *)malloc(sizeof(dict));
        temp->key1 = pre1;
        temp->key2 = pre2;
        temp->value = NULL;
        temp->next = NULL;
        curr->next = temp;
    }
}

dict *swapkey(dict *ptr1, dict *ptr2)
{
    dict *temp = ptr2->next;
    ptr2->next = ptr1;
    ptr1->next = temp;
    return ptr2;
}

void bubbleSortkey(dict **head, int count)
{
    dict **h;
    int i, j, swapped;

    for (i = 0; i <= count; i++)
    {

        h = head;
        swapped = 0;

        for (j = 0; j < count - i - 1; j++)
        {

            dict *p1 = *h;
            dict *p2 = p1->next;
            if (strcmp(p1->key1, p2->key1) == 0)
            {
                if (strcmp(p1->key2, p2->key2) > 0)
                {
                    *h = swapkey(p1, p2);
                    swapped = 1;
                }
            }
            else if (strcmp(p1->key1, p2->key1) > 0)
            {
                *h = swapkey(p1, p2);
                swapped = 1;
            }

            h = &(*h)->next;
        }
        if (swapped == 0)
            break;
    }
}

value_node *swapvalue(value_node *ptr1, value_node *ptr2)
{
    value_node *temp = ptr2->next;
    ptr2->next = ptr1;
    ptr1->next = temp;
    return ptr2;
}

void bubbleSortvalue(value_node **head, int count)
{
    value_node **h;
    int i, j, swapped;
    for (i = 0; i <= count; i++)
    {

        h = head;
        swapped = 0;

        for (j = 0; j < count - i - 1; j++)
        {

            value_node *p1 = *h;
            value_node *p2 = p1->next;
            if (strcmp(p1->data1, p2->data1) == 0)
            {
                if (strcmp(p1->data2, p2->data2) > 0)
                {
                    *h = swapvalue(p1, p2);
                    swapped = 1;
                }
            }
            else if (strcmp(p1->data1, p2->data1) > 0)
            {
                *h = swapvalue(p1, p2);
                swapped = 1;
            }
        }
        if (swapped == 0)
            break;
    }
}

int check(dict *answer, char *pre1, char *pre2)
{
    dict *temp = answer;
    while (temp)
    {
        if (!strcmp(temp->key1, pre1))
        {
            if (!strcmp(temp->key2, pre2))
            {
                return 1;
            }
        }
        temp = temp->next;
    }
    return 0;
}

void de_bruijn(dict ** answer,int k, int d)
{
    char *text[1000];
    int countkey = 0;
    
    while (scanf("%s", text) != EOF)
    {
        // int len = strlen(text);
        char *window1 = malloc(k);
        char *window2 = malloc(k);
        slice(&window1, text, 0, k);
        slice(&window2, text, k + 1, k);
        char *pre1 = malloc(k - 1);
        char *pre2 = malloc(k - 1);
        char *suf1 = malloc(k - 1);
        char *suf2 = malloc(k - 1);
        prefix(&pre1, window1, k - 1);
        prefix(&pre2, window2, k - 1);
        suffix(&suf1, window1, k - 1);
        suffix(&suf2, window2, k - 1);
        
        if (check(*answer, pre1, pre2) == 0)
        {
            add_key_value(answer, pre1, pre2, suf1, suf2);
            countkey++;
        }
        
        else
        {
            add_value(answer, pre1, pre2, suf1, suf2);
        }
        
    }
    
    bubbleSortkey(answer, countkey);
    char *string[1000];

    dict *temp = *answer;
    
    while (temp)
    {

        strcat(string, temp->key1);
        strcat(string, "|");
        strcat(string, temp->key2);
        strcat(string, " -> ");
        if (temp->value->next == NULL)
        {
            strcat(string, temp->value->data1);
            strcat(string, "|");
            strcat(string, temp->value->data2);
            strcat(string, "\n");
        }
        else
        {
            value_node *c = temp->value;
            int countvalue = 0;
            while (c)
            {
                countvalue++;
                c = c->next;
            }
            bubbleSortvalue(&(temp->value), countvalue);
            strcat(string, temp->value->data1);
            strcat(string, "|");
            strcat(string, temp->value->data2);
            value_node *temp1 = temp->value->next;
            while (temp1)
            {
                strcat(string, ",");
                strcat(string, temp1->data1);
                strcat(string, "|");
                strcat(string, temp1->data2);
                temp1 = temp1->next;
            }
            strcat(string, "\n");
        }
        temp = temp->next;
    }
    printf("%s", string);
}

void startnode(dict *answer, dict **temp1)
{
    dict *temp = answer;
    while (temp)
    {
        int indegree = 0;
        int outdegree = 0;
        value_node *temp3 = temp->value;
        while (temp3)
        {
            outdegree++;
            temp3 = temp3->next;
        }
        char *tempkey1 = temp->key1;
        char *tempkey2 = temp->key2;
        dict *temp4 = answer;
        while (temp4)
        {
            value_node *temp5 = temp4->value;
            while (temp5)
            {
                if (!(strcmp(tempkey1, temp5->data1)) && !(strcmp(tempkey2, temp5->data2)))
                {
                    indegree++;
                }
                temp5 = temp5->next;
            }
            temp4 = temp4->next;
        }
        if (outdegree > indegree)
        {
            *temp1 = temp;
            break;
        }
        else if (outdegree > 0)
        {
            *temp1 = temp;
        }
        temp = temp->next;
    }
}




