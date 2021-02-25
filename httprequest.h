/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod REST in Pawn Extension
 * Copyright 2017-2021 Erik Minekus
 * =============================================================================
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SM_RIPEXT_HTTPREQUEST_H_
#define SM_RIPEXT_HTTPREQUEST_H_

#include "extension.h"

class HTTPRequest
{
public:
	HTTPRequest(const std::string &url) : url(url) {}

	const std::string GetURL() const;

	int GetConnectTimeout() const;
	void SetConnectTimeout(int connectTimeout);

	bool GetFollowLocation() const;
	void SetFollowLocation(bool followLocation);

	int GetMaxRecvSpeed() const;
	void SetMaxRecvSpeed(int maxSpeed);

	int GetMaxSendSpeed() const;
	void SetMaxSendSpeed(int maxSpeed);

	int GetTimeout() const;
	void SetTimeout(int timeout);

private:
	const std::string url;
	int connectTimeout = 10;
	bool followLocation = true;
	int maxRecvSpeed = 0;
	int maxSendSpeed = 0;
	int timeout = 30;
};

#endif // SM_RIPEXT_HTTPREQUEST_H_
