// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "M01 firmware version: " __DATE__ " "__TIME__
#endif


/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 01's firmware
 */

#include "secrets_file.h"

// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for storing the keymap in EEPROM
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"

// Support for communicating with the host via a simple Serial protocol
#include "Kaleidoscope-FocusSerial.h"

// Support for keys that move the mouse
#include "Kaleidoscope-MouseKeys.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for "Numpad" mode, which is mostly just the Numpad specific LED mode
//#include "Kaleidoscope-NumPad.h"

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

// Support for shared palettes for other plugins, like Colormap below
#include "Kaleidoscope-LED-Palette-Theme.h"

// Support for an LED mode that lets one configure per-layer color maps
#include "Kaleidoscope-Colormap.h"

// Support for Keyboardio's internal keyboard testing mode
#include "Kaleidoscope-HardwareTestMode.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

// Support for magic combos (key chords that trigger an action)
#include "Kaleidoscope-MagicCombo.h"

// Support for USB quirks, like changing the key state report protocol
#include "Kaleidoscope-USB-Quirks.h"


#include "Kaleidoscope-TopsyTurvy.h"
#include "Kaleidoscope-TapDance.h"

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
       MACRO_UNDO,

       MACRO_AUTOCOMPLETE,

       MACRO_HEATMAP,

       MACRO_MOVE_LINE_UP,
       MACRO_MOVE_LINE_DOWN,

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
       MACRO_DELETE_WINDOW,
       MACRO_FORWARD_DELETE_WORD,
       MACRO_FIND,
       MACRO_FIND_FILE,
       
       MACRO_SHOW_BOOKMARKS,
       MACRO_SET_BOOKMARK,
       MACRO_SHOW_BUFFERS,

       MACRO_ENTER_KEY,
       MACRO_ORG_EMACS_CAPTURE,
       MACRO_EMACS_ORG_REFILE,
       MACRO_ORG_CLOCK_GOTO,
       MACRO_ORG_CLOCK_IN,
       MACRO_ORG_CLOCK_OUT,      
       MACRO_EMACS_AGENDA_SEARCH,
       MACRO_EMACS_MOVE_TO_PREV_MARKED_POS,
       MACRO_EMACS_CcCc,

       MACRO_EMACS_CAPTURE_TODO,
       MACRO_EMACS_CAPTURE_NOTE,
       MACRO_EMACS_CAPTURE_JOURNAL,

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

       MACRO_FOCUS_IDE,

       ////////////////////////////////////////////////////
       // "Abstract" AHK Command Keys
       // (as opposed to named ones)
       // Their actual function is assigned in AHK
       ////////////////////////////////////////////////////

       MACRO_RFN_PGDN, // RFN+PGDN
       MACRO_RFN_PGUP,  // RFN+PGUP
       MACRO_BUTTERFLY, // butterfly key
       MACRO_LED_KEY,


       MACRO_SHUTDOWN,

       MACRO_SMART_ENTER,

       
       ////////////////////////////////////////////////////
       // IDE Development Keys
       ////////////////////////////////////////////////////
       MACRO_DEV_RENAME,
       MACRO_DEV_GENERATE,
       MACRO_DEV_NEW_CLASS,
       MACRO_DEV_COMMENT,
       MACRO_DEV_FIND_IN_PATH,



       ////////////////////////////////////////////////////
       // OTHER
       ////////////////////////////////////////////////////
       MACRO_PRINT_MY_MAIL
     };

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
  *   keeping NUM and FN consistent and accessible on all layers
  *
  * The PROG key is special, since it is how you indicate to the board that you
  * want to flash the firmware. However, it can be remapped to a regular key.
  * When the keyboard boots, it first looks to see whether the PROG key is held
  * down; if it is, it simply awaits further flashing instructions. If it is
  * not, it continues loading the rest of the firmware and the keyboard
  * functions normally, with whatever binding you have set to PROG. More detail
  * here: https://community.keyboard.io/t/how-the-prog-key-gets-you-into-the-bootloader/506/8
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
  *
  */
  
// enum { QWERTY, FUNCTION, NUMPAD }; // layers
enum {
  DVORAK,
  //SHIFT,

  // Left FN
  LFN,

  // Right FN
  RFN,

  LFNandRFN,

  //  AltLayer,
  
