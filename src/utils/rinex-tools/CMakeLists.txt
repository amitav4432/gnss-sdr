# Copyright (C) 2012-2020  (see AUTHORS file for a list of contributors)
#
# GNSS-SDR is a software-defined Global Navigation Satellite Systems receiver
#
# This file is part of GNSS-SDR.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

if("${ARMADILLO_VERSION_STRING}" VERSION_GREATER "9.800" OR (NOT ARMADILLO_FOUND) OR ENABLE_OWN_ARMADILLO)  # requires back(), introduced in Armadillo 9.800
    message(STATUS "The obsdiff utility tool will be built when doing '${CMAKE_MAKE_PROGRAM_PRETTY_NAME}'")
    find_package(GPSTK QUIET)
    if(NOT GPSTK_FOUND OR ENABLE_OWN_GPSTK)
        include(GNUInstallDirs)
        set(GPSTK_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/../../../thirdparty/gpstk-${GNSSSDR_GPSTK_LOCAL_VERSION}/install/${CMAKE_INSTALL_LIBDIR}/${CMAKE_FIND_LIBRARY_PREFIXES}gpstk${CMAKE_SHARED_LIBRARY_SUFFIX})
        set(GPSTK_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../thirdparty/gpstk-${GNSSSDR_GPSTK_LOCAL_VERSION}/install/include)
    endif()

    set(obsdiff_HEADERS obsdiff_flags.h)
    source_group(Headers FILES ${obsdiff_HEADERS})

    add_executable(obsdiff ${CMAKE_CURRENT_SOURCE_DIR}/obsdiff.cc ${obsdiff_HEADERS})
    target_include_directories(obsdiff PUBLIC ${CMAKE_SOURCE_DIR}/src/tests/common-files)
    set_property(TARGET obsdiff PROPERTY CXX_STANDARD 14)  # Required by GPSTk v3.0.0
    # Do not show warnings raised by GPSTk v3.0.0
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(obsdiff
            PUBLIC
                -Wno-deprecated -Wno-unused-parameter -Wno-sign-compare -Wno-reorder -Wno-deprecated-copy -Wno-extra -Wno-unused-but-set-variable -Wno-unknown-pragmas
        )
    endif()
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(obsdiff
            PUBLIC
                -Wno-deprecated -Wno-unused-parameter -Wno-sign-compare -Wno-reorder
        )
    endif()

    if(NOT ARMADILLO_FOUND OR ENABLE_OWN_ARMADILLO)
        add_dependencies(obsdiff armadillo-${armadillo_RELEASE})
    endif()
    if(NOT GFLAGS_FOUND)
        add_dependencies(obsdiff gflags-${GNSSSDR_GFLAGS_LOCAL_VERSION})
    endif()
    if(NOT GPSTK_FOUND OR ENABLE_OWN_GPSTK)
        add_dependencies(obsdiff gpstk-${GNSSSDR_GPSTK_LOCAL_VERSION})
    endif()
    if(NOT MATIO_FOUND OR MATIO_VERSION_STRING VERSION_LESS ${GNSSSDR_MATIO_MIN_VERSION})
        add_dependencies(obsdiff matio-${GNSSSDR_MATIO_LOCAL_VERSION})
    endif()

    target_link_libraries(obsdiff
        PUBLIC
            Armadillo::armadillo
            Threads::Threads
            Gflags::gflags
            Matio::matio
            ${GPSTK_LIBRARY}
    )

    target_include_directories(obsdiff
        PUBLIC
            ${GPSTK_INCLUDE_DIR}/gpstk
            ${GPSTK_INCLUDE_DIR}
    )

    add_custom_command(TARGET obsdiff POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:obsdiff>
        ${CMAKE_SOURCE_DIR}/install/$<TARGET_FILE_NAME:obsdiff>
    )

    install(TARGETS obsdiff
        RUNTIME DESTINATION bin
        COMPONENT "obsdiff"
    )
else()
    message(STATUS "The Armadillo library version found (${ARMADILLO_VERSION_STRING}) is older than 9.800.")
    message(STATUS " The obsdiff utility tool will not be built.")
    message(STATUS " You could build it by setting -DENABLE_OWN_ARMADILLO=ON")
endif()
