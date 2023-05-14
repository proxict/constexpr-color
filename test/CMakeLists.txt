add_executable(unittests
    main.cpp
)

set_property(TARGET unittests PROPERTY CXX_STANDARD 11)
set_property(TARGET unittests PROPERTY CXX_STANDARD_REQUIRED TRUE)
set_property(TARGET unittests PROPERTY CXX_EXTENSIONS OFF)

target_compile_options(unittests PRIVATE
    -Wall
    -Wextra
    -pedantic
    -Wshadow
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wnull-dereference
    -Wformat=2
)

# Specify include directory for the interface rather than
# linking to it so that we get warnings despite the interface
# being defined as SYSTEM
target_include_directories(unittests
    PRIVATE ../include
)

