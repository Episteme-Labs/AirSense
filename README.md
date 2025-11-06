# AirSense
An embedded systems project designed to develop an indoor air quality monitoring device with integrated mobile app support for real-time user interaction.

## Development

### Building for Raspberry Pi Pico

The main application builds for Raspberry Pi Pico W:

```bash
# Configure and build
cd build
cmake ..
make
```

### Running Unit Tests

Unit tests run on the host system (not on the Pico). Use the Python test runner:

```bash
# Run all tests
python3 run_tests.py

# Clean build and run
python3 run_tests.py --clean

# Or use the Makefile wrapper
make -f Makefile.tests test
make -f Makefile.tests clean
```

See [tests/README.md](tests/README.md) for detailed testing documentation.

