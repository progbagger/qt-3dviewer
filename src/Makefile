CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -Wextra -Wshadow

DIR_MODEL = model
DIR_CONTROLLER = controller
DIR_VIEW = view
DIR_TESTS = tests
DIR_BUILD = build
DIR_APP = app

APP_NAME = 3DViewer_v2

PROJECT_DIRS = $(DIR_MODEL) $(DIR_TESTS) $(DIR_CONTROLLER) $(DIR_VIEW)

CXXPATHS = $(addprefix -I, $(PROJECT_DIRS))

CXXFLAGS += $(CXXPATHS)

CXX_FILES_MODEL = $(wildcard $(DIR_MODEL)/*.cc)
H_FILES_MODEL = $(wildcard $(DIR_MODEL)/*.h)
OBJ_FILES_MODEL = $(addprefix $(DIR_BUILD)/, $(notdir $(CXX_FILES_MODEL:.cc=.o)))

CXX_FILES_CONTROLLER = $(wildcard $(DIR_CONTROLLER)/*.cc)
H_FILES_CONTROLLER = $(wildcard $(DIR_CONTROLLER)/*.h)
OBJ_FILES_CONTROLLER = $(addprefix $(DIR_BUILD)/, $(notdir $(CXX_FILES_CONTROLLER:.cc=.o)))

CXX_FILES_TESTS = $(wildcard $(DIR_TESTS)/*.cc)
H_FILES_TESTS = $(wildcard $(DIR_TESTS)/*.h)
OBJ_FILES_TESTS = $(addprefix $(DIR_BUILD)/, $(notdir $(CXX_FILES_TESTS:.cc=.o)))

CXX_FILES_ALL = $(CXX_FILES_MODEL) $(CXX_FILES_CONTROLLER) $(CXX_FILES_TESTS)
H_FILES_ALL = $(H_FILES_MODEL) $(H_FILES_CONTROLLER) $(H_FILES_TESTS)

OBJ_FILES = $(OBJ_FILES_MODEL) $(OBJ_FILES_CONTROLLER) $(OBJ_FILES_TESTS)

GTESTFLAGS = -lgtest -lgtest_main
GTESTEXEC = $(DIR_BUILD)/tests.out

$(DIR_BUILD)/%.o: $(DIR_MODEL)/%.cc
	@echo -n 'Compiling $@ from $<...'
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo ' done'

$(DIR_BUILD)/%.o: $(DIR_CONTROLLER)/%.cc
	@echo -n 'Compiling $@ from $<...'
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo ' done'

$(DIR_BUILD)/%.o: $(DIR_TESTS)/%.cc
	@echo -n 'Compiling $@ from $<...'
	@$(CXX) $(CXXFLAGS) -c $< $(GTESTFLAGS) -o $@
	@echo ' done'

SHELL = /bin/bash
OS = $(shell uname)

all: install

# Compiling

create_build_dir:
	@echo -n 'Making $(DIR_BUILD) directory...'
	@mkdir -p $(DIR_BUILD)
	@echo ' done'

build_tests: create_build_dir $(OBJ_FILES)
	@echo 'Compiling tests executable...'
	@$(CXX) $(CXXFLAGS) $(OBJ_FILES) $(GTESTFLAGS) -o $(GTESTEXEC)
	@echo 'Compiling tests executable - done'

tests: build_tests
	@echo 'Starting tests...'
	@./$(GTESTEXEC)
	@echo 'Starting tests - done'

create_app_dir:
	@echo -n 'Making $(DIR_APP) directory...'
	@mkdir -p $(DIR_APP)
	@echo ' done'

install: uninstall create_build_dir create_app_dir
	@echo "Installing application..."
	@cd $(DIR_BUILD); cmake ../
	@cd $(DIR_BUILD); make all
ifeq ($(OS), Linux)
	@mv $(DIR_BUILD)/Viewer2 $(DIR_APP)/$(APP_NAME)
endif
ifeq ($(OS), Darwin)
	@mv $(DIR_BUILD)/Viewer2.app $(DIR_APP)/$(APP_NAME).app
endif
	@echo "Application situated in $(DIR_APP) directory. Use 'make run' to start application."

run: install
	@echo "Running application..."
ifeq ($(OS), Linux)
	@./$(DIR_APP)/$(APP_NAME)
endif
ifeq ($(OS), Darwin)
	@open ./$(DIR_APP)/$(APP_NAME).app
endif
	@echo "Done"

uninstall:
	@echo -n "Uninstalling application..."
	@rm -rf $(DIR_APP)
	@echo " done"

# Other

dvi:
	@echo -n "Opening documentation..."
	@open ../docs/index.html
	@echo " done"

dist:
	@echo -n "Creating project archive..."
	@mkdir $(APP_NAME)
	@cp -r $(DIR_MODEL) $(DIR_CONTROLLER) $(DIR_VIEW) shaders assets external CMakeLists.txt Makefile resources.qrc main.cc fonts $(APP_NAME)/
	@tar -zcf $(APP_NAME).tar $(APP_NAME)
	@rm -rf $(APP_NAME)
	@echo " done"

# GCOV report targets

GCOVFLAGS = --coverage
GCOVEXEC = $(DIR_BUILD)/tests_gcov.out
SUFFIX_GCOV = _gcov
DIR_REPORT = report

OBJ_FILES_GCOV = $(addsuffix $(SUFFIX_GCOV).o, $(basename $(OBJ_FILES_MODEL) $(OBJ_FILES_CONTROLLER))) $(OBJ_FILES_TESTS)

$(DIR_BUILD)/%$(SUFFIX_GCOV).o: $(DIR_MODEL)/%.cc
	@echo -n 'Compiling $@ from $<...'
	@$(CXX) $(CXXFLAGS) -O0 -c $< $(GCOVFLAGS) -o $@
	@echo ' done'

$(DIR_BUILD)/%$(SUFFIX_GCOV).o: $(DIR_CONTROLLER)/%.cc
	@echo -n 'Compiling $@ from $<...'
	@$(CXX) $(CXXFLAGS) -O0 -c $< $(GCOVFLAGS) -o $@
	@echo ' done'

$(GCOVEXEC): create_build_dir $(OBJ_FILES_GCOV)
	@echo 'Compiling executable for GCOV report...'
	@$(CXX) $(CXXFLAGS) -O0 $(OBJ_FILES_GCOV) $(GTESTFLAGS) $(GCOVFLAGS) -o $(GCOVEXEC)
	@echo 'Compiling executable for GCOV report - done'

gcov_report: $(GCOVEXEC)
	@echo 'Generating GCOV report...'
	@./$(GCOVEXEC) > /dev/zero 2> /dev/zero
	@lcov --no-external -t "Coverage report" -o $(DIR_BUILD)/$(DIR_REPORT).info -c -d .
	@genhtml -o $(DIR_REPORT) $(DIR_BUILD)/$(DIR_REPORT).info
	@echo 'Generating GCOV report - done'

open_report: gcov_report
	@echo "Opening GCOV report..."
	@open $(DIR_REPORT)/index.html

# Checking

leaks: build_tests
	@echo -n 'Starting leaks checking'
ifeq ($(OS), Darwin)
	@echo ' using "leaks"...'
	-@leaks --atExit -- ./$(GTESTEXEC)
	@echo 'Starting leaks checking using "leaks" utility - done'
else
	@echo ' using "valgrind"...'
	@valgrind --show-leak-kinds=all --leak-check=full ./$(GTESTEXEC)
	@echo 'Starting leaks checking using "valgrind" utility - done'
endif

clang-format-check:
	@echo -n "Copying format settings..."
	@cp ../materials/linters/.clang-format .
	@echo " done"
	@echo "Starting clang-format checking..."
	@clang-format -n --verbose -Werror -style=file $(CXX_FILES_ALL) $(H_FILES_ALL)
	@rm .clang-format
	@echo "Done clang-format checking"

# Cleaning

SUFFIX_CLEAN = .o .a .out .gch .gcda .gcno

clean:
	@echo -n 'Cleanup...'
	@rm -rf $(DIR_BUILD)
	@rm -rf $(addprefix *, $(SUFFIX_CLEAN))
	@rm -rf $(addprefix */*, $(SUFFIX_CLEAN))
	@rm -rf $(addprefix */*/*, $(SUFFIX_CLEAN))
	@rm -rf $(DIR_REPORT)
	@rm -rf ../build*
	@rm -rf $(APP_NAME) $(APP_NAME).tar
	@rm -rf *.dSYM
	@echo ' done'
