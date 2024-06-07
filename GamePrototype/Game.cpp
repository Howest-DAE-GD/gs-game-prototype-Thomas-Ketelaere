#include "pch.h"
#include "Game.h"
#include <fstream>
#include <iostream>

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_TextureLost = new Texture("You Lost", "font/DIN-Light.otf", 30, Color4f{ 1.f, 0.f, 0.f, 1.f });
	m_TextureWon = new Texture("You Won", "font/DIN-Light.otf", 30, Color4f{ 0.f, 0.f, 1.f, 1.f });
	std::string Level{ "Level: " + std::to_string(m_Level) };
	m_pLevel = new Texture(Level, "font/DIN-Light.otf", 30, Color4f{ 1.f, 0.f, 1.f, 1.f });


	m_MazeVector.push_back(Rectf{ 200, 200, 5, 300 });
	m_MazeVector.push_back(Rectf{ 600, 0, 5, 300 });
	m_MazeVector.push_back(Rectf{ 300, 0, 5, 300 });
	m_MazeVector.push_back(Rectf{ 500, 200, 5, 300 });
	m_MazeVector.push_back(Rectf{ 300, 300, 100, 5 });
	m_MazeVector.push_back(Rectf{ 400, 200, 100, 5 });
	m_MazeVector.push_back(Rectf{ 100, 200, 100, 5 });
	m_MazeVector.push_back(Rectf{ 600, 300, 100, 5 });
}

void Game::Cleanup( )
{
	delete m_TextureLost;
	m_TextureLost = nullptr;
	delete m_TextureWon;
	m_TextureWon = nullptr;
	delete m_pLevel;
	m_pLevel = nullptr;
}

