/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QComboBox>
#include <QStringList>
#include <QMessageBox>
#include <QCheckBox>
#include <iostream>
#include "../include/qt_test/main_window.hpp"
#include <ros/ros.h>

#include <qwt_dial_needle.h>

// #include <unordered_map>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qt_test {

using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent), node(new RNode(argc, argv, "")), m_rviz(this)
	
{
	pix_error = new QPixmap(":/images/error.png");
	pix_ok = new QPixmap(":/images/ok.png");

	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.

	ui.treeWidget->setWindowTitle(QString("Display"));
	ui.treeWidget->setHeaderLabels(QStringList() << "key" << "value");
	this->setWindowIcon(QIcon(":/images/rosicon.png"));

	/****************************************************************/

	QTreeWidgetItem *Global = new QTreeWidgetItem(QStringList() << "Global Options");
	ui.treeWidget->addTopLevelItem(Global);

	QTreeWidgetItem *fixed_frame = new QTreeWidgetItem(QStringList() << "Fixed Frame");
	fixed_box = new QComboBox(this);
	fixed_box->addItem("base_link");
	fixed_box->setMaximumWidth(200);
	fixed_box->setEditable(true);

	Global->addChild(fixed_frame);
	Global->setIcon(0, QIcon(":/images/setting.png"));

	ui.treeWidget->setItemWidget(fixed_frame, 1, fixed_box);

	ui.tabWidget_2->setCurrentIndex(1);

	/*************************************************************/

	QTreeWidgetItem *Grid = new QTreeWidgetItem(QStringList() << "Grid");
	Grid->setIcon(0, QIcon(":/images/grid.png"));
	ui.treeWidget->addTopLevelItem(Grid);
	grid_box = new QCheckBox(this);
	ui.treeWidget->setItemWidget(Grid, 1, grid_box);

	grid_box->setChecked(true);

	QTreeWidgetItem *cell_count = new QTreeWidgetItem(QStringList() << "Cell Counts");
	cell_count_box = new QSpinBox(this);
	Grid->addChild(cell_count);
	ui.treeWidget->setItemWidget(cell_count, 1, cell_count_box);
	this->cell_count_box->setValue(10);
	cell_count_box->setRange(0, 100);

	QTreeWidgetItem *Color = new QTreeWidgetItem(QStringList() << "Color");
	color_box = new QComboBox(this);
	Grid->addChild(Color);
	ui.treeWidget->setItemWidget(Color, 1, color_box);
	color_box->setEditable(true);
	color_box->addItem(QString("160;160;160"));

	/***********************************************************/

	QTreeWidgetItem *TF = new QTreeWidgetItem(QStringList() << "TF");
	TF->setIcon(0, QIcon(":/images/TF.png"));
	ui.treeWidget->addTopLevelItem(TF);
	this->tf_box = new QCheckBox(this);
	ui.treeWidget->setItemWidget(TF, 1, tf_box);


	/************************************************************/

	QTreeWidgetItem *Laser = new QTreeWidgetItem(QStringList() << "Scan");
	Laser->setIcon(0, QIcon(":/images/laser.png"));
	ui.treeWidget->addTopLevelItem(Laser);
	this->laserCheckBox = new QCheckBox(this);
	ui.treeWidget->setItemWidget(Laser, 1, laserCheckBox);

	QTreeWidgetItem *statusLaser = new QTreeWidgetItem(QStringList() << "status");
	status_Laser = new QLabel(this);
	status_Laser->setPixmap(*pix_error);
	Laser->addChild(statusLaser);
	ui.treeWidget->setItemWidget(statusLaser, 1, status_Laser);

	QTreeWidgetItem *LaserTopic = new QTreeWidgetItem(QStringList() << "topic");
	laserTopicBox = new QComboBox(this);
	Laser->addChild(LaserTopic);
	ui.treeWidget->setItemWidget(LaserTopic, 1, laserTopicBox);
	laserTopicBox->setEditable(true);
	laserTopicBox->addItem(QString("/scan"));

	QTreeWidgetItem *PointSize = new QTreeWidgetItem(QStringList() << "size");
	pointSize_edit = new QLineEdit(this);
	Laser->addChild(PointSize);
	ui.treeWidget->setItemWidget(PointSize, 1, pointSize_edit);
	pointSize_edit->setText(QString("0.01"));

	/************************************************************/

	QTreeWidgetItem *Map = new QTreeWidgetItem(QStringList() << "Map");
	Map->setIcon(0, QIcon(":/images/map.png"));
	ui.treeWidget->addTopLevelItem(Map);

	/************************************************************/

	Global->setExpanded(true);
	Grid->setExpanded(true);
	TF->setExpanded(true);
	Laser->setExpanded(true);

	ui.camera_view->init("/home/book/ROS_study/catkin_ws/src/qt_test/resources/video/video.mp4", 10);
	ui.camera_view->start();

	connect(fixed_box, &QComboBox::currentTextChanged, this, &MainWindow::slot_fixbox_textchanged);

	connect(grid_box, &QCheckBox::clicked, this, &MainWindow::slot_gridbox_clicked);

	connect(ui.btn_quit, &QPushButton::clicked, this, &MainWindow::slot_btn_quit_clicked);
	//static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged)
	connect(cell_count_box, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::slot_cellbox_textchanged);

	connect(this->color_box, &QComboBox::currentTextChanged, this, &MainWindow::slot_colorbox_textchanged);

	connect(this->pointSize_edit, &QLineEdit::textChanged, this, &MainWindow::slot_point_size_changed);

	connect(this->tf_box, &QCheckBox::clicked, this, &MainWindow::slot_tfbox_clicked);

	connect(ui.btn_connect, &QPushButton::clicked, this, &MainWindow::slot_btn_connect_clicked);

	connect(this->laserCheckBox, &QCheckBox::clicked, this, &MainWindow::slot_laser_checkbox_clicked);

	connect(this->laserTopicBox, &QComboBox::currentTextChanged, this, &MainWindow::slot_laser_topic_changed);

	connect(this->ui.btn_start_listen, &QPushButton::clicked, this, &MainWindow::slot_btn_device_connect_clicked);

	connect(this->ui.btn_stop_listen,&QPushButton::clicked, this, &MainWindow::slot_btn_device_disconnect_clicked);

	connect(&this->socket, &QTcpSocket::connected, this, &MainWindow::slot_device_conn_success);
	connect(&this->socket, &QTcpSocket::disconnected, this, &MainWindow::slot_device_disconnected);
	connect(&this->socket, static_cast<void(QTcpSocket::*)(QTcpSocket::SocketError)>(&QTcpSocket::error), 
		this, &MainWindow::slot_device_conn_error);
	// node.init();

	ui.btn_stop_listen->setDisabled(true);

	dial_init();

	ReadSettings();
}


