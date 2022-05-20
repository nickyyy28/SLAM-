/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qwt_compass.h"
#include "qwt_dial.h"
#include "videoview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindowDesign
{
public:
    QAction *action_Quit;
    QAction *action_Preferences;
    QAction *actionAbout;
    QAction *actionAbout_Qt;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QWidget *configWidget;
    QVBoxLayout *verticalLayout;
    QWidget *robotstate;
    QTabWidget *tabWidget_2;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLineEdit *masterUrl;
    QLabel *label_4;
    QLineEdit *hostIP;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btn_connect;
    QPushButton *btn_quit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLineEdit *sensor_IP;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLineEdit *sensor_port;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *btn_start_listen;
    QPushButton *btn_stop_listen;
    QSpacerItem *verticalSpacer;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QTreeWidget *treeWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_8;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QLabel *label_10;
    QLabel *label_8;
    QLabel *label_9;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_9;
    QWidget *widget_11;
    QVBoxLayout *verticalLayout_9;
    QwtDial *x_speed_dial;
    QLabel *x_speed_label;
    QWidget *widget_10;
    QVBoxLayout *verticalLayout_8;
    QwtDial *y_speed_dial;
    QLabel *y_speed_label;
    QWidget *widget_9;
    QVBoxLayout *verticalLayout_7;
    QwtCompass *compass;
    QLabel *mag_label;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_11;
    QLabel *label_7;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QVBoxLayout *render_layout;
    QWidget *tab_5;
    QGridLayout *gridLayout_3;
    QWidget *widget_4;
    QGridLayout *gridLayout_5;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_6;
    VideoView *camera_view;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *btn_opencamera;
    QComboBox *camera_index;
    QWidget *tab_6;
    QGridLayout *gridLayout_6;
    QTextEdit *log_edit;

    void setupUi(QMainWindow *MainWindowDesign)
    {
        if (MainWindowDesign->objectName().isEmpty())
            MainWindowDesign->setObjectName(QString::fromUtf8("MainWindowDesign"));
        MainWindowDesign->resize(1036, 693);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowDesign->setWindowIcon(icon);
        MainWindowDesign->setLocale(QLocale(QLocale::English, QLocale::Australia));
        action_Quit = new QAction(MainWindowDesign);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        action_Quit->setShortcutContext(Qt::ApplicationShortcut);
        action_Preferences = new QAction(MainWindowDesign);
        action_Preferences->setObjectName(QString::fromUtf8("action_Preferences"));
        actionAbout = new QAction(MainWindowDesign);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAbout_Qt = new QAction(MainWindowDesign);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        centralwidget = new QWidget(MainWindowDesign);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMaximumSize(QSize(100000, 100000));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        configWidget = new QWidget(centralwidget);
        configWidget->setObjectName(QString::fromUtf8("configWidget"));
        configWidget->setMinimumSize(QSize(300, 0));
        configWidget->setMaximumSize(QSize(300, 16777215));
        verticalLayout = new QVBoxLayout(configWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        robotstate = new QWidget(configWidget);
        robotstate->setObjectName(QString::fromUtf8("robotstate"));
        robotstate->setMinimumSize(QSize(0, 30));

        verticalLayout->addWidget(robotstate);

        tabWidget_2 = new QTabWidget(configWidget);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_3 = new QVBoxLayout(tab_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_3->addWidget(label_3);

        masterUrl = new QLineEdit(tab_3);
        masterUrl->setObjectName(QString::fromUtf8("masterUrl"));

        verticalLayout_3->addWidget(masterUrl);

        label_4 = new QLabel(tab_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_3->addWidget(label_4);

        hostIP = new QLineEdit(tab_3);
        hostIP->setObjectName(QString::fromUtf8("hostIP"));

        verticalLayout_3->addWidget(hostIP);

        widget_3 = new QWidget(tab_3);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btn_connect = new QPushButton(widget_3);
        btn_connect->setObjectName(QString::fromUtf8("btn_connect"));

        horizontalLayout_3->addWidget(btn_connect);

        btn_quit = new QPushButton(widget_3);
        btn_quit->setObjectName(QString::fromUtf8("btn_quit"));

        horizontalLayout_3->addWidget(btn_quit);


        verticalLayout_3->addWidget(widget_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(tab_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(80, 0));
        label_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_5);

        sensor_IP = new QLineEdit(tab_3);
        sensor_IP->setObjectName(QString::fromUtf8("sensor_IP"));

        horizontalLayout_5->addWidget(sensor_IP);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_6 = new QLabel(tab_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(80, 0));
        label_6->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_6);

        sensor_port = new QLineEdit(tab_3);
        sensor_port->setObjectName(QString::fromUtf8("sensor_port"));

        horizontalLayout_4->addWidget(sensor_port);


        verticalLayout_3->addLayout(horizontalLayout_4);

        widget_2 = new QWidget(tab_3);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_6 = new QHBoxLayout(widget_2);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        btn_start_listen = new QPushButton(widget_2);
        btn_start_listen->setObjectName(QString::fromUtf8("btn_start_listen"));

        horizontalLayout_6->addWidget(btn_start_listen);

        btn_stop_listen = new QPushButton(widget_2);
        btn_stop_listen->setObjectName(QString::fromUtf8("btn_stop_listen"));

        horizontalLayout_6->addWidget(btn_stop_listen);


        verticalLayout_3->addWidget(widget_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        tabWidget_2->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_2 = new QVBoxLayout(tab_4);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(tab_4);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(16, 16));
        label->setMaximumSize(QSize(16, 16));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/display.png")));

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(tab_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);


        verticalLayout_2->addLayout(horizontalLayout);

        treeWidget = new QTreeWidget(tab_4);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));

        verticalLayout_2->addWidget(treeWidget);

        tabWidget_2->addTab(tab_4, QString());

        verticalLayout->addWidget(tabWidget_2);


        gridLayout->addWidget(configWidget, 0, 2, 1, 1);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_4 = new QGridLayout(tab);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        widget = new QWidget(tab);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMaximumSize(QSize(16777215, 250));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_10 = new QLabel(widget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 4, 0, 1, 1);

        label_8 = new QLabel(widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 1, 0, 1, 1);

        label_9 = new QLabel(widget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 3, 0, 1, 1);


        horizontalLayout_8->addWidget(widget);


        gridLayout_4->addLayout(horizontalLayout_8, 1, 0, 1, 1);

        widget_7 = new QWidget(tab);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        horizontalLayout_9 = new QHBoxLayout(widget_7);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        widget_11 = new QWidget(widget_7);
        widget_11->setObjectName(QString::fromUtf8("widget_11"));
        verticalLayout_9 = new QVBoxLayout(widget_11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        x_speed_dial = new QwtDial(widget_11);
        x_speed_dial->setObjectName(QString::fromUtf8("x_speed_dial"));
        x_speed_dial->setLineWidth(4);

        verticalLayout_9->addWidget(x_speed_dial);

        x_speed_label = new QLabel(widget_11);
        x_speed_label->setObjectName(QString::fromUtf8("x_speed_label"));
        x_speed_label->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(x_speed_label);


        horizontalLayout_9->addWidget(widget_11);

        widget_10 = new QWidget(widget_7);
        widget_10->setObjectName(QString::fromUtf8("widget_10"));
        verticalLayout_8 = new QVBoxLayout(widget_10);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        y_speed_dial = new QwtDial(widget_10);
        y_speed_dial->setObjectName(QString::fromUtf8("y_speed_dial"));
        y_speed_dial->setLineWidth(4);

        verticalLayout_8->addWidget(y_speed_dial);

        y_speed_label = new QLabel(widget_10);
        y_speed_label->setObjectName(QString::fromUtf8("y_speed_label"));
        y_speed_label->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(y_speed_label);


        horizontalLayout_9->addWidget(widget_10);

        widget_9 = new QWidget(widget_7);
        widget_9->setObjectName(QString::fromUtf8("widget_9"));
        verticalLayout_7 = new QVBoxLayout(widget_9);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        compass = new QwtCompass(widget_9);
        compass->setObjectName(QString::fromUtf8("compass"));
        compass->setLineWidth(4);

        verticalLayout_7->addWidget(compass);

        mag_label = new QLabel(widget_9);
        mag_label->setObjectName(QString::fromUtf8("mag_label"));
        mag_label->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(mag_label);


        horizontalLayout_9->addWidget(widget_9);


        gridLayout_4->addWidget(widget_7, 2, 0, 1, 1);

        widget_8 = new QWidget(tab);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        widget_8->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_10 = new QHBoxLayout(widget_8);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_11 = new QLabel(widget_8);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(label_11);

        label_7 = new QLabel(widget_8);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMaximumSize(QSize(16777215, 51515));
        label_7->setLayoutDirection(Qt::RightToLeft);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_10->addWidget(label_7);


        gridLayout_4->addWidget(widget_8, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_5 = new QVBoxLayout(tab_2);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_2 = new QPushButton(tab_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout_4->addLayout(horizontalLayout_2);

        render_layout = new QVBoxLayout();
        render_layout->setObjectName(QString::fromUtf8("render_layout"));

        verticalLayout_4->addLayout(render_layout);


        verticalLayout_5->addLayout(verticalLayout_4);

        tabWidget->addTab(tab_2, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        gridLayout_3 = new QGridLayout(tab_5);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        widget_4 = new QWidget(tab_5);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        gridLayout_5 = new QGridLayout(widget_4);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        widget_5 = new QWidget(widget_4);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setMaximumSize(QSize(50000, 50000));
        verticalLayout_6 = new QVBoxLayout(widget_5);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        camera_view = new VideoView(widget_5);
        camera_view->setObjectName(QString::fromUtf8("camera_view"));
        camera_view->setMinimumSize(QSize(200, 200));
        camera_view->setMaximumSize(QSize(5000, 5000));

        verticalLayout_6->addWidget(camera_view);

        widget_6 = new QWidget(widget_5);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        widget_6->setMinimumSize(QSize(200, 0));
        widget_6->setMaximumSize(QSize(50000, 40));
        horizontalLayout_7 = new QHBoxLayout(widget_6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        btn_opencamera = new QPushButton(widget_6);
        btn_opencamera->setObjectName(QString::fromUtf8("btn_opencamera"));

        horizontalLayout_7->addWidget(btn_opencamera);

        camera_index = new QComboBox(widget_6);
        camera_index->setObjectName(QString::fromUtf8("camera_index"));

        horizontalLayout_7->addWidget(camera_index);


        verticalLayout_6->addWidget(widget_6);


        gridLayout_5->addWidget(widget_5, 0, 0, 1, 1);


        gridLayout_3->addWidget(widget_4, 0, 0, 1, 1);

        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        gridLayout_6 = new QGridLayout(tab_6);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        log_edit = new QTextEdit(tab_6);
        log_edit->setObjectName(QString::fromUtf8("log_edit"));

        gridLayout_6->addWidget(log_edit, 0, 0, 1, 1);

        tabWidget->addTab(tab_6, QString());

        gridLayout->addWidget(tabWidget, 0, 1, 1, 1);

        MainWindowDesign->setCentralWidget(centralwidget);

        retranslateUi(MainWindowDesign);
        QObject::connect(action_Quit, SIGNAL(triggered()), MainWindowDesign, SLOT(close()));

        tabWidget_2->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindowDesign);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowDesign)
    {
        MainWindowDesign->setWindowTitle(QCoreApplication::translate("MainWindowDesign", "\346\234\272\345\231\250\344\272\272", nullptr));
        action_Quit->setText(QCoreApplication::translate("MainWindowDesign", "&Quit", nullptr));
#if QT_CONFIG(shortcut)
        action_Quit->setShortcut(QCoreApplication::translate("MainWindowDesign", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Preferences->setText(QCoreApplication::translate("MainWindowDesign", "&Preferences", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindowDesign", "&About", nullptr));
        actionAbout_Qt->setText(QCoreApplication::translate("MainWindowDesign", "About &Qt", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindowDesign", "Ros Master Url", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindowDesign", "Host IP", nullptr));
        btn_connect->setText(QCoreApplication::translate("MainWindowDesign", "connect", nullptr));
        btn_quit->setText(QCoreApplication::translate("MainWindowDesign", "quit", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindowDesign", "\344\270\213\344\275\215\346\234\272IP", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindowDesign", "\344\270\213\344\275\215\346\234\272\347\253\257\345\217\243", nullptr));
        btn_start_listen->setText(QCoreApplication::translate("MainWindowDesign", "\350\277\236\346\216\245", nullptr));
        btn_stop_listen->setText(QCoreApplication::translate("MainWindowDesign", "\346\226\255\345\274\200", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QCoreApplication::translate("MainWindowDesign", "ROS", nullptr));
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindowDesign", "Display", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QCoreApplication::translate("MainWindowDesign", "rviz", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindowDesign", "\347\243\201\345\201\217\350\247\222:\344\270\234132\345\272\246", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindowDesign", "\347\273\217\347\272\254\345\272\246: \n"
"    \344\270\234\347\273\217ddddmm.mmmm\n"
"    \345\214\227\347\272\254ddmm.mmmm", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindowDesign", "\345\234\260\351\200\237: 001.3\350\212\202", nullptr));
        x_speed_label->setText(QCoreApplication::translate("MainWindowDesign", "X\350\275\264\351\200\237\345\272\246", nullptr));
        y_speed_label->setText(QCoreApplication::translate("MainWindowDesign", "Y\350\275\264\351\200\237\345\272\246", nullptr));
        mag_label->setText(QCoreApplication::translate("MainWindowDesign", "\347\243\201\345\201\217\350\247\222", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindowDesign", "\346\227\266\351\227\264\346\210\263\357\274\232", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindowDesign", "UTC\346\227\266\351\227\264: 2022-3-15:12:03:43", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindowDesign", "\345\257\274\350\210\252\344\277\241\346\201\257", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindowDesign", "PushButton", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindowDesign", "PushButton", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindowDesign", "rviz", nullptr));
        btn_opencamera->setText(QCoreApplication::translate("MainWindowDesign", "open", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("MainWindowDesign", "\347\233\270\346\234\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QCoreApplication::translate("MainWindowDesign", "\346\227\245\345\277\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowDesign: public Ui_MainWindowDesign {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAIN_WINDOW_H
