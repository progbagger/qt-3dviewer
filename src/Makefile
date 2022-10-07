##########################
# Variables to be edited #
##########################

CFILES = list.c obj_parcer.c affine.c
HEADERS = list.h obj_parcer.h affine.h
SLIB = parcer.a
DFLAGS =
TMAIN = tests.c
GCOV_FOLDER = report
PROJECT_NAME = 3DViewer
MODELS_PATH = ./models

####################
# Common variables #
####################

SHELL = /bin/bash
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wshadow -std=c11
OBJ = $(CFILES:.c=.o)
TEXEC = $(TMAIN:.c=_exec)
OS = $(shell uname)

TFLAGS = -lcheck
ifeq ($(OS), Linux)
TFLAGS += -lm -lpthread -lrt -lsubunit
OPEN_CMD = xdg-open
endif
ifeq ($(OS), Darwin)
OPEN_CMD = open
endif

GOBJ = $(CFILES:.c=_gcov.o)
GEXEC = $(TMAIN:.c=_gcov)
GFLAGS = --coverage

###########
# Targets #
###########

all: style cppcheck dvi tests install

create_tests: $(TMAIN:.c=.check)
	@checkmk clean_mode=1 $(TMAIN:.c=.check) > $(TMAIN)
	@clang-format --style=file -i $(TMAIN)

style:
	@clang-format -n *.c *.h ./$(PROJECT_NAME)/*.cpp ./$(PROJECT_NAME)/*.h

cppcheck:
	-@cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

leaks: $(TEXEC)
ifeq ($(OS), Darwin)
	@echo 'Starting "leaks"...'
	@CK_FORK=no leaks --atExit -q -- ./$(TEXEC)
else
	@echo 'Starting "valgrind"...'
	@CK_FORK=no valgrind --leak-check=full -s -- ./$(TEXEC)
endif
	@echo "Done"

install:
	@echo "Building an application..."
	@mkdir -p App
	@mkdir -p Build
	cd ./Build && qmake6 ../$(PROJECT_NAME)
	cd ./Build && make
	@echo "Done"
	@echo -n "Moving application into 'App' directory..."
ifeq ($(OS), Darwin)
	@mv ./Build/$(PROJECT_NAME).app/Contents/MacOS/$(PROJECT_NAME) ./App/$(PROJECT_NAME).app
else
	@mv ./Build/$(PROJECT_NAME) ./App/$(PROJECT_NAME)
endif
	@echo " Done"
	@echo "Installation complete."

uninstall:
	@echo -n "Uninstalling application..."
	@rm -rf ./App
	@echo " Done"
	@echo "Uninstallation complete."

tests: $(TEXEC)
	@echo " Done"
	@echo "Starting tests..."
	@./$(TEXEC)
	@echo "Done"

$(TEXEC): $(OBJ)
	@$(CC) $(CFLAGS) $(DFLAGS) $(TMAIN) $(OBJ) $(TFLAGS) -o $(TEXEC)

$(OBJ): $(CFILES)
	@echo -n "Building tests..."
	@$(CC) $(CFLAGS) $(DFLAGS) -c $(CFILES)

dvi:
	@echo -n "Opening documentation..."
	@$(OPEN_CMD) ./Docs/documentation.html
	@echo " Done"

dist:
	@echo "Creating archive '$(PROJECT_NAME).tar.gz'..."
	@mkdir -p ./$(PROJECT_NAME)_v1.0
	@cp *.c ./$(PROJECT_NAME)_v1.0
	@cp *.h ./$(PROJECT_NAME)_v1.0
	@cp Makefile ./$(PROJECT_NAME)_v1.0
	@cp -r Docs ./$(PROJECT_NAME)_v1.0
	@cp -r Qtgifimage ./$(PROJECT_NAME)_v1.0
	@cp -r $(PROJECT_NAME) ./$(PROJECT_NAME)_v1.0
	@cp .clang-format ./$(PROJECT_NAME)_v1.0
	@cp $(TMAIN:.c=.check) ./$(PROJECT_NAME)_v1.0
	@cp -r $(MODELS_PATH) ./$(PROJECT_NAME)_v1.0
	@tar -cf $(PROJECT_NAME)_v1.0.tar.gz ./$(PROJECT_NAME)_v1.0
	@rm -rf ./$(PROJECT_NAME)_v1.0
	@echo "Done"

gcov: clean $(GEXEC)
	@echo "Generating GCOV report..."
	@./$(GEXEC) > /dev/zero 2> /dev/zero
	@lcov -t "Coverage report" -o $(GCOV_FOLDER).info -c -d .
	@genhtml -o $(GCOV_FOLDER) $(GCOV_FOLDER).info
	@$(OPEN_CMD) ./$(GCOV_FOLDER)/index.html
	@echo "GCOV report created."

$(GEXEC): $(GOBJ)
	@$(CC) $(CFLAGS) $(DFLAGS) $(TMAIN) $(OBJ) $(TFLAGS) $(GFLAGS) -o $(GEXEC)

$(GOBJ): $(CFILES)
	@$(CC) $(CFLAGS) $(DFLAGS) -c $(CFILES) $(TFLAGS) $(GFLAGS)

clean:
	@echo -n "Started cleanup..."
	@rm -rf *.o *.out *.gcda *.gch *.gcno *.gcov $(TEXEC) $(GEXEC) $(GCOV_FOLDER) Build build-* *.info
	@echo " Done"