
#include <stdio.h>

int main()
{
	int i = 0;
	char s[] = "Hello \0World!";
	while (i < 10)
	{
		printf("%c", s[i]);
		i++;
	}
}