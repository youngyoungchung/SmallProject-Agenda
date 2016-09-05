#include "Storage.hpp"
#include "Path.hpp"

#include <fstream>
#include <sstream>

std::shared_ptr<Storage> Storage::m_instance = nullptr;

Storage::Storage()
{
	
	bool b = readFromFile();
	m_dirty = false;
	
}

bool Storage::readFromFile(void)
{
	std::ifstream isuser(Path::userPath);
	if(!isuser.is_open())
	{
		
		return false;
	}
	std::ifstream ismeet(Path::meetingPath);
	if(!ismeet.is_open())
	{
		return false;
	}


	std::string line;

	while (getline(isuser, line,'\n'))
	{
		std::string username, password, email, phone;
		std::string username2, password2, email2, phone2;
		std::stringstream ss(line);
		getline(ss, username, ',');
		getline(ss, password, ',');
		getline(ss, email, ',');
		getline(ss, phone, '\n');
		username2 = username.substr(1, username.length()-2);
		password2 = password.substr(1, password.length()-2);
		email2 = email.substr(1, email.length()-2);
		phone2 = phone.substr(1, phone.length()-2);
		User nuser;
		nuser.setName(username2);
		nuser.setPassword(password2);
		nuser.setEmail(email2);
		nuser.setPhone(phone2);
		m_userList.push_back(nuser);

	}


	std::string li;

	while (getline(ismeet, li, '\n'))
	{
		std::string sp, pa, start, end, tit;
		std::string sp2, pa2, start2, end2, tit2;
		std::stringstream ss(li);
		getline(ss, sp, ',');
		getline(ss, pa, ',');
		getline(ss, start, ',');
		getline(ss, end, ',');
		getline(ss, tit, '\n');
		sp2 = sp.substr(1, sp.length()-2);
		pa2 = pa.substr(1, pa.length()-2);
		start2 = start.substr(1, start.length()-2);
		end2 = end.substr(1, end.length()-2);
		tit2 = tit.substr(1, tit.length()-2);

		Meeting nmeet;                                         
		nmeet.setSponsor(sp2);

		std::vector<std::string> partis;
		int index = 0;
		int last = 0;
		while ( (index = pa2.find('&', index)) != std::string::npos)
		{
			std::string person = pa2.substr(last, index-last);
			partis.push_back(person);
			last = index+1;
			index++;
		}
		index = pa2.rfind('&');
		std::string person = pa2.substr(index+1, pa2.length()-index+1);
		partis.push_back(person);
		nmeet.setParticipator(partis);

		Date start3 = Date::stringToDate(start2);
		nmeet.setStartDate(start3);

		Date end3 = Date::stringToDate(end2);
		nmeet.setEndDate(end3);


		nmeet.setTitle(tit2);
		m_meetingList.push_back(nmeet);

	}
	
	return true;
}

bool Storage::writeToFile(void)
{
	std::ofstream osuser(Path::userPath);
	std::ofstream osmeet(Path::meetingPath);

	if (!osuser.is_open())
	{
		
		return false;
	}
	if (!osmeet.is_open())
	{
		return false;
	}
	
	for (auto ituser = m_userList.begin(); ituser != m_userList.end(); ++ituser)
	{
		osuser << "\""<<(*ituser).getName()<< "\",\"" <<(*ituser).getPassword()
			<<  "\",\"" <<(*ituser).getEmail() << "\",\"" <<(*ituser).getPhone()
			<< "\""<< std::endl;
	}



	for (auto itmeet = m_meetingList.begin(); itmeet != m_meetingList.end(); ++itmeet)
	{
		osmeet << "\""<<(*itmeet).getSponsor()<< "\",\"";
		std::vector<std::string> par_list = (*itmeet).getParticipator();
		int i;
		for (i = 0; i < par_list.size()-1; i++)
		{
			osmeet << par_list[i]<<"&";
		}
		osmeet << par_list[i] <<  "\",\"" ;

		std::string sta, en;
		sta = Date::dateToString((*itmeet).getStartDate());
		en = Date::dateToString((*itmeet).getEndDate());

		osmeet << sta << "\",\"" << en 
		<<  "\",\"" <<(*itmeet).getTitle()<< "\""<< std::endl;
	}

	return true;
}

std::shared_ptr<Storage> Storage::getInstance(void)
{
	if (m_instance == nullptr)
	{
		m_instance = std::shared_ptr<Storage>(new Storage);
	}
	return m_instance;
}

Storage::~Storage()
{
	bool bo = writeToFile();
	m_dirty = false;

}

void Storage::createUser(const User& t_user)
{

	m_userList.push_back(t_user);

	m_dirty = true;
	
}

