#!/bin/sh

find . -type f -exec sed -i 's/vec2(\([^,()]*\), *\([^()]*\))/vec3(\1, \2, 0)/g' {} +
find . -type f -exec sed -i 's/vec2/vec3/g' {} +
