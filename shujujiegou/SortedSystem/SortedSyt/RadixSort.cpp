#include "RadixSort.h"
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

RadixSort::RadixSort(QObject *parent)
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

void RadixSort::initArr(int count){
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
    swapFlag = false;
    emit updateRequest();
}

void RadixSort::stop(){
    setRunFlag(false);
    animation.stop();
    loop.quit();
    emit updateRequest();
}

// 获取数组中的最大值
int RadixSort::getMax(QVector<int>& arr, int n){
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

// 对数组按照指定的位数进行计数排序
void RadixSort::countSort(QVector<int>& arr, int n, int exp) {
    QVector<int> output(n); // 输出数组
    int i, count[10] = {0};

    // 计算每个位数的出现次数
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // 计算每个位数的结束位置
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // 根据每个位数的结束位置，将元素放到输出数组的相应位置
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // 将排序后的结果复制回原数组
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

// 基数排序
void RadixSort::sort(int count, int interval)
{
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

    // 找到最大的数，以便知道要进行多少轮排序
    int max = getMax(arr, count);

    // 从最低有效位开始，一直到最大数的最高位
    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        // 对每一位进行计数排序
        countSort(arr, count, exp);

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
}
void RadixSort::draw(QPainter *painter, int width, int height)
{
    const int len = arr.length();
    painter->setPen(QColor(200,200,200));//灰色
    //设置边框距离
    const int left_space = 0;
    const int right_space = 0;
    const int top_space = 20;
    const int bottom_space = 50;
    const int item_space = 10;//间隔距离
    const int text_height = painter->fontMetrics().height();//获取字体的高度
    const int text_space = 15;//文本和柱子之间的间隔
    //每一个柱状图的宽度
    const double item_width = (width+item_space-left_space-right_space)/(double)len-item_space;
    const double item_bottom = height-bottom_space;//每个的底部高度
    const double height_factor = (height-top_space-bottom_space)/(double)len;
    double item_left = 0;
    double item_height = 0;
    QColor color;
    for(int i = 0;i<len;i++){
        item_left = left_space+i*(item_width+item_space);
        item_height = height_factor*arr.at(i);//色块高度
        color = QColor(200,200,200);
        if(getRunFlag()){//进行交换
            if(i==arrJ){
                color = QColor(0,170,255);
                if(swapFlag){
                    item_left += animation.currentValue().toDouble()*(item_width+item_space);
                }
            } else if(i==arrJ+1){
                color = QColor(0,170,255);
                if(swapFlag){
                    item_left -= animation.currentValue().toDouble()*(item_width+item_space);
                }
            } else if(i>=len-arrI){
                //排序结束
                color = QColor(0,170,0);
            }
        }
        //画出文字
        painter->drawText(item_left,item_bottom+text_height+text_space,QString::number(arr.at(i)));
        //画色块柱子
        painter->fillRect(item_left,item_bottom-item_height,item_width,item_height,color);
    }
}
