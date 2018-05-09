// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for 

// keycode definitions: https://github.com/keyboardio/Kaleidoscope/wiki/Keycode-meanings
// Empty template for keymap: https://community.keyboard.io/t/boilerplate-for-empty-layer/760/2?u=rumpel

/* Modifiers (in file key_defs.h):
#define LCTRL(k)  ((Key) { k.keyCode, k.flags | CTRL_HELD })
#define LALT(k)   ((Key) { k.keyCode, k.flags | LALT_HELD })
#define RALT(k)   ((Key) { k.keyCode, k.flags | RALT_HELD })    // AltGr
#define LSHIFT(k) ((Key) { k.keyCode, k.flags | SHIFT_HELD })
#define LGUI(k)   ((Key) { k.keyCode, k.flags | GUI_HELD })
*/

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "version 2"
#endif

/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 01's firmware
 */


// The Kaleidoscope core
#include "Kaleidoscope.h"

#include <Kaleidoscope-Leader.h>

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
// Support for an LED mode that prints the keys you press in letters 4px high
#include "Kaleidoscope-LED-AlphaSquare.h"
// Support for Keyboardio's internal keyboard testing mode
#include "Kaleidoscope-Model01-TestMode.h"

#include "Kaleidoscope-OneShot.h"

#include "Kaleidoscope-TapDance.h"

#include "Kaleidoscope-LED-ActiveModColor.h"

#include "Kaleidoscope-TopsyTurvy.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

// use Syster conjunction with Unicode
// https://github.com/keyboardio/Kaleidoscope-Syster
//#include "Kaleidoscope-Syster.h"


//#define KALEIDOSCOPE_HOSTOS_GUESSER 0
//#include <Kaleidoscope-HostOS.h>
//#include <Kaleidoscope/HostOS-select.h>

#include "Kaleidoscope-Unicode.h"


enum { MACRO_VERSION_INFO,
       MACRO_ANY,
       MACRO_TOGGLE_FACTORY_LAYOUT,
       MACRO_LED_DEACTIVATION,

      
       MACRO_UMLAUT_A,
       MACRO_UMLAUT_CA, // C for capital
       MACRO_UMLAUT_O,
       MACRO_UMLAUT_CO,
       MACRO_UMLAUT_U,
       MACRO_UMLAUT_CU,
       MACRO_UMLAUT_S,

       MACRO_VIELE_GR,
       MACRO_LENNY,
       MACRO_SHRUG,
       MACRO_DISAPPROVAL,

       MACRO_APP_BROWSER_OPEN_SEARCH,

       MACRO_COPY,
       MACRO_CUT,
       MACRO_PASTE,

       ////////////////////////////////////////////////////
       // Emacs Macros
       ////////////////////////////////////////////////////

       MACRO_FOCUS_EMACS,
       
       // Save file macro: sends a long key combo that is translated by autohotkey
       // to the proper save file keyboard shortcut, depending on the currently active
       // program. ("C-x s" in emacs was too cumbersome in the end)
       MACRO_SAVE_FILE,       
       MACRO_ACE_JUMP,
       // Instantly go to prev/next buffer
       MACRO_GOTO_PREV_BUFFER,
       MACRO_GOTO_NEXT_BUFFER,
       MACRO_KILL_BUFFER,

       MACRO_SHOW_BOOKMARKS,
       MACRO_SET_BOOKMARK,
       MACRO_SHOW_BUFFERS,

       MACRO_ENTER_KEY,
       MACRO_ORG_CAPTURE,
       MACRO_ORG_CLOCK_GOTO,
       MACRO_ORG_CLOCK_IN,
       MACRO_ORG_CLOCK_OUT,
       MACRO_EMACS_AGENDA_SEARCH,

       ////////////////////////////////////////////////////
       // Workaround macros
       ////////////////////////////////////////////////////

       // sends '()' and shifts cursor one to the right
       // directoly from the keyboard, since AHK does such
       // a buggy job of it for some reason (and only for
       // the normal parens)
       MACRO_PAREN_PAIR,
       MACRO_BRACKET_PAIR,
       MACRO_CURLYBRACKET_PAIR,
       
       ////////////////////////////////////////////////////
       // App Macros
       ////////////////////////////////////////////////////

