/* Copyright 2022  CyanDuck
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "digitizer.h"
#include "features/layer_lock.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _EXTRA,
    _NAV,
    _MOUSE,
    _MEDIA,
    _BUTTON,
    _NUM,
    _SYM,
    _FUNC,
    _DIGITIZER,
};

enum custom_keycodes {
  LLOCK = QK_KB_0,
  MACRO_SETUP_EDITOR,
  MACRO_THUMBS_UP,
  DG_LEFT,
  DG_RIGHT,
  DG_UP,
  DG_DOWN,
};

static float dig_x = 0.5;
static float dig_y = 0.5;
static float x_bound = 1.0;
static float y_bound = 1.0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BASE
 *
 * ,----------------------------------.                      ,----------------------------------.
 * |   Q  |   W  |   F  |   P  |   B  |                      |   J  |   L  |   U  |   Y  |   '  |
 * |------+------+------+------+------|                      |------+------+------+------+------|
 * |   A  |   R  |   S  |   T  |   G  |                      |   M  |   N  |   E  |   I  |   O  |
 * |------+------+------+------+------|  ,-----.    ,-----.  |------+------+------+------+------|
 * |   Z  |   X  |   C  |   D  |   V  |  |     |    |     |  |   K  |   H  |   ,  |   .  |   /  |
 * `----------------------------------'  `-----'    `-----'  `----------------------------------'
 *          ,-----.   ,--------------------.            ,--------------------.   ,-----.
 *          |     |   | ESC | SPACE | TAB  |            |  BS | ENTER  | DEL |   |     |
 *          `-----'   `--------------------'            `--------------------'   `-----'
 */
[_BASE] = LAYOUT(
	KC_Q,				KC_W,				KC_F,				KC_P,				KC_B,			KC_J,	KC_L,				KC_U,				KC_Y,				KC_QUOT,
	MT(MOD_LGUI, KC_A),	MT(MOD_LALT, KC_R),	MT(MOD_LCTL, KC_S),	MT(MOD_LSFT, KC_T),	KC_G,			KC_M,	MT(MOD_LSFT, KC_N),	MT(MOD_LCTL, KC_E),	MT(MOD_LALT, KC_I),	MT(MOD_LGUI, KC_O),
	LT(_BUTTON, KC_Z),	KC_X,				KC_C,				KC_D,				KC_V,			KC_K,	KC_H,				KC_COMM,			KC_DOT,				LT(_BUTTON, KC_SLSH),
	KC_NO,				LT(_MEDIA, KC_ESC),	LT(_NAV, KC_SPC),	LT(_MOUSE, KC_TAB),	KC_NO,  		KC_NO,	LT(_SYM, KC_BSPC),	LT(_NUM, KC_ENT),	LT(_FUNC, KC_DEL),	KC_NO
),

/* EXTRA
 *
 * ,----------------------------------.                      ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |                      |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|                      |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |                      |   H  |   J  |   K  |   L  |   '  |
 * |------+------+------+------+------|  ,-----.    ,-----.  |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |  |     |    |     |  |   N  |   M  |   ,  |   .  |   /  |
 * `----------------------------------'  `-----'    `-----'  `----------------------------------'
 *          ,-----.   ,--------------------.            ,--------------------.   ,-----.
 *          |     |   | ESC | SPACE | TAB  |            |  ENTER  | BS | DEL |   |     |
 *          `-----'   `--------------------'            `--------------------'   `-----'
 */
[_EXTRA] = LAYOUT(
	KC_Q,				KC_W,				KC_E,				KC_R,				KC_T,			KC_Y,	KC_U,				KC_I,				KC_O,				KC_P,
	MT(MOD_LGUI, KC_A),	MT(MOD_LALT, KC_S),	MT(MOD_LCTL, KC_D),	MT(MOD_LSFT, KC_F),	KC_G,			KC_H,	MT(MOD_LSFT, KC_J),	MT(MOD_LCTL, KC_K),	MT(MOD_LALT, KC_L),	MT(MOD_LGUI, KC_QUOT),
	LT(_BUTTON, KC_Z),	KC_X,				KC_C,				KC_V,				KC_B,			KC_N,	KC_M,				KC_COMM,			KC_DOT,				LT(_BUTTON, KC_SLSH),
	KC_NO,				LT(_MEDIA, KC_ESC),	LT(_NAV, KC_SPC),	LT(_MOUSE, KC_TAB),	KC_NO,  		KC_NO,	LT(_SYM, KC_ENT),	LT(_NUM, KC_BSPC),	LT(_FUNC, KC_DEL),	KC_NO
),



