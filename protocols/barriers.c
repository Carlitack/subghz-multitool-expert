// protocols/barriers.c — Barrier/Gate protocol placeholder (compiles, decode pending)
#include "protocols_common.h"

#define TAG "Barriers"

struct SubGhzProtocolDecoderBarriers {
    SubGhzProtocolDecoderBase base;
    SubGhzBlockDecoder decoder;
    SubGhzBlockGeneric generic;
};

static void* barriers_decoder_alloc(SubGhzEnvironment* environment) {
    UNUSED(environment);
    struct SubGhzProtocolDecoderBarriers* instance = malloc(sizeof(*instance));
    memset(instance, 0, sizeof(*instance));
    instance->generic.protocol_name = "Barrier/Gate";
    return instance;
}

static void barriers_decoder_free(void* context) {
    free(context);
}

static void barriers_decoder_reset(void* context) {
    UNUSED(context);
}

static void barriers_decoder_feed(void* context, bool level, uint32_t duration) {
    UNUSED(context); UNUSED(level); UNUSED(duration);
}

static SubGhzProtocolStatus barriers_decoder_serialize(
    void* context, FlipperFormat* ff, SubGhzRadioPreset* preset) {
    UNUSED(context); UNUSED(ff); UNUSED(preset);
    return SubGhzProtocolStatusError;
}

static SubGhzProtocolStatus barriers_decoder_deserialize(void* context, FlipperFormat* ff) {
    UNUSED(context); UNUSED(ff);
    return SubGhzProtocolStatusError;
}

static void barriers_decoder_get_string(void* context, FuriString* output) {
    struct SubGhzProtocolDecoderBarriers* instance = context;
    furi_string_cat_printf(output, "%s", instance->generic.protocol_name);
}

const SubGhzProtocolDecoder subghz_protocol_barriers_decoder = {
    .alloc = barriers_decoder_alloc,
    .free = barriers_decoder_free,
    .reset = barriers_decoder_reset,
    .feed = barriers_decoder_feed,
    .get_hash_data = NULL,
    .serialize = barriers_decoder_serialize,
    .deserialize = barriers_decoder_deserialize,
    .get_string = barriers_decoder_get_string,
};
