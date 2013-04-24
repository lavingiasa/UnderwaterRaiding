#include "things.h"

using namespace std;

Thing::Thing( QPixmap* p, int nx, int ny ) 
{
	pixMap = p;
	x = nx;
	y = ny;
	setPos( x, y );
}

Player::Player(QPixmap *pm, int nx, int ny): Thing(pm, nx, ny)
{
	setPixmap(*pm);
}

Squid::Squid(QPixmap *pm, int nx, int ny, int left): Thing (pm, nx, ny)
{
	setPixmap(*pm);
	left_ = left;
}

void Squid::move()
{
	if(left_ == 1)
	{
		moveBy(-1,1);
	}else{
		moveBy(1,1);
	}
	x++;
	y--;
}
	
/*Manta::Manta(QPixMap *pm, int nx, int ny): Thing (pm, nx, ny)
{
	
}*/

void Manta::move()
{
	moveBy(1,-1);
}

/*Shark::Shark(QPixMap *pm, int nx, int ny): Thing (pm, nx, ny)
{
	
}*/

void Shark::move()
{
	moveBy(10,-10);
}

void Player::moveUp()
{
	cout << "Up" << endl;
	if(y > 0)
	{
		moveBy(0,-10);
		y = y - 10;
	}
}
void Player::moveDown()
{
	cout << "Down" << endl;
	if(y < WINDOW_MAX_Y*2-55)
	{
		moveBy(0,10);
		y = y + 10;
	}
}

void Player::moveLeft()
{
	cout << "Left" << endl;
	if(x > -WINDOW_MAX_X)
	{
		moveBy(-10,0);
		x = x - 10;
	}
}

void Player::moveRight()
{
	cout << "Right" << endl;
	if(x < WINDOW_MAX_X*2)
	{
		moveBy(10,0);
		x = x + 10;
	}

}

void Player::move()
{
	
}
