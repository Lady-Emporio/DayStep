#include "widget.h"
#include <QDateTime>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    isPlay=false;
    player=new QMediaPlayer(this);
    playlist=new QMediaPlaylist();
    makeGui();
}

void Widget::makeGui(){
    typeRoundLabel=new QLabel(this);
    production=new QLabel(this);
    production->setStyleSheet("border:2px solid blue;");
    firstLabel=new QLabel(this);
    defineLabel=new QLabel(this);
    secondLabel=new QLabel(this);
    inputLabel=new QLabel(this);

    QVBoxLayout*mainLayout =new QVBoxLayout(this);
    QHBoxLayout*labelLayout =new QHBoxLayout(this);
    QHBoxLayout*stateLayout =new QHBoxLayout(this);
    this->setLayout(mainLayout);
    stateLayout->addWidget(typeRoundLabel);
    stateLayout->addWidget(production);
    mainLayout->addLayout(stateLayout);
    mainLayout->addLayout(labelLayout);
    labelLayout->addWidget(firstLabel);
    labelLayout->addWidget(defineLabel);
    labelLayout->addWidget(secondLabel);
    mainLayout->addWidget(inputLabel);
    mainMenu=new QMenuBar(this);
    mainLayout->setMenuBar(mainMenu);
    QMenu * roundMenu=new QMenu("rounds",mainMenu);
    mainMenu->addMenu(roundMenu);
    roundMenu->addAction("roundLowSum",this,SLOT(action_roundLowSum()));
    roundMenu->addAction("roundTableMultiplication",this,SLOT(action_roundTableMultiplication()));
    roundMenu->addAction("roundMiddleSum",this,SLOT(action_roundMiddleSum()));
    roundMenu->addAction("roundBigMultiplication",this,SLOT(action_roundBigMultiplication()));
    roundMenu->addAction("roundBigSum",this,SLOT(action_roundBigSum()));

    mainMenu->addAction("sound",this,SLOT(action_isPlay()));
}

void Widget::setValues(){
    firstLabel->setText(QString("").setNum(first));
    secondLabel->setText(QString("").setNum(second));
    production->setText("");
}

void Widget::inputValue(int key)
{
    if(-2==key){//enter
        int myValue=inputLabel->text().toInt();
        if(myValue!=production->objectName().toInt()){
            inputLabel->setText("");
            soundError(2);
        }else{
            nextRound();
        }
    }
    else if(-3==key){
        QString text=inputLabel->text();
        if(!text.isEmpty()){
            inputLabel->setText(text.remove(text.count()-1,1));
        }
    }else if(-4==key){
        soundValues();
    }else{
        inputLabel->setText( inputLabel->text()+QString("").setNum(key));
    }
}

int Widget::keyToRealValue(int key)
{
    switch ( key ) {
    case 13://enter
        return -2;
    case 8://<-
        return -3;
    case 192://`
        return -4;
    case 48:
        return 0;
    case 49:
        return 1;
    case 50:
        return 2;
    case 51:
        return 3;
    case 52:
        return 4;
    case 53:
        return 5;
    case 54:
        return 6;
    case 55:
        return 7;
    case 56:
        return 8;
    case 57:
        return 9;
    case 96:
        return 0;
    case 97:
        return 1;
    case 98:
        return 2;
    case 99:
        return 3;
    case 100:
        return 4;
    case 101:
        return 5;
    case 102:
        return 6;
    case 103:
        return 7;
    case 104:
        return 8;
    case 105:
        return 9;
    default:
        return -1;
    }
    return -1;
}

void Widget::roundLowSum(){
    QDateTime now=QDateTime::currentDateTime();
    int seek=(now.time().msec()+1)*(now.time().second()+1) * (now.time().minute()+1)*(now.time().hour()+1);
    qsrand(seek);
    typeRoundLabel->setText("roundLowSum");
    first=qrand()%8+2;
    defineLabel->setText("+");
    second=qrand()%8+2;
    production->setObjectName(QString("").setNum(first+second));
}

