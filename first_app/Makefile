CC=g++ 
VERSION=-std=c++2a
OUTPUT=./first_app.out

SRCS:=$(wildcard ../utilities/src/*.cpp)
SRCS+=$(wildcard ./src/*.cpp)

.PHONY:run
run:clean build
	$(OUTPUT)

.PHONY:build
build:
	$(CC) $(VERSION) $(SRCS) -DLOG -o $(OUTPUT)

.PHONY:clean
clean:
	rm -rf $(OUTPUT)