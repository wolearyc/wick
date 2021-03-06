/* ----------------------------------------------------------------------------
 * wic - a simple 2D game engine for Mac OSX written in C
 * Copyright (C) 2013-2017  Willis O'Leary
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * ----------------------------------------------------------------------------
 * File:    wic_font.h
 * ----------------------------------------------------------------------------
 */
/** \file */
#ifndef WIC_FONT_H
#define WIC_FONT_H
#include "FreeType/ft2build.h"
#include FT_FREETYPE_H
#include FT_BITMAP_H
#include "wic_game.h"
#include "wic_texture.h"
#include "wic_image.h"
#include "wic_error.h"
/** \brief a font
 *
 *  A WicFont should be initialized via wic_init_font, which loads a font file
 *  to be used to draw text. A WicFont should eventually be deallocated via 
 *  wic_free_font.
 */
typedef struct WicFont WicFont;
/** \brief initializes a WicFont from a file
 *  \param filepath the absolute or relative filepath to a TrueType (TTF), 
 *         TrueType collection (TTC), Type 1 (PFA and PFB), CID-keyed Type 1,
 *         CFF, OpenType, OpenType collection, SFNT-based bitmap, X11 PCF,
 *         Windows FNT, BDF, or PFR font file; the file must exist and be one of 
 *         the forementioned formats
 * \param point the size of the font measured in font points; must be > 0
 * \param antialias whether or not to antialias the font; antialiased fonts with
 *        a small point size can be difficult to read
 * \param game the game
 * \return a valid pointer to a WicFont on success, null on failure
 */
WicFont* wic_init_font(const char* filepath, unsigned point, bool antialias,
                       WicGame* game);
/** \brief deallocates a WicFont
 *  \param target the target WicFont
 *  \return true on success, false on failure
 */
bool wic_free_font(WicFont* target);
#endif
