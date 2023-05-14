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

file=$1

function time_() {
    command=$1
    ts=$(date +%s%N)
    sh -c "$command"
    tt=$(($(date +%s%N) - $ts))
    echo "$tt"
}

function run_benchmark() {
    test_name=$1
    compile_cmd=$2

    bench_dir=bench/$file/$test_name
    mkdir -p $bench_dir

    # Get everyline that start with `// TEST:` from the file and print it in a new file.
    # Don't include the `// TEST:` part
    grep -E "// TEST:" $file | sed -E 's/\/\/ TEST: //' >$bench_dir/test.h

    # Copy bench.c to the benchmark directory
    cp bench.c $bench_dir/bench.c

    # Compile the benchmark and the test code
    gcc -c -O3 -o $bench_dir/bench.o $bench_dir/bench.c
    sh -c "$compile_cmd -c -o $bench_dir/$file.o"

    # Link the benchmark and the test code
    gcc -o $bench_dir/bench $bench_dir/bench.o $bench_dir/$file.o

    # Run the benchmark
    time_for_run=$($bench_dir/bench)
    echo "$1,$time_for_run" >>bench/$file/$file-benchmarks.csv
}

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
    # Run command
    time_for_compilation=$(time_ "$cmd -c -S -o $out_file")
    echo "$1,$name,$time_for_compilation" &>>compilation_times.csv

    # Generate hash
    hash=$(sha1sum $out_file | cut -d' ' -f1)

    # Add hash to array
    if [ -z "${assembly_hashes[__$hash]}" ]; then
        assembly_hashes[__$hash]=$name
    else
        echo "Warning: tests ${assembly_hashes[__$hash]},$name generate the same assembly"
        assembly_hashes[__$hash]="${assembly_hashes[__$hash]},$name"
    fi

    run_benchmark $name "$cmd"
done
