#include "mainwindow.h"

using namespace std;

void MainWindow::handleTimer() 
{
	numHandles ++;
	if (numHandles == 10000)
	{
		srand(0);
		Squid * currSquid = new Squid(squidImage, rand()%200, 0);
		myThings.push_back(currSquid);
		startingScene->addItem(currSquid);
		numHandles = 0;
	}
	if (numHandles == 1000)
	{
		for(unsigned int i = 0; i < myThings.size(); i ++)
		{
			myThings[i]->move();
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
	namePrompt = new QLabel("Name:");
	mainLayout = new QVBoxLayout;
    
    std::srand(0);
    numHandles = 0;
    startingScene = new QGraphicsScene();
    view = new QGraphicsView( startingScene );
    mainLayout->addWidget(view);

    startButton = new QPushButton("Start Game");
    stopButton = new QPushButton("Quit");
    name = new QTextEdit("");  
    timer = new QTimer();
    intro = new QLabel("Welcome to my game!");
    namePrompt = new QLabel("Name:");
    
    sharkImage = new QPixmap("Images/shark.png");
    playerImage = new QPixmap("Images/carry.png");
    squidImage = new QPixmap("Images/squid.PNG");
    mantaImage = new QPixmap("Images/manta.png");
	
	player = new Player(playerImage, 0, 0);

	
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
