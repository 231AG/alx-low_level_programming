#include "main.h"


/**
*_memset - Fills a memory space with constant byte
*@n: first fills n
*@s: point to s
*@b: b is constant byte
*Return: Always Success
*/

char *_memset(char *s, char b, unsigned int n)
{
	while (n)
	{
		s[n - 1] = b;
		n--;
	}
	return (s);
}
