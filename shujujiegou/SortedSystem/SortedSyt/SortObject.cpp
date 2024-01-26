#include "SortObject.h"

SortObject::SortObject(QObject *parent)
    : QObject(parent)
{

}

bool SortObject::getRunFlag() const
{
    return runFlag;
}

void SortObject::setRunFlag(bool flag)
{
    if (runFlag == flag) {
        return;
    }
    runFlag = flag;
    //更新改变状态
    emit runFlagChanged(flag);
}
