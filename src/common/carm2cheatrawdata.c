#include "carm2cheatrawdata.h"

#include "carmcheatrawdata.h"

#include <stdint.h>

static const uint32_t cheatTable_CARMA2_HW_fileOffset = 0x0018eb70;
static const uint8_t cheatTable_CARMA2_HW_rawData[] = {
    0x5d, 0xe7, 0x1e, 0xa1, 0xdd, 0xed, 0x05, 0xf8, 0x80, 0x15, 0x44, 0x00, 0x5d, 0xe7, 0x1e, 0xa1,
    0x8c, 0xa2, 0x8d, 0x39, 0xd4, 0x9d, 0x33, 0x44, 0x80, 0x15, 0x44, 0x00, 0xb9, 0x78, 0x4e, 0x56,
    0xf3, 0x10, 0xc5, 0x7d, 0x37, 0x15, 0xc6, 0x65, 0x50, 0x43, 0x44, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x55, 0x4f, 0x9e, 0x30, 0xaf, 0xda, 0xc7, 0xec, 0xc0, 0x15, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x48, 0xe1, 0xcb, 0x1b, 0xb1, 0x61, 0x01, 0x04, 0x80, 0x2e, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x25, 0x77, 0x5e, 0x1d, 0x70, 0x2a, 0xd6, 0x0e, 0x80, 0x2e, 0x44, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x63, 0x50, 0xc6, 0x22, 0xc8, 0x1b, 0x33, 0xe4, 0x80, 0x2e, 0x44, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x8a, 0xd2, 0x37, 0x1a, 0xe4, 0x87, 0x97, 0x13, 0x80, 0x2e, 0x44, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x60, 0xa3, 0xcb, 0x1d, 0xa1, 0xbf, 0x38, 0x1e, 0x80, 0x2e, 0x44, 0x00, 0x04, 0x00, 0x00, 0x00,
    0xfb, 0x9a, 0xc9, 0x24, 0x52, 0xf9, 0x08, 0xd9, 0x80, 0x2e, 0x44, 0x00, 0x05, 0x00, 0x00, 0x00,
    0xd4, 0x1b, 0x0c, 0x20, 0x91, 0xe3, 0x3d, 0x66, 0x80, 0x2e, 0x44, 0x00, 0x06, 0x00, 0x00, 0x00,
    0x6b, 0x2e, 0x2a, 0x25, 0x47, 0xd6, 0x04, 0x33, 0x80, 0x2e, 0x44, 0x00, 0x07, 0x00, 0x00, 0x00,
    0x5c, 0x55, 0x8f, 0x21, 0x58, 0xac, 0xd3, 0xe2, 0x80, 0x2e, 0x44, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x5b, 0x65, 0xc7, 0x1f, 0x58, 0x92, 0x2f, 0xa1, 0x80, 0x2e, 0x44, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x91, 0x68, 0x2e, 0x2b, 0xc2, 0x11, 0xd6, 0x4b, 0x80, 0x2e, 0x44, 0x00, 0x0a, 0x00, 0x00, 0x00,
    0x4a, 0xb3, 0xb8, 0x2d, 0x58, 0xac, 0x18, 0x44, 0x80, 0x2e, 0x44, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0x7e, 0x46, 0x01, 0x30, 0x44, 0xf9, 0x23, 0xb3, 0x80, 0x2e, 0x44, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0xda, 0x8e, 0x96, 0x23, 0x6e, 0x24, 0x59, 0x92, 0x80, 0x2e, 0x44, 0x00, 0x0d, 0x00, 0x00, 0x00,
    0x55, 0xaa, 0x3b, 0x1f, 0xa9, 0x05, 0xc5, 0x56, 0x80, 0x2e, 0x44, 0x00, 0x0f, 0x00, 0x00, 0x00,
    0x58, 0x25, 0x4a, 0x21, 0x21, 0xf4, 0xcb, 0x56, 0x80, 0x2e, 0x44, 0x00, 0x10, 0x00, 0x00, 0x00,
    0x9a, 0xe6, 0x3a, 0x37, 0x8f, 0x99, 0x8c, 0xef, 0x80, 0x2e, 0x44, 0x00, 0x11, 0x00, 0x00, 0x00,
    0x75, 0xbd, 0x7e, 0x32, 0x3e, 0x9e, 0x5a, 0x60, 0x80, 0x2e, 0x44, 0x00, 0x12, 0x00, 0x00, 0x00,
    0x84, 0x03, 0x0c, 0x35, 0xd2, 0x76, 0xe5, 0x73, 0x80, 0x2e, 0x44, 0x00, 0x13, 0x00, 0x00, 0x00,
    0x24, 0x3c, 0xf0, 0x17, 0x0c, 0x65, 0x71, 0x00, 0x80, 0x2e, 0x44, 0x00, 0x14, 0x00, 0x00, 0x00,
    0x21, 0xca, 0xae, 0x32, 0x68, 0x31, 0x9d, 0x68, 0x80, 0x2e, 0x44, 0x00, 0x15, 0x00, 0x00, 0x00,
    0xaa, 0x41, 0x18, 0x19, 0x70, 0xd7, 0xfb, 0x10, 0x80, 0x2e, 0x44, 0x00, 0x16, 0x00, 0x00, 0x00,
    0x96, 0x68, 0x02, 0x26, 0xa9, 0x5f, 0x0e, 0x63, 0x80, 0x2e, 0x44, 0x00, 0x17, 0x00, 0x00, 0x00,
    0x1b, 0xca, 0x40, 0x24, 0x4c, 0x30, 0x68, 0x2e, 0x80, 0x2e, 0x44, 0x00, 0x18, 0x00, 0x00, 0x00,
    0x1b, 0x1b, 0xa1, 0x37, 0x7d, 0xb8, 0x20, 0x68, 0x80, 0x2e, 0x44, 0x00, 0x19, 0x00, 0x00, 0x00,
    0x09, 0xa5, 0x2e, 0x2f, 0xb7, 0x04, 0xb8, 0x6b, 0x80, 0x2e, 0x44, 0x00, 0x1a, 0x00, 0x00, 0x00,
    0xf1, 0x22, 0xf5, 0x28, 0xc0, 0xf8, 0x52, 0x2f, 0x80, 0x2e, 0x44, 0x00, 0x1b, 0x00, 0x00, 0x00,
    0x53, 0x55, 0xc1, 0x26, 0x54, 0xa3, 0x19, 0xba, 0x80, 0x2e, 0x44, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x2b, 0xb5, 0x64, 0x39, 0x48, 0x46, 0xc9, 0x40, 0x80, 0x2e, 0x44, 0x00, 0x21, 0x00, 0x00, 0x00,
    0x3a, 0x12, 0xbf, 0x18, 0xa9, 0xc0, 0x80, 0x00, 0x80, 0x2e, 0x44, 0x00, 0x22, 0x00, 0x00, 0x00,
    0x13, 0x9e, 0x43, 0x2a, 0xb0, 0xc0, 0x56, 0x33, 0x80, 0x2e, 0x44, 0x00, 0x23, 0x00, 0x00, 0x00,
    0x02, 0x99, 0x76, 0x28, 0xd1, 0xd8, 0xa5, 0x50, 0x80, 0x2e, 0x44, 0x00, 0x24, 0x00, 0x00, 0x00,
    0xe5, 0xa4, 0x5a, 0x2d, 0x82, 0x9d, 0x7f, 0x42, 0x80, 0x2e, 0x44, 0x00, 0x25, 0x00, 0x00, 0x00,
    0x54, 0xb3, 0x73, 0x1e, 0x19, 0x16, 0x74, 0x17, 0x80, 0x2e, 0x44, 0x00, 0x26, 0x00, 0x00, 0x00,
    0x7c, 0x0a, 0xac, 0x1c, 0xb1, 0x1b, 0x46, 0x0a, 0x80, 0x2e, 0x44, 0x00, 0x27, 0x00, 0x00, 0x00,
    0x3a, 0x61, 0x3c, 0x1e, 0x2c, 0xe9, 0x56, 0x6b, 0x80, 0x2e, 0x44, 0x00, 0x28, 0x00, 0x00, 0x00,
    0x19, 0x35, 0x4c, 0x2f, 0xf8, 0x21, 0x23, 0x08, 0x80, 0x2e, 0x44, 0x00, 0x29, 0x00, 0x00, 0x00,
    0x61, 0xd2, 0xf0, 0x21, 0xb9, 0x90, 0xe0, 0xda, 0x80, 0x2e, 0x44, 0x00, 0x2a, 0x00, 0x00, 0x00,
    0x44, 0x73, 0x72, 0x1c, 0x91, 0x5c, 0xf6, 0x78, 0x80, 0x2e, 0x44, 0x00, 0x2b, 0x00, 0x00, 0x00,
    0x45, 0x48, 0x57, 0x2f, 0x28, 0x14, 0xff, 0x75, 0x80, 0x2e, 0x44, 0x00, 0x2c, 0x00, 0x00, 0x00,
    0xe3, 0x01, 0x06, 0x1f, 0xc8, 0xc4, 0x55, 0x94, 0x80, 0x2e, 0x44, 0x00, 0x2d, 0x00, 0x00, 0x00,
    0xf3, 0x9f, 0x21, 0x26, 0x46, 0x8b, 0xfd, 0xfd, 0x80, 0x2e, 0x44, 0x00, 0x2f, 0x00, 0x00, 0x00,
    0x31, 0xbb, 0xaf, 0x26, 0x40, 0x5e, 0x27, 0xe3, 0x80, 0x2e, 0x44, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x46, 0x55, 0x20, 0x25, 0x4c, 0xa1, 0x86, 0xcf, 0x80, 0x2e, 0x44, 0x00, 0x31, 0x00, 0x00, 0x00,
    0x5b, 0x8e, 0x0a, 0x1a, 0x40, 0x53, 0x03, 0x02, 0x80, 0x2e, 0x44, 0x00, 0x33, 0x00, 0x00, 0x00,
    0x25, 0xa9, 0xde, 0x1b, 0x0c, 0xfd, 0x98, 0x5d, 0x80, 0x2e, 0x44, 0x00, 0x34, 0x00, 0x00, 0x00,
    0xa9, 0xd2, 0x4d, 0x2d, 0x96, 0xa6, 0x1b, 0xf0, 0x80, 0x2e, 0x44, 0x00, 0x35, 0x00, 0x00, 0x00,
    0x05, 0x75, 0x7a, 0x2e, 0xf6, 0xe4, 0x20, 0x89, 0x80, 0x2e, 0x44, 0x00, 0x36, 0x00, 0x00, 0x00,
    0x40, 0x09, 0x29, 0x17, 0x01, 0x18, 0x90, 0x00, 0x80, 0x2e, 0x44, 0x00, 0x37, 0x00, 0x00, 0x00,
    0x9c, 0x7a, 0x4e, 0x1d, 0x50, 0x26, 0x0e, 0x03, 0x80, 0x2e, 0x44, 0x00, 0x38, 0x00, 0x00, 0x00,
    0x4a, 0xd6, 0x79, 0x35, 0xc3, 0x34, 0x2e, 0x3d, 0x80, 0x2e, 0x44, 0x00, 0x39, 0x00, 0x00, 0x00,
    0x9c, 0xd4, 0xf4, 0x28, 0x48, 0x81, 0x41, 0xb3, 0x80, 0x2e, 0x44, 0x00, 0x3a, 0x00, 0x00, 0x00,
    0xc3, 0xa9, 0x6b, 0x1d, 0x49, 0x77, 0x01, 0x0e, 0x80, 0x2e, 0x44, 0x00, 0x3b, 0x00, 0x00, 0x00,
    0xab, 0x71, 0x09, 0x31, 0x02, 0x37, 0x97, 0xcb, 0x80, 0x2e, 0x44, 0x00, 0x3c, 0x00, 0x00, 0x00,
    0xeb, 0x1e, 0x45, 0x28, 0xcb, 0x63, 0xff, 0x30, 0x80, 0x2e, 0x44, 0x00, 0x3d, 0x00, 0x00, 0x00,
    0xba, 0xa5, 0xbf, 0x1e, 0xec, 0x34, 0xe0, 0x92, 0x80, 0x2e, 0x44, 0x00, 0x3e, 0x00, 0x00, 0x00,
    0x73, 0x97, 0x07, 0x27, 0x1c, 0x51, 0xef, 0xd1, 0x80, 0x2e, 0x44, 0x00, 0x3f, 0x00, 0x00, 0x00,
    0x2c, 0xe7, 0x8d, 0x38, 0xca, 0x8d, 0x7a, 0x04, 0x80, 0x2e, 0x44, 0x00, 0x40, 0x00, 0x00, 0x00,
    0xfc, 0xa9, 0x0d, 0x1a, 0x10, 0xe0, 0x80, 0x01, 0x80, 0x2e, 0x44, 0x00, 0x41, 0x00, 0x00, 0x00,
    0x0c, 0xa1, 0x75, 0x29, 0x5d, 0x5f, 0xd6, 0xef, 0x80, 0x2e, 0x44, 0x00, 0x42, 0x00, 0x00, 0x00,
    0xca, 0xc6, 0x5c, 0x1e, 0x91, 0x63, 0xb7, 0x17, 0x80, 0x2e, 0x44, 0x00, 0x43, 0x00, 0x00, 0x00,
    0x99, 0x6f, 0x0c, 0x25, 0xcc, 0x24, 0xda, 0xbd, 0x80, 0x2e, 0x44, 0x00, 0x44, 0x00, 0x00, 0x00,
    0x49, 0x0e, 0x95, 0x33, 0x8c, 0x73, 0x90, 0x28, 0x80, 0x2e, 0x44, 0x00, 0x45, 0x00, 0x00, 0x00,
    0x7a, 0x48, 0x5f, 0x4e, 0xb8, 0x35, 0xc6, 0x3d, 0x80, 0x2e, 0x44, 0x00, 0x46, 0x00, 0x00, 0x00,
    0x4c, 0x58, 0x15, 0x38, 0x6e, 0xc2, 0xbb, 0x91, 0x80, 0x2e, 0x44, 0x00, 0x47, 0x00, 0x00, 0x00,
    0xb2, 0x32, 0x97, 0x45, 0x10, 0xe0, 0x71, 0xb5, 0x80, 0x2e, 0x44, 0x00, 0x48, 0x00, 0x00, 0x00,
    0x03, 0x10, 0x87, 0x62, 0x84, 0x50, 0xb1, 0x79, 0x80, 0x2e, 0x44, 0x00, 0x49, 0x00, 0x00, 0x00,
    0xb4, 0xeb, 0x72, 0x2d, 0xca, 0xd3, 0xd4, 0x5f, 0x80, 0x2e, 0x44, 0x00, 0x4a, 0x00, 0x00, 0x00,
    0xaa, 0xe2, 0x3b, 0x2c, 0x9c, 0xeb, 0xe0, 0x90, 0x80, 0x2e, 0x44, 0x00, 0x4b, 0x00, 0x00, 0x00,
    0x8b, 0xe2, 0x2b, 0x2b, 0x7b, 0xeb, 0xe0, 0x30, 0x80, 0x2e, 0x44, 0x00, 0x4c, 0x00, 0x00, 0x00,
    0x9d, 0x08, 0xbe, 0x29, 0x96, 0xeb, 0x5c, 0x63, 0x80, 0x2e, 0x44, 0x00, 0x4d, 0x00, 0x00, 0x00,
    0x2d, 0x98, 0x97, 0x48, 0x99, 0xfa, 0xc4, 0x06, 0x80, 0x2e, 0x44, 0x00, 0x4e, 0x00, 0x00, 0x00,
    0x49, 0x0f, 0xd5, 0x44, 0x42, 0xdb, 0x0e, 0x01, 0x80, 0x2e, 0x44, 0x00, 0x4f, 0x00, 0x00, 0x00,
    0xe5, 0xfa, 0x3a, 0x40, 0xd2, 0xa7, 0x04, 0x01, 0x80, 0x2e, 0x44, 0x00, 0x50, 0x00, 0x00, 0x00,
    0x5e, 0x9e, 0xc1, 0x45, 0xf9, 0x2c, 0x1b, 0x01, 0x80, 0x2e, 0x44, 0x00, 0x51, 0x00, 0x00, 0x00,
    0xbd, 0x0e, 0x79, 0x2f, 0x6b, 0x7f, 0xd8, 0x2f, 0x80, 0x2e, 0x44, 0x00, 0x52, 0x00, 0x00, 0x00,
    0xc9, 0x60, 0x4f, 0x24, 0xa3, 0xfd, 0xf4, 0x31, 0x80, 0x2e, 0x44, 0x00, 0x53, 0x00, 0x00, 0x00,
    0xd3, 0x94, 0x07, 0x2b, 0xc9, 0x7d, 0x92, 0x12, 0x80, 0x2e, 0x44, 0x00, 0x54, 0x00, 0x00, 0x00,
    0x28, 0xb6, 0x44, 0x2a, 0xdb, 0x7e, 0x3e, 0x0c, 0x80, 0x2e, 0x44, 0x00, 0x55, 0x00, 0x00, 0x00,
    0x6d, 0xe4, 0x98, 0x29, 0x3e, 0xa6, 0x60, 0x13, 0x80, 0x2e, 0x44, 0x00, 0x56, 0x00, 0x00, 0x00,
    0x28, 0x87, 0x24, 0x23, 0x51, 0x9d, 0x4d, 0xc8, 0x80, 0x2e, 0x44, 0x00, 0x57, 0x00, 0x00, 0x00,
    0x22, 0x18, 0x9c, 0x28, 0xc3, 0x9f, 0x6e, 0x13, 0x80, 0x2e, 0x44, 0x00, 0x58, 0x00, 0x00, 0x00,
    0xd0, 0xb7, 0xab, 0x35, 0x7c, 0xa5, 0x8d, 0xa0, 0x80, 0x2e, 0x44, 0x00, 0x5a, 0x00, 0x00, 0x00,
    0x92, 0xdd, 0x1f, 0x1c, 0x0c, 0x06, 0xdd, 0x01, 0x80, 0x2e, 0x44, 0x00, 0x5b, 0x00, 0x00, 0x00,
    0xc1, 0x69, 0x30, 0x25, 0x6a, 0x79, 0x72, 0x49, 0x80, 0x2e, 0x44, 0x00, 0x5c, 0x00, 0x00, 0x00,
    0x73, 0x48, 0xca, 0x33, 0x24, 0x5b, 0x00, 0x3b, 0x80, 0x2e, 0x44, 0x00, 0x5d, 0x00, 0x00, 0x00,
    0xe5, 0xcd, 0x56, 0x1f, 0xae, 0x3a, 0x21, 0x8f, 0x80, 0x2e, 0x44, 0x00, 0x5e, 0x00, 0x00, 0x00,
    0x5b, 0x99, 0x84, 0x17, 0x89, 0xc3, 0x63, 0x01, 0x80, 0x2e, 0x44, 0x00, 0x60, 0x00, 0x00, 0x00,
    0xcb, 0xec, 0x03, 0x30, 0x6f, 0xf3, 0x74, 0x1d, 0x80, 0x2e, 0x44, 0x00, 0x61, 0x00, 0x00, 0x00,
    0x60, 0x4b, 0x05, 0x4b, 0xcb, 0x36, 0x67, 0x6b, 0x10, 0x4f, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static const CarmCheatTableItem carm2CheatTableItems[] = {
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 0),
        .cheat = "sblqhpsyngswyrzzynbdcpppjnwvzyedtvj",
        .description = "Edit mode (also for multiplayer)",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 1),
        .cheat = "lapmylovepump",
        .description = "Edit mode",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 2),
        .cheat = "iwishicouldflyrightuptothesky",
        .description = "Flight mode",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 3),
        .cheat = "smartbastard",
        .description = "Finish race",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 4),
        .cheat = "wetwet",
        .description = "Credit bonus",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 5),
        .cheat = "gluglug",
        .description = "Mega bonus",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 6),
        .cheat = "stickits",
        .description = "Pedestrians are stuck",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 7),
        .cheat = "megabum",
        .description = "Giant pedestrians",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 8),
        .cheat = "twatoff",
        .description = "Explosive pedestrians",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 9),
        .cheat = "clintonco",
        .description = "Hot rod",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 10),
        .cheat = "fastbast",
        .description = "Fast pedestrians",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 11),
        .cheat = "supacocks",
        .description = "Invincibility",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 12),
        .cheat = "tingting",
        .description = "Free repairs",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 13),
        .cheat = "mingming",
        .description = "Instant Repairs",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 14),
        .cheat = "stopsnatch",
        .description = "Toggle timer",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 15),
        .cheat = "watersport",
        .description = "Underwater capability",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 16),
        .cheat = "timmytitty",
        .description = "Time bonus",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 17),
        .cheat = "clangclang",
        .description = "Trashed bodywork",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 18),
        .cheat = "bluebalz",
        .description = "Frozen opponents",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 19),
        .cheat = "bluepigz",
        .description = "Frozen police",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 20),
        .cheat = "swiftyshifty",
        .description = "Turbo opponents",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 21),
        .cheat = "pigsmightfly",
        .description = "Turbo police",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 22),
        .cheat = "mooningminnie",
        .description = "lunar gravity",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 23),
        .cheat = "tilty",
        .description = "Pinball mode",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 24),
        .cheat = "stickytyres",
        .description = "Wall climbing",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 25),
        .cheat = "jigajig",
        .description = "Bouncy mode",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 26),
        .cheat = "mrwobbley",
        .description = "Jelly suspension",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 27),
        .cheat = "dotaction",
        .description = "Pedestrians on map",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 28),
        .cheat = "fryingtonight",
        .description = "Pedestrian electric ray",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 29),
        .cheat = "wotatwatami",
        .description = "Slippery tires",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 30),
        .cheat = "stuffitup",
        .description = "Damage magnifier",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 31),
        .cheat = "eyepopper",
        .description = "Instant handbrake",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 32),
        .cheat = "angelmolesters",
        .description = "Immortal pedestrians",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 33),
        .cheat = "whizz",
        .description = "Turbo",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 34),
        .cheat = "supawhizz",
        .description = "Mega-turbo",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 35),
        .cheat = "lemmingize",
        .description = "Disable pedestrian AI",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 36),
        .cheat = "takemetakeme",
        .description = "Suicidal pedestrians",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 37),
        .cheat = "pillpop",
        .description = "Five Recovery Vouchers",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 38),
        .cheat = "bigtwat",
        .description = "Solid granite car",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 39),
        .cheat = "duffride",
        .description = "Rock springs",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 40),
        .cheat = "bloodyhippy",
        .description = "Drug mode",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 41),
        .cheat = "rubberup",
        .description = "Gripomatic tires",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 42),
        .cheat = "goodhead",
        .description = "Pedestrians have stupid heads",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 43),
        .cheat = "stiffspasms",
        .description = "Mutant corpses",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 44),
        .cheat = "ledsleds",
        .description = "Jupiter gravity",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 45),
        .cheat = "easypeasy",
        .description = "Slow motion pedestrians",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 46),
        .cheat = "tinytoss",
        .description = "Mini-pedestrians",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 47),
        .cheat = "furkinell",
        .description = "Turbo Bastard Nutter Nitros",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 48),
        .cheat = "hotass",
        .description = "After burner",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 49),
        .cheat = "didedodi",
        .description = "Lay mines",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 50),
        .cheat = "liquidlunge",
        .description = "Oil slicks",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 51),
        .cheat = "skippypoos",
        .description = "Kangaroo on command",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 52),
        .cheat = "zazaz",
        .description = "Pedestrian annihilator",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 53),
        .cheat = "powpow",
        .description = "Repulse opponents",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 54),
        .cheat = "oohmessymess",
        .description = "Dismemberfest",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 55),
        .cheat = "xrayspeks",
        .description = "Ethereal pedestrians",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 56),
        .cheat = "getdown",
        .description = "Grooving pedestrians",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 57),
        .cheat = "mrmainwaring",
        .description = "Panicked pedestrians",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 58),
        .cheat = "fartsuits",
        .description = "Helium pedestrians",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 59),
        .cheat = "largeone",
        .description = "Angry pedestrians",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 60),
        .cheat = "hippotart",
        .description = "Fat pedestrians",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 61),
        .cheat = "bloodyartists",
        .description = "Stick insects",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 62),
        .cheat = "cowcow",
        .description = "Pedestrian repulsificator",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 63),
        .cheat = "osostrong",
        .description = "Extra armor",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 64),
        .cheat = "osofast",
        .description = "Extra power",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 65),
        .cheat = "osonasty",
        .description = "Extra offensive",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 66),
        .cheat = "osoversatile",
        .description = "Extra everything",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 67),
        .cheat = "osostrongsostrong",
        .description = "Double extra armor",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 68),
        .cheat = "osofastsofast",
        .description = "Double extra power",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 69),
        .cheat = "osonastysonasty",
        .description = "Double extra offensive",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 70),
        .cheat = "osoversatilesoversatile",
        .description = "Double extra everything",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 71),
        .cheat = "stringvest",
        .description = "Maximum armour",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 72),
        .cheat = "vastnesses",
        .description = "Maximum power",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 73),
        .cheat = "fistnesses",
        .description = "Maximum offensive",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 74),
        .cheat = "skegnesses",
        .description = "Maximum everything",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 75),
        .cheat = "thatsalotofarmour",
        .description = "Extra armor slot",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 76),
        .cheat = "thatsalotofpower",
        .description = "Extra power slot",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 77),
        .cheat = "thatsalotofoffal",
        .description = "Extra offensive slot",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 78),
        .cheat = "thatsalotofslots",
        .description = "Extra slots all around",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 79),
        .cheat = "strongbones",
        .description = "Bonus armor slots",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 80),
        .cheat = "fastbones",
        .description = "Bonus power slots",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 81),
        .cheat = "nastybones",
        .description = "Bonus offensive slots",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 82),
        .cheat = "loadsabones",
        .description = "Bonus slots all around",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 83),
        .cheat = "randypandy",
        .description = "Random APO",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 84),
        .cheat = "randypot",
        .description = "Random APO potential",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 85),
        .cheat = "randyquaid",
        .description = "Random good APO",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 86),
        .cheat = "eveningoccifer",
        .description = "Drunk driving",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 87),
        .cheat = "fryfry",
        .description = "Pedestrian flamethrower",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 88),
        .cheat = "ineedapill",
        .description = "Pedestrian valium",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 89),
        .cheat = "oypowerupno",
        .description = "No power-ups",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 90),
        .cheat = "bigdangle",
        .description = "Mutant tail",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 91),
        .cheat = "bonbon",
        .description = "Slaughter mortar",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 92),
        .cheat = "gotoinfrared",
        .description = "Cloaking device",
    },
    {
        .rawData = cheatTable_CARMA2_HW_rawData + (16 * 93),
        .cheat = "ezpzkballxxewazon",
        .description = "Steel Gonad O’ Death",
    },
};

