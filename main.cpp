#include "mainwindow.h"
#include <QApplication>
#include<hole.h>
#include<vector>
#include<list>
int MemorySize;
int NumberOfHoles;
int flag=0;
QString method;
std::list <hole> memory;
std::list<QString> combox;
std::vector<QString>names;
std::vector <QString> ssize;
std::vector <int> ff;
std::vector <int>bf;
std::vector <int> wf;
std::vector <int> pb;
bool del =0;
int NumberOfSegments;
int processNumber =0;
QString * temp1;
QString * temp3;
int * temp2;
std::vector<int> copy1;
int flag2=0;
int fla=0;
int fla1=0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
