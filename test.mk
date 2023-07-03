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

# implicit rules
$(addprefix $(OBJ_DIR)/, %$(TEST_OBJ_SUFFIX)): $(addprefix $(SRC_DIR)/, %$(TEST_SUFFIX))
	@echo "test obj"
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
