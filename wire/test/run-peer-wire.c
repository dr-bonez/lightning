#include "../towire.c"
#include "../fromwire.c"
#include "../peer_wire.c"

#include <assert.h>
#include <stdio.h>

#include <ccan/str/hex/hex.h>
#include <common/amount.h>
#include <common/bigsize.h>
#include <bitcoin/chainparams.h>
#include <common/sphinx.h>
#include <wire/gen_peer_wire.h>

extern secp256k1_context *secp256k1_ctx;

/* AUTOGENERATED MOCKS START */
/* Generated stub for amount_asset_is_main */
bool amount_asset_is_main(struct amount_asset *asset UNNEEDED)
{ fprintf(stderr, "amount_asset_is_main called!\n"); abort(); }
/* Generated stub for amount_asset_to_sat */
struct amount_sat amount_asset_to_sat(struct amount_asset *asset UNNEEDED)
{ fprintf(stderr, "amount_asset_to_sat called!\n"); abort(); }
/* Generated stub for amount_sat_add */
 bool amount_sat_add(struct amount_sat *val UNNEEDED,
				       struct amount_sat a UNNEEDED,
				       struct amount_sat b UNNEEDED)
{ fprintf(stderr, "amount_sat_add called!\n"); abort(); }
/* Generated stub for amount_sat_eq */
bool amount_sat_eq(struct amount_sat a UNNEEDED, struct amount_sat b UNNEEDED)
{ fprintf(stderr, "amount_sat_eq called!\n"); abort(); }
/* Generated stub for amount_sat_sub */
 bool amount_sat_sub(struct amount_sat *val UNNEEDED,
				       struct amount_sat a UNNEEDED,
				       struct amount_sat b UNNEEDED)
{ fprintf(stderr, "amount_sat_sub called!\n"); abort(); }
/* AUTOGENERATED MOCKS END */

/* memsetting pubkeys doesn't work */
static void set_pubkey(struct pubkey *key)
{
	u8 der[PUBKEY_CMPR_LEN];
	memset(der, 2, sizeof(der));
	assert(pubkey_from_der(der, sizeof(der), key));
}

static void set_node_id(struct node_id *id)
{
	memset(id->k, 2, sizeof(id->k));
}

/* Size up to field. */
#define upto_field(p, field)				\
	((char *)&(p)->field - (char *)(p))

/* Size including field. */
#define with_field(p, field)				\
	(upto_field((p), field) + sizeof((p)->field))

/* Equal up to this field */
#define eq_upto(p1, p2, field)			\
	(memcmp((p1), (p2), upto_field(p1, field)) == 0)

/* Equal up to and including this field */
#define eq_with(p1, p2, field)			\
	(memcmp((p1), (p2), with_field(p1, field)) == 0)

/* Equal from fields first to last inclusive. */
#define eq_between(p1, p2, first, last)					\
	(memcmp((char *)(p1) + upto_field((p1), first),			\
		(char *)(p2) + upto_field((p1), first),			\
		with_field(p1, last) - upto_field(p1, first)) == 0)

/* Equal in one field. */
#define eq_field(p1, p2, field)						\
	(memcmp((char *)(p1) + upto_field((p1), field),			\
		(char *)(p2) + upto_field((p1), field),			\
		sizeof((p1)->field)) == 0)

#define eq_var(p1, p2, field)			\
	(tal_count((p1)->field) == tal_count((p2)->field) \
	 && (tal_count((p1)->field) == 0 || memcmp((p1)->field, (p2)->field, tal_bytelen((p1)->field)) == 0))

