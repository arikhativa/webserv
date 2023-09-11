
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
	(void)request;
	request.setResponse("HTTP/1.1 200 OK\r\n\r\nYOU SENT A POST REQUEST");
}

void HTTPRequestHandler::DELETE(HTTPCall &request)
{
	(void)request;
	request.setResponse("HTTP/1.1 200 OK\r\n\r\nYOU SENT A DELETE REQUEST");
}

void HTTPRequestHandler::UNKNOWN(HTTPCall &request)
{
	(void)request;
	request.setResponse("HTTP/1.1 200 OK\r\n\r\nYOU SENT A UNKNOWN REQUEST");
}