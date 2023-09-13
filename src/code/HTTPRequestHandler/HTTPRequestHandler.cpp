
#include <HTTPCall/HTTPCall.hpp>
#include <HTTPRequestHandler/HTTPRequestHandler.hpp>

void HTTPRequestHandler::GET(HTTPCall &request)
{
	try
	{
		const IPath *root(request.getLocation()->getRoot());
		Path url(root->get() + request.getBasicRequest().getPath());
		if (httpRequestHandlerGET::isDirectoryListing(url, request))
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), request.getLocation()->getErrorPageSet());
			response.setContentType(httpConstants::HTML_SUFFIX);
			response.setBody(
				httpRequestHandlerGET::getDirectoryContent(root, Path(request.getBasicRequest().getPath())));
			return (request.setResponse(response.getResponse()));
		}
		else if (FileManager::isFileExists(url.get()))
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), request.getLocation()->getErrorPageSet());
			response.setBody(httpRequestHandlerGET::getFileContent(url.get(), response));
			return (request.setResponse(response.getResponse()));
		}
		else
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::NOT_FOUND),
									request.getLocation()->getErrorPageSet());
			return (request.setResponse(response.getResponse()));
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::INTERNAL_SERVER_ERROR),
									 request.getLocation()->getErrorPageSet());
		return (request.setResponse(errorResponse.getResponse()));
	}
}

void HTTPRequestHandler::POST(HTTPCall &request)
{
	try
	{
		const IPath *root(request.getLocation()->getRoot());
		Path url(root->get() + request.getBasicRequest().getPath());
		if (!FileManager::isFileExists(url.get()))
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::NOT_FOUND),
									request.getLocation()->getErrorPageSet());
			return (request.setResponse(response.getResponse()));
		}
		if (httprequesthandlerPOST::isDirectoryListing(url, request))
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), request.getLocation()->getErrorPageSet());
			response.setContentType(httpConstants::HTML_SUFFIX);
			response.setBody(
				httprequesthandlerPOST::getDirectoryContent(root, Path(request.getBasicRequest().getPath())));
			return (request.setResponse(response.getResponse()));
		}
		ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), request.getLocation()->getErrorPageSet());
		response.setBody(httprequesthandlerPOST::getFileContent(url.get(), response));
		return (request.setResponse(response.getResponse()));
	}
	catch (const std::exception &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::INTERNAL_SERVER_ERROR),
									 request.getLocation()->getErrorPageSet());
		return (request.setResponse(errorResponse.getResponse()));
	}
}

void HTTPRequestHandler::DELETE(HTTPCall &request)
{
	try
	{
		const IPath *root(request.getLocation()->getRoot());
		Path url(root->get() + request.getBasicRequest().getPath());
		if (!FileManager::isFileExists(url.get()) || FileManager::isDirectory(url.get()))
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::NOT_FOUND),
									request.getLocation()->getErrorPageSet());
			return (request.setResponse(response.getResponse()));
		}
		httprequesthandlerDELETE::deleteFile(url);
		ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), request.getLocation()->getErrorPageSet());
		return (request.setResponse(response.getResponse()));
	}
	catch (const httprequesthandlerDELETE::DeleteFileException &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::CONFLICT),
									 request.getLocation()->getErrorPageSet());
		return (request.setResponse(errorResponse.getResponse()));
	}
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::INTERNAL_SERVER_ERROR),
									 request.getLocation()->getErrorPageSet());
		return (request.setResponse(errorResponse.getResponse()));
	}
}

void HTTPRequestHandler::UNKNOWN(HTTPCall &request)
{
	ResponseHeader response(HTTPStatusCode(HTTPStatusCode::METHOD_NOT_ALLOWED),
							request.getLocation()->getErrorPageSet());
	request.setResponse(response.getResponse());
}