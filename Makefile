CFLAGS = -std=c18 -Iinclude

CFLAGS += -Wall -Wextra -Wpedantic
CFLAGS += -Wswitch-enum -Wstrict-prototypes -Wmissing-variable-declarations
CFLAGS += -fsanitize=address -g

# CFLAGS += -Weverything -Wno-padded -Wno-extra-semi-stmt -Wno-declaration-after-statement -Wno-covered-switch-default 
# CFLAGS += -Wno-format-nonliteral -Wno-double-promotion

.PHONY: clean build build-gdb run

build:
	@clang $(CFLAGS) src/*.c -o bin/neur.out

build-gdb:
	@clang $(CFLAGS) -ggdb3 src/*.c -o bin/neur-gdb.out

run: build
	@./bin/neur.out

clean:
	@rm -rf ./bin/*

SOURCE_FILES = $(filter-out ./src/main.c, $(wildcard ./src/*.c))
TEST_FILES = $(wildcard ./tests/*.c)

# A target that doesn't exist, so anything depending on it
# will be rebuilt everytime.
.FORCE:

tests/%.c: .FORCE
	@clang -o ./bin/test.out $(CFLAGS) $(SOURCE_FILES) $@ -w
	@echo "\033[4;33m"+ $@: "\033[0m"
	@if ./bin/test.out; then \
		echo "\033[1;32mPASS\033[0m"; \
	else \
		echo "\033[1;31mFAIL\033[0m"; \
	fi

test: $(TEST_FILES)