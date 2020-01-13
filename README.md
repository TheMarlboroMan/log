# Simple logging library for C++.

## What are all these branches?

Ignore them all. Just use master, really. Classic was supposed to be the one that was in the old libdansdl2, not-so-classic was supposed to be an intermediate state and master is supposed to be a refactor. Just go with master.

## How does it work?

- Choose the kind of log you want to use (to an output stream, nowhere, 
  to file...).
- Instance it.
- Use the "sentries" to log. Sentries are instanced either by
	- lm::lock(logger_instance, level) //With locking capabiities for
	  multithreaded applications.
	- lm::log(logger_instance, level)
- Sentries are used as if they were streams (lm::lock(logger, lg::lvl::info)<<"Hello"<<std::endl;

## What is this level mask thing?

It allows you to filter out certain log levels. Check the example in mask.cpp.

## What's with the namespace? Why is it not log?

Because including cmath and this library at the same time causes a clash between the logarithm functions (declared in the global namespace) and the log namespace.

We could use a nested namespace (something like lg::log) and then force the client code to either prefix or do "using lg" or we can just use a different namespace and pray that no more global functions are introduced. Either case, it is a shame since short, snappy and memorable namespaces for logging functionalities are pretty much limited to "log". Weird as it sounds, we went with lm for "Log module" since it was short and keys are close to each other on a QWERTY keyboard.
