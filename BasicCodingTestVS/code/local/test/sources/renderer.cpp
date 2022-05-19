#include "renderer.hpp"
#include "SDL2/SDL.h"

Renderer::Renderer(SDL_Renderer* pRenderer) {
	m_pRenderer = pRenderer;
}

void Renderer::drawRect(float x, float y, float w, float h, Color c) {
	SDL_SetRenderDrawColor( m_pRenderer, ( Uint8 )( ( c >> 16 ) & 255 ), ( Uint8 )( ( c >> 8 ) & 255 ), ( Uint8 )( c & 255), ( Uint8 )255 );
	SDL_Rect rect;
	rect.x = ( int )x;
	rect.y = ( int )y;
	rect.w = ( int )w;
	rect.h = ( int )h;
	SDL_RenderFillRect(m_pRenderer, &rect);
}