  // For numpad, etc
  LFN2,

  // For app control (foobar2k etc)
  RFN2,
  
  //  FACTORY_QWERTY,
  //  FACTORY_FN
};  


/* Key modifiers
LCTRL(k)
LALT(k)
RALT(k)
LSHIFT(k)
LGUI(k)
*/



#ifndef NAMED_HOTKEYS
#define EMACS_JustOneSpace LALT(Key_Space)
#define EMACS_KillLine LCTRL(Key_K)
#define EMACS_Command LALT(Key_X) /* is: M-x */
#define EMACS_SetMark LCTRL(Key_Space)
#define EMACS_CenterScreen LCTRL(Key_L)
#define EMACS_EditLines LCTRL(Key_F14)
#define EMACS_MarkAllLikeThis LCTRL(Key_F15)
#define EMACS_MoveToPrevMarkedPos M(MACRO_EMACS_MOVE_TO_PREV_MARKED_POS)
//#define EMACS_MoveLineUp M(MACRO_MOVE_LINE_UP) //LCTRL(Key_F16) 
//#define EMACS_MoveLineDown M(MACRO_MOVE_LINE_DOWN) //LCTRL(Key_F17)
#define All_MoveLineUp LCTRL(Key_F16)
#define All_MoveLineDown LCTRL(Key_F17)
#define All_CopyLine LCTRL(Key_F18)
#define EMACS_CutLine LCTRL(Key_F19)
#define EMACS_Refile M(MACRO_EMACS_ORG_REFILE)// LCTRL(Key_F20) // use C-c C-w since it's view-dependant (agenda, normal)
#define EMACS_InsertLink LCTRL(Key_F21)
#define EMACS_AceJump M(MACRO_ACE_JUMP)
#define EMACS_SwitchWindow LCTRL(Key_F23) // uses ace-window
#define EMACS_CcCc M(MACRO_EMACS_CcCc) // C-c C-c  
#define EMACS_MarkNextLikeThis LCTRL(Key_F24)
#define EMACS_CaptureTodo M(MACRO_EMACS_CAPTURE_TODO)
#define EMACS_CaptureNote M(MACRO_EMACS_CAPTURE_NOTE)
#define EMACS_CaptureJournal M(MACRO_EMACS_CAPTURE_JOURNAL)
#define EMACS_DeleteWindow M(MACRO_DELETE_WINDOW)
#define EMACS_KillBuffer M(MACRO_KILL_BUFFER)
#define EMACS_ForwardDeleteWord LCTRL(LSHIFT(Key_F7)) // M(MACRO_FORWARD_DELETE_WORD)
#define EMACS_AgendaSearch M(MACRO_EMACS_AGENDA_SEARCH)
#define WINDOWS_Lockscreen LGUI(Key_L)
#define WINDOWS_FocusEmacs LGUI(Key_3) //M(MACRO_FOCUS_EMACS)
#define WINDOWS_FocusChrome LGUI(Key_1)
#define WINDOWS_FocusIDE M(MACRO_FOCUS_IDE)
#define WINDOWS_Shutdown M(MACRO_SHUTDOWN)
#define DEV_FindInPath M(MACRO_DEV_FIND_IN_PATH)
#define All_SaveFile LCTRL(Key_S) //M(MACRO_SAVE_FILE) //LCTRL(Key_S) 
#define All_Copy LCTRL(Key_C) //M(MACRO_COPY)
#define All_Cut LCTRL(Key_X) //M(MACRO_CUT)
#define All_Paste LCTRL(Key_V) //M(MACRO_PASTE)
#define EMACS_KeyboardQuit LCTRL(Key_G) // C-g // lets try C-z for undo (and implicit keyboard-quit)
#define All_Undo LCTRL(Key_Z) // M(MACRO_UNDO)
#define All_SearchForward LCTRL(Key_F) // M(MACRO_FIND)
#define EMACS_SearchBackward LCTRL(Key_R) // Emacs only functionality??

#endif




