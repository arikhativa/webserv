# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yrabby <yrabby@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/18 13:56:52 by yrabby            #+#    #+#              #
#    Updated: 2023/09/30 17:29:54 by yrabby           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# general
NAME 						:= webserv
export ROOT_DIR				:= $(CURDIR)

# src
SRC_SUFFIX					:= .cpp
SRC_DIR						:= src
ALL_SRC_FULL_PATH			:= src/class/ABaseHTTPCall/ABaseHTTPCall.cpp \
	src/class/AllowedMethods/AllowedMethods.cpp \
	src/class/BasePairCodePath/BasePairCodePath.cpp \
	src/class/BasicHTTPRequest/BasicHTTPRequest.cpp \
	src/class/CGIConf/CGIConf.cpp \
	src/class/CgiManager/CgiManager.cpp \
	src/class/Conf/Conf.cpp \
	src/class/ContentTypes/ContentTypes.cpp \
	src/class/ErrorPage/ErrorPage.cpp \
	src/class/ErrorPageSet/ErrorPageSet.cpp \
	src/class/FileManager/FileManager.cpp \
	src/class/HTTPCall/HTTPCall.cpp \
	src/class/HTTPResponse/HTTPResponse.cpp \
	src/class/HTTPStatusCode/HTTPStatusCode.cpp \
	src/class/IP/IP.cpp \
	src/class/Listen/Listen.cpp \
	src/class/Location/Location.cpp \
	src/class/Path/Path.cpp \
	src/class/Pipe/Pipe.cpp \
	src/class/Poll/Poll.cpp \
	src/class/Port/Port.cpp \
	src/class/ResponseHeader/ResponseHeader.cpp \
	src/class/Return/Return.cpp \
	src/class/ServerConf/ServerConf.cpp \
	src/class/ServerManager/ServerManager.cpp \
	src/class/Socket/Socket.cpp \
	src/class/Tab/Tab.cpp \
	src/class/Time/Time.cpp \
	src/class/Token/Token.cpp \
	src/code/HTTPRequestHandler/HTTPRequestHandler.cpp \
	src/code/builder/builder.cpp \
	src/code/builder/builder_location.cpp \
	src/code/builder/builder_server.cpp \
	src/code/builder/builder_validate.cpp \
	src/code/converter/converter.cpp \
	src/code/defaultPager/defaultPager.cpp \
	src/code/header/header.cpp \
	src/code/httpRequestHandlerDELETE/httpRequestHandlerDELETE.cpp \
	src/code/httpRequestHandlerGET/httpRequestHandlerGET.cpp \
	src/code/httpRequestHandlerPOST/httpRequestHandlerPOST.cpp \
	src/code/lexer/lexer.cpp \
	src/code/listPrint/listPrint.cpp \
	src/code/main/main.cpp \
	src/code/mapPrint/mapPrint.cpp \
	src/code/matcher/matcher.cpp \
	src/code/parser/parser.cpp \
	src/code/parser/parser_rules.cpp \
	src/code/pollHandler/pollHandler.cpp \
	src/code/signalHandler/signalHandler.cpp \
	src/code/vectorUtils/vectorUtils.cpp

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
