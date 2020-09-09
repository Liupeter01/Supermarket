#include"statistics.h"

void InitStatistics()
{
          if (_access("ware_base.dat", 0) == -1)    //判断文件是否存在
          {
                    printf("尚未创建基本的商品目录、请先选择1\n");
                    return;
          }
          int choice = 0;
          while (1)
          {
                    printf("\n欢迎使用统计系统，请进行需要进行的操作(1代表商品基本信息、2代表商品交易信息、0返回上级菜单)：");
                    scanf("%d", &choice);
                    if (choice == 1)    //商品的基本信息
                    {
                              Commodity* phead_commodity = NULL;  //用于从基本信息表中添加信息
                              FILE* pfr = fopen("ware_base.dat", "r");
                              while (!feof(pfr))
                              {
                                        char* temp = (char*)calloc(MAXBYTE, sizeof(char));
                                        fgets(temp, MAXBYTE, pfr);
                                        phead_commodity = LoadCommMem(phead_commodity, temp);
                              }
                              fclose(pfr);
                              /*内存加载完成*/

                              printf("请输入需要查找的内容(1商品名称、2商品种类、3生产厂家、4有效期)：");
                              choice = -1;
                              scanf("%d", &choice);
                              printf("请输入需要查找的内容：");
                              char temp[MAXBYTE] = { 0 };
                              scanf("%s", temp);

                              Commodity* p1 = phead_commodity;
                              int storage = 0;

                              if (choice == 1)//商品名称
                              {
                                        while (p1 != NULL)
                                        {
                                                  if (strcmp(p1->Name, temp) == 0)
                                                  {
                                                            storage += p1->Left;
                                                  }
                                                  p1 = p1->pnext;
                                        }
                              }
                              else if (choice == 2)//商品种类
                              {
                                        while (p1 != NULL)
                                        {
                                                  if (strcmp(p1->Variety, temp) == 0)
                                                  {
                                                            storage += p1->Left;
                                                  }
                                                  p1 = p1->pnext;
                                        }
                              }
                              else if (choice == 3)//生产厂家
                              {
                                        while (p1 != NULL)
                                        {
                                                  if (strcmp(p1->Manufacture, temp) == 0)
                                                  {
                                                            storage += p1->Left;
                                                  }
                                                  p1 = p1->pnext;
                                        }
                              }
                              else if (choice == 4)//有效期
                              {
                                        while (p1 != NULL)
                                        {
                                                  if (strcmp(p1->Valid_date, temp) == 0)
                                                  {
                                                            storage += p1->Left;
                                                  }
                                                  p1 = p1->pnext;
                                        }
                              }
                              else
                              {
                                        printf("输入错误\n");
                              }

                              printf("根据您的筛选情况，已找到满足条件的库存量为：%d\n", storage);
                              memset(temp, 0, MAXBYTE);
                              FreeCommodityMemory(phead_commodity);   //清理内存
                    }
                    else if (choice == 2)//商品的交易信息
                    {
                              Transaction* phead_transaction = NULL;  //用于从交易信息表中添加信息
                              FILE* pfr = fopen("bankcard_deal.dat", "r");
                              while (!feof(pfr))
                              {
                                        char* temp = (char*)calloc(MAXBYTE, sizeof(char));
                                        fgets(temp, MAXBYTE, pfr);
                                        phead_transaction = LoadTransMem(phead_transaction, temp);
                              }
                              fclose(pfr);
                              /*内存加载完成*/
                              printf("请输入需要查找的内容(1商品名称、2交易时间、"
                                        "3交易地点、4交易类型、5操作员)：");

                              choice = -1;
                              scanf("%d", &choice);
                              printf("请输入需要查找的内容：");
                              char temp[MAXBYTE] = { 0 };
                              scanf("%s", temp);

                              Transaction* p1 = phead_transaction;
                              int count = 0;
                              double money = 0.0;

                             
                              if (choice == 1)//商品名称
                              {
                                        while (p1 != NULL)
                                        {
                                                  if (strcmp(p1->Name, temp) == 0)
                                                  {
                                                            ++count;
                                                            money += p1->Price;
                                                  }
                                                  p1 = p1->pnext;
                                        }
                              }
                              else if (choice == 2)//交易时间
                              {
                                        while (p1 != NULL)
                                        {
                                                  if (strcmp(p1->TransTime, temp) == 0)
                                                  {
                                                            ++count;
                                                            money += p1->Price;
                                                  }
                                                  p1 = p1->pnext;
                                        }
                              }
                              else if (choice == 3)//交易地点
                              {
                                        while (p1 != NULL)
                                        {
                                                  if (strcmp(p1->Place, temp) == 0)
                                                  {
                                                            ++count;
                                                            money += p1->Price;
                                                  }
                                                  p1 = p1->pnext;
                                        }
                              }
                              else if (choice == 4)//交易类型
                              {
                                        while (p1 != NULL)
                                        {
                                                  if (strcmp(p1->TranscationType, temp) == 0)
                                                  {
                                                            ++count;
                                                            money += p1->Price;
                                                  }
                                                  p1 = p1->pnext;
                                        }
                              }
                              else if (choice == 5)//操作员
                              {
                                        while (p1 != NULL)
                                        {
                                                  if (strcmp(p1->Operator, temp) == 0)
                                                  {
                                                            ++count;
                                                            money += p1->Price;
                                                  }
                                                  p1 = p1->pnext;
                                        }
                              }
                              else
                              {
                                        printf("输入错误\n");
                                        return;
                              }
                              printf("根据您的筛选情况，已找到满足条件的交易数量为：%d\n总的交易金额为%lf\n", count, money);
                              memset(temp, 0, MAXBYTE);
                              FreeTransMemory(phead_transaction);
                              choice = -1;
                    }
                    else if(choice==0)
                    {
                              break;
                    }
                    else if(choice <-2)
                    {
                              printf("输入错误\n");
                    }
          }
}

