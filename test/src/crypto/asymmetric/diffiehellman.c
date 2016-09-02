#include "../../stdincl.h"
#include "../../../../libstrawberry/src/crypto/key_exchange/diffiehellman.h"
#include "../../../../libstrawberry/src/crypto/prng/isaac.h"
#include "../../../../libstrawberry/src/core/time.h"

//static void do_seed(sb_crypto_prng_isaac_ctx_t *ctx, uint64_t *seed) {
	//*seed = (((uint64_t)sb_crypto_prng_isaac(ctx) << 32) | sb_crypto_prng_isaac(ctx));
//}

sb_bool_t test_diffiehellman() {
	sb_crypto_diffiehellman_ctx_t alice;
	sb_crypto_diffiehellman_ctx_t bob;

	sb_crypto_diffiehellman_init(&alice, 2048, sb_time_nsec());
	sb_crypto_diffiehellman_generate_base(&alice);
	sb_crypto_diffiehellman_generate_keys(&alice);

	sb_crypto_diffiehellman_init(&bob, 2048, sb_time_nsec());
	sb_crypto_diffiehellman_copy_base(&bob, &alice);
	sb_crypto_diffiehellman_generate_keys(&bob);

	sb_crypto_diffiehellman_generate_secret(&alice, bob.pu);
	sb_crypto_diffiehellman_generate_secret(&bob, alice.pu);

	sb_bool_t valid = (mpz_cmp(alice.s, bob.s) == 0);

	sb_crypto_diffiehellman_clear(&alice);
	sb_crypto_diffiehellman_clear(&bob);

	return valid;
}
