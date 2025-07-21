# File System Simulator

A minimal file system simulator implemented in C++ with smart pointer memory management. This project demonstrates object-oriented programming principles, smart pointers usage, and basic file system operations.

## Features-1

- **Object-Oriented Design**: Clean class hierarchy with `FileSystemNode`, `File`, and `Directory` classes
- **Smart Pointer Memory Management**: Uses `shared_ptr` and `weak_ptr` to avoid memory leaks and circular references
- **Basic File System Commands**: Supports `mkdir`, `touch`, `ls`, `cd`, `pwd`, and `rm`
- **Path Navigation**: Supports both absolute and relative paths
- **Cross-Platform**: Works on macOS, Linux, and other Unix-like systems

## Project Structure

```
fs-simulator/
├── FileSystemNode.h     # Abstract base class for file system nodes
├── FileSystemNode.cpp   # Implementation of base class
├── File.h              # File class declaration
├── File.cpp            # File class implementation
├── Directory.h         # Directory class declaration
├── Directory.cpp       # Directory class implementation
├── FileSystemSimulator.h # Main simulator class declaration
├── FileSystemSimulator.cpp # Main simulator implementation
├── main.cpp            # Entry point
├── Makefile            # Build configuration
└── README.md           # This file
```

## Requirements

- **Compiler**: Clang++ or G++ with C++17 support
- **Operating System**: macOS, Linux, or Unix-like system
- **Make**: For building the project

## Building the Project

### Quick Build and Run
```bash
make run
```

### Standard Build
```bash
make
```

### Debug Build
```bash
make debug
```

### Release Build
```bash
make release
```

### Clean Build Artifacts
```bash
make clean
```

## Usage

Run the simulator:
```bash
./filesystem_simulator
```

### Available Commands

- `mkdir <directory_name>` - Create a new directory
- `touch <file_name>` - Create a new empty file
- `ls` - List contents of current directory
- `cd <path>` - Change directory (supports `.`, `..`, `/`, and directory names)
- `pwd` - Print current working directory path
- `rm <name>` - Remove file or directory
- `help` - Show available commands
- `exit` or `quit` - Exit the simulator

### Example Session

```
=== File System Simulator ===
Type 'help' for available commands or 'exit' to quit.
/ $ mkdir documents
Directory 'documents' created
/ $ mkdir photos
Directory 'photos' created
/ $ ls
[DIR]  documents
[DIR]  photos
/ $ cd documents
/documents $ touch readme.txt
File 'readme.txt' created
/documents $ touch notes.txt
File 'notes.txt' created
/documents $ ls
[FILE] readme.txt (0 bytes)
[FILE] notes.txt (0 bytes)
/documents $ cd ..
/ $ pwd
/
/ $ rm photos
Removed 'photos'
/ $ ls
[DIR]  documents
/ $ exit
Goodbye!
```

## Architecture Details

### Class Hierarchy

- **`FileSystemNode`**: Abstract base class defining the interface for all file system objects
- **`File`**: Represents a file with content storage
- **`Directory`**: Represents a directory that can contain other nodes, uses `enable_shared_from_this`

### Memory Management

The project uses modern C++ smart pointers for automatic memory management:

- **`shared_ptr`**: For shared ownership of file system nodes
- **`weak_ptr`**: For parent references to prevent circular dependencies
- **`enable_shared_from_this`**: Allows directories to safely create shared pointers to themselves

### Key Design Decisions

1. **Circular Reference Prevention**: Parent-child relationships use `weak_ptr` for parent references
2. **Type Safety**: Enum class for node types and proper casting
3. **RAII**: Automatic resource management through smart pointers
4. **Const Correctness**: Proper const methods and parameters

## Installation

To install the simulator system-wide:
```bash
make install
```

To uninstall:
```bash
make uninstall
```

## Development

### Makefile Targets

- `make` or `make all` - Build the project
- `make clean` - Remove build artifacts
- `make run` - Build and run
- `make debug` - Build with debug flags
- `make release` - Build with optimizations
- `make install` - Install to `/usr/local/bin`
- `make uninstall` - Remove from system
- `make dist` - Create distribution package
- `make help` - Show available targets

### Compiler Optimizations for Apple Silicon

The Makefile is optimized for macOS M3 Pro with:
- `-arch arm64` for Apple Silicon architecture
- Clang++ as the default compiler
- Appropriate optimization flags

## Contributing

Feel free to extend the simulator with additional features such as:
- File content editing
- Copy and move operations
- Permissions system
- File search functionality
- Tree view display

## License

This project is provided as an educational example and is free to use and modify.
