cmake_minimum_required(VERSION 3.8)
project(bezpieczenstwo6)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_system -lboost_thread -lgmp -lboost_timer -lboost_regex -lpthread")

find_package(Boost 1.65.1 COMPONENTS program_options REQUIRED)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

set(BSERVER_SOURCE_FILES bserver/bserver.cpp bserver/setup.cpp bserver/primes.cpp bserver/sign.cpp bserver/cryptutil.cpp)
set(BSERVER_HEADER_FILES bserver/setup.h stdafx.h bserver/primes.h bserver/sign.h bserver/cryptutil.h)
add_executable(bserver ${BSERVER_SOURCE_FILES} ${BSERVER_HEADER_FILES})
target_link_libraries(bserver LINK_PUBLIC ${Boost_LIBRARIES})

set(BCLIENT_SOURCE_FILES bclient/bclient.cpp)
set(BCLIENT_HEADER_FILES stdafx.h)
add_executable(bclient ${BCLIENT_SOURCE_FILES} ${BCLIENT_HEADER_FILES})
target_link_libraries(bclient LINK_PUBLIC ${Boost_LIBRARIES})

set(BVERIFY_SOURCE_FILES bverify/bverify.cpp bserver/cryptutil.cpp)
set(BVERIFY_HEADER_FILES stdafx.h bserver/cryptutil.h)
add_executable(bverify ${BVERIFY_SOURCE_FILES} ${BVERIFY_HEADER_FILES})
target_link_libraries(bverify LINK_PUBLIC ${Boost_LIBRARIES})