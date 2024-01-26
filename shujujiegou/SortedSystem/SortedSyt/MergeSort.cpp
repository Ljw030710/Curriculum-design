#include "MergeSort.h"
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

MergeSort::MergeSort(QObject *parent)
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

void MergeSort::initArr(int count)
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

    mergeFlag = false;
    emit updateRequest();
}

void MergeSort::stop(){
    setRunFlag(false);
    animation.stop();
    loop.quit();
    emit updateRequest();
}

void MergeSort::sort(int count,int interval){
    auto guard = qScopeGuard([this]{
        setRunFlag(false);
        emit updateRequest();
    });
    Q_UNUSED(guard)

    stop();
    initArr(count);
    setRunFlag(true);

    this->interval = interval;
    doSort(0, arr.size()-1);
}

void MergeSort::wait(int ms){
    animation.setDuration(ms);
    animation.start();
    loop.exec();
}

/*
 * template<typename T>
void merge(std::vector<T>& arr, int low, int mid, int high)
{
    std::vector<T> temp(high - low + 1);
    int i = low, j = mid + 1, k = 0;
    while (i <= mid && j <= high) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= high) {
        temp[k++] = arr[j++];
    }
    for (i = low, k = 0; i <= high;) {
        arr[i++] = temp[k++];
    }
}

template<typename T>
void merge_sort(std::vector<T>& arr, int low, int high)
{
    if (low >= high) {
        return;
    }
    int mid = low + (high - low) / 2;
    merge_sort(arr, low, mid);
    merge_sort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}
*/
// merge函数用于合并两个已排序的子序列
void MergeSort::merge(int low, int mid, int high){
    // 设置动画的持续时间
    animation.setDuration(interval*3);
    // 开始动画
    animation.start();
    // 设置合并标志为true，表示正在进行合并
    mergeFlag = true;
    // 记录合并的范围
    mergeBegin = low;
    mergeEnd = high;
    // 进入事件循环，等待动画完成
    loop.exec();
    // 如果运行标志为true，表示排序没有被中断，可以进行合并
    if(getRunFlag()){
        // 创建临时数组，用于存储合并后的结果
        std::vector<int> temp(high - low + 1);
        // i和j分别指向两个子序列的开始，k指向临时数组的开始
        int i = low, j = mid + 1, k = 0;
        // 合并两个子序列
        while (i <= mid && j <= high) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }
        // 如果左边的子序列还有剩余，将其复制到临时数组
        while (i <= mid) {
            temp[k++] = arr[i++];
        }
        // 如果右边的子序列还有剩余，将其复制到临时数组
        while (j <= high) {
            temp[k++] = arr[j++];
        }
        // 将临时数组的内容复制回原数组
        for (i = low, k = 0; i <= high;) {
            arr[i++] = temp[k++];
        }
        // 设置合并标志为false，表示合并已完成
        mergeFlag = false;
    }
}

// doSort函数用于进行归并排序
void MergeSort::doSort(int low, int high){
    // 如果low大于等于high，说明排序已完成，直接返回
    if(low>=high){
        return;
    }
    // 初始化排序范围和当前处理的范围
    rangeBegin = low;
    rangeEnd = high;
    curBegin = low;
    curEnd = high;
    // 选择基准元素
    posIndex = curBegin;
    posValue = arr[posIndex];
    // 等待一段时间
    wait(interval);
    // 如果运行标志为false，表示排序被中断，直接返回
    if(!getRunFlag()){
        return;
    }
    // 计算中点
    int mid = low + (high - low) / 2;
    // 递归地对左边的子序列进行排序
    doSort(low, mid);
    if(!getRunFlag()){
        return;
    }
    // 递归地对右边的子序列进行排序
    doSort(mid + 1, high);
    if(!getRunFlag()){
        return;
    }
    // 合并两个已排序的子序列
    merge(low, mid, high);
    if(!getRunFlag()){
        return;
    }
    // 发出更新请求
    emit updateRequest();
}
void MergeSort::draw(QPainter *painter, int width, int height){
    painter->setPen(QColor(200, 200, 200));
    const int len = arr.length();
    const int left_space = 0;
    const int right_space = 0;
    const int top_space = 30;
    const int bottom_space = 90;

    const int item_space = 10;
    const int text_height = painter->fontMetrics().height();
    const int text_space = 15;
    const double item_width = (width + item_space - left_space - right_space) / (double)len - item_space;
    const double item_bottom = height - bottom_space;
    const double height_factor = (height - top_space - bottom_space) / (double)len;
    double bottom_offset = 0;
    double item_left = 0;
    double item_height = 0;
    QColor color;
    QString text;
    for (int i = 0; i < len; i++)
    {
        item_left = left_space + i * (item_width + item_space);
        item_height = height_factor * arr.at(i);
        bottom_offset = 0;
        color = QColor(200, 200, 200);
        text = QString::number(arr.at(i));
        if (getRunFlag()) {
            if (i >= rangeBegin && i <= rangeEnd) {
                color = QColor(0, 170, 255);
            }
            if (mergeFlag && i >= mergeBegin && i <= mergeEnd) {
                color = QColor(255, 170, 0);
            }
        }
        painter->drawText(item_left, item_bottom + text_height + text_space, text);
        painter->fillRect(item_left, item_bottom - item_height - bottom_offset,
                          item_width, item_height,
                          color);
    }

    if (getRunFlag()) {
        const int level = rangeStack.size() > 6 ? rangeStack.size() - 6 : 0;
        int y_pos = height - 5;
        for (int i = level; i < rangeStack.size(); i++, y_pos -= 5)
        {
            QPair<int, int> range = rangeStack.at(i);
            int begin_Left = left_space + range.first * (item_width + item_space);
            int end_right = left_space + range.second * (item_width + item_space) + item_width;
            painter->drawLine(begin_Left, y_pos, end_right, y_pos);
        }
    }

    painter->fillRect(10, 12, 10, 10, QColor(0, 170, 255));
    painter->drawText(30, 20, "排序区间");
    painter->fillRect(10, 32, 10, 10, QColor(255, 170, 0));
    painter->drawText(30, 40, "合并区间");
}
