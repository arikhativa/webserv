
#ifndef MATCHER_HPP
#define MATCHER_HPP

#include <algorithm>
#include <list>

#include <BasicHTTPRequest/BasicHTTPRequest.hpp>
#include <IConf/IConf.hpp>
#include <IServerConf/IServerConf.hpp>

namespace matcher
{
	const IServerConf *requestToServer(const IConf *conf, const IListen *socket, const BasicHTTPRequest &req);
	const ILocation *requestToLocation(const IServerConf *s, const BasicHTTPRequest &req);
} // namespace matcher

#endif
