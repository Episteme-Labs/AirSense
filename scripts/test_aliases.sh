#!/bin/bash
# Quick test runner for AirSense
# Source this file to add 'test' alias: source scripts/test_aliases.sh

alias test='python3 run_tests.py'
alias test-clean='python3 run_tests.py --clean'
alias test-build='python3 run_tests.py --build-only'
alias test-run='python3 run_tests.py --run-only'

echo "AirSense test aliases loaded:"
echo "  test        - Build and run tests"
echo "  test-clean  - Clean build and run"
echo "  test-build  - Build only"
echo "  test-run    - Run only"
