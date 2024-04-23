NAME	= ircserv

CC		= c++
CFLAGS	= -std=c++98 -Wall -Wextra -Werror -g -MMD -MP
RM		= rm -rf

GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
END			=	\e[0m

SRC_DIR = sources/
CMD_DIR = sources/commands/
OBJ_DIR = .obj
INCLUDES = -I ./includes

DEPS = $(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)/%.d)

SRC =	$(SRC_DIR)main.cpp				\
		$(SRC_DIR)Server.cpp			\
		$(SRC_DIR)Client.cpp			\
		$(SRC_DIR)NumericReplies.cpp	\
		$(CMD_DIR)Command.cpp			\
		$(CMD_DIR)invite.cpp			\
		$(CMD_DIR)join.cpp				\
		$(CMD_DIR)kick.cpp				\
		$(CMD_DIR)mode.cpp				\
		$(CMD_DIR)nick.cpp				\
		$(CMD_DIR)part.cpp				\
		$(CMD_DIR)pass.cpp				\
		$(CMD_DIR)privmsg.cpp			\
		$(CMD_DIR)quit.cpp				\
		$(CMD_DIR)topic.cpp				\
		$(CMD_DIR)user.cpp				\
		$(CMD_DIR)who.cpp				\
		$(CMD_DIR)cap.cpp

OBJ = $(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) -o $(NAME)
	@printf "$(GREEN)Compilation succeded ! ✔️$(END)\n"

-include $(DEPS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@mkdir -p .obj/commands
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@printf "$(YELLOW)Objects removed 🗑$(END)\n"
		@rm -rf $(OBJ_DIR)

fclean: clean
	@printf "$(YELLOW)Executable removed 🗑$(END)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY:		all clean fclean re
