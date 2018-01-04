#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*
    edge_weight[MAX]紀錄所有起點出發到各點的最小路徑。 
    stack紀錄trace的順序。 
 
    1. PushStack(起點) 
     
    2. 初始化edge_weight[]為-1 (視作無限大)
     
    3. V=PopStack() 
     
    4. 檢驗該V連接的每一個vertice（N）。 
     
    5. If（（V的edge_weight + V到N的weight）<（N在edge_weight中的權重））

             N在edge_weight中的權重= V的edge_weight + V到N的weight
     
    7. PushStack(與V連接且擁有最小權重的Vertice)。 
     
    If(stack_is_empty||遇到終點)break 
    else跳到STEP 3 
*/

int stack[1000],top=0;// top is first empty space in stack
int edge_weight[1000],adj[1000][1000],term_num=0;

void pushstack(int number);

int popstack(void);

int end_node(int number);

int main(void)
{

    char tmp[1000], *ptr=NULL;
    int i=0, j=0, len=0;
    int now=0,start=0,end=0, minist=0, first=0;

    memset(adj,0,sizeof(adj));
    memset(stack,0,sizeof(stack));

    // Because memset will initialize element with unsigned char, 
    // the memset is not suitable to fill -1 to edge_weight.
    for(i=0;i<1000;i++)
        edge_weight[i]=-1;

    FILE *fp=NULL,*result=NULL;
    fp=fopen("1input.txt","r");
    result=fopen("result1.txt","w");

    if(fp==NULL)
    {
        fprintf(stderr, "ERROR: The file is not existed\n");
        return 1;
    }

    // get term_num
    fgets(tmp,1000-1,fp);
    term_num=atoi(tmp);

    for(i=0;i<term_num;i++)
    {
        fgets(tmp,1000-1,fp);
        len=strlen(tmp);

        if(tmp[len-1]=='\n')
            tmp[len-1]='\0';


        ptr=strtok(tmp," ");
        adj[i][0]=atoi(ptr);

        for(j=1;j<term_num;j++)
        {
            ptr=strtok(NULL," ");
            adj[i][j]=atoi(ptr);
        }
    }

    for(i=0;i<term_num;i++)
    {
        for(j=0;j<term_num;j++)
        {
            printf("%d ",adj[i][j]);
        }
        printf("\n");
    }

    printf("Enter two vertice <start end>:");
    fprintf(result,"Enter two vertice <start end>:");

    while(scanf("%d %d",&start,&end)!=EOF)
    {
        fprintf(result,"%d %d\n",start,end);


        for(i=0;i<1000;i++)
            edge_weight[i]=-1;

        if(start==0||end==0)
        {
            return 0;
        }

        if((start<0)||(end<0)||(start>term_num)||(end>term_num))
        {
            fprintf(stderr, "The number is illegal\n");
            printf("Enter two vertice <start end>:");
            fprintf(result,"Enter two vertice <start end>:");
            continue;
        }

        pushstack(start-1);
        edge_weight[start-1]=0;

        while(top!=0)
        {
            now=popstack();
            first=minist=0;

            if(end_node(now)) break;// 遇到終點

            //推進first到第一個不為0的index,將第一個遇到的非零視作minist.
            for(i=0;i<term_num;i++)
            {
                first=minist=i;
                if(adj[now][i]!=0) break;
            }

            //更新每個節點的最短路徑
            for(i=first;i<term_num;i++)
            {
                if(adj[now][i]!=0)
                {
                    if(((edge_weight[now]+adj[now][i])<edge_weight[i])||(edge_weight[i]==-1))
                        edge_weight[i]=edge_weight[now]+adj[now][i];

                    if(adj[now][minist]>adj[now][i]) minist=i;
                }
            }

            pushstack(minist);
        }

        printf("The cost from %d to %d is : %d\n",start,end,edge_weight[end-1]);
        fprintf(result,"The cost from %d to %d is : %d\n",start,end,edge_weight[end-1]);
        printf("Enter two vertice <start end>:");
        fprintf(result,"Enter two vertice <start end>:");
    }

    return 0;
}


void pushstack(int number)
{
    stack[top++]=number;
}


int popstack(void)
{
    return stack[--top];
}


int end_node(int number)
{
    int i=0,empty=1;

    for(i=0;i<term_num;i++)
    {
        if(adj[number][i]!=0)
        {
            empty=0;
            break;
        }
    }
    return empty;
}




