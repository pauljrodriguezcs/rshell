#!/bin/bash
cd ..
bin/rshell << 'EOF'
./a.out << 'EOF'
echo hello world
echo dog && echo tiger woods #tiger woods is a golfer || echo help && ls; echo what is up
echo dog || echo cat || echo like a boss && ls && mkdir test
ls && echo hello aliens #this is a comment
exit
EOF
