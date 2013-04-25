#include "mainwindow.h"

using namespace std;

void MainWindow::handleTimer() 
{
	numHandles ++;
	scoreNumber ++;
	
	stringstream ss; 
	ss << scoreNumber;
	string str = ss.str();

	score -> setText(str.c_str());
	if(justShot > 0)
	{
		justShot --;
	}

	if(numHandles == spawnNumber)
	{
		Shark * currShark = new Shark(sharkImage, 0,-300);
		numHandles = 0;
		myThings.push_back(currShark);
		startingScene->addItem(currShark);
		if(spawnNumber >= 50)
		{
			spawnNumber = spawnNumber - 50;
		}

	}
	
	if(numHandles % (spawnNumber/2) == 1)
	{
		Manta * currManta = new Manta(mantaImage,0,-300);
		myThings.push_back(currManta);
		startingScene -> addItem(currManta);
		currManta = new Manta(mantaImage,-100, -300);
		myThings.push_back(currManta);
		startingScene -> addItem(currManta);
		
	}
		
	if (numHandles % (spawnNumber/20) == 1)
	{
		Squid * currSquid;

		justHit = 0;
		if(left == 1)
		{
			currSquid = new Squid(squidImage, 200, -300, left);
			left = 0;

		}else{
			currSquid = new Squid(squidImage, -250, -300, left);
			left = 1;

		}
		myThings.push_back(currSquid);
		startingScene->addItem(currSquid);

	}
	
	for(unsigned int i = 0; i < myThings.size(); i ++)
		{
			myThings[i]->move();
		}
	
	for(unsigned int i = 0; i < myThings.size(); i ++)
		{
			if(!(myThings[i]->isBad()) && player->collidesWithItem(myThings[i]))
			{
				if (myThings[i] -> powerUpNumber() == 1)
				{
					if(numBombs < 3)
					{
						numBombs ++;
						
						delete myThings[i];
						vector <Thing*>::iterator Itone;
						Itone = myThings.begin() + i;
						myThings.erase(Itone);
							
						
						if (numBombs == 3)
						{
							bombThree -> show();
						}else if(numBombs == 2)
						{
							bombTwo -> show();
						}else if (numBombs == 1)
						{
							bombOne -> show();
						}
					}
				}
				if (myThings[i] -> powerUpNumber() == 2)
					{
						scoreNumber += 1000;
						delete myThings[i];
						vector <Thing*>::iterator Itone;
						Itone = myThings.begin() + i;
						myThings.erase(Itone);
						
					}
				if (myThings[i] -> powerUpNumber() == 3)
					{
						justHit = 1;
						delete myThings[i];
						vector <Thing*>::iterator Itone;
						Itone = myThings.begin() + i;
						myThings.erase(Itone);
						
					}
				if (myThings[i] -> powerUpNumber() == 4)
					{
						delete myThings[i];
						vector <Thing*>::iterator Itone;
						Itone = myThings.begin() + i;
						myThings.erase(Itone);
						
					}
			}
			
			if(myThings[i]->isBad() && player->collidesWithItem(myThings[i]) && justHit == 0)
			{
				player->isHit();
				if (player->getHP() == 2)
				{
					heartThree -> hide();
				}else if(player->getHP() == 1)
				{
					heartTwo -> hide();
				}else if (player->getHP() == 0)
				{
					heartOne -> hide();
				}
				
				if(player->getHP() == -1)
				{
					timer -> stop();
					for (unsigned int h = 0; h < myThings.size(); h++)
					{
						myThings[h] -> hide();
					}
					
					player -> hide();
					namePrompt -> show();
					namePrompt -> setText("You lose");

				}
				justHit = 1;
			}
			
			for (unsigned int j = 0; j < myThings.size(); j++)
			{
				if (i == j)
				{
					continue;
				}
				
				if (myThings[j] -> isBad() && myThings[i]->isBad() == false && myThings[i]->collidesWithItem(myThings[j]) && myThings[i] -> powerUpNumber() == 0 && myThings[j] -> powerUpNumber() == 0)
				{
					myThings[i] -> isHit();
					myThings[j] -> isHit();
				}
			}
			
			if(myThings[i] -> getHP() == 0 || myThings[i] -> getY() > WINDOW_MAX_Y || myThings[i] -> getY() < -WINDOW_MAX_Y - 30 || myThings[i] -> getX() > WINDOW_MAX_X || myThings[i] -> getX() < -WINDOW_MAX_X)
			{
				if(myThings[i] -> isBad())
				{
					if(rand()%10 == 1)
					{
						PlusBomb * currBomb = new PlusBomb(bombImage, myThings[i] -> getX(), myThings[i] -> getY());
						myThings.push_back(currBomb);
						startingScene -> addItem(currBomb);
					}
					
					if(rand()%10 == 2)
					{
						PlusPoints * currPoints = new PlusPoints(pointsImage, myThings[i] -> getX(), myThings[i] -> getY());
						myThings.push_back(currPoints);
						startingScene -> addItem(currPoints);
					}
					
					if(rand()%10 == 3)
					{
						Shield * currShield = new Shield(shieldImage, myThings[i] -> getX(), myThings[i] -> getY());
						myThings.push_back(currShield);
						startingScene -> addItem(currShield);
					}
					
					if(rand()%10 == 4)
					{
						BetterGun * currGun = new BetterGun(gunImage, myThings[i] -> getX(), myThings[i] -> getY());
						myThings.push_back(currGun);
						startingScene -> addItem(currGun);
						intGunToUse = 1;
					}
				}
				
				delete myThings[i];
				vector <Thing*>::iterator Itone;
				Itone = myThings.begin() + i;
				myThings.erase(Itone);
				
			}
			
			
		}
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event -> key())
    {
		case Qt::Key_Left:
			player -> moveLeft();
			break;
		case Qt::Key_Right:
			player -> moveRight();
			break;
		case Qt::Key_Down:
			player -> moveDown();
			break;
		case Qt::Key_Up:
			player -> moveUp();
			break;
		case Qt::Key_Space:
			
			if(justShot == 0)
			{
				cout << intGunToUse << endl;
				Lazer * lazer;
				
				if (intGunToUse == 1)
				{
					lazer = new Lazer(bulletImage, player->getX(), player->getY());
				}else{
					lazer = new Lazer(thickBulletImage, player->getX(), player->getY());
				}
				myThings.push_back(lazer);
				startingScene -> addItem(lazer);
				justShot = 6;
			}
			break;
		case Qt::Key_P:
			if (timer -> isActive())
			{
				timer -> stop();
			}else{
				timer -> start();
			}
			break;
		case Qt::Key_B:
			if (numBombs > 0)
			{
				for(int i = 0; i < myThings.size(); i++)
				{
					delete myThings[i];
				}
				myThings.clear();
				numBombs --;
				
				if (numBombs == 2)
				{
					bombThree -> hide();
				}else if(numBombs == 1)
				{
					bombTwo -> hide();
				}else if (numBombs == 0)
				{
					bombOne -> hide();
				}
			}
			
			break;
				
		
	}

}

