/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
#include "raw_hid.h"

enum layers {
    _DEFAULT = 0,
    _LAYER_2,
    _LAYER_3,
    _LAYER_4
};

enum CustomKeycodes {
    CustomCopy = SAFE_RANGE,    // 'copy' that works on all OS's
    CustomPaste,                // 'paste' that works on all OS's
    CustomCut,                  // 'cut' that works on all OS's
    CustomCtrl,                 // Change between ctrl and gui depending on OS (linux/windows vs mac, respectively)
    CustomAlt,                  // alt or gui, depending on the os (for application/window switching)
    GitStatus,
    GitDiff,
    GitAdd,
    GitCommit,
    GitPull,
    ExitVim,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Base Layer: QWERTY
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |        |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |        |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |   Z  |   X  |   C  |   V  |   B  |      |      |  |      |      |   N  |   M  | ,  < | . >  | /  ? |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
    [_DEFAULT] = LAYOUT(
      _______,    KC_Q,   KC_W,   KC_E,    KC_R,    KC_T,                                           KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,    _______,
      LALT_T(KC_ESC),   KC_A,   KC_S,   KC_D,    KC_F,    KC_G,                                           KC_H,     KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT,    KC_Z,   KC_X,   KC_C,    KC_V,    KC_B,       _______, _______, _______, _______, KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SFT_T(KC_MINS),
                                  KC_LCTL, LT(_LAYER_4, KC_HOME), CustomCtrl, LT(_LAYER_2, KC_SPC),  LT(_LAYER_3, KC_TAB),  LT(_LAYER_3, KC_BSPC), LT(_LAYER_2, KC_ENT),  KC_DEL,  LT(_LAYER_4, KC_END), KC_LGUI
    ),
    /*
     * Symbols
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
     [_LAYER_2] = LAYOUT(
             _______, _______, KC_PERC, KC_GRV,  CustomAlt, KC_TAB,                                             KC_AMPR, KC_LCBR, KC_RCBR, KC_LT,   KC_GT,   _______,
             _______, _______, _______, KC_AT,   KC_TILD, KC_CIRC,                                              KC_PIPE, KC_LPRN, KC_RPRN, KC_HASH, KC_COLN, KC_DQUO,
             _______, _______, CustomCut, CustomCopy, CustomPaste, _______, _______, _______, _______, _______, KC_EXLM, KC_LBRC, KC_RBRC, KC_DLR,  KC_QUES, _______,
                                        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
     ),
    /*
     * Placeholder
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
    [_LAYER_3] = LAYOUT(
            _______, _______, KC_F1, KC_F2, KC_F3, KC_F4,                                     KC_0,    KC_1, KC_2, KC_3, KC_EQL, _______,
            _______, _______, KC_F5, KC_F6, KC_F7, KC_F8,                                     KC_MINS, KC_4, KC_5, KC_6, KC_PLUS, _______,
            _______, _______, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______, _______, _______, KC_SLSH, KC_7, KC_8, KC_9, KC_ASTR, _______,
                                       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    /*
     * Placeholder
     *
     * ,-------------------------------------------.                              ,-------------------------------------------.
     * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        |      |      |      |      |      |  |      |      |      |      |      |
     *                        `----------------------------------'  `----------------------------------'
     */
    [_LAYER_4] = LAYOUT(
            _______, _______, GitPull, GitDiff, GitStatus, ExitVim,                                     _______, _______, _______, _______, _______, _______,
            _______, _______, _______, GitCommit, GitAdd, _______,                                     KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
//    /*
//     * Layer template
//     *
//     * ,-------------------------------------------.                              ,-------------------------------------------.
//     * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//     * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//     * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//     * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//     * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//     * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//     *                        |      |      |      |      |      |  |      |      |      |      |      |
//     *                        |      |      |      |      |      |  |      |      |      |      |      |
//     *                        `----------------------------------'  `----------------------------------'
//     */
//    [_TEMPLATE] = LAYOUT(
//            _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//            _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//    ),

};


#ifdef RAW_ENABLE
/*
Below is the layout of data sent in the HID API.

Byte 0:         HIDCommand -- A value in the HIDCommand enum.
Byte 1..N:      Command parameters -- The parameter(s) to the first HIDCommand.
Byte N+1:       HIDCommand -- A value in the HIDCommand enum.
Byte N+2..M:    Command parameters - The parameter(s) to the second HIDCommand.
etc
*/

/*
The commands available in the HID API.
*/
enum HIDCommand {
    // Command to notify QMK of what OS is running on the connected computer.
    // Takes a single parameter.
    UpdateOS = 0x1,
    // Command to notify QMK of what the foreground application is.
    // Takes a single parameter.
    UpdateForegroundApp = 0x2,
    // The end of the data in the interface
    DataEnd = 0xFF,
};

/*
Possible values for the parameter provided to the UpdateOS command.
*/
enum OS {
    Linux = 0x1,
    Windows = 0x2,
    Mac = 0x3,
    OtherOS = 0xFF,
};

/*
Possible values for the parameter provided to the UpdateForegroundApp command.
The API only supports specific applications for which special behavior is desired.
*/
enum App {
    /*
    A terminal application.
    */
    Terminal = 0x1,
    /*
    Any other application, for which we won't provide special behavior.
    */
    OtherApp = 0xFF,
};

static enum OS currentOS = OtherOS;
static enum App currentApp = OtherApp;

/*
Respond to an update in the OS the keyboard is connected to.
Return the new index value after reading the parameter(s) for this command.
*/
uint8_t update_os(uint8_t *data, uint8_t length, uint8_t index) {
    // The index is already at the correct position for the next
    // data field; check that it's a valid value.
    if (index >= length) {
        return index;
    }
    enum OS os = data[index++];
    switch (os) {
        case Linux:
            currentOS = os;
            break;
        case Windows:
            currentOS = os;
            break;
        case Mac:
            currentOS = os;
            break;
        default:
            currentOS = OtherOS;
            break;
    }
    return index;
}

/*
Respond to a new application becoming foreground.
Return the new index value after reading the parameter(s) for this command.
*/
uint8_t update_app(uint8_t *data, uint8_t length, uint8_t index) {
    if (index >= length) {
        return index;
    }
    enum App app = data[index++];
    switch (app) {
        case Terminal:
            currentApp = app;
            break;
        default:
            currentApp = OtherApp;
            break;
    }
    return index;
}

void handle_commands(uint8_t *data, uint8_t length) {
    int index = 0;
    while (index < length) {
        enum HIDCommand command = data[index++];
        switch (command) {
            case DataEnd:
                // This is the end of the command data, so exit.
                return;
            case UpdateOS:
                index = update_os(data, length, index);
                break;
            case UpdateForegroundApp:
                index = update_app(data, length, index);
                break;
            default:
                // unknown command
                break;
        }
    }
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    handle_commands(data, length);
    // raw_hid_send(data, length);
}
#else
static enum OS currentOS = Linux;       // Default to Linux if HID is not enabled
static enum App currentApp = OtherApp;  // Default to 'other' if HID is not enabled
#endif //RAW_ENABLE

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_status(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _DEFAULT:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LAYER_2:
            oled_write_P(PSTR("Layer 2\n"), false);
            break;
        case _LAYER_3:
            oled_write_P(PSTR("Layer 3\n"), false);
            break;
        case _LAYER_4:
            oled_write_P(PSTR("Layer 4\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }
#ifdef RAW_ENABLE
    oled_write_P(PSTR("OS: "), false);
    switch (currentOS) {
        case Linux:
            oled_write_P(PSTR("Linux\n"), false);
            break;
        case Windows:
            oled_write_P(PSTR("Windows\n"), false);
            break;
        case Mac:
            oled_write_P(PSTR("Mac\n"), false);
            break;
        default:
            oled_write_P(PSTR("Unknown\n"), false);
            break;
    }

    oled_write_P(PSTR("App: "), false);
    switch (currentApp) {
        case Terminal:
            oled_write_P(PSTR("Terminal\n"), false);
            break;
        default:
            oled_write_P(PSTR("Other\n"), false);
            break;
    }
#endif //RAW_ENABLE

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_kyria_logo();
    }
}
#endif //OLED_DRIVER_ENABLE

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}
#endif //ENCODER_ENABLE

void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
    debug_enable=true;
    // debug_matrix=true;
    debug_keyboard=true;
#endif //CONSOLE_ENABLE
}

