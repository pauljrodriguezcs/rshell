#!/bin/bash
cd ..
bin/rshell << 'EOF'
echo hello world #this is a test comment 
echo dog #this is a test comment && echo tiger woods #tiger woods is a golfer || echo help && ls; echo what is up #this is a test comment 
echo dog || echo cat || echo like a boss && ls #this is a comment && mkdir test
echo testing one two three #echo this is a comment && echo hello aliens #this is a comment
cal #print calendar my favorite new command lol
id #print some user and group id's whatever that means lol idk
echo this is a calendar #I hope my spelling is right && cal 
echo Now this is a story all about how #I 
echo My life got flipped turned upside down #love
echo And Id like to take a minute #this
echo Just sit right there #show
echo Ill tell you how I became the prince of a town called Bel Air #its the best
test src #this is a comment bro
(echo A #this is a comment && echo B #comment 2) || (echo C # this is a comment echo D #this is a comment)
exit
EOF