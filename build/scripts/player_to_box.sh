#!/bin/bash

SRC_DIR="build/bin/sprites"
BOX="box.png"
BOX_NORMAL="box_normalmap.png"

cd "$SRC_DIR" || exit 1

for f in player_*.png; do
	if [[ "$f" == *normalmap.png ]]; then
		mv "$f" "$BOX_NORMAL"
	else
		mv "$f" "$BOX"
	fi
done
