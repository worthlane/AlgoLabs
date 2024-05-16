if [ "$#" -ne 5 ]; then
    echo "EXPECTED: $0 <from> <to> <step> <sort_flag> <output_directory>"
    exit 1
fi

from_size=$1
to_size=$2
step=$3
sort_flag=$4
output_directory=$5

mkdir -p "$output_directory"

current_size=$from_size
while [ "$current_size" -le "$to_size" ]; do

    for k in {1..5}; do

        half_size=$((current_size / 2))

        ./arrgen $current_size $sort_flag > "$output_directory/${current_size}_${k}_ins.in"

        ./arrgen $half_size $sort_flag > "$output_directory/${current_size}_${k}_del.in"

    done

    current_size=$((current_size + step))
done
