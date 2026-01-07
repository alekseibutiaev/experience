
#PYTHON_ADD_MODULE(policies policies.cpp)
ADD_EXECUTABLE(callpython callpython.cpp)
FILE(COPY pyprog.py DESTINATION .)
ADD_TEST(NAME 15-CallPython COMMAND callpython)
