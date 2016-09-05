[BUILD MODE FLAGS]

DEBUG
Debug build.

RELEASE
Release build.



[LOGGING FLAGS]

DONT_REPORT_PLATFORM
Do not report platform information upon inclusion of core/platform.h.



[MISC IN/EXCLUSION FLAGS]

SB_OPT_MLOCK
Specifies that memory locking functionality should be available.

HAVE_GMP
Specifies that the GNU Multiple-Precision arithmetics library is available and added to the project.
By not using this flag, features and algorithms using the library that are not excluded will generate compiler errors (with exception to misc/gmp.c).



[FEATURE EXCLUSION FLAGS]

SB_EXCLUDE_CORE_TYPE_DICTIONARY
Specifies that the dictionary type should be excluded.

SB_EXCLUDE_CRYPTO_HASHING
Specifies that hashing features should be excluded.

SB_EXCLUDE_CRYPTO_KEX_EXCHANGE
Specifies that key exchange features should be excluded.

SB_EXCLUDE_CRYPTO_PADDING
Specifies that padding features should be excluded.

SB_EXCLUDE_CRYPTO_PRNG
Specifies that pseudo-random number generators should be excluded.

SB_EXCLUDE_CRYPTO_SYMMETRIC
Specifies that symmetric ciphers should be excluded.

SB_EXCLUDE_CRYPTO_BLOCKMODE
Specifies that block modes of operation should be excluded.

SB_EXCLUDE_CRYPTO_CIPHER
Specifies that the cipher helper should be excluded.

SB_EXCLUDE_NETWORKING
Specifies that networking features should be excluded.



[FILE EXCLUSION LIST]
crypto/key_exchange/diffiehellman.c: SB_EXCLUDE_CRYPTO_KEY_EXCHANGE_DIFFIE_HELLMAN
