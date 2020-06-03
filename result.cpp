#include "result.h"
#include "ui_result.h"
#include<QMessageBox>
#include<hole.h>
#include<QMessageBox>
#include<addprocess.h>
#include<QButtonGroup>
#include<vector>
#include<QDebug>
#include <map>
int p;
extern int MemorySize;

extern bool del;
extern int NumberOfHoles;
extern int flag;
extern  QString *temp1;
extern  QString *temp3;
extern int * temp2;
extern int  fla1;
extern std::list <hole> memory;
extern int NumberOfSegments;
extern std::list<QString> combox;
extern QString method;
extern std::vector<QString>names;
extern int processNumber;
extern std::vector <int> copy1;
extern std::vector <QString> ssize;
extern std::vector <int> pb;
extern int flag2;
std::list<hole > ::iterator it123;
bool p123=0;
bool p1234=0;
std::map<int,int> process;
std::map<int,int> procf;
bool fff=0;
bool bff=0;
bool wff=0;
int ff1=0;
int bf1=0;
int wf1=0;
extern std::vector <int> ff;
extern std::vector <int> bf;
extern std::vector <int> wf;
result::result(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::result)
{
    ui->setupUi(this);

    model1= new QStandardItemModel(0,1,this);
    model1->setHorizontalHeaderItem(0,new QStandardItem  ("Processes"));
    ui->tableView_2->setModel(model1);
    ui->tableView_2->setColumnWidth(0,190);
    //
    model= new QStandardItemModel(0,3,this);
    model->setHorizontalHeaderItem(0,new QStandardItem  ("segmant name"));
    model->setHorizontalHeaderItem(1,new QStandardItem  ("limit"));
    model->setHorizontalHeaderItem(2,new QStandardItem  ("base"));
    ui->tableView->setModel(model);


    scene = new QGraphicsScene(this);
    ui->draw->setScene(scene);
    ui->comboBox->addItem("None");
    QButtonGroup * buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->firstfit);
    buttonGroup->addButton(ui->bestfit);
    buttonGroup->addButton(ui->WorestFit);
    buttonGroup->setExclusive(true);
    ui->firstfit->setChecked(true);
    QFont Times1 ("Times",15,QFont::Bold);
    ui->firstfit->setFont(Times1);
    ui->bestfit->setFont(Times1);
    ui->WorestFit->setFont(Times1);
    if (combox.size()!=0)
    {
        for (std::list<QString>::iterator it=combox.begin();it != combox.end() ;it++)
        {
            ui->comboBox->addItem(*it);
        }
    }
    //  combox.clear();
    QBrush greenBrush (Qt::green);
    QBrush yellowBrush (Qt::yellow);
    QColor orange(255,165,0);
    QPainter p(this);
    QBrush orangeBursh(orange);
    QPen blackpen (Qt::black);
    blackpen.setWidth(2);
    int start_point =0;
    int count =1;
    int temp = MemorySize;
    while (temp/10){
        temp = temp/10;
        count++;
    }
    int size = memory.size();
    for (std::list<hole > ::iterator it = memory.begin();it != memory.end();it++)
    {
        if ((*it).get_flag()==-1)
        {
            rect=scene->addRect(20,start_point,250,((*it).get_endAdress()-(*it).get_StartingAddress()),blackpen,greenBrush);
            QString temp_str= (*it).get_name();
            QGraphicsTextItem *txtitem1 = new QGraphicsTextItem(temp_str);
            txtitem1->setPos(80,(start_point+((*it).get_endAdress()-(*it).get_StartingAddress())/2)-15);

            QFont  Times ("Times",10,QFont::Bold);
            txtitem1->setFont(Times);
            scene->addItem(txtitem1);
            temp_str=QString::number((*it).get_StartingAddress());
            QGraphicsTextItem *txtitem2= new QGraphicsTextItem(temp_str);
            txtitem2->setPos(QPointF(20-17*count,start_point-20));
            txtitem2->setFont(Times);
            scene->addItem(txtitem2);
            start_point = start_point+((*it).get_endAdress()-(*it).get_StartingAddress());
        }
        else if ((*it).get_flag() == 0)
        {
            rect=scene->addRect(20,start_point,250,((*it).get_endAdress()-(*it).get_StartingAddress()),blackpen,yellowBrush);
            QString temp_str=(*it).get_name();
            QGraphicsTextItem *txtitem1 = new QGraphicsTextItem(temp_str);
            txtitem1->setPos(QPointF(110,(start_point+((*it).get_endAdress()-(*it).get_StartingAddress())/2)-15));
            QFont Times ("Times",10,QFont::Bold);
            txtitem1->setFont(Times);
            scene->addItem(txtitem1);
            temp_str=QString::number((*it).get_StartingAddress());
            QGraphicsTextItem *txtitem2= new QGraphicsTextItem(temp_str);
            txtitem2->setPos(QPointF(20-17*count,start_point-20));
            txtitem2->setFont(Times);
            scene->addItem(txtitem2);
            start_point = start_point+((*it).get_endAdress()-(*it).get_StartingAddress());
        }
        else
        {
            rect=scene->addRect(20,start_point,250,((*it).get_endAdress()-(*it).get_StartingAddress()),blackpen,orangeBursh);
            QString temp_str = (*it).get_name();
            QGraphicsTextItem *txtitem1 = new QGraphicsTextItem(temp_str);
            txtitem1->setPos(QPointF(110,(start_point+((*it).get_endAdress()-(*it).get_StartingAddress())/2)-15));
            QFont Times ("Times",10,QFont::Bold);
            txtitem1->setFont(Times);
            scene->addItem(txtitem1);
            temp_str=QString::number((*it).get_StartingAddress());
            QGraphicsTextItem *txtitem2= new QGraphicsTextItem(temp_str);
            txtitem2->setPos(QPointF(20-17*count,start_point-20));
            txtitem2->setFont(Times);
            scene->addItem(txtitem2);
            start_point = start_point+((*it).get_endAdress()-(*it).get_StartingAddress());
        }
        if (size == 1)
        {

            QString temp_str = QString::number((*it).get_endAdress());
            QGraphicsTextItem *txtitem1 = new QGraphicsTextItem(temp_str);
            txtitem1->setPos(QPointF(20-17*count,(*it).get_endAdress()-20));
            QFont Times ("Times",10,QFont::Bold);
            txtitem1->setFont(Times);
            scene->addItem(txtitem1);
        }
        size --;
    }
}


