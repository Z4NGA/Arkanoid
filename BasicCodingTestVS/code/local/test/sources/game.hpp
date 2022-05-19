#ifndef GAME_HPP
#define GAME_HPP

#include "gamebase.hpp"

class Game : public GameBase {
public:
	Game();
	virtual void update(float timeStep, float mouseX, float mouseY, bool pressed);
	virtual void render(Renderer& renderer);

private:
	float	m_x, m_y, m_time;
};

#endif
