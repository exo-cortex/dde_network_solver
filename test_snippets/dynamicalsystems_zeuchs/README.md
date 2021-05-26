
compile with:
g++ dynamic_main.cpp -o main

or "make"

execute:

# integrate Mackey-Glass-system with standard parameters run the following command

./main -runtime 15 -runsilent 100 -delay 17

# the data will be written into "output.txt", to plot it run:

./plot.py