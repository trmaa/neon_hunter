for f in *.hpp; do
  guard=$(echo "$f" | tr '[:lower:]./' '[:upper:]__')
  awk -v guard="$guard" '
    BEGIN { replaced=0 }
    {
      if (!replaced && $0 ~ /^#pragma[ \t]+one[ \t]*$/) {
        print "#ifndef " guard
        print "#define " guard
        replaced=1
      } else {
        print
      }
    }
    END {
      if (replaced) print ""
    }
  ' "$f" > "$f.tmp" && mv "$f.tmp" "$f"
done
