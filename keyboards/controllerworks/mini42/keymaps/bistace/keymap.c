/*
 * Copyright 2022 Kevin Gee <info@controller.works>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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


typedef struct {
  bool is_press_action;
  int state;
} tap;

//Define a type for as many tap dance states as you need
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3
};

//Our custom tap dance key; add any other tap dance keys to this enum 
enum {
  A_LAYR = 0,
  O_LAYR = 1,
  R_CTRL = 2,
  I_CTRL = 3, 
};

//Declare the functions to be used with your tap dance key(s)
//Function associated with all tap dances
int cur_dance (tap_dance_state_t *state);

//Functions associated with individual tap dances
void ql_finished (tap_dance_state_t *state, void *user_data);
void ql_reset (tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_A,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_H,    KC_J,    KC_L,    KC_U,   KC_Y,   KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        MO(1),    TD(A_LAYR),    TD(R_CTRL),    KC_S,    KC_T,    KC_G,                      KC_SCLN,    KC_N,    KC_E,    TD(I_CTRL),   TD(O_LAYR),   KC_LBRC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_NO,   MO(2),  KC_SPC,     KC_ENT,   MO(3),   KC_NO
                                      //`--------------------------'  `--------------------------'
  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO, KC_QUOT,   KC_UP,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                       KC_NUHS, KC_LEFT, KC_DOWN,KC_RIGHT,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,   KC_NO
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO, KC_AMPR, KC_ASTR, KC_LPRN,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,  KC_DLR, KC_PERC, KC_CIRC,   LSFT(KC_COMM),   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO, KC_EXLM,   KC_AT,  KC_HASH,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_NO, KC_TRNS,   KC_NO,    KC_RPRN,   KC_NO,   KC_NO
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, RALT(KC_0), KC_RBRC, KC_5, KC_MINS, RALT(KC_7),                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO, KC_EQL, RALT(KC_3), RALT(KC_5), RALT(KC_MINS), LSFT(KC_EQL),                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO, RALT(KC_8), RALT(KC_6), RALT(KC_4), RALT(KC_EQL), RALT(KC_2),                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,   KC_NO
                                      //`--------------------------'  `--------------------------'
  ),

  [4] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_NO,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO, KC_TRNS,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                      KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_TRNS,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,   KC_NO
                                      //`--------------------------'  `--------------------------'
  ),
  
/*  [5] = LAYOUT_split_3x6_3(
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX,                       XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
),*/


};

/*
  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,   KC_NO
                                      //`--------------------------'  `--------------------------'
  ),
  
*/

//Determine the current tap dance state
int cur_dance (tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) {
      return SINGLE_TAP;
    } else {
      return SINGLE_HOLD;
    }
  } 
  else return SINGLE_TAP;
}

//Initialize tap structure associated with example tap dance key
static tap a_o_ql_tap_state = {
  .is_press_action = true,
  .state = 0
};

static tap r_i_ql_tap_state = {
  .is_press_action = true,
  .state = 0
};

//Functions that control what our tap dance key does
void A_finished (tap_dance_state_t *state, void *user_data) {
  a_o_ql_tap_state.state = cur_dance(state);
  switch (a_o_ql_tap_state.state) {
    case SINGLE_TAP: 
      tap_code(KC_Q); 
      break;
    case SINGLE_HOLD: 
      layer_on(4); 
      break;
  }
}

void O_finished (tap_dance_state_t *state, void *user_data) {
  a_o_ql_tap_state.state = cur_dance(state);
  switch (a_o_ql_tap_state.state) {
    case SINGLE_TAP: 
      tap_code(KC_O); 
      break;
    case SINGLE_HOLD: 
      layer_on(4); 
      break;
  }
}

void R_ctrl_finished (tap_dance_state_t *state, void *user_data) {
  r_i_ql_tap_state.state = cur_dance(state);
    switch (r_i_ql_tap_state.state) {
        case SINGLE_TAP:
            register_code16(KC_R);
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        default:
            break;
    }
}

void I_ctrl_finished (tap_dance_state_t *state, void *user_data) {
  r_i_ql_tap_state.state = cur_dance(state);
    switch (r_i_ql_tap_state.state) {
        case SINGLE_TAP:
            register_code16(KC_I);
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        default:
            break;
    }
}

void A_O_reset (tap_dance_state_t *state, void *user_data) {
  //if the key was held down and now is released then switch off the layer
  if (a_o_ql_tap_state.state==SINGLE_HOLD) {
    layer_off(4);
  }
  a_o_ql_tap_state.state = 0;
}

void R_ctrl_reset (tap_dance_state_t *state, void *user_data) {
  switch (r_i_ql_tap_state.state) {
    case SINGLE_TAP:
      unregister_code16(KC_R);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_LCTL)); // for a layer-tap key, use `layer_off(_MY_LAYER)` here
      break;
  }
}

void I_ctrl_reset (tap_dance_state_t *state, void *user_data) {
  switch (r_i_ql_tap_state.state) {
    case SINGLE_TAP:
      unregister_code16(KC_I);
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_LCTL)); // for a layer-tap key, use `layer_off(_MY_LAYER)` here
      break;
  }
}

//Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
  [A_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, A_finished, A_O_reset),
  [O_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, O_finished, A_O_reset),
  [R_CTRL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, R_ctrl_finished, R_ctrl_reset),
  [I_CTRL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, I_ctrl_finished, I_ctrl_reset),
};
