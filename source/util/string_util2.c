#include "../main.h"

/**
 * print_decimal - adds an integer to the buffer
 * @n: the number to be printed
 * @buffer: buffer to append
 * Return: void
 */
void print_decimal(int n, char *buffer)
{
	unsigned int number;
	char curr_char;

	if (n < 0)
	{
		n = -n;
		addto_buff(buffer, '-');
	}

	number = (unsigned int) n / 10;
	if (number)
		print_decimal(number, buffer);
	curr_char = (unsigned int) n % 10 + 48;
	addto_buff(buffer, curr_char);
}
/**
 * addto_buff - adds a character to the end of the given buffer
 * @buffer: the buffer to append
 * @c: the character to add to the end of the given buffer
 * Return: (void)
 */
void addto_buff(char *buffer, char c)
{
	int len = __strlen(buffer);

	if (len == 0)
	{
		buffer[0] = c;
		buffer[1] = 0;
		return;
	}
	buffer[len] = c;
	buffer[len + 1] = 0;
}
/**
 * print_string - adds a string to the buffer
 * @string: the string to be added to buffer
 * @buffer: the string to be appended
 * Return: (void)
 */
void print_string(char *string, char *buffer)
{
	int i = 0;

	if (*string == 0)
		return;
	addto_buff(buffer, *string);
	i++;
	print_string(string + i, buffer);
}
/**
 * _atoi - converts a string to integer
 * @s: string to be converted
 * Return: the equivalent integer to s
 */

int _atoi(char *s)
{
	bool isnegative = false, hasnumbers = false;
	unsigned int i, integer = 0;

	for (i = 0; i < (unsigned int)__strlen(s); i++)
	{
		if (s[i] == '-')
		{
			if (!isnegative)
				isnegative = true;
			else
				isnegative = false;
		}
		while (s[i] >= 48 && s[i] <= 57)
		{
			hasnumbers = true;
			integer = integer * 10 + (s[i] - 48);
			i++;
		}
		if (hasnumbers)
			break;
	}
	if (!hasnumbers)
		return (0);

	else
	{
		if (isnegative)
			return (integer * (-1));
		else
			return (integer);
	}
}
/**
  * fill_row_logic - fill worldlist pointer with words
  * @wordlist: pointer
  * @row: wordlist pointer row
  * @word: content to fill
  */
void fill_row_logic(char **wordlist, int row, char *word)
{
	int i = 0, j = 0;

	while (word[i] == 32 || word[i] == '&' || word[i] == '|')
		i++;
	while (word[i] != 0)
	{
		if (word[i] != 10 && (word[i] != '&' || word[i] != '|'))
		{
			wordlist[row][j] = word[i];
			i++;
			j++;
		}
		else
			i++;
	}
	wordlist[row][i] = '\0';
}