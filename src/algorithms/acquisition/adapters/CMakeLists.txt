# Copyright (C) 2012-2020  (see AUTHORS file for a list of contributors)
#
# GNSS-SDR is a software-defined Global Navigation Satellite Systems receiver
#
# This file is part of GNSS-SDR.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#


set(ACQ_ADAPTER_SOURCES
    gps_l1_ca_pcps_acquisition.cc
    gps_l1_ca_pcps_assisted_acquisition.cc
    gps_l1_ca_pcps_acquisition_fine_doppler.cc
    gps_l1_ca_pcps_tong_acquisition.cc
    gps_l1_ca_pcps_quicksync_acquisition.cc
    gps_l2_m_pcps_acquisition.cc
    gps_l5i_pcps_acquisition.cc
    galileo_e1_pcps_ambiguous_acquisition.cc
    galileo_e1_pcps_cccwsr_ambiguous_acquisition.cc
    galileo_e1_pcps_quicksync_ambiguous_acquisition.cc
    galileo_e1_pcps_tong_ambiguous_acquisition.cc
    galileo_e1_pcps_8ms_ambiguous_acquisition.cc
    galileo_e5a_noncoherent_iq_acquisition_caf.cc
    galileo_e5a_pcps_acquisition.cc
    glonass_l1_ca_pcps_acquisition.cc
    glonass_l2_ca_pcps_acquisition.cc
    beidou_b1i_pcps_acquisition.cc
    beidou_b3i_pcps_acquisition.cc
)

set(ACQ_ADAPTER_HEADERS
    gps_l1_ca_pcps_acquisition.h
    gps_l1_ca_pcps_assisted_acquisition.h
    gps_l1_ca_pcps_acquisition_fine_doppler.h
    gps_l1_ca_pcps_tong_acquisition.h
    gps_l1_ca_pcps_quicksync_acquisition.h
    gps_l2_m_pcps_acquisition.h
    gps_l5i_pcps_acquisition.h
    galileo_e1_pcps_ambiguous_acquisition.h
    galileo_e1_pcps_cccwsr_ambiguous_acquisition.h
    galileo_e1_pcps_quicksync_ambiguous_acquisition.h
    galileo_e1_pcps_tong_ambiguous_acquisition.h
    galileo_e1_pcps_8ms_ambiguous_acquisition.h
    galileo_e5a_noncoherent_iq_acquisition_caf.h
    galileo_e5a_pcps_acquisition.h
    glonass_l1_ca_pcps_acquisition.h
    glonass_l2_ca_pcps_acquisition.h
    beidou_b1i_pcps_acquisition.h
    beidou_b3i_pcps_acquisition.h
)

if(ENABLE_FPGA)
    set(ACQ_ADAPTER_SOURCES ${ACQ_ADAPTER_SOURCES}
        gps_l1_ca_pcps_acquisition_fpga.cc
        gps_l2_m_pcps_acquisition_fpga.cc
        galileo_e1_pcps_ambiguous_acquisition_fpga.cc
        galileo_e5a_pcps_acquisition_fpga.cc
        gps_l5i_pcps_acquisition_fpga.cc
    )
    set(ACQ_ADAPTER_HEADERS ${ACQ_ADAPTER_HEADERS}
        gps_l1_ca_pcps_acquisition_fpga.h
        gps_l2_m_pcps_acquisition_fpga.h
        galileo_e1_pcps_ambiguous_acquisition_fpga.h
        galileo_e5a_pcps_acquisition_fpga.h
        gps_l5i_pcps_acquisition_fpga.h
    )
endif()

if(ENABLE_OPENCL)
    set(ACQ_ADAPTER_SOURCES
        ${ACQ_ADAPTER_SOURCES}
        gps_l1_ca_pcps_opencl_acquisition.cc
    )
    set(ACQ_ADAPTER_HEADERS ${ACQ_ADAPTER_HEADERS}
        gps_l1_ca_pcps_opencl_acquisition.h
    )
endif()

list(SORT ACQ_ADAPTER_HEADERS)
list(SORT ACQ_ADAPTER_SOURCES)

source_group(Headers FILES ${ACQ_ADAPTER_HEADERS})

add_library(acquisition_adapters ${ACQ_ADAPTER_SOURCES} ${ACQ_ADAPTER_HEADERS})

target_link_libraries(acquisition_adapters
    PUBLIC
        algorithms_libs
        acquisition_gr_blocks
        acquisition_libs
        channel_libs
        core_system_parameters
        Gnuradio::blocks
    PRIVATE
        gnss_sdr_flags
        Boost::headers
        Gflags::gflags
        Glog::glog
        Gnuradio::fft
)

if(ENABLE_FPGA)
    target_link_libraries(acquisition_adapters
        PRIVATE
            Volk::volk
            Volkgnsssdr::volkgnsssdr
    )
endif()

target_include_directories(acquisition_adapters
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src/core/interfaces
)

if(ENABLE_CLANG_TIDY)
    if(CLANG_TIDY_EXE)
        set_target_properties(acquisition_adapters
            PROPERTIES
                CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
        )
    endif()
endif()

set_property(TARGET acquisition_adapters
    APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
