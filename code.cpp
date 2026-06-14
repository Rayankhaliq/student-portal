#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;


//============================================================================================================================================//
void LoadData(ifstream &fin,char name[35][30],char ID[35][20],char dept[35][15],float*& gpa,int*& attandance,int& count,int& gpasize,int& attsize);
bool login(char name[35][30],char ID[35][20],char dept[35][15],float*& gpa,int*& attandance,int& count,int& gpasize,int& attsize);
void addStudent(char name[35][30],char ID[35][20],char dept[35][15],float *&gpa,int*& attandance,int &count,int &gpasize,int &attsize,int& number);
void RemoveStudent(char name[35][30],char ID[35][20],char dept[35][15],float*& gpa,int*& attandance,int& count,int& gpasize,int& attsize);
void showStudents(char NAME[][30],char ID[][20],char DEPT[][15],float *gpa,int *attandance,int count);
void searchStudent(int &choice,char searchNAME[],char searchID[],char name[35][30],char ID[35][20],char dept[35][15],float*& gpa,int*& attandance,int& count);
void UpdateRecord(char name[35][30],char ID[35][20],char dept[35][15],float*& gpa,int*& attandance,int& count,int& gpasize,int& attsize);
void deptFilter(char searchDEPT[],char name[35][30],char ID[35][20],char dept[35][15],float*& gpa,int*& attandance,int& count);
void DeptStats(char name[35][30],char ID[35][20],char dept[35][15],float*& gpa,int*& attandance,int& count);
void HighestStudent(char name[35][30],char ID[35][20],char dept[35][15],float*& gpa,int*& attandance,int& count);
int Warning(char name[35][30],char ID[35][20],float* gpa,int* attandance,int count);
void GPAsorted(char name[35][30],char ID[35][20],char dept[35][15],float* gpa,int* attandance,int count);
void dataSaver(char name[35][30],char ID[35][20],char dept[35][15],float*& gpa,int*& attandance,int& count,int& gpasize,int& attsize,int number);
void adminMenu();
void studentMenu();
void AdminOptions(char name[35][30],char ID[35][20],char dept[35][15],float*& gpa,int*& attandance,int& count,int& gpasize,int& attsize);
void StudentOptions(char name[35][30],char ID[35][20],float*& gpa,int*& attandance,int& count,char username[]);
void intgrow(int *&arr,int &size);
void floatgrow(float *&arr,int &size);
void intshrink(int*& arr, int& size);
void floatshrink(float*& arr, int& size);
void shiftleft1(int* arr,int size,int target);
void shiftleft2(float* arr,int size,int target);
void swapint(int &a,int &b);
void swapfloat(float &a,float &b);
void swapchar(char a[],char b[]);
//============================================================================================================================================//



int main()
{
    ifstream fin;
    int gpasize,count,attsize;
    char Name[35][30];
    char ID[35][20];
    char Dept[35][15];
    float *GPA=NULL;
    int *Attandance=NULL;
    
    LoadData(fin,Name,ID,Dept,GPA,Attandance,count,gpasize,attsize);
    
    if(login(Name,ID,Dept,GPA,Attandance,count,gpasize,attsize))
    {
        cout<<"ACCESS GRANTED\n";
    }
    else
    {
        cout<<"ACCESS DENIED\n";
    }
    
    delete[] GPA;
    delete[] Attandance;
    return 0;
}

//============================================================================================================================================//

void LoadData(ifstream &fin,char name[35][30],char ID[35][20],char dept[35][15],float*& gpa,int*& attandance,int& count,int& gpasize,int& attsize)
{
    fin.open("students.txt");
    count=0;
    attandance=NULL;
    gpa=NULL;
    gpasize=0;
    attsize=0;
    float GPA;
    int ATTANDANCE;
    char first[15];
    char last[15];
    
    
    while(fin>>first>>last)
    {
        strcpy(name[count],first);
        strcat(name[count]," ");
        strcat(name[count],last);
        
        fin>>ID[count]>>dept[count];
        
        floatgrow(gpa,gpasize);
        fin>>GPA;
        gpa[gpasize-1]=GPA;
        
        intgrow(attandance,attsize);
        fin>>ATTANDANCE;
        attandance[attsize-1]=ATTANDANCE;
        
        count++;
    }
}

