/* 

SDL2_gfxPrimitives.h: graphics primitives for SDL

Copyright (C) 2012-2014  Andreas Schiffler
Additions for BBC BASIC (C) 2016-2020 Richard Russell

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.

Andreas Schiffler -- aschiffler at ferzkopp dot net
Richard Russell -- richard at rtrussell dot co dot uk

*/

#ifndef _SDL2_gfx_extra_h
#define _SDL2_gfx_extra_h


#include "SDL.h"

	/* Richard Russell's additions */

	 int thickEllipseColor(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint32 color, Uint8 thick);
	 int thickEllipseRGBA(SDL_Renderer * renderer, Sint16 xc, Sint16 yc, Sint16 xr, Sint16 yr, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint8 thick);
	 int thickArcColor(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad, Sint16 start, Sint16 end, Uint32 color, Uint8 thick);
	 int thickArcRGBA(SDL_Renderer * renderer, Sint16 xc, Sint16 yc, Sint16 rad, Sint16 start, Sint16 end, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint8 thick);
	 int thickCircleColor(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad, Uint32 color, Uint8 thick);
	 int thickCircleRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint8 thick);
	 int filledPolyBezierColor(SDL_Renderer * renderer, const Sint16 *x, const Sint16 *y, int n, int s, Uint32 color);
	 int filledPolyBezierRGBA(SDL_Renderer * renderer, const Sint16 *x, const Sint16 *y, int n, int s, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	 int aaFilledEllipseColor(SDL_Renderer * renderer, float cx, float cy, float rx, float ry, Uint32 color);
	 int aaFilledEllipseRGBA(SDL_Renderer * renderer, float cx, float cy, float rx, float ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a); 
	 int aaFilledPolygonColor(SDL_Renderer * renderer, const double * vx, const double * vy, int n, Uint32 color);
	 int aaFilledPolygonRGBA(SDL_Renderer * renderer, const double * vx, const double * vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	 int aaFilledPieColor(SDL_Renderer * renderer, float cx, float cy, float rx, float ry, float start, float end, Uint32 chord, Uint32 color);
	 int aaFilledPieRGBA(SDL_Renderer * renderer, float cx, float cy, float rx, float ry,
	 	float start, float end, Uint32 chord, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	 int aaArcColor(SDL_Renderer * renderer, float cx, float cy, float rx, float ry, float start, float end, float thick, Uint32 color);
	 int aaArcRGBA(SDL_Renderer * renderer, float cx, float cy, float rx, float ry,
	 	float start, float end, float thick, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	 int aaBezierColor(SDL_Renderer * renderer, double *x, double *y, int n, int s, float thick, Uint32 color);
	 int aaBezierRGBA(SDL_Renderer * renderer, double *x, double *y, int n, int s, float thick, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	 int aaFilledPolyBezierColor(SDL_Renderer * renderer, double *x, double *y, int n, int s, Uint32 color);
	 int aaFilledPolyBezierRGBA(SDL_Renderer * renderer, double *x, double *y, int n, int s, Uint8 r, Uint8 g, Uint8 b, Uint8 a);


#endif				/* _SDL2_gfx_extra_h */
