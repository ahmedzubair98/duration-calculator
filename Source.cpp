#include<iostream>
using namespace std;


struct Date
{
	int d, m, y;
};


const int monthDays[12] = { 31, 28, 31, 30, 31, 30,
31, 31, 30, 31, 30, 31 };


int countLeapYears(Date d)
{
	int years = d.y;

	if (d.m <= 2)
		years--;

	return years / 4 - years / 100 + years / 400;
}


int getDifference(Date dt1, Date dt2)
{
	
	int n1 = (dt1.y * 365) + dt1.d;

	for (int i = 0; i<dt1.m - 1; i++)
		n1 += monthDays[i];
	n1 += countLeapYears(dt1);

	int n2 = dt2.y * 365 + dt2.d;
	for (int i = 0; i<dt2.m - 1; i++)
		n2 += monthDays[i];
	n2 += countLeapYears(dt2);

	return (n2 - n1 - 1);
}
Date duration(long int d)
{
	Date temp{ 0,0,0 };
	for (; d > 365; d -= 365)
	{
		temp.y++;
	}
	for (int i = 0; d > monthDays[i]; i++)
	{
		d -= monthDays[i];
		temp.m++;
		if (i == 11)
			i = -1;
	}
	if (d > 0)
		temp.d += d;
	for (int i = 0; i <= temp.y; i += 4)
	{
		if(i != 0)
			temp.d++;
	}
	return temp;
}
Date add(Date arr[],int size)
{
	Date temp{ 0,0,0 };
	for (int i = 0; i < size; i++)
	{
		temp.y += arr[i].y;
	}
	for (int i = 0; i < size; i++)
	{
		temp.m += arr[i].m;
		while (temp.m >= 12)
		{
			temp.m = 0;
			temp.y++;
		}
	}
	for (int i = 0; i < size; i++)
	{
		temp.d += arr[i].d;
		while (temp.d >= monthDays[temp.m])
		{
			temp.d = 0;
			temp.m++;
			if(temp.m >= 12)
			{
				temp.m = 0;
				temp.y++;
			}
		}
	}
	return temp;
}

ostream& operator<<(ostream& os, const Date& dt)
{
	os << dt.d << '/' << dt.m << '/' << dt.y;
	return os;
}

int main()
{
	Date arr[20] = { {11,1,1992},{15,1,1993},{20,5,1993},{2,3,1996},{3,3,1996},{30,6,1997},{17,12,1997},{6,3,1998},{6,3,1998},{27,2,2001}, {27,2,2001},{19,9,2008},{20,9,2008},{2,2,2010},{2,2,2010},{4,2,2014},{5,2,2014},{19,5,2016},{19,5,2016},{17,7,2017} };
	long int dur[10];
	for (int i = 0,j = 0; i < 19; i+=2,j++)
	{
		dur[j] = getDifference(arr[i], arr[i + 1]);
	}
	Date dur2[10];
	for (int i = 0; i < 10; i++)
	{
		dur2[i] = duration(dur[i]);
	}
	for (int i = 0,j=0; i < 19; i += 2,j++)
	{
		cout <<j+1<<"_ "<< arr[i] << " ---- " << arr[i + 1] << endl;
	}
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << i+1 << "_ " << dur2[i].y << " Years " << dur2[i].m << " Months " << dur2[i].d << " Days " << endl;
	}
	cout << endl;
	cout << "total: " << add(dur2, 10).y<<" Years "<<add(dur2,10).m<<" Months "<< add(dur2,10).d<<" Days " << endl;
	return 0;
}