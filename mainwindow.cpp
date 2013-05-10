	#include "mainwindow.h"

using namespace std;


/** handles the timer and stuff to make sure the game works as intended. It is the drum beat of the game */
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
	
	//if it has been 100 cycles since my last hit, let it hit me again
	if(justHitCount == 100)
	{
		justHit = 0;
		player -> setPixmap(*playerShield);

	}
	
	//if it has been 100 cycles since my last hit, give me the bad gun again
	if(gunTimer == 100)
	{
		intGunToUse = 0;
	}
	
	//if it has been 100 cycles since my last hit, get rid of my shield
	if(ShieldHitCount == 100)
	{
		justHit = 0;
		player -> setPixmap(*playerImage);

	}
	//next 4 if statements are for the bomb animation once it is used

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
	
	//make it so it sets the right image for the player, based on shields
	if(justHit == 1)
	{
		player -> setPixmap(*playerShield);
	}else{
		player -> setPixmap(*playerImage);
	}

	//keep the background connected
	if(background -> y() == WINDOW_MAX_Y)
	{
		background -> setPos(-WINDOW_MAX_X-5,-3*WINDOW_MAX_Y);
	}
	
	//keep the background connected
	if(background2 -> y() == WINDOW_MAX_Y)
	{
		background2 -> setPos(-WINDOW_MAX_X-5,-3*WINDOW_MAX_Y);
	}
	//change the score
	score -> setText(str.c_str());
	
	//timer for shooting
	if(justShot > 0)
	{
		justShot --;
	}
	//make a shark
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
	
	//make a manta ray
	if(numHandles % (spawnNumber/2) == 1)
	{
		Manta * currManta = new Manta(mantaImage,0,-300);
		myThings.push_back(currManta);
		startingScene -> addItem(currManta);
		currManta = new Manta(mantaImage,-100, -300);
		myThings.push_back(currManta);
		startingScene -> addItem(currManta);
		
	}
		
	//make a squid
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
	//move everything. If a certain amount of time has passed, move everything again
	for(unsigned int i = 0; i < myThings.size(); i ++)
		{
			myThings[i]->move();
			if(spawnNumber < 400)
			{
				myThings[i]->move();
			}
		}
	//checks the collisions
	for(unsigned int i = 0; i < myThings.size(); i ++)
		{
			//with the player
			if(!(myThings[i]->isBad()) && player->collidesWithItem(myThings[i]))
			{
				//if it is a bomb
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
				//if it is for more points
				if (myThings[i] -> powerUpNumber() == 2)
					{
						scoreNumber += 1000;
						delete myThings[i];
						vector <Thing*>::iterator Itone;
						Itone = myThings.begin() + i;
						myThings.erase(Itone);
						
					}
				//if it is the shield
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
				//if it is the better gun
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
			//compares if the item collides with a bad thing
			if(myThings[i]->isBad() && player->collidesWithItem(myThings[i]) && justHit == 0)
			{
				//gets hit
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
				
				//if it is dead, end the game
				if(player->getHP() == -1)
				{
					for (unsigned int h = 0; h < myThings.size(); h++)
					{
						myThings[h] -> hide();
					}
					
					timer -> stop();

					
					player -> hide();
					namePrompt -> show();
					writeScores();

					namePrompt -> setText("You lose");
					instructions -> show();
					gameInProgress = 0;

				}
				justHit = 1;
				justHitCount = 0;
			}
			
			//more collisions
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
			
			//if items hit an edge lose a life 
			if(myThings[i] -> getHP() == 0 || myThings[i] -> getY() > WINDOW_MAX_Y || myThings[i] -> getY() < -WINDOW_MAX_Y - 30 || myThings[i] -> getX() > WINDOW_MAX_X || myThings[i] -> getX() < -WINDOW_MAX_X)
			{
				if(myThings[i] -> getY() > WINDOW_MAX_Y || myThings[i] -> getY() < -WINDOW_MAX_Y - 30 || myThings[i] -> getX() > WINDOW_MAX_X || myThings[i] -> getX() < -WINDOW_MAX_X)
				{
					hitEdge = 1;
				}
				
				//when a thing dies, there is a chance it will drop an item
				if(myThings[i] -> isBad())
				{
					//drop a bomb chance
					if(rand()%200 == 1)
					{
						PlusBomb * currBomb = new PlusBomb(bombImage, myThings[i] -> getX(), myThings[i] -> getY());
						myThings.push_back(currBomb);
						startingScene -> addItem(currBomb);
					}
					
					//drop an medal for extra point
					if(rand()%10 == 2)
					{
						PlusPoints * currPoints = new PlusPoints(pointsImage, myThings[i] -> getX(), myThings[i] -> getY());
						myThings.push_back(currPoints);
						startingScene -> addItem(currPoints);
					}
					
					//drop a shield
					if(rand()%100 == 3)
					{
						Shield * currShield = new Shield(shieldImage, myThings[i] -> getX(), myThings[i] -> getY());
						myThings.push_back(currShield);
						startingScene -> addItem(currShield);
					}
					
					//drop a better gun
					if(rand()%25 == 4)
					{
						BetterGun * currGun = new BetterGun(gunImage, myThings[i] -> getX(), myThings[i] -> getY());
						myThings.push_back(currGun);
						startingScene -> addItem(currGun);
					}
				}
				
				//if it hits an edge remove a life
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
				
				//end game if no lives
				if(player->getHP() == -1)
				{
					for (unsigned int h = 0; h < myThings.size(); h++)
					{
						myThings[h] -> hide();
					}
					timer -> stop();

					player -> hide();
					namePrompt -> show();
					writeScores();
					namePrompt -> setText("You lose");
					instructions -> show();
					gameInProgress = 0;
				}
			}
		}
}

