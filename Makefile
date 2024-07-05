# Путь к каталогу cJSON
CJSON_DIR = ./cJSON

# Имя вашего исходного файла и исполняемого файла
SRC = test.c
TARGET = json_example

# Компилятор и флаги
CC = gcc
CFLAGS = -I$(CJSON_DIR) -Wall -Wextra
LDFLAGS = -L$(CJSON_DIR) -lcjson

# Правило по умолчанию: собрать и связать проект
all: $(TARGET)

# Правило для сборки cJSON
$(CJSON_DIR)/libcjson.a:
	@echo "Building cJSON library..."
	$(MAKE) -C $(CJSON_DIR)

# Правило для сборки вашего проекта
$(TARGET): $(SRC) $(CJSON_DIR)/libcjson.a
	@echo "Building $(TARGET)..."
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Правило для установки cJSON
install-cjson:
	@echo "Installing cJSON library..."
	cp $(CJSON_DIR)/libcjson.a /usr/local/lib/
	cp $(CJSON_DIR)/cJSON.h /usr/local/include/
	ldconfig

# Правило для очистки
clean:
	@echo "Cleaning up..."
	$(MAKE) -C $(CJSON_DIR) clean
	rm -f $(TARGET)

.PHONY: all clean install-cjson
