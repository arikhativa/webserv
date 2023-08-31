
#include <HTTPRequestHandler/HTTPRequestHandler.hpp>

void HTTPRequestHandler::GET(HTTPRequest &request)
{
	try
	{
		BasicHTTPRequest requestRecived = request.getBasicRequest();
		requestRecived.parseRaw();
		Path url(request.getPathServerDirectory().get() + requestRecived.getPath());
		if (httprequesthandlerGET::isDirectory(url.get()) && request.isAutoIndexOn())
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), request.getErrorPages());
			response.setContentType(httpConstants::HTML_SUFFIX);
			response.setBody(httprequesthandlerGET::getDirecoryContent(request.getPathServerDirectory(),
																	   Path(requestRecived.getPath())));
			return (request.setResponse(response.getResponse()));
		}
		else if (httprequesthandlerGET::isFileExists(url.get()))
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), request.getErrorPages());
			response.setBody(httprequesthandlerGET::getFileContent(url.get(), response));
			return (request.setResponse(response.getResponse()));
		}
		else
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::NOT_FOUND), request.getErrorPages());
			return (request.setResponse(response.getResponse()));
		}
	}
	catch (const BasicHTTPRequest::Incomplete &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::BAD_REQUEST), request.getErrorPages());
		return (request.setResponse(errorResponse.getResponse()));
	}
	catch (const BasicHTTPRequest::Invalid &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::BAD_REQUEST), request.getErrorPages());
		return (request.setResponse(errorResponse.getResponse()));
	}
	catch (const std::exception &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::INTERNAL_SERVER_ERROR), request.getErrorPages());
		return (request.setResponse(errorResponse.getResponse()));
	}
}

void HTTPRequestHandler::POST(HTTPRequest &request)
{
	try
	{
		BasicHTTPRequest requestRecived = request.getBasicRequest();
		requestRecived.parseRaw();
		Path url(request.getPathServerDirectory().get() + requestRecived.getPath());
		if (!httprequesthandlerPOST::isFileExists(url.get()))
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::NOT_FOUND), request.getErrorPages());
			return (request.setResponse(response.getResponse()));
		}
		if (httprequesthandlerPOST::isDirectory(url.get()))
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), request.getErrorPages());
			response.setContentType(httpConstants::HTML_SUFFIX);
			response.setBody(httprequesthandlerPOST::getDirecoryContent(request.getPathServerDirectory(),
																		Path(requestRecived.getPath())));
			return (request.setResponse(response.getResponse()));
		}
		ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), request.getErrorPages());
		response.setBody(httprequesthandlerPOST::getFileContent(url.get(), response));
		return (request.setResponse(response.getResponse()));
	}
	catch (const BasicHTTPRequest::Incomplete &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::BAD_REQUEST), request.getErrorPages());
		return (request.setResponse(errorResponse.getResponse()));
	}
	catch (const BasicHTTPRequest::Invalid &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::BAD_REQUEST), request.getErrorPages());
		return (request.setResponse(errorResponse.getResponse()));
	}
	catch (const std::exception &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::INTERNAL_SERVER_ERROR), request.getErrorPages());
		return (request.setResponse(errorResponse.getResponse()));
	}
}

void HTTPRequestHandler::DELETE(HTTPRequest &request)
{
	try
	{
		BasicHTTPRequest requestRecived = request.getBasicRequest();
		requestRecived.parseRaw();
		Path path(request.getPathServerDirectory().get() + requestRecived.getPath());
		if (!httprequesthandlerDELETE::isFileExists(path.get()) || httprequesthandlerDELETE::isDirectory(path.get()))
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::NOT_FOUND), request.getErrorPages());
			return (request.setResponse(response.getResponse()));
		}
		httprequesthandlerDELETE::deleteFile(path.get());
		ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), request.getErrorPages());
		return (request.setResponse(response.getResponse()));
	}
	catch (const BasicHTTPRequest::Incomplete &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::BAD_REQUEST), request.getErrorPages());
		return (request.setResponse(errorResponse.getResponse()));
	}
	catch (const BasicHTTPRequest::Invalid &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::BAD_REQUEST), request.getErrorPages());
		return (request.setResponse(errorResponse.getResponse()));
	}
	catch (const std::exception &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::INTERNAL_SERVER_ERROR), request.getErrorPages());
		return (request.setResponse(errorResponse.getResponse()));
	}
}

void HTTPRequestHandler::UNKNOWN(HTTPRequest &request)
{
	(void)request;
	request.setResponse("HTTP/1.1 200 OK\r\n\r\nYOU SENT A UNKNOWN REQUEST");
}