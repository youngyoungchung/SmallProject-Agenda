#include <sstream>
#include "Date.hpp"


Date::Date()
{
  m_year = 0;
  m_month = 0;
  m_day = 0;
  m_hour = 0;
  m_minute = 0;
}

Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute)
{
  m_year = t_year;
  m_month = t_month;
  m_day = t_day;
  m_hour = t_hour;
  m_minute = t_minute;
}


Date::Date(std::string dateString)                 
{
    *this = stringToDate(dateString);
}

int Date::getYear(void) const
{
  return m_year;
}


void Date::setYear(const int t_year)
{
    m_year = t_year;
}


int Date::getMonth(void) const
{
  return m_month;
}


void Date::setMonth(const int t_month)
{

    m_month = t_month;
}


int Date::getDay(void) const
{
  return m_day;
}

void Date::setDay(const int t_day)
{

  m_day = t_day;

}

int Date::getHour(void) const
{
  return m_hour;
}


void Date::setHour(const int t_hour)
{
    m_hour = t_hour;
}
  

int Date::getMinute(void) const
{
  return m_minute;
}

void Date::setMinute(const int t_minute)
{
  m_minute = t_minute;
}

  /**
  *   @brief check whether the date is valid or not
  *   @return the bool indicate valid or not
  */
bool Date::isValid(const Date t_date)
{
  
  if (t_date.getYear() > 9999 || t_date.getYear() < 1000)
  {
    return false;
  }
 
  if (t_date.getMonth() < 1 || t_date.getMonth() > 12)
  {
    return false;
  }
  
  if (t_date.getMonth() == 2 && ( (t_date.getYear()%4 == 0&& t_date.getYear()%100 != 0) || t_date.getYear()%400 ==0 ) ) //29
  {
    if (t_date.getDay()< 1 || t_date.getDay() > 29)
    {
      return false;
    }
  }
  if (t_date.getMonth() == 2 && !((t_date.getYear()%4 == 0&& t_date.getYear()%100 != 0) || t_date.getYear()%400 ==0 ) ) //28
  {
    if (t_date.getDay() < 1 || t_date.getDay() > 28)
    {
      return false;
    }
  }
  if (t_date.getMonth()== 1 || t_date.getMonth() ==3 || t_date.getMonth() ==5 || t_date.getMonth() ==7 || t_date.getMonth() ==8 || t_date.getMonth() ==10 || t_date.getMonth() ==12)
  {
    if (t_date.getDay() < 1 || t_date.getDay() > 31)
    {
      return false;
    }
  }

  if (t_date.getMonth() == 4 || t_date.getMonth() ==6 || t_date.getMonth() ==9 || t_date.getMonth() ==11 )
  {
    if (t_date.getDay() < 1 || t_date.getDay() > 30)
    {
      return false;
    }
  }
  if (t_date.getHour()> 23 || t_date.getHour() < 0)
  {
    return false;
  }
 
  if (t_date.getMinute() > 59 || t_date.getMinute() < 0)
  {
    return false;
  }
 
  return true;
}


  /**
  * @brief convert a string to date, if the format is not correct return
  * 0000-00-00/00:00
  * @return a date
  */
