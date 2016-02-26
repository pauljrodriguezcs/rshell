#include "execute.h"
#include "object.h"
#include "testfunctions.h"
#include "user_details.h"
#include "parenth.h"
#include <iostream> 
#include <vector>
#include <string>
#include <boost/tokenizer.hpp> //needed for tokenizer
#include <stdlib.h>
#include <cstdlib>
using namespace std;


int main(){
    bool loop = true;   //bool for loop
    //bool status = false; //current status of commands
    string user_input;
    
    while(loop){ 
        
        //set both skips to false
        bool superskip = false;
        bool superskip2 = false;
        bool status = false; //current status of commands
         
        //data
        typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
        
        //command prompt
        cout << "$ "; 
        //get_them_dets();
        
        //read in user input
        getline(cin, user_input);
        
        //tokenize user input
        //tokenizer tok{user_input};
        tokenizer tok(user_input);
        vector<string>temp(1); //needed for conversion to allow for comparisons
        tokenizer::iterator it = tok.begin(); //iterator for tokenizor
        string type; // n = first or after semicolon, o OR, a AND
        
        //test
        //cout << "user input is " << user_input << endl;
        //check for exit
        if(user_input == "exit" || user_input  == "Exit"){
            //cout << "first exit called" << endl;
            status = false;
            //cout << "in exit" << endl;
            it = tok.end();
			cout << endl;
		    break;
            return 0;
            
        }
        
        
        while(it != tok.end()){ //once end of user input reached exit loop
            superskip = false;
            superskip2 = false;
            
            string user_cmd; //string to store command temporarily
            vector<string> user_args; //vector to temp store arguments
            
            //copies first token of new loop to string for comparisons
            temp.at(0) = *it;
            string temp2 = temp.at(0);
            //checks if exit command entered
            if(temp2 == "exit"){ //checks for exit command assume to be first 
                //loop = false;
                //break;          //exit main loop end program
                //exit(0);
                return 0;
            }
            
            //checks if first input is parenthesis
            if(temp2 == "("){
                //execute everything in parenthesis first
                status = parenthesis_detect(it, tok);
                superskip = true;
            }
            
            if(superskip != true){
            //now checks type and obtains command
            
            if(temp2 == "|"){
                type = 'o'; //type OR
                ++it; //update iterator to command
                ++it;
                temp.at(0) = *it;
                user_cmd = temp.at(0); //copy cmd to string
                
                //check for parenthesesis if status true skip all 
                if(status == true && user_cmd == "("){ // skip to end of parenthesis
                   //call skip function pass in iterator and tok
            
                   orskip(it, tok);
                   superskip2 = true;
                   //cout << "out of orskip" << endl;
                   //cout << *it << endl;
                }
                
                if(status == false && user_cmd == "("){
                //call parentheses execute function
                    status = parenthesis_detect(it, tok);
                    superskip2 = true;
                }
            }
            else if(temp2 == "&"){
                type = 'a'; //type AND
                ++it; //update iterator to command
                ++it;
                temp.at(0) = *it;
                user_cmd = temp.at(0); //copy cmd to string
                //cout << "user command is " << user_cmd << endl;
                if(status == false && user_cmd == "("){ // skip to end of parenthesis
                   //call skip function pass in iterator and tok
            
                   orskip(it, tok);
                   superskip2 = true;
                   //cout << "out of orskip" << endl;
                   //cout << *it << endl;
                }
                
                if(status == true && user_cmd == "("){
                //call parentheses execute function
                    status = parenthesis_detect(it, tok);
                    superskip2 = true;
                }

            }
            else if(temp2 == ";"){ // semicolon command
                type = 'n'; 
                ++it; //update iterator to command
                //++it;
                //bug fix
                if(it != tok.end()){
                    temp.at(0) = *it;
                    user_cmd = temp.at(0); //copy cmd to string
                    if(user_cmd == "("){
                        //call parentheses execute function
                        status = parenthesis_detect(it, tok);
                        superskip2 = true;
                    }
                }
                //fixes bug with comments
                else{
                    superskip2 = true;
                }
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
                if(user_cmd == "("){
                    //call parentheses execute function
                    status = parenthesis_detect(it, tok);
                    superskip2 = true;
                }
            }
           
            // put or skip here assn3
            if(superskip2 == false){
           
           //cout << "user_cmd is " << user_cmd << endl;
            //now check if at end of user input or single length command EX: ls
            bool do_not_skip = true; // jump passed next section if necesary 
            
            
            ++it;
            if(it != tok.end()){ //make sure nt=ot end of it
                temp.at(0) = *it;
                string temp3 = temp.at(0);
                //check if at end of single length command
                //added for assn 3
                if(temp3 == "|" || temp3 == "&" || temp3 == ";"){
                    //added assn3
                    //if(temp3 == "]"){
                       // ++it;
                    //}
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
            //added for assn3
            if(temp2 == "|" || temp2 == "&" || temp2 == ";"){
                //added assn3
                //if(temp2 == "]"){
                  //  ++it;
                //} 
                do_not_skip = false; //skip next section
            }
    
            //if skip still false then arguments and or comments exist
            while(do_not_skip){
                //cout << "temp2 above comment is " << temp2 << endl;
                if(temp2 == "#"){ //comment reached
                    string comment = "";
                    bool comment_loop = true;
                    
                    while(comment_loop){
                        ++it; //update iterator till end of comment
                        
                        if(it == tok.end()){
                            do_not_skip = false;
                            comment_loop = false;
                            //break;
                        }
                        //looks for end of comment
                        else{
                            temp.at(0) = *it;
                            comment = temp.at(0);
                            if(comment == ";"){
                                do_not_skip = false;
                                comment_loop = false;
                                //break;
                            }
                            if(comment == "&"){
                                do_not_skip = false;
                                comment_loop = false;
                                //break;
                            }
                            if(comment == "|"){
                                do_not_skip = false;
                                comment_loop = false;
                                //break;
                            }
                            //added for assn3
                            //if(comment == "]"){
                                //added assn3;
                              //  ++it;
                                //do_not_skip = false;
                                //comment_loop = false;
                                //break;
                            //}
                            
                        }
                        //cout << "comment is " << *it << " " << endl;
                    
                    }
                    do_not_skip = false;
                }
          
                else{
                    //command 
                    //check if temp2 is "-"
                    
                    if(temp2 == "-"){
                        ++it;
                        if(it != tok.end()){
                            string tempVal; 
                            temp.at(0) = *it;
                            tempVal = temp.at(0);
                            temp2 = temp2 + tempVal; //string addition 
                        }
                    }
                    
                    //checks for symbols and adds then to string
                    if(temp2 == "/" || temp2 == "." || temp2 == "_" || temp2 == "\\"){
                        //added assn3
                        if(it != tok.end() || temp2!= "&" || temp2 != "|" || temp2 != ";"){
                            bool skip_next = true;
                            string temp_s;
                            if(user_args.size() >= 1){
                                int loc = user_args.size() -1; //need prev string
                                temp_s = user_args.at(loc);
                                //just added
                                //cout << "temp_s = " << temp_s << endl;
                                if(temp_s == "-e" || temp_s == "-d" || temp_s == "-f"){
                                    //skip if one of these before
                                    //cout << "went into skip" << endl;
                                    skip_next = false;
                                }
                                else{
                                    temp_s = temp_s + temp2;
                                }
                                
                            }
                            if(skip_next){
                                ++it;
                                if(it!= tok.end()){
                                    string tempVal;
                                    temp.at(0) = *it;
                                    tempVal = temp.at(0);
                                    //cout << "tempVal = " << tempVal << endl;
                                    //added assn3
                                    if(tempVal != "&" || tempVal != "|" || tempVal != ";"){
                                        temp_s = temp_s + tempVal;
                                    }
                                }
                            }
                            
                            if(user_args.size() >= 1){
                                user_args.pop_back(); //rmove old string
                                
                            }
                            temp2 = temp_s;
                        }
                        
                    }
                    
                    //cout << "temp2 = " << temp2 << endl;
                    user_args.push_back(temp2); //push user argument
                   // cout << "user_cmd is " << user_cmd << endl;
                    //for(unsigned i = 0; i < user_args.size(); ++i){
                    //    cout << "argument " << i << " is " << user_args.at(i) << endl;
                    //}
                    
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
                        //added assn3
                        //if(temp2 == "]"){
                          //  do_not_skip = false;
                        //}
                    }//if it makes it this far then next string # or argument
                }
            }
            //arguments vector now ready 
            //cout << "the user command is " << user_cmd << endl;
            Object temp_obj(type, user_cmd, user_args);
            
            //now execute time
            if(type == "n"){ //either first or ; command
                
                //execute no matter what status is currently
                if(user_cmd == "exit"){ //checks for exit command
                    //loop = false;
                    //break;
                    //exit(0);
                    return 0;
                }
                if(user_cmd != "test" || user_cmd != "["){
                    status = execute(temp_obj, user_args);
                    //bool function that also executes commands
                }
                
                if(user_cmd == "test" || user_cmd == "["){
            
                    //test if file / directory exist
                    if(user_args.size() != 0){
                        if(user_args.at(0) == "-e"){
                            //cout << "ok -e" << endl;
                            if(user_args.size() >= 2){
                                string file = user_args.at(1);
                                //whole next command will be path
                                status = fileExists(file);
                                if(status){
                                    cout << "(TRUE)" << endl;
                                }
                                else{
                                    cout << "(FALSE)" << endl;
                                }
                            }
                        }
                        //test if regular file
                        else if(user_args.at(0) == "-f"){
                            //cout << "ok -f" << endl;
                            if(user_args.size() >= 2){
                                string file = user_args.at(1);
                                //whole next command will be path
                                status = reg_file(file);
                            }
                        }
                        
                        //test if is directory
                        else if(user_args.at(0) == "-d"){
                            //cout << "ok -d" << endl;
                            if(user_args.size() >= 2){
                                string file = user_args.at(1);
                                //whole next command will be path
                                status = directory(file);
                            }
                        }
                        else{
                            //default test if file / directory exist
                            //cout << "ok -e" << endl;
                            if(user_args.size() >= 1){
                                string file = user_args.at(0);
                                //whole next command will be path
                                status = fileExists(file);
                                if(status){
                                    cout << "(TRUE)" << endl;
                                }
                                else{
                                    cout << "(FALSE)" << endl;
                                }
                            }
                        }
                        
                    }
                }
            
        
                
            }
            else if(type == "a"){ //AND command
                if(status){ //if status good execute
                    //execute no matter what status is currently
                    if(user_cmd == "exit"){ //checks for exit command
                        //exit(0);
                        return 0;
                    }
                    if(user_cmd != "test" || user_cmd != "["){
                        status = execute(temp_obj, user_args);
                        //bool function that also executes commands
                    }
                
                if(user_cmd == "test" || user_cmd == "["){
            
                    if(user_args.size() != 0){
                        //test if file / directory exist
                        if(user_args.at(0) == "-e"){
                        //    cout << "ok -e" << endl;
                            if(user_args.size() >= 2){
                                string file = user_args.at(1);
                                //whole next command will be path
                                status = fileExists(file);
                                if(status){
                                    cout << "(TRUE)" << endl;
                                }
                                else{
                                    cout << "(FALSE)" << endl;
                                }
                            }
                        }
                        //test if regular file
                        else if(user_args.at(0) == "-f"){
                          //  cout << "ok -f" << endl;
                            if(user_args.size() >= 2){
                                string file = user_args.at(1);
                                //whole next command will be path
                                status = reg_file(file);
                            }
                        }
                        //test if directory
                        else if(user_args.at(0) == "-d"){
                            //cout << "ok -d" << endl;
                            if(user_args.size() >= 2){
                                string file = user_args.at(1);
                                //whole next command will be path
                                status = directory(file);
                            }
                        }
                        else{
                            //test if file / directory exist
                            //cout << "ok -e" << endl;
                            if(user_args.size() >= 1){
                                string file = user_args.at(0);
                                //whole next command will be path
                                status = fileExists(file);
                                if(status){
                                    cout << "(TRUE)" << endl;
                                }
                                else{
                                    cout << "(FALSE)" << endl;
                                }
                            }
                        }
                        
                    }
                }
                }
                //else do nothing and skip execution
            }
            else if(type == "o"){ //OR command
                if(status == false){ //OR only goes if staus bad
                    //execute no matter what status is currently
                    if(user_cmd == "exit"){ //checks for exit command
                        //loop = false;
                        //break;
                        //exit(0);
                        return 0;
                    }
                    if(user_cmd != "test" || user_cmd != "["){
                    status = execute(temp_obj, user_args);
                    //bool function that also executes commands
                }
                
                    if(user_cmd == "test" || user_cmd == "["){
            
                        if(user_args.size() != 0){
                            //test if file / directory exist
                            if(user_args.at(0) == "-e"){
                              //  cout << "ok -e" << endl;
                                if(user_args.size() >= 2){
                                    string file = user_args.at(1);
                                    //whole next command will be path
                                    status = fileExists(file);
                                    if(status){
                                        cout << "(TRUE)" << endl;
                                    }
                                else{
                                    cout << "(FALSE)" << endl;
                                    }
                                }
                            }
                            //test if regular file
                            else if(user_args.at(0) == "-f"){
                                //cout << "ok -f" << endl;
                                if(user_args.size() >= 2){
                                    string file = user_args.at(1);
                                    //whole next command will be path
                                    status = reg_file(file);
                                }
                            }
                            //test if directory
                            else if(user_args.at(0) == "-d"){
                                //cout << "ok -d" << endl;
                                if(user_args.size() >= 2){
                                string file = user_args.at(1);
                                //whole next command will be path
                                status = directory(file);
                            }
                            }
                            else{
                                //default test if file / directory exist
                                //cout << "ok -e" << endl;
                                if(user_args.size() >= 1){
                                    string file = user_args.at(0);
                                    //whole next command will be path
                                    status = fileExists(file);
                                    if(status){
                                        cout << "(TRUE)" << endl;
                                    }
                                    else{
                                        cout << "(FALSE)" << endl;
                                    }
                                }
                            }
                        
                    }
                }
                }
                //if status good do not execute and ski
            }
            
            }//end of or skip
            //cout << "at end of or skip " << endl;
            } //end of superskip
        } //end of while loop
        
    }
    return 0;
}