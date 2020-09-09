/*
*查询管理模块
*/
#pragma once
#include"data_structure.h"

void InitSearchingUnit();   //查询模块初始化
static Commodity* LoadCommMem(Commodity* phead, char* data);
static   Transaction* LoadTransMem(Transaction* phead, char* data);