KEYMAPS
(
        
  [DVORAK] = KEYMAP_STACKED
  (___,                      Key_1,         Key_2,       Key_3,      Key_4, Key_5, M(MACRO_LED_KEY),
   Key_Backtick,             Key_Quote,     Key_Comma,   Key_Period, Key_P, Key_Y, M(MACRO_PAREN_PAIR),
   All_Paste,           Key_A,         Key_O,       Key_E,      Key_U, Key_I,
   TD(TapDanceKey::CopyCut), Key_Semicolon, Key_Q,       Key_J,      Key_K, Key_X, Key_Escape,
   Key_LeftShift,           Key_Space,     Key_LeftAlt, ShiftToLayer(LFN2),
   ShiftToLayer(LFN),

   Key_RightGui,          Key_6,     Key_7,         Key_8, Key_9, Key_0, ___,
   M(MACRO_ENTER_KEY),    Key_F,     Key_G,         Key_C, Key_R, Key_L, Key_Slash,
                          Key_D, Key_H,     Key_T,         Key_N, Key_S, Key_Minus,
   M(MACRO_BUTTERFLY),    Key_B,     Key_M,         Key_W, Key_V, Key_Z, Key_Equals,
   ShiftToLayer(RFN2),    Key_Enter, Key_Backspace, Key_RightControl,
   ShiftToLayer(RFN)),

  [LFN] =  KEYMAP_STACKED
  (WINDOWS_Lockscreen, Key_F1,                Key_F2,                Key_F3,                    Key_F4,                    Key_F5,            ___,
   ___,                ___,                ___,           ___,     ___,            All_Paste, ___,
   ___,                Key_Home,           EMACS_SetMark, Key_End, Key_Tab,        EMACS_AceJump,
   ___,                ___,                ___,           ___,     EMACS_KillLine, ___,            ___,
   ___,                EMACS_JustOneSpace, Key_LeftAlt,           ___,
   ___,

   ___, Key_F6, Key_F7, Key_F8, Key_F9, Key_F10, Key_F11,
   TD(TapDanceKey::RightBrackets), M(MACRO_FIND_FILE),    EMACS_KeyboardQuit,    Key_UpArrow,   ___,            EMACS_CenterScreen,    Key_Backslash,
   EMACS_ForwardDeleteWord, Key_LeftArrow, Key_DownArrow, Key_RightArrow, All_SaveFile,    ___,
   ___,                            TD(TapDanceKey::Bookmarks), ___,           All_Cut,  ___,            M(MACRO_AUTOCOMPLETE), Key_Pipe,
   ___,                           M(MACRO_SMART_ENTER),           Key_Delete,    ___,
   ShiftToLayer(LFNandRFN)),
  
  
  [RFN] = KEYMAP_STACKED
  (WINDOWS_Lockscreen,       Key_F1,                Key_F2,                Key_F3,                    Key_F4,                    Key_F5, M(MACRO_CURLYBRACKET_PAIR),
   ___,               WINDOWS_FocusIDE,                   WINDOWS_FocusChrome,     WINDOWS_FocusEmacs,          WINDOWS_FocusIDE,                       ___,           TD(TapDanceKey::RightBrackets),
   //   M(MACRO_RFN_PGUP), TD(TapDanceKey::AUml), TD(TapDanceKey::OUml), ___,                       TD(TapDanceKey::UUml),     M(MACRO_UMLAUT_S),
   M(MACRO_RFN_PGUP), M(MACRO_UMLAUT_A), M(MACRO_UMLAUT_O), ___, M(MACRO_UMLAUT_U),     M(MACRO_UMLAUT_S),
   M(MACRO_RFN_PGDN), EMACS_SwitchWindow,                   EMACS_KillBuffer,  M(MACRO_GOTO_PREV_BUFFER), M(MACRO_GOTO_NEXT_BUFFER), EMACS_Command, M(MACRO_BRACKET_PAIR),
   Key_mouseBtnR,     Key_mouseBtnL,         Key_mouseBtnR,         ___,
   ShiftToLayer(LFNandRFN),
 
   ___, Key_F6,     Key_F7,      Key_F8,      Key_F9,                       Key_F10, Key_F11,
   ___, ___,        All_Undo,         Key_mouseUp, EMACS_SearchBackward,                 ___,     Key_F12,
        ___, Key_mouseL, Key_mouseDn, Key_mouseR,  All_SearchForward, ___,
   ___, ___,        ___,         ___,         EMACS_MoveToPrevMarkedPos,                          ___,     ___,
   ___, ___,        ___,         ___,
   ___),  

  
  [LFNandRFN] = KEYMAP_STACKED
  (___, ___,              ___, ___,                ___, ___, ___,
   ___, ___,              ___, All_MoveLineUp,   ___, ___, ___,
   ___, EMACS_InsertLink, ___, All_MoveLineDown, ___, ___,
   ___, ___,              ___, EMACS_CaptureJournal,                ___, ___, ___,
   ___, ___,              ___, ___,
   ___,
   
   ___, ___,                    ___,           ___,            ___,          ___, ___,
   ___, EMACS_EditLines,        EMACS_CutLine, All_CopyLine, EMACS_Refile, ___, ___,
        EMACS_MarkAllLikeThis,  ___,           EMACS_CaptureTodo,            EMACS_CaptureNote, EMACS_AgendaSearch, ___,
   ___, EMACS_MarkNextLikeThis, ___,           ___,            ___,          ___, ___,
   ___, ___,                    ___,           ___,

   ___),
  
  
  [LFN2] =  KEYMAP_STACKED 
  (___,          ___,                              ___,                           ___,                         ___,                               ___, Key_LEDEffectNext,
   ___,          ___,                              ___,                           ___,                         ___,                               ___, Key_LeftBracket,
   Key_PageUp,   M(MACRO_APP_BROWSER_OPEN_SEARCH), M(MACRO_APP_FOOBAR2K_UnFOCUS), M(MACRO_APP_FOOBAR2K_PAUSE), M(MACRO_APP_FOOBAR2K_SEEK_FW1MIN), M(MACRO_APP_FOOBAR2K_RATE1),
   Key_PageDown, LSHIFT(Key_Semicolon),            ___,                           ___,                         ___,                               ___, ___,
   ___,          ___,                              ___,                           ___,
   ___,

   M(MACRO_VERSION_INFO),  M(MACRO_PRINT_MY_MAIL),                ___,   ___,   ___,   ___,                ___,
   Key_RightBracket,       Key_KeypadAdd,      Key_4, Key_5, Key_6, Key_Equals,         ___,
                           Key_0,              Key_1, Key_2, Key_3, Key_KeypadMultiply, ___,
   ___,                    Key_KeypadSubtract, Key_7, Key_8, Key_9, Key_KeypadDivide,   ___,
   Key_Space, Key_Enter, ___, Key_Space,
   ___),


  // RFN2 is for development stuff
  [RFN2] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, M(MACRO_LED_DEACTIVATION),
   ___, ___, ___, ___, ___, ___, ___,
   ___, M(MACRO_UMLAUT_CA), M(MACRO_UMLAUT_CO), ___, M(MACRO_UMLAUT_CU), ___, 
   ___, ___, EMACS_DeleteWindow, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, M(MACRO_DEV_GENERATE), M(MACRO_DEV_COMMENT), M(MACRO_DEV_RENAME), ___, ___,
        ___, ___, ___, ___, DEV_FindInPath, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___),  

  //  [AltLayer] = KEYMAP_STACKED // look at how many ALT keys are i am replicating. the only keys that changed are pageUp/Down. Why bother
  //  (___, ___, ___,         ___, ___, ___, ___,
    //   ___, ___, ___,         ___, ___, ___, ___,
    //   ___, ___, ___,         ___, ___, ___,
    //   ___, ___, LALT(Key_Q), ___, ___, ___, ___,
    //   ___, ___, ___,         ___,
    //   ___, 
    //
    //   ___, ___,             ___,                 ___,          ___,         ___,         ___,
    //   ___, ___,             ___,                 Key_PageUp,   ___,         ___,         ___,
    //        LALT(Key_D),     LALT(Key_H),         Key_PageDown, LALT(Key_N), LALT(Key_S), ___,
    //   ___, ___,             ___,                 LALT(Key_W),  ___,         ___,         ___,
    //   ___, LALT(Key_Enter), LALT(Key_Backspace), ___,
    //   ___),

   
   //   ___, ___,             ___,                 ___,            ___,                  ___,         ___,
   //   ___, ___,             ___,                 LALT(Key_PageUp), ___,                  ___,         ___,
   //        LALT(Key_D),     LALT(Key_LeftArrow), LALT(Key_PageDown), LALT(Key_RightArrow), LALT(Key_S), ___,
   //   ___, ___,             ___,                 LALT(Key_W),    ___,                  ___,         ___,
   //   ___, LALT(Key_Enter), ___,                 ___,
   //   ___),

  
) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

