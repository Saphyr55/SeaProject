#pragma once

#include <SDL2/SDL.h>

namespace Sea
{
	enum class Keys
	{
		UNKNOWN = 0,

		RETURN = '\r',
		ESCAPE = '\x1B',
		BACKSPACE = '\b',
		TAB = '\t',
		SPACE = ' ',
		EXCLAIM = '!',
		QUOTEDBL = '"',
		HASH = '#',
		PERCENT = '%',
		DOLLAR = '$',
		AMPERSAND = '&',
		QUOTE = '\'',
		LEFTPAREN = '(',
		RIGHTPAREN = ')',
		ASTERISK = '*',
		PLUS = '+',
		COMMA = ',',
		MINUS = '-',
		PERIOD = '.',
		SLASH = '/',
		ONE = '0',
		TWO = '1',
		THREE = '2',
		FOUR = '3',
		FIVE = '4',
		SIX = '5',
		SEVEN = '6',
		EIGHT = '7',
		NINE = '8',
		ZERO = '9',
		COLON = ':',
		SEMICOLON = ';',
		LESS = '<',
		EQUALS = '=',
		GREATER = '>',
		QUESTION = '?',
		AT = '@',

		/*
		   Skip uppercase letters
		 */

		 LEFTBRACKET = '[',
		 BACKSLASH = '\\',
		 RIGHTBRACKET = ']',
		 CARET = '^',
		 UNDERSCORE = '_',
		 BACKQUOTE = '`',
		 A = 'a',
		 B = 'b',
		 C = 'c',
		 D = 'd',
		 E = 'e',
		 F = 'f',
		 G = 'g',
		 H = 'h',
		 I = 'i',
		 J = 'j',
		 K = 'k',
		 L = 'l',
		 M = 'm',
		 N = 'n',
		 O = 'o',
		 P = 'p',
		 Q = 'q',
		 R = 'r',
		 S = 's',
		 T = 't',
		 U = 'u',
		 V = 'v',
		 W = 'w',
		 X = 'x',
		 Y = 'y',
		 Z = 'z',

		 CAPSLOCK = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CAPSLOCK),

