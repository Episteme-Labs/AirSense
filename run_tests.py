#!/usr/bin/env python3
"""
Build and run unit tests for AirSense project.

This script:
1. Creates a build directory for tests
2. Configures the tests with CMake
3. Builds the tests
4. Runs the tests and reports results

Usage:
    python3 run_tests.py              # Build and run tests
    python3 run_tests.py --clean      # Clean build directory first
    python3 run_tests.py --build-only # Only build, don't run
    python3 run_tests.py --run-only   # Only run (assumes already built)
"""

import sys
import os
import subprocess
import argparse
from pathlib import Path

# Colors for terminal output
class Colors:
    HEADER = '\033[95m'
    BLUE = '\033[94m'
    CYAN = '\033[96m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def print_header(msg):
    """Print a header message"""
    print(f"\n{Colors.BOLD}{Colors.CYAN}{'=' * 60}{Colors.ENDC}")
    print(f"{Colors.BOLD}{Colors.CYAN}{msg}{Colors.ENDC}")
    print(f"{Colors.BOLD}{Colors.CYAN}{'=' * 60}{Colors.ENDC}\n")

def print_success(msg):
    """Print a success message"""
    print(f"{Colors.GREEN}✓ {msg}{Colors.ENDC}")

def print_error(msg):
    """Print an error message"""
    print(f"{Colors.RED}✗ {msg}{Colors.ENDC}")

def print_warning(msg):
    """Print a warning message"""
    print(f"{Colors.YELLOW}⚠ {msg}{Colors.ENDC}")

def print_info(msg):
    """Print an info message"""
    print(f"{Colors.BLUE}ℹ {msg}{Colors.ENDC}")

def run_command(cmd, cwd=None, env=None):
    """Run a shell command and return the result"""
    try:
        result = subprocess.run(
            cmd,
            cwd=cwd,
            env=env,
            capture_output=True,
            text=True,
            check=True
        )
        return True, result.stdout, result.stderr
    except subprocess.CalledProcessError as e:
        return False, e.stdout, e.stderr

def clean_build_dir(build_dir):
    """Clean the build directory"""
    print_header("Cleaning Build Directory")
    
    if build_dir.exists():
        print_info(f"Removing {build_dir}")
        import shutil
        shutil.rmtree(build_dir)
        print_success("Build directory cleaned")
    else:
        print_info("Build directory doesn't exist, nothing to clean")

def configure_tests(tests_dir, build_dir):
    """Configure tests with CMake"""
    print_header("Configuring Tests")
    
    # Create build directory if it doesn't exist
    build_dir.mkdir(parents=True, exist_ok=True)
    
    print_info(f"Running CMake in {build_dir}")
    success, stdout, stderr = run_command(
        ["cmake", ".."],
        cwd=build_dir
    )
    
    if success:
        print_success("CMake configuration successful")
        return True
    else:
        print_error("CMake configuration failed")
        print(stderr)
        return False

def build_tests(build_dir):
    """Build the tests"""
    print_header("Building Tests")
    
    print_info("Running make")
    success, stdout, stderr = run_command(
        ["make"],
        cwd=build_dir
    )
    
    if success:
        print_success("Build successful")
        # Print summary of what was built
        for line in stdout.split('\n'):
            if 'Built target' in line or 'Building' in line:
                print(f"  {line.strip()}")
        return True
    else:
        print_error("Build failed")
        print(stderr)
        return False

def run_tests(build_dir):
    """Run the test executables"""
    print_header("Running Tests")
    
    # Find all test executables
    test_executables = []
    for file in build_dir.iterdir():
        if file.is_file() and file.stat().st_mode & 0o111 and not file.suffix:
            # It's an executable file
            if file.name.startswith('test_'):
                test_executables.append(file)
    
    if not test_executables:
        print_warning("No test executables found in build directory")
        return False
    
    all_passed = True
    results = []
    
    for test_exe in test_executables:
        print_info(f"Running {test_exe.name}")
        success, stdout, stderr = run_command([str(test_exe)], cwd=build_dir)
        
        # Parse Unity test output
        test_passed = success
        test_count = 0
        failures = 0
        
        for line in stdout.split('\n'):
            if 'Tests' in line and 'Failures' in line:
                # Unity output format: "X Tests Y Failures Z Ignored"
                parts = line.split()
                if len(parts) >= 4:
                    test_count = int(parts[0])
                    failures = int(parts[2])
                    test_passed = (failures == 0)
        
        results.append({
            'name': test_exe.name,
            'passed': test_passed,
            'tests': test_count,
            'failures': failures,
            'output': stdout
        })
        
        # Print output
        print(stdout)
        if stderr:
            print(stderr)
        
        if test_passed:
            print_success(f"{test_exe.name} passed ({test_count} tests)")
        else:
            print_error(f"{test_exe.name} failed ({failures}/{test_count} tests failed)")
            all_passed = False
        
        print()
    
    return all_passed, results

def print_summary(results):
    """Print a summary of test results"""
    print_header("Test Summary")
    
    total_tests = sum(r['tests'] for r in results)
    total_failures = sum(r['failures'] for r in results)
    total_suites = len(results)
    passed_suites = sum(1 for r in results if r['passed'])
    
    print(f"Test Suites: {Colors.GREEN}{passed_suites} passed{Colors.ENDC}, "
          f"{Colors.RED}{total_suites - passed_suites} failed{Colors.ENDC}, "
          f"{total_suites} total")
    print(f"Tests:       {Colors.GREEN}{total_tests - total_failures} passed{Colors.ENDC}, "
          f"{Colors.RED}{total_failures} failed{Colors.ENDC}, "
          f"{total_tests} total")
    print()
    
    if total_failures == 0:
        print_success("All tests passed! 🎉")
        return 0
    else:
        print_error(f"{total_failures} test(s) failed")
        return 1

def main():
    parser = argparse.ArgumentParser(
        description='Build and run unit tests for AirSense project'
    )
    parser.add_argument('--clean', action='store_true',
                        help='Clean build directory before building')
    parser.add_argument('--build-only', action='store_true',
                        help='Only build tests, do not run them')
    parser.add_argument('--run-only', action='store_true',
                        help='Only run tests, do not build (assumes already built)')
    parser.add_argument('--verbose', '-v', action='store_true',
                        help='Verbose output')
    
    args = parser.parse_args()
    
    # Get project directories
    script_dir = Path(__file__).parent.absolute()
    tests_dir = script_dir / "tests"
    build_dir = tests_dir / "build"
    
    print_header("AirSense Unit Test Runner")
    print_info(f"Project directory: {script_dir}")
    print_info(f"Tests directory: {tests_dir}")
    print_info(f"Build directory: {build_dir}")
    print()
    
    # Validate tests directory exists
    if not tests_dir.exists():
        print_error(f"Tests directory not found: {tests_dir}")
        return 1
    
    # Clean if requested
    if args.clean:
        clean_build_dir(build_dir)
    
    # Build tests
    if not args.run_only:
        if not configure_tests(tests_dir, build_dir):
            return 1
        
        if not build_tests(build_dir):
            return 1
    
    # Run tests
    if not args.build_only:
        all_passed, results = run_tests(build_dir)
        return print_summary(results)
    else:
        print_success("Build complete. Skipping test execution.")
        return 0

if __name__ == "__main__":
    sys.exit(main())
