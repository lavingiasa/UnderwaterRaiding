#include "things.h"

using namespace std;

/**
Constructor for the thing class
	@param Pixmap pointer that will be used on the item to show the image. Nx is the x position. Ny is the y position
*/
Thing::Thing( QPixmap* p, int nx, int ny ) 
{
	pixMap = p;
	x = nx;
	y = ny;
	setPos( x, y );
}
/**
get the y position of the thing
	@return the y position of the current thing
*/
int Thing::getY()
{
	return y;
}
/**
get the x position of the thing
	@return the x position of the current thing
*/
int Thing::getX()
{
	return x;
}

/**
Constructor for the player class
	@param Pixmap pointer that will be used on the item to show the image. Nx is the x position. Ny is the y position
	@post: give the player 3hp
*/
Player::Player(QPixmap *pm, int nx, int ny): Thing(pm, nx, ny)
{
	setPixmap(*pm);
	hp_= 3;
}

/**
 * removes one hp whenever the item is hit
 */
void Thing::isHit()
{
	hp_--;
}

/**
 * @return bool that tells the caller if the item is for or against the player
 */
bool Thing::isBad()
{
	if(bad == 1)
	{
		return true;
	}else{
		return false;
	}
}

/**
Constructor for the player class
	@param Pixmap pointer that will be used on the item to show the image. Nx is the x position. Ny is the y position. Left tells the squid what side of the screen is should spawn
	@post: give the squid 1hp, it is bad, not a power up
*/
Squid::Squid(QPixmap *pm, int nx, int ny, int left): Thing (pm, nx, ny)
{
	setPixmap(*pm);
	left_ = left;
	hp_ = 1;
	bad = 1;
	powerUpNumberz = 0;

}

/**
 * removes one HP off the squid
 */
void Squid::hit()
{
	hp_ --;
}

/**
 * moves the squid based on the side it is on
 * */
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

/**
 * just moves the bomb directly down by two pixels per call
 * */
void PlusBomb::move()
{
	moveBy(0,2);
	y = y + 2;
	
}

/**
 * just moves the manta directly down by one pixel per call
 * */
void Manta::move()
{
	moveBy(0,1);
	y = y + 1;
}

/**
 * just moves the shark in a zig zag movement
 * */
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

/**
 * moves the player up by ten pixels if it is in the bounds
 * */
void Player::moveUp()
{
	if(y > -WINDOW_MAX_Y)
	{
		moveBy(0,-10);
		y = y - 10;
	}
}

/**
 * moves the player down by ten pixels if it is in the bounds
 * */
void Player::moveDown()
{
	if(y < WINDOW_MAX_Y-65)
	{
		moveBy(0,10);
		y = y + 10;
	}
}

/**
 * moves the player left by ten pixels if it is in the bounds
 * */
void Player::moveLeft()
{
	if(x > -WINDOW_MAX_X)
	{
		moveBy(-10,0);
		x = x - 10;
	}
}

/**
 * moves the player right by ten pixels if it is in the bounds
 * */
void Player::moveRight()
{
	if(x < WINDOW_MAX_X - 100)
	{
		moveBy(10,0);
		x = x + 10;
	}

}

/**
 * does nothing. I just had to satisfy the pure virtual function
 * */
void Player::move()
{
	
}

/**
 * @return teh current HP of the thing
 * */
int Thing::getHP()
{
	return hp_;
}

/**
 * @return teh x position of the current item
 * */
int Player::getX()
{
	return x;
}
/**
 * @return teh Y position of the current item
 * */
int Player::getY()
{
	return y;
}

/**
 * Constructor to make a bullet
 * @post it is not bad, hp = 1, not a power up
 * */
Lazer::Lazer (QPixmap *pm, int nx, int ny): Thing(pm,nx,ny)
{
	setPixmap(*pm);
	bad = 0;
	hp_ = 1;
	powerUpNumberz = 0;
}

/**
 * Constructor to make a manta
 * @post it is  bad, hp = 10, not a power up
 * */
Manta::Manta (QPixmap *pm, int nx, int ny): Thing(pm,nx,ny)
{
	setPixmap(*pm);
	bad = 1;
	hp_ = 10;
	powerUpNumberz = 0;

}

/**
 * Constructor to make a manta
 * @post it is  bad, hp = 5, not a power up, not going left
 * */
Shark::Shark (QPixmap *pm, int nx, int ny): Thing(pm,nx,ny)
{
	setPixmap(*pm);
	bad = 1;
	hp_ = 5;
	goingLeft = 0;
	powerUpNumberz = 0;

}



 

/**
 * @return the number of the power up
 * */
int Thing::powerUpNumber()
{
	return powerUpNumberz;
}

/**
 * Constructor to make a plusbomb
 * @post it is not bad, a power up, infinite HP
 * */
PlusBomb::PlusBomb (QPixmap *pm, int nx, int ny): Thing(pm,nx,ny)
{
	setPixmap(*pm);
	bad = 0;
	powerUpNumberz = 1;
	hp_ = 10000;
	
}

/**
 * Constructor to make a pluspints
 * @post it is  not bad, hp = 10000,  a power up
 * */
PlusPoints::PlusPoints(QPixmap *pm, int nx, int ny): Thing(pm,nx,ny)
{
	setPixmap(*pm);
	bad = 0;
	powerUpNumberz = 2;
	hp_ = 10000;
}

/**
 * Constructor to make a shield
 * @post it is not bad, hp = 10000,  a power up
 * */
Shield::Shield(QPixmap *pm, int nx, int ny): Thing(pm,nx,ny)
{
	setPixmap(*pm);
	bad = 0;
	powerUpNumberz = 3;
	hp_ = 10000;
}

/**
 * Moves the shield down by 5 pixels
 * */
void Shield::move()
{
	moveBy(0,5);
	y = y + 5;
}

/**
 * Constructor to make a better gun power up
 * @post not bad, power up, hp = 10000
 * */
BetterGun::BetterGun(QPixmap *pm, int nx, int ny): Thing(pm,nx,ny)
{
	setPixmap(*pm);
	bad = 0;
	powerUpNumberz = 4;
	hp_ = 10000;
}

/**
 * move the better gun power up by 5 pixels
 * */
void BetterGun::move()
{
	moveBy(0,5);
	y = y + 5;
}

/**
 * move the plus points power up by pixels
 * */
void PlusPoints::move()
{
	moveBy(0,5);
	y = y + 5;
}

/**
 * move the lazer by 5 pixels
 * */
void Lazer::move()
{
	moveBy(0,-5);
	y = y - 5;
}
