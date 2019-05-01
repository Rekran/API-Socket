#include <exception>
using namespace std;

class UnknownHostException : public exception
{
    public:
        UnknownHostException(string m): msg(m){}
        virtual const char* what() const throw()
        {
            return msg.c_str();
        }
        virtual ~UnknownHostException() throw(){}

    private:
        string msg;
};
