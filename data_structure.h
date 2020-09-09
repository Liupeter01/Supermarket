#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include<string.h>
#include<io.h>

 #define MAXBYTE 256

/*
*商品的基本信息
*/
typedef struct Commodity
{
          char* Name;   //商品名称
          char* Variety;  //商品种类
          char* Manufacture;//生产厂家
          double Price;//价格
          char* Valid_date;//有效期
          int Left;//商品库存量
          char* Addition;     //备注
          int TransAcation; //交易状态，用0代表没有交易与1开始了交易
          struct Commodity* pnext;   //链表下一个节点

}Commodity;

/*
*商品的采购销售交易信息
*/
typedef struct Transaction
{
          char* Name;   //商品名称
          int Amount;  //交易数量
          char* Place;        //交易地点
          char* TransTime;   //交易时间
          double Price;       //交易金额
          char*TranscationType;         //交易类型
          char*Operator;      //操作员
          int TempoaryItemCount;  //当前库存余量
          struct Transaction* pnext;   //链表下一个节点

}Transaction;

/*链表内存释放工具*/
void FreeTransMemory(struct Transaction* phead);
void FreeCommodityMemory(struct Commodity* phead);
/*
*链表尾插法
* 不同商品信息的商品名称不能相同，若出现相同，应该给出不能保存商品信息的提示模块
*/
Commodity* AddNodeFromTail(Commodity* phead);
 void WriteToFile(struct Commodity* phead);   //将商品信息写入到文件之中
 static Commodity* LoadMem(Commodity* phead, char* data);