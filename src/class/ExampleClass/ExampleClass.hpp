/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExampleClass.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrabby <yrabby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:22:28 by yrabby            #+#    #+#             */
/*   Updated: 2023/06/28 13:29:18 by yrabby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXAMPLECLASS_HPP
# define EXAMPLECLASS_HPP

# ifdef TEST_ON
#  define private public
#  define protected public
# endif

# include <iostream>
# include <string>

class ExampleClass
{

	public:

		ExampleClass();
		explicit ExampleClass(int i);
		ExampleClass( ExampleClass const & src );
		~ExampleClass();

		ExampleClass &		operator=( ExampleClass const & rhs );

		int		getValue(void) const;

	private:
		int	_value;

		void	_setValue(int value);

};

std::ostream &			operator<<( std::ostream & o, ExampleClass const & i );

#endif /* **************************************************** EXAMPLECLASS_H */
