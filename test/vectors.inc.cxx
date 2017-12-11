
/* X448 test vectors */
template<> const uint8_t Tests<Ed448Goldilocks>::rfc7748_1[56] = {
    0x3f,0x48,0x2c,0x8a,0x9f,0x19,0xb0,0x1e,
    0x6c,0x46,0xee,0x97,0x11,0xd9,0xdc,0x14,
    0xfd,0x4b,0xf6,0x7a,0xf3,0x07,0x65,0xc2,
    0xae,0x2b,0x84,0x6a,0x4d,0x23,0xa8,0xcd,
    0x0d,0xb8,0x97,0x08,0x62,0x39,0x49,0x2c,
    0xaf,0x35,0x0b,0x51,0xf8,0x33,0x86,0x8b,
    0x9b,0xc2,0xb3,0xbc,0xa9,0xcf,0x41,0x13
};
template<> const uint8_t Tests<Ed448Goldilocks>::rfc7748_1000[56] = {
    0xaa,0x3b,0x47,0x49,0xd5,0x5b,0x9d,0xaf,
    0x1e,0x5b,0x00,0x28,0x88,0x26,0xc4,0x67,
    0x27,0x4c,0xe3,0xeb,0xbd,0xd5,0xc1,0x7b,
    0x97,0x5e,0x09,0xd4,0xaf,0x6c,0x67,0xcf,
    0x10,0xd0,0x87,0x20,0x2d,0xb8,0x82,0x86,
    0xe2,0xb7,0x9f,0xce,0xea,0x3e,0xc3,0x53,
    0xef,0x54,0xfa,0xa2,0x6e,0x21,0x9f,0x38
};
template<> const uint8_t Tests<Ed448Goldilocks>::rfc7748_1000000[56] = {
    0x07,0x7f,0x45,0x36,0x81,0xca,0xca,0x36,
    0x93,0x19,0x84,0x20,0xbb,0xe5,0x15,0xca,
    0xe0,0x00,0x24,0x72,0x51,0x9b,0x3e,0x67,
    0x66,0x1a,0x7e,0x89,0xca,0xb9,0x46,0x95,
    0xc8,0xf4,0xbc,0xd6,0x6e,0x61,0xb9,0xb9,
    0xc9,0x46,0xda,0x8d,0x52,0x4d,0xe3,0xd6,
    0x9b,0xd9,0xd9,0xd6,0x6b,0x99,0x7e,0x37
};

template<> const Block Tests<Ed448Goldilocks>::sqrt_minus_one(NULL,0);
template<> const Block Tests<Ed448Goldilocks>::minus_sqrt_minus_one(NULL,0);

const uint8_t elli_patho_448[56] = {
    0x14,0xf0,0x70,0x58,0x41,0xc7,0xf9,0xa5,
    0xfa,0x2c,0x7d,0x87,0x07,0x89,0xe8,0x61,
    0x63,0xe8,0xc8,0xdc,0x06,0x2d,0x39,0x8f,
    0x18,0x83,0x1e,0xc6,0x8c,0x6d,0x73,0x24,
    0xd4,0xb3,0xd3,0xe1,0xf3,0x51,0x8c,0xee,
    0x65,0x79,0x88,0xc1,0x0b,0xcf,0x8e,0xa5,
    0x86,0xa9,0x2e,0xc9,0x17,0x68,0x9b,0x20
};
template<> const Block Tests<Ed448Goldilocks>::elli_patho(elli_patho_448,56);

