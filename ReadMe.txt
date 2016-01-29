--run_test=tutorial/tutorial_attributes

[Tutorial]
BOOST_LOG_TRIVIAL(trace)
[2016-01-11 17:34:05.987649] [0x00003764] [trace]   A trace severity message

src::severity_logger< severity_level > slg;
BOOST_LOG_SEV(slg, normal) << "A regular message";		(slg.open_record(keywords::severity = normal);)

void add_common_attributes()
{
	boost::shared_ptr< logging::core > core = logging::core::get();
	core->add_global_attribute("LineID", attrs::counter< unsigned int >(1));
	core->add_global_attribute("ProcessID", attrs::current_process_id());
	core->add_global_attribute("ThreadID", attrs::thread_id());	// add_global_attribute("ThreadID", attrs::current_thread_id());?
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

src::logger
src::severity_logger
src::channel_logger< > m_net(keywords::channel = "net")
src::severity_channel_logger


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
		unbounded_fifo_queu
		unbounded_ordering_queue
		bounded_fifo_queue
		bounded_ordering_queue


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


[Lambda expressions]
expr::stream 
expr::record
expr::smessage
expr::ends_with(expr::attr< std::string >("Domain"), ".ru")

Formatting expressions:
expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d ?%H:%M:%S")
expr::format_named_scope("Scopes", "%n")
expr::if_ (expr::has_attr< int >("ID"))	.else_[			]
expr::xml_decor


[Attributes]
Constants:
lg.add_attribute("MyInteger", attrs::constant<int>(10));
lg.add_attribute("MyInteger", attrs::make_constant(10));

Counters:
lg.add_attribute("LineCounter", attrs::counter<unsigned int>());	// starting from 0
lg.add_attribute("CountDown", attrs::counter< int >(100, -5));	// starting from 100 with step -5

Wall clock:
add_global_attribute("TimeStamp", attrs::local_clock());

Stop watch (timer):
m_logger.add_attribute("Duration", attrs::timer());

Named scopes:
logging::core::get()->add_thread_attribute("Scope", attrs::named_scope());
logging::core::get()->add_global_attribute("Scope", attrs::named_scope());
BOOST_LOG_FUNCTION();
BOOST_LOG_NAMED_SCOPE("case 0");

Current process identifier:
logging::core::get()->add_global_attribute("ProcessID",attrs::current_process_id());

Current process name:
logging::core::get()->add_global_attribute("Process",attrs::current_process_name());

Function objects as attributes:
logging::core::get()->add_global_attribute("MyRandomAttr", attrs::make_function(&std::rand));


******Sample******

	logging::formatter fmt = expr::stream
		<< std::setw(6) << std::setfill('0') << line_id << std::setfill(' ')
		<< ": <" << severity << ">\t"
		<< expr::if_(expr::has_attr(tag_attr))
			[
				expr::stream << "[" << tag_attr << "] "
			]
		<< expr::smessage;
	sink->set_formatter
	(
		expr::format("%1%: <%2%> %3%")
			% expr::attr< unsigned int >("LineID")
			% logging::trivial::severity
			% expr::smessage
	);


    sink->set_filter(severity >= warning || (expr::has_attr(tag_attr) && tag_attr == "IMPORTANT_MESSAGE"));

	
	logging::core::get()->add_thread_attribute("Scope", attrs::named_scope());	// 只对当前线程有效
	logging::core::get()->add_global_attribute("Scope", attrs::named_scope());	// 对所有线程有效
	BOOST_LOG_FUNCTION();
	BOOST_LOG_NAMED_SCOPE("named_scope_logging");
	BOOST_LOG_SCOPED_THREAD_ATTR("Uptime", attrs::timer());
	BOOST_LOG_SCOPED_THREAD_TAG("Tag", "IMPORTANT_MESSAGE");
	BOOST_LOG_SCOPED_THREAD_TAG("ThreadID", boost::this_thread::get_id());
	 
	BOOST_LOG_SCOPED_LOGGER_TAG(lg, "Tag", "Tagged line");
	lg.add_attribute("Tag", attrs::constant< std::string >("My tag value"));
    
    
	logging::add_file_log
	(
		keywords::open_mode = std::ios::app,
		keywords::auto_flush = true,
        keywords::file_name = "logs/tutorial_file_%N.log",								/*< file name pattern >*/
        keywords::rotation_size = 10 * 1024 * 1024,									/*< rotate files every 10 MiB... >*/
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),	/*< ...or at midnight >*/
        keywords::format = "[%TimeStamp%]: %Message%"									/*< log record format >*/
    );
    
	logging::add_file_log
    (
        keywords::file_name = "logs/tutorial_fmt_stream_%N.log",
        keywords::format =
        (
            expr::stream
                << expr::attr< unsigned int >("LineID")
                << ": <" << logging::trivial::severity
                << "> " << expr::smessage
        )
    );


	BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger3, src::logger_mt)
    src::logger_mt& lg = my_logger3::get();

	src::channel_logger< > m_net(keywords::channel = "net");
	BOOST_LOG_INLINE_GLOBAL_LOGGER_CTOR_ARGS(my_logger5, src::channel_logger_mt< >, (keywords::channel = "net"))
	BOOST_LOG_CHANNEL(my_logger5::get(), "net") << logging::add_value("RemoteAddress", m_remote_addr) << "Connection established";

	typedef src::severity_channel_logger_mt<severity_level, std::string> my_logger_mt;
	BOOST_LOG_INLINE_GLOBAL_LOGGER_INIT(my_logger2, my_logger_mt)
	{
		return my_logger_mt(keywords::channel = "my_logger2");
	}

	BOOST_LOG_ATTRIBUTE_KEYWORD(remote_address, "RemoteAddress", std::string)
	logging::attribute_set::iterator m_remote_addr = m_logger.add_attribute("RemoteAddress", attrs::constant< std::string >(remote_addr)).first;
	m_logger.remove_attribute(m_remote_addr);
	BOOST_LOG(m_logger) << logging::add_value("ReceivedSize", size) << "Some data received";


    boost::shared_ptr< sinks::text_file_backend > backend =
        boost::make_shared< sinks::text_file_backend >(
			keywords::open_mode = std::ios::app,
			keywords::auto_flush = true,
			keywords::file_name = "logs/sinks_file_%5N.log",
            keywords::rotation_size = 5 * 1024 * 1024,
            keywords::time_based_rotation = sinks::file::rotation_at_time_point(12, 0, 0)
        );

    logging::add_file_log
    (
        "logs/basic_usage.log",
        keywords::filter = expr::attr< severity_level >("Severity") >= warning,
        keywords::format = expr::stream
            << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d, %H:%M:%S.%f")
            << " [" << expr::format_date_time< attrs::timer::value_type >("Uptime", "%O:%M:%S")
            << "] [" << expr::format_named_scope("Scope", keywords::format = "%n (%f:%l)")
            << "] <" << expr::attr< severity_level >("Severity")
            << "> " << expr::message
    );

    pSink->set_formatter(expr::stream
        << expr::attr< unsigned int >("RecordID") // First an attribute "RecordID" is written to the log
        << " [" << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%d.%m.%Y %H:%M:%S.%f")
        << "] [" << expr::attr< severity_level >("Severity")
        << "] [" << expr::attr< boost::posix_time::time_duration >("Uptime")
        << "] [" // then this delimiter separates it from the rest of the line
        << expr::if_(expr::has_attr("Tag"))
           [
               expr::stream << expr::attr< std::string >("Tag") // then goes another attribute named "Tag"
                << "] [" // yet another delimiter
           ]
        << expr::format_named_scope("Scope", keywords::format = "%c", keywords::iteration = expr::reverse) << "] "
        << expr::smessage); // here goes the log record text

    pSink->set_filter(
		expr::attr< severity_level >("Severity").or_default(normal) >= warning
        || expr::begins_with(expr::attr< std::string >("Tag").or_default(std::string()), "IMPORTANT"));


    typedef sinks::asynchronous_sink<
        sinks::text_ostream_backend,
        sinks::unbounded_ordering_queue<
            logging::attribute_value_ordering< unsigned int, std::less< unsigned int > >
        >
    > sink_t;
    shared_ptr< sink_t > sink(new sink_t(
        boost::make_shared< sinks::text_ostream_backend >(),
        keywords::order = logging::make_attr_ordering("LineID", std::less< unsigned int >()),  /*< log record ordering predicate >*/
        keywords::ordering_window = boost::posix_time::seconds(1)                /*< latency of log record processing >*/
    ));

    typedef sinks::asynchronous_sink<
        sinks::text_ostream_backend,
        sinks::bounded_ordering_queue<
            logging::attribute_value_ordering< unsigned int, std::less< unsigned int > >,
            128,                        // queue no more than 128 log records
            sinks::block_on_overflow    // wait until records are processed
        >
    > sink_t;
    shared_ptr< sink_t > sink(new sink_t(
        boost::make_shared< sinks::text_ostream_backend >(),
        keywords::order = logging::make_attr_ordering("RecordID", std::less< unsigned int >())));

	typedef sinks::asynchronous_sink<
		sinks::text_ostream_backend,
		sinks::bounded_fifo_queue<     /*< log record queueing strategy >*/
			100,                        /*< record queue capacity >*/
			sinks::drop_on_overflow    /*< overflow handling policy >*/
		>
	> sink_t;

    std::ifstream settings("settings_file.txt");
    if (!settings.is_open())
    {
        std::cout << "Could not open settings.txt file" << std::endl;
    }
    logging::init_from_stream(settings);

	BOOST_LOG_FUNCTION();
	throw boost::enable_error_info(std::range_error("x must not be zero")) << logging::current_scope();