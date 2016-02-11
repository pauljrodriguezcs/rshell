#!/bin/bash
cd ..
bin/rshell << 'EOF'
echo hello world
echo dog && echo tiger woods #tiger woods is a golfer || echo help && ls; echo what is up
echo dog || echo cat || echo like a boss && ls && mkdir test
ls && echo hello aliens #this is a comment
du && cal || echo this should not print && echo success
id || cal || echo hello sir && echo some bash magic
echo I need to schedule a date on the calendar && cal
exit
EOF
