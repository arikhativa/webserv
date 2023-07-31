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

# general
NAME 						:= webserv
export ROOT_DIR				:= $(CURDIR)
export VALGRIND_OUTPUT		:= valgrind_out.txt
export TEST_EXEC			:= test.out
export TEST_RES				:= test_result.txt

# test general
TEST_SUFFIX					:= .test.cpp

# unit test
UNIT_TEST_DIR				:= src
UNIT_TEST					:= $(wildcard $(UNIT_TEST_DIR)/**/**/*$(TEST_SUFFIX))

# integration test
INT_TEST_DIR				:= tests
INT_TEST_FULL_PATH			:= $(wildcard $(INT_TEST_DIR)/**/*$(TEST_SUFFIX))

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
OBJ_NO_MAIN	 				:= $(filter-out obj/code/main/main.o,$(OBJ))

# test obj
TEST_OBJ_SUFFIX				:= .test.o
UNIT_TEST_OBJ				:= $(subst $(SRC_DIR),$(OBJ_DIR), $(UNIT_TEST:$(SRC_SUFFIX)=$(OBJ_SUFFIX)))
INT_TEST_OBJ				:= $(INT_TEST_FULL_PATH:$(TEST_SUFFIX)=$(TEST_OBJ_SUFFIX))
TEST_OBJ					:= $(UNIT_TEST_OBJ) $(INT_TEST_OBJ)

# dep
DEP_SUFFIX					:= .d
DEP							:= $(OBJ:$(OBJ_SUFFIX)=$(DEP_SUFFIX))

# script
SCRIPT_DIR					:= script
GEN_CLASS_SCRIPT			:= $(addprefix $(SCRIPT_DIR)/, create_cpp_class.sh)
GEN_INTERFACE_SCRIPT		:= $(addprefix $(SCRIPT_DIR)/, create_interface.sh)
TEST_SCRIPT					:= $(addprefix $(SCRIPT_DIR)/, test.sh)

# flags
INCLUDE						:= -I$(HEAD_DIR_TEMPLATE) -I$(HEAD_DIR_CLASS) -I$(HEAD_DIR_CODE)
CC 							:= c++
CPPFLAGS 					:= -c -MMD -MP -Wshadow -Wall -Wextra -Werror -std=c++98 -g $(INCLUDE)
TEST_COMPILE_FLAGS			:= -c -std=c++14 -DTEST_ON=1 $(INCLUDE)
TEST_LN_FLAGS				:= -std=c++14 -lgmock_main -lgmock -lgtest -lpthread $(INCLUDE)

# implicit rules

# object
$(addprefix $(OBJ_DIR)/, %$(OBJ_SUFFIX)): $(addprefix $(SRC_DIR)/, %$(SRC_SUFFIX))
	@$(CC) $(CPPFLAGS) $< -o $(@)

# unit test object
$(addprefix $(OBJ_DIR)/, %$(TEST_OBJ_SUFFIX)): $(addprefix $(SRC_DIR)/, %$(TEST_SUFFIX))
	@$(CC) $(TEST_COMPILE_FLAGS) $< -o $(@)

# integration test object
$(addprefix $(INT_TEST_DIR)/, %$(TEST_OBJ_SUFFIX)): $(addprefix $(INT_TEST_DIR)/, %$(TEST_SUFFIX))
	@$(CC) $(TEST_COMPILE_FLAGS)  $< -o $(@)

# rules
.PHONY: clean fclean re all class

all: $(NAME)

clean:
	@$(RM) $(OBJ) $(DEP) $(TEST_EXEC) $(TEST_OBJ) $(VALGRIND_OUTPUT) $(TEST_RES)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) -rf $(OBJ_DIR)

re: fclean all

class:
	@$(GEN_CLASS_SCRIPT)
	@$(RM) -rf $(OBJ_DIR)

interface:
	@$(GEN_INTERFACE_SCRIPT)
	@$(RM) -rf $(OBJ_DIR)

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(CC) $(OBJ) -o $@

$(OBJ_DIR):
	@cp -a $(SRC_DIR) $(OBJ_DIR)
	@find $(OBJ_DIR) -type f -delete

$(TEST_EXEC): $(OBJ_DIR) $(TEST_OBJ) $(OBJ_NO_MAIN)
	@$(CC) $(TEST_LN_FLAGS) $(TEST_OBJ) $(OBJ_NO_MAIN) -o $@

check: $(TEST_EXEC)
	@bash $(TEST_SCRIPT) gtest


T := ""
check/test: $(TEST_EXEC)
	./$(TEST_EXEC) --gtest_filter=$(T)*

check/leaks:
	@bash $(TEST_SCRIPT) memory

lint:
	@docker run -it --entrypoint /tmp/script/local_lint.sh \
	-e RUN_LOCAL=true \
	--env-file ".github/super-linter.env" \
	-v "$(ROOT_DIR)/$(SRC_DIR)":/tmp/lint \
	-v "$(ROOT_DIR)/.clang-format":/tmp/.clang-format \
	-v "$(ROOT_DIR)/script/local_lint.sh":/tmp/script/local_lint.sh \
	github/super-linter

-include $(DEP)
