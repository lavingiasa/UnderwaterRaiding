#include "mainwindow.h"

using namespace std;

void MainWindow::handleTimer() 
{
	numHandles ++;
	

}

/** Constructor. It makes and links all of the pointers that were jsut declared before.
 * It also positions everything in the correct place and connects and stuff
 * 
 */
MainWindow::MainWindow()  {
    std::srand(0);
    numHandles = 0;
    startingScene = new QGraphicsScene();
    gameScene =new QGraphicsScene();
    view = new QGraphicsView( startingScene );
    startButton = new QPushButton("Start Game");
    stopButton = new QPushButton("Quit");
    name = new QTextEdit("");  
    timer = new QTimer();

	startButton->resize(200,30);
	startButton->move(0,0);
	
	stopButton->resize(200,30);
	stopButton->move(200,0);
	
	name->resize(200,30);
	name->move(100,90);
	
    startingScene->addWidget( startButton );
    startingScene->addWidget( stopButton );
    startingScene->addWidget( name );


    
    view->setFixedSize( WINDOW_MAX_X*2, WINDOW_MAX_Y*2 );
    view->setWindowTitle( "Graphical Tile Slide Puzzle");

    connect(startButton,SIGNAL(clicked()), this, SLOT(startGame()));
    connect(stopButton,SIGNAL(clicked()), this, SLOT(exitGame()));
	connect(timer, SIGNAL(timeout()), this, SLOT(handleTimer()));
}

/** This is how we get our view displayed
 * 
 */
void MainWindow::show() {
    view->show();
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
	delete gameScene;
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
	
}
