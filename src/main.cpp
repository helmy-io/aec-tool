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

#include <cstring>

#include "render.h"

using namespace std;
using namespace Magick;

void test1();

int main(int argc, char** argv)
{
	printf("Starting aec-tool...\n");
	test1();
	printf("Program terminated normally.\n");
	return 0;
}

void test1()
{
	char a_buf[256];
	sprintf(a_buf, "");
	c_render render(12, 50, // rows, cols
		"./fonts/mono.ttf", // font family
		"./fonts/mono-bold.ttf", // bold font
		"./fonts/mono-oblique.ttf", // italic font
		"./fonts/mono-bold-oblique.ttf", // bold-italic font 
		12, // font size
		Color("green"), // background
		Color("black"), // foreground
		10, // vertical margin
		10 // horizontal margin
		);

	render.put_str("Normal text");

	render.row++;
	render.bold = true;
	render.put_str("Bold text");

	render.row++;
	render.bold = false;
	render.italic = true;
	render.put_str("Italic text");

	render.row++;
	render.italic = false;
	render.bg = Color("red");
	render.put_str("Different background");

	render.row++;
	render.italic = false;
	render.bg = Color("green");
	render.fg = Color("white");
	render.put_str("Different foreground");

	render.fg = Color("black");
	render.row++;
	render.decoration = UnderlineDecoration;
	render.put_str("Underlined text");

	render.row++;
	render.decoration = LineThroughDecoration;
	render.put_str("Line-through text");

	render.row++;
	render.decoration = OverlineDecoration;
	render.put_str("Overlined text");

	render.write("test.png");
}
