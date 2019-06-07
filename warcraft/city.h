#ifndef __CITY_H__
#define __CITY_H__

class City
{
public:
    City() {}
    ~City() {}
    int getId(){
        return _id;
    }
private:
int _id;//id>0&&id<=20
};

#endif
