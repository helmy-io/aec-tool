/*
 * Copyright (C) 2015, M. Helmy Hemeda
 * 
 * This file is part of aec-tool
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "render.h"

#include <cstring>

using namespace Magick;
using namespace std;

Render::Render(VTerm *vt,
	char const *p_font_family,
	int font_size,
	int vertical_margin, int horizontal_margin) :
	vt(vt),
	p_font_family(p_font_family), font_size(font_size),
	VERTICAL_MARGIN(vertical_margin), HORIZONTAL_MARGIN(horizontal_margin)
{
	row = 0;
	col = 0;
	bold = false;
	italic = false;
	decoration = NoDecoration;

	// calculate width and height of a single char (assume
	// monospaced font!)
	{
		char font_name[256];
		sprintf(font_name, p_font_family, bold?"bold":"medium", italic?"o":"r", font_size);
		image.font(font_name);

		// TODO: dummies are for noobs
		Image dummy_image("1x1", "black");
		dummy_image.font(font_name);
		dummy_image.fontPointsize(font_size);
		TypeMetric metric;
		dummy_image.fontTypeMetrics("", &metric);

		CHAR_WIDTH = metric.maxHorizontalAdvance();
		DESCENT = metric.descent();
		CHAR_HEIGHT = dummy_image.fontPointsize() - DESCENT;
	}
	
	int num_rows, num_cols;
	vterm_get_size(vt, &num_rows, &num_cols);

	int terminal_width = num_cols * CHAR_WIDTH +  2 * HORIZONTAL_MARGIN;
	int terminal_height = num_rows * CHAR_HEIGHT + 2 * VERTICAL_MARGIN;

	VTermColor vt_bg, vt_fg;
	VTermState *state = vterm_obtain_state(vt);
	vterm_state_get_default_colors(state, &vt_bg, &vt_fg);
	bg = ColorRGB(vt_bg.red, vt_bg.green, vt_bg.blue);

	image.size(Geometry(terminal_width, terminal_height));
	image.backgroundColor(bg);
	image.erase();
	image.fontPointsize(font_size);
}

void Render::put_str(char const *p_str)
{
	// calculate left bound
	int left_bound = HORIZONTAL_MARGIN + col * CHAR_WIDTH;

	// calcuate lower bound
	int lower_bound = VERTICAL_MARGIN + (row + 1) * CHAR_HEIGHT;

	// calculate text width
	int right_bound = left_bound + strlen(p_str) * CHAR_WIDTH;

	// calculate text heigh
	int upper_bound = lower_bound - CHAR_HEIGHT;

	// render background before drawing
	DrawableRectangle bg_rect(left_bound, upper_bound, right_bound, lower_bound);
	image.fillColor(bg);
	image.draw(bg_rect);

	// choose text foreground
	image.fillColor(fg);

	// TODO: font_name should be reconstructed only if bold, italic or size has changed
	// choose a font from the font family
	char font_name[256];
	sprintf(font_name, p_font_family, bold?"bold":"medium", italic?"o":"r", font_size);
	image.font(font_name);

	DrawableText text(left_bound, lower_bound + DESCENT - 1,  p_str);
	list<Drawable> text_list;
	text_list.push_back(text);
	text_list.push_back(DrawableTextDecoration(decoration));
	image.draw(text_list);
}

void Render::repaint()
{
	int rows, cols;
	vterm_get_size(vt, &rows, &cols);
	repaint(0, 0, rows - 1, cols - 1);
}

void Render::repaint(int top_row, int top_col, int bot_row, int bot_col)
{
	for(row = top_row; row <= bot_row; ++row)
	{
		for(col = top_col; col <= bot_col; ++col)
		{
			repaint_cell();
		}
	}
}

void Render::repaint_cell()
{
	VTermScreenCell cell;
	VTermPos pos;
	pos.row = row;
	pos.col = col;
	vterm_screen_get_cell(vterm_obtain_screen(vt), pos, &cell);

	char buf[VTERM_MAX_CHARS_PER_CELL];
	sprintf(buf, "%s", cell.chars);
	
	bold = cell.attrs.bold;
	italic = cell.attrs.italic;
	
	if(cell.attrs.strike)
		decoration = LineThroughDecoration;
	else if (cell.attrs.underline)
		decoration = UnderlineDecoration;
	// TODO: support overline

	// update colors
	{
		VTermColor vt_bg, vt_fg;
		VTermState *state = vterm_obtain_state(vt);
		vterm_state_get_default_colors(state, &vt_bg, &vt_fg);

		bg = ColorRGB(vt_bg.red, vt_bg.green, vt_bg.blue);
		fg = ColorRGB(vt_fg.red, vt_fg.green, vt_fg.blue);
	}

	put_str(buf);
}

void Render::write(char const *p_str)
{
	image.write(p_str);
}

