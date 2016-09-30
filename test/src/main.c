#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <libstrawberry/core/types/dictionary.h>
#include <libstrawberry/core/bits.h>
#include <libstrawberry/core/time.h>
#include <libstrawberry/core/error.h>
#include <libstrawberry/core/memory.h>
#include <libstrawberry/crypto/hashing/ripemd160.h>
#include <libstrawberry/crypto/symmetric/rijndael.h>
#include <libstrawberry/core/platform.h>
#include <libstrawberry/crypto/symmetric/salsa20.h>
#include <libstrawberry/crypto/hashing/md5.h>
#include <libstrawberry/networking/socket.h>
#include "./tests.h"
#include <libstrawberry/crypto/prng/isaac.h>
#include <libstrawberry/core/cli.h>


void test(const char *name, sb_bool_t(*func)()) {
	sb_bool_t valid = sb_true;
	register uint64_t ns_start = sb_time_nsec(), ns_stop;
	if (!func()) {
		valid = sb_false;
	}
	if (valid) {
		ns_stop = sb_time_nsec();
		printf(status_passed" %15s: %lu\n", name, (unsigned long)(ns_stop - ns_start));
	} else {
		printf(status_failed" %s\n", name);
	}
}

//void __sb_simulate_fatal();

#define TESTS

int main(int argc, char **argv, char **env) {
	sb_cprint(sb_version_full(), SB_COLOR_BRIGHT_YELLOW);
	sb_cprint(sb_compiler_full(), SB_COLOR_BRIGHT_BLUE);
	sb_cprint(sb_compile_date(), SB_COLOR_RED);
	sb_cprint(sb_compile_time(), SB_COLOR_GREEN);
	return 0;

#ifdef TESTS
	test("rijndael", test_rijndael);
	test("salsa20", test_salsa20);
	test("ripemd160", test_ripemd160);
	test("md5", test_md5);
	test("isaac", test_isaac);
	test("rabbit", test_rabbit);
	test("asym/dh", test_diffiehellman);
	test("haaalp/cipher", test_cipher);
#endif

#if (SB_PLATFORM == SB_PLATFORM_ID_WINDOWS)
	fgetc(stdin);
#endif

	return 0;
}
