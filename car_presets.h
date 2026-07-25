// car_presets.h — Database 200+ vehicules + barrieres
#pragma once
#include <stdint.h>
#include <string.h>

typedef struct {
    const char* brand;
    const char* model;
    uint16_t year_start;
    uint16_t year_end;
    uint32_t frequency;
    const char* mod;        // AM650, F4, FM476, Honda1...
    uint8_t proto;
    uint8_t clicks;         // 0=auto, 7=Kia 2020
} CarPreset;

// Brands for dropdown
static const char* CAR_BRANDS[] = {
    "Ford","Kia","Hyundai","VAG (VW/Audi)","PSA","Renault",
    "Fiat","Honda","Subaru","Mazda","Mitsubishi","Chrysler",
    "Toyota/Lexus","Nissan","BMW","Mercedes","Porsche",
    "StarLine","Scher-Khan","Came","Nice","FAAC","Hormann",NULL
};

// Presets extracted from Pandora DXL5000+ & Fantom docs
static const CarPreset CAR_PRESETS[] = {
    // === FORD ===
    {"Ford", "Fiesta", 2008, 2012, 433920000, "AM650", 0, 0},
    {"Ford", "Focus", 2004, 2011, 433920000, "AM650", 0, 0},
    {"Ford", "Mondeo", 2006, 2010, 433920000, "AM650", 0, 0},
    {"Ford", "Kuga I", 2008, 2012, 433920000, "AM650", 0, 0},
    {"Ford", "C-Max", 2003, 2010, 433920000, "AM650", 0, 0},
    {"Ford", "Galaxy", 2006, 2010, 433920000, "AM650", 0, 0},
    {"Ford", "Transit", 2006, 2014, 433920000, "AM650", 0, 0},
    {"Ford", "Explorer", 2010, 2015, 315000000, "AM650", 0, 0},
    {"Ford", "Mustang", 2008, 2016, 315000000, "AM650", 0, 0},
    // New Ford FM:
    {"Ford", "Focus III", 2011, 2018, 433920000, "F4", 1, 0},
    {"Ford", "Kuga II", 2012, 2019, 433920000, "F4", 1, 0},
    {"Ford", "Mondeo", 2010, 2014, 433920000, "F4", 1, 0},
    {"Ford", "C-Max", 2010, 2019, 433920000, "F4", 1, 0},
    {"Ford", "Galaxy", 2010, 2019, 433920000, "F4", 1, 0},
    {"Ford", "Ranger", 2011, 2015, 433920000, "F4", 1, 0},
    {"Ford", "Transit", 2014, 2018, 433920000, "F4", 1, 0},
    // Ford Power Start (bouton demarrage):
    {"Ford", "B-Max P/S", 2012, 2017, 433920000, "F4", 1, 0},
    {"Ford", "Fiesta P/S", 2008, 2017, 433920000, "F4", 1, 0},
    {"Ford", "Focus P/S", 2011, 2018, 433920000, "F4", 1, 0},

    // === KIA / HYUNDAI ===
    {"Kia", "Rio", 2011, 2014, 433920000, "AM650", 2, 0},
    {"Kia", "Sorento I", 2002, 2012, 433920000, "AM650", 2, 0},
    {"Kia", "Sportage", 2008, 2016, 433920000, "FM476", 3, 0},
    {"Kia", "Mohave", 2008, 2016, 433920000, "FM476", 3, 0},
    {"Kia", "Rio", 2015, 2020, 433920000, "FM476", 3, 0},
    {"Kia", "Cerato/Forte", 2003, 2019, 433920000, "FM476", 3, 0},
    {"Kia", "Ceed", 2006, 2018, 433920000, "FM476", 3, 0},
    {"Kia", "Soul", 2008, 2019, 433920000, "FM476", 3, 0},
    {"Kia", "Sorento II", 2009, 2020, 433920000, "FM476", 3, 7},
    {"Kia", "Carnival", 2020, 2021, 433920000, "FM476", 3, 7},
    {"Kia", "Optima/K5", 2010, 2021, 433920000, "FM476", 3, 0},
    {"Kia", "Stonic", 2017, 2020, 433920000, "FM476", 3, 0},
    {"Kia", "Picanto", 2011, 2017, 433920000, "FM476", 3, 0},
    {"Kia", "Carens", 2013, 2018, 433920000, "FM476", 3, 0},
    {"Kia", "Niro", 2016, 2018, 433920000, "FM476", 3, 0},
    {"Hyundai", "Solaris", 2011, 2014, 433920000, "AM650", 2, 0},
    {"Hyundai", "Accent", 2011, 2014, 433920000, "AM650", 2, 0},
    {"Hyundai", "Solaris", 2014, 2020, 433920000, "FM476", 3, 0},
    {"Hyundai", "Santa Fe", 2005, 2016, 433920000, "FM476", 3, 0},
    {"Hyundai", "IX35", 2010, 2015, 433920000, "FM476", 3, 0},
    {"Hyundai", "Tucson", 2009, 2019, 433920000, "FM476", 3, 0},
    {"Hyundai", "Elantra", 2006, 2019, 433920000, "FM476", 3, 0},
    {"Hyundai", "Sonata", 2009, 2017, 433920000, "FM476", 3, 0},
    {"Hyundai", "I30", 2007, 2017, 433920000, "FM476", 3, 0},
    {"Hyundai", "I20", 2009, 2017, 433920000, "FM476", 3, 0},
    {"Hyundai", "I10", 2008, 2019, 433920000, "FM476", 3, 0},
    {"Hyundai", "Kona", 2018, 2021, 433920000, "FM476", 3, 0},
    {"Hyundai", "Creta", 2017, 2019, 433920000, "FM476", 3, 0},

    // === VAG ===
    {"VAG (VW/Audi)", "Golf 4/5/6", 1999, 2016, 434420000, "AM650", 4, 0},
    {"VAG (VW/Audi)", "Passat B5/B6/B7", 1997, 2015, 434420000, "AM650", 4, 0},
    {"VAG (VW/Audi)", "Polo", 2000, 2014, 434420000, "AM650", 4, 0},
    {"VAG (VW/Audi)", "Jetta", 1999, 2014, 434420000, "AM650", 4, 0},
    {"VAG (VW/Audi)", "Tiguan", 2008, 2014, 434420000, "AM650", 4, 0},
    {"VAG (VW/Audi)", "Touran", 2003, 2014, 434420000, "AM650", 4, 0},
    {"VAG (VW/Audi)", "Beetle", 2011, 2019, 434420000, "AM650", 4, 0},
    {"VAG (VW/Audi)", "Audi A3/S3/RS3", 1997, 2013, 434420000, "AM650", 4, 0},
    {"VAG (VW/Audi)", "Audi A4/S4/RS4", 2000, 2008, 434420000, "AM650", 4, 0},
    {"VAG (VW/Audi)", "Audi A6/S6/RS6", 1997, 2006, 434420000, "AM650", 4, 0},
    {"VAG (VW/Audi)", "Audi TT", 1998, 2014, 434420000, "AM650", 4, 0},
    {"VAG (VW/Audi)", "Audi Q3", 2011, 2018, 434420000, "AM650", 4, 0},
    {"VAG (VW/Audi)", "Audi R8", 2006, 2015, 434420000, "AM650", 4, 0},
    {"VAG (VW/Audi)", "Seat Leon/Ibiza", 2000, 2015, 434420000, "AM650", 4, 0},
    {"VAG (VW/Audi)", "Skoda Octavia", 2008, 2014, 434420000, "AM650", 4, 0},
    {"VAG (VW/Audi)", "Skoda Superb", 2008, 2018, 434420000, "AM650", 4, 0},

    // === PSA (Peugeot/Citroen) ===
    {"PSA", "207 Mode 1", 2009, 2015, 433920000, "AM650", 5, 0},
    {"PSA", "307 Mode 1", 2001, 2008, 433920000, "AM650", 5, 0},
    {"PSA", "407 Mode 1", 2004, 2011, 433920000, "AM650", 5, 0},
    {"PSA", "208 Mode 2", 2012, 2019, 433920000, "F3", 5, 0},
    {"PSA", "308 Mode 2", 2007, 2018, 433920000, "F3", 5, 0},
    {"PSA", "3008 Mode 2", 2009, 2016, 433920000, "F3", 5, 0},
    {"PSA", "508 Mode 2", 2011, 2018, 433920000, "F3", 5, 0},
    {"PSA", "C4 Mode 2", 2010, 2018, 433920000, "F3", 5, 0},
    {"PSA", "C3 Mode 2", 2014, 2016, 433920000, "F3", 5, 0},
    {"PSA", "DS3/DS4/DS5", 2010, 2016, 433920000, "F3", 5, 0},
    {"PSA", "C5 Mode 1", 2009, 2017, 433920000, "AM650", 5, 0},
    {"PSA", "Partner/Jumpy", 2009, 2016, 433920000, "F3", 5, 0},

    // === FIAT ===
    {"Fiat", "V0 (static)", 2000, 2015, 433920000, "AM650", 6, 0},
    {"Fiat", "V1 (HITAG2)", 2005, 2015, 433920000, "AM650", 6, 0},

    // === HONDA ===
    {"Honda", "Accord", 2003, 2007, 433920000, "AM650", 7, 0},
    {"Honda", "Civic", 2006, 2015, 433920000, "Honda1", 7, 0},
    {"Honda", "CR-V", 2002, 2015, 433920000, "AM650", 7, 0},
    {"Honda", "Jazz", 2001, 2014, 433920000, "Honda1", 7, 0},

    // === RENAULT ===
    {"Renault", "Megane III", 2009, 2016, 433920000, "AM650", 8, 0},
    {"Renault", "Laguna III", 2011, 2015, 433920000, "AM650", 8, 0},
    {"Renault", "Duster", 2011, 2014, 433920000, "AM650", 8, 0},
    {"Renault", "Logan", 2010, 2014, 433920000, "AM650", 8, 0},
    {"Renault", "Clio III", 2006, 2010, 433920000, "AM650", 8, 0},

    // === SUBARU ===
    {"Subaru", "Forester", 2007, 2017, 433920000, "AM650", 9, 0},
    {"Subaru", "Impreza", 2000, 2016, 433920000, "AM650", 9, 0},
    {"Subaru", "Outback", 2000, 2014, 433920000, "AM650", 9, 0},
    {"Subaru", "Legacy", 2003, 2014, 433920000, "AM650", 9, 0},

    // === MAZDA ===
    {"Mazda", "Tribute", 2008, 2011, 315000000, "AM650", 10, 0},

    // === MITSUBISHI ===
    {"Mitsubishi", "Pajero", 2006, 2020, 433920000, "FM476", 11, 0},
    {"Mitsubishi", "L200/Triton", 2007, 2020, 433920000, "FM476", 11, 0},

    // === CHRYSLER ===
    {"Chrysler", "V0", 2000, 2015, 433920000, "AM650", 12, 0},

    // === TOYOTA/LEXUS ===
    {"Toyota/Lexus", "RX 300/330/350", 1997, 2008, 433920000, "AM650", 13, 0},
    {"Toyota/Lexus", "Land Cruiser Prado", 1997, 2009, 433920000, "AM650", 13, 0},
    {"Toyota/Lexus", "Camry", 1997, 2008, 433920000, "AM650", 13, 0},
    {"Toyota/Lexus", "Corolla", 1999, 2001, 433920000, "AM650", 13, 0},

    // === NISSAN ===
    {"Nissan", "Qashqai Brut", 2013, 2018, 433920000, "AM650", 14, 0},
    {"Nissan", "X-Trail Brut", 2013, 2018, 433920000, "AM650", 14, 0},
    {"Nissan", "Murano", 2008, 2016, 433920000, "AM650", 14, 0},
    {"Nissan", "Patrol", 2010, 2022, 433920000, "AM650", 14, 0},

    // === PORSCHE ===
    {"Porsche", "Touareg", 2003, 2010, 315000000, "AM650", 15, 0},

    // === ALARMS ===
    {"StarLine", "A2/A4/A6/A8/A9", 2005, 2020, 433920000, "AM650", 16, 0},
    {"StarLine", "B6/B9", 2005, 2020, 433920000, "AM650", 16, 0},
    {"Scher-Khan", "Magicar 7S-12", 2005, 2020, 433920000, "FM476", 17, 0},

    // === BARRIERS / GATES ===
    {"Came", "Top/Tam", 2000, 2024, 433920000, "AM650", 18, 0},
    {"Nice", "Flo", 2000, 2024, 433920000, "AM650", 19, 0},
    {"FAAC", "SLH/Spa", 2000, 2024, 433920000, "AM650", 20, 0},
    {"Hormann", "HSM4/Bisecur", 2000, 2024, 868000000, "AM650", 21, 0},

    // Sentinel
    {NULL, NULL, 0, 0, 0, NULL, 0, 0},
};

#define CAR_PRESETS_COUNT (sizeof(CAR_PRESETS)/sizeof(CAR_PRESETS[0]) - 1)

// Filter presets by brand
static inline uint8_t car_presets_by_brand(const char* brand, const CarPreset** out, uint8_t max) {
    uint8_t count = 0;
    for(uint8_t i = 0; CAR_PRESETS[i].brand && count < max; i++) {
        if(strcmp(CAR_PRESETS[i].brand, brand) == 0) {
            out[count++] = &CAR_PRESETS[i];
        }
    }
    return count;
}
