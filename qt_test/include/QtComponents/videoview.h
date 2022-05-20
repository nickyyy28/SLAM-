#ifndef __VIDEOVIEW_H
#define __VIDEOVIEW_H

#include <QWidget>
#include <QTimer>
#include <QString>
#include <QPaintEvent>
#include <opencv2/opencv.hpp>

class VideoView : public QWidget
{
    Q_OBJECT
public:
    explicit VideoView(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

    bool init(QString video_path, int freq = 30);
    bool init(int camera, int freq = 30);
    void start(void);


private:
    bool m_isInit{false};
    cv::Mat m_src_frame;
    cv::Mat m_show_frame;
    cv::VideoCapture *m_cap{nullptr};
    QTimer *m_timer{nullptr};
    
    void frameInit(void);

signals:
    void initFailed();
    void openCameraFailed();
    void openVideoFailed();
private slots:
    void slot_timer_timout(void);

};

#endif //__VIDEOVIEW_H