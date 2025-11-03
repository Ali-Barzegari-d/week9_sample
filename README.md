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
- **Exercise 2 — PluginLoader** – a runtime dynamic-loader for math plugins (shared libraries), demonstrating `extern "C"` exports, dlopen/dlsym usage, and ABI/version handling.
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

## 6. Task D — PluginLoader

Design a **runtime plugin-based math system**.  
The main program dynamically loads a shared library (`libmath.so` or `.dll`), retrieves function pointers,  
and calls them at runtime.  
This simulates real-world **C++ packaging**, **ABI stability**, and **versioning management**.


### Required Behavior
- Implement a shared library (`mathlib`) with:
  - `add`, `mul`, and `mean` functions (`extern "C"`).
  - `version()` returning `"MathLib v1.0"`.
  - `mean` returns `0.0` if size ≤ 0.

- Implement `PluginLoader` that:
  - Loads the library using `dlopen` and retrieves symbols via `dlsym`.
  - Closes the handle in the destructor (RAII).
  - Provides:
    - `is_loaded()`
    - `get_version()`
    - `call_add`, `call_mul`, `call_mean`
  - Throws `std::runtime_error` if a symbol is missing.

### Concepts Covered
- Shared libraries vs static libraries
- extern "C" linkage and name-mangling control
- Dynamic symbol loading using dlopen and dlsym
- ABI versioning and stable exported interfaces
- Exception safety and RAII for external resources

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
