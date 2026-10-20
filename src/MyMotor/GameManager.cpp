#include "GameManager.h"
#include <iostream>
#include <cmath>
#include "MyLib/Collideable.h"
#include "MyLib/Sprite.h"
#include "MyLib/Writer.h"
#include "MyLib/SoundLector.h"
#include "MyMotor/Timer.h"
#include "MyMotor/RectCollider.h"
#include "MyMotor/CircleCollider.h"
#include "MyMotor/UI.h"
#include "MyMotor/Camera.h"
#include "Game1/Player.h"
#include <Game1/PlayerScene.h>
#include "Game1/LevelManager.h"
#include "Game1/Point.h"
#include "Window.h"
#include "Input.h"
#include "BackGroundManager.h"
#include <fstream>
#include <functional>

#define WIDTH 1000
#define HEIGHT 800

GameManager::GameManager(const char* title, int x, int y, int w, int h, unsigned int flags)
{
	_window = new Window(title, x, y, w, h, flags);
}
GameManager::~GameManager()
{
	delete _backGroundManager;
	_backGroundManager = nullptr;

	delete _camera;
	_camera = nullptr;

	delete _ui;
	_ui = nullptr;

	// Les vecteurs ne sont PAS propriétaires : on les vide, sans delete
	_entities.clear();
	_rectangles.clear();
	_collideables.clear();
	_checkPoints.clear();
	_rectColliders.clear();
	_circleColliders.clear();
	_player = nullptr;

	delete _window;   // en dernier
	_window = nullptr;
}

SceneManager* GameManager::GetSceneManager()
{
	return SceneManager::GetInstance();
}
void GameManager::Initialize()
{
	InitializeOnce();
	ResetGame();
	_window->SetIsrunning(0);
}
void GameManager::InitializeOnce()
{
	_input = Input::Get();

	_ui = new UI(GetWindow(), Vector2(0, 0), Vector2(500, 350), Vector2(0, 0));
	_ui->OnInitialize();
	_ui->LoadFont();
	_ui->SetMusicState(_musicMutted);
	_ui->CreateMuteButton(*_window, 0, HEIGHT - 100, 100, 100);

	SoundLector::GetInstance()->Initialize();
	SoundLector::GetInstance()->SetMusicVolume(_ui->GetMuteState() ? 0 : 50);
	SoundLector::GetInstance()->LoadLongMusic("mainMusic", "forestAmbiant.mp3");
	SoundLector::GetInstance()->PlayLongMusic("mainMusic", -1);

	_backGroundManager = new BackGroundManager();
	_backGroundManager->LoadBackGround(GetWindow(), "foret.bmp");
	_backGroundManager->LoadBackGround(GetWindow(), "foret.bmp");
	_backGroundManager->SetBackGroundScale(0, WIDTH, HEIGHT);
	_backGroundManager->SetBackGroundScale(1, WIDTH, HEIGHT);

}

void GameManager::ResetGame()
{
	_player = SceneManager::GetInstance()->GetCurrentScene()->GetEntity<Player>();

	delete _camera;
	_camera = new Camera(Vector2(0, 0), Vector2(1, 1), Vector2(0, 0));
	_camera->Initialize(_player);

	_ui->SetPlayerHighScore(LoadHighScore());
	_ui->SetPlayerLastScore(LoadLastScore());
	_ui->CreateTitle(*_window, _window->GetWidth() / 4, 2, 500, 500);

	_levelManager = std::make_unique<LevelManager>();
	_timer = std::make_unique<Timer>();
	_timer->Get_Deltatime();

	_waitingScreen = true;

}

