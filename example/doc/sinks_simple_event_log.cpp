/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
#include <boost/test/unit_test.hpp> 


#include <stdexcept>
#include <string>
#include <iostream>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <boost/log/common.hpp>

#if defined(BOOST_WINDOWS) && !defined(BOOST_LOG_WITHOUT_EVENT_LOG)

#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/event_log_backend.hpp>

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

//[ example_sinks_simple_event_log
// Complete sink type
typedef sinks::synchronous_sink< sinks::simple_event_log_backend > sink_t;

// Define application-specific severity levels
enum severity_level
{
    normal,
    warning,
    error
};

static void init_logging()
{
	logging::core::get()->flush();
	logging::core::get()->reset_filter();
	logging::core::get()->remove_all_sinks();

	// Create an event log sink
    boost::shared_ptr< sink_t > sink(new sink_t());

    sink->set_formatter
    (
        expr::format("%1%: [%2%] - %3%")
            % expr::attr< unsigned int >("LineID")
            % expr::attr< boost::posix_time::ptime >("TimeStamp")
            % expr::smessage
    );

    // We'll have to map our custom levels to the event log event types
    sinks::event_log::custom_event_type_mapping< severity_level > mapping("Severity");
    mapping[normal] = sinks::event_log::info;
    mapping[warning] = sinks::event_log::warning;
    mapping[error] = sinks::event_log::error;

    sink->locked_backend()->set_event_type_mapper(mapping);

    // Add the sink to the core
    logging::core::get()->add_sink(sink);
}
//]

BOOST_AUTO_TEST_SUITE(sink)
BOOST_AUTO_TEST_CASE(sinks_simple_event_log)
{
    try
    {
        // Initialize logging library
        init_logging();

        // Add some attributes too
        logging::core::get()->add_global_attribute("TimeStamp", attrs::local_clock());
        logging::core::get()->add_global_attribute("LineID", attrs::counter< unsigned int >());

        // Do some logging
        src::severity_logger< severity_level > lg(keywords::severity = normal);
        BOOST_LOG_SEV(lg, normal) << "Some record for NT event log with normal level";
        BOOST_LOG_SEV(lg, warning) << "Some record for NT event log with warning level";
        BOOST_LOG_SEV(lg, error) << "Some record for NT event log with error level";

    }
    catch (std::exception& e)
    {
        std::cout << "FAILURE: " << e.what() << std::endl;
    }
}

#else

int main(int, char*[])
{
    return 0;
}

#endif
BOOST_AUTO_TEST_SUITE_END()