result::~result()
{
    scene->clear();
    memory.clear();
    delete ui;

}


int c=0;
int h=0;
int l=0;

int row=-1;
int rrow=-1;
int segmr=-1;

void result::on_push_clicked()
{
    if(del)
    {
        row--;
        segmr-=l;
    }
    if(model1->rowCount()==0&&model->rowCount()==0&&c!=1)
    {
        int row=-1;
        int segmr=-1;
        row++;
        segmr++;
    }
    c++;
    row++;
    h++;
    rrow++;
    procf[h]=rrow;


    QString p ="p"+ QString::number(c);


    QString temp = ui->number->text();
    NumberOfSegments = temp.toInt();
    process[h]=NumberOfSegments;

    if (NumberOfSegments <= 0)
    {
        QMessageBox  message;
        message.setParent(this);
        message.setAutoFillBackground(true);
        message.setMinimumSize(1000,1000);
        message.setWindowTitle("Error");
        message.setText("something happened");
        message.setInformativeText("enter vaild number of segmants");
        message.setIcon(QMessageBox::Critical);
        message.setStandardButtons(QMessageBox::Ok);
        message.setDefaultButton(QMessageBox::Ok);
        ui->number->clear();
        message.exec();
    }
    else
    {
        model1->insertRow(row);
        ui->tableView_2->setRowHeight(row,50*NumberOfSegments);
        QModelIndex index =model1->index(row,0,QModelIndex());
        model1->setData(index,p);

        if (ui->firstfit->isChecked())
        {
            method = "firstfit";
            fff=1;
        }
        else if (ui->bestfit->isChecked())
        {
            method = "bestfit";
            bff=1;
        }
        else
        {
            method = "WorestFit";
            wff=1;
        }
        flag2=0;
        fla1=0;
        addprocess y (this);
        y.exec();

        if(!fla1)
        {



            for(unsigned int i=0;i<names.size();i++)
            {
                segmr++;


                model->insertRow(segmr,new QStandardItem(names[i]));
                QModelIndex index1=model->index(segmr,1,QModelIndex());
                QModelIndex index2=model->index(segmr,2,QModelIndex());
                model->setData(index1,ssize[i]);
                if(fff)
                {
                    model->setData(index2,ff[ff1]);
                    ff1++;
                }
                else if(bff)
                {
                    model->setData(index2,bf[bf1]);
                    bf1++;
                }
                else if(wff)
                {
                    model->setData(index2,wf[wf1]);
                    wf1++;
                }

                ui->tableView->setRowHeight(segmr,50);






            }

        }
        fff=0;
        bff=0;
        wff=0;

        //ff.clear();
        //bf.clear();
        //wf.clear();
        names.clear();
        ssize.clear();
        l=0;

        //
        delete[]temp1;
        delete[]temp2;
        delete[]temp3;

        if (flag2==1){

            ui->comboBox->addItem("P("+QString::number(processNumber)+")");
            scene->clear();
            QBrush greenBrush (Qt::green);
            QBrush yellowBrush (Qt::yellow);
            QColor orange(255,165,0);
            QBrush orangeBursh(orange);
            QPen blackpen (Qt::black);
            blackpen.setWidth(2);
            int start_point =0;
            int count =1;
            int temp = MemorySize;
            while (temp/10){
                temp = temp/10;
                count++;
            }
            int size = memory.size();
            for (std::list<hole > ::iterator it = memory.begin();it != memory.end();it++)
            {
                if ((*it).get_flag()==-1)
                {
                    rect=scene->addRect(20,start_point,250,((*it).get_endAdress()-(*it).get_StartingAddress()),blackpen,greenBrush);
                    QString temp_str= (*it).get_name();
                    QGraphicsTextItem *txtitem1 = new QGraphicsTextItem(temp_str);
                    txtitem1->setPos(QPointF(80,(start_point+((*it).get_endAdress()-(*it).get_StartingAddress())/2)-15));
                    QFont Times ("Times",10,QFont::Bold);
                    txtitem1->setFont(Times);
                    scene->addItem(txtitem1);
                    temp_str=QString::number((*it).get_StartingAddress());
                    QGraphicsTextItem *txtitem2= new QGraphicsTextItem(temp_str);
                    txtitem2->setPos(QPointF(20-17*count,start_point-20));
                    txtitem2->setFont(Times);
                    scene->addItem(txtitem2);
                    start_point = start_point+((*it).get_endAdress()-(*it).get_StartingAddress());
                }
                else if ((*it).get_flag() == 0)
                {
                    rect=scene->addRect(20,start_point,250,((*it).get_endAdress()-(*it).get_StartingAddress()),blackpen,yellowBrush);
                    QString temp_str=(*it).get_name();
                    QGraphicsTextItem *txtitem1 = new QGraphicsTextItem(temp_str);
                    txtitem1->setPos(QPointF(110,(start_point+((*it).get_endAdress()-(*it).get_StartingAddress())/2)-15));
                    QFont Times ("Times",10,QFont::Bold);
                    txtitem1->setFont(Times);
                    scene->addItem(txtitem1);
                    temp_str=QString::number((*it).get_StartingAddress());
                    QGraphicsTextItem *txtitem2= new QGraphicsTextItem(temp_str);
                    txtitem2->setPos(QPointF(20-17*count,start_point-20));
                    txtitem2->setFont(Times);
                    scene->addItem(txtitem2);
                    start_point = start_point+((*it).get_endAdress()-(*it).get_StartingAddress());
                }
                else
                {
                    rect=scene->addRect(20,start_point,250,((*it).get_endAdress()-(*it).get_StartingAddress()),blackpen,orangeBursh);
                    QString temp_str =(*it).get_name();
                    QGraphicsTextItem *txtitem1 = new QGraphicsTextItem(temp_str);
                    txtitem1->setPos(QPointF(110,(start_point+((*it).get_endAdress()-(*it).get_StartingAddress())/2)-15));
                    QFont Times ("Times",10,QFont::Bold);
                    txtitem1->setFont(Times);
                    scene->addItem(txtitem1);
                    temp_str=QString::number((*it).get_StartingAddress());
                    QGraphicsTextItem *txtitem2= new QGraphicsTextItem(temp_str);
                    txtitem2->setPos(QPointF(20-17*count,start_point-20));
                    txtitem2->setFont(Times);
                    scene->addItem(txtitem2);
                    start_point = start_point+((*it).get_endAdress()-(*it).get_StartingAddress());
                }
                if (size == 1)
                {

                    QString temp_str = QString::number((*it).get_endAdress());
                    QGraphicsTextItem *txtitem1 = new QGraphicsTextItem(temp_str);
                    txtitem1->setPos(QPointF(20-17*count,(*it).get_endAdress()-20));
                    QFont Times ("Times",10,QFont::Bold);
                    txtitem1->setFont(Times);
                    scene->addItem(txtitem1);
                }
                size --;

            }
        }
        del=0;
    }

}

