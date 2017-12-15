// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for 

// keycode definitions: https://github.com/keyboardio/Kaleidoscope/wiki/Keycode-meanings

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif

/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 01's firmware
 */


// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for keys that move the mouse
#include "Kaleidoscope-MouseKeys.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for an "LED off mode"
#include "LED-Off.h"

// Support for the "Boot greeting" effect, which pulses the 'LED' button for 10s
// when the keyboard is connected to a computer (or that computer is powered on)
#include "Kaleidoscope-LEDEffect-BootGreeting.h"

// Support for LED modes that set all LEDs to a single color
#include "Kaleidoscope-LEDEffect-SolidColor.h"

// Support for an LED mode that makes all the LEDs 'breathe'
#include "Kaleidoscope-LEDEffect-Breathe.h"

// Support for an LED mode that makes a red pixel chase a blue pixel across the keyboard
#include "Kaleidoscope-LEDEffect-Chase.h"

// Support for LED modes that pulse the keyboard's LED in a rainbow pattern
#include "Kaleidoscope-LEDEffect-Rainbow.h"

// Support for an LED mode that lights up the keys as you press them
#include "Kaleidoscope-LED-Stalker.h"

// Support for an LED mode that prints the keys you press in letters 4px high
#include "Kaleidoscope-LED-AlphaSquare.h"

// Support for Keyboardio's internal keyboard testing mode
#include "Kaleidoscope-Model01-TestMode.h"

#include "Kaleidoscope-OneShot.h"

#include "Kaleidoscope-TapDance.h"

#include "Kaleidoscope-LED-ActiveModColor.h"

#include "Kaleidoscope-TopsyTurvy.h"

// use Syster conjunction with Unicode
// https://github.com/keyboardio/Kaleidoscope-Syster
//#include "Kaleidoscope-Syster.h"


#define KALEIDOSCOPE_HOSTOS_GUESSER 1
#include <Kaleidoscope-HostOS.h>
#include <Kaleidoscope/HostOS-select.h>

#include "Kaleidoscope-Unicode.h"

/** This 'enum' is a list of all the macros used by the Model 01's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

enum { MACRO_VERSION_INFO,
       MACRO_ANY,
       MACRO_TOGGLE_FACTORY_LAYOUT,
       MACRO_LED_DEACTIVATION,

       // Save file macro: sends a long key combo that is translated by autohotkey
       // to the proper save file keyboard shortcut, depending on the currently active
       // program. ("C-x s" in emacs was too cumbersome in the end)
       MACRO_SAVE_FILE,

       MACRO_UMLAUT_A,
       MACRO_UMLAUT_CA, // C for capital
       MACRO_UMLAUT_O,
       MACRO_UMLAUT_CO,
       MACRO_UMLAUT_U,
       MACRO_UMLAUT_CU,
       MACRO_UMLAUT_S,

       MACRO_VIELE_GRUESSE,
       MACRO_LENNY,
       MACRO_SHRUG,
       MACRO_DISAPPROVAL
     };



/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   the special nature of the PROG key
  *   keeping NUM and FN consistent and accessible on all layers
  *
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  */


enum TapDanceKey { LeftBrackets, RightBrackets };

// enum { QWERTY, FUNCTION, NUMPAD }; // layers
enum { DVORAK, SHIFT, LFN, RFN, FN2, FACTORY_QWERTY, FACTORY_FN };

/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

