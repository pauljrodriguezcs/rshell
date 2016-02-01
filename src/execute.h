#ifndef execute_h
#define execute_h
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include "object.h"

using namespace std;

bool execute(Object &temp, vector<string>&v){
    char * args[1024];
    bool success = true; //this will be function return value
    //obtain user command
    string cmd = temp.get_command();
    if(cmd == "exit"){ //checks for exit command
        //loop = false;
        //break;
        exit(1);
    }
    
    args [0] = (char*)cmd.c_str(); //place cmd at front of array
    
    
    //fill rest of array with arguments then null character
    unsigned i = 0;
    for(i = 0; i < v.size(); ++i){
        args[i+1] = (char*)v.at(i).c_str();
    }
    //add null character at end
    args [i+1] = '\0';
    
    
    //NOW EXECUTION TIME (ノಠ益ಠ)ノ
    pid_t pid = fork();
    
    if(pid == 0){
        //child
        if(execvp(args[0], args) == -1){
            perror ("exec");
            success = false;
        }
    }
    
    if(pid > 0){
        //parent
        if(wait(0) == -1){
            perror("wait");
            success = false;
        }
    }
    
    return success;
}

#endif