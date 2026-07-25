<div align="center">
  <h1>🔧 SubGhz Multitool Expert</h1>
  <p><strong>L'arme ultime SubGHz pour Flipper Zero — Pandora-like, gratuit, open source</strong></p>
  <p>
    <a href="https://github.com/Carlitack/subghz-multitool-expert/actions">
      <img src="https://github.com/Carlitack/subghz-multitool-expert/actions/workflows/build.yml/badge.svg" alt="Build">
    </a>
    <img src="https://img.shields.io/badge/Flipper_Zero-FAP-blue" alt="Flipper Zero">
    <img src="https://img.shields.io/badge/version-1.0-green" alt="v1.0">
  </p>
</div>

---

## 🎯 Pourquoi cette app ?

Parce que les Pandora/DXL coûtent 4000-6500€ et sont closed-source.
**SubGhz Multitool Expert** fait la même chose, gratuitement, sur ton Flipper Zero.

---

## 🚀 Quick Start

```
flipper0.com → colle https://github.com/Carlitack/subghz-multitool-expert → COMPILE
```

**Menu principal** :
- **Voiture** → Capture configurable par fréquence
- **Emulation** → Saved captures → emulate
- **Outils** → Timing Tuner, Sub Decode
- **Guide** → Documentation protocoles embarquée

---

## 🔫 Fonctionnalités

### 📡 Capture & Analyse
- Récepteur temps réel avec radar animé
- Frequency Hopping (315/433/434/868 MHz)
- AM et FM supportés (AM650, F4, FM476, Honda1, F2, F3)
- RSSI threshold
- Auto-save

### 🔐 Crypto & Protocoles (30 protocoles)

| Crypto | Protocoles |
|---|---|
| **KeeLoq** | StarLine, Kia V3/V4, + Secure (type 3), + FAAC (type 5) |
| **AUT64** | VAG (VW/Audi/Seat/Skoda) |
| **XTEA** | PSA (Peugeot/Citroën) |
| **HITAG2** | Fiat V1 |
| **AES-128** | Kia V6 |
| **CRC/Checksum** | Ford, Honda, Kia, Mazda, Subaru… |

| Marque | Versions |
|---|---|
| Ford | V0 (AM), V1 (F4), V2 (F4), V3 (AM+F4) |
| Kia/Hyundai | V0-V7 (FM476, AM650) |
| VAG | AUT64+XTEA (AM650 434.42) |
| PSA | Mode 1 (AM650), Mode 2 (F3) |
| Honda | Static, V1, V2 |
| Fiat | V0, V1 (HITAG2), V2 |
| Renault | V0 |
| Subaru, Mazda, Mitsubishi, Chrysler, Porsche | ✅ |

### 🎛️ Émulation & TX
- TX activé par défaut
- Compteur rolling persisté via SD
- HITAG2 key prompt (Fiat V1)
- PSA Bruteforce plugin

### 🛠️ Outils
- **Timing Tuner** — Compare timing télécommande vs constante
- **Sub Decode** — Analyse fichiers .sub existants
- **Export CSV** — Données décodées exportables
- **Protocol Help** — Doc embarquée par marque/modèle avec modulations

### 🔜 Roadmap (v1.1+)
- [ ] **Jamming 433 MHz**
- [ ] **Barrières** (Came, Nice, FAAC, Hormann)
- [ ] **Presets 100+ voitures** (choisis ta caisse, appuie, ouvre)
- [ ] **Catch-up +50** compteur
- [ ] **Animations** (radar, unlock, jamming waves)

---

## 🔧 Compilation

### En ligne
```
https://flipper0.com
→ colle https://github.com/Carlitack/subghz-multitool-expert
→ choisis ton firmware
→ COMPILE
```

### GitHub Actions
Chaque push sur `main` → build automatique → artifacts dans l'onglet Actions.

### Local
```bash
pip install ufbt
git clone https://github.com/Carlitack/subghz-multitool-expert
cd subghz-multitool-expert && ufbt
```

---

## 📊 Comparaison Pandora

| Feature | Pandora Fantom | Pandora DXL 5000 | SubGhz MT Expert |
|---|---|---|---|
| Prix | 4000€ | 6500€ | **Gratuit** |
| Protocoles voiture | ~100 | ~150 | 30 |
| Barrières/Portails | 6 | 10+ | 🔜 v1.1 |
| Jamming | ✅ | ✅ | 🔜 v1.1 |
| KeeLoq | ✅ | ✅ | ✅ |
| Smart keys | ❌ | Nissan/Infiniti | ❌ |
| OBDII | ❌ | ✅ | ❌ |
| Open source | ❌ | ❌ | ✅ GPLv3 |

---

## 🧪 Tests

```bash
cd tests
gcc -o test_keeloq test_keeloq.c -lm && ./test_keeloq   # 14/14 ✅
gcc -o test_aut64 test_aut64.c -lm && ./test_aut64       # 16/20 ✅
```

---

## 🙏 Credits

Basé sur **ProtoPirate v3.2** par The Pirates' Plunder.
Fork maintenu par **Carlitack**.

**Devs originaux** : RocketGod, MMX, Leeroy, gullradriel, Skorp, Vadim, L0rdDiakon, YougZ, DoobTheGoober, Slackware, Trikk, Wootini, Li0ard, Ash

---

## 📝 Licence

**GPLv3** — Libre, gratuit, pour toujours.
