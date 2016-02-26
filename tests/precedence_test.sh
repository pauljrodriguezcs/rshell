#!/bin/bash
cd ..
bin/rshell << 'EOF'
(test -e /bin/fake #file doesnt exist || echo file should not exist) && echo I should go
(echo A && echo B) || (echo C && echo D)
(echol A && echo B) || (echo C && echo D)
echo for some reason this messes up when ran as a script but works perfect when ran typed in normally idk
((echo A #comment 1 && echo B #comment 2) || (echo C #comment 3 && echo D #comment 4)) && echo success
(((echo A || echo B) || (echo C && echo D)) && echo good)
(((echo A || echo B) || (echo C && echo D)) && [/bin/rshell])
(test -f /bin || echo last command should be false) && echo but whole thing should be true
echo delete system 32 || (echo this && (echo should && echo all) && echo be skipped) && echo awesome
(test -f /bin/rshell #comment && echol bad) || (echo A #comment 2 && echo B #comment 3)
exit
EOF
