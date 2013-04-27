	#include "mainwindow.h"

using namespace std;

void MainWindow::handleTimer() 
{
	numHandles ++;
	scoreNumber ++;
	justHitCount ++;
	ShieldHitCount ++;
	bombTimer ++;
	gunTimer ++;
	
	stringstream ss; 
	ss << scoreNumber;
	string str = ss.str();

	background -> moveBy(0,1);
	background2 -> moveBy(0,1);
	
	if(justHitCount == 100)
	{
		justHit = 0;
		player -> setPixmap(*playerShield);

	}
	
	if(gunTimer == 100)
	{
		intGunToUse = 0;
	}
	
	if(ShieldHitCount == 100)
	{
		justHit = 0;
		player -> setPixmap(*playerImage);

	}
	
	if(bombTimer == 1)
	{
		startingScene -> setBackgroundBrush(Qt::white);
		background -> hide();
		background2 -> hide();
	}
	
	if(bombTimer == 5)
	{
		background -> show();
		background2 -> show();
	}
	
	if(bombTimer == 10)
	{
		startingScene -> setBackgroundBrush(Qt::cyan);
		background -> hide();
		background2 -> hide();
	}
	
	if(bombTimer == 15)
	{
		startingScene -> setBackgroundBrush(Qt::blue);
		background -> show();
		background2 -> show();
	}
	
	if(justHit == 1)
	{
		player -> setPixmap(*playerShield);
	}else{
		player -> setPixmap(*playerImage);
	}

	if(background -> y() == WINDOW_MAX_Y)
	{
		background -> setPos(-WINDOW_MAX_X-5,-3*WINDOW_MAX_Y);
	}
	
	if(background2 -> y() == WINDOW_MAX_Y)
	{
		background2 -> setPos(-WINDOW_MAX_X-5,-3*WINDOW_MAX_Y);
	}

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
		if(spawnNumber > 50)
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
			if(spawnNumber < 400)
			{
				myThings[i]->move();
			}
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
						ShieldHitCount = 0;

						player -> setPixmap(*playerShield);
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
						intGunToUse = 1;
						gunTimer = 0;
						
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
				justHitCount = 0;
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
				if(myThings[i] -> getY() > WINDOW_MAX_Y || myThings[i] -> getY() < -WINDOW_MAX_Y - 30 || myThings[i] -> getX() > WINDOW_MAX_X || myThings[i] -> getX() < -WINDOW_MAX_X)
				{
					hitEdge = 1;
				}
				
				if(myThings[i] -> isBad())
				{
					if(rand()%200 == 1)
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
					
					if(rand()%100 == 3)
					{
						Shield * currShield = new Shield(shieldImage, myThings[i] -> getX(), myThings[i] -> getY());
						myThings.push_back(currShield);
						startingScene -> addItem(currShield);
					}
					
					if(rand()%25 == 4)
					{
						BetterGun * currGun = new BetterGun(gunImage, myThings[i] -> getX(), myThings[i] -> getY());
						myThings.push_back(currGun);
						startingScene -> addItem(currGun);
					}
				}
				
				
				if(myThings[i] -> isBad() && hitEdge == 1)
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
				}
		
				delete myThings[i];
				vector <Thing*>::iterator Itone;
				Itone = myThings.begin() + i;
				myThings.erase(Itone);
				hitEdge = 0;
				
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
			}
		}
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event -> key())
    {
		case Qt::Key_A:
			player -> moveLeft();
			break;
		case Qt::Key_D:
			player -> moveRight();
			break;
		case Qt::Key_S:
			player -> moveDown();
			break;
		case Qt::Key_W:
			player -> moveUp();
			break;
		case Qt::Key_Space:
			
			if(justShot == 0)
			{
				Lazer * lazer;
				
				if (intGunToUse == 0)
				{
					lazer = new Lazer(bulletImage, player->getX() + 30, player->getY());
				}else if(intGunToUse == 1){
					lazer = new Lazer(thickBulletImage, player->getX() - 5, player->getY() - 50);
				}
				myThings.push_back(lazer);
				startingScene -> addItem(lazer);
				justShot = 6;
			}
			break;
		case Qt::Key_P:
			if(gameInProgress == 1)
			{
				if (timer -> isActive())
				{
					timer -> stop();
					pauseButton -> setText("Resume");
				}else{
					timer -> start();
					pauseButton -> setText("Pause");
				}
			}
			break;
		case Qt::Key_B:
			if (gameInProgress == 1 && numBombs > 0)
			{
				bombTimer = 0;

				
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
	hitEdge = 0;
	spawnNumber = 500;
	gameInProgress = 0;
	bombTimer = 200;
	ShieldHitCount = 200;
    left = 0;
    justShot = 5;
    justHit = 0;
    std::srand(time(0));
    numBombs = 3;
    numHandles = 0;
    scoreNumber = 0;
    intGunToUse = 0;
    gunTimer = 200;
    startingScene = new QGraphicsScene();
    instructions = new QLabel("Instructions: \nWASD to move\nB to use your bomb\nP to pause\nSpace to shoot\nAvoid getting hit by enemies and don't let them escape");
    instructions -> setAlignment( Qt::AlignCenter );
    instructions->setStyleSheet("QLabel { color : white; }");
    instructions -> move(-185, 0);
    instructions -> setAttribute(Qt::WA_TranslucentBackground);
    
    ocean2 = new QPixmap("Images/ocean2.png");
     
    background = new QGraphicsPixmapItem(QPixmap("Images/ocean1.png"));
	background -> setPos(-WINDOW_MAX_X-5,-WINDOW_MAX_Y-5);
	
	background2 = new QGraphicsPixmapItem(QPixmap("Images/ocean2.png"));
	background2 -> setPos(-WINDOW_MAX_X-5,-3*WINDOW_MAX_Y-5);
	
    startingScene -> addItem(background);
    startingScene -> addItem(background2);
    startingScene -> addWidget(instructions);

    startingScene->setSceneRect(-WINDOW_MAX_X, -WINDOW_MAX_Y , 2*WINDOW_MAX_X -10 , 2*WINDOW_MAX_Y -10);
    view = new QGraphicsView( startingScene );
    
    
    
    heartOne = new QLabel();
    heartTwo = new QLabel();
    heartThree = new QLabel();
    
	bombOne = new QLabel();
    bombTwo = new QLabel();
    bombThree = new QLabel();
    
    scorePrompt = new QLabel("Score: ");
    
	


    startButton = new QPushButton("Start Game");
    stopButton = new QPushButton("Quit");
    pauseButton = new QPushButton("Pause");
    
    name = new QTextEdit("");  
    timer = new QTimer();
    
    timer -> setInterval(30);
    
    
    
    sharkImage = new QPixmap("Images/shark.png");
    playerImage = new QPixmap("Images/carry.png");
    squidImage = new QPixmap("Images/squid.PNG");
    mantaImage = new QPixmap("Images/manta.png");
    bulletImage = new QPixmap("Images/bullet.png");
    heartImage = new QPixmap("Images/heart.png");
    bombImage = new QPixmap("Images/bomb.png");
    pointsImage = new QPixmap("Images/medal.gif");
    shieldImage = new QPixmap("Images/shieldIcon.png");
    gunImage = new QPixmap("Images/fire.png");
    thickBulletImage = new QPixmap("Images/laser.png");
    playerShield = new QPixmap("Images/playerShield.png");
    
    *sharkImage = sharkImage -> scaled(60,110);
    *playerImage = playerImage -> scaled (80, 80);
    *playerShield = playerShield -> scaled (80,80);
    *thickBulletImage = thickBulletImage -> scaled(100,100); 
    *bulletImage = bulletImage -> scaled(20,20);
    *gunImage = gunImage -> scaled(30,30);
    *shieldImage = shieldImage -> scaled (30,30);
    
    heartOne -> setPixmap(*heartImage);
    heartTwo -> setPixmap(*heartImage);
    heartThree -> setPixmap(*heartImage);
    
    bombOne -> setPixmap(*bombImage);
    bombTwo -> setPixmap(*bombImage);
    bombThree -> setPixmap(*bombImage);

	
	player = new Player(playerImage, -40, 200);

	score = new QLabel;
	score -> setText("0");
	
	lives->addWidget( heartOne);
    lives->addWidget( heartTwo);
    lives->addWidget( heartThree);
    
    lives->addStretch();

	lives->addWidget( bombOne);
    lives->addWidget( bombTwo);
    lives->addWidget( bombThree);
    
    lives->addStretch();

    lives->addWidget( scorePrompt);
    lives->addWidget( score);
    
    
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
	name -> setFixedHeight(30);
	name->move(100,90);
	
	intro->resize(200,30);
	intro->move(200,200);
		
    mainLayout->addWidget( startButton);
    mainLayout->addWidget( stopButton );
    mainLayout->addWidget( pauseButton);
    mainLayout->addWidget( namePrompt );
    mainLayout->addWidget( name );
    
	    
    view->setFixedSize( WINDOW_MAX_X*2, WINDOW_MAX_Y*2 );
    view->setWindowTitle("Raiden");

    connect(startButton,SIGNAL(clicked()), this, SLOT(startGame()));
    connect(stopButton,SIGNAL(clicked()), this, SLOT(exitGame()));	
	connect(timer, SIGNAL(timeout()), this, SLOT(handleTimer()));
	connect(pauseButton, SIGNAL(clicked()), this, SLOT(pauseGame()));
	
	setFocus();
	setLayout(mainLayout);
	pauseButton -> hide();

}

/** This is how we get our view displayed
 * 
 */

void MainWindow::pauseGame() 
{
	if(timer -> isActive())
	{
		timer -> stop();
		pauseButton -> setText("Resume");
	}else{
		timer -> start();
		pauseButton -> setText("Pause");
	}
	
}

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
	instructions -> hide();
	namePrompt -> setText(name -> toPlainText());
	startingScene -> addItem(player);
	timer -> start();
	pauseButton -> show();
	gameInProgress = 1;
	
	
	

	return 0;
}
