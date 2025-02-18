#include <stdio.h>


char *user_strcat(char *str1, char *str2);

int main(void)
{
	char fruit[80]="straw";
	
	printf("연결된 문자열 : %s\n", user_strcat(fruit, "berry"));
	printf("연결된 문자열 : %s\n", fruit);
	return 0;
}

char* user_strcat(char *str1, char *str2)
{
   /*
	int i = 0;
	int j = 0;

	for (;;)
	{
		if (*(str1 + i) == '\0') break;
		i++;
	}

	for (;;)
	{
		*(str1 + i) = *(str2 + j);
		i++;
		j++;
		if (*(str2 + j) == '\0') break;
	}

	return str1;
	*/
	char* temp = str1;

	while (*str1 != '\0')
	{
		str1++;
	}
	while (*str2 != '\0')
	{
		*str1 = *str2;
		str1++;
		str2++;
	}
	*str1 = '\0';

	return temp;
}