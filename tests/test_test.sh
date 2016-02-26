#!/bin/bash
cd ..
bin/rshell << 'EOF'
test -e /bin/fake #file doesnt exist
test -e /bin/rshell #file exist
test -d /bin #directory exist
test -d /bin2 #directory does not exist
test -f /tests/exit.sh #this exist
test -f /tests/exit1.sh #this does not exist
[-e /bin/fake] #file doesnt exist
[-e /bin/rshell] #file exist
[-d /bin] #directory exist
[-d /bin2] #directory does not exist
[-f /tests/exit.sh] #this exist
[-f /tests/exit1.sh] #this does not exist
exit
EOF