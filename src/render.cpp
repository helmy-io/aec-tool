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

c_render::c_render(int num_rows, int num_cols,
	char const *p_font_family,
	char const *p_font_bold,
	char const *p_font_italic,
	char const *p_font_bold_italic,
	int font_size,
	Color bg, Color fg,
	int vertical_margin, int horizontal_margin) :
	NUM_ROWS(num_rows), NUM_COLS(num_cols),
	bg(bg), fg(fg),
	VERTICAL_MARGIN(vertical_margin), HORIZONTAL_MARGIN(horizontal_margin)
{
	row = 0;
	col = 0;
	bold = false;
	italic = false;
	decoration = NoDecoration;
	
	this->p_font_family = p_font_family;
	this->p_font_bold = p_font_bold;
	this->p_font_italic = p_font_italic;
	this->p_font_bold_italic = p_font_bold_italic;

	// calculate width and height of a single char (assume
	// monospaced font!)
	{
		// TODO: dummies are for noobs
		Image dummy_image("1x1", "black");
		dummy_image.font(p_font_family);
		dummy_image.fontPointsize(font_size);
		TypeMetric metric;
		dummy_image.fontTypeMetrics("", &metric);

		CHAR_WIDTH = metric.maxHorizontalAdvance();
		DESCENT = metric.descent();
		CHAR_HEIGHT = dummy_image.fontPointsize() - DESCENT;
	}
	
	int terminal_width = num_cols * CHAR_WIDTH +  2 * HORIZONTAL_MARGIN;
	int terminal_height = num_rows * CHAR_HEIGHT + 2 * VERTICAL_MARGIN;

	image.size(Geometry(terminal_width, terminal_height));
	// TODO: set bg
	image.font(p_font_family);
	image.fontPointsize(font_size);
}

void c_render::put_str(char const *p_str)
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

	// choose a font from the font family
	if(bold && italic)
		image.font(p_font_bold_italic);
	else if(bold)
		image.font(p_font_bold);
	else if(italic)
		image.font(p_font_italic);
	else
		image.font(p_font_family);

	DrawableText text(left_bound, lower_bound + DESCENT - 1,  p_str);
	list<Drawable> text_list;
	text_list.push_back(text);
	text_list.push_back(DrawableTextDecoration(decoration));
	image.draw(text_list);
}

void c_render::write(char const *p_str)
{
	image.write(p_str);
}