static Commodity* LoadCommMem(Commodity* phead, char* data)
{
          Commodity* newnode = (Commodity*)malloc(sizeof(Commodity));  //创建第一个节点
          newnode->pnext = NULL;

          /*
       *以下临时变量用于存储以下信息
                  char* Name;   //商品名称
                   char* Variety;  //商品种类
                   char* Manufacture;//生产厂家
                   double Price;//价格
                  char* Valid_date;//有效期
                  int Left;//商品库存量
                   char* Addition;     //备注
                   int TransAcation  //交易状态
       */
          char name[MAXBYTE] = { 0 };
          char variety[MAXBYTE] = { 0 };
          char manufacture[MAXBYTE] = { 0 };
          char valid_date[MAXBYTE] = { 0 };
          char add[MAXBYTE] = { 0 };

          for (int i = 0; i < (int)strlen(data); ++i)
          {
                    if (data[i] == ',')
                    {
                              data[i] = ' ';
                    }
          }
          sscanf(data, " %s%s%s%lf%s%d%s%d",
                    name,
                    variety,
                    manufacture,
                    &newnode->Price,
                    valid_date,
                    &newnode->Left,
                    add,
                    &newnode->TransAcation
          );

          if (strcmp(name, "") == 0)
          {
                    return phead;
          }


          newnode->Name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
          strcpy(newnode->Name, name);

          newnode->Variety = (char*)malloc(sizeof(char) * (strlen(variety) + 1));
          strcpy(newnode->Variety, variety);

          newnode->Manufacture = (char*)malloc(sizeof(char) * (strlen(manufacture) + 1));
          strcpy(newnode->Manufacture, manufacture);

          newnode->Valid_date = (char*)malloc(sizeof(char) * (strlen(valid_date) + 1));
          strcpy(newnode->Valid_date, valid_date);

          newnode->Addition = (char*)malloc(sizeof(char) * (strlen(add) + 1));
          strcpy(newnode->Addition, add);

          if (phead == NULL)   //不存在头节点
          {
                    phead = newnode;
          }
          else
          {
                    Commodity* temp = phead;
                    while (temp->pnext != NULL)
                    {
                              temp = temp->pnext;
                    }
                    temp->pnext = newnode;  ///链接
          }
          return phead;
}

static   Transaction* LoadTransMem(Transaction* phead, char* data)
{
          Transaction* newnode = (Transaction*)malloc(sizeof(Transaction));  //创建第一个节点
          newnode->pnext = NULL;

          /*
          *以下临时变量用于存储以下信息
                     char* Name;   //商品名称
                      char* Variety;  //商品种类
                      char* Manufacture;//生产厂家
                      double Price;//价格
                     char* Valid_date;//有效期
                     int Left;//商品库存量
                      char* Addition;     //备注
                      int TransAcation  //交易状态
          */
          char name[MAXBYTE] = { 0 };
          char valid_date[MAXBYTE] = { 0 };
          char place[MAXBYTE] = { 0 };
          char type[MAXBYTE] = { 0 };
          char _operator[MAXBYTE] = { 0 };

          for (int i = 0; i < (int)strlen(data); ++i)
          {
                    if (data[i] == ',')
                    {
                              data[i] = ' ';
                    }
          }
          sscanf(data, " %s%d%s%s%lf%s%s",
                    name,
                    &newnode->Amount,
                    place,
                    valid_date,
                    &newnode->Price,
                    type,
                    _operator
          );

          if (strcmp(name, "") == 0)
          {
                    return phead;
          }

          newnode->Name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
          strcpy(newnode->Name, name);

          newnode->TransTime = (char*)malloc(sizeof(char) * (strlen(valid_date) + 1));
          strcpy(newnode->TransTime, valid_date);

          newnode->Place = (char*)malloc(sizeof(char) * (strlen(place) + 1));
          strcpy(newnode->Place, place);

          newnode->TranscationType = (char*)malloc(sizeof(char) * (strlen(type) + 1));
          strcpy(newnode->TranscationType, type);

          newnode->Operator = (char*)malloc(sizeof(char) * (strlen(_operator) + 1));
          strcpy(newnode->Operator, _operator);

          if (phead == NULL)   //不存在头节点
          {
                    phead = newnode;
          }
          else
          {
                    Transaction* temp = phead;
                    while (temp->pnext != NULL)
                    {
                              temp = temp->pnext;
                    }
                    temp->pnext = newnode;  ///链接
          }
          return phead;
}