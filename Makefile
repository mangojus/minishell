NAME = minishell

# === CONFIG ===

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

IFLAGS = -I $(INC) -I $(LIBFT)/$(INC) -MMD -MP

RM = rm -rf

# === PATHING ===

SRC_DIR = src

BLD_DIR = .build

SRC = $(SRC_DIR)/main.c \
	  $(SRC_DIR)/parsing/parser.c \
	  $(SRC_DIR)/parsing/lexer.c \
	  $(SRC_DIR)/parsing/checker.c \
	  $(SRC_DIR)/parsing/expander.c \
	  $(SRC_DIR)/parsing/assembler.c \
	  $(SRC_DIR)/exec/executor.c \
	  $(SRC_DIR)/exec/proc.c \
	  $(SRC_DIR)/exec/pipe_utils.c \
	  $(SRC_DIR)/exec/handle_exec.c \
	  $(SRC_DIR)/exec/handle_builtin.c \
	  $(SRC_DIR)/exec/handle_heredoc.c \
	  $(SRC_DIR)/exec/handle_fds.c \
	  $(SRC_DIR)/exec/proc_utils.c \
	  $(SRC_DIR)/exec/exec_utils.c \
	  $(SRC_DIR)/builtins/env.c \
	  $(SRC_DIR)/builtins/pwd.c \
	  $(SRC_DIR)/builtins/cd.c \
	  $(SRC_DIR)/builtins/echo.c \
	  $(SRC_DIR)/builtins/exit.c \
	  $(SRC_DIR)/builtins/export.c \
	  $(SRC_DIR)/builtins/unset.c \
	  $(SRC_DIR)/utils/data.c \
	  $(SRC_DIR)/utils/error.c \
	  $(SRC_DIR)/utils/signals.c

SRC += $(SRC_DIR)/token/tok_dlstadd_back.c \
	   $(SRC_DIR)/token/tok_dlstfree.c \
	   $(SRC_DIR)/token/tok_dlstsize.c \
	   $(SRC_DIR)/token/tok_dlstsplit.c \
	   $(SRC_DIR)/token/tok_dlstlink.c \
	   $(SRC_DIR)/token/tok_dlsthead.c \
	   $(SRC_DIR)/token/tok_dlstlast.c \
	   $(SRC_DIR)/token/tok_dlstiter.c \
	   $(SRC_DIR)/token/tok_dlstreplace.c \
	   $(SRC_DIR)/token/tok_dlstconvert.c \
	   $(SRC_DIR)/token/tok_dlstremove.c

SRC += $(SRC_DIR)/command/cmd_dlstsize.c \
	   $(SRC_DIR)/command/cmd_dlsthead.c \
	   $(SRC_DIR)/command/cmd_dlstlast.c \
	   $(SRC_DIR)/command/cmd_dlstfree.c \
	   $(SRC_DIR)/command/cmd_dlstlink.c

SRC += $(SRC_DIR)/env/env_dlstadd_back.c \
	   $(SRC_DIR)/env/env_dlstadd_front.c \
	   $(SRC_DIR)/env/env_dlstconvert.c \
	   $(SRC_DIR)/env/env_dlstfind.c \
	   $(SRC_DIR)/env/env_dlstfree.c \
	   $(SRC_DIR)/env/env_dlstlast.c \
	   $(SRC_DIR)/env/env_dlsthead.c \
	   $(SRC_DIR)/env/env_dlstlink.c \
	   $(SRC_DIR)/env/env_dlstnew.c \
	   $(SRC_DIR)/env/env_dlstremove.c \
	   $(SRC_DIR)/env/env_dlstsize.c \
	   $(SRC_DIR)/env/env_utils.c

INC = include

LIBFT = libft

LIB_A = $(LIBFT)/libft.a

OBJ = $(patsubst $(SRC_DIR)/%.c, $(BLD_DIR)/%.o, $(SRC))

DEP = $(patsubst $(SRC_DIR)/%.c, $(BLD_DIR)/%.d, $(SRC))

# === TARGET RULES ===

all: $(NAME)

$(NAME): $(OBJ) $(LIB_A)
	$(CC) $(CFLAGS) $(IFLAGS) $(OBJ) $(LIB_A) -lreadline -o $(NAME)

$(BLD_DIR)/%.o: $(SRC_DIR)/%.c Makefile
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIB_A): FORCE
	make -C $(LIBFT)

clean:
	make -C $(LIBFT) clean
	$(RM) $(OBJ)

re: fclean all

fclean: clean
	$(RM) $(LIBFT)/$(BLD_DIR) $(LIB_A)
	$(RM) $(BLD_DIR) $(NAME)

FORCE:

-include $(DEP)

.PHONY: all clean fclean re FORCE