///////////////////////////////
/// Custom keycode handling ///
///////////////////////////////

// CustomCut
bool handle_custom_cut(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (currentOS) {
        case Linux:
            SEND_STRING(SS_LCTL("x"));
            break;
        case Mac:
            SEND_STRING(SS_LGUI("x"));
            break;
        case Windows:
            SEND_STRING(SS_LCTL("x"));
            break;
        default:
            break;
    }
    return true;
}
// End CustomCut

// CustomCopy
void handle_custom_copy_linux(uint16_t keycode, keyrecord_t *record) {
    switch (currentApp) {
        case Terminal:
            SEND_STRING(SS_DOWN(X_LCTL)SS_DOWN(X_LSFT)"c"SS_UP(X_LSFT)SS_UP(X_LCTL));
            break;
        default:
            SEND_STRING(SS_LCTL("c"));
            break;
    }
}

bool handle_custom_copy(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (currentOS) {
        case Linux:
            handle_custom_copy_linux(keycode, record);
            break;
        case Mac:
            SEND_STRING(SS_LGUI("c"));
            break;
        case Windows:
            SEND_STRING(SS_LCTL("c"));
            break;
        default:
            break;
    }
    return true;
}
// End CustomCopy


// CustomPaste
void handle_custom_paste_linux(uint16_t keycode, keyrecord_t *record) {
    switch (currentApp) {
        case Terminal:
            SEND_STRING(SS_DOWN(X_LCTL)SS_DOWN(X_LSFT)"v"SS_UP(X_LSFT)SS_UP(X_LCTL));
            break;
        default:
            SEND_STRING(SS_LCTL("v"));
            break;
    }
}

