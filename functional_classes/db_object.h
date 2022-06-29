#ifndef DB_OBJECT_H
#define DB_OBJECT_H


class dbObject
{
public:
    //dbObject() {}

    virtual bool isInDb() = 0;
    virtual void addIntoDb() = 0;
    virtual void getFromDb() = 0;
    virtual int getId() = 0;
    virtual void deleteFromDb() = 0;
    virtual void update() = 0;

};

#endif // DB_OBJECT_H
