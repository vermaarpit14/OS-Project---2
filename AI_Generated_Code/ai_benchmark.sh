#!/bin/bash

# 1. Setup Folder
OUTPUT_DIR="AI_Outputs"
mkdir -p "$OUTPUT_DIR"

# 2. Create a unique log file name using the current timestamp
# This ensures that "every run creates a new log.txt" instead of overwriting
TIMESTAMP=$(date "+%Y%m%d_%H%M%S")
LOG_FILE="$OUTPUT_DIR/log_$TIMESTAMP.txt"

# 3. System Metadata
USER_NAME="himanshu"
CURRENT_DATE=$(date "+%Y-%m-%d %H:%M:%S")
CPU_INFO=$(grep "model name" /proc/cpuinfo | head -n 1 | cut -d ':' -f 2 | xargs)
N_SIZE=${1:-1000}
THREADS=${2:-4}

# 4. Compile the code
# Using -O3 flag for maximum math optimization
gcc -O3 ai_fast_calculation.c -o matrix_benchmark

# 5. Execute and redirect ALL output to the UNIQUE log file
{
    echo "------------------------------------------------"
    echo "User:      $USER_NAME"
    echo "Date:      $CURRENT_DATE"
    echo "Hardware:  $CPU_INFO"
    echo "Command:   ./matrix_benchmark $N_SIZE $THREADS"
    echo "Results:"
    echo "Initializing Matrix: ${N_SIZE}x${N_SIZE} | Workers: $THREADS"
    
    # Call the C program
    ./matrix_benchmark $N_SIZE $THREADS
    
    echo "------------------------------------------------"
} > "$LOG_FILE"

# Inform the user where the specific results were saved
echo "Success! Results saved to: $LOG_FILE"
cat "$LOG_FILE"