/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   main.cpp
 * \author Andrey Semashev
 * \date   26.04.2008
 *
 * \brief  An example of initializing the library from a settings file.
 *         See the library tutorial for expanded comments on this code.
 *         It may also be worthwhile reading the Wiki requirements page:
 *         http://www.crystalclearsoftware.com/cgi-bin/boost_wiki/wiki.pl?Boost.Logging
 */

// #define BOOST_ALL_DYN_LINK 1
#include <boost/test/unit_test.hpp> 

#include <exception>
#include <string>
#include <iostream>
#include <fstream>

#include <boost/log/common.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/utility/setup/from_stream.hpp>

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;

using boost::shared_ptr;

// Here we define our application severity levels.
enum severity_level
{
    normal,
    notification,
    warning,
    error,
    critical
};

//  Global logger declaration
BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(test_lg3, src::severity_logger< >)

static void try_logging()
{
    src::severity_logger< >& lg = test_lg3::get();
    BOOST_LOG_SEV(lg, normal) << "This is a normal severity record";
    BOOST_LOG_SEV(lg, notification) << "This is a notification severity record";
    BOOST_LOG_SEV(lg, warning) << "This is a warning severity record";
    BOOST_LOG_SEV(lg, error) << "This is a error severity record";
    BOOST_LOG_SEV(lg, critical) << "This is a critical severity record";
}

BOOST_AUTO_TEST_SUITE(single)
BOOST_AUTO_TEST_CASE(settings_file)
{
    try
    {
        // Open the file
        std::ifstream settings("settings_file.txt");
        if (!settings.is_open())
        {
            std::cout << "Could not open settings.txt file" << std::endl;
        }

        // Read the settings and initialize logging library
        logging::init_from_stream(settings);

        // Add some attributes
        logging::core::get()->add_global_attribute("TimeStamp", attrs::local_clock());

        // Try logging
        try_logging();

        // Now enable tagging and try again
        BOOST_LOG_SCOPED_THREAD_TAG("Tag", "TAGGED");
        try_logging();

    }
    catch (std::exception& e)
    {
        std::cout << "FAILURE: " << e.what() << std::endl;
    }
}
BOOST_AUTO_TEST_SUITE_END()