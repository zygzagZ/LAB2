#!/bin/bash
gcc -g -Wall -Wextra -O2 -std=c11 -c strset_test1.c -o strset_test1.o
g++ -g -Wall -Wextra -O2 -std=c++17 -c strset.cc -o strset.o
g++ -g -Wall -Wextra -O2 -std=c++17 -c strsetconst.cc -o strsetconst.o
g++ -g strset_test1.o strsetconst.o strset.o -o strset1
g++ -g -Wall -Wextra -O2 -std=c++17 -c strset_test2a.cc -o strset_test2a.o
g++ -g -Wall -Wextra -O2 -std=c++17 -c strset_test2b.cc -o strset_test2b.o
g++ -g strset_test2a.o strsetconst.o strset.o -o strset2a
g++ -g strset_test2b.o strsetconst.o strset.o -o strset2b
