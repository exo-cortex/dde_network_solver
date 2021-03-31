mkdir build
cd build
cmake ..
make

# cd ..
# rm build -rf


### advanced:

## erstes mal:
(mkdir -p build && cd build && cmake .. && make)

## jedes weiter mal:
(cd build && make)
