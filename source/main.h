#ifndef _MAIN_H_
#define _MAIN_H_
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stddef.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#define LEN 1256

/*Colors for prompt customization*/
#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"
#define DARK_WHITE "\x1B[38;5;250m"
#define BOLDBLACK   "\x1B[1;30m"
#define BOLDRED     "\x1B[1;31m"
#define BOLDGREEN   "\x1B[1;32m"
#define BOLDYELLOW  "\x1B[1;33m"
#define BOLDBLUE    "\x1B[1;34m"
#define BOLDMAGENTA "\x1B[1;35m"
#define BOLDCYAN    "\x1B[1;36m"
#define BOLDWHITE   "\x1B[1;37m"
#define BOLD_BRIGHT_BLACK "\x1B[1;90m"

/*global variables*/
extern char **environ;

/*Structures*/
/**
 * struct alloclist_s - a linked list containing memory addresses
 * to free after the program exits
 * @address: address to free
 * @next: pointer to the next element inn the list
 */
typedef struct alloclist_s
{
	void *address;
	struct alloclist_s *next;
} alloclist_t;

/**
 * struct path_s - defines a linked list containis all the directories
 * contained within the PATH environment variable
 * @name: the name of the directory
 * @next: a pointer to the next directory in the PATH
 */
typedef struct path_s
{
	char *name;
	struct path_s *next;
} path_t;
/**
 * struct builtin_s - defines a builtin element
 * @cmdname: builtin name
 * @func: the assossiated function
 */
typedef struct builtin_s
{
	char *cmdname;
	int (*func)(char *buffer, alloclist_t **head, path_t **path);
} builtin_t;

/*Function Declarations*/

/*Count functions*/
int line_counter(char *str);
int _strlen(char *buffer);
int __strlen(char *buffer);
int word_count(char *str);
int _strlentok(char *str);
int string_count(char **env);
int cmd_counter(char *str);
int logic_counter(char *str);
int equal_check(char *str);

/*Memory management functions*/
void free_memory(char **pointer, int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_env(char **environ, int n);
void free_everything(alloclist_t **head);
void ultimate_free(path_t **path, alloclist_t **head, char *buffer);
void free_pathlist(path_t **head);
void *_calloc(unsigned int nmemb, unsigned int size);

/*Check functions*/
int space_check(char *buffer);
int alpha_check(char *str);
int logic_check(char *str);
int semicolon_check(char *str);
int file_exist_exec(char *command);

/*Error handler functions*/
void error_handler(char *argv, char *command, int counter, int option);
void arg_err(char **argv, int option, char **command, int line);
void exit_arg_err(char *argv, char **command, int option);
void cd_err(char **command, char *argv, int wordc);

/*Alloclist functions*/
alloclist_t *alloclist_init(void);
alloclist_t *add_node_end(alloclist_t **head, void *address);

/*Setter and getter functions*/
void set_entry(char *buffer, char *name, char *value);
void var_set(char *buffer, int *check, char ***command);
void replacer(alloclist_t **head, char *buff3, char **command, int wordc);
void initializer(char *buffer, int *cmdc, int *check, char *del);
int get_del(char *buffer);
void set_delimiter(int check, char *del);

/*Command execution functions*/
int exec_handl(int check, char **cmd, char *argv, path_t **p, int wdc, int c);
void executor(char **command);
int logicexecutor(char **command);
int lexec_handl(int check, char **cmd, char *argv, path_t **p, int wdc, int c);

/*Multiple and logically connected commands functions*/
char **logictok(char *ch, char *del);
void multicmd_hand(char *buffer, char *argv, path_t **p, alloclist_t **head);
void logic_hand(char *buffer, char *argv, path_t **p, alloclist_t **head);

/*Tokenizer and string functions*/
char **tokenizer(char *ch);
void fill_row(char **wordlist, int row, char *word);
char *_memcpy(char *src, char *dest, unsigned int n);
void print_string(char *string, char *buffer);
void addto_buff(char *buffer, char c);
int str_cmp(char *s1, char *s2);
void print_decimal(int n, char *buffer);
int _atoi(char *s);
char *_strncpy(char *dest, char *src, int n);
char **commandtok(char *ch, char *del);
char *filetobuff(char **argv, alloclist_t **head);
void fill_row_def(char **wordlist, int row, char *word);
int str_cmp_df(char *s1, char *s2);
char *fill_string(char *dirname, char *command, char *newcommand);
char **cmdtok(char *ch);
void fill_row_cmd(char **wordlist, int row, char *word);
char *_strtok(char *str, char *delimiter);
void fill_row_logic(char **wordlist, int row, char *word);

/*Prompt handling functions*/
void prompt_handl(void);

/*Signal handler functions*/
void sigint_handler(int sig);

/*mode handler functions*/
void interactive_mode(char *argv);
void argument_mode(char **argv);
void noninteractive_mode(FILE *file, char **argv);

/*built-in handler functions*/
int (*bltn_chck(char *buff))(char *buffer, alloclist_t **head, path_t **path);
int exit_handler(char *buffer, alloclist_t **head, path_t **path);
int env_handler(char *buffer, alloclist_t **head, path_t **path);
int emptycmd_handler(char *buffer, alloclist_t **head, path_t **path);
int setenv_handler(char *buffer, alloclist_t **head, path_t **path);
int unsetenv_handler(char *buffer, alloclist_t **head, path_t **path);
int cd_handler(char *buffer, alloclist_t **head, path_t **path);
int _setenv(char *name, char *value, alloclist_t **head);
int _unsetenv(char *name, alloclist_t **head);

/*PATH handler functions*/
char *_getenv(const char *name);
path_t *add_node_end_path(path_t **head, char *dirname);
int executable_locator(path_t **head, char **command);
path_t *path_creator(path_t **head);

#endif
