
PYTHON_ADD_MODULE(_mymodule mymodule.cpp)
ADD_EXECUTABLE(myembedding mymodule.cpp embedding.cpp)
TARGET_LINK_LIBRARIES(myembedding ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
FILE(COPY embedding.py DESTINATION .)
ADD_TEST(NAME 14-MyEmbedding COMMAND myembedding)
