/* ScummVM - Scumm Interpreter
 * Copyright (C) 2002 The ScummVM project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header$
 */

#ifndef NEWGUI_H
#define NEWGUI_H

#include "scummsys.h"

class Dialog;
class Scumm;

// Extremly simple stack class, doesn't even do any error checking (for now)
class DialogStack {
protected:
	Dialog	*_stack[10];	// Anybody nesting dialogs deeper than 4 is mad anyway
	int		_size;
public:
	DialogStack() : _size(0) {}
	
	bool	empty() const		{ return _size <= 0; }
	void	push(Dialog *d)		{ _stack[_size++] = d; }
	Dialog	*top() const		{ return _stack[_size-1]; }
	void	pop()				{ if (_size > 0) _stack[--_size] = 0; }
};

// This class hopefully will replace the old Gui class completly one day 
class NewGui {
	friend class Dialog;
public:
	byte _color, _shadowcolor;
	byte _bgcolor;
	byte _textcolor;
	byte _textcolorhi;

	// Dialogs
	void pauseDialog();
	void saveloadDialog();
	void aboutDialog();
	void optionsDialog();

	void loop();

	bool isActive()	{ return ! _dialogStack.empty(); }

	NewGui(Scumm *s);

protected:
	Scumm		*_s;
	bool		_need_redraw;
	DialogStack	_dialogStack;
	
	Dialog		*_pauseDialog;
	Dialog		*_saveLoadDialog;
	Dialog		*_aboutDialog;
	Dialog		*_optionsDialog;

	// sound state
	bool		_old_soundsPaused;

	// mouse cursor state
	bool		_old_cursor_mode;
	int			_old_cursorHotspotX, _old_cursorHotspotY, _old_cursorWidth, _old_cursorHeight;
	byte		_old_grabbedCursor[2048];
	
	// mouse pos
	struct {
		int16 x,y;
	} _old_mouse;

	void saveState();
	void restoreState();
	
	void openDialog(Dialog *dialog);
	void closeTopDialog();

public:
	// Drawing
	byte *getBasePtr(int x, int y);
	void box(int x, int y, int width, int height);
    void line(int x, int y, int x2, int y2, byte color);
    void fillArea(int x, int y, int w, int h, byte color);
    void setAreaDirty(int x, int y, int w, int h);
	void drawChar(const char c, int x, int y);
	void drawString(const char *str, int x, int y, int w, byte color);
	void drawBitmap(uint32 bitmap[8], int x, int y, byte color);

	// Query a string from the resources
	const char *queryResString(int stringno);
	
	// Query a custom string. This is in a seperate method so that we
	// can easily localize the messages in the future if we want to.
	const char *queryCustomString(int stringno);
};

#endif