//============================================================================================================================================//

bool login(char name[35][30],char ID[35][20],char dept[35][15],float*& gpa,int*& attandance,int& count,int& gpasize,int& attsize)
{
    char username[50];
    char password[50];
    char fileUser[50];
    char filePass[50];
    char fileRole;
    bool found=false;
    char role;
    
    cout<<"==========================STUDENT PORTAL SYSTEM======================\n";
    for(int attempt=3;attempt>0;attempt--)
    {
        cout<<"Enter username: ";
        cin>>username;
        cout<<"Enter password: ";
        cin>>password;
        
        ifstream fin;
        fin.open("users.txt");
        
        while(fin>>fileUser>>filePass>>fileRole)
        {
            if(strcmp(username,fileUser)==0&&strcmp(password,filePass)==0)
            {
                found=true;
                role=fileRole;
                break;
            }
        }
        fin.close();
        
        if(found)
        {
            cout<<"LOGIN SUCCESSFUL\n";
            break;
        }
        
        cout<<"Wrong credentials. Attempts left: "<<(attempt-1)<<"\n";
    }
    
    if(!found)
    {
        cout<<"ACCOUNT BLOCKED AFTER 3 FAILED ATTEMPTS\n";
        return false;
    }
    
    if(role=='A')
    {
        AdminOptions(name,ID,dept,gpa,attandance,count,gpasize,attsize);
    }
    else if(role=='S')
    {
        StudentOptions(name,ID,gpa,attandance,count,username);  
    }
    
    return true;
}

//============================================================================================================================================//


void addStudent(char name[35][30],char ID[35][20],char dept[35][15],float *&gpa,int*& attandance,int &count,int &gpasize,int &attsize,int &number)
{
    cout<<"Enter the number of STUDENTS you want to add: ";
    cin>>number;
    cin.ignore();
    float Gpa;

    
    for(int i=0;i<number;i++)
    {
        cout<<"Enter the Student's NAME: ";
        cin.getline(name[count],30);
        
        cout<<"ENter the Student's ID: ";
        cin>>ID[count];
        
        cout<<"Enter the student's DEPARTMENT: ";
        cin>>dept[count];
        
        cout<<"Enter the student's GPA (if transfer (else Enter 0)): ";
        cin>>Gpa;
        floatgrow(gpa,gpasize);
        gpa[gpasize-1]=Gpa;
        
        intgrow(attandance,attsize);
        attandance[attsize-1]=0;
        
        
        dataSaver(name,ID,dept,gpa,attandance,count,gpasize,attsize,number);
        cin.ignore();
        count++;
    
    }
}

//======================================================================================================================================//

void showStudents(char NAME[][30],char ID[][20],char DEPT[][15],float *gpa,int *attandance,int count)
{
    if(count==0)
    {
        cout<<"No student data to show...\n";
        return;
    }
    
    cout<<"===================STUDENT DATA====================";
    for(int i=0;i<count;i++)
    {
        cout << "\nStudent " << i + 1 << ":\n";
        cout<<fixed;
        cout.width(20);

        cout<<left<<"Student's name ";
        cout<<" : ";
        
        cout<<NAME[i]<<endl;
        cout.width(20);
        cout<<left<<"Student's Department : ";
        
        cout<<DEPT[i]<<endl;
        cout.width(20);
        cout<<left<<"Student's ID ";
        
        cout<<" : ";
        
        cout<<ID[i]<<endl;
        cout.width(20);
        cout<<left<<"Student's CGPA ";
        
        cout<<" : ";
        cout.precision(2);
        cout<<gpa[i]<<endl;
        cout<<endl;
        
        cout<<left<<"Student's ATTANDANCE ";
        
        cout<<" : ";
        cout<<attandance[i]<<endl;
        cout<<endl;
    }
    cout<<"===================================================";
    cout<<endl;
}

//======================================================================================================================================//

