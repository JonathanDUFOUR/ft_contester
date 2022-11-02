# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/27 10:35:48 by jodufour          #+#    #+#              #
#    Updated: 2022/11/02 11:32:38 by jodufour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######################################
#              COMMANDS              #
######################################
CXX			=	clang++
LINK		=	clang++
MKDIR		=	mkdir -p
RM			=	rm -rf
VG			=	valgrind

######################################
#             EXECUTABLE             #
######################################
NAME		=	unit_test.out

#######################################
#             DIRECTORIES             #
#######################################
SRC_DIR		=	srcs
OBJ_DIR		=	objs
INC_DIR		=	../include
PRV_DIR		=	private

######################################
#            SOURCE FILES            #
######################################
SRC			=	\
				benchmark.cpp				\
				main.cpp					\
				test_algorithm.cpp			\
				test_is_integral.cpp		\
				test_map.cpp				\
				test_pair.cpp				\
				test_reverse_iterator.cpp	\
				test_stack.cpp				\
				test_vector.cpp				\
				title.cpp

#				\
				test_rb_tree.cpp			\
				test_set.cpp				\

######################################
#            OBJECT FILES            #
######################################
OBJ			=	${SRC:.cpp=.o}
OBJ			:=	${addprefix ${OBJ_DIR}/, ${OBJ}}

DEP			=	${OBJ:.o=.d}

#######################################
#                FLAGS                #
#######################################
CXXFLAGS	=	-c
CXXFLAGS	+=	-Wall -Wextra -Werror
CXXFLAGS	+=	-Wshadow
CXXFLAGS	+=	-Weffc++
CXXFLAGS	+=	-std=c++98
CXXFLAGS	+=	-pedantic
CXXFLAGS	+=	-ferror-limit=1
CXXFLAGS	+=	-MMD -MP
CXXFLAGS	+=	-I${INC_DIR}
CXXFLAGS	+=	-I${PRV_DIR}

LDFLAGS		=	

VGFLAGS		=	--leak-check=full
VGFLAGS		+=	--show-leak-kinds=all
VGFLAGS		+=	--track-fds=yes

ifeq (${DEBUG}, 1)
	CXXFLAGS	+=	-g
else \
ifeq (${DEBUG}, 2)
	CXXFLAGS	+=	-g
	CXXFLAGS	+=	-fsanitize=address
	CXXFLAGS	+=	-fsanitize=leak
	CXXFLAGS	+=	-fsanitize=undefined
	CXXFLAGS	+=	-fstandalone-debug

	LDFLAGS		+=	-fsanitize=address
	LDFLAGS		+=	-fsanitize=leak
	LDFLAGS		+=	-fsanitize=undefined
endif

#######################################
#                RULES                #
#######################################
.PHONY: all clean fclean re fre

${NAME}: ${OBJ}
	${LINK} $^ ${LDFLAGS} ${OUTPUT_OPTION}

all: ${NAME}

test: GREEN	=	\033[38;2;0;255;0m
test: RED	=	\033[38;2;255;0;0m
test: RESET	=	\033[0m
test: ${NAME}
ifeq (${DEBUG}, 1)
	@${VG} ${VGFLAGS} ./$< ; \
	if [ $$? -eq 0 ] ; then \
		printf "${GREEN}>>> SUCCESS <<<${RESET}\n" ; \
	else \
		printf "${RED}>>> FAILURE <<<${RESET}\n" ; \
	fi
else
	@./$< ; \
	if [ $$? -eq 0 ] ; then \
		printf "${GREEN}>>> SUCCESS <<<${RESET}\n" ; \
	else \
		printf "${RED}>>> FAILURE <<<${RESET}\n" ; \
	fi
endif

-include ${DEP}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.cpp
	@${MKDIR} ${@D}
	${CXX} $< ${CXXFLAGS} ${OUTPUT_OPTION}

clean:
	${RM} ${OBJ_DIR} ${NAME} vgcore.*

fclean:
	${RM} ${OBJ_DIR} ${NAME} vgcore.*

re: clean all

fre: fclean all

-include ${HOME}/Templates/mk_files/coffee.mk
