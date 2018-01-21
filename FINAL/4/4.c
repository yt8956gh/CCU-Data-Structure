#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int len=0;

void quicksort(int *number, int left, int right);

int main(void)
{
    char tmp[1000]={'\0'},*ptr=NULL;
    int number[1000]={0},i=0,j=0;

    fgets(tmp,1000-1,stdin);

    ptr=strtok(tmp," ");

    while(ptr!=NULL)
    {
        number[len++]=atoi(ptr);
        ptr=strtok(NULL," ");
    }

    quicksort(number,0,len-1);

    return 0;

}

void quicksort(int *number, int left, int right)
{
    int pivot=0,tmp=0,i=0,j=0,k=0;

    if(left<right)
    {
        i=left; j=right+1;
        pivot=number[left];

        do {
            do i++; while(number[i]<pivot);
            do j--; while(number[j]>pivot);
            if(i<j)
            {
                tmp=number[i];
                number[i]=number[j];
                number[j]=tmp;
                for(k=0;k<(len-1);k++)
                    printf("%d ",number[k]);
                printf("%d\n", number[k]);
            }
        } while(i<j);

        if(j!=left)
        {//如果切割到最後有區段只剩2個元素，必須要用j!=left判斷，以免重複print。
            tmp=number[left];
            number[left]=number[j];
            number[j]=tmp;
            for(k=0;k<(len-1);k++)
                printf("%d ",number[k]);
            printf("%d\n", number[k]);
        }

        quicksort(number, left, j-1);
        quicksort(number, j+1, right);
    }
}
