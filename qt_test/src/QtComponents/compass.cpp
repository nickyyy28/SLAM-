#include "compass.h"
#include <QDebug>

Compass::Compass(QWidget *parent) : QWidget(parent)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(50);

    connect(m_timer, &QTimer::timeout, [this]{this->update();});
    m_timer->start();
}

void Compass::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter:: Antialiasing, true);

    //获取尺寸
    int _size = (height() > width() ? width() : height());

    //参考点移至中心
    painter.translate(width() / 2, height() / 2);

    QPen pen;

    //表盘
    pen.setColor(QColor(100, 100, 100));
    painter.setBrush(QColor(100, 100, 100));
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawEllipse(QPoint(0, 0), _size / 2 - 2, _size / 2 - 2);

    //表盘外圈
    painter.setBrush(Qt::NoBrush);
    pen.setColor(Qt::black);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawEllipse(QPoint(0, 0), _size / 2 - 2, _size / 2 - 2);

    float textR = (_size / 2) * 0.7;

#define PI 3.1415926535

    m_scale.clear();
    m_nums.clear();

    for(int i = 0 ; i <= 350 ; i += 10) {

        float r1 = _size / 2 - 4;
        float r2 = 0.9 * r1;

        QPoint p1(r1 * cos(i / 180.0 * PI), - r1 * sin(i / 180.0 * PI));
        QPoint p2(r2 * cos(i / 180.0 * PI), - r2 * sin(i / 180.0 * PI));
        QLine line(p1, p2);
        m_scale.push_back(line);
    }

    for (int i = 0 ; i <= 330 ; i += 30) {
        if (i == 0 || i == 90 || i == 270 || i == 180) {
            continue;
        }

        ScaleNumber num;
        num.angle = (90 - i) > 0 ? (90 - i) : (360 + 90 - i);
        num.text = QString("%1").arg(num.angle / 10);
        num.width = painter.fontMetrics().width(num.text);
        //qDebug() << "width = " << num.width;
        num.pos = QPoint(textR * cos(i / 180.0 * PI), - textR * sin(i / 180.0 * PI));

        m_nums.push_back(num);
    }

#undef PI

    //画刻度
    painter.drawLines(m_scale);

    //画WESN
    float fontSize = (_size / 2) * 0.1;
    QFont _font;

    _font.setPointSizeF(fontSize);
    painter.setFont(_font);


    int strwidth = painter.fontMetrics().width("N");//字符串显示的像素大小

    painter.save();
    painter.translate(QPoint(0, - textR));
    painter.drawText(-strwidth / 2,0,"N");
    painter.restore();

    painter.save();
    painter.translate(QPoint(0, textR));
    painter.rotate(180);
    painter.drawText(-strwidth / 2,0,"S");
    painter.restore();

    painter.save();
    painter.translate(QPoint(-textR, 0));
    painter.rotate(270);
    painter.drawText(-strwidth / 2,0,"W");
    painter.restore();

    painter.save();
    painter.translate(QPoint(textR, 0));
    painter.rotate(90);
    painter.drawText(-strwidth / 2,0,"E");
    painter.restore();

    //画数字
    for (ScaleNumber& num : m_nums) {
        painter.save();
        painter.translate(num.pos);
        painter.rotate(num.angle);
        painter.drawText(-num.width / 2, 0, num.text);
        painter.restore();
    }

    //画中心点
    int _centerR = _size / 2 * 0.07;
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.setBrush(Qt::red);
    painter.drawEllipse(QPoint(0, 0), _centerR, _centerR);

    //画箭头
    int arrowLength = 0.65 * _size;
    //计算旋转角度
    int _angle = m_angle;

    painter.save();

    painter.rotate(_angle);

    pen.setWidth(6);
    painter.setPen(pen);

    painter.drawLine(QPoint(0, arrowLength / 2), QPoint(0, -arrowLength / 2 + 5));

    QVector<QPoint> _polygon;

    _polygon.push_back(QPoint(0, -arrowLength / 2));
    _polygon.push_back(QPoint(- 0.1 * arrowLength / 2, -0.8 * arrowLength / 2));
    _polygon.push_back(QPoint(0.1 * arrowLength / 2, -0.8 * arrowLength / 2));

    painter.drawPolygon(QPolygon(_polygon));

    painter.restore();


}

void Compass::setAngle(float angle)
{
    if (angle > 360 || angle < 0) {
        return;
    }

    m_angle = angle;
}
