SRC    = src
BUILD  = build
LIB    = lib
CFLAGS = -Wall -O3 -std=c11
LIBS   = -ldl

.PHONY: all
all: main $(LIB)/libfunction.so

# main executable
main: $(BUILD)/main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# shared lib
$(LIB)/lib%.so: $(BUILD)/%.o | $(LIB)
	$(CC) $(CFLAGS) -shared -o $@ $^

# source files
$(BUILD)/%.o: $(SRC)/%.c | $(BUILD)
	$(CC) $(CFLAGS) -fPIC -c -o $@ $^

$(BUILD):
	mkdir -p $(BUILD)

$(LIB):
	mkdir -p $(LIB)

# .PHONY: clean
clean:
	rm -rf $(BUILD)
	rm -rf $(LIB)
	rm -f main