void RemoveStudent(char name[35][30],char ID[35][20],char dept[35][15],float*& gpa,int*& attandance,int& count,int& gpasize,int& attsize)
{
    char remID[50];
    bool found=false;
    cout<<"ENter the ID of the student you want to remove: ";
    cin>>remID;
    for(int i=0;i<count;i++)
    {
        if(strcmp(remID,ID[i])==0)
        {
            found=true;
            for(int j=i;j<count-1;j++)
            {
                strcpy(name[j],name[j+1]);
                strcpy(ID[j],ID[j+1]);
                strcpy(dept[j],dept[j+1]);
            }
            
            
            shiftleft2(gpa,gpasize,i);
            shiftleft1(attandance,attsize,i);
            break;
            
        }
    }
    
    if(!found)
    {
        cout<<"Student not found!\n";
        return;
    }
    floatshrink(gpa, gpasize);      
    intshrink(attandance, attsize); 
    count--;

    ofstream fout1;
    fout1.open("students.txt");
    for(int i = 0; i < count; i++)
    {
        fout1 << name[i] << " " << ID[i] << " " << dept[i] << " " << gpa[i] << " " << attandance[i] << endl;
    }
    fout1.close();
    
    
    char unames[35][50];
    char upass[35][50];
    char urole[35][10];
    int ucount = 0;
    char uid[50];
    int j = 0;
    ifstream fin;
    fin.open("users.txt");
    
    while(fin >> unames[ucount] >> upass[ucount] >> urole[ucount])
    {
        
        for(j = 0; unames[ucount][j] != '@'; j++)
        {
            uid[j] = unames[ucount][j];
        }
        uid[j] = '\0';
    
        if(strcmp(uid, remID) != 0) 
        {
            ucount++;
        }
    }
    fin.close();
    
    ofstream fout2;
    fout2.open("users.txt");
    for(int i = 0; i < ucount; i++)
    {
        fout2 << unames[i] << " " << upass[i] << " " << urole[i] << endl;
    }
    fout2.close();
}

//======================================================================================================================================//

void searchStudent(int &choice,char searchNAME[50],char searchID[50],char name[35][30],char ID[35][20],char dept[35][15],float*& gpa,int*& attandance,int& count)
{
    cout<<"ENTER 1 to search by NAME, 2 to Search by ID:\n";
    cin>>choice;
    cin.ignore();
    if(choice==1)
    {
        cout<<"Enter the students name:\n";
        cin.getline(searchNAME,50);
        int j=0;
        if(searchNAME[j]>='a'&&searchNAME[j]<='z')
        {
            searchNAME[j]-=32;
            j++;
        }
        for(int i=0;i<count;i++)
        {
            if(strcmp(searchNAME,name[i])==0)
            {
                cout<<fixed;
                cout.width(20);

                cout<<left<<"Student's name ";
                cout<<" : ";
        
                cout<<name[i]<<endl;
                cout.width(20);
                cout<<left<<"Student's Department ";
        
                cout<<dept[i]<<endl;
                cout.width(20);
                cout<<left<<"Student's ID ";
        
                cout<<" : ";
            
                cout<<ID[i]<<endl;
                cout.width(20);
                cout<<left<<"Student's CGPA ";
        
                cout<<" : ";
                cout.precision(2);
                cout<<gpa[i]<<endl;
                cout.width(20);
                cout<<left<<"Student's ATTANDANCE ";
        
                cout<<" : ";
                cout<<attandance[i]<<endl;
                cout<<endl;
            }
        }
    }
    
    else if(choice==2)
    {
        cout<<"Enter the students ID:\n";
        cin.getline(searchID,50);
        int j=0;
        if(searchID[j]>='a'&&searchID[j]<='z')
        {
            searchID[j]-=32;
            j++;
        }
        for(int i=0;i<count;i++)
        {
            if(strcmp(searchID,ID[i])==0)
            {
                cout<<fixed;
                cout.width(20);

                cout<<left<<"Student's name ";
                cout<<" : ";
        
                cout<<name[i]<<endl;
                cout.width(20);
                cout<<left<<"Student's Department :";
        
                cout<<dept[i]<<endl;
                cout.width(20);
                cout<<left<<"Student's ID ";
        
                cout<<" : ";
            
                cout<<ID[i]<<endl;
                cout.width(20);
                cout<<left<<"Student's CGPA ";
        
                cout<<" : ";
                cout.precision(2);
                cout<<gpa[i]<<endl;
                cout.width(20);
                cout<<left<<"Student's ATTANDANCE ";
        
                cout<<" : ";
                cout<<attandance[i]<<endl;
                cout<<endl;
            }
        }
    }
    else
    {
        cout<<"INVALID CHOICE...\n";
    }
}

