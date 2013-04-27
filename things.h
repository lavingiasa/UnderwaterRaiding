#ifndef THINGS_H
#define THINGS_H

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QRectF>

#define WINDOW_MAX_X 250
#define WINDOW_MAX_Y 280

/**
 *A abstract "thing" class, which the rest of the things will inherit and impliment
 * 
 * @author Samir Lavingia
 * 
 */
class Thing: public QGraphicsPixmapItem 
{	
	public:
		/**Constuctor*/
		Thing(QPixmap *pm, int nx, int ny);
		/**Pure virtual function for the move. Will be implimented by the subclasses*/
		void virtual move() = 0;
		/**Bool to tell if the item is evil or not*/
		bool isBad();
		/**If it is hit, do what the function says*/
		void isHit();
		/**return the current HP of the item*/
		int getHP();
		/**get the Y position of the item*/
		int getY();
		/**get the X position of the item*/
		int getX();	
		/**get the power up number of the item. If it is not a power up, the number is zero*/
		int powerUpNumber();
		/**get which monster it is */

	protected:
		/**x position*/
		int x;
		/**y position*/
		int y;
		/**health points of the item*/
		int hp_;
		/**int for it is bad or not*/
		int bad;
		/**holds the pointer to the type of image it should be*/
		QPixmap *pixMap;
		/**int of the power up*/
		int powerUpNumberz;
		/** int of which monster */
		
};

/**
 *A player class, which the player will control and use to win/lose the game
 * 
 * @author Samir Lavingia
 * 
 */
class Player: public Thing 
{
	public:
		/** constructor */
		Player (QPixmap *pm, int nx, int ny);
		/** makes the player move up by a certain number of pixels */
		void moveUp(); 
		/** makes the player move left by a certain number of pixels */
		void moveLeft(); 
		/** makes the player move down by a certain number of pixels */
		void moveDown(); 
		/** makes the player move right by a certain number of pixels */
		void moveRight();
		/** does not actually do anything. Just there because it has to be as it is a pure virtual in the parent */
		void move();
		/** get the x position */
		int getX();
		/** get the y position */
		int getY();
	private:
	 
};

/**
 *A power up which gives the player another bomb to use
 * 
 * @author Samir Lavingia
 * 
 */
class PlusBomb: public Thing 
{
	public:
		/** constructor */
		PlusBomb (QPixmap *pm, int nx, int ny);
		/**move function*/
		void move();
		
	private:
	 
};

/**
 *A power up which gives the player another gun to use
 * 
 * @author Samir Lavingia
 * 
 */
class BetterGun: public Thing 
{
	public:
		/** constructor*/
		BetterGun (QPixmap *pm, int nx, int ny);
		/**move function*/
		void move();
		
	private:
	 
};

/**
 *A power up which gives the player another 1000 points
 * 
 * @author Samir Lavingia
 * 
 */
class PlusPoints: public Thing 
{
	public:
		/**constructor*/
		PlusPoints (QPixmap *pm, int nx, int ny);
		/**move function*/
		void move();
		
	private:
	 
};

/**
 *A power up which gives the player a shield for a bit 
 * 
 * @author Samir Lavingia
 * 
 */
class Shield: public Thing 
{
	public:
		/** constructor*/
		Shield (QPixmap *pm, int nx, int ny);
		/** move function*/
		void move();
		
	private:
	 
};

/**
 *An enemy which is fast with low HP
 * 
 * @author Samir Lavingia
 * 
 */
class Squid: public Thing 
{
	public:
		/** constructor */
		Squid (QPixmap *pm, int nx, int ny, int left);
		/**move function*/
		void move(); 
		/**what to do when it is hit*/
		void hit();
	private:
		/**helps the item know which side to come from*/
		int left_;
	
};

/**
 *A class for the bullet that the player shoots
 * 
 * @author Samir Lavingia
 * 
 */
class Lazer: public Thing
{
	public:
		/**constructor for the bullet */
		Lazer (QPixmap *pm, int nx, int ny);
		/**move function for the bullet*/
		void move();
};

/**
 *An enemy which is slow with high HP
 * 
 * @author Samir Lavingia
 * 
 */
class Manta: public Thing 
{
	public:
		/** constructor for the manta*/
		Manta (QPixmap *pm, int nx, int ny);
		/**move function for the manta*/
		void move(); 
	private:
		/** going left is to help the manta move */
		int goingLeft;
};

/**
 *An enemy which is medium speed with medium HP. Moves in a zigzag
 * 
 * @author Samir Lavingia
 * 
 */
class Shark: public Thing 
{
	public:
		/** constructor */
		Shark (QPixmap *pm, int nx, int ny);
		/** move function */
		void move(); 
	private:
		/** going left is to help the shark move in a zig zag motion */
		int goingLeft;
};




#endif
