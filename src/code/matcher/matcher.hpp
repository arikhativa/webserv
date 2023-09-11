
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

class HTTPCall;

namespace matcher
{

	const IServerConf *requestToServer(const IConf *conf, const IListen *socket, const BasicHTTPRequest &req) throw();
	const ILocation *requestToLocation(const IServerConf *s, const BasicHTTPRequest &req) throw();
	Path rootToRequest(const HTTPCall &call);
	bool isAutoIndexOnToRequest(const HTTPCall &call);
	bool canUploadToRequest(const HTTPCall &call);

} // namespace matcher

#endif