       // Foobar2k
       MACRO_APP_FOOBAR2K_UnFOCUS,
       MACRO_APP_FOOBAR2K_SEEK_FW1MIN,
       MACRO_APP_FOOBAR2K_RATE1,
       MACRO_APP_FOOBAR2K_PAUSE,

       ////////////////////////////////////////////////////
       // "Abstract" AHK Command Keys
       // (as opposed to named ones)
       // Their actual function is assigned in AHK
       ////////////////////////////////////////////////////

       MACRO_RFN_PGDN, // RFN+PGDN
       MACRO_RFN_PGUP,  // RFN+PGUP
       MACRO_BUTTERFLY, // butterfly key
       MACRO_LED_KEY,
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


enum TapDanceKey {

  // 2 taps: small and capital umlaute
  AUml,
  OUml,
  UUml,

  // 3 taps (without a function key): umlaute (small and capital)
  // activate starting on the second tap
  AUml2, 
  OUml2,
  UUml2,  
  SUml2,
  
  LeftBrackets,
  RightBrackets,

  // single tap: call helm-filtered-bookmarks
  // double tap: set bookmark
  Bookmarks,

  OrgAgendaAndCapture,
  OrgClocking,

  Butterfly,

  // Because something like Key_Copy hasn't worked yet
  // (maybe it'll work after setting the HostID to Windows or smth)
  CopyCut 
};

// enum { QWERTY, FUNCTION, NUMPAD }; // layers
enum {
  DVORAK,
  //SHIFT,

  // Left FN
  LFN,

  // Right FN
  RFN,

  // For numpad, etc
  LFN2,

  // For app control (foobar2k etc)
  RFN2,
  
