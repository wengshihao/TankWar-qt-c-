#ifndef YOU_LOSE_H
#define YOU_LOSE_H
#include <QWidget>

class you_lose:public QWidget
{
    Q_OBJECT
public:
    you_lose(QWidget *parent = nullptr);
    int iswin;
    QPixmap loveforpass;
    QFont tip_font;//字体
    bool isclose;
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *);
    void setTip();
    ~you_lose();
};

#endif // YOU_LOSE_H
