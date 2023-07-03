# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yrabby <yrabby@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/18 13:56:52 by yrabby            #+#    #+#              #
#    Updated: 2023/06/29 13:07:30 by yrabby           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# TEST

# general
export VALGRIND_OUTPUT		:= valgrind_out.txt
export TEST_EXEC			:= test.out
export TEST_RES				:= test_result.txt

# test
TEST_SUFFIX					:= .test.cpp
UNIT_TEST_DIR				:= src
TEST_FULL_PATH				:= $(wildcard $(UNIT_TEST_DIR)/**/**/*$(TEST_SUFFIX))
SET_TEST_FLAG				:= -DTEST_ON=1

# integration test
INT_TEST_DIR				:= tests
INT_TEST_FULL_PATH			:= $(wildcard $(INT_TEST_DIR)/**/*$(TEST_SUFFIX))

# 


NAME 					:= webserv
export ROOT_DIR			:= $(CURDIR)

# src
SRC_SUFFIX				:= .cpp
SRC_DIR					:= src
ALL_SRC_FULL_PATH		:= $(wildcard $(SRC_DIR)/**/**/*$(SRC_SUFFIX))
SRC_FULL_PATH			:= $(filter-out $(TEST_FULL_PATH),$(ALL_SRC_FULL_PATH))
SRC_NAME				:= $(notdir $(SRC_FULL_PATH)) # use $(basename) to remove suffix

# template
TEMPLATE_SUFFIX			:= .hpp
TEMPLATE_DIR			:= $(SRC_DIR)/template
TEMPLATE_FULL_PATH		:= $(wildcard $(TEMPLATE_DIR)/**/*$(TEMPLATE_SUFFIX))
TEMPLATE				:= $(SRC_FULL_PATH)

# other header
OTHER_HEAD				:= 

# header
HEAD_SUFFIX				:= .hpp
HEAD_DIR_TEMPLATE		:= $(SRC_DIR)/template
HEAD_DIR_CLASS			:= $(SRC_DIR)/class
HEAD_DIR_CODE			:= $(SRC_DIR)/code
HEAD_FULL_PATH			:= $(SRC_FULL_PATH:$(SRC_SUFFIX)=$(HEAD_SUFFIX))
HEAD					:= $(HEAD_FULL_PATH)

# obj
OBJ_SUFFIX				:= .o
OBJ_DIR					:= obj
# OBJ						:= obj/class/ExampleClass/ExampleClass.o obj/code/main/main.o
OBJ						:= $(subst $(SRC_DIR),$(OBJ_DIR), $(SRC_FULL_PATH:$(SRC_SUFFIX)=$(OBJ_SUFFIX)))
OBJ_NO_MAIN	 			:= $(filter-out obj/code/main/main.o,$(OBJ))

# dep
DEP_SUFFIX				:= .d
DEP						:= $(OBJ:$(OBJ_SUFFIX)=$(DEP_SUFFIX))



# test obj
TEST_OBJ_SUFFIX				:= .test.o
TEST_OBJ					:= $(subst $(SRC_DIR),$(OBJ_DIR), $(TEST_FULL_PATH:$(SRC_SUFFIX)=$(OBJ_SUFFIX)))
INT_TEST_OBJ				:= $(INT_TEST_FULL_PATH:$(TEST_SUFFIX)=$(TEST_OBJ_SUFFIX))



# script
SCRIPT_DIR				:= script
GEN_CLASS_SCRIPT		:= $(SCRIPT_DIR)/create_cpp_class.sh
TEST_SCRIPT				:= $(addprefix $(SCRIPT_DIR)/, test.sh)

# flags
INCLUDE					:= -I$(HEAD_DIR_TEMPLATE) -I$(HEAD_DIR_CLASS) -I$(HEAD_DIR_CODE)
CC 						:= c++
CPPFLAGS 				:= -c -MMD -MP -Wshadow -Wall -Wextra -Werror -std=c++98 $(INCLUDE)


# flags
TEST_COMPILE_FLAGS			:= -c -std=c++11 $(SET_TEST_FLAG) $(INCLUDE)
TEST_LN_FLAGS				:= $(SET_TEST_FLAG) -std=c++11 -lgmock_main -lgmock -lgtest -lpthread $(INCLUDE)



# implicit rules
$(addprefix $(OBJ_DIR)/, %$(OBJ_SUFFIX)): $(addprefix $(SRC_DIR)/, %$(SRC_SUFFIX))
	$(CC) $(CPPFLAGS) $< -o $(@)

# rules
.PHONY: clean fclean re all class $(TEST_EXEC)

all: $(NAME)

class:
	$(GEN_CLASS_SCRIPT)
	$(RM) -rf $(OBJ_DIR)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(OBJ) -o $@

$(OBJ_DIR):
	@cp -a $(SRC_DIR) $(OBJ_DIR)
	@find $(OBJ_DIR) -type f -delete

clean:
	$(RM) $(OBJ) $(DEP) $(TEST_EXEC) $(TEST_OBJ) $(VALGRIND_OUTPUT) $(TEST_RES) $(INT_TEST_OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) -rf $(OBJ_DIR)

re: fclean all

include test.mk
-include $(DEP)
