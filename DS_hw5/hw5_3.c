#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int stack[1000],top=0;// top is first empty space in stack

void pushstack(int number);

int popstack(void);

int main(void)
{
    char tmp[100],*ptr=NULL,*node1=NULL,*node2=NULL;
    int adj[1000][1000], node_num=1, chosen[1000];
    int x=0,y=0,i=0,j=0, chosen_num=0, start_node=0,level=0;

    memset(adj,0,sizeof(adj));
    memset(chosen,0,sizeof(chosen));
    memset(stack,0,sizeof(stack));

    FILE *fp=NULL,*result=NULL;
    fp=fopen("output.txt","r");
    result=fopen("result3.txt","w");

    if(fp==NULL)
    {
        fprintf(stderr,"ERROR: The file is not existed\n");
        return 1;
    }

    while(fgets(tmp,100-1,fp))
    {
        //deal with format "Edge 1:<0 1> cost:2"
        ptr=strchr(tmp,'<');
        node1=++ptr;
        ptr=strchr(ptr,' ');
        *ptr='\0';
        node2=++ptr;
        ptr=strchr(ptr,'>');
        *ptr='\0';

        x=atoi(node1)-1;
        y=atoi(node2)-1;

        adj[x][y]=adj[y][x]=1;

        start_node=(x>=y)?x:y;

        node_num++;
    }

    for(i=0;i<node_num;i++)
    {
        for(j=0;j<node_num;j++)
        {
            adj[i][j]=!adj[i][j];
        }
    }

    chosen[start_node]=1;

    printf("Level\tName\n");
    fprintf(result,"Level\tName\n");
    printf("%d\t%d\n",level,start_node+1);
    chosen_num++;

    pushstack(start_node);

    while(chosen_num<node_num)
    {
        start_node=popstack();
        level++;

        for(i=0;i<node_num;i++)
        {
            if((adj[start_node][i]==1)&&(chosen[i]==0))
            {
                printf("%d\t%d\n",level,i+1);
                fprintf(result,"%d\t%d\n",level,i+1);
                chosen_num++;
                chosen[i]=1;
                pushstack(i);
            }
        }
    }

    return 0;
}

void pushstack(int number)
{
    stack[top]=number;
    top++;
}

int popstack(void)
{
    top--;
    return stack[top];
}

