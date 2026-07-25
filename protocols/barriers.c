// protocols/barriers.c — Generic barrier/gate fixed-code detector
#include "protocols_common.h"


#define TAG "Barriers"
#define BARRIER_UPLOAD_CAPACITY 0x200U

_Static_assert(
    BARRIER_UPLOAD_CAPACITY <= PP_SHARED_UPLOAD_CAPACITY,
    "BARRIER_UPLOAD_CAPACITY exceeds shared upload slab");

struct SubGhzProtocolDecoderBarriers {
    SubGhzProtocolDecoderBase base;
    SubGhzBlockDecoder decoder;
    SubGhzBlockGeneric generic;
};


static const SubGhzBlockConst barriers_const = {
    .te_short = 300,
    .te_long = 600,
    .te_delta = 150,
    .min_count_bit_for_found = 24,
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
    struct SubGhzProtocolDecoderBarriers* instance = context;
    instance->decoder.parser_step = 0;
    memset(&instance->generic.data, 0, sizeof(instance->generic.data));
    memset(&instance->generic.data_count_bit, 0, sizeof(instance->generic.data_count_bit));
}

static void barriers_decoder_feed(void* context, bool level, uint32_t duration) {
    struct SubGhzProtocolDecoderBarriers* instance = context;
    SubGhzBlockDecoder* d = &instance->decoder;
    SubGhzBlockGeneric* g = &instance->generic;

    if(level) {
        switch(d->parser_step) {
        case 0:
            if(DURATION_DIFF(duration, barriers_const.te_short * 2) < barriers_const.te_delta * 2) {
                d->parser_step = 1;
            }
            break;
        }
    } else {
        d->te_last = duration;
    }
    UNUSED(g);
}

static bool barriers_decoder_serialize(void* context, FlipperFormat* ff, SubGhzRadioPreset* preset) {
    struct SubGhzProtocolDecoderBarriers* instance = context;
    return subghz_block_generic_serialize(&instance->generic, ff, preset);
}

static bool barriers_decoder_deserialize(void* context, FlipperFormat* ff) {
    struct SubGhzProtocolDecoderBarriers* instance = context;
    return subghz_block_generic_deserialize(&instance->generic, ff);
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
    .type = SubGhzProtocolDecoderTypeStatic,
};

    UNUSED(context);
    UNUSED(generic);
    return SubGhzProtocolEncoderStatusError;
}

const SubGhzProtocolEncoder subghz_protocol_barriers_encoder = {
};
