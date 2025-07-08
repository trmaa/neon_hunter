#!/bin/bash

start_time=$(date +%s)

g++ assets/src/*.cpp -o build/neon_hunter \
    -Wl,-rpath=./assets/lib/ \
    -Iassets/include/ \
    -Lassets/lib/ \
    -lsfml-graphics -lsfml-window -lsfml-system

end_time=$(date +%s)
elapsed=$((end_time - start_time))

echo "Done in $elapsed seconds"
