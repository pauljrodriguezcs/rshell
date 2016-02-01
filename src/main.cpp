#include "execute.h"
#include "object.h"
#include "struct.h"
#include <iostream> 
#include <vector>
#include <string>
#include <boost/tokenizer.hpp> //needed for tokenizer
using namespace std;


int main(){
    bool loop = true;   //bool for loop
    bool status = false; //current status of commands
    
    while(loop){    
        
        //data
        typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
        
        //command prompt
        cout << "$ "; 
        
        //read in user input
        getline(cin, user_input);
        
        //tokenize user input
        tokenizer tok{user_input};
        
        vector<string>temp(1); //needed for conversion to allow for comparisons
        tokenizer::iterator it = tok.begin(); //iterator for tokenizor
        char type; // n = first or after semicolon, o OR, a AND
        
        while(it != tok.end()){ //once end of user input reached exit loop
            string user_cmd; //string to store command temporarily
            vector<string> user_args; //vector to temp store arguments
            
            //copies first token of new loop to string for comparisons
            temp.at(0) = *it;
            string temp2 = temp.at(0);
            
            //checks if exit command entered
            if(temp2 == "exit"){ //checks for exit command assume to be first 
                loop = false;
                break;          //exit main loop end program
            }
            
            //now checks type and obtains command
            if(temp2 == "|"){
                type = 'o'; //type OR
                ++it; //update iterator to command
                temp.at(0) = *it;
                user_cmd = temp.at(0); //copy cmd to string
            }
            else if(temp2 == "&"){
                type = 'a'; //type AND
                ++it; //update iterator to command
                temp.at(0) = *it;
                user_cmd = temp.at(0); //copy cmd to string
            }
            else{ //either first or semicolon command
                type = 'n'; 
                //don't update iterator already at command
                user_cmd = temp.at(0); //copy cmd to string
            }
            
            //now check if at end of user input or single length command EX: ls
            bool skip = false; // jump passed next section if necesary 
            
            if(it != tok.end()){ //end of user input
                skip = true; //skip next section 
            }
            
            ++it; //is safe to update iterator
            temp.at(0) = *it;
            temp2 = temp.at(0);
            
            //check if at end of single length command
            if(temp2 == '|' || temp2 == "&" || temp2 == ";"){
                skip = true; //skip next section
            }
            
            //if skip still false then arguments and or comments exist
            while(skip == false){
                if(temp2 == "#"){ //comment reached
                    while(temp2 != '|' || temp2 != "&" || temp2 != ";" || it != tok.end()){ //note line longer than 80
                        ++it; //update iterator till end of comment
                        temp.at(0) = *it;
                        temp2 = temp.at(0);
                        skip = true;
                    }
                }
          
                else{
                    //command 
                    user_args.push_back(temp2); //push user argument
                    
                    //check updated iterator
                    ++it;
                    if(it == tok.end()){
                        skip = true;
                    }
                    else{
                        temp.at(0) = *it;       //update temp2 string
                        temp2 = temp.at(0);
                        if(temp2 == "&"){
                            skip = true;
                        }
                        if(temp2 == "|"){
                            skip = true;
                        }
                        if(temp2 == ";"){
                            skip = true;
                        }
                    }//if it makes it this far then next string # or argument
                }
            }
            
            //arguments vector now ready 
            //create struct type data
            //command_obj(string cmd, vector<string>arguments, char type)
            command_obj temp_obj(user_cmd, user_args, type);
            
            //now create abject class type data
            //call execute function if necessary 
            //repeat loop
            
        }
        
    }
    return 0;
}