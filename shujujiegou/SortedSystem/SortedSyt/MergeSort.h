#pragma once
#include "SortObject.h"
#include <QVector>
#include <QEventLoop>
#include <QVariantAnimation>
#include<QStack>
//归并排序
class MergeSort : public SortObject
{
    Q_OBJECT
public:
    explicit MergeSort(QObject *parent = nullptr);

    //开始排序
    //count元素个数，interval动画持续时间参考值
    void sort(int count, int interval) override;
    //结束排序
    void stop() override;
    //绘制
    void draw(QPainter *painter, int width, int height) override;

private:
    void initArr(int count);
    //归并排序
    void doSort(int low, int high);
    //延时
    void wait(int ms);
    //合并
    void merge(int low, int mid, int high);

private:
    QEventLoop loop;
    QVariantAnimation animation;
    int interval{0};
    int curBegin{0};
    int curEnd{0};
    //坑的位置和坑的值
    int posIndex{0};
    int posValue{0};
    QVector<int> arr;
    QStack<QPair<int,int>> rangeStack;
    //当前分治的范围
    int rangeBegin{0};
    int rangeEnd{0};
    //合并的范围
    int mergeBegin{0};
    int mergeEnd{0};
    //标记当前合并状态
    bool mergeFlag{false};
};