const Key keymaps[][ROWS][COLS] PROGMEM = {

//  // orgiginal dovark layout
//  [DVORAK] = KEYMAP_STACKED
//  (___,          Key_1,         Key_2,     Key_3,      Key_4, Key_5, Key_LEDEffectNext,
//   Key_Backtick, Key_Quote,     Key_Comma, Key_Period, Key_P, Key_Y, Key_Tab,
//   Key_PageUp,   Key_A,         Key_O,     Key_E,      Key_U, Key_I,
//   Key_PageDown, Key_Semicolon, Key_Q,     Key_J,      Key_K, Key_X, Key_Escape,
//   Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
//   ShiftToLayer(FUNCTION),
//
//   M(MACRO_ANY),   Key_6, Key_7, Key_8, Key_9, Key_0, Key_KeypadNumLock,
//   Key_Enter,      Key_F, Key_G, Key_C, Key_R, Key_L, Key_Slash,
//                   Key_D, Key_H, Key_T, Key_N, Key_S, Key_Minus,
//   Key_RightAlt,   Key_B, Key_M, Key_W, Key_V, Key_Z, Key_Equals,
//   Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
//   ShiftToLayer(FUNCTION)),

  [DVORAK] = KEYMAP_STACKED
  (___,          Key_1,         Key_2,     Key_3,      Key_4, Key_5, Key_LEDEffectNext,
   Key_Backtick, Key_Quote,     Key_Comma, Key_Period, Key_P, Key_Y, LSHIFT(Key_9),//TD(LeftBrackets),
   Key_Copy,   Key_A,         Key_O,     Key_E,      Key_U, Key_I,
   Key_Paste, Key_Semicolon, Key_Q,     Key_J,      Key_K, Key_X, Key_Escape,
   OSM(LeftShift), Key_Space, OSM(LeftAlt), ShiftToLayer(FN2),
   ShiftToLayer(LFN),

   M(MACRO_ANY),   Key_6, Key_7, Key_8, Key_9, Key_0, XXX,
   LSHIFT(Key_0),/*TD(RightBrackets),*/      Key_F, Key_G, Key_C, Key_R, Key_L, Key_Slash,
                   Key_D, Key_H, Key_T, Key_N, Key_S, Key_Minus,
   Key_RightAlt,   Key_B, Key_M, Key_W, Key_V, Key_Z, Key_Equals,
   Key_RightGui, Key_Enter, Key_Backspace, OSM(RightControl),
   ShiftToLayer(RFN)),

  [SHIFT] = KEYMAP_STACKED
  (___,          Key_1,         Key_2,     Key_3,      Key_4, Key_5, Key_LEDEffectNext,
   Key_Backtick, Key_Quote,     Key_Comma, Key_Period, Key_P, Key_Y, TOPSY(9),//TD(LeftBrackets),
   Key_Tab,   Key_A,         Key_O,     Key_E,      Key_U, Key_I,
   Key_PageDown, Key_Semicolon, Key_Q,     Key_J,      Key_K, Key_X, Key_Escape,
   OSM(LeftControl), Key_Space, OSM(LeftAlt), ___,
   ShiftToLayer(LFN),

   M(MACRO_ANY),   Key_6, Key_7, Key_8, Key_9, Key_0, XXX,
   TOPSY(0),/*TD(RightBrackets),*/      Key_F, Key_G, Key_C, Key_R, Key_L, Key_Slash,
                   Key_D, Key_H, Key_T, Key_N, Key_S, Key_Minus,
   Key_RightAlt,   Key_B, Key_M, Key_W, Key_V, Key_Z, Key_Equals,
   Key_RightGui, Key_Enter, Key_Backspace, OSM(RightShift),
   ShiftToLayer(RFN)),

  [LFN] =  KEYMAP_STACKED
  (___,      Key_F1,           Key_F2,      Key_F3,     Key_F4,        Key_F5,           M(MACRO_LED_DEACTIVATION),
   Key_Tab,  M(MACRO_UMLAUT_CA),      M(MACRO_UMLAUT_CO), ___,    M(MACRO_UMLAUT_CU), XXX, Key_LeftCurlyBracket,
   Key_PageUp, Key_Home,       M(MACRO_UMLAUT_O), Key_End, Key_Tab/*M(MACRO_UMLAUT_U)*/, M(MACRO_UMLAUT_S),
   Key_PageDown,  Key_PrintScreen,  Key_Insert,  ___,        LCTRL(Key_K), LCTRL(Key_X),  Key_mouseWarpSE,
   ___,  LCTRL(Key_Space), ___, ___,
   ___,

   Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,                 Key_F10,            Key_F11,
   Key_RightCurlyBracket,      XXX,      LCTRL(Key_G),            Key_UpArrow,              XXX,          LCTRL(Key_L)/*for emacs*/,     Key_F12,
                               LCTRL(Key_D)/*for emacs*/,      Key_LeftArrow,            Key_DownArrow,            Key_RightArrow,         M(MACRO_SAVE_FILE), ___,
   Key_PcApplication,          Key_Mute,               Consumer_VolumeDecrement, LCTRL(Key_W), M(MACRO_VIELE_GRUESSE), Key_Backslash,      Key_Pipe,
   ___, ___, Key_Delete, ___,
   ___),

  [RFN] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, M(MACRO_UMLAUT_CA), M(MACRO_UMLAUT_CO), ___, M(MACRO_UMLAUT_CU), LCTRL(Key_Y), ___,
   ___, M(MACRO_UMLAUT_A),  M(MACRO_UMLAUT_O),  ___, M(MACRO_UMLAUT_U),  M(MACRO_UMLAUT_S),
   ___, ___, ___, ___, ___, LCTRL(Key_X), ___,
   ___, ___, ___, ___,
   ___,
 
   ___, ___,           ___,           ___,         ___,          ___,          ___,
   ___, Key_mouseBtnR, Key_mouseBtnL, Key_mouseUp, LCTRL(Key_R), ___,          ___,
        ___,           Key_mouseL,    Key_mouseDn, Key_mouseR,   LCTRL(Key_S), ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___),  

  [FN2] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, Key_LeftBracket,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   M(MACRO_VERSION_INFO),  ___,                ___,   ___,   ___,   ___,                ___,
   Key_RightBracket,       Key_KeypadAdd,      Key_4, Key_5, Key_6, Key_Equals,         ___,
                           Key_0,              Key_1, Key_2, Key_3, Key_KeypadMultiply, ___,
   ___,                    Key_KeypadSubtract, Key_7, Key_8, Key_9, Key_KeypadDivide,   ___,
   Key_Space, Key_Enter, ___, Key_Period,
   ___),
  
  [FACTORY_QWERTY] = KEYMAP_STACKED
  (LGUI(Key_L),          Key_1, Key_2, Key_3, Key_4, Key_5, Key_LEDEffectNext,
   Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
   Key_PageUp,   Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
   Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
   ShiftToLayer(FACTORY_FN),

   M(MACRO_ANY),  Key_6, Key_7, Key_8,     Key_9,         Key_0,         XXX,
   Key_Enter,     Key_Y, Key_U, Key_I,     Key_O,         Key_P,         Key_Equals,
                  Key_H, Key_J, Key_K,     Key_L,         Key_Semicolon, Key_Quote,
   Key_RightAlt,  Key_N, Key_M, Key_Comma, Key_Period,    Key_Slash,     Key_Minus,
   Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
   ShiftToLayer(FACTORY_FN)),

  [FACTORY_FN] =  KEYMAP_STACKED
  (___,      Key_F1,           Key_F2,      Key_F3,     Key_F4,        Key_F5,           XXX,
   Key_Tab,  ___,              Key_mouseUp, ___,        Key_mouseBtnR, Key_mouseWarpEnd, Key_mouseWarpNE,
   Key_Home, Key_mouseL,       Key_mouseDn, Key_mouseR, Key_mouseBtnL, Key_mouseWarpNW,
   Key_End,  Key_PrintScreen,  Key_Insert,  ___,        Key_mouseBtnM, Key_mouseWarpSW,  Key_mouseWarpSE,
   ___, Key_Delete, ___, ___,
   ___,

   Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
   Consumer_PlaySlashPause,    Consumer_ScanNextTrack, Key_LeftCurlyBracket,     Key_RightCurlyBracket,    Key_LeftBracket, Key_RightBracket, Key_F12,
                               Key_LeftArrow,          Key_DownArrow,            Key_UpArrow,              Key_RightArrow,  ___,              ___,
   Key_PcApplication,          Key_Mute,               Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,             Key_Backslash,    Key_Pipe,
   ___, ___, Key_Enter, ___,
   ___)
};

