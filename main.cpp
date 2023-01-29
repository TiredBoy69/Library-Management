#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

vector<string> UserName;
vector<string> PassWord;
int idLogin;

struct Member
{
    int id;
    string userName, passWord, firstName, lastName, phoneNumber;
};
struct Book
{
    int id;
    string name, author, genre;
};
void giveBackBook();
bool searchByTitle();
bool searchByAuthor();
bool searchByGenre();
void myBook();
void showBorrowedBook();
void getIdLogin(string user);
void borrowBook();
void pushTOVectorUser();
void pushTOVectorPass();
void showMemberProfile(string user);
void readInfoAdmin(int &user, int &pass);
void memberRegister();
void selectedBook();
void editBook();
bool wrongUserName(string person);
void changeInfoAdmin();
void changeInfoMember();
void showMember();
void memberMenu();
int lastBookId();
int lastMemberId();
void memberLogin();
void manageMember();
void adminLogin();
void manageBooks();
void managerMenu();
void addNewBook();
void showBooks();
void removeBook();
void mainMenu();

int main()
{
    pushTOVectorPass();
    pushTOVectorUser();
    mainMenu();
}
void mainMenu()
{
    cout << "WELCOME TO OUR LIBRARY:)))))"
         << "\n"
         << "\n";
    cout << "1. Member Login..."
         << "\n";
    cout << "2. Member Registraion..."
         << "\n";
    cout << "3. Admin Login..."
         << "\n";
    cout << "4. Exit..."
         << "\n";
    int number;
    cin >> number;
    switch (number)
    {
    case 1:
        system("cls");
        memberLogin();
        break;
    case 2:
        system("cls");
        memberRegister();
        break;
    case 3:
        system("cls");
        adminLogin();
        break;
    case 4:
        system("exit");
        break;
    }
}
void memberRegister()
{
    Member person;
    person.id = lastMemberId() + 1;
    cout << "Enter a Username:"
         << "\n";
    cin >> person.userName;
    cout << "Enter Your Firstname:"
         << "\n";
    getline(cin, person.firstName);
    getline(cin, person.firstName);

    cout << "Enter Your Lastname:"
         << "\n";
    getline(cin, person.lastName);

    cout << "Enter Your PhoneNumber:"
         << "\n";
    cin >> person.phoneNumber;

    cout << "Enter Your PassWord"
         << "\n";
    cin >> person.passWord;

    cout << "Saving..."
         << "\n"
         << "\n";
    if (wrongUserName(person.userName))
    {
        ofstream MemberInfo("MemberInfo.txt", ios::app);
        ofstream LoginFile("Login.txt", ios::app);

        MemberInfo << person.id << "\n";
        LoginFile << person.id << "\n";
        MemberInfo << "Username:"
                   << "       " << person.userName << "\n";
        LoginFile << person.userName << "\n";
        UserName.push_back(person.userName);
        MemberInfo << "Firstname:"
                   << "      " << person.firstName << "\n";
        MemberInfo << "Lastname:"
                   << "       " << person.lastName << "\n";
        MemberInfo << "Phone Number:"
                   << "   " << person.phoneNumber << "\n";
        MemberInfo << "Password:"
                   << "       " << person.passWord << "\n";
        LoginFile << person.passWord << "\n";
        PassWord.push_back(person.passWord);
        MemberInfo.close();
        LoginFile.close();
    }
    system("cls");
    mainMenu();
}
bool wrongUserName(string person)
{
    for (int i = 0; i < UserName.size(); i++)
    {
        if (person == UserName[i])
        {
            cout << "This UserName Was Registered!"
                 << "\n";
            this_thread::sleep_for(chrono::milliseconds(3000));
            return false;
        }
        else if (i == UserName.size() - 1)
        {
            cout << "user Registered successfully";
            this_thread::sleep_for(chrono::milliseconds(3000));
            return true;
        }
    }
    return true;
}
void pushTOVectorUser()
{
    ifstream LoginFile("Login.txt", ios::app);
    string line;
    int i = 0;
    while (getline(LoginFile, line))
    {
        if (i % 3 == 1)
        {
            UserName.push_back(line);
        }
        i++;
    }
    LoginFile.close();
}
void pushTOVectorPass()
{
    ifstream LoginFile("Login.txt", ios::app);
    string line;
    int i = 1;
    while (getline(LoginFile, line))
    {
        if (i % 3 == 0)
        {
            PassWord.push_back(line);
        }
        i++;
    }
    LoginFile.close();
}
void memberLogin()
{
    string user, pass;
    bool isOkay = false;
    cout << "Enter Your UserName:"
         << "\n";
    cin >> user;
    cout << "Enter Your PassWord:"
         << "\n";
    cin >> pass;
    for (int i = 0; i < UserName.size(); i++)
    {
        if (user == UserName[i] && pass == PassWord[i])
        {
            isOkay = true;
            break;
        }
    }
    if (isOkay)
    {
        cout << "Welcome!";
        this_thread::sleep_for(chrono::milliseconds(1500));
        system("cls");
        showMemberProfile(user);
        getIdLogin(user);
        memberMenu();
    }
    else
    {
        cout << "You have not registered before.";
        this_thread::sleep_for(chrono::milliseconds(3000));
        system("cls");
        mainMenu();
    }
}
void readInfoAdmin(string &user, string &pass)
{
    ifstream adminLoginFile("adminLogin.txt", ios::app);
    string line;
    int i = 0;
    while (getline(adminLoginFile, line))
    {
        if (i == 0)
        {
            user = line;
        }
        else
        {
            pass = line;
        }
        i++;
    }
    adminLoginFile.close();
}
void adminLogin()
{
    string user, pass;
    readInfoAdmin(user, pass);
    ofstream adminLoginFile("adminLogin.txt", ios::app);
    string user1, pass1;
    cout << "Enter a UserName:"
         << "\n";
    cin >> user1;
    cout << "Enter a PassWord:"
         << "\n";
    cin >> pass1;
    if (user1 == user && pass1 == pass)
    {
        system("cls");
        managerMenu();
    }
    else
    {
        cout << "The Entered information does not match.";
        this_thread::sleep_for(chrono::milliseconds(4000));
        system("cls");
        mainMenu();
    }
    adminLoginFile.close();
}
void changeInfoAdmin()
{
    ofstream adminLoginFile("adminLogin.txt");
    string Changeuser, Changepass;
    cout << "Enter a New UserName:"
         << "\n";
    cin >> Changeuser;
    adminLoginFile << Changeuser << "\n";
    cout << "Enter a New PassWord:"
         << "\n";
    cin >> Changepass;
    adminLoginFile << Changepass;
}
void managerMenu()
{
    cout << "***MANGER MENU***"
         << "\n"
         << "\n";
    cout << "1. Manage Books"
         << "\n";
    cout << "2. Manage Member"
         << "\n";
    cout << "3. Change Information"
         << "\n";
    cout << "4. Back"
         << "\n";
    int number;
    cin >> number;
    switch (number)
    {
    case 1:
        system("cls");
        manageBooks();
        break;
    case 2:
        system("cls");
        manageMember();
        break;
    case 3:
        system("cls");
        changeInfoAdmin();
    case 4:
        system("cls");
        mainMenu();
        break;
    }
}
void manageBooks()
{
    showBooks();
    cout << "1. Add a new book."
         << "\n";
    cout << "2. Remove a book."
         << "\n";
    cout << "3. Edit a book."
         << "\n";
    cout << "4. Show borrow book."
         << "\n";
    cout << "5. Back."
         << "\n";
    int number;
    cin >> number;
    switch (number)
    {
    case 1:
        system("cls");
        addNewBook();
        break;

    case 2:
        system("cls");
        removeBook();
        break;
    case 3:
        system("cls");
        editBook();
        break;
    case 4:
    {
        system("cls");
        showBorrowedBook();
        cout << "1. Back."
             << "\n";
        int number1;
        cin >> number1;
        system("cls");
        manageBooks();
        break;
    }
    case 5:
        system("cls");
        managerMenu();
        break;
    }
}
void addNewBook()
{
    Book book;
    book.id = lastBookId() + 1;
    ofstream bookFile("book.txt", ios::app);
    bookFile << book.id << "\n";
    cout << "Enter book name:"
         << "\n";
    getline(cin, book.name);
    getline(cin, book.name);
    bookFile << "Title:"
             << "     " << book.name << "\n";
    cout << "Enter author name:"
         << "\n";
    getline(cin, book.author);
    bookFile << "Author:"
             << "    " << book.author << "\n";
    cout << "Enter genre book:"
         << "\n";
    cin >> book.genre;
    bookFile << "Genre:"
             << "     " << book.genre << "\n";
    cout << "--------------"
         << "\n";
    bookFile.close();
    system("cls");
    manageBooks();
}
void showBooks()
{
    ifstream bookFile("book.txt", ios::app);
    string line;
    int i = 0;
    while (getline(bookFile, line))
    {
        if (i % 4 == 0)
        {
            cout << "ID:"
                 << "        " << line << "\n";
        }
        else
        {

            cout << line << "\n";
            if (i % 4 == 3)
            {
                cout << "------------"
                     << "\n";
            }
        }
        i++;
    }
    bookFile.close();
}
int lastBookId()
{
    ifstream bookFile("book.txt", ios::app);
    string line;
    int i = 0, max = 0;
    while (getline(bookFile, line))
    {
        if (i % 4 == 0)
        {
            if (max < stoi(line))
            {
                max = stoi(line);
            }
        }
        i++;
    }
    return max;
}
void removeBook()
{
    showBooks();
    ifstream bookFile("book.txt", ios::app);
    string line1;
    bool isOk = false;
    while (getline(bookFile, line1))
    {
        isOk = true;
        break;
    }
    bookFile.close();
    if (isOk)
    {
        string line, deleteLine;
        ifstream bookFile("book.txt", ios::app);
        ofstream tempFile("temp.txt");
        cout << lastBookId() + 1 << ".Back"
             << "\n";
        cout << "Enter the ID book."
             << "\n";
        int number;
        cin >> number;
        int s = 0;
        while (getline(bookFile, line))
        {
            if (s > 0)
            {
                s--;
                continue;
            }

            if (line != to_string(number))
            {
                tempFile << line << endl;
            }
            else
            {
                s = 3;
            }
        }
        bookFile.close();
        tempFile.close();
        remove("book.txt");
        rename("temp.txt", "book.txt");
        if (lastBookId() >= number)
        {
            cout << "Done.";
            this_thread::sleep_for(chrono::milliseconds(2000));
            system("cls");
            managerMenu();
        }
        if (number == lastBookId() + 1)
        {
            system("cls");
            managerMenu();
        }
    }
    else
    {
        cout << "There Is Not Any Book";
        this_thread::sleep_for(chrono::milliseconds(2000));
        system("cls");
        managerMenu();
    }
}
int lastMemberId()
{

    ifstream MemberInfo("MemberInfo.txt", ios::app);
    string line;
    int i = 0, max = 0;
    while (getline(MemberInfo, line))
    {
        if (i % 6 == 0)
        {
            if (max < stoi(line))
            {
                max = stoi(line);
            }
        }
        i++;
    }
    return max;
}
void showMember()
{
    ifstream MemberInfo("MemberInfo.txt", ios::app);
    string line;
    int i = 0;
    while (getline(MemberInfo, line))
    {
        if (i % 6 == 0)
        {
            cout << "ID:"
                 << "             " << line << "\n";
        }
        else
        {
            cout << line << "\n";
        }
        i++;
    }
    MemberInfo.close();
}
void manageMember()
{
    showMember();
    ifstream MemberInfo("MemberInfo.txt", ios::app);
    string line1;
    bool isOk = false;
    while (getline(MemberInfo, line1))
    {
        isOk = true;
        break;
    }
    MemberInfo.close();
    if (isOk)
    {
        cout << lastMemberId() + 1 << ".Back"
             << "\n";
        cout << "Enter the ID you want to delete"
             << "\n";
        string line, deleteLine;
        ifstream MemberInfo("MemberInfo.txt", ios::app);
        ifstream LoginFile("Login.txt", ios::app);
        ofstream tempFile("temp.txt");
        ofstream tempFile1("temp1.txt");
        int number;
        cin >> number;
        int s = 0;
        while (getline(MemberInfo, line))
        {
            if (s > 0)
            {
                s--;
                continue;
            }
            if (line != to_string(number))
            {
                tempFile << line << endl;
            }
            else
            {
                s = 5;
            }
        }
        int c = 0;
        while (getline(LoginFile, line))
        {
            if (c > 0)
            {
                c--;
                continue;
            }
            if (line != to_string(number))
            {
                tempFile1 << line << endl;
            }
            else
            {
                c = 2;
            }
        }
        MemberInfo.close();
        LoginFile.close();
        tempFile.close();
        tempFile1.close();
        remove("MemberInfo.txt");
        rename("temp.txt", "MemberInfo.txt");
        remove("Login.txt");
        rename("temp1.txt", "Login.txt");
        ifstream borrowBookFile("borrowbook.txt");
        ofstream tempBfile("tempB.txt");
        while (!borrowBookFile.eof())
        {
            string idb, title, author, genre, idm;
            getline(borrowBookFile, idb);
            getline(borrowBookFile, title);
            getline(borrowBookFile, author);
            getline(borrowBookFile, genre);
            getline(borrowBookFile, idm);
            if (idm == to_string(number) || idb == "")
            {
                continue;
            }
            tempBfile << idb << "\n"
                      << title << "\n"
                      << author << "\n"
                      << genre << "\n"
                      << idm << "\n";
        }
        borrowBookFile.close();
        tempBfile.close();
        remove("borrowbook.txt");
        rename("tempB.txt", "borrowbook.txt");
        if (lastMemberId() >= number)
        {
            cout << "Done.";
            this_thread::sleep_for(chrono::milliseconds(2000));
            system("cls");
            managerMenu();
        }
        if (number == lastMemberId() + 1)
        {
            system("cls");
            managerMenu();
        }
    }
    else
    {
        cout << "There Is Not Any Member";
        this_thread::sleep_for(chrono::milliseconds(2000));
        system("cls");
        managerMenu();
    }
}
void selectedBook()
{
    cout << "Enter the ID for edit."
         << "\n";
    ifstream bookFile("book.txt", ios::app);
    string line;
    int number;
    cin >> number;
    int s = 0;
    while (getline(bookFile, line))
    {
        if (line == to_string(number))
        {
            system("cls");
            s++;
            cout << "ID:"
                 << "        " << line << "\n";
        }
        else
        {
            if (s != 0)
            {
                cout << line << "\n";
                s++;
            }
        }
        if (s > 3)
        {
            break;
        }
    }
    bookFile.close();
    cout << "\n"
         << "Which part do you want to edit?"
         << "\n";
    cout << "1.Title"
         << "\n";
    cout << "2.Author"
         << "\n";
    cout << "3.Genre"
         << "\n";
    cout << "4.Back"
         << "\n";
    int number1;
    cin >> number1;
    switch (number1)
    {
    case 1:
    {
        ifstream bookFile2("book.txt");
        system("cls");
        cout << "Enter the new Title:"
             << "\n";
        string title, tLine, txt;
        cin >> title;
        bool isOk = false;
        while (getline(bookFile2, tLine))
        {
            if (isOk)
            {
                tLine = "Title:     " + title;
                isOk = false;
            }
            if (tLine == to_string(number))
            {
                isOk = true;
            }
            txt += (tLine + "\n");
        }
        bookFile2.close();
        ofstream bookFile3("book.txt");
        bookFile3 << txt;
        bookFile3.close();
        cout << "Done."
             << "\n";
        this_thread::sleep_for(chrono::milliseconds(2000));
        system("cls");
        manageBooks();
    }
    break;
    case 2:
    {
        system("cls");
        ifstream bookFile2("book.txt");
        cout << "Enter the new Author:"
             << "\n";
        string author, aLine, txt2;
        cin >> author;
        bool isOk = false;
        int s = 0;
        while (getline(bookFile2, aLine))
        {
            if (isOk)
            {
                if (s == 1)
                {
                    s++;
                    txt2 += (aLine + "\n");
                    continue;
                }
                else
                {
                    aLine = "Author:    " + author;
                    isOk = false;
                }
            }
            if (aLine == to_string(number))
            {
                isOk = true;
                s++;
            }
            txt2 += (aLine + "\n");
        }
        bookFile2.close();
        ofstream bookFile3("book.txt");
        bookFile3 << txt2;
        bookFile3.close();
        cout << "Done."
             << "\n";
        this_thread::sleep_for(chrono::milliseconds(2000));
        system("cls");
        manageBooks();
    }
    break;
    case 3:
    {
        ifstream bookFile2("book.txt");
        system("cls");
        cout << "Enter the new Genre:"
             << "\n";
        string genre, gLine, txt3;
        cin >> genre;
        bool isOk = false;
        int s = 0;
        while (getline(bookFile2, gLine))
        {
            if (isOk)
            {
                if (s == 1)
                {
                    s++;
                    txt3 += (gLine + "\n");
                    continue;
                }
                else if (s == 2)
                {
                    s++;
                    txt3 += (gLine + "\n");
                    continue;
                }
                else
                {
                    gLine = "Genre:     " + genre;
                    isOk = false;
                }
            }
            if (gLine == to_string(number))
            {
                isOk = true;
                s++;
            }
            txt3 += (gLine + "\n");
        }
        bookFile2.close();
        ofstream bookFile3("book.txt");
        bookFile3 << txt3;
        bookFile3.close();
        cout << "Done."
             << "\n";
        this_thread::sleep_for(chrono::milliseconds(2000));
        system("cls");
        manageBooks();
    }
    break;
    case 4:
        system("cls");
        manageBooks();
        break;
    }
}
void editBook()
{
    showBooks();
    selectedBook();
}
void showMemberProfile(string user)
{
    ifstream loginFile("login.txt");
    int id;
    for (int i = 0; i < UserName.size(); i++)
    {
        if (user == UserName[i])
        {
            id = i + 1;
        }
    }
    ifstream MemberInfo("MemberInfo.txt", ios::app);
    int j = 0;
    int s = 0;
    string line1;
    while (getline(MemberInfo, line1))
    {
        if (line1 == to_string(id))
        {
            system("cls");
            s++;
        }
        else
        {
            if (s != 0)
            {
                cout << line1 << "\n";
                s++;
            }
        }
        if (s > 5)
        {
            break;
        }

        j++;
    }
    MemberInfo.close();
}
void changeInfoMember()
{
    system("cls");
    cout << "1.Change Username"
         << "\n";
    cout << "2.Change First Name"
         << "\n";
    cout << "3.Change Last Name"
         << "\n";
    cout << "4.Change Phone Number"
         << "\n";
    cout << "5.Change PassWord"
         << "\n";
    int number;
    cin >> number;
    string user;
    switch (number)
    {
    case 1:
    {
        ifstream memberInfo1("Login.txt");
        int id;
        cout << "Enter current UserName"
             << "\n";
        cin >> user;
        for (int i = 0; i < UserName.size(); i++)
        {
            if (user == UserName[i])
            {
                id = i + 1;
                break;
            }
            else
            {
                cout << "The UserName Does Not Correct.";
                system("cls");
                changeInfoMember();
                break;
            }
        }
        memberInfo1.close();
        ifstream memberInfo2("MemberInfo.txt");
        cout << "Enter the new UserName:"
             << "\n";
        string user1;
        cin >> user1;
        for (int i = 0; i < UserName.size(); i++)
        {
            if (user == UserName[i])
            {
                UserName[i] = user1;
            }
        }

        string tLine, txt;
        bool isOk = false;
        while (getline(memberInfo2, tLine))
        {
            if (isOk)
            {
                tLine = "UserName:       " + user1;
                isOk = false;
            }
            if (tLine == to_string(id))
            {
                isOk = true;
            }
            txt += (tLine + "\n");
        }
        ofstream memberInfo3("MemberInfo.txt");
        memberInfo3 << txt;
        memberInfo3.close();
        ifstream loginFile1("Login.txt");
        string gLine, txt1;
        isOk = false;
        while (getline(loginFile1, gLine))
        {
            if (isOk)
            {
                gLine = user1;
                isOk = false;
            }
            if (gLine == to_string(id))
            {
                isOk = true;
            }
            txt1 += (gLine + "\n");
        }
        loginFile1.close();
        ofstream lofinFile2("Login.txt");
        lofinFile2 << txt1;
        lofinFile2.close();
        cout << "Done."
             << "\n";
        this_thread::sleep_for(chrono::milliseconds(2000));
        system("cls");
        showMemberProfile(user1);
        memberMenu();
        break;
    }
    case 5:
    {
        ifstream memberInfo1("Login.txt");
        string pass;
        int id;
        cout << "Enter current PassWord"
             << "\n";
        cin >> pass;
        for (int i = 0; i < PassWord.size(); i++)
        {
            if (pass == PassWord[i])
            {
                id = i + 1;
                break;
            }
            else
            {
                cout << "The PassWord Does Not Correct.";
                system("cls");
                changeInfoMember();
                break;
            }
        }
        memberInfo1.close();
        ifstream memberInfo2("MemberInfo.txt");
        cout << "Enter the new PassWord:"
             << "\n";
        string pass1;
        cin >> pass1;
        for (int i = 0; i < PassWord.size(); i++)
        {
            if (pass == PassWord[i])
            {
                PassWord[i] = pass1;
            }
        }
        string tLine, txt;
        bool isOk = false;
        int s = 0;
        while (getline(memberInfo2, tLine))
        {
            if (isOk)
            {
                if (s < 5)
                {
                    txt += (tLine + "\n");
                    s++;
                    continue;
                }
                else
                {
                    tLine = "PassWord:       " + pass1;
                    isOk = false;
                }
            }
            if (tLine == to_string(id))
            {
                isOk = true;
                s++;
            }
            txt += (tLine + "\n");
        }

        ofstream memberInfo3("MemberInfo.txt");
        memberInfo3 << txt;
        memberInfo3.close();
        ifstream loginFile1("Login.txt");
        string gLine, txt1, user;
        isOk = false;
        s = 0;
        while (getline(loginFile1, gLine))
        {
            if (isOk)
            {
                if (s == 1)
                {
                    user = gLine;
                    txt1 += (gLine + "\n");
                    s++;
                    continue;
                }
                else
                {
                    gLine = pass1;
                    isOk = false;
                }
            }
            if (gLine == to_string(id))
            {
                isOk = true;
                s++;
            }
            txt1 += (gLine + "\n");
        }
        loginFile1.close();
        ofstream lofinFile2("Login.txt");
        lofinFile2 << txt1;
        lofinFile2.close();
        cout << "Done."
             << "\n";
        this_thread::sleep_for(chrono::milliseconds(2000));
        system("cls");
        showMemberProfile(user);
        memberMenu();
        break;
    }

    case 2:
    {
        string FirstName;
        cout << "Enter the new First Name:"
             << "\n";
        cin >> FirstName;
        ifstream memberInfo2("MemberInfo.txt");
        string tLine, txt;
        bool isOk = false;
        int s = 0;
        while (getline(memberInfo2, tLine))
        {
            if (isOk)
            {
                if (s < 2)
                {
                    txt += (tLine + "\n");
                    s++;
                    continue;
                }
                else
                {
                    tLine = "FirstName:      " + FirstName;
                    isOk = false;
                }
            }
            if (tLine == to_string(idLogin))
            {
                isOk = true;
                s++;
            }
            txt += (tLine + "\n");
        }
        memberInfo2.close();
        ofstream memberInfo3("MemberInfo.txt");
        memberInfo3 << txt;
        memberInfo3.close();
        ifstream loginFile1("Login.txt");
        string gLine, txt1, user;
        isOk = false;
        s = 0;
        while (getline(loginFile1, gLine))
        {
            if (isOk)
            {
                if (s == 1)
                {
                    user = gLine;
                    s++;
                    break;
                }
                else
                {
                    isOk = false;
                }
            }
            if (gLine == to_string(idLogin))
            {
                isOk = true;
                s++;
            }
        }
        loginFile1.close();
        cout << "Done."
             << "\n";
        this_thread::sleep_for(chrono::milliseconds(2000));
        system("cls");
        showMemberProfile(user);
        memberMenu();
        break;
    }
    case 3:
    {
        string LastName;
        cout << "Enter the new Last Name:"
             << "\n";
        cin >> LastName;
        ifstream memberInfo2("MemberInfo.txt");
        string tLine, txt;
        bool isOk = false;
        int s = 0;
        while (getline(memberInfo2, tLine))
        {
            if (isOk)
            {
                if (s < 3)
                {
                    txt += (tLine + "\n");
                    s++;
                    continue;
                }
                else
                {
                    tLine = "LastName:      " + LastName;
                    isOk = false;
                }
            }
            if (tLine == to_string(idLogin))
            {
                isOk = true;
                s++;
            }
            txt += (tLine + "\n");
        }
        memberInfo2.close();
        ofstream memberInfo3("MemberInfo.txt");
        memberInfo3 << txt;
        memberInfo3.close();
        ifstream loginFile1("Login.txt");
        string gLine, txt1, user;
        isOk = false;
        s = 0;
        while (getline(loginFile1, gLine))
        {
            if (isOk)
            {
                if (s == 1)
                {
                    user = gLine;
                    s++;
                    break;
                }
                else
                {
                    isOk = false;
                }
            }
            if (gLine == to_string(idLogin))
            {
                isOk = true;
                s++;
            }
        }
        loginFile1.close();
        cout << "Done."
             << "\n";
        this_thread::sleep_for(chrono::milliseconds(2000));
        system("cls");
        showMemberProfile(user);
        memberMenu();
        break;
    }
    case 4:
    {
        string PhoneN;
        cout << "Enter the new Last Name:"
             << "\n";
        cin >> PhoneN;
        ifstream memberInfo2("MemberInfo.txt");
        string tLine, txt;
        bool isOk = false;
        int s = 0;
        while (getline(memberInfo2, tLine))
        {
            if (isOk)
            {
                if (s < 4)
                {
                    txt += (tLine + "\n");
                    s++;
                    continue;
                }
                else
                {
                    tLine = "Phone Number:   " + PhoneN;
                    isOk = false;
                }
            }
            if (tLine == to_string(idLogin))
            {
                isOk = true;
                s++;
            }
            txt += (tLine + "\n");
        }
        memberInfo2.close();
        ofstream memberInfo3("MemberInfo.txt");
        memberInfo3 << txt;
        memberInfo3.close();
        ifstream loginFile1("Login.txt");
        string gLine, txt1, user;
        isOk = false;
        s = 0;
        while (getline(loginFile1, gLine))
        {
            if (isOk)
            {
                if (s == 1)
                {
                    user = gLine;
                    s++;
                    break;
                }
                else
                {
                    isOk = false;
                }
            }
            if (gLine == to_string(idLogin))
            {
                isOk = true;
                s++;
            }
        }
        loginFile1.close();
        cout << "Done."
             << "\n";
        this_thread::sleep_for(chrono::milliseconds(2000));
        system("cls");
        showMemberProfile(user);
        memberMenu();
        break;
    }
    }
}
void memberMenu()
{
    cout << "\n"
         << "1.Change Information"
         << "\n";
    cout << "2.Borrow Book"
         << "\n";
    cout << "3.My Book"
         << "\n";
    cout << "4.Give Back Book"
         << "\n";
    cout << "5.Back"
         << "\n";
    int number;
    cin >> number;
    switch (number)
    {
    case 1:
        system("cls");
        changeInfoMember();
        break;
    case 2:
        system("cls");
        borrowBook();
        break;
    case 3:
    {
        system("cls");
        myBook();
        cout << "1. Back."
             << "\n";
        int number1;
        cin >> number1;
         ifstream loginFile1("Login.txt");
            string gLine, txt1, user;
        bool isOk = false;
           int s = 0;
            while (getline(loginFile1, gLine))
            {
                if (isOk)
                {
                    if (s == 1)
                    {
                        user = gLine;
                        s++;
                        break;
                    }
                    else
                    {
                        isOk = false;
                    }
                }
                if (gLine == to_string(idLogin))
                {
                    isOk = true;
                    s++;
                }
            }
            loginFile1.close();
            system("cls");
            showMemberProfile(user);
            memberMenu();
    }
    break;
    case 4:
        system("cls");
        giveBackBook();
        break;
    case 5:
        system("cls");
        mainMenu();
        break;
    }
}
bool searchByTitle()
{
    vector<int> titleSearch;
    string title, line;
    cout << "Enter your title"
         << "\n";
    cin >> title;
    system("cls");
    ifstream bookFile("book.txt");
    int i = 1, s = 1;
    while (getline(bookFile, line))
    {
        if (i % 5 == 0)
        {
            s++;
        }

        if (i % 4 == 2)
        {
            if (line.substr(12).find(title) != -1)
            {
                titleSearch.push_back(s);
            }
        }
        i++;
    }
    if (titleSearch.size() == 0)
    {
        return false;
    }

    int k = 0, f = 0;
    bookFile.close();
    ifstream bookFile1("book.txt");
    for (int j = 0; j < titleSearch.size(); j++)
    {
        while (getline(bookFile1, line))
        {
            if (f > 0 && f < 4)
            {
                cout << line << "\n";
                f++;
                k++;
                continue;
            }
            else
            {
                f = 0;
            }
            if (k % 4 == 0)
            {
                if (titleSearch[j] == stoi(line))
                {
                    cout << "ID:        " << line << "\n";
                    f++;
                }
            }
            k++;
        }
    }
    bookFile1.close();
    return true;
}
bool searchByAuthor()
{
    vector<int> AuthorSearch;
    string Author, line;
    cout << "Enter your Author"
         << "\n";
    cin >> Author;
    system("cls");
    ifstream bookFile("book.txt");
    int i = 1, s = 1;
    while (getline(bookFile, line))
    {
        if (i % 5 == 0)
        {
            s++;
        }

        if (i % 4 == 3)
        {
            if (line.substr(12).find(Author) != -1)
            {
                AuthorSearch.push_back(s);
            }
        }
        i++;
    }
    if (AuthorSearch.size() == 0)
    {
        return false;
    }

    int k = 0, f = 0;
    bookFile.close();
    ifstream bookFile1("book.txt");
    for (int j = 0; j < AuthorSearch.size(); j++)
    {
        while (getline(bookFile1, line))
        {
            if (f > 0 && f < 4)
            {
                cout << line << "\n";
                f++;
                k++;
                continue;
            }
            else
            {
                f = 0;
            }
            if (k % 4 == 0)
            {
                if (AuthorSearch[j] == stoi(line))
                {
                    cout << "ID:        " << line << "\n";
                    f++;
                }
            }
            k++;
        }
    }
    bookFile1.close();
    return true;
}
bool searchByGenre()
{
    vector<int> GenreSearch;
    string Genre, line;
    cout << "Enter your Genre"
         << "\n";
    cin >> Genre;
    system("cls");
    ifstream bookFile("book.txt");
    int i = 1, s = 1;
    while (getline(bookFile, line))
    {
        if (i % 5 == 0)
        {
            s++;
        }

        if (i % 4 == 0)
        {
            if (line.substr(12).find(Genre) != -1)
            {
                GenreSearch.push_back(s);
            }
        }
        i++;
    }
    int k = 0, f = 0;
    bookFile.close();
    ifstream bookFile1("book.txt");
    if (GenreSearch.size() == 0)
    {
        return false;
    }

    for (int j = 0; j < GenreSearch.size(); j++)
    {
        while (getline(bookFile1, line))
        {
            if (f > 0 && f < 4)
            {
                cout << line << "\n";
                f++;
                k++;
                continue;
            }
            else
            {
                f = 0;
            }
            if (k % 4 == 0)
            {
                if (GenreSearch[j] == stoi(line))
                {
                    cout << "ID:        " << line << "\n";
                    f++;
                }
            }
            k++;
        }
    }
    bookFile1.close();
    return true;
}
void borrowBook()
{
    showBooks();
    ofstream borrowBookFile("borrowbook.txt", ios::app);
    ifstream borrowBookFile1("borrowbook.txt", ios::app);
    ifstream bookFile("book.txt");
    cout << "\n"
         << lastBookId() + 1 << ".search title"
         << "\n";
    cout << lastBookId() + 2 << ".search author"
         << "\n";
    cout << lastBookId() + 3 << ".search genre"
         << "\n";
    cout << "Enter the ID for borrow."
         << "\n";
    string line, txt = "", line2;
    int number;
    cin >> number;
    if (lastBookId() + 1 == number)
    {
        system("cls");
        if (!searchByTitle())
        {
            cout << "no books found";
            this_thread::sleep_for(chrono::milliseconds(3000));
            system("cls");
            borrowBook();
        }
        else
        {
            cout << "Enter the ID for borrow."
                 << "\n";
            cin >> number;
        }
    }
    else if (lastBookId() + 2 == number)
    {
        system("cls");
        if (!searchByAuthor())
        {
            cout << "no books found";
            this_thread::sleep_for(chrono::milliseconds(3000));
            system("cls");
            borrowBook();
        }
        else
        {
            cout << "Enter the ID for borrow."
                 << "\n";
            cin >> number;
        }
    }
    else if (lastBookId() + 3 == number)
    {
        system("cls");
        if (!searchByGenre())
        {
            cout << "no books found";
            this_thread::sleep_for(chrono::milliseconds(3000));
            system("cls");
            borrowBook();
        }
        else
        {
            cout << "Enter the ID for borrow."
                 << "\n";
            cin >> number;
        }
    }
    int s = 0;
    while (getline(borrowBookFile1, line2))
    {
        if (to_string(number) == line2)
        {
            cout << "Book is borrowed by someone."
                 << "\n";
            this_thread::sleep_for(chrono::milliseconds(2000));
            ifstream loginFile1("Login.txt");
            string gLine, txt1, user;
            bool isOk = false;
            s = 0;
            while (getline(loginFile1, gLine))
            {
                if (isOk)
                {
                    if (s == 1)
                    {
                        user = gLine;
                        s++;
                        break;
                    }
                    else
                    {
                        isOk = false;
                    }
                }
                if (gLine == to_string(idLogin))
                {
                    isOk = true;
                    s++;
                }
            }
            loginFile1.close();
            system("cls");
            showMemberProfile(user);
            memberMenu();
        }
    }
    while (getline(bookFile, line))
    {
        if (s > 0)
        {
            txt += line + "\n";
            s--;
            continue;
        }
        if (line == to_string(number))
        {
            s = 3;
            txt += line + "\n";
        }
    }
    borrowBookFile << txt;
    borrowBookFile << idLogin << "\n";
    cout << "Done."
         << "\n";
    this_thread::sleep_for(chrono::milliseconds(2000));
    borrowBookFile1.close();
    borrowBookFile.close();
    bookFile.close();
    ifstream loginFile1("Login.txt");
    string gLine, txt1, user;
    bool isOk = false;
    s = 0;
    while (getline(loginFile1, gLine))
    {
        if (isOk)
        {
            if (s == 1)
            {
                user = gLine;
                s++;
                break;
            }
            else
            {
                isOk = false;
            }
        }
        if (gLine == to_string(idLogin))
        {
            isOk = true;
            s++;
        }
    }
    loginFile1.close();
    system("cls");
    showMemberProfile(user);
    memberMenu();
}
void getIdLogin(string user)
{
    ifstream MemberInfo("MemberInfo.txt");
    while (!MemberInfo.eof())
    {
        string line;
        getline(MemberInfo, line);
        int id = stoi(line);
        getline(MemberInfo, line);
        if (line.substr(16) == user)
        {
            MemberInfo.close();
            idLogin = id;
            return;
        }
        getline(MemberInfo, line);
        getline(MemberInfo, line);
        getline(MemberInfo, line);
        getline(MemberInfo, line);
    }
}
void showBorrowedBook()
{
    ifstream borrowBookFile("borrowbook.txt");
    string line;
    int i = 1;
    int c = 0;
    while (getline(borrowBookFile, line))
    {
        if (c % 5 == 4)
        {
            cout << "IDM:       " << line << "\n";
        }
        else
        {
            if (i % 5 == 1)
            {
                cout << "IDB:"
                     << "       " << line << "\n";
            }
            else
            {
                cout << line << "\n";
            }
        }
        i++;
        c++;
    }
    borrowBookFile.close();
}
void myBook()
{
    ifstream borrowBookFile("borrowbook.txt");
    string line, txt = "";
    int s = 0, i = 0, j = 0;
    while (getline(borrowBookFile, line))
    {
        if (i % 5 == 4)
        {
            if (line == to_string(idLogin))
            {
                s++;
                cout << txt;
                j++;
            }
            txt = "";
        }
        else
        {
            if (i % 5 == 0)
            {
                txt += "IDB:       " + line + "\n";
            }
            else
            {
                txt += line + "\n";
            }
        }
        i++;
    }
    if (j == 0)
    {
        cout << "You have no books!"
             << "\n";
    }
    borrowBookFile.close();
}
void giveBackBook()
{
    ifstream borrowBookFile("borrowbook.txt");
    ofstream tempFile("temp.txt");
    myBook();
    cout << "Enter the IDB for return book."
         << "\n";
    string line, txt = "";
    int number;
    cin >> number;
    int s = 0;
    int i = 0;
    while (getline(borrowBookFile, line))
    {
        if (s > 0)
        {
            s--;
            i++;
            continue;
        }
        if (i % 5 == 0)
        {
            if (line == to_string(number))
            {
                s = 4;
            }
            else
            {
                tempFile << line << "\n";
            }
        }
        else
        {
            tempFile << line << "\n";
        }
        i++;
    }
    borrowBookFile.close();
    tempFile.close();
    remove("borrowbook.txt");
    rename("temp.txt", "borrowbook.txt");
    cout << "Done."
         << "\n";
    this_thread::sleep_for(chrono::milliseconds(1500));
    ifstream loginFile1("Login.txt");
    string gLine, txt1, user;
    bool isOk = false;
    s = 0;
    while (getline(loginFile1, gLine))
    {
        if (isOk)
        {
            if (s == 1)
            {
                user = gLine;
                s++;
                break;
            }
            else
            {
                isOk = false;
            }
        }
        if (gLine == to_string(idLogin))
        {
            isOk = true;
            s++;
        }
    }
    loginFile1.close();
    system("cls");
    showMemberProfile(user);
    memberMenu();
}
