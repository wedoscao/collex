# Collex

This repository is a C library implementing basic data structures.

---

## Requirements

- [GCC](https://gcc.gnu.org/) 
- [GNU Make](https://www.gnu.org/software/make/)

## Installation Guide

1. Clone this repository:
```bash
git clone https://github.com/wedoscao/collex collex
```
2. Build the static library file:
```bash
cd collex && make build
```
## Usage
Link libcollex.a with your project:
```bash
gcc -o my_program my_program.c -L/path/to/collex/build -lcollex
```

## License
[**MIT**](https://github.com/wedoscao/collex/blob/master/LICENSE)
