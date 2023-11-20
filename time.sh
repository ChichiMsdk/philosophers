#!/bin/bash

# Initialize total minutes
total_minutes=0

# Function to add time
add_time() {
    # Split input by 'h'
    IFS='h' read -ra TIME <<< "$1"
    hours=${TIME[0]}
    minutes=${TIME[1]}

    # Convert to total minutes and add to total
    total_minutes=$((total_minutes + hours * 60 + minutes))
}

for time in "$@"
do
    add_time "$time"
done
# Convert total minutes back to hours and minutes
total_hours=$((total_minutes / 60))
remaining_minutes=$((total_minutes % 60))

# Output the result
echo "Total time: ${total_hours}h${remaining_minutes}"

