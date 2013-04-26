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

class MainWindow : public QWidget {
    Q_OBJECT
    
public:
	/**Constructor */
    explicit MainWindow();
	/**Destructor */
    ~MainWindow();
	/**show the GUI */
    void  mousePressEvent(QGraphicsSceneMouseEvent *event);

    
private:
    QGraphicsScene *startingScene;
    QGraphicsScene *gameScene;
    QGraphicsView *view;
    
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *pauseButton;
    
    QTextEdit *name;
    QLabel *intro;
    QLabel *namePrompt;
    QLabel *instructions;
    
    QLabel *heartOne;
    QLabel *heartTwo;
    QLabel *heartThree;
    
    
    QLabel *bombOne;
    QLabel *bombTwo;
    QLabel *bombThree;
    
    QLabel *score;
    QLabel *scorePrompt;
    
    int scoreNumber;
    int numBombs;
    int bombTimer;
    
    QPixmap* sharkImage;
    QPixmap* playerImage;
    QPixmap* squidImage;
    QPixmap* mantaImage;
    QPixmap* bulletImage;
    QPixmap* heartImage;
    QPixmap* bombImage;
    QPixmap* pointsImage;
    QPixmap* shieldImage;
    QPixmap* gunImage;
    QPixmap* thickBulletImage;
    QPixmap* ocean2;
    QPixmap* playerShield;
    
    QGraphicsPixmapItem* background;
    QGraphicsPixmapItem* background2;
    
    int intGunToUse;
    int gameInProgress;
    int ShieldHitCount;
    
    Player* player;
    
    vector<Thing*> myThings;

    int numHandles;
    int left;
    int justHit;
    int justHitCount;
    
    int value_;    
    QTimer *timer;
    QVBoxLayout *mainLayout;
    QHBoxLayout *lives;

	int spawnNumber;
	int justShot;
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
	void keyPressEvent(QKeyEvent *event);

};
#endif // MAINWINDOW_H
