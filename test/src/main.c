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
	sb_cprintln(sb_version_full(), SB_COLOR_BRIGHT_YELLOW);
	sb_cprintln(sb_compiler_full(), SB_COLOR_BRIGHT_BLUE);
	sb_cprintln(sb_compile_date(), SB_COLOR_RED);
	sb_cprintln(sb_compile_time(), SB_COLOR_GREEN);

	sb_dictionary_t dictionary;
	sb_dictionary_init(&dictionary, 0);
	printf("dict is %lu fat and has %lu thingies\n", dictionary.__size, dictionary.count);
	sb_dictionary_set(&dictionary, "unkn", 		(void*)0xDEADCAFE);
	sb_dictionary_set(&dictionary, "loves", 	(void*)0xF00BAAAA);
	printf("dict is %lu fat and has %lu thingies\n", dictionary.__size, dictionary.count);
	sb_dictionary_set(&dictionary, "cpck", 		(void*)0xBEEFBABE);
	sb_dictionary_set(&dictionary, "heella", 	(void*)0xBABABABA);
	sb_dictionary_set(&dictionary, "much", 		(void*)0xBAABAAB0);
	printf("dict is %lu fat and has %lu thingies\n", dictionary.__size, dictionary.count);

	sb_dictionary_entry_t *entry;
#define DICT_TEST(x) \
	entry = sb_dictionary_get(&dictionary, x);\
	if (entry) {\
		printf("%s(%u)=%p\n", entry->key, entry->key_size, entry->value);\
	} else {\
		sb_cprintln("thingy not found yo", SB_COLOR_BRIGHT_RED);\
	}

	DICT_TEST("");
	DICT_TEST("unkn");
	DICT_TEST("unikornn");
	DICT_TEST("loves");
	DICT_TEST("lotsalove");
	DICT_TEST("cpck");
	DICT_TEST("cupcake");
	DICT_TEST("heella");
	DICT_TEST("hella");
	DICT_TEST("much");
	DICT_TEST(NULL);

	DICT_TEST("unkn");
	sb_dictionary_set(&dictionary, "unkn", 		(void*)0xCAFEBEEF);
	DICT_TEST("unkn");
	sb_dictionary_set(&dictionary, "cpck", 		(void*)0xBABEBEEF);
	DICT_TEST("cpck");

	sb_dictionary_clear(&dictionary);

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
