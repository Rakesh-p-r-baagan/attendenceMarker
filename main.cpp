#include <iostream>
#include<string>
#include<cstring>
#include<fStream>
#include<conio.h>
#include <ctime>


using namespace std;

void mainmenu();
void adminLogin();
void insertionsort();
void adminMenu();
int isfileexist(string);
void initilizeAdminIdPass();
void creatAdminAccount();
void delay(int);
void markAttendence();
void attendenceStatus(string);
void studentlogin();
string hiddenpassword0();
void attendencelist();



class admin
{
    string username,password,rPassword;
public:
    void checkPasswordMatch()
    {
        int passwordMatchStatus= password.compare(rPassword);
        if(passwordMatchStatus!=0)
        {
            cout<<"passwords are not matching re-enter the password\n";
            getUserNameAndPasswordOfAdmin();              //////////////////////////////////////////
        }

    }
    int passwordformat()           //it checks if the password is of correct formate.It return '1' if password is of correct formate else '0'
    {
        int digf=0,numf=0,splf=0,i=0,len = password.size();

        if(password.size()<8)
        {
            printf("\nPassword is too short\n");
            return 0;
        }
        if(password.size()>20)
        {
            printf("\nPassword is too long");
            return 0;
        }

        for(i=0; i<len; i++)
        {
            if(password[i]>='A' && password[i]<='Z')
            {
                numf=1;
            }
            if(password[i] == '@' || password[i] == '&' || password[i] == '_' || password[i] == '*' || password[i] == '(' || password[i] ==')' || password[i] == '#' || password[i] == '$' || password[i]== '^' || password[i]== '.' || password[i]== ',')
            {
                splf =1;
            }
            if(isdigit(password[i])==0)
                digf=1;
        }
        if(numf && splf && digf )
        {

            return 1;
        }
        else
        {
            printf("\nPassword should contain atleast \none uppercase letter\none digit\none special character('@','#','$','^','&','*','(',')','.',',')");
            return 0;
        }
    }

    void getUserNameAndPasswordOfAdmin()  //this class should start from here
    {

        cout<<"\n Enter username : ";
        cin>>username;
        cout<<"\n Enter password : ";
        password=hiddenpassword0();
        while(!passwordformat())////////////////////////////////////
        {
            cout<<"\n Enter password : ";
            password=hiddenpassword0();
        }
        cout<<"\n re-Enter password : ";
        rPassword=hiddenpassword0();
        cout<<endl;
        checkPasswordMatch();/////////////////////////////////////
    }

    string returnAdminUsername()
    {
        return username;
    }

    string returnAdminPassword()
    {
        return password;
    }


};

class student
{
    string sName,usn;

public:
    void readStudentData()
    {

        cout<<"\nEnter the name\n";
        cin>>sName;
        cout<<"\nEnter the usn\n";
        cin>>usn;

    }

    string returnUsn()
    {
        return usn;
    }
    string returnSName()
    {
        return sName;
    }


};

void delay(int milli_seconds)
{
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}


void createAdminAccount()
{
    system("cls");
    admin a;
    a.getUserNameAndPasswordOfAdmin();//////////////////////////////
    string username,password;
    username=a.returnAdminUsername();
    password=a.returnAdminPassword();
    fstream f;
    f.open("AdminAccount.txt",ios::app);
    f<<username<<"\t"<<password<<"\n";
    f.close();


}


void createStudentFile()  //creates a separate file for each added student and adds the student usn to "studentlist.txt"
{
    system("cls");
    student s;
    int year,month,day,pa;
    s.readStudentData();

    string usn,sName;

    usn=s.returnUsn();
    sName=s.returnSName();


    string filename=usn + ".txt";

    time_t now = time(0);
    tm *ltm = localtime(&now);

    year=ltm->tm_year+1900;
    month=ltm->tm_mon+1;
    day=ltm->tm_mday;

    pa=2;

    if(!isfileexist(filename))/////////////////////////
    {
        cout<<"\nStudent already enrolled\n";
        system("pause");
        system("cls");
    }
    else
    {
        fstream sepratef,commonf,usnf;
        sepratef.open(filename,ios::out);
        sepratef<<usn<<"\t"<<sName<<"\t"<<pa<<"\t"<<day<<"\t"<<month<<"\t"<<year<<"\n";
        commonf.open("studentlist.txt",ios::app);
        commonf<<usn<<"\t"<<sName<<"\n";
        usnf.open("UsnFile.txt",ios::app);
        usnf<<usn<<"\n";
        commonf.close();
        usnf.close();
        sepratef.close();
        cout<<"\nStudent successfully added to the list\n";
        system("pause");
        system("cls");

    }
     insertionsort();
}

