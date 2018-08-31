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
    QStringList actionNames;
    actionNames<<"roundLowSum"
                <<"roundMiddleSum"
                <<"roundTableMultiplication"
                <<"roundBigMultiplication"
                <<"roundModulo"
                <<"roundLowDivision"
                <<"roundMiddleSubtraction"
                <<"roundBigSum";
    for(QString nameAction:actionNames){
    QAction *action = roundMenu->addAction(nameAction,this,SLOT(nextRound()));
    action->setObjectName("actionToStart");
    action->setData(nameAction);
    mainMenu->addMenu(roundMenu);
    }
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

void Widget::nextRound()
{
    if((this->sender()!=nullptr)&&("actionToStart"==this->sender()->objectName())){
        QAction *thisAction=(QAction *)this->sender();
        typeRoundLabel->setText(thisAction->data().toString());
    }
    QString nameRound=typeRoundLabel->text();
    inputLabel->setText("");
    if("roundLowSum"==nameRound){
        roundLowSum();
    }else if("roundMiddleSum"==nameRound){
        roundMiddleSum();
    }else if("roundTableMultiplication"==nameRound){
        roundTableMultiplication();
    }else if("roundBigMultiplication"==nameRound){
        roundBigMultiplication();
    }else if("roundModulo"==nameRound){
        roundModulo();
    }else if("roundLowDivision"==nameRound){
        roundLowDivision();
    }else if("roundMiddleSubtraction"==nameRound){
        roundMiddleSubtraction();
    }else if("roundBigSum"==nameRound){
        roundBigSum();
    }
    soundValues();
}

void Widget::soundValues()
{
    if(isPlay){
        playlist->clear();
        fillPlayList(firstLabel->text());
        playlist->addMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("./Nombers/"+defineLabel->text()+".mp3")));
        fillPlayList(secondLabel->text());
        playlist->setCurrentIndex(0);
        player->setPlaylist(playlist);
        player->play();
    }
}

void Widget::fillPlayList(QString s_value)
{
    int value=s_value.toInt();
    if( ((value<20)||(value%10==0)) && (value<=100) ){
        playlist->addMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("./Nombers/"+s_value+".mp3")));
    }else if(  ((value>20)||(value%10!=0)) && (value<100)  ){
        QString ten=s_value.left(1)+"0";
        QString one=s_value.right(1);
        playlist->addMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("./Nombers/"+ten+".mp3")));
        playlist->addMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("./Nombers/"+one+".mp3")));
    }else if(value>100 && value<200){
        QString h=s_value.left(1)+"00";
        QString ten=s_value.mid(1,1)+"0";
        QString one=s_value.right(1);
        playlist->addMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("./Nombers/"+h+".mp3")));
        playlist->addMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("./Nombers/"+ten+".mp3")));
        playlist->addMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("./Nombers/"+one+".mp3")));
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

int Widget::getValue(int min,int max){//включительно с min по включительно max
    QDateTime now=QDateTime::currentDateTime();
    int msec=now.time().msec()+1;
    int seek=msec*(now.time().second()+1) * (now.time().minute()+1)*(now.time().hour()+1);
    static int seek_version=msec;
    if(seek_version!=msec)
    {
        seek_version=msec;
        qsrand(seek);
    }
    return qrand()%(max-min+1)+min;
}
void Widget::fillAll(int f_min,int f_max,int s_min,int s_max,QString state,QString nameRound){
    typeRoundLabel->setText(nameRound);
    first=getValue(f_min,f_max);
    second=getValue(s_min,s_max);
    if("+"==state){
        defineLabel->setText("+");
        production->setObjectName(QString("").setNum(first+second));
    }else if("x"==state){
        defineLabel->setText("x");
        production->setObjectName(QString("").setNum(first*second));
    }else if("%"==state){
        if(first<second){
            int i=first;
            first=second;
            second=i;
        }
        defineLabel->setText("%");
        production->setObjectName(QString("").setNum(first%second));
    }else if("-"==state){
        if(first<second){
            int i=first;
            first=second;
            second=i;
        }
        defineLabel->setText("-");
        production->setObjectName(QString("").setNum(first-second));
    }else if("⌠"==state){
        if(first<second){
            int i=first;
            first=second;
            second=i;
        }
        defineLabel->setText("⌠");
        production->setObjectName(QString("").setNum(first/second));
    }
    setValues();
}

void Widget::roundLowSum(){//2:9 + 2:9
    fillAll(2,9,2,9,"+","roundLowSum");
}
void Widget::roundMiddleSum(){//2:99 + 2:99
    fillAll(2,99,2,99,"+","roundMiddleSum");
}
void Widget::roundTableMultiplication(){//2:9 * 2:9
    fillAll(2,9,2,9,"x","roundTableMultiplication");
}
void Widget::roundBigMultiplication(){//11:19 * 2*10
    fillAll(11,19,2,10,"x","roundBigMultiplication");
}
void Widget::roundModulo(){//10:99 % 2:9
    fillAll(10,99,2,9,"%","roundModulo");
}
void Widget::roundLowDivision(){//10:99 /  ⌠ 2:9
    fillAll(10,99,2,9,"⌠","roundLowDivision");
}
void Widget::roundMiddleSubtraction(){//10:99 - 10:99
    fillAll(10,99,10,99,"-","roundMiddleSubtraction");
}
void Widget::roundBigSum(){//101:199 + 101:199
    fillAll(101,199,101,199,"+","roundBigSum");
}
