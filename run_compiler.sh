#! /bin/bash
#
# Usage: run_compiler.sh file
#
# Looks for patterns of the form:
# // RUN(name): <compiler> -c
#
# And adds the filename at the end
# Then generates disassembly

# Check for correct number of arguments
if [ $# -ne 1 ]; then
    echo "Usage: run_compiler.sh <file>"
    exit 1
fi

declare -A assembly_hashes=()

# Search for patterns
grep -E '// RUN\([a-zA-Z0-9_-]+\):' $1 | while read -r line; do
    # Extract test name
    name=$(echo $line | sed -E 's/\/\/ RUN\(([a-zA-Z0-9_-]+)\):.*/\1/')
    # Extract command start: everything from the `:` to `\n`
    cmd=$(echo $line | sed -E 's/\/\/ RUN\([a-zA-Z0-9_-]+\): (.*)/\1/')
    # Append filename
    cmd="$cmd $1"
    out_dir=${1%.c}
    # Create output directory
    out_file="$out_dir/$name.s"
    mkdir -p $out_dir
    # Append output
    cmd="$cmd -c -S -o $out_file"
    # Run command
    $cmd

    # Generate hash
    hash=$(sha1sum $out_file | cut -d' ' -f1)

    # Add hash to array
    if [ -z "${assembly_hashes[__$hash]}" ]; then
        assembly_hashes[__$hash]=$name
    else
        echo "Warning: tests ${assembly_hashes[__$hash]},$name generate the same assembly"
        assembly_hashes[__$hash]="${assembly_hashes[__$hash]},$name"
    fi
done
