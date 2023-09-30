# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yrabby <yrabby@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/18 13:56:52 by yrabby            #+#    #+#              #
#    Updated: 2023/09/30 17:21:11 by yrabby           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# general
NAME 						:= webserv
export ROOT_DIR				:= $(CURDIR)

# src
SRC_SUFFIX					:= .cpp
SRC_DIR						:= src
ALL_SRC_FULL_PATH			:= $(wildcard $(SRC_DIR)/**/**/*$(SRC_SUFFIX))
SRC							:= $(filter-out $(UNIT_TEST),$(ALL_SRC_FULL_PATH))

# template
TEMPLATE_SUFFIX				:= .hpp
TEMPLATE_DIR				:= $(SRC_DIR)/template

# header
HEAD_SUFFIX					:= .hpp
HEAD_DIR_TEMPLATE			:= $(SRC_DIR)/template
HEAD_DIR_CLASS				:= $(SRC_DIR)/class
HEAD_DIR_CODE				:= $(SRC_DIR)/code

# obj
OBJ_SUFFIX					:= .o
OBJ_DIR						:= obj
OBJ							:= $(subst $(SRC_DIR),$(OBJ_DIR), $(SRC:$(SRC_SUFFIX)=$(OBJ_SUFFIX)))

# dep
DEP_SUFFIX					:= .d
DEP							:= $(OBJ:$(OBJ_SUFFIX)=$(DEP_SUFFIX))

# flags
INCLUDE						:= -I$(HEAD_DIR_TEMPLATE) -I$(HEAD_DIR_CLASS) -I$(HEAD_DIR_CODE)
CC 							:= c++
CPPFLAGS 					:= -c -MMD -MP -Wshadow -Wall -Wextra -Werror -std=c++98 $(INCLUDE)

# implicit rules

# object
$(addprefix $(OBJ_DIR)/, %$(OBJ_SUFFIX)): $(addprefix $(SRC_DIR)/, %$(SRC_SUFFIX))
	@$(CC) $(CPPFLAGS) $< -o $(@)

# rules
.PHONY: clean fclean re all class

all: $(NAME)

clean:
	@$(RM) $(OBJ) $(DEP) 

fclean: clean
	@$(RM) $(NAME)
	@$(RM) -rf $(OBJ_DIR)

re: fclean all

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(CC) $(OBJ) -o $@

$(OBJ_DIR):
	@cp -a $(SRC_DIR) $(OBJ_DIR)
	@find $(OBJ_DIR) -type f -delete

-include $(DEP)