MainWindow::~MainWindow() {
	WriteSettings();
}

void MainWindow::dial_init(void)
{
	this->ui.x_speed_dial->setFrameShadow(QwtDial::Shadow::Raised);
	this->ui.x_speed_dial->setLineWidth(6);
	this->ui.x_speed_dial->setMode(QwtDial::Mode::RotateNeedle);
	this->ui.x_speed_dial->setScale(0, 60);
	this->ui.x_speed_dial->setScaleStepSize(5);
	this->ui.x_speed_dial->setScaleArc(0, 360);
	this->ui.x_speed_dial->setScaleMaxMajor(10);
	this->ui.x_speed_dial->setScaleMaxMinor(5);

	this->ui.y_speed_dial->setFrameShadow(QwtDial::Shadow::Raised);
	this->ui.y_speed_dial->setLineWidth(6);
	this->ui.y_speed_dial->setMode(QwtDial::Mode::RotateNeedle);
	this->ui.y_speed_dial->setScale(0, 60);
	this->ui.y_speed_dial->setScaleStepSize(5);
	this->ui.y_speed_dial->setScaleArc(0, 360);
	this->ui.y_speed_dial->setScaleMaxMajor(10);
	this->ui.y_speed_dial->setScaleMaxMinor(5);

	QwtDialSimpleNeedle *dialNeedle = new QwtDialSimpleNeedle(QwtDialSimpleNeedle::Style::Arrow,true,Qt::green,Qt::blue);
    dialNeedle->setWidth(10);

    this->ui.x_speed_dial->setNeedle(dialNeedle);
	this->ui.x_speed_dial->setValue(0);
	this->ui.y_speed_dial->setNeedle(dialNeedle);
	this->ui.y_speed_dial->setValue(0);

	ui.compass->setLineWidth(4);
	ui.compass->setFrameShadow(QwtCompass::Shadow::Raised);
	QwtCompassScaleDraw *scaleDraw = new QwtCompassScaleDraw();
    scaleDraw->enableComponent(QwtAbstractScaleDraw::Ticks,true);       // 显示刻度尺
    scaleDraw->enableComponent(QwtAbstractScaleDraw::Labels,true);      // 显示文字标签
    scaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone,false);   // 刻度尺圆环是否连续

    scaleDraw->setTickLength(QwtScaleDiv::MinorTick,0);
    scaleDraw->setTickLength(QwtScaleDiv::MediumTick,0);
    scaleDraw->setTickLength(QwtScaleDiv::MajorTick,3);
    ui.compass->setScaleDraw(scaleDraw);

	QwtCompassMagnetNeedle *compassNeedle = new QwtCompassMagnetNeedle(QwtCompassMagnetNeedle::TriangleStyle);
	this->ui.compass->setNeedle(compassNeedle);

}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/

