# CMake generated Testfile for 
# Source directory: C:/Users/godfr/Desktop/CS_179M_Repo/test
# Build directory: C:/Users/godfr/Desktop/CS_179M_Repo/build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(DeckwareTests "C:/Users/godfr/Desktop/CS_179M_Repo/build/test/Debug/DeckwareTests.exe")
  set_tests_properties(DeckwareTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/godfr/Desktop/CS_179M_Repo/test/CMakeLists.txt;16;add_test;C:/Users/godfr/Desktop/CS_179M_Repo/test/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(DeckwareTests "C:/Users/godfr/Desktop/CS_179M_Repo/build/test/Release/DeckwareTests.exe")
  set_tests_properties(DeckwareTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/godfr/Desktop/CS_179M_Repo/test/CMakeLists.txt;16;add_test;C:/Users/godfr/Desktop/CS_179M_Repo/test/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(DeckwareTests "C:/Users/godfr/Desktop/CS_179M_Repo/build/test/MinSizeRel/DeckwareTests.exe")
  set_tests_properties(DeckwareTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/godfr/Desktop/CS_179M_Repo/test/CMakeLists.txt;16;add_test;C:/Users/godfr/Desktop/CS_179M_Repo/test/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(DeckwareTests "C:/Users/godfr/Desktop/CS_179M_Repo/build/test/RelWithDebInfo/DeckwareTests.exe")
  set_tests_properties(DeckwareTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/godfr/Desktop/CS_179M_Repo/test/CMakeLists.txt;16;add_test;C:/Users/godfr/Desktop/CS_179M_Repo/test/CMakeLists.txt;0;")
else()
  add_test(DeckwareTests NOT_AVAILABLE)
endif()
