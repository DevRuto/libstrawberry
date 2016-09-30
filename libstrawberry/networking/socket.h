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
**    // TODO Accept functionality /might/ come in handy for server-mode sockets.
**
*/

#ifndef __SB_NETWORKING_SOCKET_H
#define __SB_NETWORKING_SOCKET_H


#include "../core/stdincl.h"

#include "../core/bits.h"
#include "../core/memory.h"


// Experimental changes.
typedef uint64_t sb_sockfd_t;
#if (SB_PLATFORM == SB_PLATFORM_ID_WINDOWS)
#	include <winsock2.h>
#	include <ws2tcpip.h>

	//typedef SOCKET sb_sockfd_t;
#	define SB_INVALID_SOCKET				INVALID_SOCKET
#	define SB_GOOD_SOCKFD(x)				((x) != SB_INVALID_SOCKET)
#elif (SB_PLATFORM == SB_PLATFORM_ID_LINUX)
#	include <sys/socket.h>
#	include <sys/types.h>
#	include <arpa/inet.h>
#	include <unistd.h>
#	include <errno.h>
#	include <fcntl.h>
#	include <sys/ioctl.h>
#	include <netdb.h>

	//typedef int sb_sockfd_t;

#	define SB_INVALID_SOCKET				-1
#	define SB_GOOD_SOCKFD(x)				((x) > 0)
#else
#	error "No networking support available."
#endif


typedef struct addrinfo sb_addrinfo_t;

typedef struct sb_socket_ctx {
	sb_sockfd_t fd;
	sb_addrinfo_t *addrinfo;
	sb_addrinfo_t *selected;
	uint32_t flags;
} sb_socket_ctx_t;

typedef uint8_t sb_addr6_storage[16];


#define SB_SOCKET_SERVER					SB_BIT_1
#define SB_SOCKET_EXITED					SB_BIT_2
#define SB_SOCKET_UDP						SB_BIT_3
#define SB_SOCKET_ACCEPTED					SB_BIT_4


#ifdef __cplusplus
extern "C" {
#endif

	SBAPI sb_bool_t sb_socket_init(sb_socket_ctx_t *sock, const char *node, uint32_t flags);
	SBAPI sb_bool_t sb_socket_clear(sb_socket_ctx_t *sock);

	SBAPI sb_bool_t sb_socket_fromfd(sb_socket_ctx_t *sock, sb_sockfd_t fd, uint32_t flags);

	SBAPI sb_bool_t sb_socket_start(sb_socket_ctx_t *sock, uint16_t port);
	SBAPI sb_bool_t sb_socket_stop(sb_socket_ctx_t *sock);

	SBAPI sb_bool_t sb_socket_accept(sb_socket_ctx_t *sock, sb_socket_ctx_t *out, struct sockaddr *saddr, socklen_t *saddrlen);
	SBAPI sb_sockfd_t sb_socket_acceptfd(sb_socket_ctx_t *sock, struct sockaddr *saddr, socklen_t *saddrlen);

	SBAPI sb_ssize_t sb_socket_write(sb_socket_ctx_t *sock, void *in, sb_size_t size);
	SBAPI sb_ssize_t sb_socket_write_str(sb_socket_ctx_t *sock, const char *str);
	SBAPI sb_ssize_t sb_socket_read(sb_socket_ctx_t *sock, void *out, sb_size_t size);

#ifdef __cplusplus
}
#endif


#endif
