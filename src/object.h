#ifndef object_h
#define object_h

#include <iostream>
#include <vector>

using namespace std;

class Object {
protected:
    string type;
    string command;
    vector<string> args;
public:
    
    Object(string type, string command, vector<string> args)
    : type(type), command(command), args(args) {}
    
    string get_type()
    {
        return type;
    }
    
    string get_command()
    {
        return command;
    }
    
    //char get_args()
    //{
    //   int pos = 0;
    //   char arguments[1024];
    
    //    for (int i = 0; i < args.size(); ++i)
    //    {
    //        for (int j = 0; j < args.at(i).size(); ++j,++pos)
    //        {
    //            arguments[pos] = args.at(i).at(j);
    //        }
    //
    //        arguments[pos] = ' ';
    //        ++pos;
    //    }
    
    //    arguments[pos] = '\0';
    
    //    return arguments;
    //}
};

#endif