void GameManager::Loop()
{
	
	while (_window->GetRunningState() && !_quitRequested)
	{
		_waitingScrollX += _waitingScrollSpeed * _deltatime;
		//SWITCH TO GAMEOVER SCENE
		Player* p = SceneManager::GetInstance()->GetCurrentScene()->GetEntity<Player>();
		if (p != nullptr)
			_player = p;
		
		_window->Clear();
		_camRight = _camera->GetRightBorder();
		_camLeft = _camera->GetLeftBorder();
		_camTop = _camera->GetTopBorder();
		_camBot = _camera->GetBotBorder();
		_deltatime = _timer->Get_Deltatime();
		_camera->OnUpdate(_deltatime);
	
		_levelManager->SetCamera(_camera);
		float bgWidth = _backGroundManager->GetBackGround(0)->GetScale().GetX();
		float scroll = fmod(_waitingScrollX, bgWidth);
		_offsetX = fmod(_camera->GetRawPos().GetX(), bgWidth);
		
		//_backGroundManager->SetBackGroundPos(0, _camera->GetRawPos().GetX() - _offsetX, 0);
		//_backGroundManager->SetBackGroundPos(1, _camera->GetRawPos().GetX() - _offsetX + bgWidth, 0);
		
		_backGroundManager->SetBackGroundPos(0, _camera->GetRawPos().GetX() - scroll, 0);
		_backGroundManager->SetBackGroundPos(1, _camera->GetRawPos().GetX() - scroll + bgWidth, 0);
		_window->Event();
		
		Input::Get()->Update();
		_ui->OnUpdate(_deltatime);
		
		_entities = SceneManager::GetInstance()->GetCurrentScene()->GetAllEntity<Entity>();
		_rectangles = SceneManager::GetInstance()->GetCurrentScene()->GetAllEntity<Rectangle>();
		_collideables = SceneManager::GetInstance()->GetCurrentScene()->GetAllEntity<Collideable>();
		_checkPoints = SceneManager::GetInstance()->GetCurrentScene()->GetAllEntity<Point>();
		_rectColliders = SceneManager::GetInstance()->GetCurrentScene()->GetAllRectColliders();
 		_circleColliders = SceneManager::GetInstance()->GetCurrentScene()->GetAllCircleColliders();
	
		
		SceneManager::GetInstance()->GetCurrentScene()->Update(_deltatime);
		
		_backGroundManager->DrawAllBackGrounds(GetWindow(), _camera);
		
		_ui->DrawTitle(*_window, _camera);
	
		if (_waitingScreen)
		{
			_window->ShowDrawable(SceneManager::GetInstance()->GetCurrentScene(), _camera);
			if(_player != nullptr)
				_player->SetWaitingState(1);
	
			_ui->ShowText("HIGHSCORE:", false,850, 5, 0.35, 0.4);
			_ui->ShowNumber(_ui->GetPlayerHighScore(), false, 905, 25, 0.65, 0.4);
			_ui->ShowText("LASTSCORE:", false, 850, 60, 0.35, 0.4);
			_ui->ShowNumber(_ui->GetPlayerLastScore(), false, 905, 80, 0.63, 0.4);
			_ui->ShowText("   Press M to MUTE and UNMUTE the ambient sound.", false, WIDTH / 6, HEIGHT - 100, 0.35, 0.4);
			_ui->ShowText("   Press R to replay and Q to quit.", false, WIDTH / 4, HEIGHT - 150, 0.35, 0.4);
			_ui->ShowText("Controls: press SPACE or MOUSE CLICK or UP to play !", false, WIDTH / 6, HEIGHT - 50, 0.35, 0.4);
			
			if (_player != nullptr)
				_player->MooveInWaitingState();
			_ui->MooveTile(0);
			
			
			if (_input->IsMouseDown(0)  || _input->IsMouseDown(2)  || _input->IsKeyDown(KEYCODE_SPACE) || _input->IsKeyDown(KEYCODE_UP))
			{
				_waitingScreen = false;
			}

			if(_input->IsKeyDown(KEYCODE_A))
			{
				_quitRequested = true;
			}
			
		}
	
		else
		{

			_ui->MooveTile(1);
			if (_player != nullptr)
				_player->SetWaitingState(0);
		}
		
		if (_gameOver == false)
		{
			_window->ShowDrawable(SceneManager::GetInstance()->GetCurrentScene(), _camera);
			if(!_waitingScreen)
				_levelManager->OnUpdate(_deltatime, _player);

			for (int i = 0; i < _collideables.size(); ++i)
			{
				for (int j = i + 1; j < _collideables.size(); ++j)
				{
					
					Entity* eI = dynamic_cast<Entity*>(_collideables[i]);
					Entity* eJ = dynamic_cast<Entity*>(_collideables[j]);

					if (!eI || !eJ) continue;
					if (eI->IsDestroy() || eJ->IsDestroy()) continue;
					if (_player == nullptr) continue;
					bool collision = false;

					if (_collideables[i]->GetCircleCollider() && _collideables[j]->GetCircleCollider())
					{
						collision = _collideables[i]->GetCircleCollider()->IsCollidingCircle(_collideables[j]->GetCircleCollider());
					}

					if (!collision && _collideables[i]->GetCircleCollider() && _collideables[j]->GetRectCollider())
					{
						collision = _collideables[i]->GetCircleCollider()->IsCollidingRect(_collideables[j]->GetRectCollider());
					}

					if (collision)
					{
						_collideables[i]->OnCollision(_collideables[j]);
						if (eI->IsDestroy() || eJ->IsDestroy()) continue;
						_collideables[j]->OnCollision(_collideables[i]);
					}

				}
				
				if (_player != nullptr && _player->IsDestroy() == true && _gameOver == false )
				{
					_player->SaveHighScore(_player->GetScore());
					_ui->SetPlayerHighScore(LoadHighScore());
					_waitingScreen = true;
					_gameOver = true;
					std::cout << "GameOver Scene\n";
				}	
				
				for (Entity* e : _entities)
				{
					if (e != _player && e!= _ui->GetTitle() && e->GetPos().GetX()  < _camLeft - 110 && !e->GetScale().GetX() > WIDTH)
					{
						e->SetRangeState(0);
					}
					if (e == _ui->GetTitle() && e->GetPos().GetY() + e->GetScale().GetY() < _camLeft - 110)
					{
						
						e->SetRangeState(0);
						std::cout << "Title destroyed";
					}
					
				}
			}

			_ui->SetPos(_window->GetWidth() / 4, HEIGHT / 3);
		
			_ui->OnUpdate(_deltatime);

			_ui->SwitchIcon(*_window);
			_ui->DrawMuteButton(*_window, _camera);

			_ui->ShowNumber(_avgFps, false, 0, 5);
			if(_player)
				_ui->ShowNumber(_player->GetScore(), false, WIDTH / 2, 5);//Score in Game
			_ui->ShowText("HIGHSCORE:", false,850, 5, 0.35, 0.4);
			_ui->ShowNumber(_ui->GetPlayerHighScore(), false, 905, 25, 0.65, 0.4);
			_ui->ShowText("FPS", false, 50, 5);
			if (_input->IsKeyDown(KEYCODE_SEMICOLON) || _input->IsKeyDown(KEYCODE_M))
			{
				_ui->SetMusicIsmuted(_musicMutted);
			}
			_frameCount++;
			if (_frameCount >= 10) // Moyenne toutes les 10 frames
			{
				_avgFps = (10.0f / (_deltatime * 10));
				_frameCount = 0;
			}
			_ui->SetPlayerScore(_player->GetScore());
		}	

		std::vector<Entity*> toDestroy;
		for (int i = _entities.size() - 1; i >= 0; i--)
		{
			if (_entities[i]->IsDestroy() && _entities[i] != _player)
			{
				if (!_gameOver)
					toDestroy.push_back(_entities[i]);
			}
		}

		for (Entity* e : toDestroy)
		{
			SceneManager::GetInstance()->GetCurrentScene()->DestroyEntity(e);
			std::cout << "Entity Destroyed\n";
		}

		toDestroy.clear();

		if (_gameOver)
		{
			_window->ShowDrawable(SceneManager::GetInstance()->GetCurrentScene(), _camera);
			_backGroundManager->DrawAllBackGrounds(GetWindow(), _camera);
			_lastScore = _ui->GetPlayerScore();
		
			_ui->SetGameOver("true");
			_ui->DrawMenu(*_window, _camera);

			if (LoadMusicVolumeState(_ui->GetMuteState()) == true)
				_musicMutted = true;
			else
				_musicMutted = false;

			if (!_gameOverSet)
			{
				_ui->CreateQuitButton(*_window, 0.1, 0.6, 130, 80);
				_ui->CreateReplaytButton(*_window, 0.6, 0.6, 130, 80);
				
			}
			_ui->DrawButtons(*_window, _camera);
			_ui->ShowText("GAME OVER", true, 0, 0, 0.35, 0.1);
			_ui->ShowText("SCORE:", true, 0, 0, 0.35, 0.3);
			_ui->ShowNumber(_ui->GetPlayerScore(), true, 0, 0, 0.53, 0.3);
			_ui->ShowText("HIGHSCORE:", true, 0, 0, 0.35, 0.4);
		
			_ui->ShowNumber(_ui->GetPlayerHighScore(), true, 0, 0, 0.63, 0.4);
			_ui->ShowText("      Press R to replay and Q to quit.", false, WIDTH / 4, HEIGHT - 150, 0.35, 0.4);
			
			_ui->OnUpdate(_deltatime);
			
			if (_ui->MouseOnQuitButton() && _input->IsMouseDown(0) || _input->IsKeyDown(KEYCODE_Q))
			{
				_quitRequested = true;
				std::cout << "Mouse  Clicked On QuitButton\n";
				
			}

			else if (_ui->MouseOnReplayButton() && _input->IsMouseDown(0) || _input->IsKeyDown(KEYCODE_R))
			{
				//SoundLector::GetInstance()->Clean();
				_gameOver = false;
				_gameOverSet = false;

				SceneManager::GetInstance()->RemoveScene("Game");
				SceneManager::GetInstance()->AddScene("Game", new PlayerScene(this));
				
				_ui->AddReplayCount();
				SceneManager::GetInstance()->SetCurrentScene("Game");
				Restart(); 
				std::cout << "Mouse Clicked On ReplayButton\n";
			}
		}

		if (_gameOver && !_gameOverSet)
		{
			_gameOverSet = true;
		}
		
		SceneManager::GetInstance()->GetCurrentScene()->FlushDeleted();
		
		_window->Update();

		if (_gameOverSet)
		{
			SceneManager::GetInstance()->SetCurrentScene("Game_Over");
		}
	}
	_ui->FreeFont();
	_ui->Clean();

	_entities.clear();

	SceneManager::GetInstance()->RemoveScene("Game");
}


void GameManager::Restart()
{
	_player = nullptr;
	
	_entities.clear();
	_collideables.clear();
	_rectColliders.clear();
	_circleColliders.clear();
	ResetGame();
}


std::string ComputeChecksum(int score)
{
	std::string secret = "Facile3367";
	std::string data = std::to_string(score) + secret;
	std::hash<std::string> hasher;
	return std::to_string(hasher(data));
}

int LoadVerifiedHighScore()
{
	std::ifstream inFile("highscore.txt");
	if (!inFile.is_open())
		return 0;

	int score = 0;
	std::string checksum;
	inFile >> score >> checksum;
	inFile.close();

	if (ComputeChecksum(score) != checksum)
		return 0;

	return score;
}

int GameManager::LoadHighScore()
{
	return LoadVerifiedHighScore();
}

int GameManager::LoadLastScore()
{
	return _lastScore;
}

bool GameManager::LoadMusicVolumeState(bool state)
{
	return state;
}

Window& GameManager::GetWindow()
{
	return *_window;
}

UI* GameManager::GetUI()
{
	return _ui;
}

Player* GameManager::Get_Player()
{
	return _player;
}

float GameManager::GetOffsetX()
{
	return _offsetX;
}

