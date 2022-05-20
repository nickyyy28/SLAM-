#ifndef COMPASS_H
#define COMPASS_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QVector>
#include <qmath.h>
#include <QTimer>

class Compass : public QWidget
{
    Q_OBJECT
public:
    explicit Compass(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

    void setAngle(float angle);

private:
    typedef struct {
        QString text;
        QPoint pos;
        int width;
        int angle;

    }ScaleNumber;

    QPixmap m_pixmap;
    int m_size{50};

    QVector<QLine> m_scale; /* 表盘刻度线条 */
    QVector<ScaleNumber> m_nums;    /* 表盘数字 */
    float m_angle{0};
    QTimer *m_timer;
signals:



};

#endif // COMPASS_H
