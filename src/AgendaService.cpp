#include "AgendaService.hpp"


AgendaService::AgendaService()
{
    startAgenda();
}

    /**
     * destructor
     */
AgendaService::~AgendaService()
{
    quitAgenda();
}

    /**
     * check if the username match password
     * @param userName the usernamine want to login
     * @param password the password user enter
     * @return if success, true will be returned
     */
bool AgendaService::userLogIn(const std::string userName, const std::string password)
{

    std::list<User> related_userlist = m_storage->queryUser([&](const User& log_user)->bool {
        if (userName == log_user.getName())
        {
            if(password == log_user.getPassword())
            {
                return true;
            }
        }
        return false;
    });

    if (related_userlist.size() == 0)
        return false;
    return true;

}
    /**
     * regist a user
     * @param userName new user's username
     * @param password new user's password
     * @param email new user's email
     * @param phone new user's phone
     * @return if success, true will be returned
     */
bool AgendaService::userRegister(const std::string userName, const std::string password,
                      const std::string email, const std::string phone)
{
    std::list<User> related_userlist = m_storage->queryUser([&](const User& log_user)->bool {
        if (userName == log_user.getName())
        {
            return true;
        }
        return false;
    });

    if (related_userlist.size() == 0)
    {
        User new_user;
        new_user.setName(userName);
        new_user.setPassword(password);
        new_user.setEmail(email);
        new_user.setPhone(phone);
        m_storage->createUser(new_user);
        m_storage->sync();
        return true;
    }
    return false;
 
}

    /**
     * delete a user
     * @param userName user's username
     * @param password user's password
     * @return if success, true will be returned
     */
bool AgendaService::deleteUser(const std::string userName, const std::string password)
{

    int num = m_storage->deleteUser([&](const User& log_user)->bool {
    if (userName == log_user.getName())
    {
        if(password == log_user.getPassword())
        {
            return true;
        }
    }
    return false;
    });

    if (num == 0)
        return false;

   // std::list<Meeting> related_meeting = listAllMeetings(userName);
    
    int num2 = 0;
    num2 = m_storage->deleteMeeting([&](const Meeting& r_meeting)-> bool {
        if(userName == r_meeting.getSponsor())
        {
            return true;
        }
        if(r_meeting.isParticipator(userName))
        {
            return true;
        }
        
        return false;
    });

    m_storage->sync();
    return true;

}

    /**
     * list all users from storage
     * @return a user list result        // param User a is not used,ok?
     */
std::list<User> AgendaService::listAllUsers(void) const
{
    std::list<User> all_userList = m_storage->queryUser([](const User& a)->bool {
        if (1)
            return true;    
    });
    return all_userList;

}

    /**
     * create a meeting
     * @param userName the sponsor's userName
     * @param title the meeting's title
     * @param participator the meeting's participator
     * @param startData the meeting's start date
     * @param endData the meeting's end date
     * @return if success, true will be returned
     */
bool AgendaService::createMeeting(const std::string userName, const std::string title,
                       const std::string startDate, const std::string endDate,
                       const std::vector<std::string> participator)
{
    std::list<Meeting> related_meetinglist = m_storage->queryMeeting([&](const Meeting& new_meeting)->bool {
        if (title == new_meeting.getTitle())  // title tong fangru list
        {
            return true;
        }
        Date start1 = Date::stringToDate(startDate);
        Date end1 = Date::stringToDate(endDate);
        if (!Date::isValid(start1) || !Date::isValid(end1))
        {
            return true;
        }
        if (start1 >= end1)
        {
            return true;
        }
        if (participator.size() == 0)
        {
            return true;
        }
        std::list<User> related_userlist = m_storage->queryUser([&](const User& log_user)->bool {
            if (userName == log_user.getName())
            {
                return true;
            }
            for (auto i = 0; i < participator.size(); i++)
            {
                if (participator[i] == log_user.getName())
                    return true;
            }
            return false;
        });

        if (related_userlist.size() != participator.size()+1)  // meiyouzhegeyonghu
        {
            return true;
        }

        if ( !(start1 >= new_meeting.getEndDate()
            || end1 <= new_meeting.getStartDate()) )  
        {
            return true;
        }                          
        return false;
    });
    if (related_meetinglist.size() == 0)
    {
        Date start1 = Date::stringToDate(startDate);
        Date end1 = Date::stringToDate(endDate);
        Meeting m(userName, participator, start1, end1, title);
        m_storage->createMeeting(m);
        m_storage->sync();
        return true;
    }
    return false;
}

    /**
     * search meetings by username and title (user as sponsor or participator)
     * @param uesrName the user's userName
     * @param title the meeting's title
     * @return a meeting list result
     */
std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string title) const
{
    std::list<Meeting> related_meetinglist = m_storage->queryMeeting([&](const Meeting& r_meeting)-> bool {
        if(title == r_meeting.getTitle())
        {
            if(userName == r_meeting.getSponsor())
            {
                return true;
            }
            if(r_meeting.isParticipator(userName))
            {
                return true;
            }
        }
        return false;
    });
    return related_meetinglist;
}
    /**
     * search a meeting by username, time interval (user as sponsor or participator)
     * @param uesrName the user's userName
     * @param startDate time interval's start date
     * @param endDate time interval's end date
     * @return a meeting list result
     */