/* NAV
 *
 * ,----------------------------------.                      ,----------------------------------.
 * |      |      |      |      |      |                      | REDO | PASTE| COPY | CUT  | UNDO |
 * |------+------+------+------+------|                      |------+------+------+------+------|
 * | SUPR | ALT  | CTRL | SHIFT|      |                      | CAPS | LEFT | DOWN |  UP  | RIGHT|
 * |------+------+------+------+------|  ,-----.    ,-----.  |------+------+------+------+------|
 * |      |      |      |      |      |  |     |    |     |  |INSERT| HOME | PGUP | PGDN | END  |
 * `----------------------------------'  `-----'    `-----'  `----------------------------------'
 *          ,-----.   ,--------------------.            ,--------------------.   ,-----.
 *          |     |   |     | XXXXX |      |            |  ENTER  | BS | DEL |   |     |
 *          `-----'   `--------------------'            `--------------------'   `-----'
 */
[_NAV] = LAYOUT(
	QK_BOOT,    KC_NO,		TD(2),		TD(3),	    KC_NO,		C(KC_Y),C(KC_V),C(KC_C),C(KC_X),	C(KC_Z),
	KC_LGUI,	KC_LALT,	KC_LCTL,	KC_LSFT,	KC_NO,		CW_TOGG,KC_LEFT,KC_DOWN,KC_UP,		KC_RIGHT,
	KC_NO,		KC_NO,		KC_NO,		TD(1),	KC_NO,		KC_INS,	KC_HOME,KC_PGUP,KC_PGDN,	KC_END,
	KC_NO,		KC_NO,      KC_NO,      KC_NO,		KC_NO,	    KC_NO,	KC_ENT,	KC_BSPC,KC_DEL,     KC_NO
),

/* MOUSE
 *
 * ,----------------------------------.                      ,----------------------------------.
 * |      |      |      |      |      |                      |      |      |      |      |      |
 * |------+------+------+------+------|                      |------+------+------+------+------|
 * | SUPR | ALT  | CTRL | SHIFT|      |                      |      | M <- | M v  |  M ^ | M -> |
 * |------+------+------+------+------|  ,-----.    ,-----.  |------+------+------+------+------|
 * |      |      |      |      |      |  |     |    |     |  |      | W <- | W v  |  W ^ |W ->  |
 * `----------------------------------'  `-----'    `-----'  `----------------------------------'
 *          ,-----.   ,--------------------.            ,--------------------.   ,-----.
 *          |     |   |     |       | XXXX |            | RIGHT | LEFT | MID |   |     |
 *          `-----'   `--------------------'            `--------------------'   `-----'
 */
[_MOUSE] = LAYOUT(
	QK_BOOT,    KC_NO,		TD(2),		TD(3),	    KC_NO,		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_LGUI,	KC_LALT,	KC_LCTL,	KC_LSFT,	TT(_DIGITIZER),      KC_NO,	    KC_MS_LEFT, KC_MS_DOWN,	KC_MS_UP,	KC_MS_RIGHT,
	KC_NO,		KC_NO,		KC_NO,		TD(1),	KC_NO,		KC_NO,		KC_WH_L,	KC_WH_D,	KC_WH_U,	KC_WH_R,
	KC_NO,		KC_NO,      KC_NO,      KC_NO,		KC_NO,	    KC_NO,		KC_MS_BTN2,	KC_MS_BTN1,	KC_MS_BTN3, KC_NO
),

/* BUTTON
 *
 * ,----------------------------------.                      ,----------------------------------.
 * | UNDO |  CUT | COPY | PASTE| REDO |                      | REDO | PASTE| COPY | CUT  | UNDO |
 * |------+------+------+------+------|                      |------+------+------+------+------|
 * | SUPR | ALT  | CTRL | SHIFT|      |                      |      |SHIFT | CTRL | ALT  | SUPR |
 * |------+------+------+------+------|  ,-----.    ,-----.  |------+------+------+------+------|
 * | Reset|      |      |      | +1   |  |     |    |     |  | REDO | PASTE| COPY | CUT  | UNDO |
 * `----------------------------------'  `-----'    `-----'  `----------------------------------'
 *          ,-----.   ,--------------------.            ,--------------------.   ,-----.
 *          |     |   | MID | LEFT | RIGHT |            | RIGHT | LEFT | MID |   |     |
 *          `-----'   `--------------------'            `--------------------'   `-----'
 */
