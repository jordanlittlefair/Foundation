#include "../Include/HTTPClient.hpp"

#define _WIN32_WINNT 0x0501
#include <boost/asio.hpp>

namespace Fnd
{
namespace HTTPClient
{
class HTTPClientImpl
{
	public:

		HTTPClientImpl();

		void SetServer( const std::string& server );
		void SetPort( const std::string& port );

		bool Send( const Request& request, Response& response );

		~HTTPClientImpl();

	private:

		std::string _server;
		std::string _port;
};
}
}

using namespace Fnd::HTTPClient;

HTTPClient::HTTPClient():
	_impl(new Fnd::HTTPClient::HTTPClientImpl())
{
}

void HTTPClient::SetServer( const std::string& server )
{
	_impl->SetServer(server);
}

void HTTPClient::SetPort( const std::string& port )
{
	_impl->SetPort(port);
}

bool HTTPClient::Send( const Request& request, Response& response )
{
	return _impl->Send(request,response);
}


HTTPClient::~HTTPClient()
{
}

HTTPClientImpl::HTTPClientImpl()
{
}

void HTTPClientImpl::SetServer( const std::string& server )
{
	_server = server;
}

void HTTPClientImpl::SetPort( const std::string& port )
{
	_port = port;
}

bool HTTPClientImpl::Send( const Request& request, Response& response )
{
	try
	{
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::socket socket(io_service);

		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::query query( _server, _port );
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		boost::asio::ip:: tcp::resolver::iterator end;

		boost::system::error_code error = boost::asio::error::host_not_found;
		while (error && endpoint_iterator != end)
		{
			socket.close();
			socket.connect(*endpoint_iterator++, error);
		}
		if (error)
		{
			auto m = error.message();
			return false;
		}

		{
			boost::asio::streambuf streambuf;
			std::ostream request_stream(&streambuf);

			std::string queries;
			for ( auto iter = request.queries.begin(); iter != request.queries.end(); ++iter )
			{
				if ( iter == request.queries.begin() )
				{
					queries += '?';
				}
				else
				{
					queries += '&';
				}
				queries += iter->first + "=" + iter->second;
			}

			request_stream
				<< request.method << " " << request.url << queries << " HTTP/1.1" << "\r\n"
				<< "Host: " << _server << ":" << _port << "\r\n"
				<< "Connection: close" << "\r\n";

			for ( auto iter = request.headers.begin(); iter != request.headers.end(); ++iter )
			{
				request_stream << iter->first << ": " << iter->second << "\r\n";
			}
			if ( !request.body.empty() )
			{
				request_stream << "Content-Length: " << request.body.length() << "\r\n";
			}

			request_stream
				<< "\r\n"
				<< request.body << "\r\n"
				<< "\r\n";

			boost::asio::write( socket, streambuf );
		}

		{
			boost::asio::streambuf streambuf;

			/*
				Read status line.
			*/
			boost::asio::read_until( socket, streambuf, "\r\n" );

			std::istream response_stream(&streambuf);
			std::string http_version;
			response_stream >> http_version;
			response_stream >> response.return_code;
			std::getline( response_stream, response.message );
			if ( !response_stream || http_version.substr(0,5) != "HTTP/" )
			{
				return false;
			}

			/*
				Read headers.
			*/
			boost::asio::read_until( socket, streambuf, "\r\n\r\n" );

			std::string header;
			while ( std::getline( response_stream, header ) && header != "\r" )
			{
				int key_start = 0;
				int key_end = header.find_first_of(':');

				std::string key = header.substr( 0, key_end - key_start );

				int val_start = header.find_first_not_of( ": ", key.length() );
				int val_end = header.find_last_not_of( "\r\n" ) + 1;

				std::string val = header.substr( val_start, val_end - val_start );

				response.headers[key] = val;
			}

			/*
				Read body.
			*/
			std::stringstream body_ss;

			if ( streambuf.size() > 0 )
			{
				body_ss << &streambuf;
			}

			boost::system::error_code err;
			while ( boost::asio::read( socket, streambuf, boost::asio::transfer_at_least(1), err ) )
			{
				body_ss << &streambuf;
			}
			if ( err != boost::asio::error::eof )
			{
				return false;
			}

			response.body = body_ss.str();
		}
	}
	catch(std::exception& e )
	{
		auto exc = e.what();
		(void)exc;
		return false;
	}

	return true;
}

HTTPClientImpl::~HTTPClientImpl()
{
}