//======================================================================================================================================//

void deptFilter(char searchDEPT[],char name[35][30],char ID[35][20],char dept[35][15],float*& gpa,int*& attandance,int& count)
{
    cout<<"=================STUDENTS OF THE DEPT=================\n";
    cout<<"Enter the department to filter students: \n";
    cin>>searchDEPT;
    int j=0;
    for(int j = 0; searchDEPT[j] != '\0'; j++)
    {
        if(searchDEPT[j] >= 'a' && searchDEPT[j] <= 'z')
        {
            searchDEPT[j] -= 32; 
        }
    }
    for(int i=0;i<count;i++)
    {
        if(strcmp(searchDEPT,dept[i])==0)
        {
            cout<<fixed;
            cout.width(20);
            cout<<left<<"Student's name ";
            cout<<" : ";
            cout<<name[i]<<endl;
            cout.width(20);
            cout<<left<<"Student's Department ";
        
            cout<<dept[i]<<endl;
            cout.width(20);
            cout<<left<<"Student's ID ";
        
            cout<<" : ";
            
            cout<<ID[i]<<endl;
            cout.width(20);
            cout<<left<<"Student's CGPA ";
        
            cout<<" : ";
            cout.precision(2);
            cout<<gpa[i]<<endl;
            cout.width(20);
            cout<<left<<"Student's ATTANDANCE ";
        
            cout<<" : ";
            cout<<attandance[i]<<endl;
            cout<<endl;
            cout<<"-----------------------------------------\n";
        }
    }     
}



//======================================================================================================================================//


void adminMenu()
{
    cout<<"\n===== ADMIN PORTAL =====\n";
    cout<<"1. Add Student\n";
    cout<<"2. Show Students\n";
    cout<<"3. Search Student\n";
    cout<<"4. Department Filter\n";
    cout<<"5. Update Record\n";
    cout<<"6. Remove Student\n";
    cout<<"7. Department Stats\n";
    cout<<"8. Highest GPA Student\n";
    cout<<"9. Scholarship Warning\n";
    cout<<"10. Sort by GPA\n";
    cout<<"0. Logout\n";
}

//======================================================================================================================================//

void studentMenu()
{
    cout << "1. View GPA\n";
    cout << "2. View Attendance\n";
    cout << "3. Logout\n";
}

//======================================================================================================================================//

void UpdateRecord(char name[35][30],char ID[35][20],char dept[35][15],float*& gpa,int*& attandance,int& count,int& gpasize,int& attsize)
{

    char upID[50];
    cout<<"Enter the Student's ID to update data: ";
    cin>>upID;
    int target=-1;
    for(int i=0;i<count;i++)
    {
        if(strcmp(upID,ID[i])==0)
        {
            target=i;
        }
    }

    if(target==-1)
    {
        cout<<"Student not FOUND!!!\n";
        return;
    }

    int choice;
    do
    {
        cout<<"Enter 1 to update NAME...\n";
        cout<<"Enter 2 to update DePT...\n";
        cout<<"Enter 3 to update GPA...\n";
        cout<<"Enter 4 to update ATTANDANCE...\n";
        cout<<"Enter 5 to update EXIT...\n";
        cin>>choice;
        switch(choice)
        {
            case 1:
                cout<<"Update the name to what you want:\n";
                cin>>name[target];
                break;

            case 2:
                cout<<"Update the department what you want: \n";
                cin>>dept[target];
                break;

            case 3:
                cout<<"Update the GPA :\n";
                cin>>gpa[target];
                break;

            case 4:
                cout<<"Update the attandance :\n";
                cin>>attandance[target];
                break;

            case 5:
                cout<<"Exited!!!\n";
                break;

            default:
                cout<<"Invalid choice!!!\n";
                break;

        }
    }while(choice!=5);

    ofstream fout;
    fout.open("students.txt");
    for(int i = 0; i < count; i++)
    {
        fout << name[i] << " " << ID[i] << " " << dept[i] << " " << gpa[i] << " " << attandance[i] << endl;
    }
    fout.close();

}

//======================================================================================================================================//

