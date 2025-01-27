NAME		= ReadySetBoole
	
CC			= c++
FLAGS		= -Wall -Wextra -Werror
RM			= rm -rf

OBJDIR 		= obj
SRCDIR		= src

FILES		= main BitsetU32

SRC			= $(addprefix $(SRCDIR)/,$(FILES:=.cpp))
OBJ			= $(addprefix $(OBJDIR)/, $(FILES:=.o))
HEADER		= BitsetU32.hpp

#Colors:
GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
GRAY		=	\e[33;2;37m
RESET		=	\e[0m
CURSIVE		=	\e[33;3m


all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(OBJ) -o $(NAME)
	@printf "$(_SUCCESS) $(GREEN)- Executable ready.\n$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADER)
	@mkdir -p $(OBJDIR)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJDIR) $(OBJ)
	@printf "$(YELLOW)    - Object files removed.$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(YELLOW)    - Executable removed.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re