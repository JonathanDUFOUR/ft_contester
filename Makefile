######################################
#              COMMANDS              #
######################################
CXX			=	clang++
LINK		=	clang++
MKDIR		=	mkdir -p
RM			=	rm -rf

######################################
#             EXECUTABLE             #
######################################
NAME		=	ft_contester.out

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
				main.cpp

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
CXXFLAGS	+=	-MMD -MP

LDFLAGS		=	

ifeq (${DEBUG}, 1)
	CXXFLAGS	+=	-g
	CXXFLAGS	+=	-DDEBUG=1
endif

#######################################
#                RULES                #
#######################################
.PHONY: all clean fclean re fre

${NAME}: ${OBJ}
	${LINK} $^ ${LDFLAGS} ${OUTPUT_OPTION}

all: ${NAME}

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
