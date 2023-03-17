#include <stdio.h>
/**
 * main - prints from 0 to 9
 * Return: Always 0 (Sucess)
 */
int main(void)
{
	int i;
	for (i = 0; i < 10; i++)
	{
		putchar('%d\n', i);
	}
	putchar('\n');
	return (0);
}
