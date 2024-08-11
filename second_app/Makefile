CC=g++ 
VERSION=-std=c++2a
OUTPUT=./second_app.out

SRCS:=$(wildcard ../utilities/src/*.cpp)
SRCS+=$(wildcard ./src/*.cpp)

.PHONY:build
build:
	$(CC) $(VERSION) $(SRCS) -DLOG -o $(OUTPUT)

.PHONY:run
run:clean build
	$(OUTPUT)
.PHONY:clean
clean:
	rm -rf $(OUTPUT)