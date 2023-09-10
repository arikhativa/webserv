
#ifndef DEFAULTPAGER_HPP
#define DEFAULTPAGER_HPP

#include <map>
#include <string>

#include <FileManager/FileManager.hpp>
#include <HTTPStatusCode/HTTPStatusCode.hpp>

namespace defaultPager
{
	std::string getPage(HTTPStatusCode::Code code);
	const std::map<HTTPStatusCode::Code, std::string> &getPages(void);

} // namespace defaultPager

#endif
