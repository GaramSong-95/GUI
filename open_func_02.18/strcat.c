#include <stdio.h>
char * user_strcat(char *str1,const char *str2);
int main(int argc, char* argv[])
{
	char fruit[20] = "straw";
	printf("%p\n", "straw");
//	user_strcat(fruit, "berry");
	printf("연결된 문자열 : %s\n", user_strcat(fruit, "berry"));

	return 0;
}

#if 1
char * user_strcat(char* str1, const char* str2)
{
	char * temp = str1;
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
#endif

#if 0
char * user_strcat(char* str1, char* str2)
{
	char * temp = str1;
	int i;
	int j;
/*	while (str1[i] != '\0')
	{
		i++;
	}
	while (str2[j] != '\0')
	{
		str1[i] = str2[j];
		i++;
		j++;
	}
*/

	for (i = 0; str1[i] != '\0'; i++);
	for (j = 0; str2[j] != '\0'; i++, j++)
		str1[i] = str2[j];
	str1[i] = '\0';
	return temp;
}
#endif

