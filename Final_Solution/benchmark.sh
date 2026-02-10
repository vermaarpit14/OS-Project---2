#!/bin/bash

LOG_FILE="benchmark_log.txt"
EXEC_NAME="matrix_benchmark"
SRC_FILE="fast_mul.c"

if [ ! -f "$SRC_FILE" ]; then
    echo "Error: Source file '$SRC_FILE' not found."
    exit 1
fi

echo "Building $EXEC_NAME from $SRC_FILE..."
gcc -O2 "$SRC_FILE" -o "$EXEC_NAME"
if [ $? -ne 0 ]; then
    echo "Build failed! Please check your source code."
    exit 1
fi

CURRENT_USER=$(whoami)
if command -v git &> /dev/null; then
    GIT_USER=$(git config user.name)
    if [ ! -z "$GIT_USER" ]; then
        CURRENT_USER=$GIT_USER
    fi
fi

TIMESTAMP=$(date "+%Y-%m-%d %H:%M:%S")
CPU_MODEL=$(grep -m1 'model name' /proc/cpuinfo | cut -d: -f2 | xargs)
if [ -z "$CPU_MODEL" ]; then
    CPU_MODEL="Unknown CPU"
fi

echo "Starting benchmark for user: $CURRENT_USER"
echo "------------------------------------------------" >> "$LOG_FILE"
echo "User:     $CURRENT_USER" >> "$LOG_FILE"
echo "Date:     $TIMESTAMP" >> "$LOG_FILE"
echo "Hardware: $CPU_MODEL" >> "$LOG_FILE"
echo "Command:  ./$EXEC_NAME 2000 4" >> "$LOG_FILE"
echo "Results:" >> "$LOG_FILE"

./"$EXEC_NAME" 2000 4 | tee -a "$LOG_FILE"

echo "" >> "$LOG_FILE"
echo "------------------------------------------------" >> "$LOG_FILE"

rm "$EXEC_NAME"
echo "Benchmark complete. Data saved to $LOG_FILE"