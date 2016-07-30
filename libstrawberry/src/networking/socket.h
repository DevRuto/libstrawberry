#ifndef _SB_NETWORKING_SOCKET_H
#define _SB_NETWORKING_SOCKET_H


#include <stdint.h>
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>

#include "../core/sbapi.h"
#include "../core/platform.h"
#include "../core/types/bool.h"


#if (SB_PLATFORM == SB_PLATFORM_ID_WINDOWS)
#	include <winsock2.h>
#	include <ws2tcpip.h>

	typedef SOCKET sockfd_t;

#	define SB_GOOD_SOCKFD(x)				((x) != INVALID_SOCKET)
#elif (SB_PLATFORM == SB_PLATFORM_ID_LINUX)
#	include <sys/socket.h>

	typedef int sockfd_t;

#	define SB_GOOD_SOCKFD(x)				(x)
#else
#	error "No networking support available."
#endif


typedef struct sb_socket_ctx {
	struct addrinfo *addrinfo;
	void *selected_addr;
	sockfd_t sockfd;
	uint32_t flags;
} sb_socket_ctx_t;

typedef struct sb_pssocket_ctx { // ps = "packet switched" (might not be an accurate term but it should describe its purpose reasonably well)
	pthread_t thread;
	void(*on_receive)(void *ctx, void *packet);
	sb_socket_ctx_t socket;
} sb_pssocket_ctx_t;


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI sb_bool_t sb_socket_init(sb_socket_ctx_t *socket, const char *node, uint32_t flags);
	SBAPI sb_bool_t sb_socket_clear(sb_socket_ctx_t *socket);

	SBAPI sb_bool_t sb_socket_start(sb_socket_ctx_t *socket, uint16_t port);
	SBAPI sb_bool_t sb_socket_stop(sb_socket_ctx_t *socket);

	SBAPI size_t sb_socket_write(sb_socket_ctx_t *socket, void *in, size_t size);
	SBAPI size_t sb_socket_read(sb_socket_ctx_t *socket, void *out, size_t size);

	///////////////////////////////////////////////////////////////////////////////////////////

	SBAPI sb_bool_t sb_pssocket_init(sb_pssocket_ctx_t *socket, const char *node, uint32_t flags);
	SBAPI sb_bool_t sb_pssocket_clear(sb_pssocket_ctx_t *socket);

	SBAPI sb_bool_t sb_pssocket_start(sb_pssocket_ctx_t *socket, uint16_t port);
	SBAPI sb_bool_t sb_pssocket_stop(sb_pssocket_ctx_t *socket);

	SBAPI size_t sb_pssocket_write(sb_pssocket_ctx_t *socket, void *in, size_t size);

#ifdef __cplusplus
}
#endif


#endif
