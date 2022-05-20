#include "QRviz.h"
#include <QDebug>

QRviz::QRviz(QObject *parent) : QObject(parent)
{
    //m_manager->createDisplay()
}

QRviz::~QRviz()
{

}

void QRviz::setFixedFrame(QString frameName)
{
    qDebug() << frameName;
    m_manager->setFixedFrame(frameName);
}

bool QRviz::init(QVBoxLayout *layout)
{
    if (nullptr == layout) {
        return false;
    }
    //创建rviz
    m_render_panel = new rviz::RenderPanel();

    //向layout添加
    layout->addWidget(m_render_panel);

    //rviz控制对象
    m_manager = new rviz::VisualizationManager(m_render_panel);

    ROS_ASSERT(m_manager!=NULL);

    m_tool_manager = m_manager->getToolManager();

    m_render_panel->initialize(m_manager->getSceneManager(), m_manager);

    m_manager->setFixedFrame("map");

    m_manager->initialize();
    m_manager->startUpdate();
    m_manager->removeAllDisplays();

    m_grid = nullptr;

    is_init = true;
    return true;
}

bool QRviz::ok()
{
    return is_init;
}

bool QRviz::display_grid(int Cell_Count, QColor color, bool enable)
{
    if(m_grid != nullptr)
    {
        delete m_grid;
        m_grid = nullptr;
    }

    m_grid = m_manager->createDisplay("rviz/Grid","myGrid",enable);
    //设置cell Count
    m_grid->subProp("Plane Cell Count")->setValue(Cell_Count);
    //设置颜色
    m_grid->subProp("Color")->setValue(color);
    ROS_ASSERT(m_grid!=nullptr);
    return true;
}

bool QRviz::display_tf(bool enable)
{
    if (m_tf != nullptr) {
        delete m_tf;
        m_tf = nullptr;
    }

    m_tf = m_manager->createDisplay("rviz/TF", "myTF", enable);
    ROS_ASSERT(m_tf != nullptr);
    return true;
}

bool QRviz::display_laser_scan(QString laser_topic, float point_size, bool enable)
{
    if(m_laser != nullptr)
    {
        delete m_laser;
        m_laser = nullptr;
    }
    m_laser = m_manager->createDisplay("rviz/LaserScan","myLaser",enable);
    m_laser->subProp("Topic")->setValue(laser_topic);
    m_laser->subProp("Size (m)")->setValue(point_size);
    ROS_ASSERT(m_laser!=nullptr);
    return true;
}

bool QRviz::display_map(QString map_topic, bool enable)
{
    if(m_map != nullptr)
    {
        delete m_map;
        m_map = nullptr;
    }

    m_map = m_manager->createDisplay("rviz/Map", "myMap", enable);
    m_map->subProp("Topic")->setValue(map_topic);

    ROS_ASSERT(m_map!=nullptr);
    return true;
}