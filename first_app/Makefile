CC=g++ 
CFLAGS=-std=c++2a
OUTPUT=first_app.out
DEBUG_FLAG=-DLOG

# Источники
SRCS:=$(wildcard ../utilities/src/*.cpp) $(wildcard ./src/*.cpp)

# Директория где хранится сборка
BUILD_DIR = ./build
OBJS_DIR = $(BUILD_DIR)/objs_files

# Преобразование пути к объектным файлам, сохраняя структуру каталогов
OBJS := $(SRCS:../utilities/src/%.cpp=$(OBJS_DIR)/utilities/%.o) $(SRCS:./src/%.cpp=$(OBJS_DIR)/%.o)
OBJS := $(filter-out %.cpp, $(OBJS))


.PHONY:all
all:build

# Сборка исполняемого файла из объектных файлов
.PHONY:build
build:$(OUTPUT)

#Сборка исполняемого файла в отладочном режиме
.PHONY:build_debug
build_debug:CFLAGS+=$(DEBUG_FLAG)
build_debug:$(OUTPUT)

# Компиляция каждого .cpp файла в объектный файл
$(OUTPUT):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BUILD_DIR)/$(OUTPUT)

$(OBJS_DIR)/utilities/%.o: ../utilities/src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o : ./src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run:
	$(BUILD_DIR)/$(OUTPUT)

.PHONY:clean
clean:
	rm -rf $(BUILD_DIR)