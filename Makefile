# Pencli Makefile

CC = clang
CFLAGS = -Wall
TARGET = pencli
INSTALL_DIR = /usr/local/bin

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c -lrt

install: $(TARGET)
	sudo cp $(TARGET) $(INSTALL_DIR)
	sudo ln -sf $(INSTALL_DIR)/$(TARGET) $(INSTALL_DIR)/pc
	@echo "Install complete! You can now use 'pencli' or 'pc'."

uninstall:
	sudo rm -f $(INSTALL_DIR)/$(TARGET)
	sudo rm -f $(INSTALL_DIR)/pc
	@echo "Uninstalled pencli and pc."

clean:
	rm -f $(TARGET)
