#!/bin/bash

# Check if filename is provided as argument
if [ $# -eq 0 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

# Get the filename from the argument
filename=$1

# Check if filename ends with .cpp
if [[ $filename != *.cpp ]]; then
    echo "Filename must end with .cpp"
    exit 1
fi


# Extract the number at the beginning of the filename
number=$(echo $filename | grep -o '^[0-9]*')

# Create a new filename using the extracted number
new_filename="$number.cpp"

# Create a new file with the new filename
# Add include statement at the beginning of the new file
echo -e "#include\"$filename\"\n\nMYTEST(1){\n\tSolution s;\n}" > ./test/$new_filename && code ./test/$new_filename
