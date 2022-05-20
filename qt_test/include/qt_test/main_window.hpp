/**
 * @file /include/qt_test/main_window.hpp
 *
 * @brief Qt based gui for qt_test.
 *
 * @date November 2010
 **/
#ifndef qt_test_MAIN_WINDOW_H
#define qt_test_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtWidgets/QMainWindow>
#include <QCheckBox>
#include "ui_main_window.h"
#include "../ROSNode.hpp"
#include "QRviz.h"
#include "decoder/GPSParser.h"

#include <QComboBox>
#include <QLabel>
#include <QSpinBox>
#include <QTcpSocket>
#include <QTcpServer>

#define vtkRenderingCore_AUTOINIT 2(vtkRenderingOpenGL2, vtkInteractionStyle)

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace qt_test {

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	~MainWindow();

	/**
	 * @brief 加载配置
	 * 
	 */
	void ReadSettings(); // Load up qt program settings at startup

	/**
	 * @brief 写入配置
	 * 
	 */
	void WriteSettings(); // Save qt program settings when closing

	/**
	 * @brief 关闭事件
	 * 
	 * @param event 
	 */
	void closeEvent(QCloseEvent *event); // Overloaded function
	void showNoMasterMessage();

	/**
	 * @brief 速度计, 电子罗盘初始化
	 * 
	 */
	void dial_init(void);

private slots:

	/**
	 * @brief rviz配置页面相关槽函数
	 * 
	 */
	void slot_fixbox_textchanged(void);
	void slot_gridbox_clicked(void);
	void slot_btn_quit_clicked(void);
	void slot_cellbox_textchanged(int);
	void slot_colorbox_textchanged(void);
	void slot_btn_connect_clicked(void);
	void slot_tfbox_clicked(void);
	void slot_laser_checkbox_clicked(void);
	void slot_laser_topic_changed(void);
	void slot_point_size_changed(void);
	/******************************************
	** Auto-connections (connectSlotsByName())
	*******************************************/

	/**
	 * @brief 下位机连接按钮按下事件槽函数
	 * 
	 */
	void slot_btn_device_connect_clicked(void);

	/**
	 * @brief 下位机断开连接按钮按下事件槽函数
	 * 
	 */
	void slot_btn_device_disconnect_clicked(void);

	/**
	 * @brief GPS信息更新槽函数
	 * 
	 * @param info 
	 */
	void slot_gps_info_update(const GPSInfo* info);

	/**
	 * @brief 接收到下位机数据的回调
	 * 
	 */
	void slot_device_receive();

	/**
	 * @brief 下位机连接成功
	 * 
	 */
	void slot_device_conn_success(void);

	/**
	 * @brief 下位机断开连接
	 * 
	 */
	void slot_device_disconnected(void);

	/**
	 * @brief 连接发生错误
	 * 
	 * @param error 
	 */
	void slot_device_conn_error(QTcpSocket::SocketError error);

private:

	enum ConnectState{
		DISCONNECTED = 0x0,	//断开连接
		CONNECTING,			//连接中
		CONNECTED			//已连接
	};

	Ui::MainWindowDesign ui;
	RNode *node = nullptr;					//ROS结点, 处理ros相关数据
	QRviz m_rviz;							//rviz界面, 显示点云信息

	bool is_Connect = false;				//是否连接上ros master

	ConnectState connstate = DISCONNECTED;	//是否与下位机连接状态

	/**
	 * @brief UI界面
	 * 
	 */
	QComboBox *fixed_box = nullptr;
	QCheckBox *grid_box = nullptr;
	QCheckBox *tf_box = nullptr;
	QSpinBox *cell_count_box = nullptr;
	QComboBox *color_box = nullptr;
	QCheckBox *laserCheckBox = nullptr;
	QComboBox *laserTopicBox = nullptr;
	QLineEdit *pointSize_edit = nullptr;
	QLabel *status_Laser = nullptr;
	QColor m_color = Qt::gray;
	QPixmap *pix_error = nullptr;
	QPixmap *pix_ok = nullptr;

	QCheckBox *map_box = nullptr;

	QTcpSocket socket;

	GPSParser parser;
};

}  // namespace qt_test

#endif // qt_test_MAIN_WINDOW_H
