/**********************************************************************************
**                                                                               **
**  Copyright 2016 strawberryentrypoint                                          **
**                                                                               **
**  This file is part of libstrawberry.                                          **
**                                                                               **
**  libstrawberry is free software: you can redistribute it and/or modify        **
**  it under the terms of the GNU General Public License as published by         **
**  the Free Software Foundation, either version 3 of the License, or            **
**  (at your option) any later version.                                          **
**                                                                               **
**  libstrawberry is distributed in the hope that it will be useful,             **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of               **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                **
**  GNU General Public License for more details.                                 **
**                                                                               **
**  You should have received a copy of the GNU General Public License            **
**  along with libstrawberry.  If not, see <http://www.gnu.org/licenses/>.       **
**                                                                               **
***********************************************************************************
**
**  Notes:
**    -
**
*/

#include "../core/../core/identid.h"
IDENTID("pssocket.c", "0.1", "1", "2016-07-30");

#include "socket.h"


sb_bool_t sb_pssocket_init(sb_pssocket_ctx_t *pssock, const char *node, uint32_t flags, void(*on_receive)(void *ctx, void *packet)) {
	return sb_false;
}

sb_bool_t sb_pssocket_clear(sb_pssocket_ctx_t *pssock) {
	return sb_false;
}

sb_bool_t sb_pssocket_start(sb_pssocket_ctx_t *pssock, uint16_t port) {
	return sb_false;
}

sb_bool_t sb_pssocket_stop(sb_pssocket_ctx_t *pssock) {
	return sb_false;
}

sb_ssize_t sb_pssocket_write(sb_pssocket_ctx_t *pssock, void *in, sb_size_t size) {
	return sb_false;
}
