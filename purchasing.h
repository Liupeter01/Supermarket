/*
*采购专属
*/
#pragma once
#include"SalesAndPurchasing.h"

void InitPurchasing(); //负责采购的主程序
static  Commodity* LoadMem(Commodity* phead, char* data);

/*
*商品的采购信息
* 参数1，phead作为采购信息链表的头节点
* 参数2，compare用于比较在商品信息中是否存在此商品
* 如果商品存在才可以进行添加
*/
Transaction* PurchasingAddNodeFromTail(Transaction* phead, Commodity* compare);

