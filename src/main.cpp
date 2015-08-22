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
	int rows = 12;
	int cols = 32;

	VTerm *vt = vterm_new(rows, cols);
	VTermScreen *vts = vterm_obtain_screen(vt);
	vterm_screen_reset(vts, 1);

	const VTermColor bg = {0, 0, 0};
	const VTermColor fg = {255, 255, 255};
	vterm_state_set_default_colors(vterm_obtain_state(vt), &bg, &fg);

	Render render(vt,
		"-*-dejavu sans mono-%s-%s-normal--%d-*-*-*-*-*-*-*", // font
		32, // font size
		10, // vertical margin
		10 // horizontal margin
		);

	char buf[256];
	sprintf(buf, "Hello, \033[1mworld!\n");
	vterm_input_write(vt, buf, strlen(buf));

	render.repaint();
	render.write("test.png");
	vterm_free(vt);
}