static const CarmCheatTable carm2CheatTable = {
    .fileOffset = cheatTable_CARMA2_HW_fileOffset,
    .items = carm2CheatTableItems,
    .nbItems = sizeof(carm2CheatTableItems) / sizeof(carm2CheatTableItems[0]),
};

// file location: 0x43055
// hash offset: 0x2 (code1)
// hash offset: 0xb (code1)
static const uint32_t cheatFragmentAllCars_fileOffset = 0x00043055;
static const int cheatFragmentAllCars_code1Offset = 0x2;
static const int cheatFragmentAllCars_code2Offset = 0xb;
static const uint8_t cheatFragmentAllCars_rawData[] = {
    0x81, 0x38, 0xe4, 0xb8, 0x6f, 0x61, 0x75, 0x28,
    0x81, 0x78, 0x04, 0xa8, 0x00, 0x61, 0x7c,
};

static const CarmCheatFragment carm2Fragments[] = {
    {
        .fileOffset = cheatFragmentAllCars_fileOffset,
        .rawData = cheatFragmentAllCars_rawData,
        .rawDataSize = sizeof(cheatFragmentAllCars_rawData),
        .cheat = "mwucuzysfuyhtqwxepvu",
        .description = "All cars + races (from main menu)",
        .code1Offset = cheatFragmentAllCars_code1Offset,
        .code2Offset = cheatFragmentAllCars_code2Offset,
    },
};

static const CarmGameCheats carm2Cheats = {
    .gameDescription = "CarmageddonII (CARMA2_HW.EXE)",
    .table = &carm2CheatTable,
    .fragments = carm2Fragments,
    .nbFragments = sizeof(carm2Fragments) / sizeof(carm2Fragments[0]),
};

const CarmGameCheats *
carm2_game_cheats() {
    return &carm2Cheats;
}