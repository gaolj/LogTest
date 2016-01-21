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
}

sink->set_filter(severity >= warning || (expr::has_attr(tag_attr) && tag_attr == "IMPORTANT_MESSAGE"));

core->add_global_attribute("Scope", attrs::named_scope());
BOOST_LOG_NAMED_SCOPE("named_scope_logging");

expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")


logging::add_file_log	file:///D:/Program%20Files/boost_1_59_0/libs/log/doc/html/boost/log/add_file_log.html

[Logging core]
core->set_global_attributes
core->add_thread_attributes 
core->add_global_attribute("LineID", attrs::counter< unsigned int >());
core->remove_global_attribute(res.first);
core->set_filter(expr::attr< severity_level >("Severity") >= error);
core->set_exception_handler
core->add_sink(sink);
core->remove_sink(sink);
core->open_record
core->push_record

[Logging sources]
logging::attribute_set::iterator m_remote_addr = m_logger.add_attribute("RemoteAddress", attrs::constant< std::string >(sIP)).first;
m_logger.remove_attribute(m_remote_addr);
BOOST_LOG(m_logger) << logging::add_value("ReceivedSize", size) << "Some data received";	// The attribute will be attached only to this log record.

src::channel_logger< > m_net(keywords::channel = "net")

[Global loggers]
BOOST_LOG_GLOBAL_LOGGER(my_logger, src::severity_logger_mt)
BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::severity_logger_mt< >)
BOOST_LOG_INLINE_GLOBAL_LOGGER_CTOR_ARGS(	my_logger,
											src::severity_channel_logger< >,
											(keywords::severity = error)(keywords::channel = "my_channel"))
BOOST_LOG_INLINE_GLOBAL_LOGGER_INIT(my_logger, src::severity_logger_mt)
{
	src::severity_logger_mt< > lg;
	lg.add_attribute("StopWatch", boost::make_shared< attrs::timer >());
	return lg;
}

[Sink frontends]
set_filter		reset_filter
set_formatter	reset_formatter
set_exception_handler

sinks::unlocked_sink
sinks::synchronous_sink
sinks::asynchronous_sink


[Sink backends]
sinks::text_ostream_backend
sinks::text_file_backend
sinks::text_multifile_backend 
sinks::syslog_backend
sinks::debug_output_backend
sinks::simple_event_log_backend



[Output manipulators]
logging::to_log_manip< int > manip = logging::to_log(1010);
logging::to_log_manip< int, tag_A > manip = logging::to_log< tag_A >(1010);
BOOST_LOG(lg) << logging::add_value("MyAttr", 10) << "Hello world!";
BOOST_LOG(lg) << "Packet received: " << logging::dump(packet.data(), packet.size(), 8);
BOOST_LOG(lg) << "Matrix     dump: " << logging::dump_elements(matrix.data(), matrix.size());

[Simplified library initialization tools]
logging::add_console_log();	//logging to std::clog
logging::add_console_log(std::cout);
logging::add_file_log("test.log");
boost::shared_ptr<sinks::synchronous_sink< sinks::text_ostream_backend >> sink = logging::add_console_log();