void MainWindow::showNoMasterMessage() {
	QMessageBox msgBox;
	msgBox.setText("Couldn't find the ros master.");
	msgBox.exec();
    close();
}

/*
 * These triggers whenever the button is clicked, regardless of whether it
 * is already checked or not.
 */

/*****************************************************************************
** Implementation [Configuration]
*****************************************************************************/

void MainWindow::ReadSettings()
{
    QSettings settings("config", "qt_test");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    QString master_url = settings.value("master_url",QString("http://127.0.0.1:11311/")).toString();
    QString host_url = settings.value("host_url", QString("127.0.0.1")).toString();
    QString device_ip = settings.value("device_ip", QString("192.168.1.122")).toString();
	QString device_port = settings.value("device_port", QString("5999")).toString();

	ui.masterUrl->setText(master_url);
    ui.hostIP->setText(host_url);
	ui.sensor_IP->setText(device_ip);
	ui.sensor_port->setText(device_port);
}

void MainWindow::WriteSettings()
{
    QSettings settings("config", "qt_test");
    settings.setValue("master_url",ui.masterUrl->text());
    settings.setValue("host_url",ui.hostIP->text());
	settings.setValue("device_ip", ui.sensor_IP->text());
	settings.setValue("device_port", ui.sensor_port->text());
    //settings.setValue("topic_name",ui.line_edit_topic->text());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	WriteSettings();
	QMainWindow::closeEvent(event);
}

void MainWindow::slot_fixbox_textchanged(void)
{
	// qDebug() << "text changed";
	if (!this->m_rviz.ok()) {
		return;
	}
	this->m_rviz.setFixedFrame(fixed_box->currentText());
}

void MainWindow::slot_gridbox_clicked(void)
{
	if (!this->m_rviz.ok()) {
		return;
	}
	this->m_rviz.display_grid(this->cell_count_box->text().toInt(), this->m_color, this->grid_box->isChecked());
}

void MainWindow::slot_btn_quit_clicked(void)
{
	this->close();
}

void MainWindow::slot_cellbox_textchanged(int value)
{
	if ((!this->m_rviz.ok()) || (!this->grid_box->isChecked())) {
		return;
	}
	this->m_rviz.display_grid(value, this->m_color, this->grid_box->isChecked());
}

void MainWindow::slot_colorbox_textchanged(void)
{
	if (!this->m_rviz.ok()) {
		return;
	}
	QStringList list = this->color_box->currentText().split(";");
	if (list.count() != 3) {
		return;
	}
	this->m_color = QColor(list[0].toInt(), list[1].toInt(), list[2].toInt());
	this->m_rviz.display_grid(this->cell_count_box->text().toInt(), this->m_color, this->grid_box->isChecked());

}

void MainWindow::slot_point_size_changed(void)
{
	if (!this->m_rviz.ok()) {
		this->status_Laser->setPixmap(*pix_error);
		return;
	}
	this->status_Laser->setPixmap(*pix_ok);
	this->m_rviz.display_laser_scan(this->laserTopicBox->currentText(), this->pointSize_edit->text().toFloat(), this->laserCheckBox->isChecked());
}

