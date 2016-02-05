#!/bin/bash
cd ..
bin/rshell << 'EOF'
echo this is not a test of the emergency alert system
echo at 500 hours US satelites detected launch of Iranian ICBMs headed toward all major US cities
echo please report to your nearest fall out shelter
echo odds are many of you will die
echo good luck and may the odds be ever in your favor
echo psyche #this is a test of the comment alert system
ls
mkdir test
ls
echo Routing devices and tunnels
ip
echo Print user and group id's
id
echo Print or set system name
hostname
echo Print group names a user is in
groups
echo Environment variables
env
echo Estimate file space usage
du
echo display calender
cal
exit
EOF