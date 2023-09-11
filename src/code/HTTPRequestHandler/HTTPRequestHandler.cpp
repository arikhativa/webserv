
#include <HTTPCall/HTTPCall.hpp>
#include <HTTPRequestHandler/HTTPRequestHandler.hpp>

void HTTPRequestHandler::GET(HTTPCall &request)
{
	try
	{
		if (request.getBasicRequest().isBody())
			request.parseRawRequest();
		Path url(matcher::rootToRequest(request).get() + request.getBasicRequest().getPath());
		if (httprequesthandlerGET::isDirectoryListing(url, request))
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), request.getErrorPages());
			response.setContentType(httpConstants::HTML_SUFFIX);
			response.setBody(httprequesthandlerGET::getDirecoryContent(matcher::rootToRequest(request),
																	   Path(request.getBasicRequest().getPath())));
			return (request.setResponse(response.getResponse()));
		}
		else if (FileManager::isFileExists(url.get()))
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

void HTTPRequestHandler::POST(HTTPCall &request)
{
	try
	{
		if (request.getBasicRequest().isBody())
			request.parseRawRequest();
		Path url(matcher::rootToRequest(request).get() + request.getBasicRequest().getPath());
		if (!FileManager::isFileExists(url.get()))
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::NOT_FOUND), request.getErrorPages());
			return (request.setResponse(response.getResponse()));
		}
		if (httprequesthandlerPOST::isDirectoryListing(url, request))
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), request.getErrorPages());
			response.setContentType(httpConstants::HTML_SUFFIX);
			response.setBody(httprequesthandlerPOST::getDirecoryContent(matcher::rootToRequest(request),
																		Path(request.getBasicRequest().getPath())));
			return (request.setResponse(response.getResponse()));
		}
		ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), request.getErrorPages());
		response.setBody(httprequesthandlerPOST::getFileContent(url.get(), response));
		return (request.setResponse(response.getResponse()));
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

void HTTPRequestHandler::DELETE(HTTPCall &request)
{
	try
	{
		if (request.getBasicRequest().isBody())
			request.parseRawRequest();
		Path url(matcher::rootToRequest(request).get() + request.getBasicRequest().getPath());
		if (!FileManager::isFileExists(url.get()) || FileManager::isDirectory(url.get()))
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::NOT_FOUND), request.getErrorPages());
			return (request.setResponse(response.getResponse()));
		}
		httprequesthandlerDELETE::deleteFile(url);
		ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), request.getErrorPages());
		return (request.setResponse(response.getResponse()));
	}
	catch (const httprequesthandlerDELETE::DeleteFileException &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::CONFLICT), request.getErrorPages());
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

void HTTPRequestHandler::UNKNOWN(HTTPCall &request)
{
	(void)request;
	request.setResponse("HTTP/1.1 200 OK\r\n\r\nYOU SENT A UNKNOWN REQUEST");
}