void DeptStats(char name[35][30],char ID[35][20],char dept[35][15],float*& gpa,int*& attandance,int& count)
{
    char d1[10]="SE";
    char d2[10]="CS";
    char d3[10]="IT";
    int cs,it,se;
    cs=it=se=0;
    float sum1,sum2,sum3;
    sum1=sum2=sum3=0;
    
    for(int i=0;i<count;i++)
    {
        if(strcmp(d1,dept[i])==0)
        {
            sum1+=gpa[i];
            se++;
        }
        if(strcmp(d2,dept[i])==0)
        {
            sum2+=gpa[i];
            it++;
        }
        if(strcmp(d3,dept[i])==0)
        {
            sum3+=gpa[i];
            cs++;
        }
    }
    
    float seavg;
    float itavg;
    float csavg;
    if(cs!=0) csavg=sum3/cs;
    if(it!=0) itavg=sum2/it;
    if(se!=0) seavg=sum1/se;
        
    cout<<"=================DEPARTMENT STaTISTICS===================\n";
    cout<<"SOFTWARE ENGINEERING:\n";
    cout<<"TOTAL NUMBER of STUDENTS: "<<se<<endl;
    cout<<"AVERAGE GPA OF SE DEPT IS: "<<seavg<<endl;
    
    cout<<"INFORMATION TECHNOLOGY:\n";
    cout<<"TOTAL NUMBER of STUDENTS: "<<it<<endl;
    cout<<"AVERAGE GPA OF IT DEPT IS: "<<itavg<<endl;
    
    cout<<"COMPUTER SCIENCE:\n";
    cout<<"TOTAL NUMBER of STUDENTS: "<<cs<<endl;
    cout<<"AVERAGE GPA OF CS DEPT IS: "<<csavg<<endl;
    cout<<"==========================================================\n";
    
}

//======================================================================================================================================//

void HighestStudent(char name[35][30],char ID[35][20],char dept[35][15],float*& gpa,int*& attandance,int& count,int& gpasize,int& attsize)
{
    int maxindex=0;
    for(int i=0;i<count;i++)
    {
        if(gpa[i]>gpa[maxindex])
        {
            maxindex=i;
        }
    }
    
    
    cout<<"STUDENT WITH HIGHEST MARKS IS:\n";
    cout<<"NAME:       "<<name[maxindex]<<endl;
    cout<<"ROLL NO:    "<<ID[maxindex]<<endl;
    cout<<"DEPARTMENT: "<<dept[maxindex]<<endl;
    cout<<"GPA:        "<<gpa[maxindex]<<endl;
    cout<<"ATTANDANCE: "<<attandance[maxindex]<<endl;
}

//======================================================================================================================================//

int Warning(char name[35][30],char ID[35][20],float* gpa,int* attandance,int count)
{
    cout<<"==========SCHOLARSHIP WARNING==========\n";
    int warned=0;
    for(int i=0;i<count;i++)
    {
        if(attandance[i]==0){
            continue;
        }
        if(gpa[i]<2.0||attandance[i]<75)
        {
            cout<<"Student: "<<name[i]<<" ID: "<<ID[i]<<"\n";
            if(gpa[i]<2.0)
            {
                cout<<"  WARNING: GPA "<<gpa[i]<<" is below 2.0\n";
            }
            if(attandance[i]<75)
            {
                cout<<"  WARNING: Attendance "<<attandance[i]<<"% is below 75%\n";
            }
            cout<<"---------------------------------------\n";
            warned++;
        }
    }
    if(warned==0)
    {
        cout<<"No Student with Low attandance or warning!!!\n";
    }
    cout<<"=======================================\n";
    return warned;
}

//======================================================================================================================================//