/* Convenience structs for everyone! */
struct msg_error {
	struct channel_id channel_id;
	u8 *data;
};
struct msg_closing_signed {
	struct channel_id channel_id;
	struct amount_sat fee_satoshis;
	secp256k1_ecdsa_signature signature;
};
struct msg_funding_created {
	struct channel_id temporary_channel_id;
	struct bitcoin_txid txid;
	u16 output_index;
	secp256k1_ecdsa_signature signature;
};
struct msg_accept_channel {
	struct channel_id temporary_channel_id;
	struct amount_sat dust_limit_satoshis;
	struct amount_msat max_htlc_value_in_flight_msat;
	struct amount_sat channel_reserve_satoshis;
	struct amount_msat htlc_minimum_msat;
	u32 minimum_depth;
	u16 to_self_delay;
	u16 max_accepted_htlcs;
	struct pubkey funding_pubkey;
	struct pubkey revocation_basepoint;
	struct pubkey payment_basepoint;
	struct pubkey delayed_payment_basepoint;
	struct pubkey htlc_basepoint;
	struct pubkey first_per_commitment_point;
};
struct msg_update_fulfill_htlc {
	struct channel_id channel_id;
	u64 id;
	struct preimage payment_preimage;
};
struct msg_shutdown {
	struct channel_id channel_id;
	u8 *scriptpubkey;
};
struct msg_funding_signed {
	struct channel_id temporary_channel_id;
	secp256k1_ecdsa_signature signature;
};
struct msg_revoke_and_ack {
	struct channel_id channel_id;
	struct secret per_commitment_secret;
	struct pubkey next_per_commitment_point;
};
struct msg_channel_update {
	secp256k1_ecdsa_signature signature;
	u32 timestamp;
	u8 message_flags;
	u8 channel_flags;
	u16 expiry;
	struct amount_msat htlc_minimum_msat;
	u32 fee_base_msat;
	u32 fee_proportional_millionths;
	struct bitcoin_blkid chain_hash;
	struct short_channel_id short_channel_id;
};
struct msg_channel_update_opt_htlc_max {
	secp256k1_ecdsa_signature signature;
	u32 timestamp;
	u8 message_flags;
	u8 channel_flags;
	u16 expiry;
	struct amount_msat htlc_minimum_msat;
	u32 fee_base_msat;
	u32 fee_proportional_millionths;
	struct amount_msat htlc_maximum_msat;
	struct bitcoin_blkid chain_hash;
	struct short_channel_id short_channel_id;
};
struct msg_funding_locked {
	struct channel_id channel_id;
	struct pubkey next_per_commitment_point;
};
struct msg_announcement_signatures {
	struct channel_id channel_id;
	secp256k1_ecdsa_signature announcement_node_signature;
	secp256k1_ecdsa_signature announcement_bitcoin_signature;
	struct short_channel_id short_channel_id;
};
struct msg_commitment_signed {
	struct channel_id channel_id;
	secp256k1_ecdsa_signature signature;
	secp256k1_ecdsa_signature *htlc_signature;
};
struct msg_node_announcement {
	secp256k1_ecdsa_signature signature;
	u32 timestamp;
	struct node_id node_id;
	u8 rgb_color[3];
	u8 alias[32];
	u8 *features;
	u8 *addresses;
};
struct msg_open_channel {
	struct bitcoin_blkid chain_hash;
	struct channel_id temporary_channel_id;
	struct amount_sat funding_satoshis;
	struct amount_msat push_msat;
	struct amount_sat dust_limit_satoshis;
	struct amount_msat max_htlc_value_in_flight_msat;
	struct amount_sat channel_reserve_satoshis;
	struct amount_msat htlc_minimum_msat;
	u32 feerate_per_kw;
	u16 to_self_delay;
	u16 max_accepted_htlcs;
	struct pubkey funding_pubkey;
	struct pubkey revocation_basepoint;
	struct pubkey payment_basepoint;
	struct pubkey delayed_payment_basepoint;
	struct pubkey htlc_basepoint;
	struct pubkey first_per_commitment_point;
	u8 channel_flags;
};
struct msg_update_fail_htlc {
	struct channel_id channel_id;
	u64 id;
	u8 *reason;
};
struct msg_channel_announcement {
	secp256k1_ecdsa_signature node_signature_1;
	secp256k1_ecdsa_signature node_signature_2;
	secp256k1_ecdsa_signature bitcoin_signature_1;
	secp256k1_ecdsa_signature bitcoin_signature_2;
	u8 *features;
	struct bitcoin_blkid chain_hash;
	struct short_channel_id short_channel_id;
	struct node_id node_id_1;
	struct node_id node_id_2;
	struct pubkey bitcoin_key_1;
	struct pubkey bitcoin_key_2;
};
struct msg_init {
	u8 *globalfeatures;
	u8 *localfeatures;
	struct tlv_init_tlvs *tlvs;
};
struct msg_update_add_htlc {
	struct channel_id channel_id;
	u64 id;
	struct amount_msat amount_msat;
	u32 expiry;
	struct sha256 payment_hash;
	u8 onion_routing_packet[TOTAL_PACKET_SIZE];
};
struct msg_update_fee {
	struct channel_id channel_id;
	u32 feerate_per_kw;
};

static void *towire_struct_channel_announcement(const tal_t *ctx,
						const struct msg_channel_announcement *s)
{
	return towire_channel_announcement(ctx,
					   &s->node_signature_1,
					   &s->node_signature_2,
					   &s->bitcoin_signature_1,
					   &s->bitcoin_signature_2,
					   s->features,
					   &s->chain_hash,
					   &s->short_channel_id,
					   &s->node_id_1,
					   &s->node_id_2,
					   &s->bitcoin_key_1,
					   &s->bitcoin_key_2);
}

static struct msg_channel_announcement *fromwire_struct_channel_announcement(const tal_t *ctx, const void *p)
{
	struct msg_channel_announcement *s = tal(ctx, struct msg_channel_announcement);
	if (!fromwire_channel_announcement(s, p,
					  &s->node_signature_1,
					  &s->node_signature_2,
					  &s->bitcoin_signature_1,
					  &s->bitcoin_signature_2,
					  &s->features,
					  &s->chain_hash,
					  &s->short_channel_id,
					  &s->node_id_1,
					  &s->node_id_2,
					  &s->bitcoin_key_1,
					  &s->bitcoin_key_2))
		return tal_free(s);
	return s;
}

static void *towire_struct_open_channel(const tal_t *ctx,
						const struct msg_open_channel *s)
{
	return towire_open_channel(ctx,
				   &s->chain_hash,
				   &s->temporary_channel_id,
				   s->funding_satoshis,
				   s->push_msat,
				   s->dust_limit_satoshis,
				   s->max_htlc_value_in_flight_msat,
				   s->channel_reserve_satoshis,
				   s->htlc_minimum_msat,
				   s->feerate_per_kw,
				   s->to_self_delay,
				   s->max_accepted_htlcs,
				   &s->funding_pubkey,
				   &s->revocation_basepoint,
				   &s->payment_basepoint,
				   &s->delayed_payment_basepoint,
				   &s->htlc_basepoint,
				   &s->first_per_commitment_point,
				   s->channel_flags);
}