void MainWindow::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	cout << "adsf" << endl;
}

/** Constructor. It makes and links all of the pointers that were jsut declared before.
 * It also positions everything in the correct place and connects and stuff
 * 
 */
MainWindow::MainWindow()  {	
	this -> setWindowTitle("Pew Pew");
	namePrompt = new QLabel("Name:");
	mainLayout = new QVBoxLayout;
	lives = new QHBoxLayout;
	spawnNumber = 500;
    left = 0;
    justShot = 5;
    justHit = 0;
    std::srand(time(0));
    numBombs = 3;
    numHandles = 0;
    scoreNumber = 0;
    intGunToUse = 0;
    startingScene = new QGraphicsScene();
    startingScene->setSceneRect(-WINDOW_MAX_X, -WINDOW_MAX_Y , 2*WINDOW_MAX_X -10 , 2*WINDOW_MAX_Y -10);
    startingScene->setBackgroundBrush(QBrush(Qt::blue));
    view = new QGraphicsView( startingScene );
    
    
    
    heartOne = new QLabel();
    heartTwo = new QLabel();
    heartThree = new QLabel();
    
	bombOne = new QLabel();
    bombTwo = new QLabel();
    bombThree = new QLabel();
    
	


    startButton = new QPushButton("Start Game");
    stopButton = new QPushButton("Quit");
    name = new QTextEdit("");  
    timer = new QTimer();
    
    timer -> setInterval(30);
    
    
    
    sharkImage = new QPixmap("Images/shark.png");
    playerImage = new QPixmap("Images/carry.png");
    squidImage = new QPixmap("Images/squid.PNG");
    mantaImage = new QPixmap("Images/manta.png");
    bulletImage = new QPixmap("Images/bullet.gif");
    heartImage = new QPixmap("Images/heart.png");
    bombImage = new QPixmap("Images/bomb.png");
    pointsImage = new QPixmap("Images/medal.gif");
    shieldImage = new QPixmap("Images/shield.png");
    gunImage = new QPixmap("Images/gun.png");
    thickBulletImage = new QPixmap("Images/laser.png");
    
    heartOne -> setPixmap(*heartImage);
    heartTwo -> setPixmap(*heartImage);
    heartThree -> setPixmap(*heartImage);
    
    bombOne -> setPixmap(*bombImage);
    bombTwo -> setPixmap(*bombImage);
    bombThree -> setPixmap(*bombImage);

	
	player = new Player(playerImage, 0, 0);
	score = new QLabel;
	score -> setText("0");
	
	lives->addWidget( heartOne);
    lives->addWidget( heartTwo);
    lives->addWidget( heartThree);
    lives->addWidget( score);

	lives->addWidget( bombOne);
    lives->addWidget( bombTwo);
    lives->addWidget( bombThree);
    
    mainLayout->addLayout(lives);

    mainLayout->addWidget(view);
    
    intro = new QLabel("Welcome to my game!");
    namePrompt = new QLabel("Name:");

	
	startButton->resize(200,30);
	startButton->move(0,0);
	
	stopButton->resize(200,30);
	stopButton->move(200,0);
	
	namePrompt->resize(200,30);
	namePrompt->move(100,60);
	
	name->resize(200,30);
	name->move(100,90);
	
	intro->resize(200,30);
	intro->move(200,200);
		
    mainLayout->addWidget( startButton );
    mainLayout->addWidget( stopButton );
    mainLayout->addWidget( namePrompt);
    mainLayout->addWidget( name );
    
	    
    view->setFixedSize( WINDOW_MAX_X*2, WINDOW_MAX_Y*2 );
    view->setWindowTitle("Raiden");

    connect(startButton,SIGNAL(clicked()), this, SLOT(startGame()));
    connect(stopButton,SIGNAL(clicked()), this, SLOT(exitGame()));	
	connect(timer, SIGNAL(timeout()), this, SLOT(handleTimer()));
	
	setFocus();
	setLayout(mainLayout);

}

/** This is how we get our view displayed
 * 
 */

/*void MainWindow::show() 
{
    view->show();
}*/

/** This is the destructor 
 * 
 */
MainWindow::~MainWindow()
{
    delete startButton;  
    delete stopButton; 
 
    delete timer;
    delete name;
    
	delete startingScene;
    delete view;
}

/** This is the slot for exiting the game*/
void MainWindow::exitGame()
{
	QApplication::exit(1);
}
/** This is the slot for starting the game. It has to check if the numbers in the text boxes were valid then delete the old game and make a new one
 * 
 * @return bool that says if starting the games were effective
 * */

bool MainWindow::startGame()
{
	setFocus();
	startButton -> hide();
	name -> hide();
	namePrompt -> hide();
	startingScene -> addItem(player);
	timer -> start();

	
	
	

	return 0;
}
