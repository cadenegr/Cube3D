#!/bin/bash

# Cub3D Interactive Test Suite
# Manual tests for game functionality and user interaction

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

echo -e "${BLUE}=== CUB3D INTERACTIVE TEST SUITE ===${NC}"
echo -e "${YELLOW}This suite requires manual interaction to test game functionality${NC}"
echo

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

# Function to run an interactive test
run_interactive_test() {
    local test_name="$1"
    local command="$2"
    local description="$3"
    local instructions="$4"
    
    echo -e "${YELLOW}Interactive Test: $test_name${NC}"
    echo "  Description: $description"
    echo "  Command: $command"
    echo "  Instructions: $instructions"
    echo
    
    read -p "Press ENTER to start this test (or 'q' to quit): " user_input
    if [ "$user_input" = "q" ] || [ "$user_input" = "Q" ]; then
        echo "Test suite aborted by user."
        exit 0
    fi
    
    echo -e "${GREEN}Starting $test_name...${NC}"
    echo -e "${BLUE}Use ESC or close window to exit the game${NC}"
    echo
    
    # Run the command
    eval $command
    
    echo
    echo -e "${YELLOW}Test completed. Did the game work as expected?${NC}"
    echo "1) Yes - Game worked perfectly"
    echo "2) No - There were issues"
    echo "3) Skip - Couldn't test"
    
    read -p "Your response (1/2/3): " response
    case $response in
        1)
            echo -e "${GREEN}✓ PASSED${NC} - $test_name"
            ;;
        2)
            echo -e "${RED}✗ FAILED${NC} - $test_name"
            read -p "Please describe the issue: " issue_description
            echo "  Issue: $issue_description"
            ;;
        3)
            echo -e "${YELLOW}⚠ SKIPPED${NC} - $test_name"
            ;;
        *)
            echo -e "${YELLOW}⚠ INVALID RESPONSE${NC} - Marking as skipped"
            ;;
    esac
    echo
}

# Test 1: Basic game functionality with valid map
run_interactive_test "Basic Game Functionality" \
    "./cub3D test/maps/valid_basic.cub" \
    "Test basic raycasting, movement, and window management" \
    "Try moving with WASD keys, look around with arrow keys, press ESC to exit"

# Test 2: Original map test
run_interactive_test "Original Map Test" \
    "./cub3D maps_sub/map.cub" \
    "Test with the original provided map" \
    "Navigate the map, test collision detection with walls, verify textures render correctly"

# Test 3: Performance test
run_interactive_test "Performance Test" \
    "./cub3D maps_sub/map1.cub" \
    "Test game performance and responsiveness" \
    "Move quickly around the map, check for smooth rendering and responsive controls"

echo -e "${BLUE}=== INTERACTIVE TEST SUMMARY ===${NC}"
echo "Interactive testing completed!"
echo
echo -e "${YELLOW}Key Controls Reminder:${NC}"
echo "  W/A/S/D - Move forward/left/backward/right"
echo "  Arrow Keys - Look around"
echo "  ESC - Exit game"
echo "  X (close button) - Exit game"
echo
echo -e "${GREEN}If all tests passed, your Cub3D raycasting engine is working correctly!${NC}"