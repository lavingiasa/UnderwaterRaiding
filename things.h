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

class Thing: public QGraphicsPixmapItem 
{	
	public:
		Thing(QPixmap *pm, int nx, int ny);
		void virtual move() = 0;
		bool isBad();
		void isHit();
		int getHP();
		int getY();
		int getX();	
		int powerUpNumber();

	protected:
		int x;
		int y;
		int vX;
		int vY;
		int hp_;
		int bad;
		QPixmap *pixMap;
		int powerUpNumberz;
};

class Player: public Thing 
{
	public:
		Player (QPixmap *pm, int nx, int ny);
		void moveUp(); 
		void moveLeft(); 
		void moveDown(); 
		void moveRight();
		void move();
		int getX();
		int getY();
	private:
	 
};

class PlusBomb: public Thing 
{
	public:
		PlusBomb (QPixmap *pm, int nx, int ny);
		void move();
		
	private:
	 
};

class PlusPoints: public Thing 
{
	public:
		PlusPoints (QPixmap *pm, int nx, int ny);
		void move();
		
	private:
	 
};

class Squid: public Thing 
{
	public:
		Squid (QPixmap *pm, int nx, int ny, int left);
		void move(); 
		void hit();
	private:
		int left_;
	
};

class Lazer: public Thing
{
	public:
		Lazer (QPixmap *pm, int nx, int ny);
		void move();
};

class Manta: public Thing 
{
	public:
		Manta (QPixmap *pm, int nx, int ny);
		void move(); 
	private:
		int goingLeft;
};

class Shark: public Thing 
{
	public:
		Shark (QPixmap *pm, int nx, int ny);
		void move(); 
	private:
		int goingLeft;
};


#endif
