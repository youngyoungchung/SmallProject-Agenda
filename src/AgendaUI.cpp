#include "AgendaUI.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

AgendaUI::AgendaUI()
{
    m_userName = "";
    m_userPassword = "";
    startAgenda();
}

void AgendaUI::OperationLoop(void)
{
    cout << "-------------------------- Agenda ------------------------"<< endl;
    cout << "Action :"<< endl;
    cout << "l   - log in Agenda by user name and password"<<endl;
    cout << "r   - register an Agenda account"<<endl;
    cout << "q   - quit Agenda"<<endl;
    cout << "----------------------------------------------------------"<< endl;
    cout <<endl<<endl;
    cout << "Agenda : ~$ ";

    string str;
    cin >> str;
    
    if (str[0] == 'l' && str.length() == 1)
    {
        userLogIn();
     
    }
    else if (str[0] == 'r' && str.length() == 1)
    {
        userRegister();
    
    }
    else if (str[0] == 'q' && str.length() == 1)
    {
        quitAgenda();
     
    }
    else
    {
        cout <<endl;
        cout <<"[error] wrong operation!Please choose again."<<endl;
        cout <<endl;
        OperationLoop();
    }

}


    /**
     * constructor
     */
void AgendaUI::startAgenda(void)
{
    m_agendaService.startAgenda();


}

    /**
     * catch user's operation
     * @return the operation
     */
std::string AgendaUI::getOperation()
{
        cout << "-------------------------- Agenda ------------------------"<< endl;
        cout << "Action :"<<endl;
        cout << "o   - log out Agemda"<< endl;
        cout << "dc  - delete Agenda account" <<endl;
        cout << "lu  - list all Agenda user" <<endl;
        cout << "cm  - create a meeting"<< endl;
        cout << "la  - list all meetings" <<endl;
        cout << "las - list all sponsor meetings"<< endl;
        cout << "lap - list all participate meetings" << endl;
        cout << "qm  - query meeting by title" << endl;
        cout << "qt  - query meeting by time interval"<< endl;
        cout << "dm  - delete meeting by title" << endl;
        cout << "da  - delete all meetings" <<endl;
        cout << "rp  - reset password" <<endl;
        cout << "----------------------------------------------------------"<< endl;
        cout << endl;
        cout << "Agenda@" <<m_userName <<" : # ";
        string cd;
        cin >> cd;
        return cd;

}

    /**
     * execute the operation
     * @return if the operationloop continue
     */
bool AgendaUI::executeOperation(std::string t_operation)
{

    if (t_operation == "dc")
    {
        deleteUser();
     
    }
    else if (t_operation == "lu")
    {
        listAllUsers();
        
       
    }
    else if (t_operation == "cm")
    {
        createMeeting();
        
        
    }
    else if (t_operation == "la")
    {
        listAllMeetings();
       
        
    }
    else if (t_operation == "las")
    {
        listAllSponsorMeetings();
        
        
    }
    else if(t_operation == "lap")
    {
        listAllParticipateMeetings();
       
        
    }
    else if(t_operation == "qm")
    {
        queryMeetingByTitle();
        
        
    }
    else if (t_operation =="qt")
    {
        queryMeetingByTimeInterval();
        
        
    }
    else if(t_operation == "dm")
    {
        deleteMeetingByTitle();
        
        
    }
    else if(t_operation == "da")
    {
        deleteAllMeetings();
        
        
    }
    else if(t_operation[0] =='o' && t_operation.length() == 1)
    {
        userLogOut();
        
        
    }
    else if(t_operation == "rp")
    {
        resetPassword();
    }
    else
    {
        cout <<endl;
        cout << "[error] wrong operation! please choose again!"<<endl;
        cout << endl;
        string ab;
        ab = getOperation();
        executeOperation(ab);
    }
    return true;
 

}   


    /**
     * user Login
     */
