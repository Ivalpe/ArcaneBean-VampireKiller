#include "Game.h"
#include "Globals.h"
#include "ResourceManager.h"
#include <stdio.h>
#include "raylib.h"

Game::Game()
{
	state = GameState::MAIN_SCREEN;
	scene = nullptr;
	img_menu = nullptr;
	img_mscreen = nullptr;
	img_gameover = nullptr;
	posYCredits = WINDOW_HEIGHT;

	target = {};
	src = {};
	dst = {};
}
Game::~Game()
{
	if (scene != nullptr)
	{
		scene->Release();
		delete scene;
		scene = nullptr;
	}
}
AppStatus Game::Initialise(float scale)
{
	float w, h;
	w = WINDOW_WIDTH * scale;
	h = WINDOW_HEIGHT * scale;

	//Initialise window
	InitWindow((int)w, (int)h, "Vampire Killer");

	//Render texture initialisation, used to hold the rendering result so we can easily resize it
	target = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
	if (target.id == 0)
	{
		LOG("Failed to create render texture");
		return AppStatus::ERROR;
	}
	SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
	src = { 0, 0, WINDOW_WIDTH, -WINDOW_HEIGHT };
	dst = { 0, 0, w, h };

	//Load resources
	if (LoadResources() != AppStatus::OK)
	{
		LOG("Failed to load resources");
		return AppStatus::ERROR;
	}

	//Set the target frame rate for the application
	SetTargetFPS(60);

	//Disable the escape key to quit functionality
	SetExitKey(0);

	//ToggleFullscreen();

	return AppStatus::OK;
}
AppStatus Game::LoadResources()
{
	ResourceManager& data = ResourceManager::Instance();

	if (data.LoadTexture(Resource::IMG_MENU, "Assets/InitialScreen.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}
	img_menu = data.GetTexture(Resource::IMG_MENU);

	if (data.LoadTexture(Resource::IMG_MSCREEN, "Assets/MainScreen.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}
	img_mscreen = data.GetTexture(Resource::IMG_MSCREEN);

	if (data.LoadTexture(Resource::IMG_GAMEOVER, "Assets/GameOver.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}
	img_gameover = data.GetTexture(Resource::IMG_GAMEOVER);

	if (data.LoadTexture(Resource::IMG_ENDING, "Assets/GameWin.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}
	img_ending = data.GetTexture(Resource::IMG_ENDING);

	if (data.LoadTexture(Resource::IMG_CREDITS, "Assets/Ending.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}
	img_credits = data.GetTexture(Resource::IMG_CREDITS);

	return AppStatus::OK;
}



AppStatus Game::BeginPlay()
{
	scene = new Scene();
	if (scene == nullptr)
	{
		LOG("Failed to allocate memory for Scene");
		return AppStatus::ERROR;
	}
	if (scene->Init() != AppStatus::OK)
	{
		LOG("Failed to initialise Scene");
		return AppStatus::ERROR;
	}

	return AppStatus::OK;
}
void Game::FinishPlay()
{
	scene->Release();
	delete scene;
	scene = nullptr;
}
AppStatus Game::Update()
{
	//Only sum if there is in the main screen or the game over the screen
	if (state == GameState::MAIN_SCREEN || state == GameState::GAME_OVER || state == GameState::GAME_WIN)	frameCount++;

	//Check if user attempts to close the window, either by clicking the close button or by pressing Alt+F4
	if (WindowShouldClose()) return AppStatus::QUIT;

	switch (state)
	{
	case GameState::MAIN_SCREEN:
		if (frameCount >= HOLD_FRAMES) {
			state = GameState::MAIN_MENU;
			frameCount = 0;
		}
		break;
	case GameState::MAIN_MENU:
		if (IsKeyPressed(KEY_ESCAPE)) return AppStatus::QUIT;
		if (IsKeyPressed(KEY_SPACE))
		{
			if (BeginPlay() != AppStatus::OK) return AppStatus::ERROR;
			state = GameState::PLAYING;
		}
		break;

	case GameState::PLAYING:
		if (scene->getLevelOver())
			state = GameState::GAME_OVER;

		if (scene->getLevelWin())
			state = GameState::GAME_WIN;

		if (IsKeyPressed(KEY_ESCAPE))
		{
			FinishPlay();
			state = GameState::MAIN_MENU;
		}
		else
		{
			//Game logic
			scene->Update();
		}
		break;

	case GameState::GAME_OVER:
		if (frameCount >= HOLD_FRAMES) {
			state = GameState::MAIN_MENU;
			frameCount = 0;
		}
		break;
	case GameState::GAME_WIN:
		if (frameCount >= HOLD_FRAMES * 2) {
			state = GameState::MAIN_MENU;
			frameCount = 0;
		}
		break;
	}

	return AppStatus::OK;
}
void Game::Render()
{


	//Draw everything in the render texture, note this will not be rendered on screen, yet
	BeginTextureMode(target);
	ClearBackground(BLACK);

	switch (state)
	{
	case GameState::MAIN_SCREEN:
		DrawTexture(*img_mscreen, 0, 0, WHITE);
		break;

	case GameState::MAIN_MENU:
		DrawTexture(*img_menu, 0, 0, WHITE);
		break;

	case GameState::PLAYING:
		scene->Render();
		break;

	case GameState::GAME_OVER:
		DrawTexture(*img_gameover, 0, 0, WHITE);
		break;
	case GameState::GAME_WIN:
		DrawTexture(*img_ending, 0, 0, WHITE);
		DrawTexture(*img_credits, (WINDOW_WIDTH - 193) / 2 , posYCredits-- , WHITE);
		break;
	}

	EndTextureMode();

	//Draw render texture to screen, properly scaled
	BeginDrawing();
	DrawTexturePro(target.texture, src, dst, { 0, 0 }, 0.0f, WHITE);
	EndDrawing();
}
void Game::Cleanup()
{
	UnloadResources();
	CloseWindow();
}
void Game::UnloadResources()
{
	ResourceManager& data = ResourceManager::Instance();
	data.ReleaseTexture(Resource::IMG_MENU);
	data.ReleaseTexture(Resource::IMG_MSCREEN);
	data.ReleaseTexture(Resource::IMG_CREDITS);
	data.ReleaseTexture(Resource::IMG_ENDING);

	UnloadRenderTexture(target);
}