Date Date::stringToDate(const std::string t_dateString)                    
{
  if (t_dateString[4] != '-' || t_dateString[7] !='-' || t_dateString[10] != '/' || t_dateString[13] != ':')
  {
    return Date(0,0,0,0,0);
  }
  if ( t_dateString.length() != 16)
  {
    return Date(0,0,0,0,0);
  }
  if (t_dateString[0] < '0' || t_dateString[0] > '9' 
    || t_dateString[1] < '0' || t_dateString[1] > '9'
    || t_dateString[2] < '0' || t_dateString[2] > '9'
    || t_dateString[3] < '0' || t_dateString[3] > '9'
    || t_dateString[5] < '0' || t_dateString[5] > '9'
    || t_dateString[6] < '0' || t_dateString[6] > '9'
    || t_dateString[8] < '0' || t_dateString[8] > '9'
    || t_dateString[9] < '0' || t_dateString[9] > '9'
    || t_dateString[11] < '0' || t_dateString[11] > '9'
    || t_dateString[12] < '0' || t_dateString[12] > '9'
    || t_dateString[14] < '0' || t_dateString[14] > '9'
    || t_dateString[15] < '0' || t_dateString[15] > '9')
  {
    return Date(0,0,0,0,0);
  }
  std::string s1 = t_dateString.substr(0, 4);
  std::string s2 = t_dateString.substr(5, 2);
  std::string s3 = t_dateString.substr(8, 2);
  std::string s4 = t_dateString.substr(11, 2);
  std::string s5 = t_dateString.substr(14, 2);

  std::stringstream ss1(s1);
  std::stringstream ss2(s2);
  std::stringstream ss3(s3);
  std::stringstream ss4(s4);
  std::stringstream ss5(s5);
  int ye = 0, mo = 0, da = 0, ho = 0, mi = 0;
  ss1 >> ye;
  ss2 >> mo;
  ss3 >> da;
  ss4 >> ho;
  ss5 >> mi;
  Date res;
  res.setYear(ye);
  res.setMonth(mo);
  res.setDay(da);
  res.setHour(ho);
  res.setMinute(mi);
  return res;
}


  /**
  * @brief convert a date to string, if the format is not correct return
  * 0000-00-00/00:00
  */                                     
  std::string Date::dateToString(Date t_date)                 //Date format erro??????
  {
    if (!(isValid(t_date)))
    {
      return "0000-00-00/00:00";
    }
    else
    {
    std::ostringstream ss;
    ss << t_date.getYear();
    std::string ye = ss.str();
    ss.str("");
    ss << t_date.getMonth();
    std::string mo = ss.str();
    ss.str("");
    ss << t_date.getDay();
    std::string da = ss.str();
    ss.str("");
    ss << t_date.getHour();
    std::string ho = ss.str();
    ss.str("");
    ss << t_date.getMinute();
    std::string mi = ss.str();

    if (mo.length() == 1)
    {
      mo = '0' + mo;
    }
    if (da.length() == 1)
    {
      da = '0' + da;
    }
    if (ho.length() == 1)
    {
      ho = '0' + ho;
    }
    if (mi.length() == 1)
    {
      mi = '0' + mi;
    }
    std::string res = ye + '-' + mo + '-' + da + '/' + ho + ':' + mi;
    return res;
  }
  }

  /**
  *  @brief overload the assign operator
  */
  Date & Date::operator=(const Date &t_date)
  {
    m_year = t_date.getYear();
    m_month = t_date.getMonth();
    m_day = t_date.getDay();
    m_hour = t_date.getHour();
    m_minute = t_date.getMinute();
    return *this;

  }

  /**
  * @brief check whether the CurrentDate is equal to the t_date
  */
  bool Date::operator==(const Date &t_date) const
  {
    if (m_year == t_date.getYear() && m_month == t_date.getMonth() && m_day == t_date.getDay() && m_minute == t_date.getMinute() && m_hour == t_date.getHour())
      return true;
    return false;
  }

  /**
  * @brief check whether the CurrentDate is  greater than the t_date
  */
  bool Date::operator>(const Date &t_date) const
  {
    if (m_year > t_date.getYear() || m_year == t_date.getYear() && m_month > t_date.getMonth() || 
      m_year == t_date.getYear() && m_month == t_date.getMonth() && m_day > t_date.getDay() ||
      m_year == t_date.getYear() && m_month == t_date.getMonth() && m_day == t_date.getDay() && m_hour >t_date.getHour() ||
      m_year == t_date.getYear() && m_month == t_date.getMonth() && m_day == t_date.getDay() && m_hour ==t_date.getHour() &&m_minute>t_date.getMinute())
      return true;
    return false;
  }

  /**
  * @brief check whether the CurrentDate is  less than the t_date
  */
  bool Date::operator<(const Date &t_date) const
  {
    if (*this > t_date || *this == t_date)
      return false;
    return true;
  }

  /**
  * @brief check whether the CurrentDate is  greater or equal than the t_date
  */
  bool Date::operator>=(const Date &t_date) const
  {
    if (*this < t_date)
      return false;
    return true;
  }

  /**
  * @brief check whether the CurrentDate is  less than or equal to the t_date
  */
  bool Date::operator<=(const Date &t_date) const
  {
    if (*this > t_date)
      return false;
    return true;
  }

