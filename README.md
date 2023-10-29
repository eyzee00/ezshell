# ezshell: An Improved version of simple_shell
My take on how to implement a simple Shell using the C programming language. using only a few syscalls and standard Unix C functions, I've been able to pretty much simulate the functionality of the "SH" shell present in the /bin directory. Managing memory manually was tough, to say the least, but I've managed to get the shell running without memory leaks, and made sure to handle kill and interupt signals properly, and free memory when necessary.
The ezshell can execute simple commands, multiple commands and logically connected commands, pipes are still in development for now. The user can interact with the shell throught 3 different modes:
 
**1-Interactive mode**:Your usual shell experience, the ezshell displays a prompt containing relevant information like the current user name, the path to the current directory and the user's privelges('$' for a normal user, '#' for superuser), and waits for input. The shell processes the command and executes it if written correctly, in case of failure, an error message is written to the standard error.

**2-Non-Interative Mode**: The ezshell always checks if input was written to its standard input before it was called, for example you can use echo and redirect its output using a pipe to ezshell standard input, like: *****(echo "ls -l -a --color=auto" | ./ezshell)*****, the ezshell will execute the command written in it's standard input *(ls -l -a --color=auto)*, and exit without displaying a prompt.

**3-File mode**: The ezshell can take a file as an argument, this file can contain simple or multiple commands. The shell interprets each line as a command and executes it. Similarly to The Non-Interactive Mode, the ezshell won't display a prompt and exits directly after executing all the commands in the file.

**Important: Mode priority**: The ezshell checks if a file was passed to it first, if no argument *(file)* is passed to the shell when you call it, it checks if input is already present in stdin *(through piping for example)*, else, it displays a prompt and waits for commands from the user.
