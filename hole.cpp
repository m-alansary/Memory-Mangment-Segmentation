#include "hole.h"

hole::hole()
{
}
void hole :: set_ID(int ID)
{
    this->ID= ID;
}
int hole :: get_ID(){
    return this->ID;
}
void hole ::set_endAdress(int size){
    this->endAdress= size;
}
int hole ::get_endAdress(){
    return endAdress;
}
void hole ::set_StartingAddress(int StartingAddress)
{
    this->StartingAddress = StartingAddress;
}
int  hole ::get_StartingAddress(){
    return this->StartingAddress;
}
void hole ::set_name( QString name){
    this->name=name;
}
QString  hole ::get_name(){
    return name;
}
void hole ::set_flag( int flag){
    this->flag = flag;
}
int hole :: get_flag(){
    return flag;
}
