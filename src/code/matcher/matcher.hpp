
#ifndef MATCHER_HPP
#define MATCHER_HPP

#include <algorithm>
#include <list>

#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <IConf/IConf.hpp>
#include <IServerConf/IServerConf.hpp>
#include <Location/Location.hpp>
#include <Path/Path.hpp>
#include <Server/Server.hpp>

namespace matcher
{
	const IServerConf *requestToServer(const IConf *conf, const IListen *socket, const BasicHTTPRequest &req);
	const ILocation *requestToLocation(const IServerConf *s, const BasicHTTPRequest &req);
	Path rootToRequest(const Server *server, const BasicHTTPRequest &req);
	bool isAutoIndexOnToRequest(const Server *server, const BasicHTTPRequest &req);
	bool canUploadToRequest(const Server *server, const BasicHTTPRequest &req);
} // namespace matcher

#endif
