# Compiler to be used for building the project.
CC = gcc

# Compiler flags:
# -Wall: Enables all common warnings.
# -g: Generates debug information for use with a debugger.
# -O2: Optimizes code for performance.
CFLAGS = -Wall -g -O2

# Libraries to be linked:
# -lm: Links the math library.
LIBS = -lm

# List of targets to be built. These represent different sorting algorithms and overlap calculation.
sort_algorithms = sort_bubble sort_merge sort_quick sort_radix overlap

# The default target (when `make` is run without arguments).
# Builds all targets listed in `sort_algorithms`.
all: $(sort_algorithms)

# Rule to build the `sort_bubble` executable:
# - Depends on sort_bubble.o and utils.o.
# - Combines the object files to produce the executable.
sort_bubble: sort_bubble.o utils.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Rule to build the `sort_merge` executable:
# - Depends on sort_merge.o and utils.o.
sort_merge: sort_merge.o utils.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Rule to build the `sort_quick` executable:
# - Depends on sort_quick.o and utils.o.
sort_quick: sort_quick.o utils.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Rule to build the `sort_radix` executable:
# - Depends on sort_radix.o and utils.o.
sort_radix: sort_radix.o utils.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Rule to build the `overlap` executable:
# - Depends on overlap.o and utils.o.
overlap: overlap.o utils.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Phony target for cleaning up generated files.
# - Removes all object files (*.o) and executables listed in `sort_algorithms`.
.PHONY: clean
clean:
	rm -f *.o $(sort_algorithms)


