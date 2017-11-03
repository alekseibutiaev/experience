// https://habrahabr.ru/post/271203/

// openssl genrsa -out user.key 2048
// openssl req -new -key user.key -out user.csr
// openssl x509 -req -in user.csr -CA rootca.crt -CAkey rootca.key -CAcreateserial -out user.crt -days 20000
// openssl verify -CAfile rootca.crt rootca.crt Ok
// openssl verify -CAfile rootca.crt user.crt Ok
// openssl verify -CAfile user.crt user.crt Error
// openssl dhparam -out dh2048.pem 2048
// password test_key
// g++ -std=c++11 server.cpp -o server -lboost_system -lpthread -lssl -pthread -lcrypto


#include <cstdlib>
#include <iostream>
#include <functional>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

class session
{
public:
  session(boost::asio::io_service& io_service, boost::asio::ssl::context& context)
    : socket_( io_service, context )
  {
  }

  boost::asio::ssl::stream<boost::asio::ip::tcp::socket>::lowest_layer_type& socket()
  {
    return socket_.lowest_layer();
  }

  void start()
  {
    socket_.async_handshake(boost::asio::ssl::stream_base::server,
        std::bind( &session::handle_handshake, this, std::placeholders::_1 ) );
  }

  void handle_handshake(const boost::system::error_code& error)
  {
    if( !error )
      socket_.async_read_some(boost::asio::buffer(data_, max_length),
          std::bind( &session::handle_read, this, std::placeholders::_1, std::placeholders::_2 ) );
    else
      delete this;
  }

  void handle_read( const boost::system::error_code& error, size_t bytes_transferred )
  {
    if( !error )
      boost::asio::async_write( socket_, boost::asio::buffer( data_, bytes_transferred ),
				std::bind(&session::handle_write, this, std::placeholders::_1 ) );
    else
      delete this;
  }

  void handle_write( const boost::system::error_code& error )
  {
    if( !error )
      socket_.async_read_some( boost::asio::buffer(data_, max_length),
          std::bind( &session::handle_read, this, std::placeholders::_1, std::placeholders::_2 ) );
    else
      delete this;
  }

private:
  boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
  enum { max_length = 1024 };
  char data_[max_length];
};

class server
{
public:

  server( boost::asio::io_service& io_service, unsigned short port )
    : io_service_(io_service)
    , acceptor_(io_service, boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), port ) )
		, context_( io_service, boost::asio::ssl::context::sslv23 )
  {
    context_.set_options( boost::asio::ssl::context::default_workarounds
        | boost::asio::ssl::context::no_sslv2 | boost::asio::ssl::context::single_dh_use );
    context_.set_password_callback( std::bind( &server::get_password, this ) );
    context_.use_certificate_chain_file( SERVER_CERTIFICATE_CHAIN );
    context_.use_private_key_file( SERVER_PRIVATE_KEY, boost::asio::ssl::context::pem );
    context_.use_tmp_dh_file( SERVER_TMP_DH );
		accept();
  }

  std::string get_password() const
  {
		std::cout << __FUNCTION__ << std::endl;
    return SERVER_PASSWORD;
  }

  void handle_accept(session* new_session,
      const boost::system::error_code& error)
  {
    if (!error)
      new_session->start();
    else
      delete new_session;
		accept();
  }

	void accept()
	{
    session* new_session = new session( io_service_, context_ );
    acceptor_.async_accept( new_session->socket(), std::bind( &server::handle_accept, this, new_session,
          std::placeholders::_1 ) );
	}

private:

  boost::asio::io_service& io_service_;
  boost::asio::ip::tcp::acceptor acceptor_;
  boost::asio::ssl::context context_;
};

int main(int argc, char* argv[])
{
	std::cout
			<< SERVER_CERTIFICATE_CHAIN << std::endl
			<< SERVER_PRIVATE_KEY << std::endl
			<< SERVER_TMP_DH << std::endl
			<< SERVER_PASSWORD << std::endl
			<< CLIENT_VEREFI
			<< std::endl;
  try
  {
    if( argc != 2 )
    {
      std::cerr << "Usage: server <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;
			
    server s(io_service, std::atoi( argv[1] ) );

    io_service.run();
  }
  catch( std::exception& e )
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}