static void printMyMail(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR(MY_MAIL));
  }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.
 *
 * When the 'any key' macro is toggled on, a random alphanumeric key is
 * selected. While the key is held, the function generates a synthetic
 * keypress event repeating that randomly selected key.
 *
 */

static void anyKeyMacro(uint8_t keyState) {
  static Key lastKey;
  bool toggledOn = false;
  if (keyToggledOn(keyState)) {
    lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);
    toggledOn = true;
  }

  if (keyIsPressed(keyState))
    kaleidoscope::hid::pressKey(lastKey, toggledOn);
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

  case MACRO_PRINT_MY_MAIL:
    printMyMail(keyState);
    break;

  //case MACRO_ANY:
    //anyKeyMacro(keyState, Key_O); // too many args to anyKeyMacro
    //break;

    //  case MACRO_TOGGLE_FACTORY_LAYOUT:
    //    toggleFactoryLayout(keyState);
    //    break;

  case MACRO_LED_DEACTIVATION:
    //deactivateLeds(keyState);
    break;


    //  case MACRO_FORWARD_DELETE_WORD:
    //return MACRODOWN(T(F7), T(N1), T(N2))
    

  case MACRO_EMACS_CcCc:
    return MACRODOWN(D(RightControl), T(C), T(C), U(RightControl));
    
  case MACRO_EMACS_ORG_REFILE:
    return MACRODOWN(D(RightControl), T(C), T(W), U(RightControl));
    
  case MACRO_EMACS_MOVE_TO_PREV_MARKED_POS:
    return MACRODOWN(D(RightControl), T(U), T(Space), U(RightControl));    
   
  case MACRO_PAREN_PAIR:
    return MACRODOWN(T(LeftParen), T(RightParen), T(LeftArrow));

  case MACRO_BRACKET_PAIR:
    return MACRODOWN(T(LeftBracket), T(RightBracket), T(LeftArrow));

  case MACRO_CURLYBRACKET_PAIR:
    return MACRODOWN(T(LeftCurlyBracket), T(RightCurlyBracket), T(LeftArrow));

  case MACRO_HEATMAP:
    //HeatmapEffect.activate();
    break; 


    //////////////////////////////////////////////////////////////
    // C-F<number>: See #define directives using LCTRL(F<number>)
    //////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////
    // C-S-M-F<number> shortcuts for development (a reserved range at least)
    ////////////////////////////////////////////////////////////////////////
  case MACRO_DEV_FIND_IN_PATH:
    return MACRODOWN(D(LeftControl), D(LeftShift), D(LeftAlt), T(F1), U(LeftAlt), U(LeftControl), U(LeftShift));
  case MACRO_DEV_RENAME:
    return MACRODOWN(D(LeftControl), D(LeftShift), D(LeftAlt), T(F2), U(LeftAlt), U(LeftControl), U(LeftShift));
  case MACRO_SMART_ENTER: // this is 'C-c C-c' in emacs and 'complete current statement' in intellij
    return MACRODOWN(D(LeftControl), D(LeftShift), D(LeftAlt), T(F3), U(LeftAlt), U(LeftControl), U(LeftShift));
  case MACRO_DEV_GENERATE:
    return MACRODOWN(D(LeftControl), D(LeftShift), D(LeftAlt), T(F4), U(LeftAlt), U(LeftControl), U(LeftShift));
  case MACRO_DEV_COMMENT:
    return MACRODOWN(D(LeftControl), D(LeftShift), D(LeftAlt), T(F5), U(LeftAlt), U(LeftControl), U(LeftShift));
    //  case MACRO_DEV_NEW_CLASS:
    //    return MACRODOWN(D(LeftControl), D(LeftShift), D(LeftAlt), T(F5), U(LeftAlt), U(LeftControl), U(LeftShift));
  case MACRO_FIND_FILE:
    return MACRODOWN(D(LeftControl), D(LeftShift), D(LeftAlt), T(F6), U(LeftAlt), U(LeftControl), U(LeftShift));

  case MACRO_ACE_JUMP:
    return MACRODOWN(D(LeftControl), D(LeftShift), D(LeftAlt), T(F19), U(LeftAlt), U(LeftControl), U(LeftShift));    
  case MACRO_SHOW_BUFFERS:
    return MACRODOWN(D(LeftControl), D(LeftShift), D(LeftAlt), T(F20), U(LeftAlt), U(LeftControl), U(LeftShift));    
  case MACRO_SHOW_BOOKMARKS:
    return MACRODOWN(D(LeftControl), D(LeftShift), D(LeftAlt), T(F21), U(LeftAlt), U(LeftControl), U(LeftShift));    
  case MACRO_SET_BOOKMARK:
    return MACRODOWN(D(LeftControl), D(LeftShift), D(LeftAlt), T(F22), U(LeftAlt), U(LeftControl), U(LeftShift));    
    //next, use F24 etc to also see if that works with intellij
  case MACRO_GOTO_PREV_BUFFER:
    return MACRODOWN(D(LeftControl), D(LeftShift), D(LeftAlt), T(F23), U(LeftAlt), U(LeftControl), U(LeftShift));    
  case MACRO_GOTO_NEXT_BUFFER:
    return MACRODOWN(D(LeftControl), D(LeftShift), D(LeftAlt), T(F24), U(LeftAlt), U(LeftControl), U(LeftShift));    
    //  case MACRO_AUTOCOMPLETE:
    //    return MACRODOWN(D(LeftControl), D(LeftShift), D(LeftAlt), T(F6), U(LeftAlt), U(LeftControl), U(LeftShift));





    
    //  case MACRO_SAVE_FILE:
    //    //return FNtoAHK(0,0);
     //    return MACRODOWN(D(LeftControl), D(LeftShift), T(F8), U(LeftControl), U(LeftShift));
    
    //  case MACRO_FIND:
    //    //return FNtoAHK(0,0);
    //    return MACRODOWN(D(LeftControl), D(LeftShift), T(F8), U(LeftControl), U(LeftShift));
    
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


    //9 - 12 are free
    
  case MACRO_APP_FOOBAR2K_SEEK_FW1MIN:
    return FNtoAHK(1,3);

  case MACRO_APP_FOOBAR2K_RATE1:
    return FNtoAHK(1,4);

    case MACRO_APP_FOOBAR2K_PAUSE:
    return FNtoAHK(1,5);

  case MACRO_APP_BROWSER_OPEN_SEARCH:
    return FNtoAHK(1,6);


  case MACRO_FOCUS_EMACS:
    return FNtoAHK(1,8);

  case MACRO_DELETE_WINDOW:
    return FNtoAHK(1,9);

  case MACRO_ENTER_KEY:
    return FNtoAHK(2,0);

  case MACRO_ORG_EMACS_CAPTURE:
    return FNtoAHK(2,1);

  case MACRO_ORG_CLOCK_GOTO:
    return FNtoAHK(2,2);

  case MACRO_ORG_CLOCK_IN:
    return FNtoAHK(2,3);

  case MACRO_ORG_CLOCK_OUT:
    return FNtoAHK(2,4);

  case MACRO_APP_FOOBAR2K_UnFOCUS:
    return FNtoAHK(2,5);

  case MACRO_COPY: //not in use
    return FNtoAHK(2,6);

  case MACRO_CUT: //not in use
    return FNtoAHK(2,7);

  case MACRO_PASTE: //not in use
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

    // FNtoAHK(3,4) not in use

  case MACRO_UNDO:
    return FNtoAHK(3,5);

  case MACRO_SHUTDOWN:
    return FNtoAHK(3,6);

  case MACRO_EMACS_CAPTURE_TODO:
    return FNtoAHK(3,7);

  case MACRO_EMACS_CAPTURE_NOTE:
    return FNtoAHK(3,8);

  case MACRO_EMACS_CAPTURE_JOURNAL:
    return FNtoAHK(3,9);

    //42 till 45 are free
    
  case MACRO_FOCUS_IDE:
    return FNtoAHK(4,6);

  case MACRO_KILL_BUFFER:
    return FNtoAHK(4,7);    
    
  }
  
  return MACRO_NONE;
}



// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 01.


static kaleidoscope::plugin::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::plugin::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::plugin::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::plugin::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::plugin::LEDSolidColor solidBlue(0, 70, 130);
static kaleidoscope::plugin::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::plugin::LEDSolidColor solidViolet(130, 0, 120);



void tapDanceAction(uint8_t tap_dance_index, byte row, byte col, uint8_t tap_count,
                    kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_index) {
    case TapDanceKey::LeftBrackets: {
      return tapDanceActionKeys(tap_count, tap_dance_action, M(MACRO_PAREN_PAIR), M(MACRO_BRACKET_PAIR), M(MACRO_CURLYBRACKET_PAIR));
    }
    case TapDanceKey::RightBrackets: {
      return tapDanceActionKeys(tap_count, tap_dance_action, Key_RightParen, Key_RightBracket, Key_RightCurlyBracket);
    }      

    case TapDanceKey::AUml: {
      //      return tapDanceActionKeys(tap_count, tap_dance_action, M(MACRO_UMLAUT_A), M(MACRO_UMLAUT_CA));
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
       //      return tapDanceActionKeys(tap_count, tap_dance_action, M(MACRO_ENTER_KEY), M(MACRO_ORG_EMACS_CAPTURE));
      //    }
    case TapDanceKey::OrgClocking: {
      return tapDanceActionKeys(tap_count, tap_dance_action, M(MACRO_ORG_CLOCK_GOTO), M(MACRO_ORG_CLOCK_IN), M(MACRO_ORG_CLOCK_OUT));
    }      
    case TapDanceKey::CopyCut: {
      //return tapDanceActionKeys(tap_count, tap_dance_action, M(MACRO_COPY), M(MACRO_CUT));
      return tapDanceActionKeys(tap_count, tap_dance_action, All_Copy, All_Cut);
    }      
  }
}



