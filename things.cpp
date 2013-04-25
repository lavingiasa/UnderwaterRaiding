#include "things.h"

using namespace std;

Thing::Thing( QPixmap* p, int nx, int ny ) 
{
	pixMap = p;
	x = nx;
	y = ny;
	setPos( x, y );
}

int Thing::getY()
{
	return y;
}

int Thing::getX()
{
	return x;
}

Player::Player(QPixmap *pm, int nx, int ny): Thing(pm, nx, ny)
{
	setPixmap(*pm);
	hp_= 3;
}

void Thing::isHit()
{
	hp_--;
}


bool Thing::isBad()
{
	if(bad == 1)
	{
		return true;
	}else{
		return false;
	}
}

Squid::Squid(QPixmap *pm, int nx, int ny, int left): Thing (pm, nx, ny)
{
	setPixmap(*pm);
	left_ = left;
	hp_ = 1;
	bad = 1;
	powerUpNumberz = 0;

}

void Squid::hit()
{
	hp_ --;
}

void Squid::move()
{
	if(left_ == 1)
	{
		moveBy(-1,1);
		x--;
	}else{
		moveBy(1,1);
		x++;
	}
	
	y++;
}

void PlusBomb::move()
{
	moveBy(0,1);
	y = y + 1;
	
}

void Manta::move()
{
	moveBy(0,1);
	y = y + 1;
}

void Shark::move()
{
	if(goingLeft < 30)
	{
		moveBy(2,2);
		goingLeft ++;
	}
	
	if(goingLeft >= 30)
	{
		moveBy(-2,2);
		goingLeft ++;
	}
	
	if (goingLeft == 60)
	{
		goingLeft = 0;
	}
}

void Player::moveUp()
{
	//cout << "Up" << endl;
	if(y > -WINDOW_MAX_Y)
	{
		moveBy(0,-10);
		y = y - 10;
	}
}
void Player::moveDown()
{
	//cout << "Down" << endl;
	if(y < WINDOW_MAX_Y-65)
	{
		moveBy(0,10);
		y = y + 10;
	}
}

void Player::moveLeft()
{
	//cout << "Left" << endl;
	if(x > -WINDOW_MAX_X)
	{
		moveBy(-10,0);
		x = x - 10;
	}
}

void Player::moveRight()
{
	//cout << "Right" << endl;
	if(x < WINDOW_MAX_X - 100)
	{
		moveBy(10,0);
		x = x + 10;
	}

}

void Player::move()
{
	
}

int Thing::getHP()
{
	return hp_;
}


int Player::getX()
{
	return x;
}

int Player::getY()
{
	return y;
}

Lazer::Lazer (QPixmap *pm, int nx, int ny): Thing(pm,nx,ny)
{
	setPixmap(*pm);
	bad = 0;
	hp_ = 1;
	powerUpNumberz = 0;
}

Manta::Manta (QPixmap *pm, int nx, int ny): Thing(pm,nx,ny)
{
	setPixmap(*pm);
	bad = 1;
	hp_ = 10;
	powerUpNumberz = 0;

}

Shark::Shark (QPixmap *pm, int nx, int ny): Thing(pm,nx,ny)
{
	setPixmap(*pm);
	bad = 1;
	hp_ = 5;
	goingLeft = 0;
	powerUpNumberz = 0;

}

int Thing::powerUpNumber()
{
	return powerUpNumberz;
}

PlusBomb::PlusBomb (QPixmap *pm, int nx, int ny): Thing(pm,nx,ny)
{
	setPixmap(*pm);
	bad = 0;
	powerUpNumberz = 1;
	hp_ = 10000;
	
}

PlusPoints::PlusPoints(QPixmap *pm, int nx, int ny): Thing(pm,nx,ny)
{
	setPixmap(*pm);
	bad = 0;
	powerUpNumberz = 2;
	hp_ = 10000;
}

Shield::Shield(QPixmap *pm, int nx, int ny): Thing(pm,nx,ny)
{
	setPixmap(*pm);
	bad = 0;
	powerUpNumberz = 3;
	hp_ = 10000;
}

void Shield::move()
{
	moveBy(0,5);
	y = y + 5;
}

BetterGun::BetterGun(QPixmap *pm, int nx, int ny): Thing(pm,nx,ny)
{
	setPixmap(*pm);
	bad = 0;
	powerUpNumberz = 4;
	hp_ = 10000;
}

void BetterGun::move()
{
	moveBy(0,5);
	y = y + 5;
}


void PlusPoints::move()
{
	moveBy(0,5);
	y = y + 5;
}

void Lazer::move()
{
	moveBy(0,-5);
	y = y - 5;
}
