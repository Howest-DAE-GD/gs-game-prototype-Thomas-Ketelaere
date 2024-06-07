#pragma once
#include "BaseGame.h"
#include "utils.h"
#include "Texture.h"

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

	void Reset();
	void UpdateLevelTexture();

	bool Counter(float ElapsedSec, float Delay);
	


	//POINTERS
	Texture* m_TextureWon;
	Texture* m_TextureLost;
	Texture* m_pLevel;

	//VARIABLES
	Rectf m_BlueRectBottom{ 100, 400, 50, 20 };
	Rectf m_BlueRectTop{ 100, 420, 20, 10 };

	Rectf m_RedRectBottom{ 720, 20, 30, 20 };
	Rectf m_RedRectTop{ 700, 30, 50, 10 };

	std::vector<Rectf> m_MazeVector;

	float m_RadiusSmall{ 500 };
	float m_RadiusBig{ 700 };
	float m_RadiusWon{};

	const float m_Speed{ 200 };
	const float m_CrimpSpeed{40};
	float m_AccumulatedTime{};
	int m_Level{1};
	int m_MaxLevel{4};
	bool m_Won{};
	bool m_GameDone{};
	bool m_Message{};


};