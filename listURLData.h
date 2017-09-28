// Jesse Colville September 2017

#ifndef DATALIST_H
#define DATALIST_H

typedef struct dataListRep *dataList;

dataList createDataList();
void insertDataListNode(dataList, char *, int, double);

#endif