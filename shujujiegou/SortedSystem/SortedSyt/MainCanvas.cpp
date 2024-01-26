#include "MainCanvas.h"
#include <QPaintEvent>
#include <QPainter>

MainCanvas::MainCanvas(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground, true);
}

// 获取当前的排序类型
int MainCanvas::getSortType() const
{
    return sortType;
}

// 设置排序对象
void MainCanvas::setSortObject(int type, SortObject *obj)
{
    // 如果类型相同，直接返回
    if (sortType == type) {
        return;
    }
    // 删除旧的排序对象
    if (sortObj) {
        sortObj->deleteLater();
        sortObj = nullptr;
    }

    // 设置新的排序类型和对象
    sortType = type;
    sortObj = obj;

    // 如果排序对象存在，连接其更新请求和运行标志改变的信号到相应的槽
    if (sortObj) {
        connect(sortObj, &SortObject::updateRequest, this, [this]{
            update();
        });
        connect(sortObj, &SortObject::runFlagChanged, this, &MainCanvas::runFlagChanged);
    }
    // 更新画布
    update();
}

// 执行排序
void MainCanvas::sort(int count, int interval)
{
    if (sortObj) {
        sortObj->sort(count, interval);
    }
}

// 停止排序
void MainCanvas::stop()
{
    if (sortObj) {
        sortObj->stop();
    }
}

// 画布的绘制事件
void MainCanvas::paintEvent(QPaintEvent *event)
{
    event->accept();

    QPainter painter(this);
    // 填充画布背景为深色
    painter.fillRect(rect(),QColor(20,20,20));

    // 如果排序对象存在，调用其绘制函数
    if (sortObj) {
        sortObj->draw(&painter, width(), height());
    }
}
