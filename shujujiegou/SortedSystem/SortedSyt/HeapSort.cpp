#include "HeapSort.h""
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

HeapSort::HeapSort(QObject *parent)
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

void HeapSort::stop(){
    setRunFlag(false);
    animation.stop();
    loop.quit();
    emit updateRequest();
}

void HeapSort::initArr(int count)
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
    //由于random_shuffle用不了的替代方法
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(arr.begin(),arr.end(),g);

    arrI = 0;
    arrJ = 0;
    swapFlag = false;
    emit updateRequest();
}

void HeapSort::sort(int count, int interval)
{
    // 创建一个guard对象，在离开作用域时设置运行标志为false并发出更新请求
    auto guard = qScopeGuard([this]{
        setRunFlag(false);
        emit updateRequest();
    });
    Q_UNUSED(guard)

    // 停止当前的动画，初始化数组，设置运行标志为true
    stop();
    initArr(count);
    setRunFlag(true);

    // 构建大顶堆
    int len = arr.length();
    for (arrI = len / 2 - 1; arrI >= 0; arrI--)
    {
        heapify(len, arrI,interval);
        if (!getRunFlag()) {
            return;
        }
    }

    // 交换堆顶元素和末尾元素，然后重新调整堆
    for (arrJ = len - 1; arrJ >= 0; arrJ--)
    {
        animation.setDuration(interval * 3);
        animation.start();
        swapFlag = true;
        loop.exec();
        if (getRunFlag()) {
            qSwap(arr[0], arr[arrJ]);
            swapFlag = false;
        }
        heapify(arrJ, 0,interval);
        emit updateRequest();
        if (!getRunFlag()) {
            return;
        }
    }
}


void HeapSort::heapify(int n, int i,int interval)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // 如果左子节点大于根节点，则更新largest
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // 如果右子节点大于根节点，则更新largest
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // 如果largest不等于i，说明需要调整堆
    if (largest != i) {
        animation.setDuration(interval * 3);
        animation.start();
        swapFlag = true;
        arrI = i;
        arrJ = largest;
        loop.exec();
        if (getRunFlag()) {
            qSwap(arr[i], arr[largest]);
            swapFlag = false;
        }
        // 递归调整子堆
        heapify(n, largest,interval);
        emit updateRequest();
        if (!getRunFlag()) {
            return;
        }
    }
}

void HeapSort::draw(QPainter *painter, int width, int height)
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
            if(i==arrI){
                color = QColor(0,170,255);
                if(swapFlag && i==arrJ){
                    item_left += animation.currentValue().toDouble()*(item_width+item_space);
                }
            }
            else if(i==arrJ){
                color = QColor(0,170,255);
                if(swapFlag && i==arrI){
                    item_left -= animation.currentValue().toDouble()*(item_width+item_space);
                }
            }
            else if(i>=len-arrJ){
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
