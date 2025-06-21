for file in build/bin/sprites/player_*_normalmap.png; do
    # Extract parts: action (idle, walk, etc.) and number
    if [[ $file =~ player_(.*)([0-9]+)_normalmap\.png ]]; then
        action="${BASH_REMATCH[1]}"
        number="${BASH_REMATCH[2]}"
        mv "$file" "build/bin/sprites/player_${action}_normalmap${number}.png"
    fi
done
