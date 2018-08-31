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
    explicit Widget(QWidget *parent = 0);
    QLabel * typeRoundLabel;
    QLabel * production;
    QLabel * firstLabel;
    QLabel * defineLabel;
    QLabel * secondLabel;
    QLabel * inputLabel;
    int first;
    int second;
    bool isPlay; //если Ложь не играть музыку кроме ошибок.
    QMenuBar * mainMenu; //для визуализации isPlay. Если крсное тогда isPlay=Истина и звучит нажатие
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    void setValues();//запихивает в label first and second, чисто для уменьшения кода
    void inputValue(int key);// обработка ввода, преобразованного в значение из keyToRealValue.
    int keyToRealValue(int key);//преобразовывает код клавиатуры в значение.
    void soundError(int type);//для уменьшения кода. в зависимости от типа ( неправильный ответ, ввод не числа) играет определенная музыка
    void soundValues();//Если isPlay, то озвучит условие
    void fillPlayList(QString s_value);
    int getValue(int min,int max);
    void fillAll(int f_min,int f_max,int s_min,int s_max,QString state,QString nameRound);

    void roundLowSum();
    void roundMiddleSum();
    void roundTableMultiplication();
    void roundBigMultiplication();
    void roundModulo();
    void roundLowDivision();
    void roundMiddleSubtraction();
    void roundBigSum();
public slots:
    void action_isPlay();
    void nextRound(); // запускается каждый раз при вводе правильного ответа.
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
