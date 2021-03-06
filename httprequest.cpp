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

#include "httprequest.h"

const std::string HTTPRequest::BuildURL() const
{
	std::string url(this->url);
	url.append(query);

	return url;
}

void HTTPRequest::AppendQueryParam(const char *name, const char *value)
{
	CURL *curl = curl_easy_init();
	if (curl == NULL)
	{
		return;
	}

	char *escapedName = curl_easy_escape(curl, name, 0);
	char *escapedValue = curl_easy_escape(curl, value, 0);

	if (escapedName != NULL && escapedValue != NULL)
	{
		query.append(query.size() == 0 ? "?" : "&");
		query.append(escapedName);
		query.append("=");
		query.append(escapedValue);
	}

    curl_free(escapedName);
    curl_free(escapedValue);
	curl_easy_cleanup(curl);
}

struct curl_slist *HTTPRequest::BuildHeaders(const char *acceptTypes, const char *contentType)
{
	struct curl_slist *headers = NULL;
	char header[8192];

	snprintf(header, sizeof(header), "Accept: %s", acceptTypes);
	headers = curl_slist_append(headers, header);

	snprintf(header, sizeof(header), "Content-Type: %s", contentType);
	headers = curl_slist_append(headers, header);

	for (HTTPHeaderMap::iterator iter = this->headers.iter(); !iter.empty(); iter.next())
	{
		snprintf(header, sizeof(header), "%s: %s", iter->key.chars(), iter->value.c_str());
		headers = curl_slist_append(headers, header);
	}

	return headers;
}

void HTTPRequest::SetHeader(const char *name, const char *value)
{
	std::string vstr(value);
	headers.replace(name, std::move(vstr));
}

bool HTTPRequest::UseBasicAuth() const
{
	return useBasicAuth;
}

const std::string HTTPRequest::GetUsername() const
{
	return username;
}

const std::string HTTPRequest::GetPassword() const
{
	return password;
}

void HTTPRequest::SetBasicAuth(const char *username, const char *password)
{
	this->useBasicAuth = true;
	this->username = username;
	this->password = password;
}

int HTTPRequest::GetConnectTimeout() const
{
	return connectTimeout;
}

void HTTPRequest::SetConnectTimeout(int connectTimeout)
{
	this->connectTimeout = connectTimeout;
}

bool HTTPRequest::GetFollowLocation() const
{
	return followLocation;
}

void HTTPRequest::SetFollowLocation(bool followLocation)
{
	this->followLocation = followLocation;
}

int HTTPRequest::GetMaxRecvSpeed() const
{
	return maxRecvSpeed;
}

void HTTPRequest::SetMaxRecvSpeed(int maxSpeed)
{
	this->maxRecvSpeed = maxSpeed;
}

int HTTPRequest::GetMaxSendSpeed() const
{
	return maxSendSpeed;
}

void HTTPRequest::SetMaxSendSpeed(int maxSpeed)
{
	this->maxSendSpeed = maxSpeed;
}

int HTTPRequest::GetTimeout() const
{
	return timeout;
}

void HTTPRequest::SetTimeout(int timeout)
{
	this->timeout = timeout;
}