/** this handles all of the key presses as they should be handled*/
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event)
    {
	}
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
			//checking if I just shot because I have to reload things
			if(justShot == 0 && gameInProgress == 1)
			{
				Lazer * lazer;
				//checks what gun it is supposed to use and uses it
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
			//pause if the game is active and change the button
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
			//if I have a bomb and the game is in progress, use it
			if (gameInProgress == 1 && numBombs > 0)
			{
				bombTimer = 0;

				
				for(unsigned int i = 0; i < myThings.size(); i++)
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
/** loads the scores from the file */
void MainWindow::loadScores()
{
	ifstream ifile ("leaderBoard.txt");
	string line;
	int worked = 0;
	scores.clear();
	
	while(ifile.good())
	{
		getline (ifile,line);
		if(line == "")
		{
			continue;
		}
		scores.push_back(line);

		worked = 1;
	}
	
	//scores.erase(scores.end());
	
	if(worked == 1)
	{
		ifile.close();
	}
	
	if(!ifile.good())
	{
		ofstream outputFile("leaderBoard.txt");		
	}
}
/** Writes the scores to a file */
void MainWindow::writeScores()
{
	remove ("leaderBoard.txt");
	ofstream outputFile("leaderBoard.txt");
	stringstream ss1;
	stringstream ss;
	string newScore;
	string name = namePrompt -> text().toStdString();
	ss1 << name;
	ss1 << " ";
	ss1 << scoreNumber;
	newScore = ss1.str();
	string name2;
	int score;
	
	if(scores.size() < 1)
	{
		outputFile << newScore;
	}
	
	int newor = 0;	
	for (unsigned int i = 0 ; i < scores.size(); i++)
	{
		ss << scores[i];
		ss >> name2;
		ss >> score;
		ss.clear();
		if(score < scoreNumber)
		{
			scores.insert(scores.begin()+i, newScore);
			newor = 1;
			break;
		}
	}
	
	if (newor == 0)
	{
		scores.insert(scores.begin()+scores.size(), newScore);
	}
	
	stringstream ss3;

	for (unsigned int i = 0 ; i < scores.size(); i++)
	{
		outputFile << scores[i] << endl;
		ss3 << scores[i] << "\n";

	}
	string allScores = ss3.str();
	QString qstr = QString::fromStdString(allScores);
	instructions -> setText(qstr);
	
	
	outputFile.close();
	

}

/** Constructor. It makes and links all of the pointers that were just declared before in the .h.
 * It also positions everything in the correct place and connects and stuff
 * 
 */
MainWindow::MainWindow()  {	
	this -> setWindowTitle("Underwater Raiding");
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
    
    loadScores();
    
    
    
    
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

/** Pause the game by stopping the timer if the game is in progress. If it is not, resume the game
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
/** This is the slot for starting the game. It hides stuff and shows other stuffs and starts the timer and stuff
 * 
 * @return bool that says if starting the games were effective
 * */

bool MainWindow::startGame()
{
	QString str= name->toPlainText();

	
	if(str.trimmed().isEmpty())
	{
		instructions -> setText("Please enter a name at the bottom of the window");
		return false;
		
	}
	setFocus();
	startButton -> hide();
	name -> hide();
	instructions -> hide();
	
	
	namePrompt -> setText(str);
	startingScene -> addItem(player);
	timer -> start();
	pauseButton -> show();
	gameInProgress = 1;
	
	
	

	return 0;
}