void result::on_deallocate_clicked()
{

    ui->push->hide();
    if (ui->comboBox->currentText()== "None")
    {
        QMessageBox  message;
        message.setParent(this);
        message.setAutoFillBackground(true);
        message.setMinimumSize(1000,1000);
        message.setWindowTitle("Error");
        message.setText("something happened");
        message.setInformativeText("enter vaild process to be deallocated");
        message.setIcon(QMessageBox::Critical);

        message.exec();

        ui->push->show();
    }
    else {

        QString temp =  ui->comboBox->currentText();
        ui->comboBox->removeItem(ui->comboBox->currentIndex());
        QStringRef sub(&temp,0,2);
        int num=0;
        if (sub !="P(")
        {
            QStringRef subString(&temp,13,temp.size()-14);
            num = subString.toInt();
            for (std::list<hole > ::iterator it = memory.begin();it != memory.end();it++)
            {

                if (it->get_flag()==-1)
                {
                    QString temp = it->get_name();
                    QStringRef subtemp(&temp,13,temp.size()-14);
                    int tempcomparison = subtemp.toInt();
                    if (tempcomparison == num)
                    {
                        it->set_flag(0);
                        it->set_name("empty");
                        break;
                    }
                }
            }
        }
        else
        {
            int sum=0;
            del=1;
            QStringRef subtemp(&temp,2,temp.size()-3);

            p=subtemp.toInt();

            std::map<int,int>::iterator itll;
            itll=procf.find(p);

            model1->removeRow(procf[p]);
            if(itll!=procf.end()||itll!=procf.begin())
            {
                std::map<int,int>::iterator itlll=itll;
                for(itlll;itlll!=procf.end();itlll++)
                {
                    itlll->second--;
                }
                procf.erase(itll);
            }
            std::map<int,int>::iterator itl;
            if(itll==procf.begin())
            {
                for(itl=procf.begin();itl!=procf.end();itl++)
                {
                    itl->second --;
                }
                procf.erase(itll);
            }


            std::map<int,int>::iterator itp;
            std::map<int,int>::iterator itpp;

            itp=process.find(p);
            l=process[p];

            for (itpp=process.begin();itpp!=itp;itpp++)
            {
                sum+=itpp->second;
                qDebug()<<sum;
            }

            process.erase(itp);
            model->removeRows(sum,l,QModelIndex());


            int temptemp = subtemp.toInt();
            for (std::list<hole>::iterator it = memory.begin();it != memory.end();it++)
            {
                if(it->get_flag()==temptemp)
                {
                    it->set_flag(0);
                    it->set_name("empty");
                }
            }
            //int siztemptemp = memory.size();
            for (std::list<hole> ::iterator it = memory.begin();it != memory.end();it++)
            {
                std::list<hole > ::iterator it1 = it;
                int flagtemp = -1;
                int tempid = it->get_ID();
                //int startadd = it->get_endAdress();
                int endadd = it->get_endAdress();
                if(it->get_flag()==0)
                {
                    if (it ==  memory.end())
                    {
                        break;
                    }

                    it++;
                    flagtemp=0;
                    while ((it)->get_ID()==tempid && it->get_flag()==0 && it != memory.end()&& it->get_StartingAddress()==endadd)
                    {
                        std::list<hole > ::iterator temp = it;
                        endadd = temp->get_endAdress();
                        it++;
                        memory.erase(temp);

                    }
                }
                if (flagtemp == 0)
                {
                    it1->set_endAdress(endadd);
                }
                if (flagtemp==0)
                {
                    it--;
                }

            }

        }

    }
    scene->clear();
    QBrush greenBrush (Qt::green);
    QBrush yellowBrush (Qt::yellow);
    QColor orange(255,165,0);
    QBrush orangeBursh(orange);
    QPen blackpen (Qt::black);
    blackpen.setWidth(2);
    int start_point =0;
    int count =1;
    int temp = MemorySize;
    while (temp/10){
        temp = temp/10;
        count++;
    }
    int size = memory.size();
    for (std::list<hole > ::iterator it = memory.begin();it != memory.end();it++)
    {
        if ((*it).get_flag()==-1)
        {
            rect=scene->addRect(20,start_point,250,((*it).get_endAdress()-(*it).get_StartingAddress()),blackpen,greenBrush);
            QString temp_str= (*it).get_name();
            QGraphicsTextItem *txtitem1 = new QGraphicsTextItem(temp_str);
            txtitem1->setPos(QPointF(80,(start_point+((*it).get_endAdress()-(*it).get_StartingAddress())/2)-15));
            QFont Times ("Times",10,QFont::Bold);
            txtitem1->setFont(Times);
            scene->addItem(txtitem1);
            temp_str=QString::number((*it).get_StartingAddress());
            QGraphicsTextItem *txtitem2= new QGraphicsTextItem(temp_str);
            txtitem2->setPos(QPointF(20-17*count,start_point-20));
            txtitem2->setFont(Times);
            scene->addItem(txtitem2);
            start_point = start_point+((*it).get_endAdress()-(*it).get_StartingAddress());
        }
        else if ((*it).get_flag() == 0)
        {
            rect=scene->addRect(20,start_point,250,((*it).get_endAdress()-(*it).get_StartingAddress()),blackpen,yellowBrush);
            QString temp_str=(*it).get_name();
            QGraphicsTextItem *txtitem1 = new QGraphicsTextItem(temp_str);
            txtitem1->setPos(QPointF(110,(start_point+((*it).get_endAdress()-(*it).get_StartingAddress())/2)-15));
            QFont Times ("Times",10,QFont::Bold);
            txtitem1->setFont(Times);
            scene->addItem(txtitem1);
            temp_str=QString::number((*it).get_StartingAddress());
            QGraphicsTextItem *txtitem2= new QGraphicsTextItem(temp_str);
            txtitem2->setPos(QPointF(20-17*count,start_point-20));
            txtitem2->setFont(Times);
            scene->addItem(txtitem2);
            start_point = start_point+((*it).get_endAdress()-(*it).get_StartingAddress());
        }
        else
        {
            rect=scene->addRect(20,start_point,250,((*it).get_endAdress()-(*it).get_StartingAddress()),blackpen,orangeBursh);
            QString temp_str =(*it).get_name();
            QGraphicsTextItem *txtitem1 = new QGraphicsTextItem(temp_str);
            txtitem1->setPos(QPointF(110,(start_point+((*it).get_endAdress()-(*it).get_StartingAddress())/2)-15));
            QFont Times ("Times",10,QFont::Bold);
            txtitem1->setFont(Times);
            scene->addItem(txtitem1);
            temp_str=QString::number((*it).get_StartingAddress());
            QGraphicsTextItem *txtitem2= new QGraphicsTextItem(temp_str);
            txtitem2->setPos(QPointF(20-17*count,start_point-20));
            txtitem2->setFont(Times);
            scene->addItem(txtitem2);
            start_point = start_point+((*it).get_endAdress()-(*it).get_StartingAddress());
        }
        if (size == 1)
        {

            QString temp_str = QString::number((*it).get_endAdress());
            QGraphicsTextItem *txtitem1 = new QGraphicsTextItem(temp_str);
            txtitem1->setPos(QPointF(20-17*count,(*it).get_endAdress()-20));
            QFont Times ("Times",10,QFont::Bold);
            txtitem1->setFont(Times);
            scene->addItem(txtitem1);
        }
        size --;

    }
    //memory.clear();
    ui->push->show();
}







void result::on_pushButton_clicked()
{
    this->close();
}
