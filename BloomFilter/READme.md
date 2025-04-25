**Note:** This is from a first-year assignment in an Intermediate C++ course back in 2021.

# Bloom Filter CLI

A simple command-line utility that implements a Bloom filter for efficient string filtering.

## Overview

This program provides a probabilistic data structure (Bloom filter) that tests whether an element is a member of a set. The implementation can:

1. Build a filter from stdin input (first execution)
2. Use a previously built filter to test strings (subsequent executions)

## Project Structure

- `filter.h` - Header file containing the Bloom filter class declaration
- `main.cpp` - Main program implementation

## Features

- Fast, memory-efficient filtering of strings
- False positives are possible, but false negatives are not
- Simple command-line interface
- Supports piping and redirection

## Usage

### Building a filter

```bash
./bloom_filter > filter.dat
```
Enter strings (one per line) that you want to add to the filter. Press Ctrl+D (EOF) when done.

### Using a filter

```bash
./bloom_filter filter.dat
```
Enter strings (one per line) that you want to test against the filter. Only strings that might be in the original set will be output.

## Technical Details

- Uses a 1024-byte bloom filter (8192 bits)
- Implements a simple hash function
- False positive rate depends on the number of strings added to the filter

## Example Workflow

1. Build a filter with a list of allowed words:
   ```bash
   cat allowed_words.txt | ./bloom_filter > filter.dat
   ```

2. Filter a list of words to only show potentially allowed ones:
   ```bash
   cat words_to_check.txt | ./bloom_filter filter.dat
   ```

## Notes

- A result of "true" means the string *might* be in the original set
- A result of "false" means the string is *definitely not* in the original set
- The filter is saved as a binary file that can be reused for subsequent filtering operations
