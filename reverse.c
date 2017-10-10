#include <stdio.h>
#include <stdlib.h>

char* reverse(char*);

int main()
{
	char* str = "he dsdsad dsad sad  lo";
	
	char* res = reverse(str);

	printf(res);
	printf("%c", '\n');
	
	return 0;
}

char* reverse(char* str)
{
	size_t* len = (size_t*) malloc(sizeof(size_t));
	*len = 0;
	for (char* c = str; *c != '\0'; ++c)
		++(*len);

	char* rev = (char*) malloc((*len + 1) * sizeof(char));
	size_t t = *len + 1;

	for (size_t i = 0, j = *len - 1; i < *len; )
		rev[i++] = str[j--];

	rev[*len] = '\0';

	free(len);

	return rev;
}
