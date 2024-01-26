#pragma once
#include "SortObject.h"
#include <QVector>
#include <QEventLoop>
#include <QVariantAnimation>

//冒泡排序

class BubbleSort : public SortObject
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);

    //开始排序
    //count元素个数，interval动画持续时间参考值
    void sort(int count, int interval) override;
    //结束排序
    void stop() override;
    //绘制
    void draw(QPainter *painter, int width, int height) override;

private:
    //初始化
    void initArr(int count);

private:
    //判断动画结束
    QEventLoop loop;
    //动画
    QVariantAnimation animation;
    //存贮数字的vector
    QVector<int> arr;
    //for循环下标
    int arrI{0};
    int arrJ{0};
    //标记当前交换状态
    bool swapFlag{false};
};
