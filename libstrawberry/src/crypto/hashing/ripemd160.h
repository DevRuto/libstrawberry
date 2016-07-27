#ifndef __SB_CRYPTO_HASHING_RIPEMD_H
#define __SB_CRYPTO_HASHING_RIPEMD_H


#include <stdint.h>

#include "../../core/sbapi.h"
#include "../../core/bits.h"
#include "../../core/types/bool.h"


#define R1(x, y, z)                 ((x) ^ (y) ^ (z))
#define R2(x, y, z)                 (((x) & (y)) | (~(x) & (z)))
#define R3(x, y, z)                 (((x) | ~(y)) ^ (z))
#define R4(x, y, z)                 (((x) & (z)) | ((y) & ~(z)))
#define R5(x, y, z)                 ((x) ^ ((y) | ~(z)))

#define NR1(a,b,c,d,e,x,s)          { (a) += R1((b), (c), (d)) + (x);               (a) = SB_ROTL32((a), (s)) + (e); (c) = SB_ROTL32((c), 10); }
#define NR2(a,b,c,d,e,x,s)          { (a) += R2((b), (c), (d)) + (x) + 0x5A827999U; (a) = SB_ROTL32((a), (s)) + (e); (c) = SB_ROTL32((c), 10); }
#define NR3(a,b,c,d,e,x,s)          { (a) += R3((b), (c), (d)) + (x) + 0x6ED9EBA1U; (a) = SB_ROTL32((a), (s)) + (e); (c) = SB_ROTL32((c), 10); }
#define NR4(a,b,c,d,e,x,s)          { (a) += R4((b), (c), (d)) + (x) + 0x8F1BBCDCU; (a) = SB_ROTL32((a), (s)) + (e); (c) = SB_ROTL32((c), 10); }
#define NR5(a,b,c,d,e,x,s)          { (a) += R5((b), (c), (d)) + (x) + 0xA953FD4EU; (a) = SB_ROTL32((a), (s)) + (e); (c) = SB_ROTL32((c), 10); }

#define PR1(a,b,c,d,e,x,s)          { (a) += R5((b), (c), (d)) + (x) + 0x50A28BE6U; (a) = SB_ROTL32((a), (s)) + (e); (c) = SB_ROTL32((c), 10); }
#define PR2(a,b,c,d,e,x,s)          { (a) += R4((b), (c), (d)) + (x) + 0x5C4DD124U; (a) = SB_ROTL32((a), (s)) + (e); (c) = SB_ROTL32((c), 10); }
#define PR3(a,b,c,d,e,x,s)          { (a) += R3((b), (c), (d)) + (x) + 0x6D703EF3U; (a) = SB_ROTL32((a), (s)) + (e); (c) = SB_ROTL32((c), 10); }
#define PR4(a,b,c,d,e,x,s)          { (a) += R2((b), (c), (d)) + (x) + 0x7A6D76E9U; (a) = SB_ROTL32((a), (s)) + (e); (c) = SB_ROTL32((c), 10); }
#define PR5(a,b,c,d,e,x,s)          { (a) += R1((b), (c), (d)) + (x);               (a) = SB_ROTL32((a), (s)) + (e); (c) = SB_ROTL32((c), 10); }


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI void sb_crypto_ripemd160_init(uint32_t *buffer);
	SBAPI void sb_crypto_ripemd160_compress(uint32_t *buffer, uint32_t X[16]);
	SBAPI void sb_crypto_ripemd160_finish(uint32_t *buffer, uint8_t *data, size_t lswlen, size_t mswlen);
	SBAPI void sb_crypto_ripemd160(uint8_t digest[20], void *data, size_t size);
	SBAPI void sb_crypto_ripemd160_str(uint8_t digest_str[41], uint8_t digest[20], sb_bool_t lowercase);

#ifdef __cplusplus
}
#endif


#endif
