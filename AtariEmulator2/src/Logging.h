/*
 * Logging.h
 *
 *  Created on: Apr 23, 2016
 *      Author: domahony
 */

#ifndef LOGGING_H_
#define LOGGING_H_

#define BOOST_LOG_DYN_LINK 1

#include <fstream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>


namespace LOG {

void init();

}




#endif /* LOGGING_H_ */
