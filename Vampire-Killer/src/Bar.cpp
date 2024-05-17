#include <raylib.h>
#include "Bar.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "Sprite.h"

Bar::Bar(int m, Color c, Point& pos, int w, int h) : Entity(pos, w, h)
{
	max = m;
	current = max;
	col = c;
	width = w;
	height = h;
	Initialise();
}
Bar::Bar() {};
Bar::~Bar() {}
AppStatus Bar::Initialise()
{
	ResourceManager& data = ResourceManager::Instance();
	if (data.LoadTexture(Resource::IMG_BAR, "Assets/Bar.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}

	render = new Sprite(data.GetTexture(Resource::IMG_BAR));
	if (render == nullptr)
	{
		LOG("Failed to allocate memory for bar sprite");
		return AppStatus::ERROR;
	}

	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetNumberAnimations(1);

	float n = 2;
	sprite->SetAnimationDelay(0, 0);

	sprite->AddKeyFrame(0, { 0, n * 9, 40, 2 });
	sprite->AddKeyFrame(0, { 0, n * 8, 40, 2 });
	sprite->AddKeyFrame(0, { 0, n * 7, 40, 2 });
	sprite->AddKeyFrame(0, { 0, n * 6, 40, 2 });
	sprite->AddKeyFrame(0, { 0, n * 5, 40, 2 });
	sprite->AddKeyFrame(0, { 0, n * 4, 40, 2 });
	sprite->AddKeyFrame(0, { 0, n * 3, 40, 2 });
	sprite->AddKeyFrame(0, { 0, n * 2, 40, 2 });
	sprite->AddKeyFrame(0, { 0, n, 40, 2 });
	sprite->AddKeyFrame(0, { 0, 0, 40, 2 });

	sprite->SetAnimation(0);
}
int Bar::getCurrent()
{
	return current;
}
void Bar::changeBar(int life)
{
	width = life * 3;
}
void Bar::Draw()
{
	/*
	Point p = GetRenderingPosition();
	render->DrawTint(p.x, p.y, col);
	*/
	Point p = GetRenderingPosition();
	DrawRectangle(p.x, p.y, width, height, col);
}