void GPAsorted(char name[35][30],char ID[35][20],char dept[35][15],float* gpa,int* attandance,int count)
{
    char tempname[35][30];
    char tempid[35][20];
    char tempdept[35][15];
    float tempgpa[35];
    int tempatt[35];
    bool ascdone=false;
    bool descdone=false;
    
    
    int choice;
    
    do
    {
        if(!ascdone)
        {
            cout<<"Enter 1 to sort in ASSCENDING GPA ORDER:\n";
        }
        if(!descdone)
        {
            cout<<"Enter 2 to sort in DEscENDING GPA ORDER:\n";
        }
        cout<<"Enter 3 to stop!!!\n";
        cin>>choice; 
        if(choice==1)
        {
            for(int i=0;i<count;i++)
            {
                strcpy(tempname[i],name[i]);
                strcpy(tempid[i],ID[i]);
                strcpy(tempdept[i],dept[i]);
                
                tempgpa[i]=gpa[i];
                tempatt[i]=attandance[i];
            }
            for(int i=0;i<count;i++)
            {
                for(int j=0;j<count-1-i;j++)
                {
                    if(tempgpa[j]>tempgpa[j+1])
                    {
                        swapchar(tempname[j],tempname[j+1]);
                        swapchar(tempid[j],tempid[j+1]);
                        swapchar(tempdept[j],tempdept[j+1]);
                        
                        swapfloat(tempgpa[j],tempgpa[j+1]);
                        swapint(tempatt[j],tempatt[j+1]);
                    }
                }
            }
            
            ofstream fout1;
            fout1.open("ASSSortedStudents.txt");
            fout1<<"THE SORTED STUDENT FILE IS:\n";
            for(int i=0;i<count;i++)
            {
                fout1<<tempname[i]<<" "<<tempid[i]<<" "<<tempdept[i]<<" "<<tempgpa[i]<<" "<<tempatt[i]<<endl;
            }
            fout1.close();
            ascdone=true;
        }
        
        else if(choice==2)
        {
            for(int i=0;i<count;i++)
            {
                strcpy(tempname[i],name[i]);
                strcpy(tempid[i],ID[i]);
                strcpy(tempdept[i],dept[i]);
                
                tempgpa[i]=gpa[i];
                tempatt[i]=attandance[i];
            }
            for(int i=0;i<count;i++)
            {
                for(int j=0;j<count-1-i;j++)
                {
                    if(tempgpa[j]<tempgpa[j+1])
                    {
                        swapchar(tempname[j],tempname[j+1]);;
                        swapchar(tempid[j],tempid[j+1]);
                        swapchar(tempdept[j],tempdept[j+1]);
                        
                        swapfloat(tempgpa[j],tempgpa[j+1]);
                        swapint(tempatt[j],tempatt[j+1]);
                    }
                }
            }
            
            
            ofstream fout2;
            fout2.open("DESSortedStudents.txt");
            fout2<<"THE SORTED STUDENT FILE IS:\n";
            for(int i=0;i<count;i++)
            {
                fout2<<tempname[i]<<" "<<tempid[i]<<" "<<tempdept[i]<<" "<<tempgpa[i]<<" "<<tempatt[i]<<endl;
            }
            fout2.close();
            descdone=true;
        }
        
        else if(choice==3)
        {
            cout<<"EXITING!!!\n";
        }
        
        else
        {
            cout<<"Enter a valid option!!!\n";
        }
    }while(choice!=3 && !(ascdone&&descdone));
}

//======================================================================================================================================//

void StudentOptions(char name[35][30],char ID[35][20],float*& gpa,int*& attandance,int& count,char username[])
{
    char loggedID[50];
    int j=0;
    for(j=0;username[j]!='@';j++)
    {
        loggedID[j]=username[j];
    }
    loggedID[j]='\0';
    
    int target=-1;
    for(int i=0;i<count;i++)
    {
        if(strcmp(loggedID,ID[i])==0)
        {
            target=i;
            break;
        }
    }
    
    if(target==-1)
    {
        cout<<"STUDENT NOT FOUND!!!\n";
        return;
    }
    
    int choice;
    do
    {
        studentMenu();
        cin>>choice;
        switch(choice)
        {
            case 1:
                cout<<"Your GPA is: "<<gpa[target]<<endl;
                break;
            case 2:
                cout<<"Your Attendance is: "<<attandance[target]<<endl;
                break;
            case 3:
                cout<<"LOGGING OUT!!!\n";
                break;
            default:
                cout<<"Invalid option...\n";
        }
    }while(choice!=3);
}

//======================================================================================================================================//

