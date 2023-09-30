
#include <defaultPager/defaultPager.hpp>

static std::map< HTTPStatusCode::Code, std::string > initPages(void)
{
	static const std::string base("res/default_error_pages/");

	std::map< HTTPStatusCode::Code, std::string > ret;

	ret[HTTPStatusCode::BAD_REQUEST] = base + "400.html";
	ret[HTTPStatusCode::UNAUTHORIZED] = base + "401.html";
	ret[HTTPStatusCode::FORBIDDEN] = base + "403.html";
	ret[HTTPStatusCode::NOT_FOUND] = base + "404.html";
	ret[HTTPStatusCode::METHOD_NOT_ALLOWED] = base + "405.html";
	ret[HTTPStatusCode::REQUEST_ENTITY_TOO_LARGE] = base + "413.html";
	ret[HTTPStatusCode::UNSUPPORTED_MEDIA_TYPE] = base + "415.html";
	ret[HTTPStatusCode::INTERNAL_SERVER_ERROR] = base + "500.html";
	ret[HTTPStatusCode::BAD_GATEWAY] = base + "502.html";
	ret[HTTPStatusCode::SERVICE_UNAVAILABLE] = base + "503.html";
	ret[HTTPStatusCode::GATEWAY_TIMEOUT] = base + "504.html";

	return ret;
}

static const std::map< HTTPStatusCode::Code, std::string > _default_pages(initPages());

std::vector< char > defaultPager::getPage(HTTPStatusCode::Code code)
{
	std::string key;

	try
	{
		key = _default_pages.at(code);
	}
	catch (const std::exception &e)
	{
		return std::vector< char >();
	}

	return FileManager::getFileContent(key);
}

const std::map< HTTPStatusCode::Code, std::string > &defaultPager::getPages(void)
{
	return _default_pages;
}