void Game::Update( float elapsedSec )
{
	std::cout << m_Level * 2 - 1 << std::endl;
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );

	if (m_Won && m_GameDone)
	{
		m_RedRectTop.left = m_BlueRectTop.left;
		m_RedRectTop.bottom = m_BlueRectTop.bottom + m_BlueRectTop.height;
		m_RedRectBottom.left = m_BlueRectTop.left + m_BlueRectTop.width;
		m_RedRectBottom.bottom = m_BlueRectTop.bottom;
		
		m_RadiusWon += m_Speed * elapsedSec * 2;
		m_RadiusSmall += m_Speed * elapsedSec;

		if (Counter(elapsedSec, 5.f))
		{
			if (m_Level < m_MaxLevel)
			{
				++m_Level;
				std::cout << "level plus: " << m_Level << std::endl;
			}
			Reset();
			UpdateLevelTexture();
		}
	}

	else if (!m_Won && m_GameDone)
	{
		if (m_RadiusSmall >= 0)
		{
			m_RadiusSmall -= m_CrimpSpeed * elapsedSec * 10;
		}

		m_BlueRectBottom.left -= m_Speed * elapsedSec;
		m_BlueRectTop.left += m_Speed * elapsedSec;
		m_BlueRectBottom.bottom -= m_Speed * elapsedSec;
		m_BlueRectTop.bottom += m_Speed * elapsedSec;

		m_RedRectBottom.left += m_Speed * elapsedSec;
		m_RedRectTop.left -= m_Speed * elapsedSec;
		m_RedRectBottom.bottom -= m_Speed * elapsedSec;
		m_RedRectTop.bottom += m_Speed * elapsedSec;

		if (Counter(elapsedSec, 5.f))
		{
			m_Level = 1;
			Reset();
			UpdateLevelTexture();
		}
	}

	else if (!m_GameDone)
	{
		{
			//blue rect
			if (pStates[SDL_SCANCODE_D])
			{
				m_BlueRectBottom.left += m_Speed * elapsedSec;
				m_BlueRectTop.left += m_Speed * elapsedSec;
				for (int Maze{}; Maze <= m_Level * 2 - 1; ++Maze)
				{
					if (IsOverlapping(m_BlueRectBottom, m_MazeVector.at(Maze)) || IsOverlapping(m_BlueRectTop, m_MazeVector.at(Maze)))
					{
						m_BlueRectBottom.left -= m_Speed * elapsedSec;
						m_BlueRectTop.left -= m_Speed * elapsedSec;
					}
				}

			}
			if (pStates[SDL_SCANCODE_A])
			{
				m_BlueRectBottom.left -= m_Speed * elapsedSec;
				m_BlueRectTop.left -= m_Speed * elapsedSec;

				for (int Maze{}; Maze <= m_Level * 2 - 1; ++Maze)
				{
					if (IsOverlapping(m_BlueRectBottom, m_MazeVector.at(Maze)) || IsOverlapping(m_BlueRectTop, m_MazeVector.at(Maze)))
					{
						m_BlueRectBottom.left += m_Speed * elapsedSec;
						m_BlueRectTop.left += m_Speed * elapsedSec;
					}
				}
			}

			if (pStates[SDL_SCANCODE_W])
			{
				m_BlueRectBottom.bottom += m_Speed * elapsedSec;
				m_BlueRectTop.bottom += m_Speed * elapsedSec;

				for (int Maze{}; Maze <= m_Level * 2 - 1; ++Maze)
				{
					if (IsOverlapping(m_BlueRectBottom, m_MazeVector.at(Maze)) || IsOverlapping(m_BlueRectTop, m_MazeVector.at(Maze)))
					{
						m_BlueRectBottom.bottom -= m_Speed * elapsedSec;
						m_BlueRectTop.bottom -= m_Speed * elapsedSec;
					}
				}

			}
			if (pStates[SDL_SCANCODE_S])
			{
				m_BlueRectBottom.bottom -= m_Speed * elapsedSec;
				m_BlueRectTop.bottom -= m_Speed * elapsedSec;

				for (int Maze{}; Maze <= m_Level * 2 - 1; ++Maze)
				{
					if (IsOverlapping(m_BlueRectBottom, m_MazeVector.at(Maze)) || IsOverlapping(m_BlueRectTop, m_MazeVector.at(Maze)))
					{
						m_BlueRectBottom.bottom += m_Speed * elapsedSec;
						m_BlueRectTop.bottom += m_Speed * elapsedSec;
					}
				}
			}

			//red

			if (pStates[SDL_SCANCODE_RIGHT])
			{
				m_RedRectBottom.left += m_Speed * elapsedSec;
				m_RedRectTop.left += m_Speed * elapsedSec;

				for (int Maze{}; Maze <= m_Level * 2 - 1; ++Maze)
				{
					if (IsOverlapping(m_RedRectBottom, m_MazeVector.at(Maze)) || IsOverlapping(m_RedRectTop, m_MazeVector.at(Maze)))
					{
						m_RedRectBottom.left -= m_Speed * elapsedSec;
						m_RedRectTop.left -= m_Speed * elapsedSec;
					}
				}
			}
			if (pStates[SDL_SCANCODE_LEFT])
			{
				m_RedRectBottom.left -= m_Speed * elapsedSec;
				m_RedRectTop.left -= m_Speed * elapsedSec;

				for (int Maze{}; Maze <= m_Level * 2 - 1; ++Maze)
				{
					if (IsOverlapping(m_RedRectBottom, m_MazeVector.at(Maze)) || IsOverlapping(m_RedRectTop, m_MazeVector.at(Maze)))
					{
						m_RedRectBottom.left += m_Speed * elapsedSec;
						m_RedRectTop.left += m_Speed * elapsedSec;
					}
				}
			}

			if (pStates[SDL_SCANCODE_UP])
			{
				m_RedRectBottom.bottom += m_Speed * elapsedSec;
				m_RedRectTop.bottom += m_Speed * elapsedSec;

				for (int Maze{}; Maze <= m_Level * 2 - 1; ++Maze)
				{
					if (IsOverlapping(m_RedRectBottom, m_MazeVector.at(Maze)) || IsOverlapping(m_RedRectTop, m_MazeVector.at(Maze)))
					{
						m_RedRectBottom.bottom -= m_Speed * elapsedSec;
						m_RedRectTop.bottom -= m_Speed * elapsedSec;
					}
				}
			}
			if (pStates[SDL_SCANCODE_DOWN])
			{
				m_RedRectBottom.bottom -= m_Speed * elapsedSec;
				m_RedRectTop.bottom -= m_Speed * elapsedSec;

				for (int Maze{}; Maze <= m_Level * 2 - 1; ++Maze)
				{
					if (IsOverlapping(m_RedRectBottom, m_MazeVector.at(Maze)) || IsOverlapping(m_RedRectTop, m_MazeVector.at(Maze)))
					{
						m_RedRectBottom.bottom += m_Speed * elapsedSec;
						m_RedRectTop.bottom += m_Speed * elapsedSec;
					}
				}
			}

			//UpdateVillain
			if (m_RadiusSmall >= 0)
			{
				m_RadiusSmall -= m_CrimpSpeed * elapsedSec;
			}

		}

		if (IsOverlapping(m_RedRectBottom, m_BlueRectBottom))
		{
			m_Won = true;
			if (!m_Message)
			{
				std::cout << "won" << std::endl;
				m_Message = true;
				m_GameDone = true;
			}
		}

		if (!IsOverlapping(m_RedRectBottom, Circlef{ Point2f{ 423.f, 250.f }, m_RadiusSmall }) || !IsOverlapping(m_BlueRectBottom, Circlef{ Point2f{ 423.f, 250.f }, m_RadiusSmall }))
		{
			m_Won = false;
			if (!m_Message)
			{
				std::cout << "lost" << std::endl;
				m_Message = true;
				m_GameDone = true;
			}
		}
	}
	
}

