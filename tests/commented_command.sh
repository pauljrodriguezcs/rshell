#!/bin/bash
cd ..
cd with_makefile
./a.out << 'EOF'
echo hello world #this is a test comment 
echo dog #this is a test comment && echo tiger woods #tiger woods is a golfer || echo help && ls; echo what is up #this is a test comment 
echo dog || echo cat || echo like a boss && ls #this is a comment && mkdir test
echo testing one two three #echo this is a comment && echo hello aliens #this is a comment
exit
EOF