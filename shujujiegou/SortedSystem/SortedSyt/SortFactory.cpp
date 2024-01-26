#include "SortFactory.h"
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "QuickSort.h"
#include "ShellSort.h"
#include "MergeSort.h"
#include "HeapSort.h"
#include "RadixSort.h"
#include "CountSort.h"
#include "BucketSort.h"
SortFactory::SortFactory(QObject *parent)
    : QObject(parent)
{

}

SortFactory *SortFactory::getInstance()
{
    static SortFactory instance;
    return &instance;
}

SortObject *SortFactory::createSortObject(int row, QObject *parent)
{
    switch (row) {
    case 0: return new BubbleSort(parent);
    case 1: return new SelectionSort(parent);
    case 2: return new InsertionSort(parent);
    case 3: return new QuickSort(parent);
    case 4: return new ShellSort(parent);
    case 5: return new MergeSort(parent);
    case 6: return new HeapSort(parent);
    case 7: return new RadixSort(parent);
    case 8: return new CountingSort(parent);
    case 9: return new BucketSort(parent);
    default: break;
    }
    return nullptr;
}

QStringList SortFactory::getSortList() const
{
    return QStringList{
          "冒泡排序"
        , "选择排序"
        , "插入排序"
        , "快速排序"
        , "希尔排序"
        , "归并排序"
        , "堆排序"
        , "基数排序"
        , "计数排序"
        , "桶排序"
    };
}
