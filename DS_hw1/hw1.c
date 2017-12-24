#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define Max_Length 1000

struct big_Number
{
	int ID;
	char a[Max_Length];
	char b[Max_Length];
	struct big_Number *next;
};

typedef struct big_Number BIGN;


int data_number=0, file_on=0;
char filename[100];


void show_menu(void);

// ----------------NO.1 function-----------------------

BIGN *read_file(BIGN *header);

// ----------------NO.2 function-----------------------

void show_list(BIGN *header);

char *trans_E(char *tmp);

// ----------------NO.3 function-----------------------

BIGN *insert_BIGN(BIGN *header, int ID, char *aptr, char *bptr);

BIGN *write_file(BIGN *header);

int check_number(char *tmp);

// ----------------NO.4 function-----------------------

void show_operator_list(void);

BIGN *show_source_question(BIGN *header);

void operator(BIGN *header);

// -----------------Operator_helper--------------------

void fill_zero(BIGN *ptr, char *max, char *min, int *MAX_MIN_len);

void remove_tail_zero(char *result, int *result_int);

void String_Reverse(char *s);

// -----------------Operator---------------------------

char* Plus(BIGN *ptr, char *result);

char* Subtraction(BIGN *ptr, char *result);

char* Multiplication(BIGN *ptr, char *result);



int main()
{
	int choice=1, c=0;

	BIGN *header = NULL;

	while(choice)
	{	
		show_menu();

		// will put the string including "\n" into stdin
		// if scan fail, the scanf will return EOF
		if(scanf("%d", &choice)!=EOF)
		{
			switch(choice)
			{
				case 1:
					header = read_file(header);
					break;
				case 2:
					show_list(header);
					break;
				case 3:
					header = write_file(header);
					break;
				case 4:
					operator(header);
					break;
				case 0:
					return 0;
				default:
					printf("Please enter correct choice number !!\n");
					break;
			}
		}

		printf("\n>>>>>Type Enter to Continue<<<<<\n");

		// Continuously read characters from stdin buffer until the last "\n" is removed from buffer.
		// e.g: Remove a string "ABCD\n" read from scanf in buffer.
		while ( (c = getchar()) != '\n')
		{
			c=1; 
		}

		// This way make screen stop until user type "ENTER".
		c = getchar();
	}
	return 0;
}


void show_menu(void)
{
	system("clear");
	printf("What do you want to do?\n\n");
	printf("\t1) Read numbers from a file\n");
	printf("\t2) Show the input numbers\n");
	printf("\t3) Write numbers to a file\n");
	printf("\t4) Calculate the big numbers\n");
	printf("\t0) Exit\n");
}


BIGN* read_file(BIGN *header)
{
	char tmp[Max_Length];
	char *aptr = NULL, *bptr = NULL, *IDptr = NULL;

	// deal with file-open and get filename
	FILE *fp = NULL;
	printf("Please input the file name:\n");
	scanf("%s", filename);

	fp = fopen(filename, "r");

	if(fp == NULL)
	{
		fprintf(stderr, "The file doesn't exist !!\n");
		return header;
	}

	// remove first line in file
	fgets(tmp, Max_Length - 1, fp);

	while(fgets(tmp, Max_Length - 1, fp))
	{
		tmp[strlen(tmp)-2] = '\0';// The end of line in file is "\r\n".
		IDptr = strtok(tmp, ", ");
		aptr = strtok(NULL, ", ");
		bptr = strtok(NULL, ", ");

		if(IDptr == NULL || aptr == NULL || bptr == NULL )
		{
			fprintf(stderr, "Encounter ilegal syntax !!\n");
			fclose(fp);// if there is ilegal syntax, doesn't read next line and close file
			return header;
		}

		header = insert_BIGN(header, atoi(IDptr), aptr , bptr);

	}

	printf("%s reads successfully\n", filename);

	file_on = 1;// represent that file had been read already
	fclose(fp);

	return header;
}

