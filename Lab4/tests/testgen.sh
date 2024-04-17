if [ "$#" -ne 5 ]; then
    echo "EXPECTED: $0 <from> <to> <step> <max> <output_directory>"
    exit 1
fi

from_size=$1
to_size=$2
step=$3
max=$4
output_directory=$5

mkdir -p "$output_directory"

current_size=$from_size
while [ "$current_size" -le "$to_size" ]; do

    for k in {1..5}; do

        ./arrgen $current_size $max > "$output_directory/${current_size}_${k}.in"

        ./arrheap < "$output_directory/${current_size}_${k}.in" > "$output_directory/${current_size}_${k}.out"

    done

    current_size=$((current_size + step))
done
