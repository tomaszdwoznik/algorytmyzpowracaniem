#!/bin/bash
blue=$(tput setaf 4)
gray=$(tput setaf 7)
green=$(tput setaf 2)
teal=$(tput setaf 6)
normal=$(tput sgr0)
routine_file="routines/euler"
routine=$(<"$routine_file")
saturation=30
type_file="type/hamilton"
type=$(<"$type_file")

for benchmark in benchmark/"hamilton"/"hamilton".*; do
    instance_size=${benchmark##*.}
    tmpLogFile=$(mktemp)
    cat > "$tmpLogFile" <<EOF
$normal============================[INSTANCE SIZE $instance_size]============================$green
Running the $type benchmark for $routine cycle...
$normal============================[Input]============================$gray
$instance_size 
$saturation 
$routine
exit
$normal============================[Program Output]===================$teal

EOF
    printf "%s\n" "$(cat "$tmpLogFile")"
    tmpFile=$(mktemp)
    run_project="../mainerer --$type"
    result=$( { $run_project <<< "$(printf "%s\n%s\n%s\n%s" "$instance_size" "$saturation" "$routine" "exit")" ; } 2>&1 > "$tmpFile")
    time_temp=$(cat "$tmpFile")  # Extract time taken from output
    time=$(bc -l <<< "scale=6; $time_temp / 1000000")
    if (( $(bc <<< "$time < 1") )); then
        time="0$time"
    fi
    
    # Save to .csv
    echo "$type,$instance_size,$time" >> "benchmark_${routine}cycle_results/${type}_${routine}cycle_benchmark_time.csv"

    # Follow up log - after program completion
    cat > "$tmpLogFile" <<EOF

$(cat "$tmpFile")
$normal============================[usr/bin/time]=====================$green
time = $time seconds | memory used = $mem KB
Saved to ${type}_${instance_size}_${routine}cycle_benchmark_time.csv"

$normal
EOF
    printf "%s\n" "$(cat "$tmpLogFile")"
done
