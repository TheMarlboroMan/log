# Simple logging class for C++.

A basic log to file.

The log allows for four levels (all, info, warning, error) of input, but
can be cut at any level to produce smaller files. It also has locking
capabilities for multithreading and date/time formats.

# TODO.

Turn this into a library so we don't have to link againts a .o file.