void Widget::roundMiddleSum()
{
    QDateTime now=QDateTime::currentDateTime();
    int seek=(now.time().msec()+1)*(now.time().second()+1) * (now.time().minute()+1)*(now.time().hour()+1);
    qsrand(seek);
    typeRoundLabel->setText("roundMiddleSum");
    first=qrand()%99+2;
    defineLabel->setText("+");
    second=qrand()%99+2;
    production->setObjectName(QString("").setNum(first+second));
}

void Widget::roundTableMultiplication()
{
    QDateTime now=QDateTime::currentDateTime();
    int seek=(now.time().msec()+1)*(now.time().second()+1) * (now.time().minute()+1)*(now.time().hour()+1);
    qsrand(seek);
    typeRoundLabel->setText("TableMultiplication");
    first=qrand()%8+2;//2:9
    defineLabel->setText("x");
    second=qrand()%8+2;//2:9
    production->setObjectName(QString("").setNum(first*second));
}

void Widget::roundBigMultiplication()
{
    QDateTime now=QDateTime::currentDateTime();
    int seek=(now.time().msec()+1)*(now.time().second()+1) * (now.time().minute()+1)*(now.time().hour()+1);
    qsrand(seek);
    typeRoundLabel->setText("roundBigMultiplication");
    first=qrand()%9+11;
    defineLabel->setText("x");
    second=qrand()%8+2;
    production->setObjectName(QString("").setNum(first*second));
}
void Widget::action_roundBigMultiplication(){
    roundBigMultiplication();
    setValues();
}

void Widget::nextRound()
{
    QString nameRound=typeRoundLabel->text();
    inputLabel->setText("");
    if("roundLowSum"==nameRound){
        action_roundLowSum();
    }else if("TableMultiplication"==nameRound){
        action_roundTableMultiplication();
    }else if("roundMiddleSum"==nameRound){
        action_roundMiddleSum();
    }else if("roundBigMultiplication"==nameRound){
        action_roundBigMultiplication();
    }else if("roundBigSum"==nameRound){
        action_roundBigSum();
    }
    if(isPlay){
        soundValues();
    }
}

void Widget::soundValues()
{
    if(isPlay){
        playlist->clear();
        playlist->addMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("./Nombers/"+firstLabel->text()+".mp3")));
        playlist->addMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("./Nombers/"+defineLabel->text()+".mp3")));
        playlist->addMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("./Nombers/"+secondLabel->text()+".mp3")));
        playlist->setCurrentIndex(0);
        player->setPlaylist(playlist);
        player->play();
    }
}

void Widget::soundError(int type)
{
    if(1==type){//not int
        QFile f(QDir::toNativeSeparators("./Sound/VeryFastBoof.mp3"));
        if(f.exists()){
            player->setMedia(QUrl::fromLocalFile(f.fileName()));
            player->play();
        }
    }else if(2==type){//wrong answer
        QFile f(QDir::toNativeSeparators("./Sound/Fasr07secLOWbum.mp3"));
        if(f.exists()){
            player->setMedia(QUrl::fromLocalFile(f.fileName()));
            player->play();
        }
    }
}

void Widget::action_roundBigSum()
{
    QDateTime now=QDateTime::currentDateTime();
    int seek=(now.time().msec()+1)*(now.time().second()+1) * (now.time().minute()+1)*(now.time().hour()+1);
    qsrand(seek);
    typeRoundLabel->setText("roundBigSum");
    first=qrand()%98+102;//102:199
    defineLabel->setText("+");
    second=qrand()%98+102;//102:199
    production->setObjectName(QString("").setNum(first+second));
    setValues();
}

void Widget::action_roundLowSum()
{
    roundLowSum();
    setValues();
}

void Widget::action_roundTableMultiplication()
{
    roundTableMultiplication();
    setValues();
}

void Widget::action_roundMiddleSum()
{
    roundMiddleSum();
    setValues();
}

void Widget::action_isPlay()
{
    if(isPlay){
        mainMenu->setStyleSheet("");
        isPlay=false;
    }else{
        isPlay=true;
        mainMenu->setStyleSheet("background-color:red;");
    }
}
