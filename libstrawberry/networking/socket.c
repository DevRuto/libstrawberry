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

#define __FILE_LOCAL__						"networking/socket.c"

#ifndef SB_EXCLUDE_NETWORKING


#include "./socket.h"

#include "../core/error.h"


IDENTID(__FILE_LOCAL__, "0.1", "1", "2016-07-30");


#if (SB_PLATFORM == SB_PLATFORM_ID_WINDOWS)
static sb_bool_t wsaStartup = sb_false;
static WSADATA wsaData;
#endif


sb_bool_t sb_socket_init(sb_socket_ctx_t *sock, const char *node, uint32_t flags) {
	sb_error_reset();

	if (!sock || !node) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return sb_false;
	}

#if (SB_PLATFORM == SB_PLATFORM_ID_WINDOWS)
	if (!wsaStartup) {
		int err;
		if (!(err = WSAStartup(MAKEWORD(2, 2), &wsaData))) {
			wsaStartup = sb_true;
		} else {
			sb_error_set_ex(SB_ERROR_INITIALIZATION, err);
			return sb_false;
		}
	}
#endif

	sb_memset(sock, 0, sizeof(*sock));

	sock->flags = flags;

	sb_addrinfo_t hints;
	sb_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = (SB_FLAG(flags, SB_SOCKET_UDP) ? SOCK_DGRAM : SOCK_STREAM);
	hints.ai_flags = (SB_FLAG(flags, SB_SOCKET_SERVER) ? AI_PASSIVE : 0);
	hints.ai_protocol = 0;

	int err; // TODO: remove or output/register
	if ((err = getaddrinfo(node, NULL, &hints, &sock->addrinfo)) != 0) {
		sb_error_set_ex(SB_ERROR_INITIALIZATION, err);
		return sb_false;
	}

	return sb_true;
}


sb_bool_t sb_socket_clear(sb_socket_ctx_t *sock) {
	sb_error_reset();

	if (!sock) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return sb_false;
	}

	if (sock->addrinfo) {
		freeaddrinfo(sock->addrinfo);
	}

	sb_memset(sock, 0, sizeof(*sock));

	return sb_true;
}


sb_bool_t sb_socket_fromfd(sb_socket_ctx_t *sock, sb_sockfd_t fd, uint32_t flags) {
	sb_error_reset();

	if (!sock) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return sb_false;
	}

	if (!SB_GOOD_SOCKFD(fd)) {
		sb_error_set(SB_ERROR_PARAM_INVALID);
		return sb_false;
	}

	sb_memset(sock, 0, sizeof(*sock));

	sock->fd = fd;
	sock->flags = flags;

	return sb_true;
}


sb_bool_t sb_socket_start(sb_socket_ctx_t *sock, uint16_t port) {
	sb_error_reset();

	if (!sock){
		sb_error_set(SB_ERROR_NULL_PTR);
		return sb_false;
	}

	if (!port) {
		sb_error_set(SB_ERROR_PARAM_INVALID);
		return sb_false;
	}

	sb_addrinfo_t *ptr;
	uint16_t _port = htons(port);
	for (ptr = sock->addrinfo; ptr; ptr = ptr->ai_next) {
		((struct sockaddr_in*)ptr->ai_addr)->sin_port = _port;

		if (!SB_GOOD_SOCKFD(sock->fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol))) {
			continue;
		}

		if (SB_FLAG(sock->flags, SB_SOCKET_SERVER)) {
			if (bind(sock->fd, ptr->ai_addr, ptr->ai_addrlen) == 0) {
				if (listen(sock->fd, SOMAXCONN) == 0) {
					break;
				}
			}
		} else {
			if (connect(sock->fd, ptr->ai_addr, ptr->ai_addrlen) == 0) {
				break;
			}
		}

#if (SB_PLATFORM != SB_PLATFORM_ID_WINDOWS)
		close(sock->fd);
#else
		closesocket(sock->fd);
#endif
	}

	if (!ptr) {
		sock->fd = SB_INVALID_SOCKET;
		sb_error_set(SB_ERROR_INITIALIZATION);
		return sb_false;
	}

	// TODO: timeouts

	sock->selected = ptr;

	return sb_true;
}


sb_bool_t sb_socket_stop(sb_socket_ctx_t *sock) {
	sb_error_reset();

	if (!sock) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return sb_false;
	}

	if (!SB_GOOD_SOCKFD(sock->fd)) {
		sb_error_set(SB_ERROR_VALUE_INVALID);
		return sb_false;
	}

#if (SB_PLATFORM != SB_PLATFORM_ID_WINDOWS)
	close(sock->fd);
#else
	closesocket(sock->fd);
#endif

	sock->fd = SB_INVALID_SOCKET;
	sock->selected = NULL;
	sock->flags |= SB_SOCKET_EXITED;

	return sb_true;
}


sb_bool_t sb_socket_accept(sb_socket_ctx_t *sock, sb_socket_ctx_t *out, struct sockaddr *saddr, socklen_t *saddrlen) {
	sb_error_reset();

	if (!sock) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 1);
		return sb_false;
	}

	if (!out) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 2);
		return sb_false;
	}

	return sb_socket_fromfd(out, sb_socket_acceptfd(sock, saddr, saddrlen), SB_SOCKET_ACCEPTED);
}


sb_sockfd_t sb_socket_acceptfd(sb_socket_ctx_t *sock, struct sockaddr *saddr, socklen_t *saddrlen) {
	sb_error_reset();

	if (!sock) {
		sb_error_set(SB_ERROR_NULL_PTR);
		return SB_INVALID_SOCKET;
	}

	if (!SB_GOOD_SOCKFD(sock->fd)) {
		sb_error_set(SB_ERROR_DESCRIPTOR_INVALID);
		return SB_INVALID_SOCKET;
	}

	if (!saddr && !saddrlen) {
		struct sockaddr _saddr;
		socklen_t _saddrlen;

		return accept(sock->fd, &_saddr, &_saddrlen);
	} else {
		return accept(sock->fd, saddr, saddrlen);
	}
}


sb_ssize_t sb_socket_write(sb_socket_ctx_t *sock, void *in, sb_ssize_t size) {
	sb_error_reset();

	if (!sock) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 1);
		return -2;
	}

	if (!in) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 2);
		return -3;
	}

	if (size < 1) {
		sb_error_set(SB_ERROR_PARAM_INVALID);
		return -4;
	}

	if (!SB_GOOD_SOCKFD(sock->fd)) {
		sb_error_set(SB_ERROR_VALUE_INVALID);
		return -5;
	}

	return send(sock->fd, in, size, 0);
}


sb_ssize_t sb_socket_read(sb_socket_ctx_t *sock, void *out, sb_ssize_t size) {
	sb_error_reset();

	if (!sock) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 1);
		return -2;
	}

	if (!out) {
		sb_error_set_ex(SB_ERROR_NULL_PTR, 2);
		return -3;
	}

	if (size < 1) {
		sb_error_set(SB_ERROR_PARAM_INVALID);
		return -4;
	}

	if (!SB_GOOD_SOCKFD(sock->fd)) {
		sb_error_set(SB_ERROR_VALUE_INVALID);
		return -5;
	}

	return recv(sock->fd, out, size, 0);
}


#endif
