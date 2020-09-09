#include"EditAndDelete.h"

void InitEditAndDelete()//初始化编辑与删除
{
          if (_access("ware_base.dat", 0) == -1)    //判断文件是否存在
          {
                    printf("尚未创建基本的商品目录、请先选择1\n");
                    return;
          }
          /*从基本信息表文件中获得商品名称，用于信息的比较*/
          struct Commodity* compare = NULL;  //用于从基本信息表中添加信息
          FILE* pfr = fopen("ware_base.dat", "r");
          while (!feof(pfr))
          {
                    char* temp = (char*)calloc(MAXBYTE, sizeof(char));
                    fgets(temp, MAXBYTE, pfr);
                    printf("%s", temp);
                    compare = LoadMem(compare, temp);
          }
          fclose(pfr);
          /*内存加载完成*/

          while (1)
          {
                    char* px[2] = { "删除","修改" };
                    printf("\n请选择功能：(1删除、2修改、0退出)：");
                    int i = 0;
                    scanf("%d", &i);

                    char target[MAXBYTE] = { 0 };  //用于存放查找的商品名称
                    if (i == 1)
                    {
                              printf("请输入要%s商品的名称：", px[i - 1]);
                              scanf("%s", target);
                              compare = Delete(compare, target);  //调用删除函数
                              printf("删除成功!\n");
                    }
                    else if (i == 2)
                    {
                              printf("请输入要%s商品的名称：", px[i - 1]);
                              scanf("%s", target);
                              compare = Edit(compare, target);  //调用编辑函数
                              printf("修改成功!\n");
                    }
                    else if (i == 0)
                    {
                              break;
                    }
                    else
                    {
                              printf("输入错误\n");
                    }
          }
         
          /*
          *直接更新文件
          */
          FILE* pfw = fopen("ware_base.dat", "w");
          struct Commodity* p2 = compare;
          while (p2 != NULL)
          {
                    fprintf(pfw, "%s,%s,%s,%.2lf,%s,%d,%s,%d\n",
                              p2->Name,
                              p2->Variety,
                              p2->Manufacture,
                              p2->Price,
                              p2->Valid_date,
                              p2->Left,
                              p2->Addition,
                              p2->TransAcation  //交易状态
                    );
                    p2 = p2->pnext;
          }
          fclose(pfw);
          FreeCommodityMemory(compare);
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

Commodity* Delete(Commodity* phead,char*data)
{
          Commodity* p1 = phead;
          Commodity* p2 = NULL;

          int status = 0;

          while (p1 != NULL)
          {
                    if (strcmp(p1->Name, data)!=0)
                    {
                              p2 = p1;
                              p1 = p1->pnext;
                    }
                    else
                    {
                              status = 1;
                              break;
                    }
          }
          
          if (status != 1)
          {
                    printf("商品没有被找到\n");
                    return phead;
          }
          else
          {
                    if (!p1->TransAcation)
                    {
                              if (p1 == phead)   //p1是头节点
                              {
                                        phead = phead->pnext;
                                        free(p1->Name);
                                        free(p1->Variety);
                                        free(p1->Valid_date);
                                        free(p1->Manufacture);
                                        free(p1->Addition);
                                        free(p1);
                                        return phead;
                              }
                              else
                              {
                                        p2->pnext = p1->pnext;
                                        free(p1->Name);
                                        free(p1->Variety);
                                        free(p1->Valid_date);
                                        free(p1->Manufacture);
                                        free(p1->Addition);
                                        free(p1);
                                        return phead;
                              }
                    }
                    else
                    {
                              printf("当前商品已有交易信息时，不能删除!\n");
                              return phead;
                    }
          }      
}

Commodity* Edit(Commodity* phead, char* data)
{
          Commodity* p1 = phead;
          int status = 0;

          while (p1 != NULL)
          {
                    if (strcmp(p1->Name, data) != 0)
                    {
                              p1 = p1->pnext;
                    }
                    else
                    {
                              status = 1;
                              break;
                    }
          }
          if (!status)
          {
                    printf("商品没有被找到\n");
                    return phead;
          }
          else
          {
                    printf("\n请输入需要修改的内容(1商品种类、2生产厂家、3价格、4有效期、5备注)：");
                    char temp[MAXBYTE]={0};
                    int choice = -1;
                    scanf("%d", &choice);
                    if (choice == 1)  //商品种类
                    {
                              printf("请输入修改的新内容：");
                              scanf("%s", temp);
                              free(p1->Variety);
                              p1->Variety = (char*)malloc(sizeof(char) * (strlen(temp) + 1));
                              strcpy(p1->Variety, temp);
                    }
                    else if (choice == 2)//生产厂家
                    {
                              printf("请输入修改的新内容：");
                              scanf("%s", temp);
                              free(p1->Manufacture);
                              p1->Manufacture = (char*)malloc(sizeof(char) * (strlen(temp) + 1));
                              strcpy(p1->Manufacture, temp);
                    }
                    else if (choice == 3)//价格
                    {
                              printf("请输入修改的新内容：");
                              scanf("%lf", &p1->Price);
                    }
                    else if (choice == 4)//有效期
                    {
                              free(p1->Valid_date);
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
                              p1->Valid_date = (char*)malloc(sizeof(char) * (strlen(temp) + 1));
                              strcpy(p1->Valid_date, temp);
                    }
                    else if (choice == 5)//备注
                    {
                              printf("请输入修改的新内容：");
                              scanf("%s", temp);
                              free(p1->Addition);
                              p1->Addition = (char*)malloc(sizeof(char) * (strlen(temp) + 1));
                              strcpy(p1->Addition, temp);
                    }
                    else if(choice<1 || choice>5)
                    {
                              printf("输入错误\n");
                    }
                    return phead;
          }
}