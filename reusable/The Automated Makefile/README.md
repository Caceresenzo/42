# The Automated Makefile

An already written Makefile to allow faster usage. Able to `make update` itself.

## Configuration

### Target

```makefile
TARGET                  = program           # output compiled binary file
```

### Flags & Compiler

```makefile
COMPILER                = gcc               # compiled used for every files

FRAMEWORKS              = OpenGL AppKit     # frameworks that will be linked with flag -framework (can be empty)
FLAGS                   = -Wall -g3 -O0     # flags used for every files (can be empty)
TARGET_REQUIRED_FLAGS   = -pthread          # target specific flags (can be empty)
```

### Update


```makefile
FIX_SOURCE_EXT          = c         # sources file extension
FIX_HEADER_EXT          = h         # headers file extension
FIX_GO_DEEPER           = false     # whether or not the update should try to look for files deeper that the directory 

FIX_SOURCES_DIR         = .         # sources file directory
FIX_HEADERS_DIR         = .         # headers file directory
FIX_LIBRARIES_DIR       = .         # libraries file directory
```

## Usage

```bash
$ make update
$ make
```