// insert data with linked_list in tail 
// and return header back to upper function
BIGN* insert_BIGN(BIGN *header, int ID, char *aptr, char *bptr)
{
	BIGN *current = NULL, *ptr = header, *lastp = NULL;

	current = (BIGN*)malloc(sizeof(BIGN));
	current->ID = ID;
	strcpy(current->a, aptr);
	strcpy(current->b, bptr);
	current->next = NULL;

	if(header == NULL)
	{
		return current;
	}
	// the header  is a NULL ptr in first
	while(ptr != NULL)
	{	
		lastp = ptr;
		ptr = ptr->next;
	}

	lastp->next = current;

	data_number++;
	
	return header;
}

// Ask the user numbers and check the format of number.
// Append new pair of numbers at the end of the file.
// Record how many numbers in array simultaneously.
BIGN* write_file(BIGN *header)
{
	int i=0;
	char tmp[Max_Length], input[2][Max_Length];

	FILE *fp = NULL;

	fp = fopen(filename, "a");
	// mode "a" Append data at the end of the file. 
	// The file is created if it does not exist.

	if(fp == NULL)
	{
		fprintf(stderr, "The file doesn't exist !!\n");
		return header;
	}

	printf("NO.%d\n", data_number + 1);// NO.?? will be written

	for(i=1;i<=2;i++)// read Number1 and Number2
	{
		printf("Number%d:", i);

		if(scanf("%s", tmp)!=EOF)
		{
			if(check_number(tmp))// error is 1 in check_number
			{
				fprintf(stderr, "Format Error !!\n");
				return header;
			}

			strcpy(input[i-1], tmp);// i is (1, 2)
		}
		else
		{
			printf("ERROR!!\n");
			return header;
		}
	}

	// data_number will records how many numbers in array and file simultaneously.
	fprintf(fp, "%d, %s, %s\r\n", ++data_number, input[0], input[1]);

	printf("Write file successfully !!\n");

	fclose(fp);

	return insert_BIGN(header, data_number, input[0], input[1]);

}


// Check the format of string user enter
// If syntax is illegal, will return 1 vise versa.
int check_number(char *tmp)
{
	int j=0, len = strlen(tmp) - 1;
	// use (strlen(tmp)-1) is to avoid using isdigit("\0")
	for(j=0;j<len;j++) 
	{
		if(!isdigit(tmp[j])) return 1;
	}
	return 0;
}


// Reverse String before "\0"
void String_Reverse(char *s)// will change original string
{
     int len = strlen(s), i=0;
     char temp;

     for(i=0;i<len/2;i++)
     {
         temp=s[i];
         s[i]=s[len-i-1];
         s[len-i-1]=temp;
     }
}


// WARNING: will replace original string to SCIENTIFIC NOTATION string.
// Round the number to two decimal places.
// Accept that the length of number is smaller than 4.
char* trans_E(char *tmp)
{
	char prefix[10];
	// copy 0~4 number from tmp to prefix
	int i=0, len = strlen(tmp), exp = len - 1;
	int fix = (len<4)?len:4;// judge 
	float ten=1.0;

	for(i=0;i<fix-1;i++)
	{
		ten = ten*10;
	}

	for(i=0;i<fix;i++)
	{
		prefix[i] = tmp[i];
	}
	prefix[i] = '\0';

	sprintf(tmp, "%.2fe+%03d", atoi(prefix)/ten, exp);

	return tmp;
}


// Show the list of large number in Scientific Notation.
void show_list(BIGN *header)
{
	BIGN *ptr = header;
	char A[Max_Length], B[Max_Length];

	printf("Here is your records\n\n");

	while(ptr != NULL)
	{
		strcpy(A, ptr->a);
		strcpy(B, ptr->b);
		printf("No.%d : %s , %s\n", ptr->ID, trans_E(A), trans_E(B));
		ptr = ptr->next;
	}
}


