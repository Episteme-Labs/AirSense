# AirSense Unit Tests

This directory contains unit tests for the AirSense PM2.5 sensor driver project.

## Prerequisites

- Python 3.x
- CMake 3.13 or higher
- GCC compiler (for host builds)
- Unity Test Framework (included as submodule)

## Quick Start

### Run All Tests

```bash
# From the project root directory
python3 run_tests.py
```

### Build and Run Options

```bash
# Clean build and run all tests
python3 run_tests.py --clean

# Only build tests (don't run)
python3 run_tests.py --build-only

# Only run tests (assumes already built)
python3 run_tests.py --run-only

# Show help
python3 run_tests.py --help
```

## Manual Build and Run

If you prefer to build and run tests manually:

```bash
# Navigate to tests directory
cd tests

# Create and enter build directory
mkdir -p build
cd build

# Configure with CMake
cmake ..

# Build
make

# Run tests
./test_driver_pm25
```

## Test Structure

```
tests/
├── CMakeLists.txt           # CMake configuration for tests
├── test_driver_pm25.c       # Main test file for PM2.5 driver
├── test_pm2_5.c            # Test-specific implementation using mocks
├── mocks/                   # Mock implementations
│   ├── mock_hardware_gpio.c
│   ├── mock_hardware_gpio.h
│   ├── mock_hardware_uart.c
│   └── mock_hardware_uart.h
└── unity/                   # Unity test framework (submodule)
```

## Writing Tests

Tests use the Unity test framework. Basic test structure:

```c
#include "unity.h"

void setUp(void) {
    // Setup before each test
}

void tearDown(void) {
    // Cleanup after each test
}

void test_something(void) {
    // Your test code
    TEST_ASSERT_EQUAL(expected, actual);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_something);
    return UNITY_END();
}
```

## Mock Framework

The tests use simple mocks for hardware abstraction:

- **mock_hardware_gpio**: Mocks GPIO functions (init, set_dir, put, set_function)
- **mock_hardware_uart**: Mocks UART functions (init, read, write, is_readable)

Mock expectations can be set up in your tests to verify function calls and parameters.

## Current Tests

### test_driver_pm25.c

Tests for the PMS7003 PM2.5 sensor driver:

- `test_pm25_sensor_init`: Verifies sensor initialization
- `test_pm25_sensor_read_valid`: Tests reading valid data from sensor
- `test_pm25_sensor_read_invalid_checksum`: Tests checksum validation
- `test_pm25_sensor_read_invalid_frame_length`: Tests frame length validation

## Troubleshooting

### Build Issues

If you encounter build errors:

1. Make sure you're not building for Pico (tests are host-only)
2. Clean the build directory: `python3 run_tests.py --clean`
3. Check that CMake and GCC are properly installed

### Test Failures

Current known issues:
- Mock expectation assertions need refinement for NULL parameter handling
- Some tests may need mock behavior updates to match implementation

## Adding New Tests

1. Create a new test file: `test_<feature>.c`
2. Add it to `CMakeLists.txt` in the `add_executable()` section
3. Implement tests using Unity framework
4. Add test runner main function
5. Run with `python3 run_tests.py`

## CI/CD Integration

The `run_tests.py` script returns:
- Exit code 0: All tests passed
- Exit code 1: One or more tests failed

This makes it easy to integrate with CI/CD pipelines:

```bash
python3 run_tests.py || exit 1
```

## References

- [Unity Test Framework](https://github.com/ThrowTheSwitch/Unity)
- [CMock](https://github.com/ThrowTheSwitch/CMock) (for advanced mocking)
- [PMS7003 Datasheet](../src/datasheet/)
