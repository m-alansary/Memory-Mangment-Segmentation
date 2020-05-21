#ifndef HOLE_H
#define HOLE_H
#include<QString>

class hole
{
public:
    hole();
    void set_ID(int ID);
    int get_ID();
    void set_endAdress(int size);
    int get_endAdress();
    void set_StartingAddress(int StartingAddress);
    int get_StartingAddress();
    void set_name( QString name);
    QString get_name();
    void set_flag( int flag);
    int get_flag();
private:
    int ID;
    int flag;
    int endAdress;
    int StartingAddress;
    QString name;

};

#endif // HOLE_H