[_BUTTON] =  LAYOUT(
	C(KC_Z),C(KC_X),	C(KC_C),	C(KC_V),    C(KC_Y),	C(KC_Y),C(KC_V),    C(KC_C),    C(KC_X),    C(KC_Z),
	KC_LGUI,KC_LALT,	KC_LCTL,	KC_LSFT,    KC_NO,		KC_NO,	KC_RSFT,    KC_RCTL,	KC_RALT,	KC_RGUI,
	C(KC_Z),C(KC_X),	C(KC_C),	C(KC_V),    MACRO_THUMBS_UP,    C(KC_Y),C(KC_V),    C(KC_C),    C(KC_X),    C(KC_Z),
	KC_NO,  KC_MS_BTN3,	KC_MS_BTN1,	KC_MS_BTN2, KC_NO,	    KC_NO,	KC_MS_BTN2,	KC_MS_BTN1,	KC_MS_BTN3, KC_NO
),

 /* MEDIA
  *
  * ,----------------------------------.                      ,----------------------------------.
  * |      |      |      |      |      |                      | RGB T| RGB M| RGB H| RGB S| RGB V|
  * |------+------+------+------+------|                      |------+------+------+------+------|
  * | SUPR | ALT  | CTRL | SHIFT|      |                      |      | PREV | VOL v| VOL ^| NEXT |
  * |------+------+------+------+------|  ,-----.    ,-----.  |------+------+------+------+------|
  * |      |      |      |      |      |  |     |    |     |  |      |      |      |      |      |
  * `----------------------------------'  `-----'    `-----'  `----------------------------------'
  *          ,-----.   ,--------------------.            ,--------------------.   ,-----.
  *          |     |   |  XXX |      |      |            | STOP | PLAY | MUTE |   |     |
  *          `-----'   `--------------------'            `--------------------'   `-----'
  */
 [_MEDIA] = LAYOUT(
 	QK_BOOT,    KC_NO,		TD(2),		TD(3),	    KC_NO,		RGB_TOG,	RGB_MOD,	RGB_HUI,	RGB_SAI,	RGB_VAI,
 	KC_LGUI,	KC_LALT,	KC_LCTL,	KC_LSFT,	KC_NO,		KC_NO,		KC_MPRV,    KC_VOLD,	KC_VOLU,	KC_MNXT,
 	KC_NO,		KC_NO,		KC_NO,		TD(1),	KC_NO,		KC_NO,		KC_NO,	    KC_NO,		KC_NO,		KC_NO,
 	KC_NO,		KC_NO,      KC_NO,      KC_NO,		KC_NO,	    KC_NO,		KC_MSTP,	KC_MPLY,	KC_MUTE,    KC_NO
 ),

 /* NUM
  *
  * ,----------------------------------.                      ,----------------------------------.
  * |  [   |   7  |  8   |   9  |   ]  |                      |      |      |      |      |      |
  * |------+------+------+------+------|                      |------+------+------+------+------|
  * |   ;  |   4  |  5   |   6  |   =  |                      |      |SHIFT | CTRL | ALT  | SUPR |
  * |------+------+------+------+------|  ,-----.    ,-----.  |------+------+------+------+------|
  * |  `   |   1  |  2   |   3  |   \  |  |     |    |     |  |      |      |      |      |      |
  * `----------------------------------'  `-----'    `-----'  `----------------------------------'
  *          ,-----.   ,--------------------.            ,--------------------.   ,-----.
  *          |     |   |  .  |   0   |   -  |            |       | XXXX |     |   |     |
  *          `-----'   `--------------------'            `--------------------'   `-----'
  */
 [_NUM] = LAYOUT(
 	KC_LBRC,	KC_7,	KC_8,	KC_9,	    KC_RBRC,		KC_NO,	    TD(3),	    TD(2),		KC_NO,		QK_BOOT,
 	KC_SCLN,	KC_4,	KC_5,	KC_6,	    KC_EQUAL,		KC_NO,		KC_RSFT,    KC_RCTL,	KC_RALT,	KC_RGUI,
 	KC_GRAVE,	KC_1,	KC_2,	KC_3,		KC_BSLS,		KC_NO,		TD(1),	KC_NO,		KC_NO,		KC_NO,
 	KC_NO,		KC_DOT, KC_0,   KC_MINUS,	KC_NO,	        KC_NO,		KC_NO,	    KC_NO,	    KC_NO,      KC_NO
 ),

 /* SYM
  *
  * ,----------------------------------.                      ,----------------------------------.
  * |   {  |  &   |  *   |  (   |  }   |                      |      |      |      |      |      |
  * |------+------+------+------+------|                      |------+------+------+------+------|
  * |  :   |  $   |  %   |  ^   |  +   |                      |      | SHIFT| CTRL | ALT  | SUPR |
  * |------+------+------+------+------|  ,-----.    ,-----.  |------+------+------+------+------|
  * |  ~   |  !   |  @   |  #   |  |   |  |     |    |     |  |      |      |      |      |      |
  * `----------------------------------'  `-----'    `-----'  `----------------------------------'
  *          ,-----.   ,--------------------.            ,--------------------.   ,-----.
  *          |     |   |  (  |  )    |  _   |            |  XXX  |     |      |   |     |
  *          `-----'   `--------------------'            `--------------------'   `-----'
  */
 [_SYM] = LAYOUT(
 	KC_LCBR,	KC_AMPR,	KC_ASTR,	KC_LPRN,	KC_RCBR,	KC_NO,	    TD(3),	    TD(2),		KC_NO,		QK_BOOT,
 	KC_COLN,	KC_DLR,	    KC_PERC,	KC_CIRC,	KC_PLUS,	KC_NO,		KC_RSFT,    KC_RCTL,	KC_RALT,	KC_RGUI,
 	KC_TILD,	KC_EXLM,	KC_AT,		KC_HASH,	KC_PIPE,	KC_NO,		TD(1),	KC_NO,		KC_NO,		KC_NO,
 	KC_NO,      KC_LPRN,    KC_RPRN,    KC_UNDS,    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO
 ),

 /* FUNC
  *
  * ,----------------------------------.                      ,----------------------------------.
  * | F12  |  F7  |  F8  |  F9  | PRNT |                      |      |      |      |      |   -  |
  * |------+------+------+------+------|                      |------+------+------+------+------|
  * | F11  |  F4  |  F5  |  F6  |SCRLLK|                      |      | SHIFT| CTRL | ALT  | SUPR |
  * |------+------+------+------+------|  ,-----.    ,-----.  |------+------+------+------+------|
  * | F10  |  F1  |  F2  |  F3  | PAUSE|  |     |    |     |  |      |      |      |      |      |
  * `----------------------------------'  `-----'    `-----'  `----------------------------------'
  *          ,-----.   ,--------------------.            ,--------------------.   ,-----.
  *          |     |   | APP | SPACE | TAB  |            |       |      | XXX |   |     |
  *          `-----'   `--------------------'            `--------------------'   `-----'
  */
 [_FUNC] = LAYOUT(
 	KC_F12,		KC_F7,		KC_F8,		KC_F9,	    KC_PSCR,	KC_NO,	    TD(3),	    TD(2),		KC_NO,		QK_BOOT,
 	KC_F11,	    KC_F4,	    KC_F5,	    KC_F6,	    KC_SCRL,	KC_NO,		KC_RSFT,    KC_RCTL,	KC_RALT,	KC_RGUI,
 	KC_F10,		KC_F1,		KC_F2,		KC_F3,		KC_PAUS,	KC_NO,		TD(1),	KC_NO,		KC_NO,		KC_NO,
 	KC_NO,		KC_APP,     KC_SPC,     KC_TAB,		KC_NO,	    KC_NO,		KC_NO,	    KC_NO,	    KC_NO,      KC_NO
 ),

