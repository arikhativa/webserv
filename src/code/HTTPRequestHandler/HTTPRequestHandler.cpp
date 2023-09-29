
#include <HTTPCall/HTTPCall.hpp>
#include <HTTPRequestHandler/HTTPRequestHandler.hpp>

void HTTPRequestHandler::CGI(HTTPCall &request)
{
	Path pathCGI(request.getLocation()->getCGIConf().getPath());
	Port port = request.getSocket()->getPort();
	CgiManager *cgi_obj = new CgiManager(request.getBasicRequest(), pathCGI, request.getLocalPath(),
										 request.getClientHostHeader(), converter::numToString< uint16_t >(port.get()));
	request.setCgi(cgi_obj);
	cgi_obj->executeCgiManager();
}

void HTTPRequestHandler::GET(HTTPCall &request)
{
	try
	{
		const ILocation *l(request.getLocation());
		const IPath *root(l->getRoot());
		Path url(request.getBasicRequest().getPath());
		const Path &local_path(request.getLocalPath());

		if (!local_path.isEmpty() && !FileManager::isDirectory(local_path.get()) &&
			FileManager::isFileExists(local_path.get()))
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), l->getErrorPageSet());
			response.setBody(httpRequestHandlerGET::getFileContent(local_path.get(), response));
			request.setResponse(response.getResponse());
		}
		else if (httpRequestHandlerGET::isDirectoryListing(root, url, request))
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), l->getErrorPageSet());
			response.setContentType(httpConstants::HTML_SUFFIX);
			response.setBody(httpRequestHandlerGET::getDirectoryContent(root, url));
			request.setResponse(response.getResponse());
		}
		else if (!local_path.isEmpty() && FileManager::isDirectory(local_path.get()))
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::MOVED_PERMANENTLY), l->getErrorPageSet());
			response.setLocationHeader(url.get() + "/");
			request.setResponse(response.getResponse());
		}
		else
		{
			ResponseHeader response(HTTPStatusCode(HTTPStatusCode::NOT_FOUND),
									request.getLocation()->getErrorPageSet());
			request.setResponse(response.getResponse());
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::INTERNAL_SERVER_ERROR),
									 request.getLocation()->getErrorPageSet());
		request.setResponse(errorResponse.getResponse());
	}
}

void HTTPRequestHandler::POST(HTTPCall &request)
{
	try
	{
		const IPath *root(request.getLocation()->getRoot());
		Path url(root->get() + request.getBasicRequest().getPath());

		if (request.getLocation()->getUploadStore())
		{
			FileManager::createFile(request.getBasicRequest(), request.getLocation()->getUploadStore()->get());
		}
		else
		{
			FileManager::createFile(request.getBasicRequest(), root->get());
		}

		ResponseHeader response(HTTPStatusCode(HTTPStatusCode::CREATED), request.getLocation()->getErrorPageSet());

		response.setHeader(httpConstants::headers::CONTENT_TYPE, httpConstants::headers::JSON);
		std::string json = "{\"name\": \"" + request.getBasicRequest().getPath() + "\"}";
		response.setBody(json);
		request.setResponse(response.getResponse());
	}
	catch (const httpRequestHandlerPOST::FORBIDDEN &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::FORBIDDEN),
									 request.getLocation()->getErrorPageSet());
		request.setResponse(errorResponse.getResponse());
	}
	catch (const FileManager::FileManagerException &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::INTERNAL_SERVER_ERROR),
									 request.getLocation()->getErrorPageSet());
		request.setResponse(errorResponse.getResponse());
	}
	catch (const std::exception &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::INTERNAL_SERVER_ERROR),
									 request.getLocation()->getErrorPageSet());
		request.setResponse(errorResponse.getResponse());
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
			request.setResponse(response.getResponse());
			return;
		}
		httprequesthandlerDELETE::deleteFile(url);
		ResponseHeader response(HTTPStatusCode(HTTPStatusCode::OK), request.getLocation()->getErrorPageSet());
		request.setResponse(response.getResponse());
	}
	catch (const httprequesthandlerDELETE::DeleteFileException &e)
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::CONFLICT),
									 request.getLocation()->getErrorPageSet());
		request.setResponse(errorResponse.getResponse());
	}
	{
		ResponseHeader errorResponse(HTTPStatusCode(HTTPStatusCode::INTERNAL_SERVER_ERROR),
									 request.getLocation()->getErrorPageSet());
		request.setResponse(errorResponse.getResponse());
	}
}

void HTTPRequestHandler::UNKNOWN(HTTPCall &request)
{
	ResponseHeader response(HTTPStatusCode(HTTPStatusCode::METHOD_NOT_ALLOWED),
							request.getLocation()->getErrorPageSet());
	request.setResponse(response.getResponse());
}