/* EdDSA test vectors */
const uint8_t ed448_eddsa_sk[][57] = {{
    0x6c,0x82,0xa5,0x62,0xcb,0x80,0x8d,0x10,
    0xd6,0x32,0xbe,0x89,0xc8,0x51,0x3e,0xbf,
    0x6c,0x92,0x9f,0x34,0xdd,0xfa,0x8c,0x9f,
    0x63,0xc9,0x96,0x0e,0xf6,0xe3,0x48,0xa3,
    0x52,0x8c,0x8a,0x3f,0xcc,0x2f,0x04,0x4e,
    0x39,0xa3,0xfc,0x5b,0x94,0x49,0x2f,0x8f,
    0x03,0x2e,0x75,0x49,0xa2,0x00,0x98,0xf9,
    0x5b
}, {
    0xc4,0xea,0xb0,0x5d,0x35,0x70,0x07,0xc6,
    0x32,0xf3,0xdb,0xb4,0x84,0x89,0x92,0x4d,
    0x55,0x2b,0x08,0xfe,0x0c,0x35,0x3a,0x0d,
    0x4a,0x1f,0x00,0xac,0xda,0x2c,0x46,0x3a,
    0xfb,0xea,0x67,0xc5,0xe8,0xd2,0x87,0x7c,
    0x5e,0x3b,0xc3,0x97,0xa6,0x59,0x94,0x9e,
    0xf8,0x02,0x1e,0x95,0x4e,0x0a,0x12,0x27,
    0x4e
}, {
    0xcd,0x23,0xd2,0x4f,0x71,0x42,0x74,0xe7,
    0x44,0x34,0x32,0x37,0xb9,0x32,0x90,0xf5,
    0x11,0xf6,0x42,0x5f,0x98,0xe6,0x44,0x59,
    0xff,0x20,0x3e,0x89,0x85,0x08,0x3f,0xfd,
    0xf6,0x05,0x00,0x55,0x3a,0xbc,0x0e,0x05,
    0xcd,0x02,0x18,0x4b,0xdb,0x89,0xc4,0xcc,
    0xd6,0x7e,0x18,0x79,0x51,0x26,0x7e,0xb3,
    0x28
}, {
    0x25,0x8c,0xdd,0x4a,0xda,0x32,0xed,0x9c,
    0x9f,0xf5,0x4e,0x63,0x75,0x6a,0xe5,0x82,
    0xfb,0x8f,0xab,0x2a,0xc7,0x21,0xf2,0xc8,
    0xe6,0x76,0xa7,0x27,0x68,0x51,0x3d,0x93,
    0x9f,0x63,0xdd,0xdb,0x55,0x60,0x91,0x33,
    0xf2,0x9a,0xdf,0x86,0xec,0x99,0x29,0xdc,
    0xcb,0x52,0xc1,0xc5,0xfd,0x2f,0xf7,0xe2,
    0x1b
}, {
    0x83,0x3f,0xe6,0x24,0x09,0x23,0x7b,0x9d,
    0x62,0xec,0x77,0x58,0x75,0x20,0x91,0x1e,
    0x9a,0x75,0x9c,0xec,0x1d,0x19,0x75,0x5b,
    0x7d,0xa9,0x01,0xb9,0x6d,0xca,0x3d,0x42,
    0xef,0x78,0x22,0xe0,0xd5,0x10,0x41,0x27,
    0xdc,0x05,0xd6,0xdb,0xef,0xde,0x69,0xe3,
    0xab,0x2c,0xec,0x7c,0x86,0x7c,0x6e,0x2c,
    0x49
}};
const uint8_t ed448_eddsa_pk[][57] = {{
    0x5f,0xd7,0x44,0x9b,0x59,0xb4,0x61,0xfd,
    0x2c,0xe7,0x87,0xec,0x61,0x6a,0xd4,0x6a,
    0x1d,0xa1,0x34,0x24,0x85,0xa7,0x0e,0x1f,
    0x8a,0x0e,0xa7,0x5d,0x80,0xe9,0x67,0x78,
    0xed,0xf1,0x24,0x76,0x9b,0x46,0xc7,0x06,
    0x1b,0xd6,0x78,0x3d,0xf1,0xe5,0x0f,0x6c,
    0xd1,0xfa,0x1a,0xbe,0xaf,0xe8,0x25,0x61,
    0x80
}, {
    0x43,0xba,0x28,0xf4,0x30,0xcd,0xff,0x45,
    0x6a,0xe5,0x31,0x54,0x5f,0x7e,0xcd,0x0a,
    0xc8,0x34,0xa5,0x5d,0x93,0x58,0xc0,0x37,
    0x2b,0xfa,0x0c,0x6c,0x67,0x98,0xc0,0x86,
    0x6a,0xea,0x01,0xeb,0x00,0x74,0x28,0x02,
    0xb8,0x43,0x8e,0xa4,0xcb,0x82,0x16,0x9c,
    0x23,0x51,0x60,0x62,0x7b,0x4c,0x3a,0x94,
    0x80
}, {
    0xdc,0xea,0x9e,0x78,0xf3,0x5a,0x1b,0xf3,
    0x49,0x9a,0x83,0x1b,0x10,0xb8,0x6c,0x90,
    0xaa,0xc0,0x1c,0xd8,0x4b,0x67,0xa0,0x10,
    0x9b,0x55,0xa3,0x6e,0x93,0x28,0xb1,0xe3,
    0x65,0xfc,0xe1,0x61,0xd7,0x1c,0xe7,0x13,
    0x1a,0x54,0x3e,0xa4,0xcb,0x5f,0x7e,0x9f,
    0x1d,0x8b,0x00,0x69,0x64,0x47,0x00,0x14,
    0x00
}, {
    0x3b,0xa1,0x6d,0xa0,0xc6,0xf2,0xcc,0x1f,
    0x30,0x18,0x77,0x40,0x75,0x6f,0x5e,0x79,
    0x8d,0x6b,0xc5,0xfc,0x01,0x5d,0x7c,0x63,
    0xcc,0x95,0x10,0xee,0x3f,0xd4,0x4a,0xdc,
    0x24,0xd8,0xe9,0x68,0xb6,0xe4,0x6e,0x6f,
    0x94,0xd1,0x9b,0x94,0x53,0x61,0x72,0x6b,
    0xd7,0x5e,0x14,0x9e,0xf0,0x98,0x17,0xf5,
    0x80
}, {
    0x25,0x9b,0x71,0xc1,0x9f,0x83,0xef,0x77,
    0xa7,0xab,0xd2,0x65,0x24,0xcb,0xdb,0x31,
    0x61,0xb5,0x90,0xa4,0x8f,0x7d,0x17,0xde,
    0x3e,0xe0,0xba,0x9c,0x52,0xbe,0xb7,0x43,
    0xc0,0x94,0x28,0xa1,0x31,0xd6,0xb1,0xb5,
    0x73,0x03,0xd9,0x0d,0x81,0x32,0xc2,0x76,
    0xd5,0xed,0x3d,0x5d,0x01,0xc0,0xf5,0x38,
    0x80
}};
const uint8_t ed448_eddsa_message[][12] = {{
    0
}, {
    0x03
}, {
    0x0c,0x3e,0x54,0x40,0x74,0xec,0x63,0xb0,
    0x26,0x5e,0x0c
}, {
    0x64,0xa6,0x5f,0x3c,0xde,0xdc,0xdd,0x66,
    0x81,0x1e,0x29,0x15
}, {
    0x61,0x62,0x63
}};

