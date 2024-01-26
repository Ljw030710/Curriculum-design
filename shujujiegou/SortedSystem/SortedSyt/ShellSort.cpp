#include "ShellSort.h"
#include <algorithm>
#include <cmath>
#include <QtMath>
#include <QTime>
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QScopeGuard>
#include <QFontMetrics>
#include <QDebug>
#include<random>
ShellSort::ShellSort(QObject *parent)
    : SortObject(parent)
{
    //属性动画控制交换动画效果
    //animation.setDuration(2000);
    animation.setStartValue(0.0);
    animation.setEndValue(1.0);
    animation.setEasingCurve(QEasingCurve::OutQuart);
    animation.setLoopCount(1);
    connect(&animation, &QVariantAnimation::finished, &loop, &QEventLoop::quit);
    connect(&animation, &QVariantAnimation::valueChanged, this, &SortObject::updateRequest);
}

void ShellSort::stop()
{
    setRunFlag(false);
    animation.stop();
    loop.quit();
    emit updateRequest();
}

void ShellSort::initArr(int count)
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
    //std::random_shuffle(arr.begin(), arr.end());
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(arr.begin(),arr.end(),g);
    arrI = 0;
    arrJ = 0;
    arrGap = 0;
    swapFlag = false;
    emit updateRequest();
}

/*希尔排序
template<typename T>
void shell_sort(std::vector<T>& arr)
{
    for (int gap = arr.size() / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < arr.size(); i++) {
            int j = i;
            while (j - gap >= 0 && arr[j] < arr[j - gap]) {
                std::swap(arr[j], arr[j - gap]);
                j -= gap;
            }
        }
    }
}*/
// 希尔排序
void ShellSort::sort(int count,int interval){
    // 如果排序被中断，设置运行标志为false，并发出更新请求
    auto guard = qScopeGuard([this]{
        setRunFlag(false);
        emit updateRequest();
    });
    Q_UNUSED(guard)

    // 停止当前的排序
    stop();
    // 初始化数组
    initArr(count);
    // 设置运行标志为true
    setRunFlag(true);

    int len = arr.length();
    // 外层循环：改变间隔值
    for(arrGap = len/2;arrGap>0;arrGap/=2){
        // 内层循环：对每个子序列进行插入排序
        for(arrI = arrGap;arrI<len;arrI++){
            arrJ = arrI;
            // 更新动画和界面
            animation.setDuration(interval);
            animation.start();
            loop.exec();
            emit updateRequest();
            // 如果排序被中断，直接返回
            if(!getRunFlag()){
                return;
            }
            // 如果当前元素小于间隔位置的元素，交换两者
            while(arrJ-arrGap>=0&&arr[arrJ]<arr[arrJ-arrGap]){
                animation.setDuration(interval*3);
                animation.start();
                swapFlag = true;
                loop.exec();
                if(getRunFlag()){
                    qSwap(arr[arrJ],arr[arrJ-arrGap]);
                    swapFlag = false;
                }
                // 如果排序被中断，直接返回
                if(!getRunFlag()){
                    return;
                }

                arrJ -= arrGap;
                // 更新动画和界面
                animation.setDuration(interval);
                animation.start();
                loop.exec();
                emit updateRequest();
                // 如果排序被中断，直接返回
                if(!getRunFlag()){
                    return;
                }
            }
            // 如果排序被中断，直接返回
            if(!getRunFlag()){
                return;
            }
        }
        // 如果排序被中断，直接返回
        if(!getRunFlag()){
            return;
        }
    }
}
void ShellSort::draw(QPainter *painter, int width, int height){
    painter->setPen(QColor(200, 200, 200));
    const int len = arr.length();
    //边框距离
    const int left_space = 0;
    const int right_space = 0;
    const int top_space = 20;
    const int bottom_space = 60;

    const int item_space = 10; //柱子横项间隔
    const int text_height = painter->fontMetrics().height();
    const int text_space = 15; //文字和柱子间隔
    const double item_width = (width + item_space - left_space - right_space) / (double)len - item_space;
    const double item_bottom = height - bottom_space;
    const double height_factor = (height - top_space - bottom_space) / (double)len;
    double item_left = 0;
    double item_height = 0;
    QColor color;
    for(int i = 0;i<len;i++){
        item_left = left_space + i * (item_width + item_space);
        item_height = height_factor * arr.at(i);
        //色块颜色
        color = QColor(200, 200, 200);
        if(getRunFlag()){
            int offset = animation.currentValue().toDouble()*arrGap*(item_width+item_space);
            if(i<arrI&&i%arrGap==arrI%arrGap){
                color = QColor(0,170,255);
                if(swapFlag){
                    item_left+=offset;
                }
            }
            else if(i==arrJ){
                color = QColor(0,170,255);
                if(swapFlag){
                    item_left = offset;
                }
            }
        }
        painter->drawText(item_left,item_bottom+text_height+text_space,QString::number(arr.at(i)));
        //画色块柱子
        painter->fillRect(item_left,item_bottom-item_height,item_width,item_height,color);
    }
}
