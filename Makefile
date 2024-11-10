CFLAGS = -std=c18 -Iinclude

CFLAGS += -Wall -Wextra -Wpedantic
CFLAGS += -Wswitch-enum -Wstrict-prototypes -Wmissing-variable-declarations
# CFLAGS += -Weverything -Wno-padded -Wno-extra-semi-stmt -Wno-declaration-after-statement -Wno-covered-switch-default

.PHONY: clean build run

build:
	@clang $(CFLAGS) src/*.c -o bin/neur.out

run: build
	@./bin/neur.out

clean:
	@rm -rf ./bin/*