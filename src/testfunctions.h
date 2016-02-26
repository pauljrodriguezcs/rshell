#ifndef testfunctions_h
#define testfunctions_h

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <vector>

using namespace std;

//-e command tests if file/directory exist
bool fileExists(const string &file){
    struct stat buf;
    //return true if file/directory exist
    return (stat(file.c_str(), &buf) == 0); 
}


//-d test if directory exists
bool directory(const string &file){
    bool cur_stat = true;
    struct stat buf;
    if(stat(file.c_str(), &buf) == -1) {
        //perror("stat");
        cur_stat = false;
        cout << "(FALSE)" << endl;
    }
    
    else{
        
        switch (buf.st_mode & S_IFMT){
        case S_IFDIR:  cout << "(TRUE)" << endl; break;  
        default: cur_stat = false; cout << "(FALSE)" << endl; break;
        }

    }
    return cur_stat;
}


//-f test if regular file exist
bool reg_file(const string & file){
     bool cur_stat = true;
    struct stat buf;
    if(stat(file.c_str(), &buf) == -1){
        //perror("stat");
        cur_stat = false;
        cout << "(FALSE)" << endl;
    }
    
    else{
        
        switch (buf.st_mode & S_IFMT){
        case S_IFREG: cout << "(TRUE)" << endl; break;
        default: cur_stat =false; cout << "(FALSE)" << endl; break;
        }

    }
    
    return cur_stat;
}

#endif