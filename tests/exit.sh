#!/bin/bash
cd ..
cd with_makefile
./a.out << 'EOF'
exit
EOF

./a.out << 'EOF'
echo dog || exit && echo cat && exit
EOF

./a.out << 'EOF'
echo hamster && echo tigerwoods && echo cat && exit
EOF

./a.out << 'EOF'
echo piglet && echo Babe Ruth|| echo liger; exit
EOF