void show_operator_list(void)
{
	printf("╔═════════════════════════════════════════╗\n");
	printf("║  Which operators do you want to choose? ║\n");
	printf("║  (+) Addition                           ║\n");
	printf("║  (-) Subtraction                        ║\n");
	printf("║  (*) Multiplication                     ║\n");
	printf("║  (/) Division(unfinished)               ║\n");
	printf("║  (q) Quit                               ║\n");
	printf("╚═════════════════════════════════════════╝\n");
}


BIGN *show_source_question(BIGN *header)
{
	int i=1;
	char c = '0', IDptr[10], input[2][Max_Length];
	BIGN *ptr = header;
	BIGN *current = NULL;

	printf("╔═════════════════════════════════════════╗\n");
	printf("║  Which items do you want to choose?     ║\n");
	printf("║  (1) Load the existing numbers by ID    ║\n");
	printf("║  (2) Input two numbers to calculate     ║\n");
	printf("║  (q) Quit                               ║\n");
	printf("╚═════════════════════════════════════════╝\n");

	scanf("\n%c", &c);// use "\n%c" to avoid read previous "\n" in stdin buffer

	switch(c)
	{
		case '1':

			if(file_on == 0)// global variable
			{
				printf("Must read csv file first!\n");
				return NULL;
			}

			printf("Please enter ID\n");
			scanf("%s", IDptr);

			while(ptr != NULL)
			{
				if(atoi(IDptr) == ptr->ID)
				{
					printf("Number 1:%s\nNumber 2:%s\n", ptr->a, ptr->b);
					return ptr;
				}

				ptr = ptr->next;
			}

			printf("The ID is not found !!\n");
			return NULL;

		case '2':

			for(i=1;i<=2;)
			{
				printf("Number %d :", i);
				scanf("%s", input[i-1]);

				if(check_number(input[i-1]))
				{
					fprintf(stderr, "Format Error !!\n");
					continue;
				}

				i++;// Continuously ask user number until get correct number in terms of format(make i++).
			}

			current = (BIGN*)malloc(sizeof(BIGN));
			current->ID = 0;
			strcpy(current->a, input[0]);
			strcpy(current->b, input[1]);
			current->next = NULL;

			return current;

		case 'q':
			return NULL;

		default:
			fprintf(stderr, "Please enter correct choice number !!\n");
			return NULL;
	}
}

// Choose the operator and record result in result.txt.
void operator(BIGN *header)
{
	char c;
	BIGN *ptr;
	char result[Max_Length];

	show_operator_list();

	while (getchar() != '\n')	c='0';// same way in main function

	c = getchar();

	switch(c)
	{
		case '+':
			if((ptr = show_source_question(header)) != NULL)
			{
				Plus(ptr, result);
			}
			break;

		case '-':
			if((ptr = show_source_question(header)) != NULL)
			{
				Subtraction(ptr, result);
			}
			break;

		case '*':
			if((ptr = show_source_question(header)) != NULL)
			{
				Multiplication(ptr, result);
			}
			break;

		case '/':
			break;

		case 'q':
			break;

		default:
			fprintf(stderr, "Please enter correct choice character !!\n");
			break;
	}

	FILE *fp=NULL;
	fp = fopen("result.txt","a");
	fprintf(fp,"%s\n",result);
}


// make sure "which string in a & b is larger?" and copy them into max & min with memecpy
// will make lengths of min & max same
// will fill zero in surplus places in min
void fill_zero(BIGN *ptr, char *max, char *min, int *MAX_MIN_len)
{
	int alen = strlen(ptr->a), blen = strlen(ptr->b);
	char *end = NULL;

	memcpy(max, alen>=blen?ptr->a:ptr->b, sizeof(char)*Max_Length);// warning '='
	memcpy(min, alen<blen?ptr->a:ptr->b, sizeof(char)*Max_Length);

	String_Reverse(max);
	String_Reverse(min);

	MAX_MIN_len[0] = strlen(max);
	MAX_MIN_len[1] = strlen(min);

	end = min + MAX_MIN_len[1];
	memset(end,'0',MAX_MIN_len[0] - MAX_MIN_len[1]);
}