/* Re-enable astyle's indent enforcement */
 // *INDENT-ON*

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
    //Macros.type(PSTR(" (OS: "));
    //Macros.type(HostOS.os());
    //Macros.type(PSTR(")"));
  }
}

/** toggle between my dovark etc layouts and the standard 
 *  querty layout that came with the factory firmware.
 *  
 *  algernon's code, source: 
 *  https://community.keyboard.io/t/borrow-your-laptop/423/3
 */

static void toggleFactoryLayout(uint8_t keyState) {
  if (!keyToggledOn(keyState))
    return;

  if (Layer.isOn(DVORAK)) {
    Layer.move(FACTORY_QWERTY);
  } else {
    Layer.move(DVORAK);
  }
}

static void deactivateLeds(uint8_t keyState) {
  if (!keyToggledOn(keyState))
    return;

  LEDOff.activate();
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.
 *
 * When the 'any key' macro is toggled on, a random alphanumeric key is
 * selected. While the key is held, the function generates a synthetic
 * keypress event repeating that randomly selected key.
 *
 */

static void anyKeyMacro(uint8_t keyState, Key key) {
  static Key lastKey;
  if (keyToggledOn(keyState))
    lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);

  if (keyIsPressed(keyState))
    kaleidoscope::hid::pressKey(key);
  

  //Serial.print(::HostOS::os());
}


