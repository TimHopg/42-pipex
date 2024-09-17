#!/bin/bash

# Create a function to generate a large amount of data
generate_data() {
    for i in {1..1000000}; do
        echo "This is line $i of the very large here-doc"
    done
}

# Use the generated data in a here-doc
./pipex here_doc EOF cat "wc -l" outfile
$(generate_data)
EOF
