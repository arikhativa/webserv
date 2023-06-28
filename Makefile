# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yrabby <yrabby@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/18 13:56:52 by yrabby            #+#    #+#              #
#    Updated: 2023/06/28 11:25:59 by yrabby           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 					= webserv

# unit test
TEST_SUFFIX				= .test.cpp
TEST_DIR				= src
TEST_FULL_PATH			= $(wildcard src/**/**/*$(TEST_SUFFIX))

# src
SRC_SUFFIX				= .cpp
SRC_DIR					= src
SRC_FULL_PATH			= $(filter-out $(TEST_FULL_PATH),$(wildcard $(SRC_DIR)/**/**/*$(SRC_SUFFIX)))
SRC_NAME				= $(notdir $(SRC_FULL_PATH)) # use $(basename) to remove suffix

# template
TEMPLATE_SUFFIX			= .hpp
TEMPLATE_DIR			= $(SRC_DIR)/template
TEMPLATE_FULL_PATH		= $(wildcard $(TEMPLATE_DIR)/**/*$(TEMPLATE_SUFFIX))
TEMPLATE				= $(SRC_FULL_PATH)

# other header
OTHER_HEAD				= 

# header
HEAD_SUFFIX				= .hpp
HEAD_DIR				= $(SRC_DIR)/class
HEAD_FULL_PATH			= $(SRC_FULL_PATH:$(SRC_SUFFIX)=$(HEAD_SUFFIX))
HEAD					= $(HEAD_FULL_PATH)

# obj
OBJ_SUFFIX				= .o
OBJ_DIR					= obj
OBJ						= $(subst $(SRC_DIR),$(OBJ_DIR), $(SRC_FULL_PATH:$(SRC_SUFFIX)=$(OBJ_SUFFIX)))
# OBJ						= $(SRC_FULL_PATH:$(SRC_SUFFIX)=$(OBJ_SUFFIX))

# dep
DEP_SUFFIX				= .d
DEP						:= $(OBJ:$(OBJ_SUFFIX)=$(DEP_SUFFIX))

# flags
CC 						= c++
CPPFLAGS 				= -MMD -MP -Wshadow -Wall -Wextra -Werror -std=c++98 -I$(HEAD_DIR)

# implicit rules
$(addprefix $(OBJ_DIR)/, %$(OBJ_SUFFIX)): $(addprefix $(SRC_DIR)/, %$(SRC_SUFFIX))
	$(CC) $(CPPFLAGS) $< -o $(@)

# rules
.PHONY: clean fclean re all

t:
	@echo $(OBJ)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(OBJ) -o $@

$(OBJ_DIR):
	@cp -a $(SRC_DIR) $(OBJ_DIR)
	@find $(OBJ_DIR) -type f -delete

clean:
	$(RM) $(OBJ) $(DEP)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(DEP)
