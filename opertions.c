#include"opertions.h"
#include"EditAndDelete.h"
#include"Sales.h"
#include"purchasing.h"
#include"init.h"
#include"SearchAndFind.h"
#include"statistics.h"

void Menu()   //启动初始菜单项
{
          while (1)
          {
                    printf("\n       欢迎使用小型超市管理系统 by刘沛恒    \n"
                              "                  选择菜单         \n"
                              "             1、录入商品的基本信息                \n"
                              "             2、商品采购管理                \n"
                              "             3、商品销售管理                \n"
                              "             4、维护商品基本信息(包括修改、删除)                \n"
                              "             5、输出商品基本信息                \n"
                              "             6、输出商品交易信息                \n"
                              "             7、查询管理                \n"
                              "             8、统计管理                \n"
                              "             9、退出系统                \n"
                    );

                    printf("\n请输入需要执行的操作：");
                    int choice = -1;
                    scanf_s("%d", &choice);
                    switch (choice)
                    {
                    case 1:InitCommdity(); break;
                    case 2:InitPurchasing(); break;   //采购管理
                    case 3:InitSales(); break;   //销售
                    case 4:InitEditAndDelete(); break; //修改删除
                    case 5:DisplayAllBasicInfo(); break;
                    case 6:DisplayAllTransInfo(); break;
                    case 7:InitSearchingUnit(); break;
                    case 8:InitStatistics(); break;
                    case 9:Quit(); break;
                    default: printf("输入错误请重新输入!!!!\n");
                              break;
                    }
          }
}

void DisplayAllBasicInfo()  //输出全部商品的基本信息
{
          if (_access("ware_base.dat", 0) == -1)    //判断文件是否存在
          {
                    printf("尚未创建基本的商品目录、请先选择1\n");
                    return;
          }
          FILE* pfr = fopen("ware_base.dat", "r");
          while (!feof(pfr))
          {
                    char mem[MAXBYTE] = { 0 };
                    fgets(mem, MAXBYTE, pfr);
                    printf("%s", mem);
                    memset(mem, 0, MAXBYTE);
          }
          fclose(pfr);
          fclose(pfr);
}

void DisplayAllTransInfo() //输出全部商品的交易信息
{
          FILE* pfr = fopen("bankcard_deal.dat", "r");
          while (!feof(pfr))
          {
                    char mem[MAXBYTE] = { 0 };
                    fgets(mem, MAXBYTE, pfr);
                    printf("%s", mem);
                    memset(mem, 0, MAXBYTE);
          }
          fclose(pfr);
}