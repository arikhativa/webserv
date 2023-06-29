#!/bin/bash

REPO=webserv
RES=res
FILE_H=class.hpp
FILE_C=class.cpp
FILE_TEST=class.test.cpp
SRC_DIR=src/class

create_cpp_class()
{
	read -p "Enter Class Name => ExampleClass " input

	local name_uppercamlecase=$input
	local name_lowercase=$(echo $input | tr '[:upper:]' '[:lower:]')
	local name_upcase=$(echo $input | perl -ne 'print lc(join("_", split(/(?=[A-Z])/)))' | tr '[:lower:]' '[:upper:]')

	local full_path=$SRC_DIR/$name_uppercamlecase
	mkdir $full_path
	cat $HOME/$REPO/$RES/$FILE_H | sed -e "s/REPLACE/$name_upcase/g" | sed -e "s/Replace/$name_uppercamlecase/g" > $full_path/$name_uppercamlecase.hpp
	cat $HOME/$REPO/$RES/$FILE_C | sed -e "s/Replace/$name_uppercamlecase/g" > $full_path/$name_uppercamlecase.cpp
	cat $HOME/$REPO/$RES/$FILE_TEST | sed -e "s/Replace/$name_uppercamlecase/g" > $full_path/$name_uppercamlecase.test.cpp
}

create_cpp_class
