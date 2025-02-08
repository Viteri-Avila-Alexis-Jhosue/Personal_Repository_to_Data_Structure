# include <iostream>
# ifndef USER_H
# define USER_H
using namespace std;
class User
{
private:
    int id;
    string name;
    string lastName;
    string password;
public:
    User();
    User(int id,string name, string lastName, string password);
    string getName() const;
    void setName(string name);
    string getLastName() const;
    void setLastName(string lastName);
    string getPassword() const;
    void setPassword(string password);
    int getId() const;
    void setId(int id);
    void ingresar_datos();
    void guardar_en_archivo();
};
#endif