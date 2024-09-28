/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0x95, 0x71, 0x9F, 0x29, 0xA6, 0x0B, 0x39, 0x57}

#define DYNAMIC_KEYMAP_LAYER_COUNT 10
#define VIAL_UNLOCK_COMBO_ROWS {0, 2, 4, 6}
#define VIAL_UNLOCK_COMBO_COLS {0, 0, 0, 0}
#define VIAL_TAP_DANCE_ENTRIES 8
#define PERMISSIVE_HOLD

// Framework 16 laptop
// TODO: Consider a solution where resolution is determined based
// on a single env variable, like ULTRAWIDE_MONITOR
#define DIGITIZER_RESOLUTION_X 2560
#define DIGITIZER_RESOLUTION_Y 1600