std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                    const std::string startDate,
                                    const std::string endDate) const
{
    std::list<Meeting> related_meetinglist;
    Date sd(startDate);
    Date ed(endDate);
    if(Date::isValid(sd) && Date::isValid(ed) && (sd<=ed))
    {
        related_meetinglist = m_storage->queryMeeting([&](const Meeting& r_meeting)-> bool {
        if( r_meeting.getEndDate() >= sd && r_meeting.getStartDate() <= ed)
        {
            if(userName == r_meeting.getSponsor())
            {
                return true;
            }
            if(r_meeting.isParticipator(userName))
            {
                return true;
            }
        }
        return false;
    });
    }
    return related_meetinglist;
}

    /**
     * list all meetings the user take part in
     * @param userName user's username
     * @return a meeting list result
     */
std::list<Meeting> AgendaService::listAllMeetings(const std::string userName) const
{
    std::list<Meeting> related_meetinglist = m_storage->queryMeeting([&](const Meeting& r_meeting)-> bool {
        if(userName == r_meeting.getSponsor())
        {
            return true;
        }
        if(r_meeting.isParticipator(userName))
        {
            return true;
        }
        
        return false;
    });
    return related_meetinglist;
}

    /**
     * list all meetings the user sponsor
     * @param userName user's username
     * @return a meeting list result
     */
std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string userName) const
{
    std::list<Meeting> related_meetinglist = m_storage->queryMeeting([&](const Meeting& r_meeting)-> bool {
        if(userName == r_meeting.getSponsor())
        {
            return true;
        }
        
        return false;
    });
    return related_meetinglist;
}

    /**
     * list all meetings the user take part in and sponsor by other
     * @param userName user's username
     * @return a meeting list result
     */
std::list<Meeting> AgendaService::listAllParticipateMeetings(
        const std::string userName) const
{
    std::list<Meeting> related_meetinglist = m_storage->queryMeeting([&](const Meeting& r_meeting)-> bool {

        if(r_meeting.isParticipator(userName))
        {
            return true;
        }
        
        return false;
    });
    return related_meetinglist;
}

    /**
     * delete a meeting by title and its sponsor
     * @param userName sponsor's username
     * @param title meeting's title
     * @return if success, true will be returned
     */
bool AgendaService::deleteMeeting(const std::string userName, const std::string title)
{
    int num = 0;
    num = m_storage->deleteMeeting([&](const Meeting& r_meeting)-> bool {
        if(userName == r_meeting.getSponsor())
        {

            if(title == r_meeting.getTitle())
            {
                return true;
            }
        }
        return false;
    });
    if (num == 0)
    {
        return false;
    }
    m_storage->sync();
    return true;
}

    /**
     * delete all meetings by sponsor
     * @param userName sponsor's username
     * @return if success, true will be returned
     */
bool AgendaService::deleteAllMeetings(const std::string userName)
{
    int num = 0;
    num = m_storage->deleteMeeting([&](const Meeting& r_meeting)-> bool {
        if(userName == r_meeting.getSponsor())
        {
            return true;
        }
        
        return false;
    });
    if (num == 0)
    {
        return false;
    }
    m_storage->sync();
    return true;
}

    /**
     * start Agenda service and connect to storage
     */
void AgendaService::startAgenda(void)
{
    m_storage = Storage::getInstance();

}

    /**
     * quit Agenda service
     */
void AgendaService::quitAgenda(void)
{
    m_storage = nullptr;
}

bool AgendaService::resetPassword(std::string userName, std::string password, std::string new_password)
{
    int num = m_storage->updateUser([&](const User& log_user)->bool{
    if (userName == log_user.getName())
    {
        if(password == log_user.getPassword())
        {
            return true;
        }
    }
    return false;
    }, [&](User & log_user)->void {
        log_user.setPassword(new_password);
    });

    if (num == 0)
        return false;

    m_storage->sync();
    return true;
}
/*
#include <iostream>
using namespace std;
int main(void)
{
    AgendaService as;
  
    Date d1("2016-03-31/12:00");
    Date d2("2016-03-31/13:00");
    Date d3("2016-02-17/12:09");
    Date d4("2016-02-17/13:00");
 
    vector<string> par;
    vector<string> tar;
    string s1 = "z";
    string s2 = "zmxgt";
    string s3 = "3gtrrr";
    par.push_back(s1);
    par.push_back(s2);
    par.push_back(s3);
    
    bool yo, yp;
    yo = as.createMeeting("aa", "tt", "2016-03-31/12:00", "2016-03-31/13:00", par);
    cout <<"sss"<<endl;
    tar.push_back("z2");
    tar.push_back("z4");
    yp = as.createMeeting("zmx", "zm2", "2016-02-17/12:09", "2016-02-17/13:00", tar);
    if (yo)
    {
        cout <<"?!"<<endl;
        if(yp)
        {
            cout <<"...."<<endl;
        }
    }
}
*/