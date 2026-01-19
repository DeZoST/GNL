# Get Next Line

## Overview

**Get Next Line** is a 42 school project written in **C**.
The goal is to implement a function that reads a file descriptor **line by line**, returning one line per call, while handling arbitrary buffer sizes and preserving unread data between calls.

This project focuses on low-level I/O, memory management, and state persistence, under strict constraints.

---

## Objective

Implement the following function:

```c
char *get_next_line(int fd);
```

Each call to `get_next_line()` must return the next line from the file descriptor `fd`, until the end of the file or an error occurs.

---

## Files Structure

```
.
├── get_next_line.c
├── get_next_line_utils.c
└── get_next_line.h
```

---

## Function Specification

### Prototype

```c
char *get_next_line(int fd);
```

### Parameters

* `fd`: File descriptor to read from

### Return Value

* A pointer to the next line read (including `\n` if present)
* `NULL` if:

  * There is nothing left to read
  * An error occurs

---

## Behavior & Rules

* The function reads the file **incrementally**
* Each call returns **exactly one line**
* The returned line:

  * Includes the terminating `\n` if present
  * Excludes it only if EOF is reached and the file does not end with `\n`
* Works with:

  * Regular files
  * Standard input (`stdin`)
* The function must **not** read the entire file at once
* Reading stops as soon as a newline is found

---

## Compilation

The project must compile with or without the `BUFFER_SIZE` macro.

Example:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

* `BUFFER_SIZE` defines the number of bytes read per `read()` call
* The implementation must handle extreme values:

  * `BUFFER_SIZE = 1`
  * Very large values (e.g. `9999`, `10000000`)

---

## Constraints

### Allowed Functions

* `read`
* `malloc`
* `free`

### Forbidden

* `libft`
* `lseek()`
* Global variables

---

## Architecture Overview

### Design Choice

The implementation uses:

* A **static local buffer (stash)** to persist unread data across calls
* A **pipeline-based architecture**:

  1. Read from the file descriptor into a temporary buffer
  2. Append data to a persistent stash
  3. Stop reading when a newline is detected or EOF is reached
  4. Extract one line from the stash
  5. Preserve the remainder for the next call

This approach satisfies all project constraints while ensuring correctness and efficiency.

---

## Main Components

* **Buffer Reader**

  * Handles `read()` calls
  * Appends data to the stash
  * Stops early when a newline is found

* **Stash Manager**

  * Stores unread data between calls using a static variable

* **Line Extractor**

  * Extracts one line from the stash
  * Ensures correct `\n` handling

* **Remainder Handler**

  * Removes the extracted line from the stash
  * Preserves leftover data

* **String Utilities**

  * Custom implementations of common string functions
  * Required due to `libft` being forbidden

---

## Trade-offs & Decisions

### Why a Static Stash?

* Global variables are forbidden
* Static local variables are the only legal way to persist state across calls

### Why Incremental Reading?

* Required by the subject
* Prevents excessive memory usage
* Works correctly with all `BUFFER_SIZE` values

### Known Limitations

* Assumes a single file descriptor (bonus not implemented)
* Binary file behavior is undefined (as allowed by the subject)

---
