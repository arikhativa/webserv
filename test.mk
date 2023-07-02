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
export VALGRIND_OUTPUT 	= valgrind_out.txt

# unit test
TEST_SUFFIX				= .test.cpp
export TEST_EXEC		= unit_test.out
TEST_DIR				= src
TEST_FULL_PATH			= $(wildcard src/**/**/*$(TEST_SUFFIX))
SET_TEST_FLAG			= -DTEST_ON=1
export TEST_RES			= unit_test_result.txt

# unit test obj
TEST_OBJ_SUFFIX			= .test.o
TEST_OBJ				= $(subst $(SRC_DIR),$(OBJ_DIR), $(TEST_FULL_PATH:$(SRC_SUFFIX)=$(OBJ_SUFFIX)))

# integration test
INT_TEST_SUFFIX				= .int_test.cpp
INT_TEST_DIR				= tests
export INT_TEST_EXEC		= integration_test
INT_TEST_FULL_PATH			= $(wildcard $(INT_TEST_DIR)/**/*$(INT_TEST_SUFFIX))
INT_TEST_EXEC				= $(INT_TEST_FULL_PATH:$(INT_TEST_SUFFIX)=.out)
export INT_TEST_RES			= integration_test_result.txt

# flags
TEST_COMPILE_FLAGS		= -c $(SET_TEST_FLAG) $(INCLUDE)
TEST_LN_FLAGS			= $(SET_TEST_FLAG) -lgtest_main -lgtest -lpthread $(INCLUDE)
INT_TEST_FLAGS			= -lgmock_main -lgmock -lgtest -lpthread $(INCLUDE)

# implicit rules
$(addprefix $(OBJ_DIR)/, %$(TEST_OBJ_SUFFIX)): $(addprefix $(SRC_DIR)/, %$(TEST_SUFFIX))
	$(CC) $(TEST_COMPILE_FLAGS) $< -o $(@)

$(addprefix $(INT_TEST_DIR)/, %.out): $(addprefix $(INT_TEST_DIR)/, %$(INT_TEST_SUFFIX))
	$(CC) $(INT_TEST_FLAGS) $< -o $(@)
	touch $(INT_TEST_RES)
	./$(@) >> $(INT_TEST_RES)
	echo "\n--------------\n" >> $(INT_TEST_RES)

# rules
$(TEST_EXEC): $(OBJ_DIR) $(TEST_OBJ) $(OBJ_NO_MAIN)
	$(CC) $(TEST_LN_FLAGS) $(TEST_OBJ) $(OBJ_NO_MAIN)  -o $@

check: $(TEST_EXEC)
	@bash $(TEST_SCRIPT) unit_test

check/leaks: $(TEST_EXEC)
	@bash $(TEST_SCRIPT) memory

check/integration: $(INT_TEST_EXEC)
	cat $(INT_TEST_RES)

lint:
	docker run -it --entrypoint /tmp/script/local_lint.sh \
    -e RUN_LOCAL=true \
    --env-file ".github/super-linter.env" \
    -v "$(ROOT_DIR)/$(SRC_DIR)":/tmp/lint \
    -v "$(ROOT_DIR)/.clang-format":/tmp/.clang-format \
    -v "$(ROOT_DIR)/script/local_lint.sh":/tmp/script/local_lint.sh \
	github/super-linter

-include $(DEP)
