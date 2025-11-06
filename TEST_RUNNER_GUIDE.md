# AirSense Test Runner - Quick Reference

## Overview

Created a comprehensive Python-based test runner for the AirSense project that handles building and running unit tests on the host system.

## Files Created

### 1. `run_tests.py` (Main Test Runner)
- **Location**: Project root
- **Purpose**: Python script to build and run unit tests
- **Features**:
  - Automatic CMake configuration
  - Build management
  - Test execution and reporting
  - Colorized output
  - Multiple execution modes

### 2. `tests/README.md`
- **Purpose**: Detailed documentation for the test system
- **Contents**:
  - Setup instructions
  - Test structure overview
  - How to write new tests
  - Mock framework documentation
  - Troubleshooting guide

### 3. `Makefile.tests`
- **Purpose**: Makefile wrapper for convenience
- **Usage**: Simple make commands for common operations

### 4. `scripts/test_aliases.sh`
- **Purpose**: Shell aliases for quick access
- **Usage**: Source it to add test shortcuts

## Usage Examples

### Python Script (Recommended)

```bash
# Basic usage - build and run all tests
python3 run_tests.py

# Clean build before running
python3 run_tests.py --clean

# Only build, don't run
python3 run_tests.py --build-only

# Only run already-built tests
python3 run_tests.py --run-only

# Get help
python3 run_tests.py --help
```

### Makefile Wrapper

```bash
# Run tests
make -f Makefile.tests test

# Clean and rebuild
make -f Makefile.tests clean

# Build only
make -f Makefile.tests build

# Run only
make -f Makefile.tests run
```

### Shell Aliases

```bash
# Load aliases (do this once per session)
source scripts/test_aliases.sh

# Then use simple commands
test              # Build and run
test-clean        # Clean build and run
test-build        # Build only
test-run          # Run only
```

## Script Features

### Colorized Output
- **Green (✓)**: Success messages
- **Red (✗)**: Error messages
- **Yellow (⚠)**: Warning messages
- **Blue (ℹ)**: Info messages
- **Cyan**: Headers

### Test Result Parsing
- Automatically parses Unity test framework output
- Counts total tests, failures, and passes
- Provides summary statistics
- Exit code reflects test success (0 = pass, 1 = fail)

### Build Management
- Creates build directory if needed
- Handles CMake configuration
- Runs make with proper error handling
- Captures and displays build output

## CI/CD Integration

The script is designed for easy CI/CD integration:

```bash
# In your CI/CD pipeline
python3 run_tests.py --clean
exit_code=$?

if [ $exit_code -ne 0 ]; then
    echo "Tests failed!"
    exit 1
fi
```

## Example Output

```
============================================================
AirSense Unit Test Runner
============================================================

ℹ Project directory: /home/codespace/AirSense
ℹ Tests directory: /home/codespace/AirSense/tests
ℹ Build directory: /home/codespace/AirSense/tests/build


============================================================
Configuring Tests
============================================================

ℹ Running CMake in /home/codespace/AirSense/tests/build
✓ CMake configuration successful

============================================================
Building Tests
============================================================

ℹ Running make
✓ Build successful
  [100%] Built target test_driver_pm25

============================================================
Running Tests
============================================================

ℹ Running test_driver_pm25
4 Tests 0 Failures 0 Ignored 
OK

✓ test_driver_pm25 passed (4 tests)


============================================================
Test Summary
============================================================

Test Suites: 1 passed, 0 failed, 1 total
Tests:       4 passed, 0 failed, 4 total

✓ All tests passed! 🎉
```

## Benefits

1. **Consistency**: Same commands work everywhere
2. **Automation**: No manual CMake/make commands needed
3. **Reporting**: Clear, colorful output with summaries
4. **Flexibility**: Multiple usage modes for different workflows
5. **CI/CD Ready**: Exit codes and clean output for automation
6. **User Friendly**: Help messages and clear documentation

## Next Steps

To improve the test system further:

1. Add test coverage reporting
2. Implement test filtering (run specific tests)
3. Add parallel test execution
4. Generate HTML/XML test reports
5. Add test timing information
6. Integrate with GitHub Actions

## Troubleshooting

### Tests won't build
```bash
# Clean everything and rebuild
python3 run_tests.py --clean
```

### CMake errors
- Ensure CMake 3.13+ is installed
- Check that you're in the project root directory

### Tests fail to run
- Verify the build succeeded first
- Try: `python3 run_tests.py --build-only` then check for errors

## Additional Resources

- `tests/README.md` - Detailed test documentation
- `run_tests.py --help` - Command-line options
- Unity documentation: https://github.com/ThrowTheSwitch/Unity
