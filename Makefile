# Путь к каталогу cJSON
CJSON_DIR = ./include/cJSON

# Имя вашего исходного файла и исполняемого файла
SRC = test.c
TARGET = json_example

# Компилятор и флаги
CC = gcc
CFLAGS = -I$(CJSON_DIR) -Wall -Wextra
LDFLAGS = -L$(CJSON_DIR)/build -lcjson -Wl,-rpath,$(CJSON_DIR)/build

# Правило по умолчанию: собрать и связать проект
all: $(TARGET)

# Правило для сборки cJSON
$(CJSON_DIR)/build/libcjson.a:
	@echo "Building cJSON library..."
	cd $(CJSON_DIR) && mkdir -p build && cd build && cmake .. && make

# Правило для сборки вашего проекта
$(TARGET): $(SRC) $(CJSON_DIR)/build/libcjson.a
	@echo "Building $(TARGET)..."
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Правило для установки cJSON
install-cjson: $(CJSON_DIR)/build/libcjson.a
	@echo "Installing cJSON library..."
	sudo cp $(CJSON_DIR)/build/libcjson.a /usr/local/lib/
	sudo cp $(CJSON_DIR)/build/libcjson.so /usr/local/lib/
	sudo cp $(CJSON_DIR)/cJSON.h /usr/local/include/
	sudo ldconfig

# Правило для очистки
clean:
	@echo "Cleaning up..."
	cd $(CJSON_DIR)/build && make clean
	rm -f $(TARGET)

.PHONY: all clean install-cjson
