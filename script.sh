
#!/bin/bash


# Check if the first argument is provided and is either 0 or 1
if [ -z "$1" ] || [ "$1" != "0" ] && [ "$1" != "1" ]; then
    echo "Error: First argument must be 0 or 1"
    exit 1
fi

make

# Store the first argument (0 for normal execution, 1 for valgrind)
MODE=$1

# List of all test targets defined in the Makefile
TESTS=$(find src/ -name '*_test.c' -exec basename {} .c \;)

# If a second argument is provided, work with the specified test
if [ -n "$2" ]; then
    TEST_NAME="$2"

    # Verificar si el archivo ejecutable del test existe
    if [ ! -f "$TEST_NAME" ]; then
        echo "Error: Test '$TEST_NAME' does not exist"
        make clean
        exit 1
    fi

    # Execute the test based on MODE
    if [ "$MODE" = "0" ]; then
        echo "Running $TEST_NAME..."
        ./"$TEST_NAME"

    else
        echo "Running $TEST_NAME with valgrind..."
        valgrind --leak-check=full ./"$TEST_NAME"
    fi

else
    # No second argument: compile and run all tests
    echo "Compiling all tests..."
    
    # Execute all tests based on MODE
    if [ "$MODE" = "0" ]; then
        echo "Running all tests..."
        for TEST in $TESTS; do
            echo "Running $TEST..."
            ./"$TEST"
        done

    else
        echo "Running all tests with valgrind..."
        for TEST in $TESTS; do
            echo "Running $TEST with valgrind..."
            valgrind --leak-check=full ./"$TEST"
        done
    fi
fi

make clean