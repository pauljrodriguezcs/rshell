# RSHELL
Shell Terminal: This is a program that runs bash commands just like in the shell
terminal. Examples of these commands are "ls", "mkdir", "echo", "pwd", etc.

#Requirements
This version of the shell makes use of the boost library. The boost library will 
need to be installed on the host environment prior to running.

#Installation
To install and run rshell, follow these steps in a terminal:

1) git clone https://github.com/prodr010/rshell
2) cd rshell
3) git checkout hw2
4) make
5) bin/rshell

#Program Features
- Rshell supports most bash commands: "ls", "mkdir", "echo", etc.
- Rshell can also make use of connectors to run multiple commands in one line
    ";", "&&", and "||"
    - ";" the next command will always be executed
    - "&&" the next command will only execute if the previous command succeeds
    - "||"  the next command will only execute if the previous command failed
- Anything after the "#" will be considered a comment
- To exit Rshell, type in "exit"

#Known Bugs
- This program gets a hostname and a username from the host, both having a 1023 
  character maximum.
- Under some circumstances, if "exit" is the first command, it may not exit the
  shell properly.
- Rshell assumes user enters commands in a legal fashion like entering two "&&" 
  or "||"

