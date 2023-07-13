/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExampleTemplate.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrabby <yrabby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:49:23 by yrabby            #+#    #+#             */
/*   Updated: 2023/06/28 11:51:49 by yrabby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXAMPLETEMPLATE_HPP
#define EXAMPLETEMPLATE_HPP

#include <iostream>

template <typename T>
class ExampleTemplate
{
  public:
	/*
	** ------------------------------- CONSTRUCTOR -----------------------------
	*/

	ExampleTemplate(T value)
		: _value(value){

		  };
	ExampleTemplate(ExampleTemplate const &src)
		: _value(src.getValue()){

		  };

	/*
	** -------------------------------- DESTRUCTOR -----------------------------
	*/

	~ExampleTemplate(){

	};

	/*
	** --------------------------------- OVERLOAD ------------------------------
	*/

	ExampleTemplate &operator=(ExampleTemplate const &rhs)
	{
		if (this != &rhs)
		{
			this->_value = rhs.getValue();
		}
		return *this;
	}

	/*
	** --------------------------------- METHODS -------------------------------
	*/

	T getValue(void) const
	{
		return this->_value;
	}

  private:
	T _value;
};

template <typename T>
std::ostream &operator<<(std::ostream &o, ExampleTemplate<T> const &i)
{
	o << "ExampleTemplate[" << i.getValue() << "]";
	return o;
}

#endif /* *********************************************** EXAMPLETEMPLATE_HPP */