/* DIGITIZER
 *
 * ,----------------------------------.                      ,----------------------------------.
 * |      |      |      |      |      |                      |      |      |      |      |      |
 * |------+------+------+------+------|                      |------+------+------+------+------|
 * | SUPR | ALT  | CTRL | SHIFT| XXXX |                      |      | M <- | M v  |  M ^ | M -> |
 * |------+------+------+------+------|  ,-----.    ,-----.  |------+------+------+------+------|
 * |      |      |      |      |      |  |     |    |     |  |      | W <- | W v  |  W ^ |W ->  |
 * `----------------------------------'  `-----'    `-----'  `----------------------------------'
 *          ,-----.   ,--------------------.            ,--------------------.   ,-----.
 *          |     |   |     |       | XXXX |            | RIGHT | LEFT | MID |   |     |
 *          `-----'   `--------------------'            `--------------------'   `-----'
 */
[_DIGITIZER] = LAYOUT(
	QK_BOOT,    KC_NO,		TD(2),		TD(3),	    KC_NO,		KC_TRNS,	DG_LEFT,	DG_DOWN,	DG_UP,	DG_RIGHT,
	KC_LGUI,	KC_LALT,	KC_LCTL,	KC_LSFT,	KC_NO,      KC_NO,	    DG_LEFT,   DG_DOWN,	DG_UP,	    DG_RIGHT,
	KC_NO,		KC_NO,		KC_NO,		TD(1),	    KC_NO,		KC_NO,		KC_NO,	    KC_NO,	    KC_NO,	    KC_NO,
	DB_TOGG,	KC_NO,      KC_NO,      KC_NO,		KC_NO,	    KC_NO,		KC_MS_BTN2,	KC_MS_BTN1,	KC_MS_BTN3, KC_NO
),
};

