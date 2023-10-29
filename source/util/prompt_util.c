#include "../main.h"

/**
 * prompt_handl - handles the prompt printing
 * Return: (void)
 */
void prompt_handl(void)
{
	char prompt[512] = "", placeholder[256] = "", *ptr;
	char buffer[] = "currentuser";
	int i = 0, check = 0;

	print_string(BOLDCYAN, prompt);
	ptr = getenv("USER");
	if (ptr == 0 || *ptr == 0)
	{
		ptr = getenv("USERNAME");
		if (ptr == 0 || *ptr == 0)
			ptr = getenv("LOGNAME");
		if (ptr == 0 || *ptr == 0)
			ptr = buffer;
	}
	print_string(ptr, prompt);
	if (str_cmp_df(getenv("USER"), "root") == 0)
		check++;
	print_string("@", prompt);
	ptr = getenv("SESSION_MANAGER");
	if (ptr != 0)
	{
		print_string(ptr + 6, placeholder);
		while (placeholder[i] != 0)
		{
			if (placeholder[i] == ':')
				placeholder[i] = 0;
			i++;
		}
	}
	else
		print_string("currentmachine", placeholder);
	print_string(placeholder, prompt);
	addto_buff(prompt, ':');
	print_string(RESET, prompt);
	print_string(BOLDRED, prompt);
	ptr = getenv("PWD");
	if (ptr != 0)
		print_string(ptr, prompt);
	print_string(BOLDWHITE, prompt);
	if (check)
		print_string("# ", prompt);
	else
		print_string("$ ", prompt);
	print_string(BOLD_BRIGHT_BLACK, prompt);
	write(1, prompt, __strlen(prompt));
}