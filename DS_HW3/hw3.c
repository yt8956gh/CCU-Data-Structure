#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node
{
    int number;
    struct node *next;
};

typedef struct node NODE;

NODE *end=NULL;
int NODE_NUMBER=0;

void show_main_list(void);

NODE* read_file(NODE* header);

NODE* read_input(NODE* header);

NODE* insert_node(NODE* header, int n);

void survive(NODE* header);
//ask user skipped and direction
NODE* reverse_node(NODE* header);
//reverse linked list when user choose left 
void kill(NODE* header,int skip);
//kill people with Josephus problem


int main()
{
    int choice=1,c=0;
    NODE *header=NULL;

    while(choice)
    {
        show_main_list();
        NODE_NUMBER=0;

        if(scanf("%d",&choice)!=EOF)
        {
            switch(choice)
            {
                case 1:
                    header=read_file(header);
                    break;
                case 2:
                    header=read_input(header);
                    break;
                case 0:
                    return 0;
                default:
                    fprintf(stderr, "ERROR: illegal choice !!\n");
                    continue;
            }
        }
        survive(header);
        header = NULL;

        printf("\n>>>>>Type Enter to Continue<<<<<\n");
        // Continuously read characters from stdin buffer until the last "\n" is removed from buffer. 
        // e.g: Remove a string "ABCD\n" read from scanf in buffer.
        while ((c = getchar()) != '\n')
        {
            c=1;
        }
        // This way make screen stop until user type "ENTER".
        c = getchar();
    }

    return 0;
}


void show_main_list(void)
{
    system("clear");
    printf("#================================================#\n");
    printf("||                                              ||\n");
    printf("||    Which items do you want to choose ?       ||\n");
    printf("||    (1) Read numbers from a file              ||\n");
    printf("||    (2) Input new numbers                     ||\n");
    printf("||    (0) Quit                                  ||\n");
    printf("||                                              ||\n");
    printf("#================================================#\n");
}


NODE* read_file(NODE* header)
{
    int i=0, n=0;
    NODE *ptr=NULL;
    char filename[100],tmp[1000],*qtr=NULL;
    FILE *fp=NULL;

    printf("Please enter filename:\n");
    scanf("%s",filename);
    fp=fopen(filename, "r");

    if(fp==NULL)
    {
        fprintf(stderr, "The file doesn't exist !!\n");
        return header;
    }

    fgets(tmp,1000-1,fp);
    tmp[strlen(tmp)] = '\0';//beacause there is not '\n' on the end of first line in the file

    qtr=strtok(tmp,",");

    while(qtr!=NULL)
    {
        n=atoi(qtr);
        header=insert_node(header, n);
        printf("No.%d :%d\n",++i , n);
        qtr=strtok(NULL,",");
    }
    
    printf("The persons in circular list are:\n");

    ptr=header;

    while(ptr!=NULL)
    {
        printf("%d  ", ptr->number);
        end=ptr;//global variable
        ptr=ptr->next;
    }

    printf("\n");
    fclose(fp);

    return header;
    //the linked list is still single direction and not circular
}


NODE* read_input(NODE* header)
{
    int c=0, i=0, n=0;
    NODE *ptr=header;

    printf("How many numbers do you want to add ?");
    scanf("%d",&c);

    for(i=0;i<c;i++)
    {
        printf("No.%d :", i+1);
        scanf("%d", &n);
        header=insert_node(header, n);
    }

    printf("The persons in circular list are:\n");

    ptr=header;

    while(ptr!=NULL)
    {
        printf("%d  ", ptr->number);
        end=ptr;//global variable
        ptr=ptr->next;
    }

    printf("\n");

    return header;
}


NODE* insert_node(NODE* header, int n)
{
    NODE *ptr=header, *lastp=header, *current=NULL;

    current=(NODE*)malloc(sizeof(NODE));
    current->number=n;
    current->next=NULL;
    NODE_NUMBER++;
    
    if(header==NULL)
    {
        return current;
    }

    while(ptr!=NULL)
    {
        lastp=ptr;
        ptr=ptr->next;
    }

    lastp->next=current;

    return header;

}


void survive(NODE* header)
{
    int skip=0,choice=0;
    printf("Enter the number of persons to be skipped:");
    scanf("%d",&skip);
    printf("Which direction do you want to choose ? (1)Left (2)Right\n");
    scanf("%d",&choice);

    if(skip<=0)
    {
        fprintf(stderr, "ERROR: Illegal Skipped\n");
        exit(1);
    }

    switch(choice)
    {
        case 1:
            header=reverse_node(header);
            kill(header, skip);
            break;

        case 2:
            kill(header, skip);
            break;

        default:
            fprintf(stderr, "ERROR: illegal choice !!\n");
            break;

    }
}


NODE* reverse_node(NODE* header)
{
    NODE *middle=NULL,*trail=NULL, *first=header;

    end = header = header->next;

    while(header!=NULL)
    {
        trail = middle;
        middle = header;
        header = header->next;
        middle->next = trail;

    }

    first->next=middle;//must keep the first s

    return first;
}


void kill(NODE* header,int skip)
{
    NODE *ptr=header, *lastp=NULL;
    int i=0;

    end->next=header;//link tail and header

    while(NODE_NUMBER>1)//break when there is only one node in linked list
    {
        for(i=1;i<skip;i++)//count 1~skip to find the person killed
        {
            lastp=ptr;
            ptr=ptr->next;
        }

        lastp->next=ptr->next;
        free(ptr);
        ptr=lastp->next;//assign "person next to dead person" to ptr

        NODE_NUMBER--;
    }

    printf("The person to survive is :");
    printf("%d\n",ptr->number);
    free(ptr);
}
