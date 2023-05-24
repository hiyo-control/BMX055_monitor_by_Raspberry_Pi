
COMPILER = gcc
CFLAGS = -Wall
LDFLAGS = -lm

BUILD_DIR = build

HEADER  = ./include/arduino_acceleration.c
HEADER += ./include/arduino_acceleration.h

.PHONY: all clean

all: $(BUILD_DIR) $(BUILD_DIR)/test 

$(BUILD_DIR)/test: $(BUILD_DIR)/test.o
	$(COMPILER) $(CFLAGS) -o $@ $^ $(HEADER) $(LDFLAGS) -lwiringPi

$(BUILD_DIR)/test.o: test.c
	$(COMPILER) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean: $(BUILD_DIR)
	rm build/*