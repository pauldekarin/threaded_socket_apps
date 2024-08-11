CC=g++ 
CFLAGS=-std=c++2a
OUTPUT=second_app.out
DEBUG_FLAG=-DLOG

# Источники
SRCS := $(wildcard ../utilities/src/*.cpp) $(wildcard ./src/*.cpp)

# Директория где хранится сборка
BUILD_DIR := ./build
OBJS_DIR := $(BUILD_DIR)/obj_files

# Преобразование пути к объектным файлам, сохраняя структуру каталогов
OBJS := $(SRCS:../utilities/src/%.cpp=$(OBJS_DIR)/utilities/%.o) $(SRCS:./src/%.cpp=$(OBJS_DIR)/%.o)
OBJS := $(filter-out %.cpp, $(OBJS))

.PHONY: all
all:build

.PHONY: build
build: $(OUTPUT)

#Сборка исполняемого файла в отладочном режиме
.PHONY:build_debug
build_debug:CFLAGS+=$(DEBUG_FLAG)
build_debug:$(OUTPUT)

# Сборка исполняемого файла из объектных файлов
$(OUTPUT): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -DLOG -o $(BUILD_DIR)/$@

# Компиляция каждого .cpp файла в объектный файл
$(OBJS_DIR)/utilities/%.o: ../utilities/src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: ./src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: run
run:
	$(BUILD_DIR)/$(OUTPUT)

.PHONY:rebuild
rebuild:clean build

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
