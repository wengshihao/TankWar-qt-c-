#ifndef YOU_PASS_THE_GAME_H
#define YOU_PASS_THE_GAME_H

#include <QWidget>
class you_pass_the_game:public QWidget
{
    Q_OBJECT
public:
    int iswin;
    QPixmap loveforpass;
    QFont tip_font;//字体
    bool isclose;
    you_pass_the_game(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *);
    void setTip();
    ~you_pass_the_game();
};

#endif // YOU_PASS_THE_GAME_H
