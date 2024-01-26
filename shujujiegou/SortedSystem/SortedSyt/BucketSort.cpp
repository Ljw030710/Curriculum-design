#include "BucketSort.h"
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
BucketSort::BucketSort(QObject *parent)
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

void BucketSort::initArr(int count) {
    arr.clear();
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,99);
    for(int i = 0; i < count; i++) {
        arr.push_back(distribution(generator)); // 假设元素在0-99之间
    }
    arrI = 0;
    arrJ = 0;
    swapFlag = false;
    animation.stop();
}

void BucketSort::stop() {
    animation.stop();
    loop.quit();
    arr.clear();
    arrI = 0;
    arrJ = 0;
    swapFlag = false;
}

void BucketSort::bucketSort(QVector<int>& arr) {
    // 获取数组中的最大值和最小值
    int max_val = *std::max_element(arr.begin(), arr.end());
    int min_val = *std::min_element(arr.begin(), arr.end());

    // 计算桶的数量
    int bucketCount = max_val - min_val + 1;
    // 创建桶
    QVector<QVector<int>> buckets(bucketCount);

    // 将数组中的每个元素放入对应的桶中
    for (int i = 0; i < arr.size(); i++) {
        buckets[arr[i] - min_val].push_back(arr[i]);
    }

    int index = 0;
    // 对每个桶中的元素进行排序，并将排序后的元素放回到原数组中
    for (int i = 0; i < buckets.size(); i++) {
        // 对桶中的元素进行排序
        std::sort(buckets[i].begin(), buckets[i].end());

        // 将排序后的元素放回到原数组中
        for (int j = 0; j < buckets[i].size(); j++) {
            arr[index++] = buckets[i][j];
        }
    }
}

void BucketSort::sort(int count, int interval) {
    initArr(count);

    // 开始排序
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // 开始动画
                animation.setDuration(interval);
                animation.start();

                // 进入事件循环，等待动画结束
                loop.exec();

                // 交换元素
                std::swap(arr[j], arr[j + 1]);
                swapFlag = true;
            }
        }

        if (!swapFlag) {
            break;
        }
    }
}

void BucketSort::draw(QPainter *painter, int width, int height) {
    if (arr.empty()) {
        return;
    }

    // 计算每个元素的宽度和高度
    int barWidth = width / arr.size() - 2;  // 减2为每个柱子留出1像素的空隙
    int maxVal = *std::max_element(arr.begin(), arr.end());
    double scaleFactor = (double)height / maxVal;

    // 绘制每个元素
    for (int i = 0; i < arr.size(); i++) {
        int barHeight = arr[i] * scaleFactor;
        QRect bar(i * (barWidth + 2), height - barHeight, barWidth, barHeight);  // 每个柱子的位置加2，为每个柱子留出1像素的空隙

        // 如果元素正在交换，使用不同的颜色
        if (swapFlag && (i == arrI || i == arrJ)) {
            painter->fillRect(bar, Qt::red);
        } else {
            painter->fillRect(bar, Qt::blue);
        }
    }
}
