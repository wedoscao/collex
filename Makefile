.PHONY: help build test clean

CC := gcc
CFLAGS := -xc -Iinclude -Wall -Wextra -Werror -std=c99 -O2
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include
TESTS_DIR := tests

LIB_NAME := libcollex.a

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/obj/%.o, $(SRC_FILES))
TESTS_FILES := $(wildcard $(TESTS_DIR)/test_*.c)
TESTS_OUT   := $(patsubst tests/test_%.c, $(BUILD_DIR)/tests/test_%.out, $(TESTS_FILES))

help:
	@echo "This is a C library implementing basic data structures."
	@echo "Available targets:"
	@echo " help			- Show this help message"
	@echo " build			- Compile the library (libcollex.a)"
	@echo " test			- Build and run tests"
	@echo " clean			- Remove build artifacts"

build: $(BUILD_DIR)/$(LIB_NAME)

test: $(TESTS_OUT)
	@$(foreach t, $(TESTS_OUT), echo "Running $(t)" && ./$(t))

clean: 
	rm -rf $(BUILD_DIR)

$(BUILD_DIR)/$(LIB_NAME): $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR)
	ar rcs $@ $^

$(BUILD_DIR)/obj/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)/obj
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/tests/%.out: $(TESTS_DIR)/%.c $(BUILD_DIR)/$(LIB_NAME)
	@mkdir -p $(BUILD_DIR)/tests
	$(CC) $(CFLAGS) $< -L$(BUILD_DIR) -lcollex -o $@
