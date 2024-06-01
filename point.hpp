class Point
{
private:
    unsigned int x, y;
public:
    Point();
    virtual ~Point();

    virtual unsigned int getX();
    virtual unsigned int getY();
};
