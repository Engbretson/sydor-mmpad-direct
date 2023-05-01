#!/bin/bash

source_file=$1
dest_dir=$2
base_name=$3
num_images=$4

install -d "$dest_dir"

for file_num in `seq "$num_images"`
do
    cp "$source_file" "$dest_dir"/"$base_name"_`printf "%06i01.raw" $(("$file_num"-1))`
    #printf "foobar_%06i01.raw\n" $(("$file_num"-1))
done

