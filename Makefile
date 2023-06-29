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

NAME 					= webserv
export ROOT_DIR			= $(CURDIR)

# unit test
export TEST_EXEC		= test
TEST_SUFFIX				= .test.cpp
TEST_DIR				= src
TEST_FULL_PATH			= $(wildcard src/**/**/*$(TEST_SUFFIX))
SET_TEST_FLAG			= -DTEST_ON=1
export VALGRIND_OUTPUT 	= valgrind_out.txt
export TEST_RES			= unit_test_result.txt

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

# script
SCRIPT_DIR				= script
GEN_CLASS_SCRIPT		= $(SCRIPT_DIR)/create_cpp_class.sh
TEST_SCRIPT				= $(addprefix $(SCRIPT_DIR)/, test.sh)

# flags
INCLUDE					= -I$(HEAD_DIR_TEMPLATE) -I$(HEAD_DIR_CLASS) -I$(HEAD_DIR_CODE)
CC 						= c++
CPPFLAGS 				= -c -MMD -MP -Wshadow -Wall -Wextra -Werror -std=c++98 $(INCLUDE)
TEST_COMPILE_FLAGS 		= -c $(SET_TEST_FLAG) $(INCLUDE)
TEST_LN_FLAGS 			= $(SET_TEST_FLAG) -Lres -lgtest -lgtest_main -lpthread $(INCLUDE)
TEST_LIB			 	= ./res/libgtest_main.so ./res/libgtest.so

# implicit rules
$(addprefix $(OBJ_DIR)/, %$(OBJ_SUFFIX)): $(addprefix $(SRC_DIR)/, %$(SRC_SUFFIX))
	$(CC) $(CPPFLAGS) $< -o $(@)

$(addprefix $(OBJ_DIR)/, %$(TEST_OBJ_SUFFIX)): $(addprefix $(SRC_DIR)/, %$(TEST_SUFFIX))
	$(CC) $(TEST_COMPILE_FLAGS) $< -o $(@)

# rules
.PHONY: clean fclean re all test class

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
	$(RM) $(OBJ) $(DEP) $(TEST_EXEC) $(TEST_OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) -rf $(OBJ_DIR)

re: fclean all

# TODO not sure about this
install/gtest:
	script/install_gtest.sh

$(TEST_EXEC): $(OBJ_DIR) $(TEST_OBJ) $(OBJ_NO_MAIN)
	$(CC) $(TEST_LN_FLAGS) $(TEST_OBJ) $(OBJ_NO_MAIN) $(TEST_LIB) -o $@

check: $(TEST_EXEC)
	@bash $(TEST_SCRIPT) unit_test

check/leaks: $(TEST_EXEC)
	@bash $(TEST_SCRIPT) memory

lint:
	docker run -it --entrypoint /tmp/script/local_lint.sh \
    -e RUN_LOCAL=true \
    --env-file ".github/super-linter.env" \
    -v "$(ROOT_DIR)/$(SRC_DIR)":/tmp/lint \
    -v "$(ROOT_DIR)/.clang-format":/tmp/.clang-format \
    -v "$(ROOT_DIR)/script/local_lint.sh":/tmp/script/local_lint.sh \
	github/super-linter

-include $(DEP)
