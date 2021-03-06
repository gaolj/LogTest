/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
#include <boost/test/unit_test.hpp> 


#include <cstddef>
#include <iostream>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/log/utility/manipulators/to_log.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

//[ example_expressions_keyword_formatter_stream_tag
// We define our own severity levels
enum severity_level1
{
    normal,
    notification,
    warning,
    error,
    critical
};

// Define the attribute keywords
BOOST_LOG_ATTRIBUTE_KEYWORD(line_id, "LineID", unsigned int)
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level1)

// The operator is used for regular stream formatting
static std::ostream& operator<< (std::ostream& strm, severity_level1 level)
{
    static const char* strings[] =
    {
        "normal",
        "notification",
        "warning",
        "error",
        "critical"
    };

    if (static_cast< std::size_t >(level) < sizeof(strings) / sizeof(*strings))
        strm << strings[level];
    else
        strm << static_cast< int >(level);

    return strm;
}

// The operator is used when putting the severity level to log
static logging::formatting_ostream& operator<<
(
    logging::formatting_ostream& strm,
    logging::to_log_manip< severity_level1, tag::severity > const& manip
)
{
    static const char* strings[] =
    {
        "NORM",
        "NTFY",
        "WARN",
        "ERRR",
        "CRIT"
    };

    severity_level1 level = manip.get();
    if (static_cast< std::size_t >(level) < sizeof(strings) / sizeof(*strings))
        strm << strings[level];
    else
        strm << static_cast< int >(level);

    return strm;
}

static void init()
{
	logging::core::get()->flush();
	logging::core::get()->reset_filter();
	logging::core::get()->remove_all_sinks();

	logging::add_console_log
    (
        std::clog,
        // This makes the sink to write log records that look like this:
        // 1: <NORM> A normal severity message
        // 2: <ERRR> An error severity message
        keywords::format =
        (
            expr::stream
                << line_id
                << ": <" << severity
                << "> " << expr::smessage
        )
    );
}
//]

//[ example_expressions_keyword_lookup
void print_severity(logging::record_view const& rec)
{
    logging::value_ref< severity_level1, tag::severity > level = rec[severity];
    std::cout << level << std::endl;
}
//]


BOOST_AUTO_TEST_SUITE(expressions)
BOOST_AUTO_TEST_CASE(expressions_keyword_fmt_tag)
{
    init();
    logging::add_common_attributes();

    src::severity_logger< severity_level1 > lg;

    // These messages will be written with CAPS severity levels
    BOOST_LOG_SEV(lg, normal) << "A normal severity message";
    BOOST_LOG_SEV(lg, notification) << "A notification severity message";
    BOOST_LOG_SEV(lg, warning) << "A warning severity message";
    BOOST_LOG_SEV(lg, error) << "An error severity message";
    BOOST_LOG_SEV(lg, critical) << "A critical severity message";

    // This line will still use lower-case severity levels
    std::cout << "The regular output still uses lower-case formatting: " << normal << std::endl;

}
BOOST_AUTO_TEST_SUITE_END()