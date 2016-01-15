/* Copyright (c) 2014 Cryptography Research, Inc.
 * Released under the MIT License.  See LICENSE.txt for license information.
 */
#ifndef __P448_H__
#define __P448_H__ 1

#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "word.h"

typedef struct gf_448_s {
  uint64_t limb[8];
} __attribute__((aligned(32))) gf_448_s, gf_448_t[1];

#define LBITS 56
#define FIELD_LITERAL(a,b,c,d,e,f,g,h) {{a,b,c,d,e,f,g,h}}

#ifdef __cplusplus
extern "C" {
#endif

static __inline__ void
gf_448_add_RAW (
    gf_448_t out,
    const gf_448_t a,
    const gf_448_t b
) __attribute__((unused));
             
static __inline__ void
gf_448_sub_RAW (
    gf_448_t out,
    const gf_448_t a,
    const gf_448_t b
) __attribute__((unused));
             
static __inline__ void
gf_448_copy (
    gf_448_t out,
    const gf_448_t a
) __attribute__((unused));
             
static __inline__ void
gf_448_weak_reduce (
    gf_448_t inout
) __attribute__((unused));
             
void
gf_448_strong_reduce (
    gf_448_t inout
);

static __inline__ void
gf_448_bias (
    gf_448_t inout,
    int amount
) __attribute__((unused));
         
void
gf_448_mul (
    gf_448_s *__restrict__ out,
    const gf_448_t a,
    const gf_448_t b
);

void
gf_448_mulw (
    gf_448_s *__restrict__ out,
    const gf_448_t a,
    uint64_t b
);

void
gf_448_sqr (
    gf_448_s *__restrict__ out,
    const gf_448_t a
);

void
gf_448_serialize (
    uint8_t *serial,
    const gf_448_t x
);

mask_t
gf_448_deserialize (
    gf_448_t x,
    const uint8_t serial[56]
);

/* -------------- Inline functions begin here -------------- */

void
gf_448_add_RAW (
    gf_448_t out,
    const gf_448_t a,
    const gf_448_t b
) {
    unsigned int i;
    for (i=0; i<8; i++) {
        out->limb[i] = a->limb[i] + b->limb[i];
    }
    gf_448_weak_reduce(out);
}

void
gf_448_sub_RAW (
    gf_448_t out,
    const gf_448_t a,
    const gf_448_t b
) {
    unsigned int i;
    uint64_t co1 = ((1ull<<56)-1)*2, co2 = co1-2;
    for (i=0; i<8; i++) {
        out->limb[i] = a->limb[i] - b->limb[i] + ((i==4) ? co2 : co1);
    }
    gf_448_weak_reduce(out);
}

void
gf_448_copy (
    gf_448_t out,
    const gf_448_t a
) {
    memcpy(out,a,sizeof(*a));
}

void
gf_448_bias (
    gf_448_t a,
    int amt
) {
    (void) a;
    (void) amt;
}

void
gf_448_weak_reduce (
    gf_448_t a
) {
    uint64_t mask = (1ull<<56) - 1;
    uint64_t tmp = a->limb[7] >> 56;
    int i;
    a->limb[4] += tmp;
    for (i=7; i>0; i--) {
        a->limb[i] = (a->limb[i] & mask) + (a->limb[i-1]>>56);
    }
    a->limb[0] = (a->limb[0] & mask) + tmp;
}

#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif /* __P448_H__ */