static void simulateUmlautUsingWinCompose(uint8_t keyState, Key key) {
  /*static Key lastKey;
  if (keyToggledOn(keyState))
  lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);*/
  if (keyIsPressed(keyState)) {
    kaleidoscope::hid::pressKey(Key_RightGui);
    kaleidoscope::hid::pressKey(key);
    kaleidoscope::hid::pressKey(key);
  }
}



/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */


#define FNTOAHK(KEY) MACRODOWN(D(RightGui), D(RightControl), T(KEY), U(RightControl), U(RightGui))

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

  case MACRO_VERSION_INFO:
    versionInfoMacro(keyState);
    break;

  case MACRO_ANY:
    anyKeyMacro(keyState, Key_O);
    break;

  case MACRO_TOGGLE_FACTORY_LAYOUT:
    toggleFactoryLayout(keyState);
    break;

  case MACRO_LED_DEACTIVATION:
    deactivateLeds(keyState);
    break;


  case MACRO_SAVE_FILE:
    //return MACRODOWN(D(LeftShift), D(LeftAlt), D(LeftGui), D(RightControl), T(S), U(RightControl), U(LeftGui), U(LeftAlt), U(LeftShift));
    //return MACRODOWN(D(RightGui), D(RightControl), T(S), U(RightControl), U(RightGui));
    return FNTOAHK(S);
    break;

  case MACRO_UMLAUT_A:
    return FNTOAHK(A);
    break;

  case MACRO_UMLAUT_CA:
    return FNTOAHK(Quote);
    break;

  case MACRO_UMLAUT_O:
    return FNTOAHK(O);
    //unicode(0x00d6, keyState);
    break;

  case MACRO_UMLAUT_CO:
    return FNTOAHK(Comma);
    break;

  case MACRO_UMLAUT_U:
    return FNTOAHK(U);
    break;

  case MACRO_UMLAUT_CU:
    return FNTOAHK(P);
    break;

  case MACRO_UMLAUT_S:
    return FNTOAHK(I);
    break;

  case MACRO_VIELE_GRUESSE:
    return FNTOAHK(V);
    break;

  case MACRO_LENNY:
    return FNTOAHK(L);
    break;

  case MACRO_SHRUG:
    //return FNTOAHK(TODO);
    break;

  case MACRO_DISAPPROVAL:
    return FNTOAHK(F);
    break;
  }
  
  return MACRO_NONE;
}



// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 01.


static kaleidoscope::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::LEDSolidColor solidBlue(0, 70, 130);
static kaleidoscope::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::LEDSolidColor solidViolet(130, 0, 120);


//void systerAction(kaleidoscope::Syster::action_t action, const char *symbol) {
//  switch (action) {
//  case kaleidoscope::Syster::StartAction:
//    Unicode.type (0x2328);
//    break;
//  case kaleidoscope::Syster::EndAction:
//    handleKeyswitchEvent (Key_Backspace, UNKNOWN_KEYSWITCH_LOCATION, IS_PRESSED | INJECTED);
//    kaleidoscope::hid::sendKeyboardReport ();
//    handleKeyswitchEvent (Key_Backspace, UNKNOWN_KEYSWITCH_LOCATION, WAS_PRESSED | INJECTED);
//    kaleidoscope::hid::sendKeyboardReport ();
//    break;
//  case kaleidoscope::Syster::SymbolAction:
//    Serial.print ("systerAction: symbol=");
//    Serial.println (symbol);
//    if (strcmp (symbol, "coffee") == 0) {
//      Unicode.type (0x2615);
//    }
//    break;
//  }
//}

void tapDanceAction(uint8_t tap_dance_index, uint8_t tap_count,
                    kaleidoscope::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_index) {
  case TapDanceKey::LeftBrackets: {
    if (tap_count < 3) {
      return tapDanceActionKeys(tap_count, tap_dance_action,
                                Key_LeftParen,
                                Key_LeftBracket);
      }
      return;
    }
  }
}

