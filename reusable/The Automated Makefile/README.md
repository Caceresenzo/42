# The Automated Makefile

An already written Makefile to allow faster usage. Able to `make update` itself.

## Configuration

### Target

```
TARGET					= program			# output compiled binary file
```

### Flags & Compiler

```
COMPILER				= gcc				# compiled used for every files

FRAMEWORKS				= OpenGL AppKit		# frameworks that will be linked with flag -framework
FLAGS					= -Wall -g3 -O0     # flags used for every files
TARGET_REQUIRED_FLAGS	= -pthread			# target specific flags
```

### Update


```makefile
FIX_SOURCE_EXT			= c			# sources file extension
FIX_HEADER_EXT			= h			# headers file extension
FIX_GO_DEEPER			= false		# whether or not the update should try to look for files deeper that the directory 

FIX_SOURCES_DIR			= .			# sources file directory
FIX_HEADERS_DIR			= .			# headers file directory
FIX_LIBRARIES_DIR		= .			# libraries file directory
```

## Usage

```
$ make update
$ make
```

