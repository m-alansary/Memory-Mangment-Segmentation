#include "addprocess.h"
#include "ui_addprocess.h"
#include<QtCore>
#include<QDialog>
#include<QtGui>
#include <QDialog>
#include<delegate.h>
#include <QKeyEvent>
#include<QTableWidget>
#include<QTableView>
#include<QMessageBox>
#include<hole.h>
#include <vector>
#include<QDebug>
extern int MemorySize;
extern int NumberOfHoles;
extern int NumberOfSegments;
extern int flag;
extern int fla;
extern bool del;
extern int flag2;
extern  QString *temp1;
extern  QString *temp3;
extern int * temp2;
extern int fla1;
extern std::list <hole> memory;
extern std::vector <int> copy1;
extern QString method;
extern int processNumber;
using std::list;
extern std::vector <QString> names;
extern std::vector <QString> ssize;
extern std::vector <int> ff;
extern std::vector <int> bf;
extern std::vector <int> wf;

addprocess::addprocess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addprocess)

{   ui->setupUi(this);
    temp1 = new QString[NumberOfSegments];
    temp2=new int [NumberOfSegments];
    temp3 =new QString[NumberOfSegments];
    mydatalate = new Delegate(this);
    model = new QStandardItemModel(NumberOfSegments,1,this);
    model->setHorizontalHeaderItem(0,new QStandardItem  ("size"));
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(mydatalate);
    ui->tableView->setColumnWidth(0,210);
    ui->tableView->setColumnWidth(1,210);

    mydelegate = new delegate2(this);
    model2 = new QStandardItemModel(NumberOfSegments,1,this);
    model2->setHorizontalHeaderItem(0,new QStandardItem  ("name"));
    ui->tableView_2->setModel(model2);
    ui->tableView_2->setItemDelegate(mydelegate);
    ui->tableView_2->setColumnWidth(0,190);
    ui->tableView_2->setColumnWidth(1,190);
}
int first_fit(list <hole> &memory, int * sizelist, QString * namelist,int NumberOFSgemnts,int ProcessNumber)
{
    list <hole> copy;
    int i = 0;

    copy.assign(memory.begin(),memory.end());
    for(i=0 ; i < NumberOFSgemnts; i++)
    {

        int count = 1;
        list<hole>::iterator it;
        for (it = copy.begin();it != copy.end();it++)
        {
            if(it->get_flag() == 0 && (it->get_endAdress() - it->get_StartingAddress() >= sizelist[i]))
            {
                int temp_endAdress = it->get_endAdress();
                it->set_StartingAddress(it->get_StartingAddress());
                //   copy1[i]=it->get_StartingAddress();
                it->set_endAdress(it->get_StartingAddress() + sizelist[i]);
                it->set_flag(ProcessNumber);
                it->set_name("P"+QString::number(ProcessNumber)+":"+namelist[i]);

                ff.push_back(it->get_StartingAddress());

                if (it->get_endAdress() !=temp_endAdress)
                {
                    hole h;
                    //accessing a new hole and set it's attributes
                    h.set_ID(it->get_ID());
                    h.set_name("empty");
                    h.set_flag(0);
                    h.set_StartingAddress(it->get_endAdress());
                    h.set_endAdress(temp_endAdress);
                    list<hole>::iterator it2 = copy.begin(); //define a new iterator to insert a hole
                    advance(it2,count);
                    copy.insert(it2,h);
                    break;
                }
                break;

            }
            count++;
        }
        if(it == copy.end())
        {
            //  copy1.assign(copy.begin(),memory.end());
            break;
        }
    }
    //if it loops over all the segments it mean they were successfully fitted
    if(i == NumberOFSgemnts){
        memory.assign(copy.begin(),copy.end());
        return 1;
    }
    else
        return -1;
}
bool hole_size(hole h1, hole h2)
{
    return ( (h1.get_endAdress() - h1.get_StartingAddress()) < (h2.get_endAdress() - h2.get_StartingAddress() ) );
}

int worest_fit(list <hole> &memory, int * sizelist, QString * namelist,int NumberOFSgemnts,int ProcessNumber)
{
    list <hole> copy;
    copy.assign(memory.begin(),memory.end());
    for(int i=0 ; i < NumberOFSgemnts; i++)
    {
        int index = -1;
        int sizetemp = 0;
        int count = 0;
        list<hole>::iterator it;
        for (it = copy.begin();it != copy.end();it++)
        {
            if(it->get_flag() == 0 && (it->get_endAdress() - it->get_StartingAddress() >= sizelist[i]) && ((it->get_endAdress() - it->get_StartingAddress())>sizetemp))
            {
                index = count;
                sizetemp =it->get_endAdress() - it->get_StartingAddress();
            }
            count++;
        }
        if (index ==-1)
        {
            wf.push_back(it->get_StartingAddress());
            return -1;
        }
        else
        {
            it = copy.begin();
            advance(it,index);
            int temp_endAdress = it->get_endAdress();
            //it->set_StartingAddress(it->get_StartingAddress());
            it->set_endAdress(it->get_StartingAddress() + sizelist[i]);
            //    copy1[i]=it->get_StartingAddress();
            it->set_flag(ProcessNumber);
            it->set_name("P"+QString::number(ProcessNumber)+":"+namelist[i]);
            wf.push_back(it->get_StartingAddress());
            if (it->get_endAdress() !=temp_endAdress)
            {
                hole h;
                //accessing a new hole and set it's attributes
                h.set_ID(it->get_ID());
                h.set_name("empty");
                h.set_flag(0);
                h.set_StartingAddress(it->get_endAdress());
                h.set_endAdress(temp_endAdress);
                list<hole>::iterator it2 = copy.begin(); //define a new iterator to insert a hole
                index++;
                advance(it2,index);
                copy.insert(it2,h);
            }
        }

    }
    memory.assign(copy.begin(),copy.end());
    return 1;
}