  //  FACTORY_QWERTY,
  //  FACTORY_FN
};

KEYMAPS(
        
  [DVORAK] = KEYMAP_STACKED
  (___,          Key_1,         Key_2,     Key_3,      Key_4, Key_5, M(MACRO_LED_KEY),
   Key_Backtick, Key_Quote,     Key_Comma, Key_Period, Key_P, Key_Y, M(MACRO_PAREN_PAIR),
   M(MACRO_PASTE),   Key_A,         Key_O,     Key_E,      Key_U, Key_I,
   TD(TapDanceKey::CopyCut), Key_Semicolon, Key_Q,     Key_J,      Key_K, Key_X, Key_Escape,
   OSM(LeftShift), Key_Space, Key_LeftAlt, ShiftToLayer(LFN2),
   ShiftToLayer(LFN),

   Key_RightGui,   Key_6, Key_7, Key_8, Key_9, Key_0, XXX,
   M(MACRO_ENTER_KEY),      Key_F, Key_G, Key_C, Key_R, Key_L, Key_Slash,
                   Key_D, Key_H, Key_T, Key_N, Key_S, Key_Minus,
   M(MACRO_BUTTERFLY),   Key_B, Key_M, Key_W, Key_V, Key_Z, Key_Equals,
   ShiftToLayer(RFN2), Key_Enter, Key_Backspace, Key_RightControl,
   ShiftToLayer(RFN)),

  //  [SHIFT] = KEYMAP_STACKED // This one is not used...
  //  (___,          Key_1,         Key_2,     Key_3,      Key_4, Key_5, Key_LEDEffectNext,
    //   Key_Backtick, Key_Quote,     Key_Comma, Key_Period, Key_P, Key_Y, TOPSY(9),
    //   Key_Tab,   Key_A,         Key_O,     Key_E,      Key_U, Key_I,
    //   Key_PageDown, Key_Semicolon, Key_Q,     Key_J,      Key_K, Key_X, Key_Escape,
    //   OSM(LeftControl), Key_Space, OSM(LeftAlt), ___,
    //   ShiftToLayer(LFN),
    //
    //   M(MACRO_ANY),   Key_6, Key_7, Key_8, Key_9, Key_0, XXX,
    //   TOPSY(0),/*TD(RightBrackets),*/      Key_F, Key_G, Key_C, Key_R, Key_L, Key_Slash,
    //                   Key_D, Key_H, Key_T, Key_N, Key_S, Key_Minus,
    //   Key_RightAlt,   Key_B, Key_M, Key_W, Key_V, Key_Z, Key_Equals,
    //   Key_RightGui, Key_Enter, Key_Backspace, OSM(RightShift),
    //   ShiftToLayer(RFN)),

  [LFN] =  KEYMAP_STACKED
  (LGUI(Key_L),  ___,                                     ___,               ___,     ___,          ___,            ___,
   ___,          ___,                                     ___,               ___,     ___,          M(MACRO_PASTE), ___,
   Key_PageUp,   Key_Home,                                M(MACRO_ACE_JUMP), Key_End, Key_Tab,      ___,
   Key_PageDown, ___,                                     ___,               ___,     LCTRL(Key_K), LCTRL(Key_X),   ___,
   ___,          LALT(Key_Space)/*emacs:just-one-space*/, ___,               ___,
   ___,

   ___,                   ___,                        ___,              ___,           ___,            ___,                ___,
   TD(TapDanceKey::RightBrackets), ___,                        LCTRL(Key_Space), Key_UpArrow,   ___,            LCTRL(Key_L),       ___,
                                   LCTRL(Key_D),               Key_LeftArrow,    Key_DownArrow, Key_RightArrow, M(MACRO_SAVE_FILE), ___,
   ___,                            TD(TapDanceKey::Bookmarks), ___,              M(MACRO_CUT),  ___,            Key_Backslash,      Key_Pipe,
   ___,                            LCTRL(Key_Enter),           Key_Delete,       ___,
   ___),

  [RFN] =  KEYMAP_STACKED
  (LGUI(Key_L),       Key_F1,                Key_F2,                Key_F3,                    Key_F4,                    Key_F5, M(MACRO_CURLYBRACKET_PAIR),
   ___,               ___,                   ___,                   M(MACRO_FOCUS_EMACS),      ___,                       ___,    ___, //TD(TapDanceKey::RightBrackets),
   M(MACRO_RFN_PGUP), TD(TapDanceKey::AUml), TD(TapDanceKey::OUml), ___,                       TD(TapDanceKey::UUml),     M(MACRO_UMLAUT_S),
   M(MACRO_RFN_PGDN), ___,                   M(MACRO_KILL_BUFFER),  M(MACRO_GOTO_PREV_BUFFER), M(MACRO_GOTO_NEXT_BUFFER), ___,    M(MACRO_BRACKET_PAIR),
   Key_mouseBtnR,     Key_mouseBtnL,         Key_mouseBtnR,         ___,
   ___,
 
   ___, Key_F6,     Key_F7,      Key_F8,      Key_F9,                       Key_F10, Key_F11,
   ___, ___,        ___,         Key_mouseUp, LCTRL(Key_R),                 ___/*LEAD(0)*/,     Key_F12,
        ___, Key_mouseL, Key_mouseDn, Key_mouseR,  M(MACRO_EMACS_AGENDA_SEARCH), ___,
   ___, ___,        ___,         ___,         ___,                          ___,     ___,
   ___, ___,        ___,         ___,
   ___),  

  [LFN2] =  KEYMAP_STACKED 
  (___, ___, ___, ___, ___, ___, Key_LEDEffectNext,
   Key_Backtick, ___, ___, ___, ___, ___, Key_LeftBracket,
   ___, M(MACRO_APP_BROWSER_OPEN_SEARCH), M(MACRO_APP_FOOBAR2K_UnFOCUS), M(MACRO_APP_FOOBAR2K_PAUSE), M(MACRO_APP_FOOBAR2K_SEEK_FW1MIN), M(MACRO_APP_FOOBAR2K_RATE1),
   ___, LSHIFT(Key_Semicolon), ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   M(MACRO_VERSION_INFO),  ___,                ___,   ___,   ___,   ___,                ___,
   Key_RightBracket,       Key_KeypadAdd,      Key_4, Key_5, Key_6, Key_Equals,         ___,
                           Key_0,              Key_1, Key_2, Key_3, Key_KeypadMultiply, ___,
   ___,                    Key_KeypadSubtract, Key_7, Key_8, Key_9, Key_KeypadDivide,   ___,
   Key_Space, Key_Enter, ___, Key_Space,
   ___),

  [RFN2] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, M(MACRO_LED_DEACTIVATION),
   ___, ___, ___, ___, ___, ___, ___,
   ___, M(MACRO_APP_BROWSER_OPEN_SEARCH), M(MACRO_APP_FOOBAR2K_UnFOCUS), M(MACRO_APP_FOOBAR2K_PAUSE), M(MACRO_APP_FOOBAR2K_SEEK_FW1MIN), M(MACRO_APP_FOOBAR2K_RATE1),
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,
 
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
        ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___),  
  
