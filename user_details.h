#ifndef user_details_h
#define user_details_h

#include <stdio.h>
#include <iostream>
#include <unistd.h>

using namespace std;

void get_them_dets()
{
    char *user;
    char host[1024];
    host[1023] = '\0';
    gethostname(host, 1023);
    
    user = getlogin();
    
//    cout << "Your name is: ";
//    
//    for (int i = 0; user[i] != '\0'; ++i)
//    {
//        cout << user[i];
//    }
//    
//    cout << endl;
//    
//    cout << "Your hostname is: ";
//    
//    for (int i = 0; host[i] != '\0'; ++i)
//    {
//        cout << host[i];
//    }
//    
//    cout << endl;
//    
//    cout << "example bash will be:" << endl << endl;
    
    
    for (int i = 0; user[i] != '\0'; ++i)
    {
        cout << user[i];
    }
    
    cout << "@";
    
    for (int i = 0; host[i] != '\0'; ++i)
    {
        cout << host[i];
    }
    
    cout << "$" << endl << endl;
}

#endif