# Compiler and flags
CXX = g++
CFLAGS = -I/usr/include/opencv4 -lcrypt -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui -lssl -lcrypto -lzbar
SRC = decode.cpp main.c decryption.c
OUT_DIR = ../app
OUT_NAME = decode
OUT_PATH = $(OUT_DIR)/$(OUT_NAME)

# Targets
all: $(OUT_PATH)

$(OUT_PATH): $(SRC)
	$(CXX) $(SRC) -o $(OUT_PATH) $(CFLAGS)

# Clean target
clean:
	rm -f $(OUT_PATH)

.PHONY: all clean
