
#ifndef PARSER_HPP
#define PARSER_HPP

#include <list>
#include <map>
#include <string>

#include <Token/Token.hpp>

namespace parser
{
	typedef bool (*t_rule)(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end);

	// is
	bool isValidServerKeyword(const std::list< Token >::const_iterator &it);
	bool isValidLocationKeyword(const std::list< Token >::const_iterator &it);

	bool validate(const std::list< Token > &list);

	namespace rule
	{
		t_rule get(std::list< Token >::const_iterator it);
		bool server(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end);
		bool serverName(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end);
		bool root(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end);
		bool listen(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end);
		bool index(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end);
		bool errorPage(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end);
		bool redirect(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end);
		bool clientMaxBodySize(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end);

		// location
		bool location(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end);
		bool allowMethods(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end);
		bool autoIndex(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end);
		bool upload(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end);
		bool cgi(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end);

		// keywords
		bool blockStart(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end);
		bool blockEnd(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end);
		bool tilde(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end);
		bool separator(std::list< Token >::const_iterator it, const std::list< Token >::const_iterator &end);
	} // namespace rule

} // namespace parser

#endif