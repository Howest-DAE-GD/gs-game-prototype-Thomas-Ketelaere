#pragma once
#include "BaseGame.h"
#include "utils.h"
using namespace utils;

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;

	//VARIABLES
	Rectf m_BlueRectBottom{ 200,20, 50, 20 };
	Rectf m_BlueRectTop{ 200, 40, 20, 10 };

	Rectf m_RedRectBottom{ 420, 20, 30, 20 };
	Rectf m_RedRectTop{ 400, 30, 50, 10 };

	float m_RadiusSmall{500};
	float m_RadiusBig{ 600 };

	const float m_Speed{ 200 };
	const float m_CrimpSpeed{30};
	bool m_collision{};
	bool m_Won{};
	bool m_Message{};


};