#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(void)
{
    int num[1000]={0},len=0,i=0,k=0,tmp=0;
    char string[1000],*ptr=NULL;

    fgets(string,1000-1,stdin);
    ptr=strtok(string," ");

    while(ptr!=NULL)
    {
        num[len++]=atoi(ptr);
        ptr=strtok(NULL," ");
    }

    for(i=1;i<len;i++)
    {
        for(k=0;k<(len-i);k++)
        {
            if(num[k]>num[k+1])
            {
                tmp=num[k];
                num[k]=num[k+1];
                num[k+1]=tmp;
            }
        }

        for(k=0;k<(len-1);k++)
            printf("%d ",num[k]);
        printf("%d\n",num[k]);
    }

    return 0;
}