static struct msg_open_channel *fromwire_struct_open_channel(const tal_t *ctx, const void *p)
{
	struct msg_open_channel *s = tal(ctx, struct msg_open_channel);

	if (fromwire_open_channel(p,
				  &s->chain_hash,
				  &s->temporary_channel_id,
				  &s->funding_satoshis,
				  &s->push_msat,
				  &s->dust_limit_satoshis,
				  &s->max_htlc_value_in_flight_msat,
				  &s->channel_reserve_satoshis,
				  &s->htlc_minimum_msat,
				  &s->feerate_per_kw,
				  &s->to_self_delay,
				  &s->max_accepted_htlcs,
				  &s->funding_pubkey,
				  &s->revocation_basepoint,
				  &s->payment_basepoint,
				  &s->delayed_payment_basepoint,
				  &s->htlc_basepoint,
				  &s->first_per_commitment_point,
				  &s->channel_flags))
		return s;
	return tal_free(s);
}

static void *towire_struct_accept_channel(const tal_t *ctx,
						const struct msg_accept_channel *s)
{
	return towire_accept_channel(ctx,
				     &s->temporary_channel_id,
				     s->dust_limit_satoshis,
				     s->max_htlc_value_in_flight_msat,
				     s->channel_reserve_satoshis,
				     s->htlc_minimum_msat,
				     s->minimum_depth,
				     s->to_self_delay,
				     s->max_accepted_htlcs,
				     &s->funding_pubkey,
				     &s->revocation_basepoint,
				     &s->payment_basepoint,
				     &s->htlc_basepoint,
				     &s->delayed_payment_basepoint,
				     &s->first_per_commitment_point);
}

static struct msg_accept_channel *fromwire_struct_accept_channel(const tal_t *ctx, const void *p)
{
	struct msg_accept_channel *s = tal(ctx, struct msg_accept_channel);

	if (fromwire_accept_channel(p,
				    &s->temporary_channel_id,
				    &s->dust_limit_satoshis,
				    &s->max_htlc_value_in_flight_msat,
				    &s->channel_reserve_satoshis,
				    &s->htlc_minimum_msat,
				    &s->minimum_depth,
				    &s->to_self_delay,
				    &s->max_accepted_htlcs,
				    &s->funding_pubkey,
				    &s->revocation_basepoint,
				    &s->payment_basepoint,
				    &s->htlc_basepoint,
				    &s->delayed_payment_basepoint,
				    &s->first_per_commitment_point))
		return s;
	return tal_free(s);
}

static void *towire_struct_node_announcement(const tal_t *ctx,
				      const struct msg_node_announcement *s)
{
	return towire_node_announcement(ctx,
					&s->signature,
					s->features,
					s->timestamp,
					&s->node_id,
					s->rgb_color,
					s->alias,
					s->addresses);
}

static struct msg_node_announcement *fromwire_struct_node_announcement(const tal_t *ctx, const void *p)
{
	struct msg_node_announcement *s = tal(ctx, struct msg_node_announcement);
	if (!fromwire_node_announcement(s, p,
				       &s->signature,
					&s->features,
				       &s->timestamp,
				       &s->node_id,
				       s->rgb_color,
				       s->alias,
					&s->addresses))
		return tal_free(s);
	return s;
}

static void *towire_struct_channel_update(const tal_t *ctx,
				      const struct msg_channel_update *s)
{
	return towire_channel_update(ctx,
				     &s->signature,
				     &s->chain_hash,
				     &s->short_channel_id,
				     s->timestamp,
				     s->message_flags,
				     s->channel_flags,
				     s->expiry,
				     s->htlc_minimum_msat,
				     s->fee_base_msat,
				     s->fee_proportional_millionths);
}

static void *towire_struct_channel_update_opt_htlc_max(const tal_t *ctx,
				      const struct msg_channel_update_opt_htlc_max *s)
{
	return towire_channel_update_option_channel_htlc_max(ctx,
				     &s->signature,
				     &s->chain_hash,
				     &s->short_channel_id,
				     s->timestamp,
				     s->message_flags,
				     s->channel_flags,
				     s->expiry,
				     s->htlc_minimum_msat,
				     s->fee_base_msat,
				     s->fee_proportional_millionths,
				     s->htlc_maximum_msat);
}
static struct msg_channel_update *fromwire_struct_channel_update(const tal_t *ctx, const void *p)
{
	struct msg_channel_update *s = tal(ctx, struct msg_channel_update);

	if (fromwire_channel_update(p,
				    &s->signature,
				    &s->chain_hash,
				    &s->short_channel_id,
				    &s->timestamp,
				    &s->message_flags,
				    &s->channel_flags,
				    &s->expiry,
				    &s->htlc_minimum_msat,
				    &s->fee_base_msat,
				    &s->fee_proportional_millionths))
		return s;
	return tal_free(s);
}

