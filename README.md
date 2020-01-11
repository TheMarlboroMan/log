# Simple logging library for C++.

A basic log to file.

The log allows for the usual levels of input, but
can be cut at any level to produce smaller files. It also has locking
capabilities for multithreading and date/time formats.

# How does it work:

- Choose the kind of log you want to use (to screen, void, to file...).
- Instance it.
- Use the "sentries" to log. Sentries are instanced either by
	- log::lock(logger_instance, level) //With locking capabiities for
		multithreaded application.
	- log::log(logger_instance, level)
- Sentries are used as if they were streams (log::lock(logger, lvl::info)<<"Hello"<<std::endl;

# What is this level mask thing?

It allows you to filter out certain log levels. Check the examples.

# Can´t get this to work on mingw32:


