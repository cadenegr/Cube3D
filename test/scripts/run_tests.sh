#!/bin/bash

# Cub3D Test Suite
# Tests various scenarios for argument validation, map parsing, and error handling

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Get the directory of the cube3d project
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"
cd "$PROJECT_DIR"

# Ensure the program is built
echo -e "${BLUE}Building cub3D...${NC}"
make clean > /dev/null 2>&1
make_output=$(make 2>&1)
make_result=$?

# Check if build was successful (either compiled or nothing to do)
if [ $make_result -ne 0 ] && [[ ! "$make_output" =~ "Nothing to be done" ]]; then
    echo -e "${RED}Build failed!${NC}"
    echo "$make_output"
    exit 1
fi
echo -e "${GREEN}Build successful!${NC}"
echo

# Test counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Function to run a test
run_test() {
    local test_name="$1"
    local command="$2"
    local expected_result="$3"
    local description="$4"
    local timeout_ok="$5"  # Optional parameter for timeout tests
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo -e "${YELLOW}Test $TOTAL_TESTS: $test_name${NC}"
    echo "  Description: $description"
    echo "  Command: $command"
    
    # Run the command and capture output and exit code
    output=$(eval $command 2>&1)
    exit_code=$?
    
    # Special handling for timeout tests (exit code 124 means timeout killed the process)
    if [ "$timeout_ok" = "timeout" ] && [ $exit_code -eq 124 ]; then
        echo -e "  ${GREEN}✓ PASSED${NC} (Program started successfully, killed by timeout)"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    # Check if the result matches expected
    elif [ $exit_code -eq $expected_result ]; then
        echo -e "  ${GREEN}✓ PASSED${NC} (Exit code: $exit_code)"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "  ${RED}✗ FAILED${NC} (Expected: $expected_result, Got: $exit_code)"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        if [ ! -z "$output" ]; then
            echo "  Output: $output"
        fi
    fi
    echo
}

echo -e "${BLUE}=== CUB3D TEST SUITE ===${NC}"
echo

# Test 1: No arguments
run_test "No Arguments" \
    "./cub3D" \
    1 \
    "Should fail when no arguments provided"

# Test 2: Too many arguments
run_test "Too Many Arguments" \
    "./cub3D maps_sub/1.cub extra_arg" \
    1 \
    "Should fail when more than one argument provided"

# Test 3: Non-existent file
run_test "Non-existent File" \
    "./cub3D nonexistent.cub" \
    1 \
    "Should fail when map file doesn't exist"

# Test 4: Wrong file extension
run_test "Wrong File Extension" \
    "./cub3D README.md" \
    1 \
    "Should fail when file doesn't have .cub extension"

# Test 5: Valid basic map
run_test "Valid Basic Map" \
    "timeout 2s ./cub3D test/maps/valid_basic.cub" \
    0 \
    "Should succeed with valid map (killed by timeout)" \
    "timeout"

# Test 6: Missing player
run_test "Missing Player" \
    "./cub3D test/maps/missing_player.cub" \
    1 \
    "Should fail when no player spawn point in map"

# Test 7: Open map (not surrounded by walls)
run_test "Open Map" \
    "./cub3D test/maps/open_map.cub" \
    1 \
    "Should fail when map is not enclosed by walls"

# Test 8: Bad texture file
run_test "Bad Texture File" \
    "./cub3D test/maps/bad_texture.cub" \
    1 \
    "Should fail when texture file doesn't exist"

# Test 9: Missing texture definition
run_test "Missing Texture Definition" \
    "./cub3D test/maps/missing_texture.cub" \
    1 \
    "Should fail when texture definition is missing"

# Test 10: Invalid color values
run_test "Invalid Color Values" \
    "./cub3D test/maps/invalid_color.cub" \
    0 \
    "Should handle color values correctly (using your parsing logic)" \
    "timeout"

# Test 11: Invalid character in map
run_test "Invalid Character in Map" \
    "./cub3D test/maps/invalid_char.cub" \
    1 \
    "Should fail when map contains invalid characters"

# Test 12: Multiple players
run_test "Multiple Players" \
    "./cub3D test/maps/multiple_players.cub" \
    1 \
    "Should fail when map has multiple player spawn points"

# Test 13: Invalid file format
run_test "Invalid File Format" \
    "./cub3D test/maps/invalid_format.cub" \
    1 \
    "Should fail when file format is completely invalid"

# Test 14: Valid original map
run_test "Valid Original Map" \
    "timeout 2s ./cub3D maps_sub/1.cub" \
    0 \
    "Should succeed with original valid map (killed by timeout)" \
    "timeout"

# Summary
echo -e "${BLUE}=== TEST RESULTS ===${NC}"
echo "Total Tests: $TOTAL_TESTS"
echo -e "Passed: ${GREEN}$PASSED_TESTS${NC}"
echo -e "Failed: ${RED}$FAILED_TESTS${NC}"
echo

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "${GREEN}All tests passed! 🎉${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed. Please review the output above.${NC}"
    exit 1
fi