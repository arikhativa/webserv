#include <HTTPRequestHandler/HTTPRequestHandler.hpp>

//! TODO this is temporal until the server has error pages
std::list<const ErrorPage *> temporalErrorPages(void)
{
	std::list<const ErrorPage *> errorPages;
	return (errorPages);
}

std::string HTTPRequestHandler::get::GET(Server server, BasicHTTPRequest basicRequest)
{
	try
	{
		basicRequest.parseRaw();
		std::string path = "./res/exampleServer"; //= server.getConf().getRoot()->get();
		std::string file = basicRequest.getPath();
		std::string url = path + basicRequest.getPath();
		if (httprequesthandlerGET::isDirectory(url))
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), temporalErrorPages());
			response.setContentType(httpConstants::HTML_SUFFIX);
			response.setBody(httprequesthandlerGET::getDirecoryContent(path, file));
			return (response.getResponse());
		}
		else if (httprequesthandlerGET::isFileExists(url))
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), temporalErrorPages());
			response.setBody(httprequesthandlerGET::getFileContent(url, server, basicRequest, response));
			return (response.getResponse());
		}
		else
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::NOT_FOUND), temporalErrorPages());
			return (response.getResponse());
		}
	}
	catch (const BasicHTTPRequest::Incomplete &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::BAD_REQUEST), temporalErrorPages());
		return (errorResponse.getResponse());
	}
	catch (const BasicHTTPRequest::Invalid &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::BAD_REQUEST), temporalErrorPages());
		return (errorResponse.getResponse());
	}
	catch (const std::exception &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::INTERNAL_SERVER_ERROR), temporalErrorPages());
		return (errorResponse.getResponse());
	}
}

std::string HTTPRequestHandler::post::POST(Server server, BasicHTTPRequest basicRequest)
{
	try
	{
		basicRequest.parseRaw();
		std::string path = "./res/exampleServer"; //= server.getConf().getRoot()->get();
		std::string file = basicRequest.getPath();
		std::string url = path + basicRequest.getPath();
		if (!httprequesthandlerPOST::isFileExists(url))
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::NOT_FOUND), temporalErrorPages());
			return (response.getResponse());
		}
		if (httprequesthandlerPOST::isDirectory(url))
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), temporalErrorPages());
			if (file[file.length() - 1] != '/')
				file += "/";
			response.setContentType(httpConstants::HTML_SUFFIX);
			response.setBody(httprequesthandlerGET::getDirecoryContent(path, file));
			return (response.getResponse());
		}
		ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), temporalErrorPages());
		response.setBody(httprequesthandlerPOST::getFileContent(url, server, basicRequest, response));
		return (response.getResponse());
	}
	/*catch (const PollManager::PollTimeoutException)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::GATEWAY_TIMEOUT), temporalErrorPages());
		return (errorResponse.getResponse());
	}*/
	catch (const BasicHTTPRequest::Incomplete &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::BAD_REQUEST), temporalErrorPages());
		return (errorResponse.getResponse());
	}
	catch (const BasicHTTPRequest::Invalid &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::BAD_REQUEST), temporalErrorPages());
		return (errorResponse.getResponse());
	}
	/*catch (const ChunkManager::ChunkManagerException &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::BAD_REQUEST), temporalErrorPages());
		return (errorResponse.getResponse());
	}*/
	catch (const std::exception &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::INTERNAL_SERVER_ERROR), temporalErrorPages());
		return (errorResponse.getResponse());
	}
}

std::string HTTPRequestHandler::delete_::DELETE(Server server, BasicHTTPRequest basicRequest)
{
	try
	{
		basicRequest.parseRaw();
		(void)server;
		std::string path = "./res/exampleServer"; //= server.getConf().getRoot()->get();
		std::string file = basicRequest.getPath();
		if (!httprequesthandlerDELETE::isFileExists(path + file) || httprequesthandlerDELETE::isDirectory(path + file))
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::NOT_FOUND), temporalErrorPages());
			return (response.getResponse());
		}
		httprequesthandlerDELETE::deleteFile(path + file);
		ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), temporalErrorPages());
		return (response.getResponse());
	}
	catch (const BasicHTTPRequest::Incomplete &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::BAD_REQUEST), temporalErrorPages());
		return (errorResponse.getResponse());
	}
	catch (const BasicHTTPRequest::Invalid &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::BAD_REQUEST), temporalErrorPages());
		return (errorResponse.getResponse());
	}
	catch (const std::exception &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::INTERNAL_SERVER_ERROR), temporalErrorPages());
		return (errorResponse.getResponse());
	}
}

std::string HTTPRequestHandler::unknown::UNKNOWN(Server server)
{
	try
	{
		(void)server;
		ResponseHeader response(HTTPStatusCode(HTTPStatusCode::METHOD_NOT_ALLOWED), temporalErrorPages());
		//! TODO temporal, must use the server config
		response.setConnection("GET, POST, DELETE");
		return (response.getResponse());
	}
	catch (const std::exception &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::INTERNAL_SERVER_ERROR), temporalErrorPages());
		return (errorResponse.getResponse());
	}
}