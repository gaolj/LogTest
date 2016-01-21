/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
#include <boost/test/unit_test.hpp> 


//[ example_tutorial_trivial
#include <boost/log/trivial.hpp>

BOOST_AUTO_TEST_SUITE(tutorial)
BOOST_AUTO_TEST_CASE(tutorial_trivial)
{
	namespace logging = boost::log;
	logging::core::get()->flush();
	logging::core::get()->reset_filter();
	logging::core::get()->remove_all_sinks();
	
	BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
    BOOST_LOG_TRIVIAL(info) << "An informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
    BOOST_LOG_TRIVIAL(error) << "An error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

}
//]
BOOST_AUTO_TEST_SUITE_END()