#include "SelectionSort.h".h"
#include <algorithm>
#include <cmath>
#include <QtMath>
#include <QTime>
#include <QPainter>
#include <QPaintEvent>
#include <QScopeGuard>
#include <QFontMetrics>
#include <QDebug>
#include<QPainterPath>
#include<random>

SelectionSort::SelectionSort(QObject *parent)
    : SortObject(parent)
{
    //属性动画控制交换动画效果
    animation.setStartValue(0.0);
    animation.setEndValue(1.0);
    animation.setEasingCurve(QEasingCurve::OutQuart);
    animation.setLoopCount(1);
    connect(&animation, &QVariantAnimation::finished, &loop, &QEventLoop::quit);
    connect(&animation, &QVariantAnimation::valueChanged, this, &SortObject::updateRequest);
}

void SelectionSort::stop(){
    setRunFlag(false);
    animation.stop();
    loop.quit();
    emit updateRequest();
}

void SelectionSort:: initArr(int count){
    if (count < 2) {
        return;
    }

    //初始化并随机打乱数据
    arr.resize(count);
    for (int i = 0; i < count; i++)
    {
        arr[i] = i + 1;
    }
    //由于random_shuffle用不了的替代方法
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(arr.begin(),arr.end(),g);


    arrI = 0;
    arrJ = 0;
    arrMin = 0;
    swapFlag = false;
    emit updateRequest();
}

void SelectionSort::draw(QPainter *painter, int width, int height)
{
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
    for (int i = 0; i < len; i++)
    {
        //色块位置x
        item_left = left_space + i * (item_width + item_space);
        item_height = height_factor * arr.at(i);
        //色块颜色
        color = QColor(200, 200, 200);
        //在执行排序操作的时候标记比较的两个元素
        if (getRunFlag()) {
            if (i == arrI) {
                color = QColor(255, 170 , 0);
                if (swapFlag) {
                    item_left += animation.currentValue().toDouble() *
                                 (arrMin - arrI) * (item_width + item_space);
                }
            } else if (i == arrJ) {
                color = QColor(0, 170 , 255);
            } else if (i < arrI) {
                //已排序好的
                color = QColor(0, 170, 0);
            }
            //最小这个数可能和i j重合，所以单独判断
            if (i == arrMin) {
                if (swapFlag) {
                    item_left -= animation.currentValue().toDouble() *
                                 (arrMin - arrI) * (item_width + item_space);
                }
                //标记最小的数，在下方画一个三角
                //painter->drawText(item_left, item_bottom + text_height * 2 + text_space, "Min");
                //记录min的下标值
                const double min_top = item_bottom + text_height + text_space * 2;
                QPainterPath m_path;
                m_path.moveTo(item_left + item_width / 2.0, min_top);
                m_path.lineTo(item_left, min_top + item_width / 2.0);
                m_path.lineTo(item_left + item_width, min_top + item_width / 2.0);
                m_path.lineTo(item_left + item_width / 2.0, min_top);
                painter->fillPath(m_path, QColor(0, 255, 0));
            }
        }
        //画文字
        painter->drawText(item_left, item_bottom + text_height + text_space,
                          QString::number(arr.at(i)));
        //画色块柱子
        painter->fillRect(item_left, item_bottom - item_height,
                          item_width, item_height,
                          color);
    }
}

// 选择排序
void SelectionSort::sort(int count, int interval){
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
    // 外层循环：遍历每一个位置
    for (arrI = 0; arrI < len - 1; arrI++)
    {
        // 记录当前位置为最小值位置
        arrMin = arrI;
        // 内层循环：找到剩余部分的最小值
        for (arrJ = arrI + 1; arrJ < len; arrJ++)
        {
            // 如果找到更小的值，更新最小值位置
            if (arr[arrJ] < arr[arrMin]) {
                arrMin = arrJ;
            }
            // 更新动画和界面
            animation.setDuration(interval);
            animation.start();
            loop.exec();
            emit updateRequest();
            // 如果排序被中断，直接返回
            if (!getRunFlag()) {
                return;
            }
        }
        // 如果当前位置不是最小值，交换两者
        if (arrI != arrMin) {
            animation.setDuration(interval * 3);
            animation.start();
            swapFlag = true;
            loop.exec();
            if (getRunFlag()) {
                qSwap(arr[arrI], arr[arrMin]);
                swapFlag = false;
            }
        }
        // 如果排序被中断，直接返回
        if (!getRunFlag()) {
            return;
        }
    }
}
