#include "videoview.h"
#include <QPainter>
#include <QImage>

VideoView::VideoView(QWidget *parent) : QWidget(parent)
{

}

void VideoView::paintEvent(QPaintEvent *event)
{
    /* the painter */
    QPainter painter(this);

    /* transform OpenCV Image to Qt Image */
    QImage image1 = QImage((uchar*)(m_src_frame.data), m_src_frame.cols, m_src_frame.rows, QImage::Format_RGB888);
    
    /* define the range of the image */
    QRect source(0, 0, image1.width(), image1.height());

    painter.save();

    painter.translate(QPointF(width() / 2.0, height() / 2.0));

    /* calclate the rate of source image & show image*/
    float rate1 = width() / (height() * 1.0);
    float rate2 = image1.width() / (image1.height() * 1.0);

    float dst_width;
    float dst_height;

    if (rate1 > rate2) {
        dst_height = height();
        dst_width = rate2 * dst_height;
    } else if (rate1 < rate2){
        dst_width = width();
        dst_height = dst_width / rate2;
    } else if (rate1 == rate2) {
        dst_height = height();
        dst_width = width();
    }
    /* define the range of the show widget */
    QRect dst(QPoint(- dst_width / 2.0, - dst_height / 2.0), QPoint(dst_width / 2.0, dst_height / 2.0));
    painter.drawImage(dst, image1, source);

    painter.restore();

}

bool VideoView::init(QString video_path, int freq)
{
    if (m_isInit) {
        emit initFailed();
        return false;
    }

    m_cap = new cv::VideoCapture(video_path.toStdString());

    if (!m_cap->isOpened()) {
        emit initFailed();
        emit openVideoFailed();
        m_cap = nullptr;
        return false;
    }

    m_isInit = true;

    m_timer = new QTimer(this);
    m_timer->setInterval(1000 / freq);

    frameInit();

    connect(m_timer, &QTimer::timeout, this, &VideoView::slot_timer_timout);

    return true;
}

bool VideoView::init(int camera, int freq)
{
    if (m_isInit) {
        emit initFailed();
        return false;
    }

    m_cap = new cv::VideoCapture(camera);

    if (!m_cap->isOpened()) {
        m_cap = nullptr;
        emit initFailed();
        emit openCameraFailed();
        return false;
    }

    m_isInit = true;

    m_timer = new QTimer(this);
    m_timer->setInterval(1000 / freq);

    frameInit();

    connect(m_timer, &QTimer::timeout, this, &VideoView::slot_timer_timout);

    return true;
}

void VideoView::start(void)
{
    if (!m_isInit || nullptr == m_timer) {
        return;
    }

    m_timer->start();
}

void VideoView::frameInit(void)
{
    m_src_frame = cv::Mat::zeros(m_cap->get(4), m_cap->get(3), CV_8UC3);
    m_show_frame = cv::Mat::zeros(height(), width(), CV_8UC3);
}

void VideoView::slot_timer_timout(void)
{
    *m_cap >> m_src_frame;
    if (m_src_frame.data) {
        cv::cvtColor(m_src_frame, m_src_frame, 4);
        // cv::resize(m_src_frame, m_show_frame, m_show_frame.size());
        // cv::resize(m_src_frame, m_show_frame, cv::Size(width(), height()));
        this->update();
    }
}