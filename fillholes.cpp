#include "fillholes.h"
#include "ui_fillholes.h"
#include<hole.h>
#include<QtCore>
#include<QDialog>
#include<QtGui>
#include<QMessageBox>
#include<delegate.h>
#include<QTableWidget>
#include<QTableView>
#include<algorithm>
#include<QString>
#include<vector>
extern int MemorySize;
extern int NumberOfHoles;
extern int flag;
extern std::list <hole > memory;
extern std::list<QString> combox;
FillHoles::FillHoles(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FillHoles)
{
    ui->setupUi(this);
         mydatalate = new Delegate();
         model = new QStandardItemModel(NumberOfHoles,2,this);
          model->setHorizontalHeaderItem(0,new QStandardItem ("starting address"));
          model->setHorizontalHeaderItem(1,new QStandardItem  ("size"));
          ui->table->setModel(model);
          ui->table->setItemDelegate(mydatalate);
         // ui->table->setColumnWidth(0,190);
         // ui->table->setColumnWidth(1,190);
}

FillHoles::~FillHoles()
{
    delete ui;
}
bool sort_holes( const std::vector<int>& v1,
               const std::vector<int>& v2 ) {
 return v1[1] < v2[1];
}
void FillHoles::on_submit_clicked()
{
    int i;

     std::vector< std::vector<int>>templist(NumberOfHoles,std::vector<int>(3));
            for ( i=0;i<NumberOfHoles;i++)
            {

                QModelIndex index = model->index(i,0,QModelIndex());
                QString value = ui->table->model()->data(index).toString();
                if (value == "")
                {
                    QMessageBox  message;
                    message.setMinimumSize(1000,1000);
                    message.setWindowTitle("ERROR");
                    message.setText("something wrong happened");
                    message.setInformativeText(" please , fill in the required data");
                    message.setIcon(QMessageBox::Critical);
                    message.setStandardButtons(QMessageBox::Ok);
                    message.setDefaultButton(QMessageBox::Ok);
                    message.exec();
                    break;
                }
                else {
                    int temp = value.toInt();
                     templist[i][0]= i;
                     templist[i][1]= temp;
                }
                index = model->index(i,1,QModelIndex());
               value = ui->table->model()->data(index).toString();
               if (value == "")
               {
                   QMessageBox  message;
                   message.setMinimumSize(1000,1000);
                   message.setWindowTitle("ERROR");
                   message.setText("something wrong happened");
                   message.setInformativeText(" please , fill in the required data");
                   message.setIcon(QMessageBox::Critical);
                   message.setStandardButtons(QMessageBox::Ok);
                   message.setDefaultButton(QMessageBox::Ok);
                   message.exec();
                   break;
               }
               else {
                   int temp = value.toInt();
                   templist[i][2]= temp;
                   if (templist[i][1]+templist[i][2] > MemorySize )// starting addrese + size akbr mn al size bta3 al memory
                   {
                       QMessageBox  message;
                       message.setMinimumSize(1000,1000);
                       message.setWindowTitle("ERROR");
                       message.setText("something wrong happened");
                       message.setInformativeText("not valid input , hole ("+QString::number(i)+" )get out of memory size");
                       message.textFormat();
                       message.setIcon(QMessageBox::Critical);
                       message.setStandardButtons(QMessageBox::Ok);
                       message.setDefaultButton(QMessageBox::Ok);
                       message.setStyleSheet("QLabel{height: 100px; min-height: 100px; max-height: 100;min-width: 300px;text-align: left;} QPushButton{ width:250px; font-size: 18px; }");
                       message.exec();
                       break;
                   }

                   if (i == NumberOfHoles-1)
                   {

                       int sum =0;
                       int count=0;
                       int count2=0;
                       std::sort(templist.begin(),templist.end(),sort_holes);
                       int tempend = templist[0][1]+templist[0][2];
                       for (int i=1;i<NumberOfHoles;i++)
                       {
                           if (templist[i][1]<tempend)
                           {
                               QMessageBox  message;
                               message.setMinimumSize(1000,1000);
                               message.setWindowTitle("ERROR");
                               message.setText("something wrong happened");
                               message.setInformativeText("not valid input ,overlapping of holes");
                               message.textFormat();
                               message.setIcon(QMessageBox::Critical);
                               message.setStandardButtons(QMessageBox::Ok);
                               message.setDefaultButton(QMessageBox::Ok);
                               message.setStyleSheet("QLabel{height: 100px; min-height: 100px; max-height: 100;min-width: 300px;text-align: left;} QPushButton{ width:250px; font-size: 18px; }");
                               message.exec();
                              return;

                           }
                           else {
                               tempend = templist[i][1];
                           }

                       }
                       flag=1;
                       for (int i=0;i<NumberOfHoles;i++)
                       {
                        int temp = templist[i][1];
                        if (sum <temp)
                        {
                            /*int *temp1 = new int [3];
                            temp1[0]= -1;
                            temp1[1]= sum;
                            temp1[2]= temp;
                            */
                            hole x ;
                            x.set_ID(count++);
                            x.set_flag(-1);
                            QString t="Old Process ("+QString::number(count2)+")";
                            x.set_name("Old Process ("+QString::number(count2++)+")");
                            x.set_StartingAddress(sum);
                            x.set_endAdress(temp);
                            sum = temp;
                            memory.push_back(x);
                            combox.push_back(t);

                        }
                        /*int* temp1 = new int [3];
                        temp1[0]=0;
                        temp1[1]= temp;
                        temp1[2]= temp+templist[1][2];
                        */
                          sum = temp + templist[i][2];
                          hole x ;
                          x.set_flag(0);
                          x.set_ID(count++);
                          x.set_name("empty");
                          x.set_endAdress(temp+templist[i][2]);
                          x.set_StartingAddress(temp);
                        memory.push_back(x);
                        if (i ==NumberOfHoles-1 )
                        {
                            if (templist[i][2]+templist[i][1]<MemorySize)
                               {
                               /*int * temp= new int [3];
                               temp[0]=-1;
                               temp[1]=templist[i][2];
                               temp[2]= MemorySize;
                               */
                               x.set_ID(count);
                               x.set_flag(-1);
                               x.set_endAdress(MemorySize);
                               x.set_StartingAddress(templist[i][2]+templist[i][1]);
                               x.set_name("Old Process ("+QString::number(count2)+")");
                               QString t="Old Process ("+QString::number(count2)+")";
                               combox.push_back(t);
                               count++;
                               memory.push_back(x);
                               templist.clear();
                               }
                        }

                       }


                       this->close();
                   }
                   }
            }
}
