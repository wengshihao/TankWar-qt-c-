#ifndef TIPWIDOW_H
#define TIPWIDOW_H

#include <QWidget>

class tipwidow : public QWidget
{
    Q_OBJECT
public:
    int iswin;
    QPixmap loveforpass;
    QFont tip_font;//字体
    bool isclose;
    tipwidow(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *);
    void setTip();
    ~tipwidow();
};

#endif // TIPWIDOW_H
