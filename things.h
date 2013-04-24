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
	protected:
		int x;
		int y;
		int vX;
		int vY;
		QPixmap *pixMap;
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
	 
};

class Squid: public Thing 
{
	public:
		Squid (QPixmap *pm, int nx, int ny, int left);
		void move(); 
	private:
		int left_;
	
};

class Manta: public Thing 
{
	public:
		Manta (QPixmap *pm, int nx, int ny);
		void move(); 
};

class Shark: public Thing 
{
	public:
		//Shark (QPixmap *pm, int nx, int ny);
		void move(); 
};


#endif
