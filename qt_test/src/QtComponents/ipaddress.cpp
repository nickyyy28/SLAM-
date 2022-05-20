#include "ipaddress.h"
#include <QIntValidator>
#include <QDebug>

IPAddress::IPAddress(QWidget *parent) : QWidget(parent)
{
    this->edit1 = new QLineEdit(this);
    this->edit2 = new QLineEdit(this);
    this->edit3 = new QLineEdit(this);
    this->edit4 = new QLineEdit(this);

    edit1->setValidator(new QIntValidator(0, 255, this));
    edit2->setValidator(new QIntValidator(0, 255, this));
    edit3->setValidator(new QIntValidator(0, 255, this));
    edit4->setValidator(new QIntValidator(0, 255, this));

    // edit1->setFixedHeight(height() * 0.9);
    // edit2->setFixedHeight(height() * 0.9);
    // edit3->setFixedHeight(height() * 0.9);
    // edit4->setFixedHeight(height() * 0.9);

    this->dot1 = new QLabel(this);
    this->dot2 = new QLabel(this);
    this->dot3 = new QLabel(this);

    this->layout = new QHBoxLayout(this);

    layout->addWidget(edit1);

    layout->addWidget(dot1);

    layout->addWidget(edit2);

    layout->addWidget(dot2);

    layout->addWidget(edit3);

    layout->addWidget(dot3);

    layout->addWidget(edit4);

    dot1->setText(".");
    dot2->setText(".");
    dot3->setText(".");

    connect(edit1, &QLineEdit::editingFinished, [&]{
        if (edit1->hasFocus()) {
            this->edit2->setFocus();
        }
    });

    connect(edit2, &QLineEdit::editingFinished, [&]{
        if (edit2->hasFocus()) {
            this->edit3->setFocus();
        }
    });

    connect(edit3, &QLineEdit::editingFinished, [&]{
        if (edit3->hasFocus()) {
            this->edit4->setFocus();
        }
    });
}

QString IPAddress::getIP() const
{
    return QString("%1.%2.%3.%4").arg(edit1->text().toInt()).arg(edit2->text().toInt()).arg(edit3->text().toInt()).arg(edit4->text().toInt());
}

void IPAddress::setIP(QString ip)
{
    QStringList iplist = ip.split(".");

    if (iplist.size() != 4) {
        qDebug() << "[WARN]: error ip data";
    }

    this->edit1->setText(iplist.at(0));
    this->edit2->setText(iplist.at(1));
    this->edit3->setText(iplist.at(2));
    this->edit4->setText(iplist.at(3));
}

void IPAddress::setIP(int ip1, int ip2, int ip3, int ip4)
{
    this->edit1->setText(QString(ip1));
    this->edit2->setText(QString(ip2));
    this->edit3->setText(QString(ip3));
    this->edit4->setText(QString(ip4));
}

void IPAddress::setText(QString text)
{
    this->setIP(text);
}
