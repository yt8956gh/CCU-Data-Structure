#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    int value;
    int coin;
    struct node *right;
    struct node *left;
};

typedef struct node NODE;

NODE *insert(NODE *header, int node, int coin_value);
int trace(NODE *header, int hunter, int sum, FILE* result);


int main(void)
{
    char *node_name=NULL, *coin_value=NULL, tmp[1000], filename[100];
    int len=0, hunter=0, sum=0;
    NODE *header=NULL;

    FILE *result=NULL, *fp=NULL;

    do
    {
        printf("Please enter input filename :");

        fgets(filename,100-1,stdin);
        len=strlen(filename);
        if(filename[len-1]=='\n')  filename[len-1]='\0';

        fp=fopen(filename,"r");
    }
    while(fp==NULL);

    result=fopen("result.txt","a");

    while(fgets(tmp, 1000-1, fp))
    {
        len=strlen(tmp);

        if(tmp[len-1]=='\n')
            tmp[len-1]='\0';

        node_name=strtok(tmp, ",");
        coin_value=strtok(NULL, ",");

        if(node_name==NULL||coin_value==NULL)
        {
            fprintf(stderr,"Syntax Error\n");
        }

        printf("%s,%s\n",node_name,coin_value);
        header=insert(header,atoi(node_name),atoi(coin_value));

    }

    if(header==NULL)
    {
        fprintf(stderr,"ERROR: Building Binary Tree Fail\n");
        return 1;
    }

    printf("\nFinish Reading file\n");
    printf("---------------------------------\n");

    printf("(type -1 to leave)\nPlease enter the node of treasure hunter:");

    while(scanf("%d",&hunter)!=EOF)
    {
        if(hunter==-1)  return 0;

        fprintf(result,"#%d hunter's walking trajectory\n",hunter);

        sum=0;
        sum=trace(header,hunter,sum,result);

        fprintf(result, "Totally collected %d coins\n", sum);

        fprintf(result, "---------------------------------\n");
        printf("Please enter the node of treasure hunter:");
    }

    return 0;
}


NODE *insert(NODE *header, int node, int coin_value)
{
    NODE *current=NULL;

    if(header==NULL)
    {
        current=(NODE *)malloc(sizeof(current));
        current->right=NULL;
        current->left=NULL;
        current->value=node;
        current->coin=coin_value;
        printf("Insert node:%d coin:%d\n", node, coin_value);
        return current;
    }

    if(header->value>node)
    {
        header->left=insert(header->left, node, coin_value);
        return header;//return original child to its parent
    }
    else if(header->value<node)
    {
        header->right=insert(header->right, node, coin_value);
        return header;//return original child to its parent
    }
    else
    {
        fprintf(stderr, "The node is existing\n");
        return NULL;
    }
}


int trace(NODE *header, int hunter, int sum, FILE* result)
{
    if(header==NULL)
        return sum;
    else
    {
        sum+=header->coin;
        fprintf(result,"node:%d collect %d coins\n", header->value, header->coin);

        if(header->value>hunter)//to left
        {
            return trace(header->left, hunter, sum, result);
        }
        else if(header->value<hunter)//to right
        {
            return trace(header->right, hunter, sum, result);
        }
        else
            return sum;
    }
}