		 F1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F1),
		 F2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F2),
		 F3 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F3),
		 F4 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F4),
		 F5 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F5),
		 F6 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F6),
		 F7 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F7),
		 F8 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F8),
		 F9 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F9),
		 F10 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F10),
		 F11 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F11),
		 F12 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F12),

		 PRINTSCREEN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRINTSCREEN),
		 SCROLLLOCK = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SCROLLLOCK),
		 PAUSE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAUSE),
		 INSERT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INSERT),
		 HOME = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HOME),
		 PAGEUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEUP),
		 DELETE = '\x7F',
		 END = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_END),
		 PAGEDOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEDOWN),
		 RIGHT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RIGHT),
		 LEFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LEFT),
		 DOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DOWN),
		 UP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UP),

		 NUMLOCKCLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_NUMLOCKCLEAR),
		 KP_DIVIDE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DIVIDE),
		 KP_MULTIPLY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MULTIPLY),
		 KP_MINUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MINUS),
		 KP_PLUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUS),
		 KP_ENTER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_ENTER),
		 KP_1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_1),
		 KP_2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_2),
		 KP_3 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_3),
		 KP_4 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_4),
		 KP_5 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_5),
		 KP_6 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_6),
		 KP_7 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_7),
		 KP_8 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_8),
		 KP_9 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_9),
		 KP_0 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_0),
		 KP_PERIOD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERIOD),

		 APPLICATION = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APPLICATION),
		 POWER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_POWER),
		 KP_EQUALS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALS),
		 F13 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F13),
		 F14 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F14),
		 F15 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F15),
		 F16 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F16),
		 F17 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F17),
		 F18 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F18),
		 F19 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F19),
		 F20 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F20),
		 F21 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F21),
		 F22 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F22),
		 F23 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F23),
		 F24 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F24),
		 EXECUTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXECUTE),
		 HELP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HELP),
		 MENU = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MENU),
		 SELECT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SELECT),
		 STOP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_STOP),
		 AGAIN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AGAIN),
		 UNDO = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UNDO),
		 CUT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CUT),
		 COPY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COPY),
		 PASTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PASTE),
		 FIND = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_FIND),
		 MUTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MUTE),
		 VOLUMEUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEUP),
		 VOLUMEDOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEDOWN),
		 KP_COMMA = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COMMA),
		 KP_EQUALSAS400 =
		 SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALSAS400),

		ALTERASE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_ALTERASE),
		SYSREQ = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SYSREQ),
		CANCEL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CANCEL),
		CLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEAR),
		PRIOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRIOR),
		RETURN2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RETURN2),
		SEPARATOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SEPARATOR),
		OUT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OUT),
		OPER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OPER),
		CLEARAGAIN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEARAGAIN),
		CRSEL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CRSEL),
		EXSEL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXSEL),

		KP_00 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_00),
		KP_000 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_000),
		THOUSANDSSEPARATOR =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_THOUSANDSSEPARATOR),
		DECIMALSEPARATOR =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DECIMALSEPARATOR),
		CURRENCYUNIT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYUNIT),
		CURRENCYSUBUNIT =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYSUBUNIT),
		KP_LEFTPAREN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTPAREN),
		KP_RIGHTPAREN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTPAREN),
		KP_LEFTBRACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTBRACE),
		KP_RIGHTBRACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTBRACE),
		KP_TAB = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_TAB),
		KP_BACKSPACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BACKSPACE),
		KP_A = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_A),
		KP_B = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_B),
		KP_C = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_C),
		KP_D = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_D),
		KP_E = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_E),
		KP_F = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_F),
		KP_XOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_XOR),
		KP_POWER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_POWER),
		KP_PERCENT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERCENT),
		KP_LESS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LESS),
		KP_GREATER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_GREATER),
		KP_AMPERSAND = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AMPERSAND),
		KP_DBLAMPERSAND =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLAMPERSAND),
		KP_VERTICALBAR =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_VERTICALBAR),
		KP_DBLVERTICALBAR =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLVERTICALBAR),
		KP_COLON = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COLON),
		KP_HASH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HASH),
		KP_SPACE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_SPACE),
		KP_AT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AT),
		KP_EXCLAM = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EXCLAM),
		KP_MEMSTORE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSTORE),
		KP_MEMRECALL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMRECALL),
		KP_MEMCLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMCLEAR),
		KP_MEMADD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMADD),
		KP_MEMSUBTRACT =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSUBTRACT),
		KP_MEMMULTIPLY =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMMULTIPLY),
		KP_MEMDIVIDE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMDIVIDE),
		KP_PLUSMINUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUSMINUS),
		KP_CLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEAR),
		KP_CLEARENTRY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEARENTRY),
		KP_BINARY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BINARY),
		KP_OCTAL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_OCTAL),
		KP_DECIMAL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DECIMAL),
		KP_HEXADECIMAL =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HEXADECIMAL),

		LCTRL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LCTRL),
		LSHIFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LSHIFT),
		LALT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LALT),
		LGUI = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LGUI),
		RCTRL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RCTRL),
		RSHIFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RSHIFT),
		RALT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RALT),
		RGUI = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RGUI),

		MODE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MODE),

		AUDIONEXT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIONEXT),
		AUDIOPREV = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPREV),
		AUDIOSTOP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOSTOP),
		AUDIOPLAY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPLAY),
		AUDIOMUTE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOMUTE),
		MEDIASELECT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIASELECT),
		WWW = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_WWW),
		MAIL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MAIL),
		CALCULATOR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CALCULATOR),
		COMPUTER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COMPUTER),
		AC_SEARCH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_SEARCH),
		AC_HOME = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_HOME),
		AC_BACK = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BACK),
		AC_FORWARD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_FORWARD),
		AC_STOP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_STOP),
		AC_REFRESH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_REFRESH),
		AC_BOOKMARKS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BOOKMARKS),

		BRIGHTNESSDOWN =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSDOWN),
		BRIGHTNESSUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSUP),
		DISPLAYSWITCH = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DISPLAYSWITCH),
		KBDILLUMTOGGLE =
		SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMTOGGLE),
		KBDILLUMDOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMDOWN),
		KBDILLUMUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMUP),
		EJECT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EJECT),
		SLEEP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SLEEP),
		APP1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APP1),
		APP2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APP2),

		AUDIOREWIND = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOREWIND),
		AUDIOFASTFORWARD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOFASTFORWARD)
	};

	class Key
	{
	public :
		

	public:
		enum class Scancode
		{

			UNKNOWN = 0,

			A = 4,
			B = 5,
			C = 6,
			D = 7,
			E = 8,
			F = 9,
			G = 10,
			H = 11,
			I = 12,
			J = 13,
			K = 14,
			L = 15,
			M = 16,
			N = 17,
			O = 18,
			P = 19,
			Q = 20,
			R = 21,
			S = 22,
			T = 23,
			U = 24,
			V = 25,
			W = 26,
			X = 27,
			Y = 28,
			Z = 29,

			ONE = 30,
			TWO = 31,
			THREE = 32,
			FOUR = 33,
			FIVE = 34,
			SIX = 35,
			SEVEN = 36,
			EIGHT = 37,
			NINE = 38,
			ZERO = 39,

			RETURN = 40,
			ESCAPE = 41,
			BACKSPACE = 42,
			TAB = 43,
			SPACE = 44,

			MINUS = 45,
			EQUALS = 46,
			LEFTBRACKET = 47,
			RIGHTBRACKET = 48,
			BACKSLASH = 49,
			NONUSHASH = 50,
			SEMICOLON = 51,
			APOSTROPHE = 52,
			GRAVE = 53,
			COMMA = 54,
			PERIOD = 55,
			SLASH = 56,

			CAPSLOCK = 57,

			F1 = 58,
			F2 = 59,
			F3 = 60,
			F4 = 61,
			F5 = 62,
			F6 = 63,
			F7 = 64,
			F8 = 65,
			F9 = 66,
			F10 = 67,
			F11 = 68,
			F12 = 69,

			PRINTSCREEN = 70,
			SCROLLLOCK = 71,
			PAUSE = 72,
			INSERT = 73,
			HOME = 74,
			PAGEUP = 75,
			DELETE = 76,
			END = 77,
			PAGEDOWN = 78,
			RIGHT = 79,
			LEFT = 80,
			DOWN = 81,
			UP = 82,

			NUMLOCKCLEAR = 83,
			KP_DIVIDE = 84,
			KP_MULTIPLY = 85,
			KP_MINUS = 86,
			KP_PLUS = 87,
			KP_ENTER = 88,
			KP_1 = 89,
			KP_2 = 90,
			KP_3 = 91,
			KP_4 = 92,
			KP_5 = 93,
			KP_6 = 94,
			KP_7 = 95,
			KP_8 = 96,
			KP_9 = 97,
			KP_0 = 98,
			KP_PERIOD = 99,

			NONUSBACKSLASH = 100,
			APPLICATION = 101,
			KP_EQUALS = 103,
			F13 = 104,
			F14 = 105,
			F15 = 106,
			F16 = 107,
			F17 = 108,
			F18 = 109,
			F19 = 110,
			F20 = 111,
			F21 = 112,
			F22 = 113,
			F23 = 114,
			F24 = 115,
			EXECUTE = 116,
			HELP = 117,
			MENU = 118,
			SELECT = 119,
			STOP = 120,
			AGAIN = 121,
			UNDO = 122,
			CUT = 123,
			COPY = 124,
			PASTE = 125,
			FIND = 126,
			MUTE = 127,
			VOLUMEUP = 128,
			VOLUMEDOWN = 129,
			KP_COMMA = 133,
			KP_EQUALSAS400 = 134,

			INTERNATIONAL1 = 135,
			INTERNATIONAL2 = 136,
			INTERNATIONAL3 = 137,
			INTERNATIONAL4 = 138,
			INTERNATIONAL5 = 139,
			INTERNATIONAL6 = 140,
			INTERNATIONAL7 = 141,
			INTERNATIONAL8 = 142,
			INTERNATIONAL9 = 143,
			LANG1 = 144,
			LANG2 = 145,
			LANG3 = 146,
			LANG4 = 147,
			LANG5 = 148,
			LANG6 = 149,
			LANG7 = 150,
			LANG8 = 151,
			LANG9 = 152,

			ALTERASE = 153,
			SYSREQ = 154,
			CANCEL = 155,
			CLEAR = 156,
			PRIOR = 157,
			RETURN2 = 158,
			SEPARATOR = 159,
			OUT = 160,
			OPER = 161,
			CLEARAGAIN = 162,
			CRSEL = 163,
			EXSEL = 164,

			KP_00 = 176,
			KP_000 = 177,
			THOUSANDSSEPARATOR = 178,
			DECIMALSEPARATOR = 179,
			CURRENCYUNIT = 180,
			CURRENCYSUBUNIT = 181,
			KP_LEFTPAREN = 182,
			KP_RIGHTPAREN = 183,
			KP_LEFTBRACE = 184,
			KP_RIGHTBRACE = 185,
			KP_TAB = 186,
			KP_BACKSPACE = 187,
			KP_A = 188,
			KP_B = 189,
			KP_C = 190,
			KP_D = 191,
			KP_E = 192,
			KP_F = 193,
			KP_XOR = 194,
			KP_POWER = 195,
			KP_PERCENT = 196,
			KP_LESS = 197,
			KP_GREATER = 198,
			KP_AMPERSAND = 199,
			KP_DBLAMPERSAND = 200,
			KP_VERTICALBAR = 201,
			KP_DBLVERTICALBAR = 202,
			KP_COLON = 203,
			KP_HASH = 204,
			KP_SPACE = 205,
			KP_AT = 206,
			KP_EXCLAM = 207,
			KP_MEMSTORE = 208,
			KP_MEMRECALL = 209,
			KP_MEMCLEAR = 210,
			KP_MEMADD = 211,
			KP_MEMSUBTRACT = 212,
			KP_MEMMULTIPLY = 213,
			KP_MEMDIVIDE = 214,
			KP_PLUSMINUS = 215,
			KP_CLEAR = 216,
			KP_CLEARENTRY = 217,
			KP_BINARY = 218,
			KP_OCTAL = 219,
			KP_DECIMAL = 220,
			KP_HEXADECIMAL = 221,

			LCTRL = 224,
			LSHIFT = 225,
			LALT = 226,
			LGUI = 227,
			RCTRL = 228,
			RSHIFT = 229,
			RALT = 230,
			RGUI = 231,

			MODE = 257,
			AUDIONEXT = 258,
			AUDIOPREV = 259,
			AUDIOSTOP = 260,
			AUDIOPLAY = 261,
			AUDIOMUTE = 262,
			MEDIASELECT = 263,
			WWW = 264,
			MAIL = 265,
			CALCULATOR = 266,
			COMPUTER = 267,
			AC_SEARCH = 268,
			AC_HOME = 269,
			AC_BACK = 270,
			AC_FORWARD = 271,
			AC_STOP = 272,
			AC_REFRESH = 273,
			AC_BOOKMARKS = 274,

			BRIGHTNESSDOWN = 275,
			BRIGHTNESSUP = 276,
			DISPLAYSWITCH = 277,
			KBDILLUMTOGGLE = 278,
			KBDILLUMDOWN = 279,
			KBDILLUMUP = 280,
			EJECT = 281,
			SLEEP = 282,

			APP1 = 283,
			APP2 = 284,

			AUDIOREWIND = 285,
			AUDIOFASTFORWARD = 286,

			SOFTLEFT = 287,
			SOFTRIGHT = 288,
			CALL = 289,
			ENDCALL = 290,
			SDL_NUM_SCANCODES = 512

		};
	};
}