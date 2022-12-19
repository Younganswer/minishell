SHELL	= /bin/bash
SPINNER	= /-\|/
IDX		= 0

NAME	= minishell

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
LDFLAGS	= -L/opt/homebrew/opt/readline/lib -lreadline
AR		= ar rcs
RM		= rm -f

LIBS_DIR	= ./libs
LIBFT_DIR	:= ${LIBS_DIR}/libft
LIBFT		:= ${LIBFT_DIR}/libft.a
LIBS		:= ${LIBFT}

INCS_DIR	= ./incs
SRCS_DIR	= ./srcs
OBJS_DIR	= ./objs

SRCS = 	minishell.c\
		execute/execute.c \
		lexer/lexer.c \
		lexer/tokenizer.c \
		parser/parser.c \
		subsystem/subsystem.c
		
SRCS := ${addprefix ${SRCS_DIR}/, ${SRCS}}
OBJS := ${SRCS:${SRCS_DIR}/%.c=${OBJS_DIR}/%.o}


all: ${NAME}


${OBJS_DIR}:
	@echo "Build ${NAME}"
	@mkdir -p ${OBJS_DIR}
	@mkdir -p ${OBJS_DIR}/execute
	@mkdir -p ${OBJS_DIR}/lexer
	@mkdir -p ${OBJS_DIR}/parser
	@mkdir -p ${OBJS_DIR}/subsystem


${LIBFT}:
	@make -C ${LIBFT_DIR}


${NAME}: ${LIBFT} ${OBJS}
	@printf "\bdone\n"
	${eval IDX = 0}
	@${CC} ${LDFLAGS} -g -o ${NAME} ${OBJS} ${LIBS} -I ${INCS_DIR}
	@echo "Build ${NAME}: done"


${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c | ${OBJS_DIR}
	${eval IDX = ${shell expr ${IDX} + 1}}
	${eval T_IDX = ${shell expr ${IDX} % 32}}
	${eval T_IDX = ${shell expr ${T_IDX} / 8 + 1}}
	${eval CHR = ${shell echo ${SPINNER} | cut -c ${T_IDX}}}
	@if [ ${IDX} = 1 ]; then\
		echo -n "Build dependencies in ${NAME} ...  ";\
	fi
	@printf "\b${CHR}"
	@${CC} ${CFLAGS} -g -c $< -o $@ -I ${INCS_DIR}


clean:
	@echo "Remove dependencies in ${NAME}"
	@make -C ${LIBFT_DIR} clean
	@rm -rf ${OBJS_DIR}


fclean:
	@echo "Remove dependencies in ${NAME}"
	@make -C ${LIBFT_DIR} fclean
	@echo "Remove ${NAME}"
	@rm -rf ${OBJS_DIR}
	@${RM} ${NAME}
	

re:
	@echo "Re-build ${NAME}"
	@make fclean
	@make all


.PHONY: all clean fclean re bonus