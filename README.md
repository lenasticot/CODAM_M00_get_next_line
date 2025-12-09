*This project has been created as part of the 42 curriculm by leodum*

# Get_next_line

## Description

### Presentation of the project

get_next_line is a C function that reads and returns a single line from a file descriptor. The function is designed to be called repeatedly to read a file line by line, making it useful for text processing and file parsing applications.

### Goal
The primary goal of this project is to:
- Understand and implement static variables in C
- Master dynamic memory allocation and management
- Handle file I/O operations efficiently
- Deal with varying buffer sizes and edge cases (EOF, empty files, files without newlines)

### Brief Overview

The function reads from a file descriptor in chunks (defined by BUFFER_SIZE) and manages leftover data between calls using a static variable. Each call returns exactly one line (including the newline character if present), or NULL when the end of file is reached or an error occurs.

## Instructions 

### Compilation

The project must be compiled with a defined BUFFER_SIZE:
`cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o`

You can change the BUFFER_SIZE value to test different behaviors:

**Small buffer (stress test)**
`cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c -o`

**Large buffer**
`cc -Wall -Wextra -Werror -D BUFFER_SIZE=1000000 get_next_line.c get_next_line_utils.c -o`

### Memory Management
**Important**: The caller is responsible for freeing the memory returned by get_next_line. Each line must be freed after use to prevent memory leaks.
### Testing
To test for memory leaks:
`valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./a.out`




## Resources
### Documentation & References

**C Programming & File I/O:**
- [Linux man pages - read(2)](https://man7.org/linux/man-pages/man2/read.2.html)
- [Linux man pages - open(2)](https://man7.org/linux/man-pages/man2/open.2.html)
- [Static variables in C](https://www.geeksforgeeks.org/static-variables-in-c/)

**Memory Management:**
- [Dynamic Memory Allocation in C](https://www.programiz.com/c-programming/c-dynamic-memory-allocation)
- [Valgrind User Manual](https://valgrind.org/docs/manual/manual.html)

**42 Network:**
- [42 Norm](https://github.com/42School/norminette)

**Youtube videos**
- [Get_next_line explained : develop a function that reads a file line by line](https://www.youtube.com/watch?v=8E9siq7apUU)
- [Comprendre get_next_line](https://www.youtube.com/watch?v=-Mt2FdJjVno&t=1s)
- [Read A Specific Line From A File | C Programming Example](https://www.youtube.com/watch?v=w0mgn6OLKUs)

### AI Usage

AI (Claude by Anthropic) was used as a **code review partner and debugging assistant** during the development of this project:

**Tasks where AI was used:**
- **Debugging:** Identifying memory leaks, segmentation faults, and logic errors
- **Conceptual understanding:** Explaining static variables, pointer arithmetic, and file descriptor behavior
- **Code review:** Suggesting improvements for edge case handling and error management
- **Testing strategy:** Guidance on comprehensive test cases and valgrind interpretation

**Parts developed independently:**
- Core algorithm design and implementation
- All function logic and structure
- Memory management strategy
- Problem-solving approach for edge cases

**Learning approach:**
Rather than providing ready-made solutions, AI acted as a **Socratic mentor**, asking guiding questions to help develop understanding:
- "What happens to this pointer after this operation?"
- "Trace through what happens with an empty file"
- "Why would this cause a segfault?"

This approach ensured genuine learning and understanding of concepts rather than copy-pasting solutions.

	
## Additional sections

## Algorithm Explanation
	to be added bonus part?

### Design Choice: Buffer-Based Reading with Static Storage

The algorithm is based on a **persistent buffer approach** using a static variable to maintain state between function calls.

### Why This Approach?

1. **Efficiency:** Reads data in chunks (BUFFER_SIZE) rather than byte-by-byte, reducing system calls
2. **State Persistence:** Static variable preserves leftover data between calls without requiring the caller to manage state
3. **Memory Efficiency:** Only allocates memory for the current line being returned, not the entire file

### Algorithm Flow
```
┌─────────────────────────────────────────────────────────────┐
│                     get_next_line(fd)                       │
│                                                             │
│  1. Validate fd and BUFFER_SIZE                             │
│  2. Check static buffer for leftover data from previous call│
│     ├─ If complete line found → extract and return          │
│     └─ If partial data → append to result                   │
│                                                             │
│  3. Read from file in BUFFER_SIZE chunks                    │
│     ├─ Join new data with existing buffer                   │
│     ├─ Check for newline ('\n')                             │
│     │  ├─ Found → extract line, save remainder, return      │
│     │  └─ Not found → continue reading                      │
│     └─ EOF reached → return remaining data or NULL          │
└─────────────────────────────────────────────────────────────┘
```

### Key Functions

1. **`reading_file`**: Reads from fd until a newline is found or EOF is reached
2. **`extract_line`**: Extracts a complete line (up to and including `\n`) from the buffer
3. **`next_line`**: Saves everything after the newline for the next call
4. **`join_and_free`**: Efficiently concatenates strings while managing memory

### Justification

**Why not read byte-by-byte?**
- Would require one system call per character → extremely inefficient
- BUFFER_SIZE chunks minimize system calls while maintaining flexibility

**Why use a static variable instead of returning a struct with state?**
- Simpler API: caller doesn't need to manage state
- Cleaner interface: function signature remains simple
- Standard practice for this type of function

**Trade-offs:**
- Can handle multiple file descriptors simultaneously (limitation of single static variable)
- Simple, clean API
- Efficient memory usage
- Handles variable-length lines gracefully

---

## Features

- Reads one line at a time from any valid file descriptor
- Handles files with or without final newline
- Works with stdin and regular files
- Configurable buffer size at compile time
- Proper error handling (invalid fd, read errors)
- Memory-efficient (no leaks when used correctly)
- Handles edge cases: empty files, very long lines, buffer size of 1



# Bonus Part
### Multiple File Descriptors Support
The bonus implementation extends the functionality to handle multiple file descriptors simultaneously while using only one static variable.
### How It Works
Instead of a single static buffer, the bonus uses a static array of buffers:

static char *buf[1024];


Each index corresponds to a file descriptor number:
- `buf[3]` stores the buffer for fd 3
- `buf[4]` stores the buffer for fd 4
- etc.

### Algorithm Explanation

**Array-Based State Management:**

The key insight is that file descriptors are small integers (typically 0-1023 on most systems). By using an array indexed by fd, we can maintain separate reading states for each open file simultaneously.

```
┌─────────────────────────────────────────┐
│     static char *buf[1024]              │
│                                         │
│  buf[0] → NULL                          │
│  buf[1] → NULL                          │
│  buf[2] → NULL                          │
│  buf[3] → "remaining data from file3\n" │
│  buf[4] → "partial line from file4"     │
│  buf[5] → "leftover from file5"         │
│  ...                                    │
│  buf[1023] → NULL                       │
└─────────────────────────────────────────┘
```

## Justification
### Why array size 1024?

- Standard POSIX systems typically limit fd numbers to 1024 (OPEN_MAX)
- Covers all practical use cases
- Memory is allocated lazily (only when fd is used)

### Trade-offs:

- Handles multiple files simultaneously
- Simple indexing (O(1) access)
- Each fd maintains independent state
- Higher memory footprint if many files open
- Fixed maximum (1024 fds)
