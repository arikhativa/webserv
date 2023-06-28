/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExampleClass.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrabby <yrabby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:22:28 by yrabby            #+#    #+#             */
/*   Updated: 2023/06/28 11:06:36 by yrabby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXAMPLECLASS_HPP
# define EXAMPLECLASS_HPP

# include <iostream>
# include <string>

class ExampleClass
{

	public:

		explicit ExampleClass(int i);
		ExampleClass( ExampleClass const & src );
		~ExampleClass();

		ExampleClass &		operator=( ExampleClass const & rhs );

		int		getValue(void) const;

	private:
		int	_value;

};

std::ostream &			operator<<( std::ostream & o, ExampleClass const & i );

#endif /* **************************************************** EXAMPLECLASS_H */
