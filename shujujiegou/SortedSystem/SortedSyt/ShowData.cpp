#include "ShowData.h"
#include "ui_ShowData.h"
#include<random>
#include<vector>
#include<QVector>
#include <QProcess>D
#include <QDebug>
#include <QRegularExpression>
#include<windows.h>
#include<Psapi.h>
#include<string>
struct SortResult {
    QString name;
    int compareCount;
    int swapCount;
    long long duration;
};

// 获取当前进程的内存使用量
qint64 getMemoryUsage() {
    HANDLE handle = GetCurrentProcess(); // 获取当前进程的句柄
    PROCESS_MEMORY_COUNTERS pmc; // 创建一个进程内存计数器的结构体
    GetProcessMemoryInfo(handle, &pmc, sizeof(pmc)); // 获取进程的内存信息，并存储在pmc中
    return pmc.WorkingSetSize; // 返回进程的工作集大小，即当前进程占用的物理内存量
}

QVector<SortResult> results;
ShowData::ShowData(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ShowData)
{
    ui->setupUi(this);
    textEdit = ui->textEdit;

}

ShowData::~ShowData()
{
    delete ui;
}

int ShowData::generateRandomNumber(){
    std::random_device rd;  // 用于获取随机数种子
    std::mt19937 gen(rd());  // 使用Mersenne Twister算法生成随机数
    std::uniform_int_distribution<> dis(10001, 20000);  // 定义随机数的范围为10001到20000

    return dis(gen);
}

