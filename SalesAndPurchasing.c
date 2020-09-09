#include"SalesAndPurchasing.h"

/*
*更新商品的基本的数量信息
* 同时更新两个文件ware_base.dat，bankcard_base.dat
*/
void UpdateBothFile(struct Transaction* phead, struct  Commodity* compare)
{
          struct Transaction* p1 = phead;
          struct  Commodity* p2 = compare;

          while (p1 != NULL)
          {
                    while (p2 != NULL)
                    {
                              if (!strcmp(p1->Name, p2->Name))  //寻找商品的名称是否匹配
                              {
                                        if (!strcmp(p1->TranscationType, "销售"))   //区分商品交易类型，来选择增加还是减少
                                        {
                                                  p2->Left -= p1->Amount;
                                                  p1->TempoaryItemCount = p2->Left;
                                                  p2->TransAcation = 1;//修改交易状态
                                        }
                                        else if (!strcmp(p1->TranscationType, "采购")) //区分商品交易类型，来选择增加还是减少
                                        {
                                                  p2->Left += p1->Amount;
                                                  p1->TempoaryItemCount = p2->Left;
                                                  p2->TransAcation = 1;  //修改交易状态
                                        }
                              }
                              p2 = p2->pnext;
                    }
                    p1 = p1->pnext;
          }

          p1 = phead;
          FILE *bankcard = fopen("bankcard_base.dat", "w");
          while (p1!=NULL)
          {
                    if (0)
                    {
                              continue;
                    }
                    else
                    {
                              fprintf(bankcard, "%s,%d,%s,%s,%.2lf,%s,%s,%d\n",
                                        p1->Name,
                                        p1->Amount,
                                        p1->TransTime,
                                        p1->Place,
                                        p1->Price,
                                        p1->TranscationType,
                                        p1->Operator,
                                        p1->TempoaryItemCount   //当前库存余量
                              );
                              p1 = p1->pnext;
                    }
          }
          fclose(bankcard);

          p2 = compare;
          FILE* pfw = fopen("ware_base.dat", "w");
          while (p2!= NULL)
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
}

/*将商品信息写入到文件之中bankcard_deal.dat*/
void WriteBankCardFile(struct Transaction* phead)
{
          FILE* pfw = fopen("bankcard_deal.dat", "a+");   //可附加模式
          struct Transaction* ptemp = phead;
          while (ptemp!=NULL)
          {
                    fprintf(pfw, "%s,%d,%s,%s,%.2lf,%s,%s\n",
                              ptemp->Name,
                              ptemp->Amount,
                              ptemp->Place,
                              ptemp->TransTime,
                              ptemp->Price,
                              ptemp->TranscationType,
                              ptemp->Operator
                    );
                    ptemp = ptemp->pnext;
          }
          fclose(pfw);
          printf("OK");
}