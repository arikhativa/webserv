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
export VALGRIND_OUTPUT		= valgrind_out.txt
export TEST_EXEC			= test.out
export TEST_RES				= test_result.txt

# test
TEST_SUFFIX					= .test.cpp
UNIT_TEST_DIR				= src
TEST_FULL_PATH				= $(wildcard $(UNIT_TEST_DIR)/**/**/*$(TEST_SUFFIX))
SET_TEST_FLAG				= -DTEST_ON=1

# test obj
TEST_OBJ_SUFFIX				= .test.o
TEST_OBJ					= $(subst $(SRC_DIR),$(OBJ_DIR), $(TEST_FULL_PATH:$(SRC_SUFFIX)=$(OBJ_SUFFIX)))

# integration test
INT_TEST_DIR				= tests
INT_TEST_FULL_PATH			= $(wildcard $(INT_TEST_DIR)/**/*$(TEST_SUFFIX))
INT_TEST_OBJ				= $(INT_TEST_FULL_PATH:$(TEST_SUFFIX)=$(TEST_OBJ_SUFFIX))

# flags
TEST_COMPILE_FLAGS			= -c $(SET_TEST_FLAG) $(INCLUDE)
TEST_LN_FLAGS				= $(SET_TEST_FLAG) -lgmock_main -lgmock -lgtest -lpthread $(INCLUDE)

# implicit rules
$(addprefix $(OBJ_DIR)/, %$(TEST_OBJ_SUFFIX)): $(addprefix $(SRC_DIR)/, %$(TEST_SUFFIX))
	$(CC) $(TEST_COMPILE_FLAGS) $< -o $(@)

$(addprefix $(INT_TEST_DIR)/, %$(TEST_OBJ_SUFFIX)): $(addprefix $(INT_TEST_DIR)/, %$(TEST_SUFFIX))
	$(CC) -c  $< -o $(@)

# rules 
$(TEST_EXEC): $(OBJ_DIR) $(TEST_OBJ) $(INT_TEST_OBJ) $(OBJ_NO_MAIN)
	$(CC) $(TEST_LN_FLAGS) $(TEST_OBJ) $(INT_TEST_OBJ) $(OBJ_NO_MAIN) -o $@

check: $(TEST_EXEC)
	@bash $(TEST_SCRIPT) gtest

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
