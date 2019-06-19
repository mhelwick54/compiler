TARGET=compile
CFLAGS=-Wall -std=c++17
OPT_LVL=
LDFLAGS=-I

################################################################################
# Select compiler based on platform                                            #
################################################################################
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	ifeq ($(shell which gcc-8), /usr/local/bin/gcc-8)
		CC=gcc-8#MacOS GNU gcc, not clang
		CXX=g++-8
	else
		CC=clang
		CXX=clang
	endif
else
	CC=gcc#GNU gcc
	CXX=g++
endif

################################################################################
# Directories                                                                  #
################################################################################
LEXDIR=./lexer
SYNDIR=./syntax
COMPDIR=./compile

IDIR=include
SDIR=src
BDIR=bin

INCLUDE=$(LDFLAGS)./$(IDIR) $(LDFLAGS)$(LEXDIR)/$(IDIR) $(LDFLAGS)$(SYNDIR)/$(IDIR) $(LDFLAGS)$(COMPDIR)/$(IDIR)

################################################################################
# Dependencies                                                                 #
################################################################################
_LEX_DEPS=lexer.h token.h tokens.h error.h defines.h
LEX_DEPS=$(patsubst %,$(LEXDIR)/$(IDIR)/%,$(_LEX_DEPS))
_SYN_DEPS=error.h defines.h
SYN_DEPS=$(patsubst %,$(SYNDIR)/$(IDIR)/%,$(_SYN_DEPS))
_COM_DEPS=error.h defines.h
COM_DEPS=$(patsubst %,$(COMDIR)/$(IDIR)/%,$(_COM_DEPS))
_MAIN_DEPS=error.h defines.h
MAIN_DEPS=$(patsubst %,$(IDIR)/%,$(_MAIN_DEPS))

################################################################################
# Source files                                                                 #
################################################################################
_LEX_SRC=lexer.cpp token.cpp tokens.cpp
LEX_SRC=$(patsubst %,$(LEXDIR)/$(SDIR)/%,$(_LEX_SRC))
_SYN_SRC=
SYN_SRC=$(patsubst %,$(SYNDIR)/$(SDIR)/%,$(_SYN_SRC))
_COMP_SRC=
COMP_SRC=$(patsubst %,$(COMPDIR)/$(SDIR)/%,$(_COMP_SRC))
_MAIN_SRC=main.cpp error.cpp
MAIN_SRC=$(patsubst %,$(SDIR)/%,$(_MAIN_SRC))

################################################################################
# Object files                                                                 #
################################################################################
_LEX_OBJ=lexer.o token.o tokens.o
LEX_OBJ=$(patsubst %,$(LEXDIR)/$(BDIR)/%,$(_LEX_OBJ))
_SYN_OBJ=
SYN_OBJ=$(patsubst %,$(SYNDIR)/$(BDIR)/%,$(_SYN_OBJ))
_COMP_OBJ=
COMP_OBJ=$(patsubst %,$(COMPDIR)/$(BDIR)/%,$(_COMP_OBJ))
_MAIN_OBJ=main.o error.o
MAIN_OBJ=$(patsubst %,$(BDIR)/%,$(_MAIN_OBJ))

################################################################################
# Color mods                                                                   #
################################################################################
COM_COLOR=\033[0;34m
OBJ_COLOR=\033[0;36m
NO_COLOR=\033[m
OK_COLOR=\033[0;32m
ERROR_COLOR=\033[0;31m
WARN_COLOR=\033[0;33m

################################################################################
# Compilation messages                                                         #
################################################################################
COM_STRING="Compiling"
OK_STRING="[OK]"
ERROR_STRING="[ERROR]"
WARN_STRING="[WARNING]"

################################################################################
# Compilation beautifier function                                              #
################################################################################
define make_pretty
printf "%b" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@F)$(NO_COLOR)\r"; \
$(1) 2> $@.log; \
RESULT=$$?; \
if [ $$RESULT -ne 0 ]; then \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"   ; \
elif [ -s $@.log ]; then \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"   ; \
else  \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"   ; \
fi; \
cat $@.log; \
rm -f $@.log; \
exit $$RESULT
endef

################################################################################
# Build rules                                                                  #
################################################################################
all: $(BDIR)/$(TARGET)
	@printf "%b" "Compilation successful\n"

$(BDIR)/$(TARGET): $(MAIN_OBJ) $(COMP_OBJ) $(LEX_OBJ) $(SYN_OBJ)
	$(CXX) $(CFLAGS) $(INCLUDE) $^ -o $@
	@$(call make_pretty)

$(COMPDIR)/$(BDIR)/%.o: $(COMPDIR)/$(SDIR)/%.cpp
	$(CXX) $(CFLAGS) -MMD -c $< -o $@
	@$(call make_pretty)

$(LEXDIR)/$(BDIR)/%.o: $(LEXDIR)/$(SDIR)/%.cpp
	$(CXX) $(CFLAGS) -MMD -c $^ -o $@
	@$(call make_pretty)

$(SYNDIR)/$(BDIR)/%.o: $(SYNDIR)/$(SDIR)/%.cpp
	$(CXX) $(CFLAGS) -MMD -c $< -o $@
	@$(call make_pretty)

$(BDIR)/%.o: $(SDIR)/%.cpp
	$(CXX) $(CFLAGS) -MMD -c ./$< -o ./$@
	@$(call make_pretty)

.PHONY: clean

clean:
	rm -rf $(LEXDIR)/$(BDIR)/*
	rm -rf $(SYNDIR)/$(BDIR)/*
	rm -rf $(COMPDIR)/$(BDIR)/*
	rm -rf ./$(BDIR)/*