static struct msg_channel_update_opt_htlc_max
*fromwire_struct_channel_update_opt_htlc_max(const tal_t *ctx, const void *p)
{
	struct msg_channel_update_opt_htlc_max *s = tal(ctx, struct msg_channel_update_opt_htlc_max);

	if (fromwire_channel_update_option_channel_htlc_max(p,
				    &s->signature,
				    &s->chain_hash,
				    &s->short_channel_id,
				    &s->timestamp,
				    &s->message_flags,
				    &s->channel_flags,
				    &s->expiry,
				    &s->htlc_minimum_msat,
				    &s->fee_base_msat,
				    &s->fee_proportional_millionths,
				    &s->htlc_maximum_msat))
		return s;
	return tal_free(s);
}

static void *towire_struct_funding_locked(const tal_t *ctx,
						const struct msg_funding_locked *s)
{
	return towire_funding_locked(ctx,
				     &s->channel_id,
				     &s->next_per_commitment_point);
}

static struct msg_funding_locked *fromwire_struct_funding_locked(const tal_t *ctx, const void *p)
{
	struct msg_funding_locked *s = tal(ctx, struct msg_funding_locked);

	if (fromwire_funding_locked(p,
				    &s->channel_id,
				    &s->next_per_commitment_point))
		return s;
	return tal_free(s);
}

static void *towire_struct_announcement_signatures(const tal_t *ctx,
						const struct msg_announcement_signatures *s)
{
	return towire_announcement_signatures(ctx,
				     &s->channel_id,
				     &s->short_channel_id,
				     &s->announcement_node_signature,
				     &s->announcement_bitcoin_signature);
}

static struct msg_announcement_signatures *fromwire_struct_announcement_signatures(const tal_t *ctx, const void *p)
{
	struct msg_announcement_signatures *s = tal(ctx, struct msg_announcement_signatures);

	if (fromwire_announcement_signatures(p,
				    &s->channel_id,
				    &s->short_channel_id,
				    &s->announcement_node_signature,
				    &s->announcement_bitcoin_signature))
		return s;
	return tal_free(s);
}

static void *towire_struct_update_fail_htlc(const tal_t *ctx,
					    const struct msg_update_fail_htlc *s)
{
	return towire_update_fail_htlc(ctx,
				       &s->channel_id,
				       s->id,
				       s->reason);
}

static struct msg_update_fail_htlc *fromwire_struct_update_fail_htlc(const tal_t *ctx, const void *p)
{
	struct msg_update_fail_htlc *s = tal(ctx, struct msg_update_fail_htlc);

	if (!fromwire_update_fail_htlc(ctx, p,
				      &s->channel_id,
				      &s->id,
				      &s->reason))
		return tal_free(s);
	return s;

}

static void *towire_struct_update_fulfill_htlc(const tal_t *ctx,
					    const struct msg_update_fulfill_htlc *s)
{
	return towire_update_fulfill_htlc(ctx,
				       &s->channel_id,
				       s->id,
				       &s->payment_preimage);
}

static struct msg_update_fulfill_htlc *fromwire_struct_update_fulfill_htlc(const tal_t *ctx, const void *p)
{
	struct msg_update_fulfill_htlc *s = tal(ctx, struct msg_update_fulfill_htlc);

	if (fromwire_update_fulfill_htlc(p,
				      &s->channel_id,
				      &s->id,
				      &s->payment_preimage))
		return s;
	return tal_free(s);
}

static void *towire_struct_commitment_signed(const tal_t *ctx,
				      const struct msg_commitment_signed *s)
{
	return towire_commitment_signed(ctx,
					&s->channel_id,
					&s->signature,
					s->htlc_signature);
}

static struct msg_commitment_signed *fromwire_struct_commitment_signed(const tal_t *ctx, const void *p)
{
	struct msg_commitment_signed *s = tal(ctx, struct msg_commitment_signed);

	if (!fromwire_commitment_signed(s, p,
				&s->channel_id,
				&s->signature,
				&s->htlc_signature))
		return tal_free(s);
	return s;
}

static void *towire_struct_revoke_and_ack(const tal_t *ctx,
				      const struct msg_revoke_and_ack *s)
{
	return towire_revoke_and_ack(ctx,
				     &s->channel_id,
				     &s->per_commitment_secret,
				     &s->next_per_commitment_point);
}

static struct msg_revoke_and_ack *fromwire_struct_revoke_and_ack(const tal_t *ctx, const void *p)
{
	struct msg_revoke_and_ack *s = tal(ctx, struct msg_revoke_and_ack);

	if (!fromwire_revoke_and_ack(p,
				     &s->channel_id,
				     &s->per_commitment_secret,
				     &s->next_per_commitment_point))
		return tal_free(s);
	return s;

}

static void *towire_struct_funding_signed(const tal_t *ctx,
					  const struct msg_funding_signed *s)
{
	return towire_funding_signed(ctx,
				     &s->temporary_channel_id,
				     &s->signature);
}

static struct msg_funding_signed *fromwire_struct_funding_signed(const tal_t *ctx, const void *p)
{
	struct msg_funding_signed *s = tal(ctx, struct msg_funding_signed);

	if (fromwire_funding_signed(p,
				    &s->temporary_channel_id,
				    &s->signature))
		return s;
	return tal_free(s);
}

