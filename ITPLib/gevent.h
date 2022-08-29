#pragma once
// Type of events we support
enum class EventType
{
	None,
	KeyDown,
	KeyUp,
	MouseBtnDown,
	MouseBtnUp
};

// Key codes for non a-z or 0-9 keys we support
enum class KeyCode
{
	Backspace = 0xff08,
	Enter = 0xff0d,
	Escape = 0xff1b,
	Space = 32,
	Left = 0xff51,
	Up = 0xff52,
	Right = 0xff53,
	Down = 0xff54,
	F1 = 0xffbe,
	F2 = 0xffbf,
	F3 = 0xffc0,
	F4 = 0xffc1,
	F5 = 0xffc2,
	F6 = 0xffc3,
	F7 = 0xffc4,
	F8 = 0xffc5,
	F9 = 0xffc6,
	F10 = 0xffc7,
	F11 = 0xffc8,
	F12 = 0xffc9,
};

// Supported mouse buttons
enum class MouseButton
{
	Left = 1,
	Middle = 2,
	Right = 3
};

// Simple struct for handling basic events
struct GEvent
{
	EventType Type;
	union
	{
		struct
		{
			int Code;
		} Key;
		struct
		{
			int Button;
			int X;
			int Y;
		} Mouse;
	} Event;
};

// We declare these so we can compare KeyCodes/MouseButtons directly to ints
inline bool operator==(int i, KeyCode c)
{
	return i == static_cast<int>(c);
}

inline bool operator==(KeyCode c, int i)
{
	return i == c;
}

inline bool operator==(int i, MouseButton c)
{
	return i == static_cast<int>(c);
}

inline bool operator==(MouseButton c, int i)
{
	return i == c;
}
