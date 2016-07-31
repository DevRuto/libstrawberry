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