  //  [FACTORY_QWERTY] = KEYMAP_STACKED
  //  (LGUI(Key_L),          Key_1, Key_2, Key_3, Key_4, Key_5, Key_LEDEffectNext,
    //   Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
    //   Key_PageUp,   Key_A, Key_S, Key_D, Key_F, Key_G,
    //   Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
    //   Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
    //   ShiftToLayer(FACTORY_FN),
    //
    //   M(MACRO_ANY),  Key_6, Key_7, Key_8,     Key_9,         Key_0,         XXX,
    //   Key_Enter,     Key_Y, Key_U, Key_I,     Key_O,         Key_P,         Key_Equals,
    //                  Key_H, Key_J, Key_K,     Key_L,         Key_Semicolon, Key_Quote,
    //   Key_RightAlt,  Key_N, Key_M, Key_Comma, Key_Period,    Key_Slash,     Key_Minus,
    //   Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
    //   ShiftToLayer(FACTORY_FN)),
  //
  //  [FACTORY_FN] =  KEYMAP_STACKED
  //  (___,      Key_F1,           Key_F2,      Key_F3,     Key_F4,        Key_F5,           XXX,
    //   Key_Tab,  ___,              Key_mouseUp, ___,        Key_mouseBtnR, Key_mouseWarpEnd, Key_mouseWarpNE,
    //   Key_Home, Key_mouseL,       Key_mouseDn, Key_mouseR, Key_mouseBtnL, Key_mouseWarpNW,
    //   Key_End,  Key_PrintScreen,  Key_Insert,  ___,        Key_mouseBtnM, Key_mouseWarpSW,  Key_mouseWarpSE,
    //   ___, Key_Delete, ___, ___,
    //   ___,
    //
    //   Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
    //   Consumer_PlaySlashPause,    Consumer_ScanNextTrack, Key_LeftCurlyBracket,     Key_RightCurlyBracket,    Key_LeftBracket, Key_RightBracket, Key_F12,
    //                               Key_LeftArrow,          Key_DownArrow,            Key_UpArrow,              Key_RightArrow,  ___,              ___,
    //   Key_PcApplication,          Key_Mute,               Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,             Key_Backslash,    Key_Pipe,
    //   ___, ___, Key_Enter, ___,
    //   ___)

 	) // KEYMAPS(
 

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    //Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
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

//static void toggleFactoryLayout(uint8_t keyState) {
  //  if (!keyToggledOn(keyState))
     //    return;
  //
     //  if (Layer.isOn(DVORAK)) {
    //    Layer.move(FACTORY_QWERTY);
    //  } else {
    //    Layer.move(DVORAK);
    //  }
  //}

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

/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */


//#define FNTOAHK(KEY) MACRODOWN(D(RightGui), D(RightControl), T(KEY), U(RightControl), U(RightGui))
//#define FNtoAHK(N1, N2, N3) MACRODOWN(T(F12), T(N1), T(N2), T(N3))
#define FNtoAHK(N1, N2) MACRODOWN(T(F13), T(N1), T(N2))

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

  case MACRO_VERSION_INFO:
    versionInfoMacro(keyState);
    break;

  case MACRO_ANY:
    anyKeyMacro(keyState, Key_O);
    break;

    //  case MACRO_TOGGLE_FACTORY_LAYOUT:
    //    toggleFactoryLayout(keyState);
    //    break;

  case MACRO_LED_DEACTIVATION:
    deactivateLeds(keyState);
    break;

  case MACRO_PAREN_PAIR:
    return MACRODOWN(T(LeftParen), T(RightParen), T(LeftArrow));

  case MACRO_BRACKET_PAIR:
    return MACRODOWN(T(LeftBracket), T(RightBracket), T(LeftArrow));

  case MACRO_CURLYBRACKET_PAIR:
    return MACRODOWN(T(LeftCurlyBracket), T(RightCurlyBracket), T(LeftArrow));

  case MACRO_SAVE_FILE:
    return FNtoAHK(0,0);

    // Note: Umlaute are not realized through AHK anymore.
    // I installed a special Dvorak-based European keyboard layout
    // on Windows, via which umlaute are activated holding the
    // AltGr (RightAlt) key
  case MACRO_UMLAUT_S:
    //return FNtoAHK(0,1);
    return MACRODOWN(D(RightAlt), T(S), U(RightAlt));
  case MACRO_UMLAUT_A:
    //return FNtoAHK(0,2);
    return MACRODOWN(D(RightAlt), T(A), U(RightAlt));

  case MACRO_UMLAUT_CA:
    //return FNtoAHK(0,3);
    return MACRODOWN(D(RightAlt), D(LeftShift), T(A), U(LeftShift), U(RightAlt));

  case MACRO_UMLAUT_O:
    //return FNtoAHK(0,4);
    return MACRODOWN(D(RightAlt), T(O), U(RightAlt));
    //unicode(0x00d6, keyState);

  case MACRO_UMLAUT_CO:
    //return FNtoAHK(0,5);
    return MACRODOWN(D(RightAlt), D(LeftShift), T(O), U(LeftShift), U(RightAlt));

  case MACRO_UMLAUT_U:
    //return FNtoAHK(0,6);
    return MACRODOWN(D(RightAlt), T(U), U(RightAlt));

  case MACRO_UMLAUT_CU:
    //return FNtoAHK(0,7);
    return MACRODOWN(D(RightAlt), D(LeftShift), T(U), U(LeftShift), U(RightAlt));

