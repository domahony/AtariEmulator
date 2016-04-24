/*
 * Logging.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: domahony
 */

#include "Logging.h"

namespace LOG {

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;

void init() {

    // Construct the sink
    typedef sinks::synchronous_sink< sinks::text_ostream_backend > text_sink;

    boost::shared_ptr< text_sink > sink = boost::make_shared< text_sink >();

    // Add a stream to write log to
    sink->locked_backend()->add_stream(
        boost::make_shared< std::ofstream >("sample.log"));

    // Register the sink in the logging core
    logging::core::get()->add_sink(sink);
}

}




