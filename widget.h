#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QMessageBox>
#include <QDebug>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QUrl>
#include <QDir>
#include <QMenu>
class Widget : public QWidget
{
    Q_OBJECT
    void makeGui();
public:
    QLabel * typeRoundLabel;
    QLabel * production;
    QLabel * firstLabel;
    QLabel * defineLabel;
    QLabel * secondLabel;
    QLabel * inputLabel;
    int first;
    int second;
    bool isPlay;
    void setValues();
    void inputValue(int key);
    int keyToRealValue(int key);
    explicit Widget(QWidget *parent = 0);
    void roundLowSum();//2:9 + 2:9
    void roundMiddleSum();//2:99 + 2:99
    void roundTableMultiplication(); //2:9 * 2:9
    void roundBigMultiplication();//11:19 * 2*10
    //void roundModulo();//10:99 % 2:9
    //void roundLowDivision();//10:99 / 2:9
    //void roundMiddleSubtraction(); //10:99 - 10:99
    void nextRound();
    void soundValues();
    void soundError(int type);
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QMenuBar * mainMenu;
public slots:
    void action_roundBigSum();//101:199 + 101:199;
    void action_roundLowSum();
    void action_roundTableMultiplication();
    void action_roundMiddleSum();
    void action_roundBigMultiplication();
    void action_isPlay();
};
struct staticVariable{
    Widget *w;
    staticVariable(){
        w=new Widget();
    }
    static staticVariable * GetStatic(){
        static staticVariable * statica=new staticVariable;
        return statica;
    }
};
#endif // WIDGET_H
