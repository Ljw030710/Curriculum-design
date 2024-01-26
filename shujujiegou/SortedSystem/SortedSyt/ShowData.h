#ifndef SHOWDATA_H
#define SHOWDATA_H

#include <QTextEdit>
#include <QWidget>
#include <algorithm>
#include <cmath>
#include <QtMath>
#include <QTime>
#include <QPainter>
#include <QPaintEvent>
#include <QScopeGuard>
#include <vector>
#include <QFontMetrics>
#include <QDebug>
#include<random>

namespace Ui {
class ShowData;
}

class ShowData : public QWidget
{
    Q_OBJECT

public:
    explicit ShowData(QWidget *parent = nullptr);
    ~ShowData();
    //---------------------排序算法---------------------//
    void bubbleSort(std::vector<int>& arr);
    void selectionSort(std::vector<int>& arr);
    void shellSort(std::vector<int>& arr);
    void radixSort(std::vector<int>& arr);
    void insertionSort(std::vector<int>& arr);
    void bucketSort(std::vector<int>& arr);
    void quickSort(std::vector<int>& arr);
    void countingSort(std::vector<int>& arr);

    void heapify(std::vector<int>& arr, int n, int i, int& swapCount,int& compareCount);
    void heapSort(std::vector<int>& arr);

    void mergeSort(std::vector<int>& arr);

    //------------------------------------------------------------
    //初始化
    void initArr(int n);
    //生成随机数
    int generateRandomNumber();
private slots:
    //用来确定选择哪个的按钮
    void on_pushButton_clicked();

private:
    Ui::ShowData *ui;
    //文本框
    QTextEdit *textEdit;
    //用来排序的数组
    std::vector<int> arr;
};

#endif // SHOWDATA_H
