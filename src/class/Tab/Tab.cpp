
#include <Tab/Tab.hpp>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Tab::Tab()
{
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Tab::~Tab()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

std::ostream &operator<<(std::ostream &o, Tab const &i)
{
	char **tab = i.toCTable();
	o << "Tab[";
	for (int j = 0; tab[j] != NULL; j++)
	{
		o << tab[j] << std::endl;
	}
	o << "]";
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

char **Tab::toCTable(void) const
{
	char **tab = (char **)calloc(this->_tab.size() + 1, sizeof(char *));
	int i = 0;
	for (std::map< int, std::string >::const_iterator it = this->_tab.begin(); it != this->_tab.end(); it++)
	{
		tab[i] = strdup(it->second.c_str());
		i++;
	}
	tab[i] = NULL;
	return tab;
}

void Tab::add(const std::string &value)
{
	int key = 0;
	if (this->_tab.size() > 0)
		key = this->_tab.rbegin()->first + 1;
	this->_tab.insert(std::make_pair(key, value));
}

const std::string &Tab::get(const int &key) const
{
	return this->_tab.at(key);
}

void Tab::freeTab(char **tab) const
{
	if (tab != NULL)
	{
		for (int i = 0; tab[i] != NULL; i++)
		{
			if (tab[i] != NULL)
				free(tab[i]);
			tab[i] = NULL;
		}
		free(tab);
		tab = NULL;
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */
