// protocols/barriers.c — Generic PWM fixed-code barrier/gate decoder
#include "protocols_common.h"

#define TAG "Barriers"

// Timing for common AM/OOK barriers (Came, Nice, FAAC, Hormann)
#define BARRIERS_TE_SHORT  300   // 300µs short pulse
#define BARRIERS_TE_LONG   650   // 650µs long pulse  
#define BARRIERS_TE_DELTA  200   // 200µs tolerance
#define BARRIERS_MIN_BITS   24   // Minimum bits for a valid frame
#define BARRIERS_MAX_BITS   64   // Maximum bits for a barrier code
#define BARRIERS_GAP_MIN   8000  // 8ms minimum gap between frames
#define BARRIERS_UPLOAD_CAP 0x400U

_Static_assert(
    BARRIERS_UPLOAD_CAP <= PP_SHARED_UPLOAD_CAPACITY,
    "BARRIERS_UPLOAD_CAP exceeds shared slab");

typedef enum {
    BarriersStepReset,
    BarriersStepSeekPreamble,
    BarriersStepReadData,
} BarriersStep;

struct SubGhzProtocolDecoderBarriers {
    SubGhzProtocolDecoderBase base;
    SubGhzBlockDecoder decoder;
    SubGhzBlockGeneric generic;
    uint8_t bits[8]; // Up to 64 bits
    uint8_t bit_count;
};

static void* barriers_decoder_alloc(SubGhzEnvironment* environment) {
    UNUSED(environment);
    struct SubGhzProtocolDecoderBarriers* ins = malloc(sizeof(*ins));
    memset(ins, 0, sizeof(*ins));
    ins->generic.protocol_name = "Barrier/Gate";
    return ins;
}

static void barriers_decoder_free(void* ctx) { free(ctx); }

static void barriers_decoder_reset(void* ctx) {
    struct SubGhzProtocolDecoderBarriers* ins = ctx;
    ins->decoder.parser_step = BarriersStepReset;
    ins->bit_count = 0;
    memset(ins->bits, 0, sizeof(ins->bits));
    memset(&ins->generic.data, 0, sizeof(ins->generic.data));
}

static void barriers_decoder_feed(void* ctx, bool level, uint32_t duration) {
    struct SubGhzProtocolDecoderBarriers* ins = ctx;

    if(!level) {
        // Falling edge — check gap
        if(ins->decoder.parser_step == BarriersStepReadData &&
           duration > BARRIERS_GAP_MIN) {
            // Valid frame detected
            if(ins->bit_count >= BARRIERS_MIN_BITS) {
                // Store bits as uint64_t
                uint64_t data = 0;
                for(uint8_t i = 0; i < ins->bit_count && i < 64; i++) {
                    if(ins->bits[i / 8] & (1 << (7 - (i % 8)))) {
                        data |= (1ULL << (63 - i));
                    }
                }
                ins->generic.data = data;
                (unsigned int)ins->generic.data_count_bit = ins->bit_count;
                // Notify decoder
                SubGhzProtocolDecoderBase* base = &ins->base;
                if(base->callback) {
                    base->callback(base, &ins->generic);
                }
            }
            ins->decoder.parser_step = BarriersStepReset;
            ins->bit_count = 0;
            return;
        }
        ins->decoder.te_last = duration;
        return;
    }

    // Rising edge — measure high pulse width
    uint32_t te = ins->decoder.te_last;
    ins->decoder.te_last = 0;

    switch(ins->decoder.parser_step) {
    case BarriersStepReset:
        // Look for a valid short pulse to start
        if(DURATION_DIFF(te, BARRIERS_TE_SHORT) < BARRIERS_TE_DELTA ||
           DURATION_DIFF(te, BARRIERS_TE_LONG) < BARRIERS_TE_DELTA) {
            ins->decoder.parser_step = BarriersStepReadData;
            ins->bit_count = 0;
        }
        break;
    case BarriersStepReadData:
        if(ins->bit_count < BARRIERS_MAX_BITS) {
            // PWM: short pulse = bit 0, long pulse = bit 1
            if(DURATION_DIFF(te, BARRIERS_TE_SHORT) < BARRIERS_TE_DELTA) {
                ins->bits[ins->bit_count / 8] |= (0 << (7 - (ins->bit_count % 8)));
            } else if(DURATION_DIFF(te, BARRIERS_TE_LONG) < BARRIERS_TE_DELTA) {
                ins->bits[ins->bit_count / 8] |= (1 << (7 - (ins->bit_count % 8)));
            }
            ins->bit_count++;
        }
        break;
    default:
        break;
    }
}

static SubGhzProtocolStatus barriers_serialize(void* ctx, FlipperFormat* ff, SubGhzRadioPreset* p) {
    struct SubGhzProtocolDecoderBarriers* ins = ctx;
    return subghz_block_generic_serialize(&ins->generic, ff, p);
}

static SubGhzProtocolStatus barriers_deserialize(void* ctx, FlipperFormat* ff) {
    struct SubGhzProtocolDecoderBarriers* ins = ctx;
    return subghz_block_generic_deserialize(&ins->generic, ff);
}

static void barriers_get_string(void* ctx, FuriString* output) {
    struct SubGhzProtocolDecoderBarriers* ins = ctx;
    furi_string_cat_printf(output, "%s %u bits", ins->generic.protocol_name, (unsigned int)ins->generic.data_count_bit);
}

const SubGhzProtocolDecoder subghz_protocol_barriers_decoder = {
    .alloc = barriers_decoder_alloc,
    .free = barriers_decoder_free,
    .reset = barriers_decoder_reset,
    .feed = barriers_decoder_feed,
    .get_hash_data = NULL,
    .serialize = barriers_serialize,
    .deserialize = barriers_deserialize,
    .get_string = barriers_get_string,
};
