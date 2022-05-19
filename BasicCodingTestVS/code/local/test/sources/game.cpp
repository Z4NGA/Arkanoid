#include "game.hpp"
#include "renderer.hpp"
#include <math.h>

Game::Game() : m_x(0.5f), m_y(0.5f), m_time(0) {
}

void Game::update(float timeStep, float mouseX, float mouseY, bool pressed) {
	m_x = mouseX;
	m_y = mouseY;
	m_time += timeStep * (pressed ? 5 : 1);
}

void Game::render(Renderer& renderer) {
	float w = ( float )sin( m_time ) * 20 + 25;

	float h = ( float )cos( m_time ) * 20 + 25;
	renderer.drawRect(m_x - w / 2, m_y - h / 2, w, h, Renderer::DARK_GREEN);
}
