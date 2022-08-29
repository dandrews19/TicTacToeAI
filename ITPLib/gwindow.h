#pragma once

#include <string>
#include "gevent.h"

// Creates a window for drawing
class GWindow
{
public:
	// Creates a window of the specified size
	GWindow(int width, int height);
	~GWindow();

	// Set whether or not closing the window should terminate
	// the program. Defaults to true.
	void setTerminateOnClose(bool terminate);

	// Clears the contents of the window.
	void clear();

	// Sets the color used for drawing.
	// Can be either in format "#rrggbb"
	// or can be one of the following preset colors:
	// BLACK, BLUE, CYAN, DARK_GRAY, GRAY, GREEN, LIGHT_GRAY,
	// MAGENTA, ORANGE, PINK, RED, WHITE, YELLOW
	void setColor(const std::string& color);

	// Returns the current color as a string in the form "#rrggbb"
	std::string getColor() const;

	// Fills the frame of a rectangle with the specified bounds.
	void fillRect(int x, int y, int width, int height);

	// Fills an oval with the specified bounds
	void fillOval(int x, int y, int width, int height);

	// Fills a circle centered at (x, y) with specified radius
	void fillCircle(int centerX, int centerY, int radius);

	// Draws a rectangle (unfilled) with the specified bounds.
	void drawRect(int x, int y, int width, int height);

	// Draws a oval with the specified bounds
	void drawOval(int x, int y, int width, int height);

	// Draws a circle centered at (x, y) with specified radius
	void drawCircle(int centerX, int centerY, int radius);

	// Draws a line from (x0, y0) to (x1, y1)
	void drawLine(int x0, int y0, int x1, int y1);

	// Draws specified text at given coordinates
	void drawLabel(const std::string& text, int x, int y);

	// Get width of window
	int getWidth() const;
	// Get height of window
	int getHeight() const;

	// Check if there are any events in the event queue
	bool hasEvents() const;
	// Get the event at the front of the event queue
	GEvent getEvent();
private:
	struct GWindowImpl* mImpl;
};

// Creates a terminal window for displaying text
class GTerminal
{
public:
	GTerminal(int width, int height);
	~GTerminal();

	// Set whether or not closing the window should terminate
	// the program. Defaults to true.
	void setTerminateOnClose(bool terminate);

	// Clear the terminal
	void clear();

	// Clears the terminal and writes the given text
	void setText(const std::string& text);

	// Appends text to terminal's current text
	void appendText(const std::string& text);

	// Used to enable/disable cursor
	void showCursor(bool show);

	// Check if there are any events in the event queue
	bool hasEvents() const;
	// Get the event at the front of the event queue
	GEvent getEvent();
private:
	struct GTerminalImpl * mImpl;
};

// Pauses for the indicated number of milliseconds.
void pause(double milliseconds);
