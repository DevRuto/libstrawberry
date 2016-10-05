[BUILD MODE FLAGS]

DEBUG
	Debug build.

RELEASE
	Release build.



[LOGGING FLAGS]

REPORT_PLATFORM
	Report platform information upon inclusion of core/platform.h.

REPORT_EXCLUSION
	Reports what files are being excluded from the compilation.



[MISC IN/EXCLUSION FLAGS]

SB_INCLUDE_INTRINSICS
	Specifies that intrinsics should be used.

SB_ASSUME_INTRINSICS_AVAILABLE
	Assumes the headers are available, doesn't use __has_include.

SB_ERROR_REPORTING
	Specifies that error reporting functionality should be included.

SB_OPT_MLOCK
	Specifies that memory locking functionality should be available.

HAVE_GMP
	Specifies that the GNU Multiple-Precision arithmetics library is available and added to the project.
	By not using this flag, features and algorithms using the library that are not excluded will generate compiler errors (with exception to misc/gmp.c).



[EXCLUSION FLAGS]

SB_EXCLUDE_CORE_TYPE_DICTIONARY
	Specifies that the dictionary type should be excluded.

SB_EXCLUDE_CORE_CLI
	Specifies that the CLI helper should be excluded.

SB_EXCLUDE_CRYPTO_HASHING_MD5
	Specifies that MD5 should be excluded.

SB_EXCLUDE_CRYPTO_HASHING_RIPEMD160
	Specifies that RIPEMD160 should be excluded.

SB_EXCLUDE_CRYPTO_HASHING_SHA256
	Specifies that SHA-256 should be excluded.

SB_EXCLUDE_CRYPTO_HASHING_SHA512
	Specifies that SHA-512 should be excluded.

SB_EXCLUDE_CRYPTO_HASHING
	Specifies that all hashing algorithms should be excluded.
		Implies: SB_EXCLUDE_CRYPTO_HASHING_MD5, SB_EXCLUDE_CRYPTO_HASHING_RIPEMD160, SB_EXCLUDE_CRYPTO_HASHING_SHA256, SB_EXCLUDE_CRYPTO_HASHING_SHA512

SB_EXCLUDE_CRYPTO_KEX_EXCHANGE_DIFFIEHELLMAN
	Specifies that Diffie Hellman should be excluded.

SB_EXCLUDE_CRYPTO_KEX_EXCHANGE
	Specifies that all key exchange algorithms should be excluded.
		Implies: SB_EXCLUDE_CRYPTO_KEX_EXCHANGE_DIFFIEHELLMAN

SB_EXCLUDE_CRYPTO_OTP_ISAAC
	Specifies that the ISAAC based OTP should be excluded.

SB_EXCLUDE_CRYPTO_OTP
	Specifies that all OTP algorithms should be excluded.
		Implies: SB_EXCLUDE_CRYPTO_OTP_ISAAC

SB_EXCLUDE_CRYPTO_PADDING_ISO979711
	Specifies that ISO 9797-1 padding method 1 should be excluded.
		Same as SB_EXCLUDE_CRYPTO_PADDING_ZERO.

SB_EXCLUDE_CRYPTO_PADDING_ISO979712
	Specifies that ISO 9797-1 padding method 2 should be excluded.

SB_EXCLUDE_CRYPTO_PADDING_PKCS7
	Specifies that PKCS#7 padding should be excluded.

SB_EXCLUDE_CRYPTO_PADDING_ZERO
	Specifies that zero padding should be excluded.
		Same as SB_EXCLUDE_CRYPTO_PADDING_ISO979711.

SB_EXCLUDE_CRYPTO_PADDING
	Specifies that all padding algorithms should be excluded.
		Implies: SB_EXCLUDE_CRYPTO_PADDING_ISO979711, SB_EXCLUDE_CRYPTO_PADDING_ISO979712, SB_EXCLUDE_CRYPTO_PADDING_PKCS7, SB_EXCLUDE_CRYPTO_PADDING_ZERO

SB_EXCLUDE_CRYPTO_PRNG_ISAAC
	Specifies that the ISAAC CSPRNG should be excluded.
		Implies: SB_EXCLUDE_CRYPTO_OTP_ISAAC

SB_EXCLUDE_CRYPTO_PRNG
	Specifies that all CSPRNGs should be excluded.
		Implies: SB_EXCLUDE_CRYPTO_PRNG_ISAAC

SB_EXCLUDE_CRYPTO_SYMMETRIC_RABBIT
	Specifies that Rabbit should be excluded.

SB_EXCLUDE_CRYPTO_SYMMETRIC_RIJNDAEL
	Specifies that Rijndael should be excluded.

SB_EXCLUDE_CRYPTO_SYMMETRIC_SALSA20
	Specifies that Salsa20 should be excluded.

SB_EXCLUDE_CRYPTO_SYMMETRIC
	Specifies that all symmetric ciphers should be excluded.

SB_EXCLUDE_CRYPTO_BLOCKMODE
	Specifies that the block mode of operation helper should be excluded.

SB_EXCLUDE_CRYPTO_CIPHER
	Specifies that the cipher helper should be excluded.

SB_EXCLUDE_CRYPTO_KEYGEN
	Specifies that the key generator should be excluded.

SB_EXCLUDE_CRYPTO_RANDOM
	Specifies that the global CSPRNG should be excluded.
		Implies: SB_EXCLUDE_CRYPTO_SEEDGEN

SB_EXCLUDE_CRYPTO_SEEDGEN
	Specifies that the seed generator should be excluded.

SB_EXCLUDE_NETWORKING
	Specifies that networking functionality should be excluded.
