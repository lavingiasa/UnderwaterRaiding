#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <cmath>
#include <QPushButton>
#include <iostream>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QString>
#include <QByteArray>
#include <QTimeLine>
#include <QTextEdit>
#include <QGraphicsItemAnimation>
#include <QPushButton>
#include <vector>
#include <QRadioButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QListView>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QKeyEvent>
#include <QPixmap>
#include <ctime>
#include <iostream>
#include <QHBoxLayout>
#include <cstdlib>
#include <sstream>
#include <QSpacerItem>


#include "things.h"


#define WINDOW_MAX_X 250
#define WINDOW_MAX_Y 280

using namespace std;

/**
 * This class is the backbone for the entire game/project. It holds all the GUI stuff, impliments the things, and makes everything work together
 * 
 * @author Samir Lavingia
 * 
 */
class MainWindow : public QWidget {
    Q_OBJECT
    
public:
	/**Constructor */
    explicit MainWindow();
	/**Destructor */
    ~MainWindow();

    
private:
    /** the scene where all the gameplay takes place*/
    QGraphicsScene *startingScene;
    /** the view in which teh scene is placed*/
    QGraphicsView *view;
    
    /** the button to start the game*/
    QPushButton *startButton;
    /** the stop button to quit the game*/
    QPushButton *stopButton;
    /** the pause button to pause the game*/
    QPushButton *pauseButton;
    
    /** the box for the player to put his name*/
    QTextEdit *name;
    /** the label that says hi*/
    QLabel *intro;
    /** the item that says name:*/
    QLabel *namePrompt;
    /** the label that tells the player about the game*/
    QLabel *instructions;
    
    /** the label for the first heart*/
    QLabel *heartOne;
    /** The label for the second heart */
    QLabel *heartTwo;
    /** the label for the third heart*/
    QLabel *heartThree;
    
    
    /** the label for the first bomb */
    QLabel *bombOne;
    /** the label for the second bomb*/
    QLabel *bombTwo;
    /** the label for the third bomb*/
    QLabel *bombThree;
    
    /** the label that contains the score and counts up*/
    QLabel *score;
    /** the item that just says what the number is*/
    QLabel *scorePrompt;
    
    /**holds teh current score */
    int scoreNumber;
    /**holds the number of bombs */
    int numBombs;
    /**holds the bomb timer for the animation */
    int bombTimer;
    /**holds gunTimer to say how long to use the new gun */
    int gunTimer;
    
    /** image for the shark*/
    QPixmap* sharkImage;
    /** image for the player*/
    QPixmap* playerImage;
    /** image for the squid*/
    QPixmap* squidImage;
    /** image for the manta*/
    QPixmap* mantaImage;
    /** image for the bullet*/
    QPixmap* bulletImage;
    /** image for the heart*/
    QPixmap* heartImage;
    /** image for the bomb*/
    QPixmap* bombImage;
    /** image for the points power up*/
    QPixmap* pointsImage;
    /** image for the shield*/
    QPixmap* shieldImage;
    /** image for the gun*/
    QPixmap* gunImage;
    /** image for the better bullet*/
    QPixmap* thickBulletImage;
    /**  image for the ocean*/
    QPixmap* ocean2;
    /** image for the shield of the player*/
    QPixmap* playerShield;
    
    /** pixmap item for the first background*/
    QGraphicsPixmapItem* background;
    /** pixmap item for the second background*/
    QGraphicsPixmapItem* background2;
    
    /** int for which gun to use*/
    int intGunToUse;
    /** int for if the game is going */
    int gameInProgress;
    /** int for the shield hit count*/
    int ShieldHitCount;
    
    /** pointer to the player */
    Player* player;
    
    /**vector that holds the things */
    vector<Thing*> myThings;

    /**int to help regulate the clock */
    int numHandles;
    /**int for the left */
    int left;
    /** int if the ship was just hit */
    int justHit;
    /**int to regulate when you can be hit again */
    int justHitCount;
    
    /** value */
    int value_;        
    /** the timer */
    QTimer *timer;
    /** main layout that is a QVboxlayout */
    QVBoxLayout *mainLayout;
    /** holds the lives, score, and the bomb display */
    QHBoxLayout *lives;

    /** spawn number*/
	int spawnNumber;
    /** regulates how often you can shoot*/
	int justShot;
    /** if an enemy hit an edge*/
	int hitEdge;


public slots:
	/** The slot for the startgame button*/
    bool startGame();
   	/** The slot for the quit game button*/
    void exitGame();
	/** The slot to handle the timer*/
    void handleTimer();
    /** The slot to handle the pause*/
    void pauseGame();
    
protected:
	/**to usekey presses */
	void keyPressEvent(QKeyEvent *event);

};
#endif // MAINWINDOW_H