void AgendaUI::userLogIn(void)
{

    cout <<endl;
    cout <<"[log in] [user name] [password]"<<endl;
    cout <<"[log in] ";
    cin >> m_userName;
    cin >> m_userPassword;
  
    if (m_agendaService.userLogIn(m_userName, m_userPassword))
    {
        cout <<"[log in] succeed!"<<endl;
        cout <<endl;
        string str;
        str = getOperation();
        executeOperation(str);

    }
    else
    {
        cout <<"[error] log in fail!"<<endl;
        OperationLoop();
    }



}

    /**
     * user regist
     */
void AgendaUI::userRegister(void)
{
    cout <<endl;
    cout <<"[register] [user name] [password] [email] [phone]"<<endl;
    cout <<"[register] ";
    string email, phone;
    cin >> m_userName >> m_userPassword >> email >> phone;
    if (m_agendaService.userRegister(m_userName , m_userPassword, email, phone))
    {
        cout <<"[register] succeed!"<<endl;
        cout <<endl;
        string str;
        str = getOperation();
        executeOperation(str);

    }
    else
    {
        cout <<"[error] register fail!"<<endl;
        OperationLoop();
    }

}

    /**
     * quit the Agenda
     */
void AgendaUI::quitAgenda(void)
{
    m_agendaService.quitAgenda();
}

    /**
     * user logout
     */
void AgendaUI::userLogOut(void)
{
    cout <<endl<<endl;
    OperationLoop();

}

    /**
     * delete a user from storage
     */
void AgendaUI::deleteUser(void)
{
    cout <<endl;
    if (m_agendaService.deleteUser(m_userName, m_userPassword))
    {
        cout <<"[delete agenda account] succeed!"<<endl;
    }
    OperationLoop();

}

    /**
     * list all users from storage
     */
void AgendaUI::listAllUsers(void)
{
    cout << endl;
    cout <<"[list all users]"<<endl;
    cout <<endl;
    cout << left << setw(20)<< "name" << setw(30) << "email" <<setw(30)<<"phone"<<endl;
    list<User> alluserlist = m_agendaService.listAllUsers();
    for (auto i = alluserlist.begin(); i!=alluserlist.end(); i++)
    {
        cout << left<<setw(20) <<(*i).getName()
                    <<setw(30) <<(*i).getEmail()
                    <<setw(30) <<(*i).getPhone() <<endl;
    }

    string ab;
    ab = getOperation();
    executeOperation(ab);
}

    /**
     * user create a meeting with someone else
     */
void AgendaUI::createMeeting(void)
{
    cout <<"[create meeting] [the number of participators]"<<endl;
    cout <<"[create meeting] ";
    int num;
    vector<string> total_par;
    string title, start, end;
    cin >> num;
    for (auto i = 1; i <= num; i++)
    {
        cout <<"[create meeting] [please enter the participator "<< i <<" ]"<<endl;
        cout <<"[create meeting] ";
        string par_name;
        cin >> par_name;
        total_par.push_back(par_name);
    }
    cout <<"[create meeting] [title] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]\n";
    cout <<"[create meeting] ";
    cin >> title >> start >> end;
    if(m_agendaService.createMeeting(m_userName, title, start, end, total_par))
    {
        cout <<"[create meeting] succeed!"<<endl;
    }
    else
    {
        cout <<"[create meeting] error!"<<endl;
    }

    string ab;
    ab = getOperation();
    executeOperation(ab);
}

    /**
     * list all meetings from storage
     */
void AgendaUI::listAllMeetings(void)
{
    cout <<endl;
    cout <<"[list all meetings]"<<endl;
    cout <<endl;

    list<Meeting> allmeetlist;
    allmeetlist = m_agendaService.listAllMeetings(m_userName);
    printMeetings(allmeetlist);

    string ab;
    ab = getOperation();
    executeOperation(ab);
}

    /**
     * list all meetings that this user sponsored
     */
