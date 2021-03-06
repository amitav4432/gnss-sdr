/*
 * SPDX-FileCopyrightText: (c) 2003, 2004 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * SPDX-License-Identifier: BSD-1-Clause
 * Generated by asn1c-0.9.22 (http://lionet.info/asn1c)
 * From ASN.1 module "RRLP-Components"
 *     found in "../rrlp-components.asn"
 */

#ifndef _LocationInfo_H
#define _LocationInfo_H

#include <asn_application.h>

/* Including external dependencies */
#include "Ext-GeographicalInformation.h"
#include "FixType.h"
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /* LocationInfo */
    typedef struct LocationInfo
    {
        long refFrame;
        long *gpsTOW /* OPTIONAL */;
        FixType_t fixType;
        Ext_GeographicalInformation_t posEstimate;

        /* Context for parsing across buffer boundaries */
        asn_struct_ctx_t _asn_ctx;
    } LocationInfo_t;

    /* Implementation */
    extern asn_TYPE_descriptor_t asn_DEF_LocationInfo;

#ifdef __cplusplus
}
#endif

#endif /* _LocationInfo_H_ */
#include <asn_internal.h>
