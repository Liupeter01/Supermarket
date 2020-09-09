#include"Sales.h"

void InitSales()//加载基本的销售信息
{
          if (_access("ware_base.dat", 0) == -1)    //判断文件是否存在
          {
                    printf("尚未创建基本的商品目录、请先选择1\n");
                    return;
          }
          /*从基本信息表文件中获得商品名称，用于信息的比较*/
          Commodity* compare = NULL;  //用于从基本信息表中添加信息
          FILE* pfr = fopen("ware_base.dat", "r");
          printf("----------即将列出所有的可以销售的物品清单-------\n\n");
          while (!feof(pfr))
          {
                    char* temp = (char*)calloc(MAXBYTE, sizeof(char));
                    fgets(temp, MAXBYTE, pfr);
                    printf("%s", temp);
                    compare = LoadMem(compare, temp);
          }
          fclose(pfr);
          /*内存加载完成*/
          printf("\n-----------------------------------------------------------------\n");
          Transaction* saling = NULL;   //采购结构体的头节点
          while (1)
          {
                    saling = SalesAddNodeFromTail(saling, compare);
                    if (saling == NULL)
                    {
                              printf("数据载入异常，请先创建商品的基本信息\n");
                              FreeCommodityMemory(compare);
                              break;
                    }

                    printf("请问是否还需要添加销售信息(Y/N)：");
                    getchar();
                    char c = getchar();
                    if (c == 'N')
                    {
                              printf("请问是否将商品流水写入到文件(Y/N)：");
                              getchar();
                              if ((c = getchar()) == 'Y')
                              {
                                        WriteBankCardFile(saling);   //将采购信息写入流水
                                        UpdateBothFile(saling, compare);  //更新基本信息文件
                              }
                              printf("即将返回首页!\n");
                              FreeCommodityMemory(compare);
                              FreeTransMemory(saling);
                              break;
                    }
          }
}

static Commodity* LoadMem(Commodity* phead, char* data)
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


/*
*商品的销售信息
* 参数1，phead作为采购信息链表的头节点
* 参数2，compare用于比较在商品信息中是否存在此商品
* 如果商品存在才可以进行添加
*/
Transaction* SalesAddNodeFromTail(Transaction* phead, Commodity* compare)
{
          if (phead == NULL && compare == NULL)
          {
                    printf("数据加载失败\n");
                    return NULL;
          }
          else
          {
                    Transaction* newnode = (Transaction*)malloc(sizeof(Transaction));  //创建第一个节点
                    newnode->pnext = NULL;
                    printf("请输入商品的销售信息\n");
                    char* temp = (char*)malloc(sizeof(char) * MAXBYTE);  //临时缓冲区
                    printf("请输入商品名称：");
                    scanf("%s", temp);

                    /*
                    *查询是否商品重名
                    */
                    int status = 0;
                    struct  Commodity* ptemp = compare;
                    while (1)
                    {
                              if ((ptemp == NULL))
                              {
                                        break;
                              }

                              if (!strcmp(ptemp->Name, temp))   //在数据中查询到了商品名称
                              {
                                        status = 1;
                                        break;
                              }
                              ptemp = ptemp->pnext;
                    }
                    if (!status || ptemp == NULL)
                    {
                              printf("没有此商品的名称信息记录不可操作\n");
                              return phead;
                    }

                    /*
                   *以下操作将会添加商品的采购信息，并添加到链表的数据结构中
                    */
                    newnode->Name = (char*)calloc(sizeof(char), strlen(temp) + 1);
                    strcpy(newnode->Name, temp);
                    memset(temp, 0, MAXBYTE);

                    printf("请输入交易数量：");
                    scanf("%d", &newnode->Amount);

                    /*
                    *在此处检查交易数量与库存量的数量关系
                    */
                    if (newnode->Amount >= ptemp->Left)
                    {
                              printf("交易数量大于库存量，库存不足，请重新输入\n");
                              return phead;
                    }

                    while (1)
                    {
                              printf("请输入商品有效期(输入示例 年份-月份-日)：");
                              scanf("%s", temp);
                              char* px = temp;
                              int count = 0;
                              while (*px != '\0')
                              {
                                        if (*px == '-')
                                        {
                                                  ++count;
                                        }
                                        ++px;
                              }
                              if (count != 2)
                              {
                                        printf("输入日期错误请重新输入\n");
                              }
                              else
                              {
                                        break;
                              }
                    }
                    newnode->TransTime = (char*)calloc(sizeof(char), strlen(temp) + 1);
                    strcpy(newnode->TransTime, temp);
                    memset(temp, 0, MAXBYTE);

                    getchar();
                    printf("请输入交易地点：");
                    scanf("%[^\n]", temp);
                    newnode->Place = (char*)calloc(sizeof(char), strlen(temp) + 1);
                    strcpy(newnode->Place, temp);
                    memset(temp, 0, MAXBYTE);

                    newnode->TranscationType = (char*)calloc(sizeof(char), strlen("销售") + 1);
                    strcpy(newnode->TranscationType, "销售");

                    printf("请输入操作员信息：");
                    scanf("%s", temp);
                    newnode->Operator = (char*)calloc(sizeof(char), strlen(temp) + 1);
                    strcpy(newnode->Operator, temp);
                    memset(temp, 0, MAXBYTE);

                    /*
                      *交易金额可以自动的进行计算
                     */
                    newnode->Price = newnode->Amount * ptemp->Price;

                    if (phead == NULL)   //不存在头节点
                    {
                              phead = newnode;
                    }
                    else
                    {
                              struct Transaction* temp = phead;
                              while (temp->pnext != NULL)
                              {
                                        temp = temp->pnext;
                              }
                              temp->pnext = newnode;  ///链接
                    }

                    free(temp);  //清空数据缓冲区
          }
          return phead;
}