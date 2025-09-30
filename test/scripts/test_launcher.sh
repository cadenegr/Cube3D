#!/bin/bash

# Cub3D Test Launcher
# Runs both automated and interactive tests

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

echo -e "${BLUE}=== CUB3D COMPREHENSIVE TEST SUITE ===${NC}"
echo

# Check if we're in a graphical environment for interactive tests
if [ -z "$DISPLAY" ]; then
    echo -e "${YELLOW}Warning: No display detected. Interactive tests will be skipped.${NC}"
    INTERACTIVE_AVAILABLE=false
else
    echo -e "${GREEN}Display detected. Interactive tests available.${NC}"
    INTERACTIVE_AVAILABLE=true
fi
echo

echo "Available test suites:"
echo "1) Automated tests only (validation, error handling, etc.)"
echo "2) Interactive tests only (manual gameplay testing)"
echo "3) Both automated and interactive tests"
echo "4) Exit"
echo

read -p "Select test suite (1-4): " choice

case $choice in
    1)
        echo -e "${BLUE}Running automated tests...${NC}"
        echo
        ./test/scripts/run_tests.sh
        ;;
    2)
        if [ "$INTERACTIVE_AVAILABLE" = false ]; then
            echo -e "${RED}Interactive tests not available (no display)${NC}"
            exit 1
        fi
        echo -e "${BLUE}Running interactive tests...${NC}"
        echo
        ./test/scripts/interactive_tests.sh
        ;;
    3)
        echo -e "${BLUE}Running automated tests first...${NC}"
        echo
        ./test/scripts/run_tests.sh
        
        if [ $? -eq 0 ]; then
            echo -e "${GREEN}Automated tests passed!${NC}"
            echo
            if [ "$INTERACTIVE_AVAILABLE" = true ]; then
                echo -e "${BLUE}Now running interactive tests...${NC}"
                echo
                ./test/scripts/interactive_tests.sh
            else
                echo -e "${YELLOW}Skipping interactive tests (no display)${NC}"
            fi
        else
            echo -e "${RED}Automated tests failed. Fix issues before running interactive tests.${NC}"
            exit 1
        fi
        ;;
    4)
        echo "Exiting..."
        exit 0
        ;;
    *)
        echo -e "${RED}Invalid choice. Exiting...${NC}"
        exit 1
        ;;
esac