/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::plugin::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::plugin::HostPowerManagement::Suspend:
    LEDControl.set_all_leds_to({0, 0, 0});
    LEDControl.syncLeds();
    LEDControl.paused = true;
    break;
  case kaleidoscope::plugin::HostPowerManagement::Resume:
    LEDControl.paused = false;
    LEDControl.refreshAll();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::plugin::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

/** This 'enum' is a list of all the magic combos used by the Model 01's
 * firmware The names aren't particularly important. What is important is that
 * each is unique.
 *
 * These are the names of your magic combos. They will be used by the
 * `USE_MAGIC_COMBOS` call below.
 */
enum {
  // Toggle between Boot (6-key rollover; for BIOSes and early boot) and NKRO
  // mode.
  COMBO_TOGGLE_NKRO_MODE,
  // Enter test mode
  COMBO_ENTER_TEST_MODE
};

/** Wrappers, to be used by MagicCombo. **/

/**
 * This simply toggles the keyboard protocol via USBQuirks, and wraps it within
 * a function with an unused argument, to match what MagicCombo expects.
 */
static void toggleKeyboardProtocol(uint8_t combo_index) {
  USBQuirks.toggleKeyboardProtocol();
}

/**
 *  This enters the hardware test mode
 */
static void enterHardwareTestMode(uint8_t combo_index) {
  HardwareTestMode.runTests();
}


