#include "Users.h"

using namespace npl;

//validate client registration
map<string,string> Users::getUsersAndPasswords() {
    return this->usersAndPasswords;
};

//constructor
Users::Users(string path){
    this->filePath = path;
};

//registration for new user
bool Users::addNewUser(string user,string password){
    string nameuser = user;
    string passworduser = password;
    //validate user registration (not already exists)
    for (map<string, string>::iterator it = this->usersAndPasswords.begin();
         it != this->usersAndPasswords.end(); ++it) {
        if (it->first == nameuser){
            cout <<"The client " << "'"<< it->first << "'" << " is already exist" <<  endl;
            return false;
        }
    }

    //adding the new user to the list
    this->usersAndPasswords.insert(pair<string,string>(nameuser,passworduser));

    //writing to file
    ofstream out;
    out.open(this->filePath.c_str() ,ios::app | ios::out);
    out << nameuser << endl;
    out.flush();
    out << passworduser<< endl;
    out.flush();
    out.close();
    return true;
};

//uploading the file to ram
map<string,string> Users::loadAllUserFromFile(){

    ifstream nameFileout;
    nameFileout.open(this->filePath.c_str(), ios::in);
    if (nameFileout) {
        string user;
        string password;
        map<string, string> map;

        while (std::getline(nameFileout, user) && getline(nameFileout, password)) {
            this->usersAndPasswords.insert(pair<string, string>(user, password));
        }
    }
    //closing the file on hard drive
    nameFileout.close();

    return this->usersAndPasswords;
};
