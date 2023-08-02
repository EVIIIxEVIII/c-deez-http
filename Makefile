# Compiler
CC := gcc

SRC_DIR := src

SRC_FILES := $(shell find $(SRC_DIR) -name "*.c")

CFLAGS := -Wall -g

EXECUTABLE := run

$(EXECUTABLE): $(SRC_FILES)
	$(CC) $(CFLAGS) $^ -o $@

all: $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)

# Watch for changes and rebuild
watch:
	while true; do \
		inotifywait -e close_write -r $(SRC_DIR); \
		$(MAKE) all; \
	done

