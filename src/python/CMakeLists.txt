PYTHON_ADD_MODULE(sokoban_boost sokoban_boost.cc)
FILE(COPY test.py DESTINATION .)
ADD_TEST(NAME Pendulum-Driver-test COMMAND ${PYTHON_EXECUTABLE} test.py)