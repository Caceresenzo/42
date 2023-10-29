custom_sh="Ressources/compile.sh"

for directory in level* bonus*; do
    level="$(basename $directory)"
    echo
    echo $level

    pushd $directory
    if [ -f "$custom_sh" ]; then
        echo "$level: using custom: $custom_sh"
        sh "$custom_sh"
    else
        source="$(find . -name "source.*")"

        program="gcc"
        if echo "$source" | grep -q ".cpp"; then
            program=g++
        fi

        echo "$level: using generic: $program"
        $program $source -o $level -m32
    fi
    popd
done
