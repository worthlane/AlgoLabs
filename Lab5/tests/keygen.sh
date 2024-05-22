if [ "$#" -ne 2 ]; then
    echo "EXPECTED: $0 <size> <output_directory>"
    exit 1
fi

size=$1
output_directory=$2

mkdir -p "$output_directory"

./intgen $size -1 > "$output_directory/int_keys.in"

./wordgen $size 5 20 > "$output_directory/word_keys.in"

./floatgen $size 10 > "$output_directory/float_keys.in"