void ShowData::initArr(int n){
    arr.clear();
    arr.resize(n);  // 改变arr的大小
    for(int i = 0;i<n;i++){
        arr[i] = i+1;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(arr.begin(),arr.end(),g);
}
//---------------------------------排序------------------------------
void ShowData::radixSort(std::vector<int>& arr){
    qint64 memoryBefore = getMemoryUsage();
    textEdit = ui->textEdit;
    int len = arr.size();
    int maxVal = *max_element(arr.begin(), arr.end());
    int exp = 1;
    int swapCount = 0;
    int compareCount = 0;
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> buffer(len);
    while(maxVal / exp > 0){
        std::vector<int> count(10, 0);

        for(int i = 0; i < len; i++){
            count[(arr[i] / exp) % 10]++;
            compareCount++;
        }

        for(int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for(int i = len - 1; i >= 0; i--)
            buffer[--count[(arr[i] / exp) % 10]] = arr[i];

        for(int i = 0; i < len; i++){
            arr[i] = buffer[i];
            swapCount++;
        }

        exp *= 10;
    }

    qint64 memoryAfter = getMemoryUsage();
    qint64 memoryUsed = memoryAfter - memoryBefore;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    QString result;
    result += "运行时间: " + QString::number(duration) + " 微秒\n";
              result += "比较次数: " + QString::number(compareCount) + "\n";
           result += "交换次数: " + QString::number(swapCount) + "\n";
           result += "内存使用量: " + QString::number(memoryUsed) + " 字节\n";
                                       textEdit->setText(result);
           SortResult result2;
           result2.name = "QuickSort";
           result2.compareCount = compareCount;
           result2.swapCount = swapCount;
           result2.duration = duration;
           results.append(result2);
}

void ShowData::shellSort(std::vector<int>& arr){
    qint64 memoryBefore = getMemoryUsage();
    textEdit = ui->textEdit;
    int len = arr.size();
    int swapCount = 0;
    int compareCount = 0;
    auto start = std::chrono::high_resolution_clock::now();

    for(int gap = len / 2; gap > 0; gap /= 2){
        for(int i = gap; i < len; i++){
            int temp = arr[i];
            int j;
            for(j = i; j >= gap && arr[j - gap] > temp; j -= gap){
                compareCount++;
                arr[j] = arr[j - gap];
                swapCount++;
            }
            arr[j] = temp;
        }
    }
    qint64 memoryAfter = getMemoryUsage();
    qint64 memoryUsed = memoryAfter - memoryBefore;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    QString result;
    result += "运行时间: " + QString::number(duration) + " 微秒\n";
              result += "比较次数: " + QString::number(compareCount) + "\n";
           result += "交换次数: " + QString::number(swapCount) + "\n";
          result += "内存使用量: " + QString::number(memoryUsed) + " 字节\n";
                          textEdit->setText(result);
           SortResult result2;
           result2.name = "shellSort";
           result2.compareCount = compareCount;
           result2.swapCount = swapCount;
           result2.duration = duration;
           results.append(result2);
}

#include <vector>
#include <list>
#include <algorithm>

void ShowData::bucketSort(std::vector<int>& arr){
    qint64 memoryBefore = getMemoryUsage();
    textEdit = ui->textEdit;
    int len = arr.size();
    int swapCount = 0;
    int compareCount = 0;
    auto start = std::chrono::high_resolution_clock::now();

    int minValue = *min_element(arr.begin(), arr.end());
    int maxValue = *max_element(arr.begin(), arr.end());

    // Bucket size. Modify this value according to the code logic
    int bucketSize = len; // Change here

    // Create an empty bucket
    std::vector<std::list<int>> bucket(bucketSize, std::list<int>());

    // Fill the bucket
    for(int i = 0; i < len; i++) {
        int bucketIndex = (arr[i] - minValue) * (bucketSize - 1) / (maxValue - minValue); // Change here
        bucket[bucketIndex].push_back(arr[i]);
    }

    // Sort each bucket and merge
    int index = 0;
    for(int i = 0; i < bucketSize; i++) {
        bucket[i].sort();
        for(auto & x : bucket[i]) {
            arr[index++] = x;
            swapCount++;
        }
    }

    qint64 memoryAfter = getMemoryUsage();
    qint64 memoryUsed = memoryAfter - memoryBefore;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    QString result;
    result += "运行时间: " + QString::number(duration) + " 微秒\n";
              result += "比较次数: " + QString::number(compareCount) + "\n";
           result += "交换次数: " + QString::number(swapCount) + "\n";
           result += "内存使用量: " + QString::number(memoryUsed) + " 字节\n";
                            textEdit->setText(result);
    SortResult result2;
    result2.name = "bucketSort";
    result2.compareCount = compareCount;
    result2.swapCount = swapCount;
    result2.duration = duration;
    results.append(result2);
}

void ShowData::selectionSort(std::vector<int>& arr){
    qint64 memoryBefore = getMemoryUsage();
    textEdit = ui->textEdit;
    int len = arr.size();
    int swapCount = 0;
    int compareCount = 0;
    auto start = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < len - 1; i++){
        int minIndex = i;
        for(int j = i + 1; j < len; j++){
            compareCount++;
            if(arr[j] < arr[minIndex]){
                minIndex = j;
            }
        }
        if(minIndex != i){
            std::swap(arr[i], arr[minIndex]);
            swapCount++;
        }
    }
    qint64 memoryAfter = getMemoryUsage();
    qint64 memoryUsed = memoryAfter - memoryBefore;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    QString result;
    result += "运行时间: " + QString::number(duration) + " 微秒\n";
              result += "比较次数: " + QString::number(compareCount) + "\n";
           result += "交换次数: " + QString::number(swapCount) + "\n";
            result += "内存使用量: " + QString::number(memoryUsed) + " 字节\n";
                          textEdit->setText(result);
           SortResult result2;
           result2.name = "selectionSort";
           result2.compareCount = compareCount;
           result2.swapCount = swapCount;
           result2.duration = duration;
           results.append(result2);
}

void ShowData::bubbleSort(std::vector<int>& arr){
    qint64 memoryBefore = getMemoryUsage();
    textEdit = ui->textEdit;
    int len = arr.size();
    int swapCount = 0;
    int compareCount = 0;
    auto start = std::chrono::high_resolution_clock::now();

    for(int i = 0;i<len-1;i++){
        for(int j = 0;j<len-i-1;j++){
            compareCount++;
            if(arr[j]>arr[j+1]){
                std::swap(arr[j],arr[j+1]);
                swapCount++;
            }
        }
    }
    qint64 memoryAfter = getMemoryUsage();
    qint64 memoryUsed = memoryAfter - memoryBefore;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    QString result;
    result += "运行时间: " + QString::number(duration) + " 微秒\n";
    result += "比较次数: " + QString::number(compareCount) + "\n";
    result += "交换次数: " + QString::number(swapCount) + "\n";
    result += "内存使用量: " + QString::number(memoryUsed) + " 字节\n";
    textEdit->setText(result);
    SortResult result2;
    result2.name = "bubbleSort";
    result2.compareCount = compareCount;
    result2.swapCount = swapCount;
    result2.duration = duration;
    results.append(result2);

}

void ShowData::insertionSort(std::vector<int>& arr){
    qint64 memoryBefore = getMemoryUsage();
    textEdit = ui->textEdit;
    int len = arr.size();
    int swapCount = 0;
    int compareCount = 0;
    auto start = std::chrono::high_resolution_clock::now();

    for(int i = 1; i < len; i++){
        int key = arr[i];
        int j = i - 1;

        while(j >= 0 && arr[j] > key){
            compareCount++;
            arr[j + 1] = arr[j];
            swapCount++;
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    qint64 memoryAfter = getMemoryUsage();
    qint64 memoryUsed = memoryAfter - memoryBefore;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    QString result;
    result += "运行时间: " + QString::number(duration) + " 微秒\n";
              result += "比较次数: " + QString::number(compareCount) + "\n";
           result += "交换次数: " + QString::number(swapCount) + "\n";
    result += "内存使用量: " + QString::number(memoryUsed) + " 字节\n";
                          textEdit->setText(result);
           SortResult result2;
           result2.name = "insertionSort";
           result2.compareCount = compareCount;
           result2.swapCount = swapCount;
           result2.duration = duration;
           results.append(result2);
}


void ShowData::countingSort(std::vector<int>& arr){
    qint64 memoryBefore = getMemoryUsage();
    textEdit = ui->textEdit;
    int len = arr.size();
    int swapCount = 0;
    int compareCount = 0;
    auto start = std::chrono::high_resolution_clock::now();

    int minValue = *min_element(arr.begin(), arr.end());
    int maxValue = *max_element(arr.begin(), arr.end());

    // Create a count array
    std::vector<int> count(maxValue - minValue + 1, 0);

    // Count the occurrence of each element
    for(int i = 0; i < len; i++) {
        count[arr[i] - minValue]++;
    }

    // Overwrite arr with the sorted elements
    int index = 0;
    for(int i = 0; i < count.size(); i++) {
        while(count[i]-- > 0) {
            arr[index++] = i + minValue;
            swapCount++;
        }
    }

    qint64 memoryAfter = getMemoryUsage();
    qint64 memoryUsed = memoryAfter - memoryBefore;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    QString result;
    result += "运行时间: " + QString::number(duration) + " 微秒\n";
              result += "比较次数: " + QString::number(compareCount) + "\n";
           result += "交换次数: " + QString::number(swapCount) + "\n";
           result += "内存使用量: " + QString::number(memoryUsed) + " 字节\n";
                            textEdit->setText(result);
    SortResult result2;
    result2.name = "countingSort";
    result2.compareCount = compareCount;
    result2.swapCount = swapCount;
    result2.duration = duration;
    results.append(result2);
}

void ShowData::heapify(std::vector<int>& arr, int n, int i, int& swapCount, int& compareCount){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n){
        compareCount++;
        if(arr[left] > arr[largest]){
            largest = left;
        }
    }

    if(right < n){
        compareCount++;
        if(arr[right] > arr[largest]){
            largest = right;
        }
    }

    if(largest != i){
        std::swap(arr[i], arr[largest]);
        swapCount++;
        heapify(arr, n, largest, swapCount, compareCount);
    }
}

void ShowData::heapSort(std::vector<int>& arr){
    qint64 memoryBefore = getMemoryUsage();
    textEdit = ui->textEdit;
    int len = arr.size();
    int swapCount = 0;
    int compareCount = 0;
    auto start = std::chrono::high_resolution_clock::now();

    for(int i = len / 2 - 1; i >= 0; i--){
        heapify(arr, len, i, swapCount, compareCount);
    }

    for(int i = len - 1; i >= 0; i--){
        std::swap(arr[0], arr[i]);
        swapCount++;
        heapify(arr, i, 0, swapCount, compareCount);
    }
    qint64 memoryAfter = getMemoryUsage();
    qint64 memoryUsed = memoryAfter - memoryBefore;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    QString result;
    result += "运行时间: " + QString::number(duration) + " 微秒\n";
              result += "比较次数: " + QString::number(compareCount) + "\n";
           result += "交换次数: " + QString::number(swapCount) + "\n";
    result += "内存使用量: " + QString::number(memoryUsed) + " 字节\n";
                          textEdit->setText(result);
           SortResult result2;
           result2.name = "heapSort";
           result2.compareCount = compareCount;
           result2.swapCount = swapCount;
           result2.duration = duration;
           results.append(result2);
}

void ShowData::quickSort(std::vector<int>& arr){
    qint64 memoryBefore = getMemoryUsage();
    int compareCount = 0;
    int swapCount = 0;
    auto start = std::chrono::high_resolution_clock::now();

    std::function<int(std::vector<int>&, int, int)> partition = [&](std::vector<int>& arr, int left, int right) -> int {
        int pivot = arr[right];
        int i = left - 1;
        for(int j = left; j <= right - 1; j++){
            compareCount++;
            if(arr[j] < pivot){
                i++;
                std::swap(arr[i], arr[j]);
                swapCount++;
            }
        }
        std::swap(arr[i + 1], arr[right]);
        swapCount++;
        return (i + 1);
    };

    std::function<void(std::vector<int>&, int, int)> quickSortRecursive = [&](std::vector<int>& arr, int left, int right){
        if(left < right){
            int pivot = partition(arr, left, right);
            quickSortRecursive(arr, left, pivot - 1);
            quickSortRecursive(arr, pivot + 1, right);
        }
    };

    quickSortRecursive(arr, 0, arr.size() - 1);
    qint64 memoryAfter = getMemoryUsage();
    qint64 memoryUsed = memoryAfter - memoryBefore;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    QString result;
    result += "运行时间: " + QString::number(duration) + " 微秒\n";
              result += "比较次数: " + QString::number(compareCount) + "\n";
           result += "交换次数: " + QString::number(swapCount) + "\n";
     result += "内存使用量: " + QString::number(memoryUsed) + " 字节\n";
                          textEdit->setText(result);
           SortResult result2;
           result2.name = "quickSort";
           result2.compareCount = compareCount;
           result2.swapCount = swapCount;
           result2.duration = duration;
           results.append(result2);
}

void ShowData::mergeSort(std::vector<int>& arr){
    qint64 memoryBefore = getMemoryUsage();
    int compareCount = 0;
    int mergeCount = 0;
    auto start = std::chrono::high_resolution_clock::now();

    std::function<void(std::vector<int>&, int, int, int)> merge = [&](std::vector<int>& arr, int left, int mid, int right){
        int i, j, k;
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<int> L(n1), R(n2);

        for(i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for(j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        i = 0;
        j = 0;
        k = left;
        while(i < n1 && j < n2){
            compareCount++;
            if(L[i] <= R[j]){
                arr[k] = L[i];
                i++;
            }else{
                arr[k] = R[j];
                j++;
            }
            mergeCount++;
            k++;
        }

        while(i < n1){
            arr[k] = L[i];
            i++;
            k++;
        }

        while(j < n2){
            arr[k] = R[j];
            j++;
            k++;
        }
    };

    std::function<void(std::vector<int>&, int, int)> mergeSortRecursive = [&](std::vector<int>& arr, int left, int right){
        if(left < right){
            int mid = left + (right - left) / 2;
            mergeSortRecursive(arr, left, mid);
            mergeSortRecursive(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    };

    mergeSortRecursive(arr, 0, arr.size() - 1);
    qint64 memoryAfter = getMemoryUsage();
    qint64 memoryUsed = memoryAfter - memoryBefore;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    QString result;
    result += "运行时间: " + QString::number(duration) + " 微秒\n";
              result += "比较次数: " + QString::number(compareCount) + "\n";
           result += "合并次数: " + QString::number(mergeCount) + "\n";
    result += "内存使用量: " + QString::number(memoryUsed) + " 字节\n";
                          textEdit->setText(result);
           SortResult result2;
           result2.name = "mergeSort";
           result2.compareCount = compareCount;
           result2.swapCount = mergeCount;
           result2.duration = duration;
           results.append(result2);
}
//----------------------------------------------------
void ShowData::on_pushButton_clicked()
{
    QString choose = ui->ChooseSort->text();
    if(choose=='1'){
        int n = generateRandomNumber();
        initArr(n);
        bubbleSort(arr);
    }
    else if(choose=='2'){
        int n = generateRandomNumber();
        initArr(n);
        selectionSort(arr);
    }
    else if(choose=='3'){
        int n = generateRandomNumber();
        initArr(n);
        shellSort(arr);
    }
    else if(choose=='4'){
        int n = generateRandomNumber();
        initArr(n);
        radixSort(arr);
    }
    else if(choose=='5'){
        int n = generateRandomNumber();
        initArr(n);
        insertionSort(arr);
    }
    else if(choose=='6'){
        int n = generateRandomNumber();
        initArr(n);
        heapSort(arr);
    }
    else if(choose=='7'){
        int n = generateRandomNumber();
        initArr(n);
        quickSort(arr);
    }
    else if(choose=='8'){
        int n = generateRandomNumber();
        initArr(n);
        mergeSort(arr);
    }
    else if(choose=="10"){
        int n = generateRandomNumber();
        initArr(n);
        bucketSort(arr);
    }
    /*
    else if(choose=="11"){
        int n = generateRandomNumber();
        initArr(n);
        countingSort(arr);
    }
    */
    else if(choose=="91"){
        int n = generateRandomNumber();
        results.clear();
        initArr(n);
        bubbleSort(arr);
        initArr(n);
        quickSort(arr);
        initArr(n);
        mergeSort(arr);
        initArr(n);
        selectionSort(arr);
        initArr(n);
        insertionSort(arr);
        initArr(n);
        radixSort(arr);
        initArr(n);
        shellSort(arr);
        initArr(n);
        heapSort(arr);
        initArr(n);
        bucketSort(arr);
       // initArr(n);
       // countingSort(arr);
        std::sort(results.begin(), results.end(), [](const SortResult& a, const SortResult& b) {
            return a.compareCount < b.compareCount;
        });
        QString resultText;
        for(const auto& result : results) {
            resultText += result.name + ": " + QString::number(result.compareCount) + " comparisons, " + QString::number(result.swapCount) + " swaps, " + QString::number(result.duration) + " microseconds\n";
        }
        textEdit->setText(resultText);
    }
    else if(choose=="92"){
        int n = generateRandomNumber();
        results.clear();
        initArr(n);
        bubbleSort(arr);
        initArr(n);
        quickSort(arr);
        initArr(n);
        mergeSort(arr);
        initArr(n);
        selectionSort(arr);
        initArr(n);
        insertionSort(arr);
        initArr(n);
        radixSort(arr);
        initArr(n);
        shellSort(arr);
        initArr(n);
        heapSort(arr);
        initArr(n);
        bucketSort(arr);
      //  initArr(n);
      //  countingSort(arr);
        std::sort(results.begin(), results.end(), [](const SortResult& a, const SortResult& b) {
            return a.duration < b.duration;
        });
        QString resultText;
        for(const auto& result : results) {
            resultText += result.name + ": " + QString::number(result.compareCount) + " comparisons, " + QString::number(result.swapCount) + " swaps, " + QString::number(result.duration) + " microseconds\n";
        }
        textEdit->setText(resultText);
    }
}

