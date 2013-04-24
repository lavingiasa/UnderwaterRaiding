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
    //void show();
    void  mousePressEvent(QGraphicsSceneMouseEvent *event);

    
private:
    QGraphicsScene *startingScene;
    QGraphicsScene *gameScene;
    QGraphicsView *view;
    QPushButton *startButton;
    QPushButton *stopButton;
    QTextEdit *name;
    QLabel *intro;
    QLabel *namePrompt;
    
    QPixmap* sharkImage;
    QPixmap* playerImage;
    QPixmap* squidImage;
    QPixmap* mantaImage;
    
    Player* player;
    
    vector<Thing*> myThings;
    


    int numHandles;
    
    int value_;    
    QTimer *timer;
    QVBoxLayout *mainLayout;



public slots:
	/** The slot for the startgame button*/
    bool startGame();
   	/** The slot for the quit game button*/
    void exitGame();
	/** The slot to handle the timer*/
    void handleTimer();
    
protected:
	void keyPressEvent(QKeyEvent *event);

};
#endif // MAINWINDOW_H
