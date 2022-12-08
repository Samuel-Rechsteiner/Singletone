#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <utility>
#include <map>
using namespace std;

class Storage
{
protected:
    map<string, string> data;

    Storage()
    {
        cout << "CONSTRUCT" << endl;
        // write in file
        ofstream file;
        file.open("data.txt");
        file << "Printer: Brother3400" << endl;
        file << "Computer: Dell" << endl;
        file.close();
    }

public:
    Storage(Storage &other) = delete;
    void operator=(const Storage &) = delete;

    ~Storage()
    {
        cout << "Destruct 1" << endl;

        // read from file
        ifstream file;
        file.open("data.txt");
        string line;
        while (getline(file, line))
        {
            cout << "Destruct 2" << endl;
            auto pos = line.find(":");
            data[line.substr(0, pos)] = line.substr(pos + 1);
        }
        file.close();
        cout << "Destruct 3" << endl;
    }

    void store(string key, string value)
    {
        data[key] = value;
    }
    string retrieve(string key, string value)
    {
        return data[key];
    }

    static Storage *get_instance()
    {
        static Storage *instance = nullptr;
        if (instance == nullptr)
        {
            instance = new Storage;
        }
        return instance;
    }
};

int main()
{
    auto storage = Storage::get_instance();
    auto storage2 = Storage::get_instance();
    storage->store("Printer", "Brother3400");
    cout << storage->get_instance() << endl;
    storage2->store("Computer", "Dell");
    cout << storage2->get_instance() << endl;

    return 0;
}