static void *towire_struct_closing_signed(const tal_t *ctx,
					  const struct msg_closing_signed *s)
{
	return towire_closing_signed(ctx,
				     &s->channel_id,
				     s->fee_satoshis,
				     &s->signature);
}

static struct msg_closing_signed *fromwire_struct_closing_signed(const tal_t *ctx, const void *p)
{
	struct msg_closing_signed *s = tal(ctx, struct msg_closing_signed);

	if (fromwire_closing_signed(p,
				    &s->channel_id,
				    &s->fee_satoshis,
				    &s->signature))
		return s;
	return tal_free(s);
}

static void *towire_struct_shutdown(const tal_t *ctx,
					  const struct msg_shutdown *s)
{
	return towire_shutdown(ctx,
			       &s->channel_id,
			       s->scriptpubkey);
}

static struct msg_shutdown *fromwire_struct_shutdown(const tal_t *ctx, const void *p)
{
	struct msg_shutdown *s = tal(ctx, struct msg_shutdown);

	if (!fromwire_shutdown(s, p,
			      &s->channel_id,
			      &s->scriptpubkey))
		return tal_free(s);
	return s;
}

static void *towire_struct_funding_created(const tal_t *ctx,
					  const struct msg_funding_created *s)
{
	return towire_funding_created(ctx,
				      &s->temporary_channel_id,
				      &s->txid,
				      s->output_index,
				      &s->signature);
}

static struct msg_funding_created *fromwire_struct_funding_created(const tal_t *ctx, const void *p)
{
	struct msg_funding_created *s = tal(ctx, struct msg_funding_created);

	if (fromwire_funding_created(p,
				     &s->temporary_channel_id,
				     &s->txid,
				     &s->output_index,
				     &s->signature))
		return s;
	return tal_free(s);
}

static void *towire_struct_error(const tal_t *ctx,
				 const struct msg_error *s)
{
	return towire_error(ctx,
			    &s->channel_id,
			    s->data);
}

static struct msg_error *fromwire_struct_error(const tal_t *ctx, const void *p)
{
	struct msg_error *s = tal(ctx, struct msg_error);

	if (!fromwire_error(s, p,
			   &s->channel_id,
			    &s->data))
		return tal_free(s);
	return s;
}

static void *towire_struct_update_add_htlc(const tal_t *ctx,
					  const struct msg_update_add_htlc *s)
{
	return towire_update_add_htlc(ctx,
				      &s->channel_id,
				      s->id,
				      s->amount_msat,
				      &s->payment_hash,
				      s->expiry,
				      s->onion_routing_packet
#if EXPERIMENTAL_FEATURES
				      ,NULL
#endif
		);
}

static struct msg_update_add_htlc *fromwire_struct_update_add_htlc(const tal_t *ctx, const void *p)
{
	struct msg_update_add_htlc *s = tal(ctx, struct msg_update_add_htlc);

	if (fromwire_update_add_htlc(p,
				     &s->channel_id,
				     &s->id,
				     &s->amount_msat,
				     &s->payment_hash,
				     &s->expiry,
				     s->onion_routing_packet
#if EXPERIMENTAL_FEATURES
				     ,NULL
#endif
		    ))
		return s;
	return tal_free(s);
}


static void *towire_struct_update_fee(const tal_t *ctx,
				      const struct msg_update_fee *s)
{
	return towire_update_fee(ctx,
				 &s->channel_id,
				 s->feerate_per_kw);
}

static struct msg_update_fee *fromwire_struct_update_fee(const tal_t *ctx, const void *p)
{
	struct msg_update_fee *s = tal(ctx, struct msg_update_fee);

	if (fromwire_update_fee(p,
				&s->channel_id,
				&s->feerate_per_kw))
		return s;
	return tal_free(s);
}

static void *towire_struct_init(const tal_t *ctx,
					  const struct msg_init *s)
{
	return towire_init(ctx,
			   s->globalfeatures,
			   s->localfeatures,
			   s->tlvs);
}

static struct msg_init *fromwire_struct_init(const tal_t *ctx, const void *p)
{
	struct msg_init *s = tal(ctx, struct msg_init);
	s->tlvs = tlv_init_tlvs_new(s);

	if (!fromwire_init(s, p,
			  &s->globalfeatures,
			  &s->localfeatures,
			  s->tlvs))
		return tal_free(s);

	return s;
}

static bool channel_announcement_eq(const struct msg_channel_announcement *a,
				    const struct msg_channel_announcement *b)
{
	return eq_upto(a, b, features)
		&& eq_var(a, b, features)
		&& eq_field(a, b, chain_hash)
		&& short_channel_id_eq(&a->short_channel_id,
				       &b->short_channel_id)
		&& eq_field(a, b, node_id_1)
		&& eq_field(a, b, node_id_2)
		&& eq_between(a, b, bitcoin_key_1, bitcoin_key_2);
}

static bool funding_locked_eq(const struct msg_funding_locked *a,
			      const struct msg_funding_locked *b)
{
	return memcmp(a, b, sizeof(*a)) == 0;
}

static bool announcement_signatures_eq(const struct msg_announcement_signatures *a,
			      const struct msg_announcement_signatures *b)
{
	return eq_upto(a, b, short_channel_id) &&
		short_channel_id_eq(&a->short_channel_id, &b->short_channel_id);
}

