# GPMG (Generic Programming Must Go - C++ edition)
A C++11 imititation implementation of statically introspective allocators from Andrei Alexandrescu's talk, Generic Programming Must Go:

* Slides [here](http://dconf.org/2015/talks/alexandrescu.pdf).
* Video [here](https://www.youtube.com/watch?v=mCrVYYlFTrA).

The code is a rough approximation of the functionality provided by the code discussed on the talk's slideshow.
I do not recommend using any of these allocators in production as their functionality hasn't even been properly tested.
The intent of this project is not to build fool-proof allocators, but to be a proof-of-concept to see whether the very concept is even viable in C++.
This requires C++11.

## Requirements
* C++11 language compatible compiler
* CMake
* Doxygen for documentation generation

## Building
Setup the build directory and build files:

```shell
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=MINSIZEREL
```

You can now build the project and run the tests:

```shell
make -j4 all check
```

If you want to build the documentation and tests:
```shell
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=MINSIZEREL -DBUILD_DOCS=ON -DBUILD_TESTS=ON
make -j4 check doc
```

## License
Issued under the MIT license.
Please see [LICENSE.md](LICENSE.md).
