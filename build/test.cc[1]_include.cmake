if(EXISTS "/home/lixhappy/codes/cpp/zachet/build/test.cc[1]_tests.cmake")
  include("/home/lixhappy/codes/cpp/zachet/build/test.cc[1]_tests.cmake")
else()
  add_test(test.cc_NOT_BUILT test.cc_NOT_BUILT)
endif()