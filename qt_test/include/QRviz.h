#ifndef __QRVIZ_H
#define __QRVIZ_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>

#include <rviz/visualization_manager.h>
#include <rviz/render_panel.h>
#include <rviz/display.h>
#include <rviz/tool_manager.h>
#include <rviz/tool.h>

class QRviz : public QObject {
    Q_OBJECT
public:
    QRviz(QObject *parent = nullptr);
    ~QRviz();

    void setFixedFrame(QString frameName);
    bool ok();
    bool init(QVBoxLayout *layout);

    /**
     * @brief 显示网格
     * 
     * @param Cell_Count    网格数量
     * @param color         网格颜色
     * @param enable        是否显示
     * @return true 
     * @return false 
     */
    bool display_grid(int Cell_Count, QColor color, bool enable);

    /**
     * @brief 显示tf坐标变换
     * 
     * @param enable        是否显示
     * @return true 
     * @return false 
     */
    bool display_tf(bool enable);

    /**
     * @brief 显示激光雷达扫描
     * 
     * @param laser_topic 
     * @param point_size 
     * @param enable 
     * @return true 
     * @return false 
     */
    bool display_laser_scan(QString laser_topic, float point_size, bool enable);

    /**
     * @brief 显示构建的地图
     * 
     * @param map_topic 地图话题名称
     * @param enable    是否显示
     * @return true 
     * @return false 
     */
    bool display_map(QString map_topic, bool enable);

private:

    bool is_init = false;

    rviz::RenderPanel* m_render_panel;
    rviz::VisualizationManager * m_manager;
    rviz::ToolManager* m_tool_manager;

    rviz::Display *m_grid = nullptr;
    rviz::Display *m_tf = nullptr;
    rviz::Display *m_laser = nullptr;
    rviz::Display *m_model = nullptr;
    rviz::Display *m_map = nullptr;
    rviz::Display *m_pointCloud = nullptr;
};


#endif //__QRVIZ_H