//  case MACRO_VIELE_GR:
//    return FNtoAHK(0,8);
//
//  case MACRO_LENNY:
//    return FNtoAHK(0,9);
//
//  case MACRO_SHRUG:
//    //return FNTOAHK(TODO);
//
//  case MACRO_DISAPPROVAL:
//    return FNTOAHK(F);

  case MACRO_ACE_JUMP:
    return FNtoAHK(0,8);

  case MACRO_GOTO_PREV_BUFFER:
    return FNtoAHK(0,9);

  case MACRO_GOTO_NEXT_BUFFER:
    return FNtoAHK(1,0);

  case MACRO_SHOW_BOOKMARKS:
    return FNtoAHK(1,1);

  case MACRO_SET_BOOKMARK:
    return FNtoAHK(1,2);

  case MACRO_APP_FOOBAR2K_SEEK_FW1MIN:
    return FNtoAHK(1,3);

  case MACRO_APP_FOOBAR2K_RATE1:
    return FNtoAHK(1,4);

    case MACRO_APP_FOOBAR2K_PAUSE:
    return FNtoAHK(1,5);

  case MACRO_APP_BROWSER_OPEN_SEARCH:
    return FNtoAHK(1,6);

  case MACRO_SHOW_BUFFERS:
    return FNtoAHK(1,7);

  case MACRO_FOCUS_EMACS:
    return FNtoAHK(1,8);

  case MACRO_KILL_BUFFER:
    return FNtoAHK(1,9);

  case MACRO_ENTER_KEY:
    return FNtoAHK(2,0);

  case MACRO_ORG_CAPTURE:
    return FNtoAHK(2,1);

  case MACRO_ORG_CLOCK_GOTO:
    return FNtoAHK(2,2);

  case MACRO_ORG_CLOCK_IN:
    return FNtoAHK(2,3);

  case MACRO_ORG_CLOCK_OUT:
    return FNtoAHK(2,4);

  case MACRO_APP_FOOBAR2K_UnFOCUS:
    return FNtoAHK(2,5);

  case MACRO_COPY:
    return FNtoAHK(2,6);

  case MACRO_CUT:
    return FNtoAHK(2,7);

  case MACRO_PASTE:
    return FNtoAHK(2,8);

  case MACRO_RFN_PGDN:
    return FNtoAHK(2,9);

  case MACRO_RFN_PGUP:
    return FNtoAHK(3,0);

  case MACRO_BUTTERFLY:
    return FNtoAHK(3,1);

  case MACRO_EMACS_AGENDA_SEARCH:
    return FNtoAHK(3,2);

  case MACRO_LED_KEY:
    return FNtoAHK(3,3);    
    
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

