#include "pch.h"
#include "Game.h"
#include "iostream"

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
	
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	if (m_collision && m_Won)
	{
		m_RedRectTop.left = m_BlueRectTop.left;
		m_RedRectTop.bottom = m_BlueRectTop.bottom + m_BlueRectTop.height;
		m_RedRectBottom.left = m_BlueRectTop.left + m_BlueRectTop.width;
		m_RedRectBottom.bottom = m_BlueRectTop.bottom;
	}

	else if (m_collision && !m_Won)
	{

	}

	else
	{
		//blue rect
		if (pStates[SDL_SCANCODE_D])
		{
			m_BlueRectBottom.left += m_Speed * elapsedSec;
			m_BlueRectTop.left += m_Speed * elapsedSec;
		}
		if (pStates[SDL_SCANCODE_A])
		{
			m_BlueRectBottom.left -= m_Speed * elapsedSec;
			m_BlueRectTop.left -= m_Speed * elapsedSec;
		}

		if (pStates[SDL_SCANCODE_W])
		{
			m_BlueRectBottom.bottom += m_Speed * elapsedSec;
			m_BlueRectTop.bottom += m_Speed * elapsedSec;
		}
		if (pStates[SDL_SCANCODE_S])
		{
			m_BlueRectBottom.bottom -= m_Speed * elapsedSec;
			m_BlueRectTop.bottom -= m_Speed * elapsedSec;
		}

		//red

		if (pStates[SDL_SCANCODE_RIGHT])
		{
			m_RedRectBottom.left += m_Speed * elapsedSec;
			m_RedRectTop.left += m_Speed * elapsedSec;
		}
		if (pStates[SDL_SCANCODE_LEFT])
		{
			m_RedRectBottom.left -= m_Speed * elapsedSec;
			m_RedRectTop.left -= m_Speed * elapsedSec;
		}

		if (pStates[SDL_SCANCODE_UP])
		{
			m_RedRectBottom.bottom += m_Speed * elapsedSec;
			m_RedRectTop.bottom += m_Speed * elapsedSec;
		}
		if (pStates[SDL_SCANCODE_DOWN])
		{
			m_RedRectBottom.bottom -= m_Speed * elapsedSec;
			m_RedRectTop.bottom -= m_Speed * elapsedSec;
		}

		//UpdateVillain
		m_RadiusSmall -= m_CrimpSpeed * elapsedSec;

	}
	
	if (IsOverlapping(m_RedRectBottom, m_BlueRectBottom))
	{
		m_collision = true;
		m_Won = true;
		if (!m_Message)
		{
			std::cout << "won" << std::endl;
			m_Message = true;
		}
	}

	if (!IsOverlapping(m_RedRectBottom, Circlef{ Point2f{ 423.f, 250.f }, m_RadiusSmall }) || !IsOverlapping(m_BlueRectBottom, Circlef{ Point2f{ 423.f, 250.f }, m_RadiusSmall }))
	{
		m_collision = true;
		m_Won = false; 
		if (!m_Message)
		{
			std::cout << "false" << std::endl;
			m_Message = true;
		}
	}



}



void Game::Draw( ) const
{
	ClearBackground( );

	SetColor(Color4f{ 0.f, 1.f, 0.f, 1.f });
	FillEllipse(Point2f{ 423.f, 250.f }, m_RadiusBig, m_RadiusBig);

	SetColor(Color4f{ 0.f, 0.f, 0.f, 1.f });
	FillEllipse(Point2f{ 423.f, 250.f }, m_RadiusSmall, m_RadiusSmall);

	SetColor(Color4f{ 0.f, 0.f, 1.f, 1.f });
	FillRect(m_BlueRectBottom);
	FillRect(m_BlueRectTop);

	SetColor(Color4f{ 1.f, 0.f, 0.f, 1.f });
	FillRect(m_RedRectBottom);
	FillRect(m_RedRectTop);


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
