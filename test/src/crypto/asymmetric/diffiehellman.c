#include "../../stdincl.h"
#include "../../../../libstrawberry/src/crypto/key_exchange/diffiehellman.h"
#include "../../../../libstrawberry/src/crypto/random.h"


sb_bool_t test_diffiehellman() {
	sb_crypto_diffiehellman_ctx_t
		alice,
		bob;

	sb_crypto_diffiehellman_init(&alice, 1024, sb_random64());
	sb_crypto_diffiehellman_generate_base(&alice);
	sb_crypto_diffiehellman_generate_keys(&alice);

	sb_crypto_diffiehellman_init(&bob, 1024, sb_random64());
	sb_crypto_diffiehellman_copy_base(&bob, &alice);
	sb_crypto_diffiehellman_generate_keys(&bob);

	sb_size_t
		alice_size = sb_crypto_diffiehellman_port_size(&alice),
		bob_size = sb_crypto_diffiehellman_port_size(&bob);

	if (!alice_size || bob_size != alice_size) {
		sb_crypto_diffiehellman_clear(&alice);
		sb_crypto_diffiehellman_clear(&bob);
        return sb_false;
	}

	SB_MEM_BUFFER_ALLOC(uint8_t, alice_buffer, alice_size);
	SB_MEM_BUFFER_ALLOC(uint8_t, bob_buffer, bob_size);

	sb_crypto_diffiehellman_export_public(&alice, alice_buffer);
	sb_crypto_diffiehellman_export_public(&bob, bob_buffer);

	sb_crypto_diffiehellman_generate_secret(&alice, bob_buffer);
	sb_crypto_diffiehellman_generate_secret(&bob, alice_buffer);

	sb_crypto_diffiehellman_export_secret(&alice, alice_buffer);
	sb_crypto_diffiehellman_export_secret(&bob, bob_buffer);

	sb_crypto_diffiehellman_clear(&alice);
	sb_crypto_diffiehellman_clear(&bob);

	sb_bool_t valid = sb_memequ(alice_buffer, bob_buffer, alice_size);

	SB_MEM_BUFFER_FREE(alice_buffer);
	SB_MEM_BUFFER_FREE(bob_buffer);

	return valid;
}
