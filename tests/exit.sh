#!/bin/bash
cd ..
bin/rshell << 'EOF'
exit
EOF

bin/rshell << 'EOF'
echo dog || exit && echo cat && exit
EOF

bin/rshell << 'EOF'
echo hamster && echo tigerwoods && echo cat && exit
EOF

bin/rshell << 'EOF'
echo piglet && echo Babe Ruth || echo liger; exit
EOF

bin/rshell << 'EOF'
echo cat || echo dog && exit
EOF