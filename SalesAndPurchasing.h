#pragma once

#include"data_structure.h"
/*
*此文件用于purchasing与Sales头文件具有共性的操作
*/

/*将商品信息写入到文件之中bankcard_deal.dat*/
void WriteBankCardFile(struct Transaction* phead);

/*将商品基本信息更新到原来的商品基本信息表中ware_base.dat.dat*/
void UpdateBothFile(struct Transaction* phead, struct  Commodity* compare);
