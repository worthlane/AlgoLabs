if [ "$#" -ne 5 ]; then
    echo "EXPECTED: $0 <from> <to> <step> <mode> <output_directory>"
    exit 1
fi

from_size=$1
to_size=$2
step=$3
mode=$4
output_directory=$5

mkdir -p "$output_directory"

current_size=$from_size
while [ "$current_size" -le "$to_size" ]; do

    for k in {1..5}; do

        ./request $current_size $mode > "$output_directory/${current_size}_${k}.in"

    done

    current_size=$((current_size + step))
done