void Game::Draw( ) const
{
	ClearBackground( );

	SetColor(Color4f{ 1.f, 0.6f, 0.f, 1.f });
	FillEllipse(Point2f{ GetViewPort().width / 2, GetViewPort().height / 2 }, m_RadiusBig, m_RadiusBig);

	SetColor(Color4f{ 0.f, 0.f, 0.f, 1.f });
	FillEllipse(Point2f{ GetViewPort().width / 2, GetViewPort().height / 2 }, m_RadiusSmall, m_RadiusSmall);

	SetColor(Color4f{ 1.f, 1.f, 1.f, 1.f });
	FillEllipse(Point2f{ GetViewPort().width / 2, GetViewPort().height / 2 }, m_RadiusWon, m_RadiusWon);

	SetColor(Color4f{ 0.f, 0.f, 1.f, 1.f });
	FillRect(m_BlueRectBottom);
	FillRect(m_BlueRectTop);

	SetColor(Color4f{ 1.f, 0.f, 0.f, 1.f });
	FillRect(m_RedRectBottom);
	FillRect(m_RedRectTop);

	SetColor(Color4f{ 1.f, 1.f, 1.f, 1.f });

	for (int wallDraw{}; wallDraw <= m_Level * 2 - 1; ++wallDraw)
	{
		FillRect(m_MazeVector.at(wallDraw));
	}

	if (m_Won && m_GameDone)
	{
		m_TextureWon->Draw(Point2f{ GetViewPort().width /2 - m_TextureWon->GetWidth() / 2, 400.f}, Rectf{0.f, 0.f, m_TextureWon->GetWidth(), 30});
	}

	if (!m_Won && m_GameDone)
	{
		m_TextureLost->Draw(Point2f{ GetViewPort().width / 2 - m_TextureLost->GetWidth() / 2, 400.f }, Rectf{ 0.f, 0.f, m_TextureLost->GetWidth(), 30 });
	}

	m_pLevel->Draw(Point2f{ GetViewPort().width / 2 - m_pLevel->GetWidth() / 2, 450.f }, Rectf{ 0.f, 0.f, m_pLevel->GetWidth(), 30 });
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::Reset()
{
	m_BlueRectBottom.left = 100;
	m_BlueRectBottom.bottom = 400;

	m_BlueRectTop.left = 100;
	m_BlueRectTop.bottom = 420;

	m_RedRectBottom.left = 720;
	m_RedRectBottom.bottom = 20;

	m_RedRectTop.left = 700;
	m_RedRectTop.bottom = 30;

	m_RadiusSmall = 500;
	m_RadiusBig = 700;
	m_RadiusWon = 0;

	m_GameDone = false;
	m_Message = false;

	std::cout << "reset " << std::endl;
}

void Game::UpdateLevelTexture()
{
	delete m_pLevel;
	m_pLevel = nullptr;

	std::string Level{ "Level: " + std::to_string(m_Level) };
	m_pLevel = new Texture(Level, "font/DIN-Light.otf", 30, Color4f{ 1.f, 0.f, 1.f, 1.f });
}

bool Game::Counter(float ElapsedSec, float Delay)
{
	m_AccumulatedTime += ElapsedSec;
	if (m_AccumulatedTime >= Delay)
	{
		m_AccumulatedTime = true;
		return true;
	}

	return false;
	
}

