
#ifndef BEZPIECZENSTWO6_STDAFX_H
#define BEZPIECZENSTWO6_STDAFX_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>

#include <boost/random.hpp>
#include <boost/multiprecision/gmp.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/future.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"

typedef boost::multiprecision::mpz_int int_type;

#define SERVER_PORT 2137
#define DEFAULT_BUFFLEN 2048

#endif //BEZPIECZENSTWO6_STDAFX_H