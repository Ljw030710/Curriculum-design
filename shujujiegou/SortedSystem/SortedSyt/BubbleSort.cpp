#include "BubbleSort.h"
#include <algorithm>
#include <cmath>
#include <QtMath>
#include <QTime>
#include <QPainter>
#include <QPaintEvent>
#include <QScopeGuard>
#include <QFontMetrics>
#include <QDebug>
#include<random>
BubbleSort::BubbleSort(QObject *parent)
    : SortObject(parent)
{
    //属性动画控制交换动画效果
   //动画的开始的值
    animation.setStartValue(0.0);
    //结束时的值
    animation.setEndValue(1.0);
    //设置动画的缓动曲线
    animation.setEasingCurve(QEasingCurve::OutQuart);
    //设置动画的循环次数
    animation.setLoopCount(1);
    //连接quit槽，当动画结束时事件循环将退出
    connect(&animation, &QVariantAnimation::finished, &loop, &QEventLoop::quit);
    //将动画改变时会触发updateRequest信号
    connect(&animation, &QVariantAnimation::valueChanged, this, &SortObject::updateRequest);
}


void BubbleSort::stop()
{
    //将运行状态设置为还没有运行
    setRunFlag(false);
    //动画停止
    animation.stop();
    //退出事件循环
    loop.quit();
    //发出信号，更新信息
    emit updateRequest();
}

void BubbleSort::initArr(int count)
{

    if (count < 2) {
        return;
    }

    //初始化并随机打乱数据
    arr.resize(count);
    for (int i = 0; i < count; i++)
    {
        arr[i] = i + 1;
    }
    //随机
    //由于random_shuffle用不了的替代方法
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(arr.begin(),arr.end(),g);


    arrI = 0;
    arrJ = 0;
    swapFlag = false;
    emit updateRequest();
}

void BubbleSort::sort(int count, int interval)
{
    //如果是false就更新请求
    auto guard = qScopeGuard([this]{
        setRunFlag(false);
        emit updateRequest();
    });
    Q_UNUSED(guard)
    //初始化
    stop();
    initArr(count);
    setRunFlag(true);

    int len = arr.length();
    for (arrI = 0; arrI < len - 1; arrI++)
    {   //内层循环，从数组开始到未排序的部分结束
        for (arrJ = 0; arrJ < len - 1 - arrI; arrJ++)
        {   //如果当前的元素大于下一个元素，说明就要进行交换
            if (arr[arrJ] > arr[arrJ + 1]) {
                //延长动漫的时间
                animation.setDuration(interval * 3);
                animation.start();
                swapFlag = true;
                //进入事件循环，等待动画播放完毕
                loop.exec();
                //如果排序没有停止
                if (getRunFlag()) {
                    //进行交换
                    qSwap(arr[arrJ], arr[arrJ + 1]);
                    swapFlag = false;
                }
            } else {
                //不需要交换
                animation.setDuration(interval);
                animation.start();
                loop.exec();
            }
            //重新更新请求信号
            emit updateRequest();
            //如果排序停止就返回
            if (!getRunFlag()) {
                return;
            }
        }
        if (!getRunFlag()) {
            return;
        }
    }
}
//绘制图像
// 冒泡排序的绘制函数
void BubbleSort::draw(QPainter *painter, int width, int height)
{
    const int len = arr.length(); // 获取数组长度
    painter->setPen(QColor(200,200,200)); // 设置画笔颜色为灰色

    // 设置各种距离参数
    const int left_space = 0;
    const int right_space = 0;
    const int top_space = 20;
    const int bottom_space = 50;
    const int item_space = 10; // 柱子之间的间隔距离
    const int text_height = painter->fontMetrics().height(); // 获取字体的高度
    const int text_space = 15; // 文本和柱子之间的间隔

    // 计算每个柱子的宽度和底部位置
    const double item_width = (width+item_space-left_space-right_space)/(double)len-item_space;
    const double item_bottom = height-bottom_space;
    const double height_factor = (height-top_space-bottom_space)/(double)len;

    double item_left = 0;
    double item_height = 0;
    QColor color;

    // 遍历数组，为每个元素绘制一个柱子
    for(int i = 0;i<len;i++){
        item_left = left_space+i*(item_width+item_space);
        item_height = height_factor*arr.at(i); // 计算柱子高度
        color = QColor(200,200,200); // 默认颜色为灰色

        // 如果正在排序，根据不同的情况设置柱子的颜色
        if(getRunFlag()){
            if(i==arrJ){
                color = QColor(0,170,255); // 如果是正在比较的元素，设置为蓝色
                if(swapFlag){
                    // 如果正在交换，根据动画的当前值移动柱子的位置
                    item_left += animation.currentValue().toDouble()*(item_width+item_space);
                }
            }
            else if(i==arrJ+1){
                color = QColor(0,170,255); // 如果是正在比较的元素，设置为蓝色
                if(swapFlag){
                    // 如果正在交换，根据动画的当前值移动柱子的位置
                    item_left -= animation.currentValue().toDouble()*(item_width+item_space);
                }
            }
            else if(i>=len-arrI){
                color = QColor(0,170,0); // 如果元素已经排序完成，设置为绿色
            }
        }

        // 绘制元素值的文本
        painter->drawText(item_left,item_bottom+text_height+text_space,QString::number(arr.at(i)));
        // 绘制柱子
        painter->fillRect(item_left,item_bottom-item_height,item_width,item_height,color);
    }
}