// this makes flux dim up/down.. ALT is still being pressed down with PageUp/Down
// it's the releaseKey that doesn't seem to work
Key customControls(Key mapped_key, byte row, byte col, uint8_t key_state) {
    // If none of the controls are pressed, fall through.useEventHandlerHook
    if (kaleidoscope::hid::wasModifierKeyActive(Key_LeftAlt) ||
        kaleidoscope::hid::wasModifierKeyActive(Key_RightAlt)) {
  
    // If we are idle, fall through
    if (!keyWasPressed(key_state) && !keyIsPressed(key_state))
      return mapped_key;
  
    if (mapped_key == Key_C) {
      // So we are not idle, one of the controls are held
      // Time to release the Kraken, and replace the keys with other ones.
      kaleidoscope::hid::releaseKey(Key_LeftAlt);
      kaleidoscope::hid::releaseKey(Key_RightAlt);
      return Key_PageUp;  
    }
  
    if (mapped_key == Key_T) {
      // So we are not idle, one of the controls are held
      // Time to release the Kraken, and replace the keys with other ones.
      kaleidoscope::hid::releaseKey(Key_LeftAlt);
      kaleidoscope::hid::releaseKey(Key_RightAlt);
      return Key_PageDown;  
    }
  }
  
  return mapped_key; 
}

/** The 'setup' function is one of the two standard Arduino sketch functions.
  * It's called when your keyboard first powers up. This is where you set up
  * Kaleidoscope and any plugins.
  */

void setup() {
  HostOS.os(kaleidoscope::hostos::WINDOWS);

  
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  //Kaleidoscope.useEventHandlerHook(customControls);  

  // Next, tell Kaleidoscope which plugins you want to use.
  // The order can be important. For example, LED effects are
  // added in the order they're listed here.
  Kaleidoscope.use(
    // The hardware test mode, which can be invoked by tapping Prog, LED and the left Fn button at the same time.
    &TestMode,

    &HostOS,

    // LEDControl provides support for other LED modes
    &LEDControl,

    // We start with the LED effect that turns off all the LEDs.
    &LEDOff,

    // The rainbow effect changes the color of all of the keyboard's keys at the same time
    // running through all the colors of the rainbow.
    &LEDRainbowEffect,

    // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
    // and slowly moves the rainbow across your keyboard
    &LEDRainbowWaveEffect,

    // The chase effect follows the adventure of a blue pixel which chases a red pixel across
    // your keyboard. Spoiler: the blue pixel never catches the red pixel
    &LEDChaseEffect,

    // These static effects turn your keyboard's LEDs a variety of colors
    &solidRed, &solidOrange, &solidYellow, &solidGreen, &solidBlue, &solidIndigo, &solidViolet,

    // The breathe effect slowly pulses all of the LEDs on your keyboard
    &LEDBreatheEffect,

    // The AlphaSquare effect prints each character you type, using your
    // keyboard's LEDs as a display
    &AlphaSquareEffect,

    // The stalker effect lights up the keys you've pressed recently
    &StalkerEffect,

    // The numlock plugin is responsible for lighting up the 'numpad' mode
    // with a custom LED effect
    //&NumLock,

    // The macros plugin adds support for macros
    &Macros,

    // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
    &MouseKeys,

    &OneShot,

    &TapDance,

    &Unicode,

    &ActiveModColorEffect // needs to go last     
    //    &Syster
  );

  // While we hope to improve this in the future, the NumLock plugin
  // needs to be explicitly told which keymap layer is your numpad layer
  //NumLock.numPadLayer = FACTORY_NUMPAD;

  // We configure the AlphaSquare effect to use RED letters
  AlphaSquare.color = { 255, 0, 0 };

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);

  // The LED Stalker mode has a few effects. The one we like is
  // called 'BlazingTrail'. For details on other options,
  // see https://github.com/keyboardio/Kaleidoscope-LED-Stalker
  StalkerEffect.variant = STALKER(BlazingTrail);

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();

  MouseKeys.speedDelay = 5;
  MouseKeys.accelDelay = 20;

  OneShot.time_out = 1200;
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}

static void unicode(uint32_t character, uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Unicode.type(character);
  }
}

