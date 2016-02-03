#include "execute.h"
#include "object.h"
//#include "struct.h"
//#include "user_details.h"
#include <iostream>
#include <vector>
#include <string>
#include <boost/tokenizer.hpp> //needed for tokenizer
#include <stdlib.h>
using namespace std;


int main(){
    bool loop = true;   //bool for loop
    bool status = false; //current status of commands
    string user_input;
    
    while(loop){
        
        //data
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
        
        //command prompt
        cout << "$ ";
        
        //read in user input
        getline(cin, user_input);
        
        //test
        //cout << "user input is " << user_input << endl;
        //check for exit
        if(user_input == "exit" || user_input  == "Exit"){
            //cout << "first exit called" << endl;
            break; //exit program
            break;
            break;
            
        }
        
        //tokenize user input
        //tokenizer tok{user_input};
        tokenizer tok(user_input);
        vector<string>temp(1); //needed for conversion to allow for comparisons
        tokenizer::iterator it = tok.begin(); //iterator for tokenizor
        string type; // n = first or after semicolon, o OR, a AND
        
        while(it != tok.end()){ //once end of user input reached exit loop
            string user_cmd; //string to store command temporarily
            vector<string> user_args; //vector to temp store arguments
            
            //copies first token of new loop to string for comparisons
            temp.at(0) = *it;
            string temp2 = temp.at(0);
            //checks if exit command entered
            if(temp2 == "exit"){ //checks for exit command assume to be first
                //loop = false;
                //break;          //exit main loop end program
                exit(0);
            }
            
            //now checks type and obtains command
            if(temp2 == "|"){
                type = 'o'; //type OR
                ++it; //update iterator to command
                ++it;
                temp.at(0) = *it;
                user_cmd = temp.at(0); //copy cmd to string
            }
            else if(temp2 == "&"){
                type = 'a'; //type AND
                ++it; //update iterator to command
                ++it;
                temp.at(0) = *it;
                user_cmd = temp.at(0); //copy cmd to string
            }
            else if(temp2 == ";"){ // semicolon command
                type = 'n';
                ++it; //update iterator to command
                //++it;
                temp.at(0) = *it;
                user_cmd = temp.at(0); //copy cmd to string
            }
            //else if(temp2 == "exit"){ //checks for exit command
            //loop = false;
            //break;          //exit main loop end program
            // exit(0);
            //}
            else{ //first command
                type = 'n';
                //don't update iterator already at command
                user_cmd = temp.at(0); //copy cmd to string
            }
            
            //now check if at end of user input or single length command EX: ls
            bool do_not_skip = true; // jump passed next section if necesary
            
            //check for exit command
            //if(user_cmd == "exit"){ //checks for exit command
            //loop = false;
            //break;
            //  exit(1);
            //}
            
            //update iterator here
            //if(temp2 != ";"){ //if semicolon don't update it
            //  ++it;
            //}
            
            //now check if single length command
            ++it;
            if(it != tok.end()){ //make sure nt=ot end of it
                temp.at(0) = *it;
                string temp3 = temp.at(0);
                //check if at end of single length command
                if(temp3 == "|" || temp3 == "&" || temp3 == ";"){
                    do_not_skip = false; // skip next section
                }
                else{
                    do_not_skip = true; //not single don't skip
                }
            }
            
            
            
            
            if(it == tok.end()){ //end of user input
                do_not_skip = false; //skip next section
            }
            else{//is safe to update iterator
                //++it;
                temp.at(0) = *it;
                temp2 = temp.at(0);
            }
            
            //check if at end of single length command
            if(temp2 == "|" || temp2 == "&" || temp2 == ";"){
                do_not_skip = false; //skip next section
            }
            
            //if skip still false then arguments and or comments exist
            while(do_not_skip){
                //cout << "temp2 above comment is " << temp2 << endl;
                if(temp2 == "#"){ //comment reached
                    string comment = "";
                    bool comment_loop = true;
                    //while(comment != "|" || comment != "&" || comment != ";"){ //note line longer than 80
                    while(comment_loop){
                        ++it; //update iterator till end of comment
                        
                        if(it == tok.end()){
                            do_not_skip = false;
                            comment_loop = false;
                            break;
                        }
                        else{
                            temp.at(0) = *it;
                            comment = temp.at(0);
                            if(comment == ";"){
                                do_not_skip = false;
                                comment_loop = false;
                                break;
                            }
                            if(comment == "&"){
                                do_not_skip = false;
                                comment_loop = false;
                                break;
                            }
                            if(comment == "|"){
                                do_not_skip = false;
                                comment_loop = false;
                                break;
                            }
                            
                        }
                        //cout << "comment is " << *it << " " << endl;
                        
                    }
                    do_not_skip = false;
                }
                
                else{
                    //command
                    user_args.push_back(temp2); //push user argument
                    
                    //check updated iterator
                    ++it;
                    if(it == tok.end()){
                        do_not_skip = false;
                    }
                    else{
                        temp.at(0) = *it;       //update temp2 string
                        temp2 = temp.at(0);
                        if(temp2 == "&"){
                            do_not_skip = false;
                        }
                        if(temp2 == "|"){
                            do_not_skip = false;
                        }
                        if(temp2 == ";"){
                            do_not_skip = false;
                        }
                    }//if it makes it this far then next string # or argument
                }
            }
            //arguments vector now ready
            //create struct type data
            //command_obj(string cmd, vector<string>arguments, char type);
            Object temp_obj(type, user_cmd, user_args);
            //cout << "user command " << user_cmd << endl;;
            //for(unsigned i = 0; i < user_args.size(); ++i){
            
            //  cout << user_args.at(i) << " ";
            //}
            //cout << endl;
            //cout << "type = " << type << endl;
            //now create abject class type data
            //call execute function if necessary
            //repeat loop
            
            //now execute time
            if(type == "n"){ //either first or ; command
                //execute no matter what status is currently
                if(user_cmd == "exit"){ //checks for exit command
                    //loop = false;
                    //break;
                    exit(0);
                }
                status = execute(temp_obj, user_args);
                //bool function that also executes commands
                
            }
            else if(type == "a"){ //AND command
                if(status){ //if status good execute
                    //execute no matter what status is currently
                    if(user_cmd == "exit"){ //checks for exit command
                        exit(0);
                    }
                    status = execute(temp_obj, user_args);
                    //executes and sets new status
                }
                //else do nothing and skip execution
            }
            else if(type == "o"){ //OR command
                if(status == false){ //OR only goes if staus bad
                    //execute no matter what status is currently
                    if(user_cmd == "exit"){ //checks for exit command
                        //loop = false;
                        //break;
                        exit(0);
                    }
                    status = execute(temp_obj, user_args);
                    //executes and sets new status
                }
                //if status good do not execute and ski
            }
            
            
            
        }
        
    }
    return 0;
}