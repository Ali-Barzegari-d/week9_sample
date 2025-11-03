# CSI2372 — Week 9 Lab Handout

**Topic:** Exception Safety • RAII • Templates • Concepts • File I/O • Resource Management  
**Course:** Advanced Programming Concepts with C++ (Fall 2025, uOttawa)

---

## 1. Overview

In this lab, you will design and implement modular C++ libraries demonstrating conditional compilation,
static library design, and file-based persistence
You will implement four independent, autograded exercises that simulate real-world components used in build systems and plugin-based architectures.

This lab contains four graded exercises:

- **Exercise 1 — BuildStats** – a modular library to collect and report build statistics (file I/O, formatting, preprocessor usage, RAII).  
- **Exercise 2 — Snapshot Serializer** – a template-based binary snapshot utility that saves and restores data from files, demonstrating file I/O, RAII, templates, and conditional compilation.
- **Exercise 3 — Flexible Data Archiver** – Implement a modular library that converts text files into a compact binary format and optionally restores them using conditional compilation.
- **Exercise 4 — Smart Translation Cache** – Develop a file-based translation cache that stores and retrieves string translations, supporting read-only and clear-on-start modes via preprocessor flags.

All work is autograded via CI/CTest.  
When the GitHub Actions build is green, you earn full marks.

---

## 2. Learning Objectives

By the end of this lab, you should be able to:

- Apply RAII for safe resource lifetime management (files, dynamic handles).  
- Use preprocessor macros to enable/disable debug behavior.  
- Separate interface and implementation (headers vs sources) and follow include-guard hygiene.  
- Build and test a header/cpp library and a runtime plugin loader.  
- Understand basic ABI/version concerns when exposing library APIs.  
- Use file I/O and formatted output to produce machine- and human-readable reports.  
- Work with dynamic loading APIs (`dlopen`/`dlsym`) and function pointers.
- Apply conditional compilation (#if defined(...)) to control optional features.
- Use namespaces to organize code logically.

---

## 3. Task A — Flexible Data Archiver

You will implement a small utility library for serializing and deserializing text data.  
The program must support two modes: a default **archive-only** mode, and a compile-time  
optional **restore** mode enabled via a preprocessor flag.

### Required Behavior

- The class `DataArchiver` accepts an input file path in its constructor.  
- `load_text()` opens a text file and stores all lines internally.  
- `save_binary(const std::string&)` writes all lines into a binary file in the following format:

```
[number of lines : size_t]
[line length : size_t][raw characters...]
...

```

sql
Copy code
- When compiled with `ENABLE_RESTORE`, two additional methods must be implemented:
- `restore_binary(const std::string&)` — reads from the binary file back into memory.  
- `print_restored()` — prints all restored lines to `std::cout`.  
- Handle file open failures gracefully.  
- Preserve all data exactly between read and write operations.  
- Follow **RAII** principles (no manual `close()` calls).

### Concepts Covered
- File I/O (text & binary)
- static library structure
- conditional compilation
- namespaces

---

## 4. Task B — Smart Translation Cache

You will implement a simple **translation memory system** using file persistence and conditional build modes.  
When translating a string, the system first checks a local cache file; if the translation exists,  
it returns it immediately. Otherwise, it generates a mock translation and stores it for future reuse.

### Required Behavior

- The class `TranslationCache` is initialized with a cache file name.  
- `load()` loads key/value pairs from file: every two lines represent one entry (`key` then `value`).  
- `translate(const std::string&)`:
- If the key exists in the cache, return its value.  
- Otherwise, generate a **fake translation** (reverse + uppercase of the input).  
- Save the new translation to the cache.  
- `save()` overwrites the cache file with all stored entries.  

**Conditional features:**
- `READONLY_CACHE`: disables saving new translations.  
- `CLEAR_ON_START`: clears the cache file before loading.  

Handle all file errors safely without throwing uncaught exceptions.  
Maintain deterministic results: translating the same word twice yields identical output.

### Concepts Covered
 - Preprocessor directives 
 - conditional compilation
 - file I/O
 - static library design, state persistence

---

## 5. Task C — BuildStats

Implement a **modular reporting library** that collects, aggregates, and stores build statistics  
(e.g., compile times, success rates).

### Required Behavior
mplement the `BuildStats` class (declared in `build_stats.hpp`).

#### Constructor
- Accepts a log file path.
- Ensures the file exists (creates it if missing).

#### `add_record(const ModuleStat&)`
- Appends a new record to memory.
- If `BUILD_DEBUG` is defined, print details (module name, compile time, success flag) to `std::cout`.

#### `avg_success_time()`
- Compute average compile time of successful modules.

#### `success_rate()`
- Compute percentage of successful modules.

#### `save_report()`
- Write a formatted report to the given log file.
- Include total count, success rate, average time, and per-module results.

#### `clear()`
- Clear in-memory records and truncate the log file.

#### `summary()`
- Return a short one-line summary string like:

### Concepts Covered
- RAII and file resource management  
- Modular header/source separation  
- Preprocessor macros for configurable logging  
- Stream-based report generation  
- Clean API design following **ODR** (One Definition Rule)

---

## 6. Task D — Snapshot Serializer

You will design and implement a **template-based binary snapshot utility**  
that can save and restore the state of objects to/from a binary file.  
The exercise focuses on **file I/O**, **RAII**, **templates**, and **conditional compilation**.  
Unlike previous template tasks, all implementation will be contained directly in the header file.

### Required Behavior

- The class `Snapshot` accepts a file path in its constructor.  

- `save(const std::vector<T>& data)`:
  - Opens the file in binary mode (truncates existing content).  
  - Writes the number of elements (`size_t`), then raw bytes of each element.  
  - Throws `std::runtime_error` if the file cannot be opened.  

- `load<T>()`:
  - Opens the file in binary read mode.  
  - Reads the element count and all stored values back into a `std::vector<T>`.  
  - Returns the reconstructed vector.  

- Uses **RAII** for automatic file management.  
- If `SNAPSHOT_LOG` is defined, print debug logs on save/load.  

### Concepts Covered
- Templates and generic programming  
- File I/O (binary mode)  
- RAII and exception safety  
- Conditional compilation for debug logging  
- Static library integration with CMake  

---

## 7. Building and Running

Recommended workflow:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```
CI/CTest runs automatically when you push.
All tests must pass for full credit.

## 8. Grading
100% autograded: your score = proportion of passing tests.

No manual grading.