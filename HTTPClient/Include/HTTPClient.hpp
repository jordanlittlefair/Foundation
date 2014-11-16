#pragma once

#ifndef _HTTPCLIENT_HPP_
#define _HTTPCLIENT_HPP_

#include <string>
#include <map>
#include <memory>

namespace Fnd
{
namespace HTTPClient
{

class HTTPClientImpl;

/**
	A struct to hold request data.
*/
struct Request
{
	std::string method;
	std::string url;
	std::map<std::string,std::string> queries;
	std::map<std::string,std::string> headers;
	std::string body;
};

/**
	A struct to hold response data.
*/
struct Response
{
	int return_code;
	std::string message;
	std::map<std::string,std::string> headers;
	std::string body;
};

/**
	A class used to synchronously send HTTP requests over a network.
*/
class HTTPClient
{
	public:

		/**
			Default constructor.
		*/
		HTTPClient();
	
		/**
			Set the server.
			@param server The server to send requests to.
		*/
		void SetServer( const std::string& server );
		
		/**
			Set the port.
			@param port The port to send requests to.
		*/
		void SetPort( const std::string& port );

		/**
			Send a HTTP request and receive a response.
			@param request The request struct initialised with the request data to send.
			@param response A reference to a response struct to fill with the received data.
			@return Returns true if the request was sent and the response has been filled with the received data.
		*/
		bool Send( const Request& request, Response& response );

		/**
			Destructor.
		*/
		~HTTPClient();

	private:
		
		std::unique_ptr<HTTPClientImpl> _impl;
};

}
}

#endif