void AgendaUI::listAllSponsorMeetings(void)
{
    cout <<endl;
    cout <<"[list all sponsor meetings]"<<endl;
    cout <<endl;
    list<Meeting> allsponmeetlist;
    allsponmeetlist = m_agendaService.listAllSponsorMeetings(m_userName);
    printMeetings(allsponmeetlist);

    string ab;
    ab = getOperation();
    executeOperation(ab);
}

    /**
     * list all meetings that this user take part in
     */
void AgendaUI::listAllParticipateMeetings(void)
{
    cout <<endl;
    cout <<"[list all paticipator meetings]"<<endl;
    cout <<endl;

    list<Meeting> allpameetlist;
    allpameetlist = m_agendaService.listAllParticipateMeetings(m_userName);
    printMeetings(allpameetlist);

    string ab;
    ab = getOperation();
    executeOperation(ab);
}

    /**
     * search meetings by title from storage
     */
void AgendaUI::queryMeetingByTitle(void)
{
    cout <<endl;
    cout <<"[query meeting] [title]"<<endl;
    cout <<"[query meeting] ";
    string title;
    cin >> title;
    list<Meeting> rela =  m_agendaService.meetingQuery(m_userName, title);
    printMeetings(rela);

    string ab;
    ab = getOperation();
    executeOperation(ab);

}

    /**
     * search meetings by timeinterval from storage
     */
void AgendaUI::queryMeetingByTimeInterval(void)
{
    cout <<endl;
    cout <<"[query meetings] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]"<<endl;
    cout <<"[query meetings] ";
    string start, end;
    cin >> start >>end;
    cout <<"[query meetings] ";
    list<Meeting> rela = m_agendaService.meetingQuery(m_userName, start, end);
    printMeetings(rela);

    string ab;
    ab = getOperation();
    executeOperation(ab);
}

    /**
     * delete meetings by title from storage
     */
void AgendaUI::deleteMeetingByTitle(void)
{
    cout <<endl;
    cout <<"[delete meeting] [title]"<<endl;
    cout <<"[delete meeting] ";
    string title;
    cin >> title;
    cout <<endl;
    if (m_agendaService.deleteMeeting(m_userName, title))
    {
        cout <<"[delete meeting by title] succeed!"<<endl;
    }
    else
    {
        cout <<"[error] delete meeting fail!"<<endl;
    }
    string ab;
    ab = getOperation();
    executeOperation(ab);
}

    /**
     * delete all meetings that this user sponsored
     */
void AgendaUI::deleteAllMeetings(void)
{
    cout <<endl;
    m_agendaService.deleteAllMeetings(m_userName);
    cout <<"[delete all meetings] succeed!"<<endl;

    string ab;
    ab = getOperation();
    executeOperation(ab);
}

    /**
     * show the meetings in the screen
     */
void AgendaUI::printMeetings(std::list<Meeting> t_meetings)
{
    cout <<endl;
    cout <<left <<setw(30)<< "title"
                <<setw(15)<<"sponsor"
                <<setw(20)<<"start time"
                <<setw(16)<<"end time" <<endl;

    for (auto i = t_meetings.begin(); i != t_meetings.end(); i++)
    {
        string start = Date::dateToString((*i).getStartDate());
        string end = Date::dateToString((*i).getEndDate());
    cout <<left <<setw(30)<< (*i).getTitle()
                <<setw(15)<< (*i).getSponsor()
                <<setw(20)<< start
                <<setw(16)<< end <<endl;
    }
}

void AgendaUI::resetPassword(void)
{
    cout <<endl;
    string new_password, userName, password;
    cout <<"[current user name]: ";
    cin >>userName;
    cout <<endl<<"[current password]: ";
    cin >>password;
    cout <<endl<<"[new password]: ";
    cin >>new_password;
    if (m_userName == userName && m_userPassword == password)
    {
        if (m_agendaService.resetPassword(userName, password, new_password))
        {
            cout <<"[reset password] succeed!"<<endl;
        }
        else
        {
            cout <<"[reset password] failed!"<<endl;
        }
    }
    else
    {
        cout <<"[error] the user name input is not the login user name"<<endl;
    }

    string ab;
    ab = getOperation();
    executeOperation(ab);

}
