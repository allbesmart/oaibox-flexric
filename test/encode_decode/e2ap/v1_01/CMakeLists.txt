####################################
# E2AP Encoding and Decoding tests
###################################

if(E2AP_ENCODING STREQUAL "ASN")

####################
# E2AP ASN Encoding
####################

  add_executable(test_e2ap_encode_asn test_e2ap_encode_asn.c  )
  target_link_libraries(test_e2ap_encode_asn
                        PUBLIC 
                        e2_agent
                        $<TARGET_OBJECTS:e2ap_ie_obj>
                        )
  target_compile_options(test_e2ap_encode_asn  PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter)
  target_compile_definitions(test_e2ap_encode_asn PRIVATE ${E2AP_VERSION})

  add_executable(test_e2ap_enc_dec_asn test_e2ap_enc_dec_asn.c)
  target_link_libraries(test_e2ap_enc_dec_asn
                        PUBLIC 
                        e2_agent
                        $<TARGET_OBJECTS:e2ap_ie_obj>
                        )

  target_compile_options(test_e2ap_enc_dec_asn PRIVATE -Wno-missing-field-initializers -Wno-unused-parameter)
  target_compile_definitions(test_e2ap_enc_dec_asn PRIVATE ${E2AP_VERSION})

  target_include_directories(test_e2ap_encode_asn  PRIVATE "../../../../src/lib/e2ap/v1_01/ie/asn/")
  target_include_directories(test_e2ap_enc_dec_asn PRIVATE "../../../../src/lib/e2ap/v1_01/ie/asn/")
  target_include_directories(test_e2ap_enc_dec_asn PRIVATE "../../../src/lib/ap/ie/asn/")

  #####
  ### CTest 
  ####
  enable_testing()
  add_test(Unit_test_e2ap_v1 test_e2ap_encode_asn)


###########################
# E2AP Flatbuffers Encoding
###########################

elseif(E2AP_ENCODING STREQUAL "FLATBUFFERS")

  add_executable(test_e2ap_enc_dec_fb test_e2ap_enc_dec_fb.c)

  target_link_libraries(test_e2ap_enc_dec_fb
                      PUBLIC 
                      e2_agent
                      ${FlatCC}
                      )
  target_compile_definitions(test_e2ap_enc_dec_fb  PRIVATE ${E2AP_ENCODING})

else()
  message(FATAL_ERROR "Unknown E2AP encoding type")
endif()


