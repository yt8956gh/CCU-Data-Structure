#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int stack_n = 2;

void push(int *stack, int a);
void pop_Q(int *a);

int main(void)
{

    int mouse[2][3] = {{4, 6, 0},{3, 5, 0}};//a is [1] ; b is [0]
    int stack[2] = {1, 2};
    int cheese_get[2] = {0, 0}, i=0, j=0, Which_Queue=0, m=0;
    int cheese[2] = {0, 0};

    FILE *fp=NULL;
    fp=fopen("result.txt","w");

    for(i=3;i<=200;i++)
    {

        if(stack_n>=2)//pop all number from stack and count the amount of cheese
        {
            for(j=1;j>=0;j--)
            {
                Which_Queue = stack[j]%2; // determine mouse's channal in stack[j]
                cheese_get[Which_Queue] += (2-j);// count the amount of cheese

                for(m=0;m<3;m++)
                {
                    if(mouse[Which_Queue][m]!=0)
                    {
                        continue;
                    }
                    else
                    {
                        mouse[Which_Queue][m]=stack[j];
                        break;
                    }
                }
            }

            cheese[0]+=cheese_get[0];//accumulation of cheese
            cheese[1]+=cheese_get[1];

            stack_n=cheese_get[0]=cheese_get[1]=stack[0]=stack[1]=0;
        }

        if(stack_n<2)//represent that there are spaces in cave
        {
            if(cheese[1] <= cheese[0])
            {
                push(stack, mouse[1][0]);//push into cave stack
                pop_Q(mouse[1]);
            }
            else
            {
                push(stack, mouse[0][0]);
                pop_Q(mouse[0]);
            }
        }
        

        if((i==17) || (i==87) || (i==200))//output result.txt
        {

            fprintf(fp,"-------------------------------------\n");
            fprintf(fp,"Round %d\n",i);
            fprintf(fp,"Channel A food: %d\nChannel b food: %d\n\n", cheese[1], cheese[0]);
            fprintf(fp,"Cave:\n");

            for(j=0;j<stack_n;j++)
            {
                    fprintf(fp,"%d ", stack[j]);
            }

            fprintf(fp,"\n\nChannel A:\n");

            for(j=0;j<3;j++)
            {
                if(mouse[1][j]==0) break;
                fprintf(fp,"%d ",mouse[1][j]);
            }

            fprintf(fp,"\nChannel B:\n");

            for(j=0;j<3;j++)
            {
                if(mouse[0][j]==0) break;
                fprintf(fp,"%d ",mouse[0][j]);
            }

            fprintf(fp,"\n");
        }
    }

    fclose(fp);

    return 0;
}

void push(int *stack, int a)
{
    stack[stack_n] = a;

    stack_n++;
}

void pop_Q(int *a)
{
    a[0]=a[1];
    a[1]=a[2];
    a[2]=0;
}

