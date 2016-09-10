/*******************************************************************************
**                                                                            **
**   The MIT License                                                          **
**                                                                            **
**   Copyright 2016 strawberryentrypoint                                      **
**                                                                            **
**   Permission is hereby granted, free of charge, to any person              **
**   obtaining a copy of this software and associated documentation files     **
**   (the "Software"), to deal in the Software without restriction,           **
**   including without limitation the rights to use, copy, modify, merge,     **
**   publish, distribute, sublicense, and/or sell copies of the Software,     **
**   and to permit persons to whom the Software is furnished to do so,        **
**   subject to the following conditions:                                     **
**                                                                            **
**   The above copyright notice and this permission notice shall be           **
**   included in all copies or substantial portions of the Software.          **
**                                                                            **
**   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,          **
**   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF       **
**   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   **
**   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     **
**   CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     **
**   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        **
**   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   **
**                                                                            **
********************************************************************************
**
**  Notes:
**    -
**
*/

#define __FILE_LOCAL__						"crypto/hashing/sha512.c"

#include "sha512.h"


IDENTID(__FILE_LOCAL__, "0.1", "1", "2016-08-12");


#ifdef PIZZA
static uint64_t constants[] = {
	0x428A2F98D728AE22U, 0x7137449123EF65CDU, 0xB5C0FBCFEC4D3B2FU, 0xE9B5DBA58189DBBCU,
	0x3956C25BF348B538U, 0x59F111F1B605D019U, 0x923F82A4AF194F9BU, 0xAB1C5ED5DA6D8118U,
	0xD807AA98A3030242U, 0x12835B0145706FBEU, 0x243185BE4EE4B28CU, 0x550C7DC3D5FFB4E2U,
	0x72BE5D74F27B896FU, 0x80DEB1FE3B1696B1U, 0x9BDC06A725C71235U, 0xC19BF174CF692694U,
	0xE49B69C19EF14AD2U, 0xEFBE4786384F25E3U, 0x0FC19DC68B8CD5B5U, 0x240CA1CC77AC9C65U,
	0x2DE92C6F592B0275U, 0x4A7484AA6EA6E483U, 0x5CB0A9DCBD41FBD4U, 0x76F988DA831153B5U,
	0x983E5152EE66DFABU, 0xA831C66D2DB43210U, 0xB00327C898FB213FU, 0xBF597FC7BEEF0EE4U,
	0xC6E00BF33DA88FC2U, 0xD5A79147930AA725U, 0x06CA6351E003826FU, 0x142929670A0E6E70U,
	0x27B70A8546D22FFCU, 0x2E1B21385C26C926U, 0x4D2C6DFC5AC42AEDU, 0x53380D139D95B3DFU,
	0x650A73548BAF63DEU, 0x766A0ABB3C77B2A8U, 0x81C2C92E47EDAEE6U, 0x92722C851482353BU,
	0xA2BFE8A14CF10364U, 0xA81A664BBC423001U, 0xC24B8B70D0F89791U, 0xC76C51A30654BE30U,
	0xD192E819D6EF5218U, 0xD69906245565A910U, 0xF40E35855771202AU, 0x106AA07032BBD1B8U,
	0x19A4C116B8D2D0C8U, 0x1E376C085141AB53U, 0x2748774CDF8EEB99U, 0x34B0BCB5E19B48A8U,
	0x391C0CB3C5C95A63U, 0x4ED8AA4AE3418ACBU, 0x5B9CCA4F7763E373U, 0x682E6FF3D6B2B8A3U,
	0x748F82EE5DEFB2FCU, 0x78A5636F43172F60U, 0x84C87814A1F0AB72U, 0x8CC702081A6439ECU,
	0x90BEFFFA23631E28U, 0xA4506CEBDE82BDE9U, 0xBEF9A3F7B2C67915U, 0xC67178F2E372532BU,
	0xCA273ECEEA26619CU, 0xD186B8C721C0C207U, 0xEADA7DD6CDE0EB1EU, 0xF57D4F7FEE6ED178U,
	0x06F067AA72176FBAU, 0x0A637DC5A2C898A6U, 0x113F9804BEF90DAEU, 0x1B710B35131C471BU,
	0x28DB77F523047D84U, 0x32CAAB7B40C72493U, 0x3C9EBE0A15C9BEBCU, 0x431D67C49C100D4CU,
	0x4CC5D4BECB3E42B6U, 0x597F299CFC657E2AU, 0x5FCB6FAB3AD6FAECU, 0x6C44198C4A475817U
};
#endif
