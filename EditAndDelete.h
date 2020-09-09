#pragma once
/*
*删与改功能集合
*/
#include"data_structure.h"

void InitEditAndDelete(); //初始化编辑与删除
Commodity* Delete(Commodity* phead, char* data);
Commodity* Edit(Commodity*phead, char* data);
static Commodity* LoadMem(Commodity* phead, char* data);