layer_state_t layer_state_set_user(layer_state_t layer_state) {
  switch(get_highest_layer(layer_state)) {
    case _DIGITIZER:
      // Reset to the center each time we go into the layer
      dig_y = 0.5;
      dig_x = 0.5;
      y_bound = 1.0;
      x_bound = 1.0;
      break;
  }

  return layer_state;
}

void move_pointer(float x, float y) {
    digitizer_t digitizer_state = digitizer_get_state();
    digitizer_state.contacts[0].type = STYLUS;
    digitizer_state.contacts[0].x = x * DIGITIZER_RESOLUTION_X;
    digitizer_state.contacts[0].y = y * DIGITIZER_RESOLUTION_Y;
    digitizer_state.contacts[0].amplitude = 10;
    digitizer_state.contacts[0].confidence = 1;
    digitizer_set_state(digitizer_state);

    // TODO: I want to "lift" the contact right after we move
    // so that the logs don't get spammed
    digitizer_state.contacts[0].amplitude = 0;
    digitizer_set_state(digitizer_state);
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_layer_lock(keycode, record, LLOCK)) { return false; }
  // Your macros ...
  switch (keycode) {
    case MACRO_SETUP_EDITOR:
      if (record->event.pressed) {
        SEND_STRING("nvim .\n");
        SEND_STRING(":Lazy\n");
        SEND_STRING(":source Session.vim");
      }
      break;
    case MACRO_THUMBS_UP:
      if (record->event.pressed) {
        SEND_STRING("+:+1:\n");
      }
      break;
    case DG_LEFT:
      if (record->event.pressed) {
        dig_x *= 0.5;
        x_bound *= 0.5;
        move_pointer(dig_x, dig_y);
      }
      break;
     case DG_DOWN:
      if (record->event.pressed) {
        dig_y = dig_y + (y_bound - dig_y)/2;
        move_pointer(dig_x, dig_y);
      }
      break;
    case DG_UP:
      if (record->event.pressed) {
        dig_y *= 0.5;
        y_bound *= 0.5;
        move_pointer(dig_x, dig_y);
      }
      break;
    case DG_RIGHT:
      if (record->event.pressed) {
        dig_x = dig_x + (x_bound - dig_x)/2;
        move_pointer(dig_x, dig_y);
      }
      break;
  }

  return true;
}


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] =   { ENCODER_CCW_CW(G(KC_TAB), RSG(KC_TAB)), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_EXTRA] =  { ENCODER_CCW_CW(G(KC_TAB), RSG(KC_TAB)), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_NAV] =    { },
    [_MOUSE] =  { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(KC_MS_WH_LEFT, KC_MS_WH_RIGHT), ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [_DIGITIZER] ={ },
    [_BUTTON] = { },
    [_MEDIA] =  { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(KC_LEFT, KC_RIGHT), ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [_NUM] =    { },
    [_SYM] =    { },
    [_FUNC] =   { },
};
#endif
