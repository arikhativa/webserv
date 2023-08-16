
#ifndef BASIC_H_T_T_P_REQUEST_HPP
#define BASIC_H_T_T_P_REQUEST_HPP

#include <cstring>
#include <iostream>
#include <map>
#include <string>

#include <ABaseHTTPCall/ABaseHTTPCall.hpp>
#include <Path/Path.hpp>
#include <httpConstants/httpConstants.hpp>
#include <mapPrint/mapPrint.hpp>
#include <parser/parser.hpp>

#ifdef TEST_ON
#define private public
#define protected public
#endif

class BasicHTTPRequest : public ABaseHTTPCall
{
  public:
	enum Type
	{
		GET,
		POST,
		DELETE,
	};

	explicit BasicHTTPRequest(const std::string &raw_request);
	BasicHTTPRequest(const BasicHTTPRequest &src);
	virtual ~BasicHTTPRequest();

	BasicHTTPRequest &operator=(const BasicHTTPRequest &rhs);

	virtual void parseRaw(void);
	virtual std::string toString(void) const;
	virtual void unParse(void);

	Type getType(void) const;
	const std::string &getPath(void) const;
	const std::string &getQuery(void) const;

	static std::string toStringType(BasicHTTPRequest::Type t);

  private:
	Type _type;
	Path _path;
	std::string _query;

	static BasicHTTPRequest::Type _parseType(const std::string &raw_request);
	static Path _parsePath(const std::string &raw_request);
	static std::string _parseQuery(const std::string &raw_request);
};

std::ostream &operator<<(std::ostream &o, const BasicHTTPRequest &i);

#ifdef TEST_ON
#undef private
#undef protected
#endif

#endif /* BASIC_H_T_T_P_REQUEST_HPP */
