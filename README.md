# Simple logging library for C++.

## What are all these branches?

Ignore them all. Just use master, really. Classic was supposed to be the one that was in the old libdansdl2, not-so-classic was supposed to be an intermediate state and master is supposed to be a refactor. Just go with master.

## How does it work?

### Method a, using sentries.

- Choose the kind of log you want to use (to an output stream, nowhere, 
  to file...).
- Instance it.
- Use the "sentries" to log. Sentries are instanced either by
	- lm::lock(logger_instance, level) //With locking capabiities for
	  multithreaded applications.
	- lm::log(logger_instance, level)
- Sentries are used as if they were streams (lm::lock(logger, lg::info())<<"Hello"<<endl

#### Advantages:
- access to the thread lock thing, even if it is something that can (and should, actually) be implemented application wise.
- simple, unified interface that guarantees that all logs must start with date and log level.

#### Disadvantages:

- the << operator for custom types must be writen as taking log_sentry&& and returning log_sentry&
- if the sentry is taken by name, the << operator must also be written as taking log_sentry&

### Method b, directly using the << operator.

- Build the library with -DOPEN_LOG_OPERATORS
- Choose the kind of log you want to use (to an output stream, nowhere, 
  to file...).
- Instance it.
- Loggers are used as if they were streams logger<<lm::info()<<"Hello"<<std::endl;

#### Advantages:

- the << operator for custom types can be defined as taking and returning &logger.
- disposes of the need to add the sentry header.

#### Disadvantages:

- this approach does not enforce that each log line starts with date and log level, which in combination with flags can result in subtle bugs.
- must be build with a particular flag.

## What is this level mask thing?

It allows you to filter out certain log levels. Check the example in mask.cpp.

## What's with the namespace? Why is it not log?

Because including cmath and this library at the same time causes a clash between the logarithm functions (declared in the global namespace) and the log namespace.

We could use a nested namespace (something like lg::log) and then force the client code to either prefix or do "using lg" or we can just use a different namespace and pray that no more global functions are introduced. Either case, it is a shame since short, snappy and memorable namespaces for logging functionalities are pretty much limited to "log". Weird as it sounds, we went with lm for "Log module" since it was short and keys are close to each other on a QWERTY keyboard.
