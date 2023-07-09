typedef struct value_node
{
    char *data1;
    char *data2;
    struct value_node *next;
} value_node;

typedef struct dict
{
    char *key1;
    char *key2;
    value_node *value;
    struct dict *next;
} dict;

typedef struct stack
{
    dict *key;
    struct stack *next;
} stack;

void push(stack **top, dict *key);
dict **pop(stack **top);
void prefix(char **pre, char *window, int len);
void suffix(char **suf, char *window, int len);
void slice(char **window, char *text, int start, int k);
void add_value(dict **answer, char *pre1, char *pre2, char *suf1, char *suf2);
void add_key_value(dict **answer, char *pre1, char *pre2, char *suf1, char *suf2);
void add_key(dict **answer, char *pre1, char *pre2);
dict *swapkey(dict *ptr1, dict *ptr2);
void bubbleSortkey(dict **head, int count);
value_node *swapvalue(value_node *ptr1, value_node *ptr2);
void bubbleSortvalue(value_node **head, int count);
int check(dict *answer, char *pre1, char *pre2);
void de_bruijn(dict ** answer,int k, int d);
void startnode(dict *answer, dict **temp1);

