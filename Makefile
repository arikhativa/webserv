# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yrabby <yrabby@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/18 13:56:52 by yrabby            #+#    #+#              #
#    Updated: 2023/06/28 14:22:12 by yrabby           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 					= webserv

# unit test
TEST					= test
TEST_SUFFIX				= .test.cpp
TEST_DIR				= src
TEST_FULL_PATH			= $(wildcard src/**/**/*$(TEST_SUFFIX))
SET_TEST_FLAG			= -DTEST_ON=1

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
HEAD_DIR_TEMPLATE		= $(SRC_DIR)/template
HEAD_DIR_CLASS			= $(SRC_DIR)/class
HEAD_DIR_CODE			= $(SRC_DIR)/code
HEAD_FULL_PATH			= $(SRC_FULL_PATH:$(SRC_SUFFIX)=$(HEAD_SUFFIX))
HEAD					= $(HEAD_FULL_PATH)

# obj
TEST_OBJ_SUFFIX			= .test.o
TEST_OBJ				= $(subst $(SRC_DIR),$(OBJ_DIR), $(TEST_FULL_PATH:$(SRC_SUFFIX)=$(OBJ_SUFFIX)))

OBJ_SUFFIX				= .o
OBJ_DIR					= obj
OBJ						= $(subst $(SRC_DIR),$(OBJ_DIR), $(SRC_FULL_PATH:$(SRC_SUFFIX)=$(OBJ_SUFFIX)))
OBJ_NO_MAIN	 			= $(filter-out obj/code/main/main.o,$(OBJ))

# dep
DEP_SUFFIX				= .d
DEP						:= $(OBJ:$(OBJ_SUFFIX)=$(DEP_SUFFIX))

# flags
INCLUDE					= -I$(HEAD_DIR_TEMPLATE) -I$(HEAD_DIR_CLASS) -I$(HEAD_DIR_CODE)
CC 						= c++
TEST_CC 						= clang
CPPFLAGS 				= -c -MMD -MP -Wshadow -Wall -Wextra -Werror -std=c++98 $(INCLUDE)
TEST_COMPILE_FLAGS 		= -c $(SET_TEST_FLAG) $(INCLUDE)
TEST_LN_FLAGS 			= $(SET_TEST_FLAG) -lgtest -lgtest_main -lpthread $(INCLUDE)
TEST_LIB			 	= ./res/gtest/googlemock/gtest/libgtest_main.so ./res/gtest/googlemock/gtest/libgtest.so

# implicit rules
$(addprefix $(OBJ_DIR)/, %$(OBJ_SUFFIX)): $(addprefix $(SRC_DIR)/, %$(SRC_SUFFIX))
	$(CC) $(CPPFLAGS) $< -o $(@)

$(addprefix $(OBJ_DIR)/, %$(TEST_OBJ_SUFFIX)): $(addprefix $(SRC_DIR)/, %$(TEST_SUFFIX))
	$(TEST_CC) $(TEST_COMPILE_FLAGS)  $< -o $(@)

# rules
.PHONY: clean fclean re all test

all: $(NAME)

$(TEST): $(OBJ_DIR) $(TEST_OBJ) $(OBJ_NO_MAIN)
	$(TEST_CC) $(TEST_LN_FLAGS) $(TEST_OBJ) $(OBJ_NO_MAIN) $(TEST_LIB) -o $@
	./$@

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(OBJ) -o $@

$(OBJ_DIR):
	@cp -a $(SRC_DIR) $(OBJ_DIR)
	@find $(OBJ_DIR) -type f -delete

clean:
	$(RM) $(OBJ) $(DEP) $(TEST) $(TEST_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all



-include $(DEP)


