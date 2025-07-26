.PHONY: help build test clean

CC := gcc
CFLAGS := -Wall -Wextra -O2 
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include
TESTS_DIR := tests

LIB_NAME := libcollex.a

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/obj/%.o, $(SRC_FILES))
TESTS_FILES := $(wildcard $(TESTS_DIR)/*.c)
TESTS_OUT   := $(patsubst tests/%.c, $(BUILD_DIR)/tests/%.out, $(TESTS_FILES))

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
	$(CC) $(CFLAGS) $< $(BUILD_DIR)/$(LIB_NAME) -o $@