enum MC {
         SwitchToLayerLFNandRFN
};

void shiftToLayerLFNandRFN(uint8_t combo_index) {
  //Macros.type(PSTR("It's a kind of magic!"));
  //Somehow switch to layer LFNandRFN

  // ShiftToLayer(LFNandRFN); // This worked with a really old firmware version only

  /* This doesn't work, LFNandRFN layer stays after depressing
  if (Layer.isActive(LFNandRFN)) {
    Layer.deactivate(LFNandRFN);
  } else {
    Layer.activate(LFNandRFN);
  }
  */
}

/** Magic combo list, a list of key combo and action pairs the firmware should
 * recognise.
 */
USE_MAGIC_COMBOS(
    {.action = toggleKeyboardProtocol,
     .keys = { R3C6, R2C6, R3C7 } // Left Fn + Esc + Shift
    },
    {.action = enterHardwareTestMode,
     .keys = { R3C6, R0C0, R0C6 } // Left Fn + Prog + LED
    },
    /*{.action = shiftToLayerLFNandRFN,
     // Left Fn + Prog + LED
     .keys = {R3C6, R3C9} // Left Fn + Right Fn
     }*/
);

// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
  // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
  // editable keymap in EEPROM.
  EEPROMSettings,
  EEPROMKeymap,

  // Focus allows bi-directional communication with the host, and is the
  // interface through which the keymap in EEPROM can be edited.
  Focus,

  // FocusSettingsCommand adds a few Focus commands, intended to aid in
  // changing some settings of the keyboard, such as the default layer (via the
  // `settings.defaultLayer` command)
  FocusSettingsCommand,

  // FocusEEPROMCommand adds a set of Focus commands, which are very helpful in
  // both debugging, and in backing up one's EEPROM contents.
  FocusEEPROMCommand,

  // The boot greeting effect pulses the LED button for 10 seconds after the
  // keyboard is first connected
  BootGreetingEffect,

  // The hardware test mode, which can be invoked by tapping Prog, LED and the
  // left Fn button at the same time.
  HardwareTestMode,

  // LEDControl provides support for other LED modes
  LEDControl,

  // We start with the LED effect that turns off all the LEDs.
  LEDOff,

  // The rainbow effect changes the color of all of the keyboard's keys at the same time
  // running through all the colors of the rainbow.
  LEDRainbowEffect,

  // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
  // and slowly moves the rainbow across your keyboard
  LEDRainbowWaveEffect,

  // The chase effect follows the adventure of a blue pixel which chases a red pixel across
  // your keyboard. Spoiler: the blue pixel never catches the red pixel
  LEDChaseEffect,

  // These static effects turn your keyboard's LEDs a variety of colors
  solidRed, solidOrange, solidYellow, solidGreen, solidBlue, solidIndigo, solidViolet,

  // The breathe effect slowly pulses all of the LEDs on your keyboard
  LEDBreatheEffect,

  // The AlphaSquare effect prints each character you type, using your
  // keyboard's LEDs as a display
  AlphaSquareEffect,

  // The stalker effect lights up the keys you've pressed recently
  StalkerEffect,

  // The LED Palette Theme plugin provides a shared palette for other plugins,
  // like Colormap below
  LEDPaletteTheme,

  // The Colormap effect makes it possible to set up per-layer colormaps
  ColormapEffect,

  // The numpad plugin is responsible for lighting up the 'numpad' mode
  // with a custom LED effect
  //NumPad,

  MagicCombo,
  
  // The macros plugin adds support for macros
  Macros,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  MouseKeys,

  // The HostPowerManagement plugin allows us to turn LEDs off when then host
  // goes to sleep, and resume them when it wakes up.
  HostPowerManagement,

  // The USBQuirks plugin lets you do some things with USB that we aren't
  // comfortable - or able - to do automatically, but can be useful
  // nevertheless. Such as toggling the key report protocol between Boot (used
  // by BIOSes) and Report (NKRO).
  USBQuirks,
  
  TapDance,
  TopsyTurvy

);

