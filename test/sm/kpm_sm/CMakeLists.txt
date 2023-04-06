cmake_minimum_required(VERSION 3.15)

project (TEST_KPM_SM)
set(CMAKE_BUILD_TYPE Debug)
set (CMAKE_C_FLAGS "-Wall -Wextra --std=gnu11 -g -fno-omit-frame-pointer") 
set(SM_ENCODING_KPM "PLAIN" CACHE STRING "The SM encoding to use")
set_property(CACHE SM_ENCODING_KPM PROPERTY STRINGS "PLAIN" "ASN" "FLATBUFFERS")
message(STATUS "Selected SM_ENCODING_KPM: ${SM_ENCODING_KPM} for tests")

option(CODE_COVERAGE "Code coverage" ON)
if(CODE_COVERAGE)
  add_compile_options("-fprofile-arcs;-ftest-coverage")
  add_link_options("-lgcov;-coverage")
  message(STATUS "Code Coverage ON. Example usage: lcov --capture --directory . --output-file coverage.info && genhtml coverage.info --output-directory out && cd out && firefox index.html")

  message(STATUS "Code Coverage ON. Example usage: lcov --capture --directory . --output-file coverage.info && genhtml coverage.info --output-directory out && cd out && firefox index.html")
  message(STATUS "To merge different coverages: lcov --add-tracefile coverage1.info -a coverage2.info ...coverageN -o merged.info")

endif()

if(SM_ENCODING_KPM STREQUAL "ASN")

  add_executable(test_kpm_sm 
                      main.c 
                      ../common/fill_ind_data.c
                      ../../../src/sm/rc_sm/test/fill_rnd_data_rc.c
                      ${asn_sources}
                      )
                        
  # XXX-IMPROVE: maybe we can avoid recompiling objects like asn_sources. 
  target_compile_options(test_kpm_sm PUBLIC "-DASN_DISABLE_OER_SUPPORT")
  target_compile_options(test_kpm_sm PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter)
  target_include_directories(test_kpm_sm PRIVATE "../../../src/sm/kpm_sm_v03.00/ie/asn")
else()
  message(FATAL_ERROR "unsupported encoding type")
endif()

target_compile_definitions(test_kpm_sm PUBLIC ${SM_ENCODING_KPM})
target_link_libraries(test_kpm_sm PUBLIC 
                                kpm_sm
                                -pthread)
                                
target_link_libraries(test_kpm_sm PUBLIC m)

enable_testing()
add_test(Unit_test_KPM test_kpm_sm)
