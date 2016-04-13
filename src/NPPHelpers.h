/*
 * This file is part of Compare plugin for Notepad++
 * Copyright (C)2011 Jean-Sébastien Leroy (jean.sebastien.leroy@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#pragma once

#include <vector>
#include "Compare.h"


/**
 *  \struct
 *  \brief
 *  \warning  Don't use that helper struct if somewhere in its scope the hView document is changed!!!
 */
struct ScopedViewWriteEnabler
{
	ScopedViewWriteEnabler(HWND hView) : _hView(hView)
	{
		_isRO = ::SendMessage(_hView, SCI_GETREADONLY, 0, 0);
		if (_isRO)
			::SendMessage(_hView, SCI_SETREADONLY, false, 0);
	}

	~ScopedViewWriteEnabler()
	{
		if (_isRO)
			::SendMessage(_hView, SCI_SETREADONLY, true, 0);
	}

private:
	HWND	_hView;
	int		_isRO;
};


/**
 *  \struct
 *  \brief
 *  \warning  Don't use that helper struct if somewhere in its scope the hView document is changed!!!
 */
struct ScopedViewUndoCollectionBlocker
{
	ScopedViewUndoCollectionBlocker(HWND hView) : _hView(hView)
	{
		_isUndoOn = ::SendMessage(_hView, SCI_GETUNDOCOLLECTION, 0, 0);
		if (_isUndoOn)
			::SendMessage(_hView, SCI_SETUNDOCOLLECTION, false, 0);
	}

	~ScopedViewUndoCollectionBlocker()
	{
		if (_isUndoOn)
			::SendMessage(_hView, SCI_SETUNDOCOLLECTION, true, 0);
	}

private:
	HWND	_hView;
	int		_isUndoOn;
};


struct BlankSection
{
	BlankSection(unsigned int line, unsigned int len) : startLine(line), length(len) {}

	unsigned int startLine;
	unsigned int length;
};


using BlankSections_t = std::vector<BlankSection>;
using DocLines_t = std::vector<std::vector<char>>;


bool isSingleView();

HWND getView(int viewId);
int getCurrentViewId();
HWND getCurrentView();
int getOtherViewId();
HWND getOtherView();

int viewIdFromBuffId(int buffId);
void activateBufferID(int buffId);

void markTextAsChanged(HWND window, int start, int length);
void markAsMoved(HWND window, int line);
void markAsRemoved(HWND window, int line);
void markAsChanged(HWND window, int line);
void markAsAdded(HWND window, int line);
void markAsBlank(HWND window, int line);

void setStyles(sUserSettings& Settings);
void setBlank(HWND window, int color);

void defineSymbol(int type, int symbol);
void defineColor(int type, int color);
void clearWindow(HWND window);

DocLines_t getAllLines(HWND window, std::vector<int>& lineNum);

void addBlankSection(HWND window, int line, int length);
int deleteBlankSection(HWND window, int line);

void addBlankLines(HWND window, const BlankSections_t& blanks);
BlankSections_t removeBlankLines(HWND window, bool saveBlanks);
