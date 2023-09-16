
#ifndef MATCHER_HPP
#define MATCHER_HPP

#include <algorithm>
#include <list>

#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <HTTPCall/HTTPCall.hpp>
#include <IConf/IConf.hpp>
#include <IServerConf/IServerConf.hpp>
#include <Location/Location.hpp>
#include <Path/Path.hpp>
#include <ResponseHeader/ResponseHeader.hpp>

class HTTPCall;

namespace matcher
{

	const IServerConf *requestToServer(const IConf *conf, const IListen *socket, const BasicHTTPRequest &req) throw();
	const ILocation *requestToLocation(const IServerConf *s, const BasicHTTPRequest &req) throw();
	void cgiToResponse(const std::string &content, ResponseHeader &response);
} // namespace matcher

#endif
