
#ifndef EXAMPLE_CLASS_HPP
# define EXAMPLE_CLASS_HPP

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

#endif /* EXAMPLE_CLASS_HPP */