std::list<User> Storage::queryUser(std::function<bool(const User&)> filter) const
{

	std::list<User> valid_userList;
	for (auto it = m_userList.begin(); it != m_userList.end(); it++)
	{
		if (filter(*it))
		{
			valid_userList.push_back(*it);
		}
	}

	return valid_userList;
}

int Storage::updateUser(std::function<bool(const User&)> filter,
	std::function<void(User &)> switcher)
{

	int i = 0;
	for (auto it = m_userList.begin(); it != m_userList.end(); it++)
	{
		if (filter(*it))
		{
			switcher(*it);
			i++;
			m_dirty = true;
		}
	}
	
	return i;
}

int Storage::deleteUser(std::function<bool(const User&)> filter)
{

	int i = 0;
	for (auto it = m_userList.begin(); it != m_userList.end(); )
	{
		if (filter(*it))
		{
			it = m_userList.erase(it);
			i++;
			m_dirty = true;
		}
		else
		{
			it++;
		}
	}
	
	return i;
}

void Storage::createMeeting(const Meeting& t_meeting)
{
	m_meetingList.push_back(t_meeting);
	m_dirty = true;
}

std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting&)> filter) const
{

	std::list<Meeting> valid_meetingList;
	for (auto it = m_meetingList.begin(); it != m_meetingList.end(); it++)
	{
		if (filter(*it))
		{
			valid_meetingList.push_back(*it);
		}
	}
	return valid_meetingList;
}

int Storage::updateMeeting(std::function<bool(const Meeting&)> filter,
	std::function<void(Meeting &)> switcher)
{

	int i = 0;
	for (auto it = m_meetingList.begin(); it != m_meetingList.end(); it++)
	{
		if (filter(*it))
		{
			switcher(*it);
			i++;
			m_dirty = true;
		}
	}
	
	return i;
}

int Storage::deleteMeeting(std::function<bool(const Meeting&)> filter)
{

	int i = 0;
	for (auto it = m_meetingList.begin(); it != m_meetingList.end(); )
	{
		if (filter(*it))
		{
			
			it = m_meetingList.erase(it);
			i++;
			m_dirty = true;
		}
		else
		{
			++it;
		}
	}
	
	return i;
}

bool Storage::sync(void)
{
	if (m_dirty)
	{
		
		if( writeToFile())
		{
			
			m_dirty = false;
			return true;
		}
		return false;
	}
	return false;
}

/*
int main(void)
{
	
	shared_ptr<Storage> sto = Storage::getInstance();

 	Date d1("2016-03-31/12:00");
 	Date d2("2016-03-31/13:00");
 
 	vector<string> par;
 	string s1 = "zm2";
 	string s2 = "zmx";
 	string s3 = "3gt";
 	par.push_back(s1);
 	par.push_back(s2);
 	par.push_back(s3);

 	string userName = "zmx";
 	string title = "lalala";
 	
 	std::list<Meeting> related_meetinglist = sto->queryMeeting([&](const Meeting& r_meeting)-> bool {
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
    for (auto i = related_meetinglist.begin(); i != related_meetinglist.end(); i++)
    {
    	cout <<(*i).getSponsor()<<endl;
    }

    int num = 0;
    num = sto->deleteMeeting([&](const Meeting& r_meeting)-> bool {
        if(userName == r_meeting.getSponsor())
        {

            if(title == r_meeting.getTitle())
            {
                return true;
            }
        }
        return false;
    });
    cout << num <<endl;
 	/*
	Meeting m("zmx", par, d1, d2, "lalala");

	sto->createMeeting(m);
/*
	User u("zm2", "swe","5663@qq.com", "1563456");
	User u2("z2", "s7","753@qq.com", "15756");
	User u3("z4", "075","55663@qq.com", "158456");
	sto->createUser(u);
	sto->createUser(u2);
	sto->createUser(u3);
	std::list<User> all_userList = sto->queryUser([](const User& a)->bool {
        if (1)
            return true;    
    });
    for (auto i = all_userList.begin(); i != all_userList.end(); i++)
    {
    	cout <<(*i).getName()<<endl;
    }
	/*
	string userName = "zm2";
	string password = "swe";
	sto->deleteUser([&](const User& log_user)->bool {
    if (userName == log_user.getName())
    {
        if(password == log_user.getPassword())
        {
            return true;
        }
    }
    return false;
    });
	*/
/*
	if(sto->sync())
	{
		cout <<"xiugaile"<<endl;
	}
	else
	cout <<"meiyouxiugai"<<endl;
	
	return 0;
}
*/
