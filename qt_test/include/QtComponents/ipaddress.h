#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>

#include <QKeyEvent>

class IPAddress : public QWidget
{
    Q_OBJECT
public:
    explicit IPAddress(QWidget *parent = nullptr);

    QString getIP() const;
    void setIP(QString ip);
    void setIP(int ip1, int ip2, int ip3, int ip4);
    void setText(QString text);

private:


    /* the IP total layout */
    QHBoxLayout *layout{nullptr};

    /* the 4 ip edit box */
    QLineEdit *edit1;
    QLineEdit *edit2;
    QLineEdit *edit3;
    QLineEdit *edit4;

    /* the dots */
    QLabel *dot1;
    QLabel *dot2;
    QLabel *dot3;

signals:

};

#endif // IPADDRESS_H
