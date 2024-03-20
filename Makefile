NAME	= ircserv

CC		= c++
CFLAGS	= -std=c++98 -Wall -Wextra -Werror -g -MMD -MP
RM		= rm -rf

GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
END			=	\e[0m

SRC_DIR = ./sources
OBJ_DIR = .obj
INCLUDES = -I ./includes

DEPS = $(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)/%.d)

SRC =	$(SRC_DIR)main.cpp

OBJ = $(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) -o $(NAME)
	@printf "$(GREEN)Compilation succeded ! ✔️$(END)\n"

-include $(DEPS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR) 
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@printf "$(YELLOW)Objects removed 🗑$(END)\n"
		@rm -rf $(OBJ_DIR)

fclean: clean
	@printf "$(YELLOW)Executable removed 🗑$(END)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY:		all clean fclean re
