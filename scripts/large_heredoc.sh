#!/bin/bash

# Create a function to generate a large amount of data
generate_data() {
    for i in {1..1000000}; do
        echo "This is line $i of the very large here-doc"
    done
}

# Use the generated data in a here-doc
cat << EOF | wc -l
$(generate_data)
EOF