int best_fit(list <hole> &memory, int * sizelist, QString * namelist,int NumberOFSgemnts,int ProcessNumber)
{
    list <hole> copy;
    copy.assign(memory.begin(),memory.end());
    for(int i=0 ; i < NumberOFSgemnts; i++)
    {
        int index = -1;
        int sizetemp = MemorySize+1000;
        int count = 0;
        list<hole>::iterator it;
        for (it = copy.begin();it != copy.end();it++)
        {
            if(it->get_flag() == 0 && (it->get_endAdress() - it->get_StartingAddress() >= sizelist[i]) && ((it->get_endAdress() - it->get_StartingAddress())<sizetemp))
            {
                index = count;
                sizetemp =it->get_endAdress() - it->get_StartingAddress();
            }
            count++;
        }
        if (index ==-1)
        {
            bf.push_back(it->get_StartingAddress());
            return -1;
        }
        else
        {
            it = copy.begin();
            advance(it,index);
            int temp_endAdress = it->get_endAdress();
            //it->set_StartingAddress(it->get_StartingAddress());
            //   copy1[i]=it->get_StartingAddress();
            it->set_endAdress(it->get_StartingAddress() + sizelist[i]);
            it->set_flag(ProcessNumber);
            it->set_name("P"+QString::number(ProcessNumber)+":"+namelist[i]);
            bf.push_back(it->get_StartingAddress());
            if (it->get_endAdress() !=temp_endAdress)
            {
                hole h;
                //accessing a new hole and set it's attributes
                h.set_ID(it->get_ID());
                h.set_name("empty");
                h.set_flag(0);
                h.set_StartingAddress(it->get_endAdress());
                h.set_endAdress(temp_endAdress);
                list<hole>::iterator it2 = copy.begin(); //define a new iterator to insert a hole
                index++;
                advance(it2,index);
                copy.insert(it2,h);
            }
        }

    }
    memory.assign(copy.begin(),copy.end());
    return 1;
}
addprocess::~addprocess()
{
    delete ui;
}

void addprocess::on_push_clicked()
{
    fla1=0;
    //    QString * temp1 = new QString[NumberOfSegments];
    //    int * temp2  = new int[NumberOfSegments];
    //    QString * temp3 = new QString[NumberOfSegments];
    for (int i=0;i<NumberOfSegments;i++)
    {
        QModelIndex index1 = model2->index(i,0,QModelIndex());
        QModelIndex index2 = model->index(i,0,QModelIndex());
        QString value1 = ui->tableView_2->model()->data(index1).toString();
        QString value2 = ui->tableView->model()->data(index2).toString();
        if (value1 == "")
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
        else
        {
            temp1[i]= value1;
        }
        if (value2 == "")
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
        else
        {
            temp3[i]=value2;
            temp2[i]= value2.toInt();
        }
        if (i == NumberOfSegments-1)
        {
            fla=1;
            for(int i =0;i<NumberOfSegments;i++)
            {
                names.push_back(temp1[i]);
                ssize.push_back(temp3[i]);
            }
        }
    }

    if(fla==1)
    {
        processNumber++;
        if (method == "firstfit")
        {
            if (first_fit(memory,temp2,temp1,NumberOfSegments,processNumber) == -1)
            {
                QMessageBox  message;
                message.setMinimumSize(1000,1000);
                message.setWindowTitle("ERROR");
                message.setText("NO ENOUGH MEMORY !! ");
                message.setInformativeText("process cann't fit in memory !");
                message.setIcon(QMessageBox::Critical);
                message.setStandardButtons(QMessageBox::Ok);
                message.setDefaultButton(QMessageBox::Ok);
                message.exec();

            }
            else {
                flag2 =1;
            }
        }
        else if (method == "bestfit")
        {
            if (best_fit(memory,temp2,temp1,NumberOfSegments,processNumber)==-1){
                QMessageBox  message;
                message.setMinimumSize(1000,1000);
                message.setWindowTitle("ERROR");
                message.setText("something wrong happened");
                message.setInformativeText(" process cann't fit in memory");
                message.setIcon(QMessageBox::Critical);
                message.setStandardButtons(QMessageBox::Ok);
                message.setDefaultButton(QMessageBox::Ok);
                message.exec();

            }
            else {
                {
                    flag2 =1;

                }
            }
        }
        else
        {
            if( worest_fit(memory,temp2,temp1,NumberOfSegments,processNumber)==-1){

                QMessageBox  message;
                message.setMinimumSize(1000,1000);
                message.setWindowTitle("ERROR");
                message.setText("something wrong happened");
                message.setInformativeText(" process cann't fit in memory");
                message.setIcon(QMessageBox::Critical);
                message.setStandardButtons(QMessageBox::Ok);
                message.setDefaultButton(QMessageBox::Ok);
                message.exec();

            }
            else {
                flag2 =1;
            }
        }
        this->close();
    }
}
