# Compiler and flags
CC = gcc
CFLAGS = -lcrypto -lqrencode -ljpeg
SRC = main.c input.c encryption.c qr.c
OUT_DIR = ../app
OUT_NAME = qrgen
OUT_PATH = $(OUT_DIR)/$(OUT_NAME)

# Targets
all: $(OUT_PATH)

$(OUT_PATH): $(SRC)
	$(CC) $(SRC) -o $(OUT_PATH) $(CFLAGS)

# Clean target
clean:
	rm -f $(OUT_PATH)

.PHONY: all clean