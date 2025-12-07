##########
# COLORS #
##########
RESET := \033[0m
  RED := \033[31m
GREEN := \033[32m

#############
# FUNCTIONS #
#############
define success
printf "$(GREEN)>>> SUCCESS <<<$(RESET)\n"
endef
define failure
printf "$(RED)>>> FAILURE <<<$(RESET)\n"
endef

############
# COMMANDS #
############
  CXX := $(shell which clang++) -c
 LINK := $(shell which clang++)
 FIND := $(shell which find)
 SORT := $(shell which sort)
MKDIR := $(shell which mkdir) -p
   RM := $(shell which rm) -rf
   VG := $(shell which valgrind)

###############
# DIRECTORIES #
###############
INC_DIR := ../abstract_data/include
PRV_DIR := private
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

#########
# FILES #
#########
HDR := $(shell $(FIND) $(PRV_DIR) -type f -name '*.hh' | $(SORT))
SRC := $(shell $(FIND) $(SRC_DIR) -type f -name '*.cc' | $(SORT))
OBJ := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC:.cc=.o))
DEP := $(OBJ:.o=.d)
BIN := $(BIN_DIR)/unit_tests

#########
# FLAGS #
#########
CPPFLAGS := \
	-I$(INC_DIR) \
	-I$(PRV_DIR) \
	-MMD -MP \

CXXFLAGS := \
	-O0 \
	-Wall \
	-Wextra \
	-Wshadow \
	-Weffc++ \
	-Wno-c99-designator \
	-std=c++98 \
	-ferror-limit=1 \


VGFLAGS := \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-fds=yes \

ifeq ($(DEBUG), 1)
CXXFLAGS += -g
endif

ifeq ($(DEBUG), 2)
CXXFLAGS += \
	-g \
	-fsanitize=address \
	-fsanitize=leak \
	-fsanitize=undefined \
	-fstandalone-debug \

LDFLAGS += \
	-fsanitize=address \
	-fsanitize=leak \
	-fsanitize=undefined \

endif

#########
# RULES #
#########
$(BIN): $(OBJ)
	$(MKDIR) $(@D)
	$(LINK) $(LDFLAGS) $^ $(OUTPUT_OPTION)

.PHONY: all
all: $(BIN)

.PHONY: test
test: $(BIN)
ifeq ($(DEBUG), 1)
	@$(VG) $(VGFLAGS) ./$< && $(success) || $(failure)
else
	@                 ./$< && $(success) || $(failure)
endif

-include $(DEP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	@$(MKDIR) $(@D)
	$(strip $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(OUTPUT_OPTION) $<)

.PHONY: fmt
fmt:
	$(FMT) -i --style=file $(HDR) $(SRC)

.PHONY: clean
clean:
	$(RM) $(OBJ_DIR) $(NAME) vgcore.*

.PHONY: fclean
fclean:
	$(RM) $(OBJ_DIR) $(NAME) vgcore.*

.PHONY: re
re: clean all

.PHONY: fre
fre: fclean all

-include $(HOME)/Templates/mk_files/coffee.mk