static bool update_fail_htlc_eq(const struct msg_update_fail_htlc *a,
				const struct msg_update_fail_htlc *b)
{
	return eq_with(a, b, id)
		&& eq_var(a, b, reason);
}

static bool commitment_signed_eq(const struct msg_commitment_signed *a,
			  const struct msg_commitment_signed *b)
{
	return eq_upto(a, b, htlc_signature)
		&& eq_var(a, b, htlc_signature);
}

static bool funding_signed_eq(const struct msg_funding_signed *a,
			      const struct msg_funding_signed *b)
{
	return memcmp(a, b, sizeof(*a)) == 0;
}

static bool closing_signed_eq(const struct msg_closing_signed *a,
			      const struct msg_closing_signed *b)
{
	return memcmp(a, b, sizeof(*a)) == 0;
}

static bool update_fulfill_htlc_eq(const struct msg_update_fulfill_htlc *a,
				   const struct msg_update_fulfill_htlc *b)
{
	return memcmp(a, b, sizeof(*a)) == 0;
}

static bool error_eq(const struct msg_error *a,
		     const struct msg_error *b)
{
	return eq_upto(a, b, data)
		&& eq_var(a, b, data);
}

static bool init_eq(const struct msg_init *a,
		    const struct msg_init *b)
{
	if (!eq_var(a, b, globalfeatures) || !eq_var(a, b, localfeatures))
		return false;

	/* Both or neither */
	if (!a->tlvs != !b->tlvs)
		return false;

	if (!a->tlvs)
		return true;

	/* Both or neither */
	if (!a->tlvs->networks != !b->tlvs->networks)
		return false;

	if (!a->tlvs->networks)
		return true;

	if (tal_count(a->tlvs->networks->chains)
	    != tal_count(b->tlvs->networks->chains))
		return false;
	for (size_t i = 0; i < tal_count(a->tlvs->networks->chains); i++)
		if (!bitcoin_blkid_eq(&a->tlvs->networks->chains[i],
				      &b->tlvs->networks->chains[i]))
			return false;
	return true;
}

static bool update_fee_eq(const struct msg_update_fee *a,
			  const struct msg_update_fee *b)
{
	return memcmp(a, b, sizeof(*a)) == 0;
}

static bool shutdown_eq(const struct msg_shutdown *a,
			const struct msg_shutdown *b)
{
	return eq_upto(a, b, scriptpubkey)
		&& eq_var(a, b, scriptpubkey);
}

static bool funding_created_eq(const struct msg_funding_created *a,
			       const struct msg_funding_created *b)
{
	return eq_with(a, b, output_index)
		&& eq_field(a, b, signature);
}

static bool revoke_and_ack_eq(const struct msg_revoke_and_ack *a,
			      const struct msg_revoke_and_ack *b)
{
	return memcmp(a, b, sizeof(*a)) == 0;
}

static bool open_channel_eq(const struct msg_open_channel *a,
			    const struct msg_open_channel *b)
{
	return eq_with(a, b, max_accepted_htlcs)
		&& eq_between(a, b, funding_pubkey, channel_flags);
}

static bool channel_update_eq(const struct msg_channel_update *a,
			      const struct msg_channel_update *b)
{
	return eq_upto(a, b, short_channel_id) &&
		short_channel_id_eq(&a->short_channel_id, &b->short_channel_id);
}

static bool channel_update_opt_htlc_max_eq(const struct msg_channel_update_opt_htlc_max *a,
			      const struct msg_channel_update_opt_htlc_max *b)
{
	return eq_upto(a, b, short_channel_id) &&
		short_channel_id_eq(&a->short_channel_id, &b->short_channel_id);
}

static bool accept_channel_eq(const struct msg_accept_channel *a,
			      const struct msg_accept_channel *b)
{
	return eq_with(a, b, max_accepted_htlcs)
		&& eq_between(a, b, funding_pubkey, first_per_commitment_point);
}

static bool update_add_htlc_eq(const struct msg_update_add_htlc *a,
			       const struct msg_update_add_htlc *b)
{
	return eq_with(a, b, onion_routing_packet);
}

static bool node_announcement_eq(const struct msg_node_announcement *a,
				 const struct msg_node_announcement *b)
{
	return eq_with(a, b, node_id)
		&& eq_field(a, b, rgb_color)
		&& eq_field(a, b, alias)
		&& eq_var(a, b, features)
		&& eq_var(a, b, addresses);
}

