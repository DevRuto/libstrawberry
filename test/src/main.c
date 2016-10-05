#include "./tests.h"

#include <libstrawberry/core/time.h>
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

int main(int argc, char **argv, char **env) {
	sb_println(sb_version_full());
	printf("Features: %016lX\n\n", sb_features());
	sb_cprintln("Running tests...", SB_COLOR_BRIGHT_GREEN);

	test("rijndael", test_rijndael);
	test("salsa20", test_salsa20);
	test("ripemd160", test_ripemd160);
	test("md5", test_md5);
	test("isaac", test_isaac);
	test("isaac-otp", test_isaac_otp);
	test("rabbit", test_rabbit);
	test("helper/cipher", test_cipher);
	test("kex/dh", test_diffiehellman);
	test("sha256", test_sha256);

	sb_cprintln("Done.", SB_COLOR_BRIGHT_GREEN);

#if (SB_PLATFORM == SB_PLATFORM_ID_WINDOWS)
	fgetc(stdin);
#endif

	return 0;
}
