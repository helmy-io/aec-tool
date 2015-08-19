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

#ifndef FILE_TERM_H
#define FILE_TERM_H

#include <vterm.h>

int on_line_push(int cols, const VTermScreenCell *cells, void *user);
int on_screen_resize(int new_rows, int new_cols, void *user);

// TODO: find a better way to initialize this
static VTermScreenCallbacks screen_callbacks = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&on_screen_resize,
	&on_line_push,
	NULL,
};

#endif