bool handle_custom_paste(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (currentOS) {
        case Linux:
            handle_custom_paste_linux(keycode, record);
            break;
        case Mac:
            SEND_STRING(SS_LGUI("v"));
            break;
        case Windows:
            SEND_STRING(SS_LCTL("v"));
            break;
        default:
            break;
    }
    return true;
}
// End CustomPaste


// CustomCtrl
bool handle_custom_ctrl(uint16_t keycode, keyrecord_t *record) {
    uint8_t kc;
    switch (currentOS) {
        case Linux:
            kc = KC_LCTRL;
            break;
        case Mac:
            kc = KC_LGUI;
            break;
        case Windows:
            kc = KC_LCTRL;
            break;
        default:
            return true;
            break;
    }
    if (record->event.pressed) {
        register_code(kc);
    } else {
        unregister_code(kc);
    }
    return true;
}
// End CustomCtrl


// CustomAlt
bool handle_custom_alt(uint16_t keycode, keyrecord_t *record) {
    uint8_t kc;
    switch (currentOS) {
        case Linux:
            kc = KC_LALT;
            break;
        case Mac:
            kc = KC_LGUI;
            break;
        case Windows:
            kc = KC_LALT;
            break;
        default:
            break;
    }
    if (record->event.pressed) {
        register_code(kc);
    } else {
        unregister_code(kc);
    }
    return true;
}
// End CustomAlt

// Basic macros
bool handle_basic_macros(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }
    switch (keycode) {
        // Git
        case GitStatus:
            SEND_STRING("git status"SS_TAP(X_ENT));
            break;
        case GitDiff:
            SEND_STRING("git diff"SS_TAP(X_ENT));
            break;
        case GitAdd:
            SEND_STRING("git add ."SS_TAP(X_ENT));
            break;
        case GitCommit:
            SEND_STRING("git commit"SS_TAP(X_ENT));
            break;
        case GitPull:
            SEND_STRING("git pull"SS_TAP(X_ENT));
            break;
        // Vim
        case ExitVim:
            SEND_STRING(SS_TAP(X_ESC)":wq"SS_TAP(X_ENT));
            break;
    }
    return true;
}
// End basic macros

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CustomCopy:
            return handle_custom_copy(keycode, record);
        case CustomPaste:
            return handle_custom_paste(keycode, record);
        case CustomCut:
            return handle_custom_cut(keycode, record);
        case CustomCtrl:
            return handle_custom_ctrl(keycode, record);
        case CustomAlt:
            return handle_custom_alt(keycode, record);
        default:
            return handle_basic_macros(keycode, record);
    }
    return true;
};

///////////////////////////////////
/// End custom keycode handling ///
///////////////////////////////////