void markAttendence()  //usn files and studentlist.txt
{
    system("cls");
    string filename,usn,sName;
    int pa,day,month,year;


    time_t now = time(0);
    tm *ltm = localtime(&now);

    year=ltm->tm_year+1900;
    month=ltm->tm_mon+1;
    day=ltm->tm_mday;

    cout<<"\nEnter 1 for present and 0 for absent\n\n";
    fstream sfile,usnfile;
    sfile.open("studentlist.txt",ios::in);
    while(sfile>>usn>>sName)
    {
        filename=usn + ".txt";
        usnfile.open(filename,ios::app);
        cout<<"USN: "<<usn<<"\tNAME: "<<sName<<"\n";
        cin>>pa;
        usnfile<<usn<<"\t"<<sName<<"\t"<<pa<<"\t"<<day<<"\t"<<month<<"\t"<<year<<"\n";
        usnfile.close();
    }
    cout<<"\nAll attendance marked\n";
    sfile.close();
    system("pause");
    system("cls");

}

void adminMenu()
{
    int choice;
    system("cls");

    for(;;)
    {
        cout<<"\n --------- Admin menu --------\n\n";
        cout<<"\n1.Mark attendence\n2.add students\n3.create new admin account\n4.Student attendance list\n5.Mainmenu\n0.exit\nEnter your choice\n"<<endl;
        cin>>choice;
        switch(choice)
        {
        case 0:
            exit(0);
        case 1:
        {
            markAttendence();
            break;
        }
        case 2:
        {
            createStudentFile();
            break;
        }
        case 3:
        {
            createAdminAccount();
            cout<<"Account created successfully\n";
            system("pause");
            system("cls");
            break;
        }
        case 4:
        {
            attendencelist();
            break;
        }
        case 5:
        {
            mainmenu();
            break;
        }
        }
    }
}

int isfileexist(string filename)  //sets default password and id as rakesh and rakesh
{
    fstream f;
    f.open(filename,ios::in);
    if(f)
    {
        f.close();
        return 0;
    }
    f.close();
    return 1;
}

void initilizeAdminIdPass()   //"AdminAccount.txt"
{
    fstream f;
    int fileStatus= isfileexist("AdminAccount.txt");
    if(fileStatus)
    {
        f.open("AdminAccount.txt",ios::out);
        f<<"rakesh\trakesh\n";
        f.close();
    }
}


void adminLogin()
{
    initilizeAdminIdPass();
    int successf=0;
    system("cls");
    cout<<"\n --------- Admin Login --------\n";
    string username,fUsername,fPassword;
    string password;

    cout<<"\n Enter username : ";
    cin>>username;
    cout<<"\n Enter password : ";
    password=hiddenpassword0();

    fstream f;
    f.open("AdminAccount.txt",ios::in);
    while(f)
    {
        f>>fUsername>>fPassword;
        if(username.compare(fUsername)==0 && password.compare(fPassword)==0)
        {
            cout<<"\nLogin successful\n\n";
            successf=1;
            adminMenu();
            f.close();
            break;
        }
    }
    if(successf==0)
    {
        f.close();
        cout<<"\n Error ! Invalid Credintials..";

    }

}

void insertionSortRecursive(string arr[], int n)
{
    // Base case
    if (n <= 1)
        return;

    insertionSortRecursive( arr, n-1 );

    string last = arr[n-1];
    int j = n-2;

    while (j >= 0 && arr[j] > last)
    {
        arr[j+1] = arr[j];
        j--;
    }
    arr[j+1] = last;
}

