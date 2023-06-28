/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExampleClass.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrabby <yrabby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:22:25 by yrabby            #+#    #+#             */
/*   Updated: 2023/06/28 11:06:50 by yrabby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ExampleClass.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ExampleClass::ExampleClass(int i)
	: _value(i)
{
}

ExampleClass::ExampleClass( const ExampleClass & src )
	: _value(src.getValue())
{
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ExampleClass::~ExampleClass()
{
	_value = 0;
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ExampleClass &				ExampleClass::operator=( ExampleClass const & rhs )
{
	if ( this != &rhs )
	{
		this->_value = rhs.getValue();
	}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, ExampleClass const & i )
{
	o << "ExampleClass[" << i.getValue() << "]";
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/


/*
** --------------------------------- ACCESSOR ---------------------------------
*/

int		ExampleClass::getValue(void) const
{
	return this->_value;
}


/* ************************************************************************** */