template<> const bool Tests<Ed448Goldilocks>::eddsa_prehashed[] = {
    false,
    false,
    false,
    false,
    false,
    true,
    true
};

const uint8_t ed448_eddsa_context[][3] = {{
    0x66,0x6f,0x6f
}};
const uint8_t ed448_eddsa_sig[][114] = {{
    0x53,0x3a,0x37,0xf6,0xbb,0xe4,0x57,0x25,
    0x1f,0x02,0x3c,0x0d,0x88,0xf9,0x76,0xae,
    0x2d,0xfb,0x50,0x4a,0x84,0x3e,0x34,0xd2,
    0x07,0x4f,0xd8,0x23,0xd4,0x1a,0x59,0x1f,
    0x2b,0x23,0x3f,0x03,0x4f,0x62,0x82,0x81,
    0xf2,0xfd,0x7a,0x22,0xdd,0xd4,0x7d,0x78,
    0x28,0xc5,0x9b,0xd0,0xa2,0x1b,0xfd,0x39,
    0x80,0xff,0x0d,0x20,0x28,0xd4,0xb1,0x8a,
    0x9d,0xf6,0x3e,0x00,0x6c,0x5d,0x1c,0x2d,
    0x34,0x5b,0x92,0x5d,0x8d,0xc0,0x0b,0x41,
    0x04,0x85,0x2d,0xb9,0x9a,0xc5,0xc7,0xcd,
    0xda,0x85,0x30,0xa1,0x13,0xa0,0xf4,0xdb,
    0xb6,0x11,0x49,0xf0,0x5a,0x73,0x63,0x26,
    0x8c,0x71,0xd9,0x58,0x08,0xff,0x2e,0x65,
    0x26,0x00
}, {
    0x26,0xb8,0xf9,0x17,0x27,0xbd,0x62,0x89,
    0x7a,0xf1,0x5e,0x41,0xeb,0x43,0xc3,0x77,
    0xef,0xb9,0xc6,0x10,0xd4,0x8f,0x23,0x35,
    0xcb,0x0b,0xd0,0x08,0x78,0x10,0xf4,0x35,
    0x25,0x41,0xb1,0x43,0xc4,0xb9,0x81,0xb7,
    0xe1,0x8f,0x62,0xde,0x8c,0xcd,0xf6,0x33,
    0xfc,0x1b,0xf0,0x37,0xab,0x7c,0xd7,0x79,
    0x80,0x5e,0x0d,0xbc,0xc0,0xaa,0xe1,0xcb,
    0xce,0xe1,0xaf,0xb2,0xe0,0x27,0xdf,0x36,
    0xbc,0x04,0xdc,0xec,0xbf,0x15,0x43,0x36,
    0xc1,0x9f,0x0a,0xf7,0xe0,0xa6,0x47,0x29,
    0x05,0xe7,0x99,0xf1,0x95,0x3d,0x2a,0x0f,
    0xf3,0x34,0x8a,0xb2,0x1a,0xa4,0xad,0xaf,
    0xd1,0xd2,0x34,0x44,0x1c,0xf8,0x07,0xc0,
    0x3a,0x00
}, {
    0x1f,0x0a,0x88,0x88,0xce,0x25,0xe8,0xd4,
    0x58,0xa2,0x11,0x30,0x87,0x9b,0x84,0x0a,
    0x90,0x89,0xd9,0x99,0xaa,0xba,0x03,0x9e,
    0xaf,0x3e,0x3a,0xfa,0x09,0x0a,0x09,0xd3,
    0x89,0xdb,0xa8,0x2c,0x4f,0xf2,0xae,0x8a,
    0xc5,0xcd,0xfb,0x7c,0x55,0xe9,0x4d,0x5d,
    0x96,0x1a,0x29,0xfe,0x01,0x09,0x94,0x1e,
    0x00,0xb8,0xdb,0xde,0xea,0x6d,0x3b,0x05,
    0x10,0x68,0xdf,0x72,0x54,0xc0,0xcd,0xc1,
    0x29,0xcb,0xe6,0x2d,0xb2,0xdc,0x95,0x7d,
    0xbb,0x47,0xb5,0x1f,0xd3,0xf2,0x13,0xfb,
    0x86,0x98,0xf0,0x64,0x77,0x42,0x50,0xa5,
    0x02,0x89,0x61,0xc9,0xbf,0x8f,0xfd,0x97,
    0x3f,0xe5,0xd5,0xc2,0x06,0x49,0x2b,0x14,
    0x0e,0x00
}, {
    0x7e,0xee,0xab,0x7c,0x4e,0x50,0xfb,0x79,
    0x9b,0x41,0x8e,0xe5,0xe3,0x19,0x7f,0xf6,
    0xbf,0x15,0xd4,0x3a,0x14,0xc3,0x43,0x89,
    0xb5,0x9d,0xd1,0xa7,0xb1,0xb8,0x5b,0x4a,
    0xe9,0x04,0x38,0xac,0xa6,0x34,0xbe,0xa4,
    0x5e,0x3a,0x26,0x95,0xf1,0x27,0x0f,0x07,
    0xfd,0xcd,0xf7,0xc6,0x2b,0x8e,0xfe,0xaf,
    0x00,0xb4,0x5c,0x2c,0x96,0xba,0x45,0x7e,
    0xb1,0xa8,0xbf,0x07,0x5a,0x3d,0xb2,0x8e,
    0x5c,0x24,0xf6,0xb9,0x23,0xed,0x4a,0xd7,
    0x47,0xc3,0xc9,0xe0,0x3c,0x70,0x79,0xef,
    0xb8,0x7c,0xb1,0x10,0xd3,0xa9,0x98,0x61,
    0xe7,0x20,0x03,0xcb,0xae,0x6d,0x6b,0x8b,
    0x82,0x7e,0x4e,0x6c,0x14,0x30,0x64,0xff,
    0x3c,0x00
}, {
    0xd4,0xf8,0xf6,0x13,0x17,0x70,0xdd,0x46,
    0xf4,0x08,0x67,0xd6,0xfd,0x5d,0x50,0x55,
    0xde,0x43,0x54,0x1f,0x8c,0x5e,0x35,0xab,
    0xbc,0xd0,0x01,0xb3,0x2a,0x89,0xf7,0xd2,
    0x15,0x1f,0x76,0x47,0xf1,0x1d,0x8c,0xa2,
    0xae,0x27,0x9f,0xb8,0x42,0xd6,0x07,0x21,
    0x7f,0xce,0x6e,0x04,0x2f,0x68,0x15,0xea,
    0x00,0x0c,0x85,0x74,0x1d,0xe5,0xc8,0xda,
    0x11,0x44,0xa6,0xa1,0xab,0xa7,0xf9,0x6d,
    0xe4,0x25,0x05,0xd7,0xa7,0x29,0x85,0x24,
    0xfd,0xa5,0x38,0xfc,0xcb,0xbb,0x75,0x4f,
    0x57,0x8c,0x1c,0xad,0x10,0xd5,0x4d,0x0d,
    0x54,0x28,0x40,0x7e,0x85,0xdc,0xbc,0x98,
    0xa4,0x91,0x55,0xc1,0x37,0x64,0xe6,0x6c,
    0x3c,0x00
}, {
    0x82,0x2f,0x69,0x01,0xf7,0x48,0x0f,0x3d,
    0x5f,0x56,0x2c,0x59,0x29,0x94,0xd9,0x69,
    0x36,0x02,0x87,0x56,0x14,0x48,0x32,0x56,
    0x50,0x56,0x00,0xbb,0xc2,0x81,0xae,0x38,
    0x1f,0x54,0xd6,0xbc,0xe2,0xea,0x91,0x15,
    0x74,0x93,0x2f,0x52,0xa4,0xe6,0xca,0xdd,
    0x78,0x76,0x93,0x75,0xec,0x3f,0xfd,0x1b,
    0x80,0x1a,0x0d,0x9b,0x3f,0x40,0x30,0xcd,
    0x43,0x39,0x64,0xb6,0x45,0x7e,0xa3,0x94,
    0x76,0x51,0x12,0x14,0xf9,0x74,0x69,0xb5,
    0x7d,0xd3,0x2d,0xbc,0x56,0x0a,0x9a,0x94,
    0xd0,0x0b,0xff,0x07,0x62,0x04,0x64,0xa3,
    0xad,0x20,0x3d,0xf7,0xdc,0x7c,0xe3,0x60,
    0xc3,0xcd,0x36,0x96,0xd9,0xd9,0xfa,0xb9,
    0x0f,0x00
}, {
    0xc3,0x22,0x99,0xd4,0x6e,0xc8,0xff,0x02,
    0xb5,0x45,0x40,0x98,0x28,0x14,0xdc,0xe9,
    0xa0,0x58,0x12,0xf8,0x19,0x62,0xb6,0x49,
    0xd5,0x28,0x09,0x59,0x16,0xa2,0xaa,0x48,
    0x10,0x65,0xb1,0x58,0x04,0x23,0xef,0x92,
    0x7e,0xcf,0x0a,0xf5,0x88,0x8f,0x90,0xda,
    0x0f,0x6a,0x9a,0x85,0xad,0x5d,0xc3,0xf2,
    0x80,0xd9,0x12,0x24,0xba,0x99,0x11,0xa3,
    0x65,0x3d,0x00,0xe4,0x84,0xe2,0xce,0x23,
    0x25,0x21,0x48,0x1c,0x86,0x58,0xdf,0x30,
    0x4b,0xb7,0x74,0x5a,0x73,0x51,0x4c,0xdb,
    0x9b,0xf3,0xe1,0x57,0x84,0xab,0x71,0x28,
    0x4f,0x8d,0x07,0x04,0xa6,0x08,0xc5,0x4a,
    0x6b,0x62,0xd9,0x7b,0xeb,0x51,0x1d,0x13,
    0x21,0x00
}};
template<> const Block Tests<Ed448Goldilocks>::eddsa_sk[] = {
    Block(ed448_eddsa_sk[0],57),
    Block(ed448_eddsa_sk[1],57),
    Block(ed448_eddsa_sk[1],57),
    Block(ed448_eddsa_sk[2],57),
    Block(ed448_eddsa_sk[3],57),
    Block(ed448_eddsa_sk[4],57),
    Block(ed448_eddsa_sk[4],57),
    Block(NULL,0)
};
template<> const Block Tests<Ed448Goldilocks>::eddsa_pk[] = {
    Block(ed448_eddsa_pk[0],57),
    Block(ed448_eddsa_pk[1],57),
    Block(ed448_eddsa_pk[1],57),
    Block(ed448_eddsa_pk[2],57),
    Block(ed448_eddsa_pk[3],57),
    Block(ed448_eddsa_pk[4],57),
    Block(ed448_eddsa_pk[4],57)
};
template<> const Block Tests<Ed448Goldilocks>::eddsa_message[] = {
    Block(ed448_eddsa_message[0],0),
    Block(ed448_eddsa_message[1],1),
    Block(ed448_eddsa_message[1],1),
    Block(ed448_eddsa_message[2],11),
    Block(ed448_eddsa_message[3],12),
    Block(ed448_eddsa_message[4],3),
    Block(ed448_eddsa_message[4],3)
};
template<> const Block Tests<Ed448Goldilocks>::eddsa_context[] = {
    Block(NULL,0),
    Block(NULL,0),
    Block(ed448_eddsa_context[0],3),
    Block(NULL,0),
    Block(NULL,0),
    Block(NULL,0),
    Block(ed448_eddsa_context[0],3)
};
template<> const Block Tests<Ed448Goldilocks>::eddsa_sig[] = {
    Block(ed448_eddsa_sig[0],114),
    Block(ed448_eddsa_sig[1],114),
    Block(ed448_eddsa_sig[4],114),
    Block(ed448_eddsa_sig[2],114),
    Block(ed448_eddsa_sig[3],114),
    Block(ed448_eddsa_sig[5],114),
    Block(ed448_eddsa_sig[6],114)
};
