/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
#include <boost/test/unit_test.hpp> 
#include "main.h"

#include <boost/move/utility.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::logger_mt)

void logging_function1()
{
    src::logger lg;

//[ example_tutorial_logging_manual_logging
    logging::record rec = lg.open_record();
    if (rec)
    {
        logging::record_ostream strm(rec);
        strm << "Hello, World!";
        strm.flush();
        lg.push_record(boost::move(rec));
    }
//]
}

void logging_function2()
{
    src::logger_mt& lg = my_logger::get();
    BOOST_LOG(lg) << "Greetings from the global logger!";
}

BOOST_AUTO_TEST_SUITE(ts_tutorial, *boost::unit_test::enable_if<tutorial>())
BOOST_AUTO_TEST_CASE(tutorial_logging)
{
    logging::add_file_log("sample.log");
    logging::add_common_attributes();

    logging_function1();
    logging_function2();

}
BOOST_AUTO_TEST_SUITE_END()