// If there are "0" in the tail of result_int, removes it.
// Only used in Subtraction & Multiplication.
void remove_tail_zero(char *result, int *result_int)
{
	int i=0, result_len=0;

	// remove surplus zero in tail of result_int
	for(i=(Max_Length-1);i>=0;i--)
	{
		if(result_int[i]==0)
			continue;
		else
			result_len = i+1;
			break;
	}

	for(i=0;i<result_len;i++)
	{
		result[i] = result_int[i] + 48;// int to char
	}

	result[result_len] = '\0';
}

char* Plus(BIGN *ptr, char *result)// transfer "char array" into "int array" for plus operator
{
	int i=0, j=0, tmp=0, carry=0;
	int result_int[Max_Length], maxlen=0, MAX_MIN_len[2];
	char max[Max_Length], min[Max_Length];

	fill_zero(ptr, max, min, MAX_MIN_len);
	maxlen = MAX_MIN_len[0];

	memset(result_int, 0, sizeof(int)*Max_Length);

	for(i=0;i<maxlen;i++)
	{
		tmp = max[i] + min[i] - 48*2 + carry;// char to int P.S. ascii '0' is 48
		carry = tmp / 10;// the places of carry could be larger than 2
		result_int[i] = tmp % 10;
	}

	if(carry != 0)// in the condition that the places of 2 number are same.
	{
		result_int[maxlen] = carry;
		i++;
	}

	for(j=0;j<i;j++)
	{
		result[j] = result_int[j] + 48;// int to char
	}

	result[j] = '\0';
	String_Reverse(result);
	printf("Sum: %s\n", result);
	return result;
}


char* Subtraction(BIGN *ptr, char *result)
{
	int i=0, borrow=0;
	int result_int[Max_Length], maxlen=0, MAX_MIN_len[2];
	char max[Max_Length], min[Max_Length];

	fill_zero(ptr, max, min, MAX_MIN_len);
	maxlen = MAX_MIN_len[0];

	memset(result_int, 0, sizeof(int) * Max_Length);

	for(i=0;i<maxlen;i++)
	{
		result_int[i] = max[i] - min[i] - borrow;// char to int (max+48)-(min+48) = max- min

		if(result_int[i]<0)// need to borrow
		{
			borrow = 1;
			result_int[i] += 10;// borrow 10 from upper places
		}
		else
		{
			borrow = 0;
		}
	}

	remove_tail_zero(result, result_int);

	String_Reverse(result);
	printf("Diff: %s\n", result);
	return result;

}

char* Multiplication(BIGN *ptr, char *result)
{
	int i=0, j=0, k=0, carry=0;
	int result_int[Max_Length], maxlen=0, minlen=0, MAX_MIN_len[2];
	char max[Max_Length], min[Max_Length];

	fill_zero(ptr, max, min, MAX_MIN_len);
	maxlen = MAX_MIN_len[0];
	minlen = MAX_MIN_len[1];

	memset(result_int, 0, sizeof(int) * Max_Length);

	for(i=0;i<minlen;i++)
	{
		if(min[i]=='0') continue;

		for(j=0;j<maxlen;j++)
		{
			if(max[j]=='0') continue;
			result_int[i+j] += (min[i]-48)*(max[j]-48);
		}
	}

	for(k=0;k<Max_Length;k++)// carry all numbers in result_int 
	{
		result_int[k] += carry;// carry is 0 in first time
		carry = result_int[k]/10;
		result_int[k] %= 10;
	}
	
	// remove surplus zero in tail of result_int
	remove_tail_zero(result, result_int);

	String_Reverse(result);
	printf("Prod: %s\n", result);
	return result;
}
