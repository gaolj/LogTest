--run_test=tutorial/tutorial_attributes
--run_test=@GLOBAL_LOGGER

BOOST_LOG_TRIVIAL(trace)
[2016-01-11 17:34:05.987649] [0x00003764] [trace]   A trace severity message

src::severity_logger< severity_level > slg;
BOOST_LOG_SEV(slg, normal) << "A regular message";		(slg.open_record(keywords::severity = normal);)

void add_common_attributes()
{
	boost::shared_ptr< logging::core > core = logging::core::get();
	core->add_global_attribute("LineID", attrs::counter< unsigned int >(1));
	core->add_global_attribute("TimeStamp", attrs::local_clock());
	// other attributes skipped for brevity
}

core->add_global_attribute("Scope", attrs::named_scope());

expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")