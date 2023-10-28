custom_sh="Ressources/compile.sh"

for directory in level*; do
    level="$(basename $directory)"
    echo
    echo $level

    pushd $directory
    if [ -f "$custom_sh" ]; then
        echo "$level: using custom: $custom_sh"
        sh "$custom_sh"
    else
        echo "$level: using generic: gcc"
        gcc source.c -o $level -m32
    fi
    popd
done
