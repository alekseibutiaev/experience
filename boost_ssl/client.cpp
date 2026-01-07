// https://habrahabr.ru/post/271203/

// openssl genrsa -out user.key 2048
// openssl req -new -key user.key -out user.csr
// openssl x509 -req -in user.csr -CA rootca.crt -CAkey rootca.key -CAcreateserial -out user.crt -days 20000
// openssl verify -CAfile rootca.crt rootca.crt Ok
// openssl verify -CAfile rootca.crt user.crt Ok
// openssl verify -CAfile user.crt user.crt Error
// openssl dhparam -out dh2048.pem 2048
// password test_key
// g++ -std=c++11 client.cpp -o client -lboost_system -lpthread -lssl -pthread -lcrypto


#include <cstdlib>
#include <iostream>
#include <functional>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

enum { max_length = 1024 };

class client
{
public:
	client( boost::asio::io_service& io_service, boost::asio::ssl::context& context,
			boost::asio::ip::tcp::resolver::iterator endpoint_iterator )
		: socket_( io_service, context )
	{
		socket_.set_verify_mode( boost::asio::ssl::verify_peer );
		socket_.set_verify_callback( std::bind( &client::verify_certificate, this, std::placeholders::_1, std::placeholders::_2 ) );
		connect( endpoint_iterator );
	}

	bool verify_certificate( bool preverified, boost::asio::ssl::verify_context& ctx )
	{
		// The verify callback can be used to check whether the certificate that is
		// being presented is valid for the peer. For example, RFC 2818 describes
		// the steps involved in doing this for HTTPS. Consult the OpenSSL
		// documentation for more details. Note that the callback is called once
		// for each certificate in the certificate chain, starting from the root
		// certificate authority.

		// In this example we will simply print the certificate's subject name.
		char subject_name[256];
		X509* cert = X509_STORE_CTX_get_current_cert( ctx.native_handle() );
		X509_NAME_oneline( X509_get_subject_name( cert ), subject_name, 256 );
		std::cout << "Verifying " << subject_name << "\n";

		return preverified;
	}

	void handle_connect( const boost::system::error_code& error,
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator )
	{
		if( !error )
		{
			socket_.async_handshake( boost::asio::ssl::stream_base::client,
				std::bind( &client::handle_handshake, this, std::placeholders::_1 ) );
		}
		else if( endpoint_iterator != boost::asio::ip::tcp::resolver::iterator() )
		{
			socket_.lowest_layer().close();
			connect( endpoint_iterator );
		}
		else
			std::cout << "Connect failed: " << error << "\n";
	}

	void handle_handshake( const boost::system::error_code& error )
	{
		if( !error )
		{
			std::cout << "Enter message: ";
			std::cin.getline( request_, max_length );
			size_t request_length = strlen( request_ );
			boost::asio::async_write( socket_, boost::asio::buffer(request_, request_length),
					std::bind( &client::handle_write, this, std::placeholders::_1, std::placeholders::_2 ) );
		}
		else
			std::cout << "Handshake failed: " << error << "\n";
	}

	void handle_write( const boost::system::error_code& error, size_t bytes_transferred )
	{
		if (!error)
		{
			boost::asio::async_read( socket_, boost::asio::buffer( reply_, bytes_transferred ),
					std::bind( &client::handle_read, this, std::placeholders::_1, std::placeholders::_2 ) );
		}
		else
		{
		 std::cout << "Write failed: " << error << "\n";
		}
	}

	void handle_read( const boost::system::error_code& error, size_t bytes_transferred )
	{
		if( !error )
		{
			std::cout << "Reply: ";
			std::cout.write(reply_, bytes_transferred);
			std::cout << "\n";
		}
		else
			std::cout << "Read failed: " << error << "\n";
	}

	void connect( boost::asio::ip::tcp::resolver::iterator endpoint_iterator )
	{
		boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
		socket_.lowest_layer().async_connect( endpoint,
			std::bind( &client::handle_connect, this, std::placeholders::_1, ++endpoint_iterator ) );
	}

private:
	boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
	char request_[ max_length ];
	char reply_[ max_length ];
};

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: client <host> <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query( argv[1], argv[2] );
    boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

    boost::asio::ssl::context ctx(io_service, boost::asio::ssl::context::sslv23);
    ctx.set_verify_mode(boost::asio::ssl::context::verify_peer);
    ctx.load_verify_file( CLIENT_VEREFI );

    client c( io_service, ctx, iterator );

    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}