void MainWindow::slot_btn_connect_clicked(void)
{
	const QString master = ui.masterUrl->text();
	const QString host = ui.hostIP->text();

	bool res = node->init(master.toStdString(), host.toStdString());

	if (!res) {
		qDebug() << "master connect fail";
		QMessageBox msg;
		msg.setWindowTitle("ERROR");
		// msg.setIcon()
		msg.setText("could not find the ros master");
		msg.exec();

	} else {
		// m_rviz = new QRviz(ui.render_layout);
		//connect(fixed_box, &QComboBox::currentTextChanged, m_rviz, &QRviz::setFixedFrame);
		this->m_rviz.init(ui.render_layout);
		this->is_Connect = true;
		this->ui.btn_connect->setDisabled(true);
		this->ui.hostIP->setDisabled(true);
		this->ui.masterUrl->setDisabled(true);

		this->m_rviz.display_grid(this->cell_count_box->text().toInt(), this->m_color, this->grid_box->isChecked());
	}
}

void MainWindow::slot_tfbox_clicked(void)
{
	if (!this->m_rviz.ok()) {
		return;
	}
	this->m_rviz.display_tf(this->tf_box->isChecked());
}

void MainWindow::slot_laser_checkbox_clicked(void)
{
	if (!this->m_rviz.ok()) {
		this->status_Laser->setPixmap(*pix_error);
		return;
	}
	this->status_Laser->setPixmap(*pix_ok);
	this->m_rviz.display_laser_scan(this->laserTopicBox->currentText(), this->pointSize_edit->text().toFloat(), this->laserCheckBox->isChecked());
}

void MainWindow::slot_laser_topic_changed(void)
{
	if (!this->m_rviz.ok()) {

		return;
	}
	this->m_rviz.display_laser_scan(this->laserTopicBox->currentText(), this->pointSize_edit->text().toFloat(), this->laserCheckBox->isChecked());
}

void MainWindow::slot_btn_device_connect_clicked(void)
{
	if (connstate == CONNECTED) {
		return;
	}

	QString ip = ui.sensor_IP->text();
	QString port = ui.sensor_port->text();

	socket.connectToHost(ip, port.toInt());
	
	connstate = CONNECTING;
	ui.btn_start_listen->setText("连接中");
	ui.btn_start_listen->setDisabled(true);

	ui.btn_stop_listen->setText("取消连接");
	ui.btn_stop_listen->setDisabled(false);
}

void MainWindow::slot_btn_device_disconnect_clicked(void)
{
	if (connstate == CONNECTING) {
		qDebug() << "connecting";
		socket.close();
	} else if (connstate == CONNECTED) {
		qDebug() << "connected";
		socket.close();
	}
}

void MainWindow::slot_gps_info_update(const GPSInfo* info)
{
	if (!info) {
	}
}

void MainWindow::slot_device_receive(void)
{
	QByteArray data = socket.readAll();
	size_t size = data.size();
	const GPSInfo* info = parser.parse((const uint8_t*)data.data(), size);
	if (info) {
		slot_gps_info_update(info);
	}
}

void MainWindow::slot_device_conn_success(void)
{
	connstate = CONNECTED;
	ui.sensor_IP->setDisabled(true);
	ui.sensor_port->setDisabled(true);
	ui.btn_start_listen->setDisabled(true);
	ui.btn_stop_listen->setDisabled(false);
	ui.btn_start_listen->setText("连接");
	ui.btn_stop_listen->setText("断开");

	socket.write("hello, this qt");
}

void MainWindow::slot_device_disconnected(void)
{
	connstate = DISCONNECTED;
	ui.sensor_IP->setDisabled(false);
	ui.sensor_port->setDisabled(false);
	ui.btn_start_listen->setDisabled(false);
	ui.btn_stop_listen->setDisabled(true);
	ui.btn_start_listen->setText("连接");
	ui.btn_stop_listen->setText("断开");
}

void MainWindow::slot_device_conn_error(QTcpSocket::SocketError error)
{
	connstate = DISCONNECTED;
	ui.sensor_IP->setDisabled(false);
	ui.sensor_port->setDisabled(false);
	ui.btn_start_listen->setDisabled(false);
	ui.btn_start_listen->setText("连接");
	ui.btn_stop_listen->setDisabled(true);
	ui.btn_stop_listen->setText("断开");
}

}  // namespace qt_test


