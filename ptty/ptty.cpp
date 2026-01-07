//============================================================================
// Name        : ptty.cpp
// Author      : Butyaev A.Y.
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <signal.h>
#include <unistd.h>
#include <termios.h>

#include <sys/poll.h>

#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#include <algorithm>
#include <utility>

const int Infinity = -1;
const int BufSize = 256;

template< typename TYPE, unsigned int SIZE >
TYPE* array_begin( TYPE(&A)[SIZE] ) {
  return &A[ 0 ];
}

template< typename TYPE, unsigned int SIZE >
TYPE* array_end( TYPE(&A)[SIZE] ) {
  return &A[ SIZE ];
}

void error( int f_Error ) {
  fprintf( stderr, "Error: %s\n", strerror( f_Error ) );
  exit( f_Error );
}

bool tuneport( int f_Fdtty ) {
  struct termios tios;
  if( 0 > tcgetattr( f_Fdtty, &tios ) )
    return false;
  // set raw mode
  cfmakeraw( &tios );
  cfsetispeed( &tios, B115200 );
  cfsetospeed( &tios, B115200 );
  if( tcsetattr( f_Fdtty, TCSAFLUSH, &tios ) < 0 )
    return false;
  return true;
}

const int rep_signals[] = { SIGINT, SIGHUP, SIGTTIN, SIGTTOU, SIGCHLD };

void signalhandler( int f_Sig ) {
  fprintf( stdout, "Catch signal %d\n", f_Sig );
}

void reposition( int f_Sig ) {
  if( SIG_ERR == signal( f_Sig, signalhandler ) ) {
    fprintf( stderr, "Can not reposition signal %d\n", f_Sig );
    exit( EXIT_FAILURE );
  }
}

int main( int ac, char* av[] ) {
  struct pollfd plfd;
  const char* pttyName;
  /* temporarily disable handler for SIGCHLD */
  signal(SIGCHLD, SIG_DFL);
  if( 0 > ( plfd.fd = getpt() ) || 0 > grantpt( plfd.fd ) ||
      0 > unlockpt( plfd.fd ) || 0L == ( pttyName = ptsname( plfd.fd ) ) )
    error( errno );
  // reposition some signals
  std::for_each( array_begin( rep_signals ), array_end( rep_signals ), &reposition );
  if( !tuneport( plfd.fd ) ) {
    fprintf( stderr, "Can not set raw mode for pseudo terminal.\n" );
    exit( EXIT_FAILURE );
  }
  fprintf( stdout, "Pseudo terminal name: %s\n", pttyName );
  plfd.events = POLLIN;
  for(;;) {
    if( 0 > poll( &plfd, 1, Infinity ) )
      error( errno );
    else {
      char buf[ BufSize ];
      int readn = read( plfd.fd, buf, BufSize );
      if( 0 > readn )
        error( errno );
      if( 0 > write( plfd.fd, buf, readn ) )
        error( errno );
    }
  }
  return EXIT_SUCCESS;
}
