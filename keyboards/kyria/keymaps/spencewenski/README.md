# Spencewenski Kyria Keymap

This is my keymap for the Kyria keyboard.

## HID API
This keymap defines a HID API. The server side of the API is implemented here: https://git.sr.ht/~spencewenski/keyboard_hid

Make sure `RAW_ENABLE = yes` is in the rules.mk

The API notifies the keyboard of what OS it is connected to.
I plan to update the API to notify the keyboard of which application is foreground,
or at least whether the foreground application is a terminal.