void tapDanceAction(uint8_t tap_dance_index, byte row, byte col, uint8_t tap_count,
                    kaleidoscope::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_index) {
    case TapDanceKey::LeftBrackets: {
      return tapDanceActionKeys(tap_count, tap_dance_action, M(MACRO_PAREN_PAIR), M(MACRO_BRACKET_PAIR), M(MACRO_CURLYBRACKET_PAIR));
    }
    case TapDanceKey::RightBrackets: {
      return tapDanceActionKeys(tap_count, tap_dance_action, Key_RightParen, Key_RightBracket, Key_RightCurlyBracket);
    }      

    case TapDanceKey::AUml: {
      return tapDanceActionKeys(tap_count, tap_dance_action, M(MACRO_UMLAUT_A), M(MACRO_UMLAUT_CA));
    }
    case TapDanceKey::OUml: {
      return tapDanceActionKeys(tap_count, tap_dance_action, M(MACRO_UMLAUT_O), M(MACRO_UMLAUT_CO));
    }
    case TapDanceKey::UUml: {
      return tapDanceActionKeys(tap_count, tap_dance_action, M(MACRO_UMLAUT_U), M(MACRO_UMLAUT_CU));
    }

    case TapDanceKey::AUml2: {
       return tapDanceActionKeys(tap_count, tap_dance_action, Key_A, M(MACRO_UMLAUT_A), M(MACRO_UMLAUT_CA));
    }
    case TapDanceKey::OUml2: {
       return tapDanceActionKeys(tap_count, tap_dance_action, Key_O, M(MACRO_UMLAUT_O), M(MACRO_UMLAUT_CO));
    }
    case TapDanceKey::UUml2: {
       return tapDanceActionKeys(tap_count, tap_dance_action, Key_U, M(MACRO_UMLAUT_U), M(MACRO_UMLAUT_CU));
    }
    case TapDanceKey::SUml2: {
       return tapDanceActionKeys(tap_count, tap_dance_action, Key_I, M(MACRO_UMLAUT_S));
    }      
      
    case TapDanceKey::Bookmarks: { // show also buffers
      return tapDanceActionKeys(tap_count, tap_dance_action, M(MACRO_SHOW_BOOKMARKS), M(MACRO_SHOW_BUFFERS), M(MACRO_SET_BOOKMARK));
    }
      //    case TapDanceKey::OrgAgendaAndCapture: {
       //      return tapDanceActionKeys(tap_count, tap_dance_action, M(MACRO_ENTER_KEY), M(MACRO_ORG_CAPTURE));
      //    }
    case TapDanceKey::OrgClocking: {
      return tapDanceActionKeys(tap_count, tap_dance_action, M(MACRO_ORG_CLOCK_GOTO), M(MACRO_ORG_CLOCK_IN), M(MACRO_ORG_CLOCK_OUT));
    }      
    case TapDanceKey::CopyCut: {
      return tapDanceActionKeys(tap_count, tap_dance_action, M(MACRO_COPY), M(MACRO_CUT));
    }      
  }
}

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::HostPowerManagement::Suspend:
    LEDControl.paused = true;
    LEDControl.set_all_leds_to({0, 0, 0});
    LEDControl.syncLeds();
    break;
  case kaleidoscope::HostPowerManagement::Resume:
    LEDControl.paused = false;
    LEDControl.refreshAll();
    break;
  case kaleidoscope::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}



static void leaderA(uint8_t seq_index) {
  Macros.type(PSTR("a "));
}

static void leaderTX(uint8_t seq_index) {
  Macros.type(PSTR("tx "));
}

static const kaleidoscope::Leader::dictionary_t leader_dictionary[] PROGMEM =
  LEADER_DICT({LEADER_SEQ(LEAD(0), Key_A), leaderA},
              {LEADER_SEQ(LEAD(0), Key_T, Key_X), leaderTX});


/** The 'setup' function is one of the two standard Arduino sketch functions.
  * It's called when your keyboard first powers up. This is where you set up
  * Kaleidoscope and any plugins.
  */

void setup() {
  Kaleidoscope.use(
    // The hardware test mode, which can be invoked by tapping Prog, LED and the left Fn button at the same time.
    &TestMode,

    &Leader,
    
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

    //&Unicode,

    &HostPowerManagement,

    &ActiveModColorEffect // needs to go last     
    //    &Syster
  );

  Kaleidoscope.setup();


  Leader.dictionary = leader_dictionary;

  // We configure the AlphaSquare effect to use RED letters
  AlphaSquare.color = CRGB(255, 0, 0);

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);

  // The LED Stalker mode has a few effects. The one we like is
  // called 'BlazingTrail'. For details on other options,
  // see https://github.com/keyboardio/Kaleidoscope-LED-Stalker
  StalkerEffect.variant = STALKER(BlazingTrail);

  // We want the keyboard to be able to wake the host up from suspend.
  HostPowerManagement.enableWakeup();

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();
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
