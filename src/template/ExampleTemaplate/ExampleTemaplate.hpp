/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExampleTemaplate.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrabby <yrabby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:49:23 by yrabby            #+#    #+#             */
/*   Updated: 2023/06/28 10:49:48 by yrabby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXAMPLETEMAPLATE_HPP
# define EXAMPLETEMAPLATE_HPP

# include <iostream>
# include <string>

template < typename T >
class ExampleTemaplate
{

	public:


	/*
	** ------------------------------- CONSTRUCTOR --------------------------------
	*/

		ExampleTemaplate() {};
		ExampleTemaplate( ExampleTemaplate const & src ) {};


	/*
	** -------------------------------- DESTRUCTOR --------------------------------
	*/

		~ExampleTemaplate() {};


	/*
	** --------------------------------- OVERLOAD ---------------------------------
	*/

		ExampleTemaplate &		operator=( ExampleTemaplate const & rhs )
		{
			//if ( this != &rhs )
			//{
				//this->_value = rhs.getValue();
			//}
			return *this;
		}

	/*
	** --------------------------------- METHODS ----------------------------------
	*/

	private:

};

#endif /* ********************************************** EXAMPLETEMAPLATE_HPP */