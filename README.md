Poros Binary
============

The command line interface for the [Poros](https://github.com/dlasalle/poros)
library.

Requirements
------------

To compile Poros you will need `CMake` >= 2.8 and a C++ compiler supporting
`c++14`.

The `configure` script is currently written in `bash`, but `cmake` can be
invoked directly to build the library.


Building
--------

To just build the dynamic library execute:

```
$ ./configure && make
```

and `build/<os-arch>/bin/poros` will be built.


Running
-------

To partition a graph into five parts with Poros:

```
$ ./poros example.graph 5
```