void AdminOptions(char name[35][30],char ID[35][20],char dept[35][15],float*& gpa,int*& attandance,int& count,int& gpasize,int& attsize)
{
    int choice;
    int number;
    do
    {
        adminMenu();
        cin>>choice;
        switch(choice)
        {
            case 1:
                addStudent(name,ID,dept,gpa,attandance,count,gpasize,attsize,number);
                break;
            
            case 2:
                showStudents(name,ID,dept,gpa,attandance,count);
                break;
            
            case 3:
                int ch;
                char sname[50];
                char sID[50];
                searchStudent(ch,sname,sID,name,ID,dept,gpa,attandance,count);
                break;
            
            case 4:
                char sdept[50];
                deptFilter(sdept,name,ID,dept,gpa,attandance,count);
                break;
            
            case 5:
                UpdateRecord(name,ID,dept,gpa,attandance,count,gpasize,attsize);
                break;
            
            case 6:
                RemoveStudent(name,ID,dept,gpa,attandance,count,gpasize,attsize);
                break;
            
            case 7:
                DeptStats(name,ID,dept,gpa,attandance,count);
                break;
            
            case 8:
                HighestStudent(name,ID,dept,gpa,attandance,count,gpasize,attsize);
                break;
            
            case 9:
                Warning(name,ID,gpa,attandance,count);
                break;
            
            case 10:
                GPAsorted(name,ID,dept,gpa,attandance,count);
                break;
            
            case 0:
                cout<<"EXITING!!!\n";
                break;
            
            default:
                cout<<"Invalid option...\n";
        }
    }while(choice!=0);
}

//======================================================================================================================================//

void dataSaver(char name[35][30],char ID[35][20],char dept[35][15],float*& gpa,int*& attandance,int& count,int& gpasize,int& attsize,int number)
{
    ofstream fout1;
    ofstream fout2;
    char USERNAME[50];
    char PASS[50];
    
    fout1.open("students.txt",ios::app);
    fout2.open("users.txt",ios::app);
    
    
    fout1<<name[count]<<" "<<ID[count]<<" "<<dept[count]<<" "<<gpa[count]<<" "<< 0<<endl;
        
        
    cout<<"Enter the Student's Username: ";
    cin>>USERNAME;
        
    cout<<"Decide the Student's PASSWORD: ";
    cin>>PASS;
        
    fout2<<USERNAME<<" "<<PASS<<" S"<<endl;
    
    
    fout1.close();
    fout2.close();
}

//======================================================================================================================================//
void floatgrow(float *&arr,int &size)
{
    float *temp=new float[size+1];
    for(int i=0;i<size;i++)
    {
        temp[i]=arr[i];
    }
    delete[] arr;
    arr=temp;
    size++;
}

//======================================================================================================================================//
void intgrow(int *&arr,int &size)
{
    int *temp=new int[size+1];
    for(int i=0;i<size;i++)
    {
        temp[i]=arr[i];
    }
    delete[] arr;
    arr=temp;
    size++;
}

//======================================================================================================================================//

void shrink(int *&arr,int &size)
{
    int *temp=new int[size-1];
    for(int i=0;i<size-1;i++)
    {
        temp[i]=arr[i];
    }
    delete[] arr;
    arr=temp;
    size--;
}

//======================================================================================================================================//

void shiftleft1(int* arr,int size,int target)
{
    for(int i=target;i<size-1;i++)
    {
        arr[i]=arr[i+1];
    }
}

//======================================================================================================================================//

void shiftleft2(float* arr,int size,int target)
{
    for(int i=target;i<size-1;i++)
    {
        arr[i]=arr[i+1];
    }
}

//======================================================================================================================================//

void swapint(int &a,int &b)
{
    int t=a;
    a=b;
    b=t;
}
//======================================================================================================================================//

void swapfloat(float &a,float &b)
{
    float t=a;
    a=b;
    b=t;
}

//======================================================================================================================================//

void swapchar(char a[],char b[])
{
    char t[30];
    strcpy(t,a);
    strcpy(a,b);
    strcpy(b,t);
}

//======================================================================================================================================//

void floatshrink(float*& arr, int& size)
{
    float* temp=new float[size-1];
    for(int i=0;i<size-1;i++)
    {
        temp[i]=arr[i];
    }
    delete[] arr;
    arr=temp;
    size--;
}

//======================================================================================================================================//

void intshrink(int*& arr, int& size)
{
    int* temp=new int[size-1];
    for(int i=0;i<size-1;i++)
    {
        temp[i]=arr[i];
    }
    delete[] arr;
    arr=temp;
    size--;
}

//========================