/** The 'setup' function is one of the two standard Arduino sketch functions.
 * It's called when your keyboard first powers up. This is where you set up
 * Kaleidoscope and any plugins.
 */
void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // While we hope to improve this in the future, the NumPad plugin
  // needs to be explicitly told which keymap layer is your numpad layer
  //NumPad.numPadLayer = NUMPAD;

  // We configure the AlphaSquare effect to use RED letters
  AlphaSquare.color = CRGB(255, 0, 0);

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  //LEDRainbowEffect.brightness(150);
  //LEDRainbowWaveEffect.brightness(150);

  // Set the action key the test mode should listen for to Left Fn
  HardwareTestMode.setActionKey(R3C6);

  // The LED Stalker mode has a few effects. The one we like is called
  // 'BlazingTrail'. For details on other options, see
  // https://github.com/keyboardio/Kaleidoscope/blob/master/doc/plugin/LED-Stalker.md
  //StalkerEffect.variant = STALKER(BlazingTrail);

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();

  // To make the keymap editable without flashing new firmware, we store
  // additional layers in EEPROM. For now, we reserve space for five layers. If
  // one wants to use these layers, just set the default layer to one in EEPROM,
  // by using the `settings.defaultLayer` Focus command, or by using the
  // `keymap.onlyCustom` command to use EEPROM layers only.
  //EEPROMKeymap.setup(5);

  // We need to tell the Colormap plugin how many layers we want to have custom
  // maps for. To make things simple, we set it to five layers, which is how
  // many editable layers we have (see above).
  //ColormapEffect.max_layers(5);
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
