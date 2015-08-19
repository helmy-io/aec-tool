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
#include <vterm.h>

#include "render.h"
#include "term.h"

using namespace std;
using namespace Magick;

void test1();
void test2();

int main(int argc, char** argv)
{
	printf("Starting aec-tool...\n");
	test2();
	printf("Program terminated normally.\n");
	return 0;
}

void test2()
{
	VTerm *vt = vterm_new(24, 80);
	VTermScreen *vts = vterm_obtain_screen(vt);
	vterm_screen_reset(vts, 1);
	vterm_screen_set_callbacks(vts, &screen_callbacks, NULL);

	char buf[256];
	sprintf(buf, "Hello, world!\n");
	vterm_input_write(vt, buf, strlen(buf));

	vterm_free(vt);
}

void test1()
{
	char a_buf[256];
	sprintf(a_buf, "");
	Render render(12, 50, // rows, cols
		"./fonts/mono.tff", // font family
		"./fonts/mono-bold.tff", // bold font
		"./fonts/mono-oblique.tff", // italic font
		"./fonts/mono-bold-oblique.tff", // bold-italic font 
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
