#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../../libstrawberry/src/core/types/dictionary.h"
#include "../../libstrawberry/src/core/bits.h"
#include "../../libstrawberry/src/core/time.h"
#include "../../libstrawberry/src/core/error.h"
#include "../../libstrawberry/src/core/memory.h"
#include "../../libstrawberry/src/crypto/hashing/ripemd160.h"
#include "../../libstrawberry/src/crypto/symmetric/rijndael.h"
#include "../../libstrawberry/src/core/platform.h"
#include "../../libstrawberry/src/crypto/symmetric/salsa20.h"
#include "../../libstrawberry/src/crypto/hashing/md5.h"
#include "../../libstrawberry/src/networking/socket.h"
#include "tests.h"
//#include "../../libstrawberry/src/core/base64.h"


void test(const char *name, sb_bool_t(*func)()) {
	sb_bool_t valid = sb_true;
	register uint64_t ns_start = sb_time_nsec(), ns_stop;//, i;
	//for (i = 0; i < 500; ++i) {
		if (!func()) {
			valid = sb_false;
		}
	//}
	if (valid) {
		ns_stop = sb_time_nsec();
		printf(status_passed" %9s: %lu\n", name, (ns_stop - ns_start));
		//printf(status_passed" %s\n", name);
	} else {
		printf(status_failed" %s\n", name);
	}
}

int main(int argc, char **argv, char **env) {
#define TESTS

#ifdef TESTS
	test("rijndael", test_rijndael);
	test("salsa20", test_salsa20);
	test("ripemd160", test_ripemd160);
	test("md5", test_md5);
	test("isaac", test_isaac);
	test("rabbit", test_rabbit);
	test("asym/dh", test_diffiehellman);
#endif

	/*int i = 100;
	while (i-- \
			  //\
			 //  \
		____//____\
		\_________/
				  \
				   > 0) {
		puts("test");
	}*/

	/*char request[] = "GET / HTTP/1.1\r\nHost: example.com\r\nAccept: * / *\r\n\r\n";
#define BUFFSIZE 128
	char buffer[BUFFSIZE + 1];

	sb_socket_ctx_t socket;
	if (!sb_socket_init(&socket, "example.com", 0)) {
		perror("sb_socket_init()");
		return 1;
	}
	if (!sb_socket_start(&socket, 80)) {
		perror("sb_socket_start()");
		return 1;
	}
	if (sb_socket_write(&socket, request, strlen(request)) < 1) {
		perror("sb_socket_write()");
		return 1;
	}

	sb_ssize_t i;
	while (i = sb_socket_read(&socket, &buffer, BUFFSIZE)) {
		buffer[i] = 0;
		puts(buffer);
	}

	sb_socket_stop(&socket);
	sb_socket_clear(&socket);*/

#if (SB_PLATFORM == SB_PLATFORM_ID_WINDOWS)
	fgetc(stdin);
#endif

	return 0;
}
