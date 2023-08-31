#include"data_structure.h"
#include"init.h"

Commodity* Head = NULL;//创建头结点

/*
*商品信息录入模块
*/
void InitCommdity()   //录入商品的信息
{
          if (_access("ware_base.dat", 0) != -1)    //判断文件是否存在
          {       
                    /*文件不存在将所有的信息加载入内存*/
                    /*从基本信息表文件中获得商品名称，用于信息的比较*/
                    FILE* pfr = fopen("ware_base.dat", "r");
                    printf("----------即将列出所有的基本商品信息表中已有的内容-------\n\n");
                    while (!feof(pfr))
                    {
                              char* temp = (char*)calloc(MAXBYTE, sizeof(char));
                              fgets(temp, MAXBYTE, pfr);     
                              printf("%s", temp);
                              Head = LoadMem(Head, temp);
                    }
                    fclose(pfr);
                    /*内存加载完成*/
                    printf("\n-----------------------------------------------------------------\n");
          }
          while (1)
          {
                    Head = AddNodeFromTail(Head);
                    printf("请问是否还需要添加商品(Y/N)：");
                    getchar();
                    char c = getchar();
                    if (c == 'N')
                    {
                              printf("请问是否存储数据(Y/N)：");
                              getchar();
                              if ((c = getchar()) == 'Y')
                              {
                                        WriteToFile(Head);   //如果确定存储，则将信息写入文件
                              }
                              printf("即将返回首页：\n");
                              FreeCommodityMemory(Head);
                              break;
                    }
          }
          
}

/*
*基本商品信息
*/
Commodity* AddNodeFromTail(Commodity* phead)   
{
          Commodity* newnode = (Commodity*)malloc(sizeof(Commodity));  //创建第一个节点
          newnode->pnext = NULL;
          printf("请输入商品的基本信息\n");
          char* temp = (char*)malloc(sizeof(char) * MAXBYTE);  //临时缓冲区
          printf("请输入商品名称：");
          scanf("%s", temp);

          if (phead != NULL)
          {
                    /*查询是否商品重名*/
                    struct Commodity* ptemp = phead;
                    while (ptemp != NULL)
                    {
                              if (!strcmp(ptemp->Name, temp))
                              {
                                        printf("商品名称重名，不可以保存\n");
                                        return phead;
                              }
                              else
                              {
                                        ptemp = ptemp->pnext;
                              }
                    }
          }
      
          newnode->Name = (char*)calloc(sizeof(char), strlen(temp) + 1);
          strcpy(newnode->Name, temp);
          memset(temp, 0, MAXBYTE);

          printf("请输入商品种类：");
          scanf("%s", temp);
          newnode->Variety = (char*)calloc(sizeof(char), strlen(temp) + 1);
          strcpy(newnode->Variety, temp);
          memset(temp, 0, MAXBYTE);

          printf("请输入商品生产厂家：");
          scanf("%s", temp);
          newnode->Manufacture = (char*)calloc(sizeof(char), strlen(temp) + 1);
          strcpy(newnode->Manufacture, temp);
          memset(temp, 0, MAXBYTE);

          printf("请输入商品价格：");
          scanf("%lf", &newnode->Price);

          while (1)
          {
                    printf("请输入商品有效期(输入示例 年份-月份-日)：");            //这里有个输入bug没有排除，比方说输入20018--25就不行了
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
         
          newnode->Valid_date = (char*)calloc(sizeof(char), strlen(temp) + 1);
          strcpy(newnode->Valid_date, temp);
          memset(temp, 0, MAXBYTE);

          printf("请输入商品库存量：");
          scanf("%d", &newnode->Left);

          printf("请输入商品备注：");
          scanf("%s", temp);
          newnode->Addition = (char*)calloc(sizeof(char), strlen(temp) + 1);
          strcpy(newnode->Addition, temp);

          newnode->TransAcation = 0;  //还没有交易信息

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
          free(temp);  //清空数据缓冲区
          return phead;
}

void WriteToFile(struct Commodity* phead)  //将商品基本信息写入到文件之中 ware_base.dat
{
          FILE* pfw = fopen("ware_base.dat", "w");
          struct Commodity* ptemp = phead;
          while (1)
          {
                    fprintf(pfw, "%s,%s,%s,%lf,%s,%d,%s,%d\n",
                              ptemp->Name,
                              ptemp->Variety,
                              ptemp->Manufacture,
                              ptemp->Price,
                              ptemp->Valid_date,
                              ptemp->Left,
                              ptemp->Addition,
                              ptemp->TransAcation
                    );

                    if (ptemp->pnext == NULL)
                    {
                              break;
                    }
                    else
                    {
                              ptemp = ptemp->pnext;
                    }

          }
          fclose(pfw);
}

/*链表内存释放工具*/
void FreeTransMemory(struct Transaction* phead)
{
          struct Transaction* p1 = phead;
          struct  Transaction* p2 = NULL;
          while (p1 != NULL)
          {
                    p2 = p1;
                    p1 = p1->pnext;  
                    free(p2);
          }
}

void FreeCommodityMemory(struct Commodity* phead)
{
          struct Commodity* p1 = phead;
          struct Commodity* p2 = NULL;
          while (p1 != NULL)
          {
                    p2 = p1;
                    p1 = p1->pnext;
                    free(p2);
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
