#include "../main.h"
/**
 * tokenizer - it remove spaces from our argument
 * it brings user commands in an array
 * @ch: strings
 * Return: pointer to wordlist
 */
char **tokenizer(char *ch)
{
	int wordc = 0, i = 1, char_count = 0;
	char *word;
	char **wordlist, del[] = " ";

	if (ch == NULL)
		return (NULL);
	wordc = word_count(ch);
	wordlist = malloc(sizeof(char *) * (wordc + 1));
	if (wordlist == NULL)
		return (NULL);
	word = _strtok(ch, del);
	char_count = _strlen(word);
	*wordlist = malloc(sizeof(char) * char_count + 1);
	if (*wordlist == NULL)
	{
		free(wordlist);
		return (NULL);
	}
	fill_row(wordlist, 0, word);
	while (i < wordc)
	{
		word = _strtok(NULL, del);
		char_count = strlen(word);
		*(wordlist + i) = malloc(sizeof(char) * char_count + 1);
		if (*(wordlist + i) == NULL)
		{
			free_memory(wordlist, i);
			return (NULL);
		}
		fill_row(wordlist, i, word);
		i++;
	}
	wordlist[i] = NULL;
	return (wordlist);
}

/**
  * fill_row - fill worldlist pointer
  * put words in each rows
  * @wordlist: pointer
  * @row: wordlist pointer row
  * @word: content to fill
  */
void fill_row(char **wordlist, int row, char *word)
{
	int i = 0, j = 0;

	while (word[i] != 0)
	{
		if (word[i] != 10 && word[i] != 32)
		{
			wordlist[row][j] = word[i];
			j++;
		}
		i++;
	}
	wordlist[row][j] = '\0';
}
/**
 * str_cmp - two strings compared
 * @s1: the first string
 * @s2: the second string
 * Return: (1) if identical, (0) otherwise
 */
int str_cmp(char *s1, char *s2)
{
	int i = 0, j;

	while (s1[i] == 32 && s1[i] != 0)
		i++;
	for (j = 0; s1[i] != 0 && s2[j] != 0; i++, j++)
		if (s1[i] != s2[j])
			return (0);
	return (1);
}
/**
 * _strncpy - copies n bytes of src to dest
 * n should be smaller than strlen(dest)
 * if n is bigger than strlen(src)
 * write '\0' in each case after copying src
 * @dest: string receiving the copying
 * @src: string being copied
 * @n: number of bytes copied from src
 * Return: a pointer to the resulting string (dest)
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		if (src[i] != '\0')
			dest[i] = src[i];
		if (src[i] == '\0')
		{
			while (i < n)
			{
				dest[i] = '\0';
				i++;
			}
			break;
		}
	}
	return (dest);
}
/**
 * str_cmp_df - compares two strings
 * compare at char level
 * @s1: the first string
 * @s2: the second string
 * Return: (1) if identical, (0) otherwise
 */
int str_cmp_df(char *s1, char *s2)
{
	int difference = 0;

	if ((s1 == NULL || *s1 == 0) || (s2 == NULL || *s2 == 0))
		return (difference  + 1);
	while (*s1 != 0 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	difference = *(unsigned char *) s1 - *(unsigned char *) s2;
	return (difference);
}
/**
 * fill_string - fills a string
 * @dirname: the directory name
 * @command: command
 * @newcommand: newcommand
 * Return: the resulting string
 */
char *fill_string(char *dirname, char *command, char *newcommand)
{
	*newcommand = 0;
	print_string(dirname, newcommand);
	print_string("/", newcommand);
	print_string(command, newcommand);
	free(command);
	return (newcommand);
}