void insertionsort()
{
    int i,j,n=0;
    string k;
    string usnarray[150];
    fstream usnf;
    usnf.open("UsnFile.txt");
    while(usnf>>usnarray[n++]);
    usnf.close();
    insertionSortRecursive(usnarray,n);
    usnf.open("UsnFile.txt");
    for(i=0; i<=n; i++)
    {
        usnf<<usnarray[i]<<"\n";
    }
    usnf.close();

}

void attendencelist()
{
    system("cls");
    string usn,name;
    int totaldays=0,p=0,a=0,flag=0,pa,day,month,year;
    float per=0.0;
    fstream sepf,usnf;
    usnf.open("UsnFile.txt",ios::in);
    while(usnf>>usn)
    {
        flag=0;
        p=0;
        a=0;
        per=0;
        totaldays=0;
        usn=usn+".txt";
        sepf.open(usn,ios::in);
        while(sepf>>usn>>name>>pa>>day>>month>>year)
        {
            if(flag==0)
            {
                cout<<"USN:"<<usn<<endl;
                flag=1;
                continue;
            }
            totaldays++;
            if(pa==1)
                p++;
            else
                a++;

        }
        sepf.close();
        per=((float)p/totaldays)*100;
        cout<<"Present:"<<p<<"\tAbsent:"<<a<<"\tAttendance percentage:"<<per<<endl;
    }
    usnf.close();
    system("pause");
    system("cls");


}

void attendenceStatus(string filename) //usn files
{
    fstream f,usnfile;
    string usn,name,usnfilename;
    int pa,day,month,year,pcount,acount,totaldays=0,p=0,a=0,flag=0;
    float per=0.0;

    usnfile.open(filename,ios::in);
    while(usnfile>>usn>>name>>pa>>day>>month>>year)
    {
        if(flag==0)
        {
            cout<<"Name:"<<name<<"\tUSN:"<<usn<<endl;
            flag=1;
            continue;
        }
        totaldays++;
        if(pa==1)
        {
            p++;
            cout<<day<<"-"<<month<<"-"<<year<<"\tPresent\n";
        }
        else
        {
            a++;
            cout<<day<<"-"<<month<<"-"<<year<<"\tAbsent\n";
        }

    }
    usnfile.close();
    per=((float)p/totaldays)*100;

    cout<<"\n\nPresent:"<<p<<"\tAbsent:"<<a<<"\tAttendance percentage:"<<per<<endl<<endl;
    system("pause");
    system("cls");
}

string hiddenpassword0()
{
    string password;
    char pass[32];
    int i=0;
    char a;
    for(;;)
    {
        a=getch();
        if(a=='\b'&&i>=1)//if user typed backspace
            //i should be greater than 1.
        {
            cout<<"\b \b";//rub the character behind the cursor.
            --i;
        }
        else if(a=='\r')//if enter is pressed
        {
            pass[i]='\0';
            break;//break the loop
        }
        else
        {
            pass[i]=a;
            i++;
            cout<<a;
            delay(200);
            cout<<"\b \b";
            cout<<"*";
        }

    }

    password=pass;

    return password;
}

void studentlogin()
{

    system("cls");
    cout<<"\n --------- Student Login --------\n";
    string password,username,fUsername,fpassword;
    int successf=0;

    cout<<"\n Enter username : ";
    cin>>username;
    cout<<"\n Enter password : ";
    password =hiddenpassword0();

    string filename=password + ".txt";


    ifstream sflogin;
    sflogin.open("studentlist.txt");
    while(sflogin>>fpassword>>fUsername)
    {
        if(password.compare(fpassword)==0 && username.compare(fUsername)==0)
        {
            system("cls");


            successf=1;
            attendenceStatus(filename);
            sflogin.close();
            break;
        }
    }
    if(successf==0)
    {
        sflogin.close();
        cout<<"\n Error ! Invalid Credintials..";

    }
    sflogin.close();
}

void mainmenu()
{
    system("cls");
    int choice;
    while(1)
    {
        cout<<"\n --------- Main menu --------\n\n";
        cout<<"\n1.student login\n2.admin login\n0.exit\nEnter your choice: ";
        cin>>choice;

        switch(choice)
        {
        case 0:
            exit(0);

        case 1:
            studentlogin();

            break;
        case 2:
            adminLogin();
            break;

        }
    }
}

int main()
{
    mainmenu();

    return 0;
}
