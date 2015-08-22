/*
 * Copyright (C) M. Helmy Hemeda, 2015
 *
 * This file is part of aec-tool.
 * 
 * aec-tool is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * aec-tool is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with aec-tool.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef FILE_RENDER_H
#define FILE_RENDER_H

#include <string.h>

#include <Magick++.h>
#include <vterm.h>

using namespace Magick;

class Render
{
	Image image;
	VTerm *vt;

	int CHAR_WIDTH;
	int CHAR_HEIGHT;

	const int VERTICAL_MARGIN;
	const int HORIZONTAL_MARGIN;

	char const *p_font_family;
	const int font_size;

	int DESCENT;

public:
	int row;
	int col;
	ColorRGB bg;
	ColorRGB fg;
	bool bold;
	bool italic;
	DecorationType decoration;

	Render(VTerm *vt,
		char const *p_font_family,
		int font_size,
		int vertical_margin, int horizontal_margin);

	void put_str(char const *p_str);
	void repaint();
	void repaint(int top_row, int top_col, int bot_row, int bot_col);
	void repaint_cell();
	void write(char const *p_str);
};
#endif
