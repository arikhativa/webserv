
#ifndef REPLACE_HPP
# define REPLACE_HPP

# ifdef TEST_ON
#  define private public
#  define protected public
# endif

# include <iostream>
# include <string>

class Replace
{
	public:
		Replace();
		explicit Replace(int i);
		Replace( Replace const & src );
		~Replace();

		Replace &		operator=( Replace const & rhs );

		int		getValue(void) const;

	private:
		int	_value;

		void	_setValue(int value);

};

std::ostream &			operator<<( std::ostream & o, Replace const & i );

#endif /* REPLACE_HPP */
