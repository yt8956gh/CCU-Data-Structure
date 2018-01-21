#include<stdio.h>

int main(void)
{
    int out[700]={0},in[100]={0};
    int i=0,k=0,num=0,tmp=0;


    scanf("%d", &num);

    for(i=0;i<num;i++)
    {
        for(k=0;k<num;k++)
        {
            scanf("%d", &tmp);
            if(tmp==1)
            {
                in[k]++;
                out[i]++;
            }
        }
    }

    for(i=0;i<num;i++)
    {
        printf("%d %d %d\n",i+1,in[i],out[i]);
    }



    return 0;
}