/* Try flipping each bit, try running short. */
#define test_bitflip_and_short(a, b, type, short_decodefail)	\
	for (i = 0; i < tal_count(msg) * 8; i++) {		\
		msg[i / 8] ^= (1 << (i%8));			\
		b = fromwire_struct_##type(ctx, msg);		\
		assert(!b || !type##_eq(a, b));			\
		msg[i / 8] ^= (1 << (i%8));			\
	}							\
	for (i = 0; i < tal_count(msg); i++) {			\
		u8 *trunc = tal_dup_arr(ctx, u8, msg, i, 0);	\
		b = fromwire_struct_##type(ctx, trunc);		\
		if (short_decodefail)				\
			assert(!b);				\
		else						\
			assert(!b || !type##_eq(a, b));		\
	}

#define test_corruption(a, b, type) \
	test_bitflip_and_short(a, b, type, true)

/* If it has a tlv at the end, truncated may still parse! */
#define test_corruption_tlv(a, b, type) \
	test_bitflip_and_short(a, b, type, false)

int main(void)
{
	setup_locale();

	struct msg_channel_announcement ca, *ca2;
	struct msg_funding_locked fl, *fl2;
	struct msg_announcement_signatures as, *as2;
	struct msg_update_fail_htlc ufh, *ufh2;
	struct msg_commitment_signed cs, *cs2;
	struct msg_funding_signed fs, *fs2;
	struct msg_closing_signed cls, *cls2;
	struct msg_update_fulfill_htlc uflh, *uflh2;
	struct msg_error e, *e2;
	struct msg_init init, *init2;
	struct msg_update_fee uf, *uf2;
	struct msg_shutdown shutdown, *shutdown2;
	struct msg_funding_created fc, *fc2;
	struct msg_revoke_and_ack raa, *raa2;
	struct msg_open_channel oc, *oc2;
	struct msg_channel_update cu, *cu2;
	struct msg_channel_update_opt_htlc_max cu_opt_htlc_max, *cu_opt_htlc_max2;
	struct msg_accept_channel ac, *ac2;
	struct msg_update_add_htlc uah, *uah2;
	struct msg_node_announcement na, *na2;
	void *ctx = tal(NULL, char);
	size_t i;
	u8 *msg;
	const struct chainparams **chains;

	secp256k1_ctx = secp256k1_context_create(SECP256K1_CONTEXT_VERIFY
						 | SECP256K1_CONTEXT_SIGN);

	memset(&ca, 2, sizeof(ca));
	set_node_id(&ca.node_id_1);
	set_node_id(&ca.node_id_2);
	set_pubkey(&ca.bitcoin_key_1);
	set_pubkey(&ca.bitcoin_key_2);
 	ca.features = tal_arr(ctx, u8, 2);
 	memset(ca.features, 2, 2);

	msg = towire_struct_channel_announcement(ctx, &ca);
	ca2 = fromwire_struct_channel_announcement(ctx, msg);
	assert(channel_announcement_eq(&ca, ca2));
	test_corruption(&ca, ca2, channel_announcement);

	memset(&fl, 2, sizeof(fl));
	set_pubkey(&fl.next_per_commitment_point);

	msg = towire_struct_funding_locked(ctx, &fl);
	fl2 = fromwire_struct_funding_locked(ctx, msg);
	assert(funding_locked_eq(&fl, fl2));
	test_corruption(&fl, fl2, funding_locked);

	memset(&as, 2, sizeof(as));

	msg = towire_struct_announcement_signatures(ctx, &as);
	as2 = fromwire_struct_announcement_signatures(ctx, msg);
	assert(announcement_signatures_eq(&as, as2));
	test_corruption(&as, as2, announcement_signatures);

	memset(&ufh, 2, sizeof(ufh));
 	ufh.reason = tal_arr(ctx, u8, 2);
 	memset(ufh.reason, 2, 2);

	msg = towire_struct_update_fail_htlc(ctx, &ufh);
	ufh2 = fromwire_struct_update_fail_htlc(ctx, msg);
	assert(update_fail_htlc_eq(&ufh, ufh2));
	test_corruption(&ufh, ufh2, update_fail_htlc);

	memset(&cs, 2, sizeof(cs));
	cs.htlc_signature = tal_arr(ctx, secp256k1_ecdsa_signature, 2);
	memset(cs.htlc_signature, 2, sizeof(secp256k1_ecdsa_signature)*2);

	msg = towire_struct_commitment_signed(ctx, &cs);
	cs2 = fromwire_struct_commitment_signed(ctx, msg);
	assert(commitment_signed_eq(&cs, cs2));
	test_corruption(&cs, cs2, commitment_signed);

	memset(&fs, 2, sizeof(fs));

	msg = towire_struct_funding_signed(ctx, &fs);
	fs2 = fromwire_struct_funding_signed(ctx, msg);
	assert(funding_signed_eq(&fs, fs2));
	test_corruption(&fs, fs2, funding_signed);

	memset(&cls, 2, sizeof(cls));

	msg = towire_struct_closing_signed(ctx, &cls);
	cls2 = fromwire_struct_closing_signed(ctx, msg);
	assert(closing_signed_eq(&cls, cls2));
	test_corruption(&cls, cls2, closing_signed);

	memset(&uflh, 2, sizeof(uflh));

	msg = towire_struct_update_fulfill_htlc(ctx, &uflh);
	uflh2 = fromwire_struct_update_fulfill_htlc(ctx, msg);
	assert(update_fulfill_htlc_eq(&uflh, uflh2));
	test_corruption(&uflh, uflh2, update_fulfill_htlc);

	memset(&e, 2, sizeof(e));
	e.data = tal_arr(ctx, u8, 2);
	memset(e.data, 2, 2);

	msg = towire_struct_error(ctx, &e);
	e2 = fromwire_struct_error(ctx, msg);
	assert(error_eq(&e, e2));
	test_corruption(&e, e2, error);

	chains = chainparams_for_networks(ctx);
	for (i = 0; i < tal_count(chains); i++) {
		memset(&init, 2, sizeof(init));
		init.globalfeatures = tal_arr(ctx, u8, 2);
		memset(init.globalfeatures, 2, 2);
		init.localfeatures = tal_arr(ctx, u8, 2);
		memset(init.localfeatures, 2, 2);
		init.tlvs = tlv_init_tlvs_new(ctx);
		init.tlvs->networks = tal(init.tlvs, struct tlv_init_tlvs_networks);
		init.tlvs->networks->chains = tal_arr(ctx, struct bitcoin_blkid, 1);
		init.tlvs->networks->chains[0] = chains[i]->genesis_blockhash;
		msg = towire_struct_init(ctx, &init);
		init2 = fromwire_struct_init(ctx, msg);
		assert(init_eq(&init, init2));
		test_corruption_tlv(&init, init2, init);
	}

	memset(&uf, 2, sizeof(uf));

	msg = towire_struct_update_fee(ctx, &uf);
	uf2 = fromwire_struct_update_fee(ctx, msg);
	assert(update_fee_eq(&uf, uf2));
	test_corruption(&uf, uf2, update_fee);

	memset(&shutdown, 2, sizeof(shutdown));
	shutdown.scriptpubkey = tal_arr(ctx, u8, 2);
	memset(shutdown.scriptpubkey, 2, 2);

	msg = towire_struct_shutdown(ctx, &shutdown);
	shutdown2 = fromwire_struct_shutdown(ctx, msg);
	assert(shutdown_eq(&shutdown, shutdown2));
	test_corruption(&shutdown, shutdown2, shutdown);

	memset(&fc, 2, sizeof(fc));

	msg = towire_struct_funding_created(ctx, &fc);
	fc2 = fromwire_struct_funding_created(ctx, msg);
	assert(funding_created_eq(&fc, fc2));
	test_corruption(&fc, fc2, funding_created);

	memset(&raa, 2, sizeof(raa));
	set_pubkey(&raa.next_per_commitment_point);

	msg = towire_struct_revoke_and_ack(ctx, &raa);
	raa2 = fromwire_struct_revoke_and_ack(ctx, msg);
	assert(revoke_and_ack_eq(&raa, raa2));
	test_corruption(&raa, raa2, revoke_and_ack);

	memset(&oc, 2, sizeof(oc));
	set_pubkey(&oc.funding_pubkey);
	set_pubkey(&oc.revocation_basepoint);
	set_pubkey(&oc.payment_basepoint);
	set_pubkey(&oc.delayed_payment_basepoint);
	set_pubkey(&oc.htlc_basepoint);
	set_pubkey(&oc.first_per_commitment_point);

	msg = towire_struct_open_channel(ctx, &oc);
	oc2 = fromwire_struct_open_channel(ctx, msg);
	assert(open_channel_eq(&oc, oc2));
	test_corruption(&oc, oc2, open_channel);

	memset(&cu, 2, sizeof(cu));

	msg = towire_struct_channel_update(ctx, &cu);
	cu2 = fromwire_struct_channel_update(ctx, msg);
	assert(channel_update_eq(&cu, cu2));
	test_corruption(&cu, cu2, channel_update);

	memset(&cu_opt_htlc_max, 2, sizeof(cu_opt_htlc_max));

	msg = towire_struct_channel_update_opt_htlc_max(ctx, &cu_opt_htlc_max);
	cu_opt_htlc_max2 = fromwire_struct_channel_update_opt_htlc_max(ctx, msg);
	assert(channel_update_opt_htlc_max_eq(&cu_opt_htlc_max, cu_opt_htlc_max2));
	test_corruption(&cu_opt_htlc_max, cu_opt_htlc_max2, channel_update_opt_htlc_max);

	memset(&ac, 2, sizeof(ac));
	set_pubkey(&ac.funding_pubkey);
	set_pubkey(&ac.revocation_basepoint);
	set_pubkey(&ac.payment_basepoint);
	set_pubkey(&ac.delayed_payment_basepoint);
	set_pubkey(&ac.htlc_basepoint);
	set_pubkey(&ac.first_per_commitment_point);

	msg = towire_struct_accept_channel(ctx, &ac);
	ac2 = fromwire_struct_accept_channel(ctx, msg);
	assert(accept_channel_eq(&ac, ac2));
	test_corruption(&ac, ac2, accept_channel);

	memset(&uah, 2, sizeof(uah));

	msg = towire_struct_update_add_htlc(ctx, &uah);
	uah2 = fromwire_struct_update_add_htlc(ctx, msg);
	assert(update_add_htlc_eq(&uah, uah2));
	test_corruption(&uah, uah2, update_add_htlc);

	memset(&na, 2, sizeof(na));
	set_node_id(&na.node_id);
	na.features = tal_arr(ctx, u8, 2);
	memset(na.features, 2, 2);
	na.addresses = tal_arr(ctx, u8, 2);
	memset(na.addresses, 2, 2);

	msg = towire_struct_node_announcement(ctx, &na);
	na2 = fromwire_struct_node_announcement(ctx, msg);
	assert(node_announcement_eq(&na, na2));
	test_corruption(&na, na2, node_announcement);

	/* No memory leaks please */
	secp256k1_context_destroy(secp256k1_ctx);
	tal_free(ctx);
	return 0;
}
