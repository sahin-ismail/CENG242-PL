#include "Bank.h"

using namespace std;


Bank::Bank(){
	_bank_name = "not defined";
	_user_count = 0;
	_users = nullptr;
}

Bank::Bank(std::string bank_name, Account* const users, int user_count){
	int i;
	_bank_name = bank_name;
	_user_count = user_count;
	if(user_count != 0){_users = new Account[_user_count];}
	if(users!=nullptr){	
		for(i = 0; i<user_count; i++){
			_users[i] = users[i];
		}
	}
}

Bank::~Bank(){
	_bank_name.erase();
	_user_count = 0;
	delete[] _users;

}

Bank::Bank(const Bank& rhs){
	int i;
	_bank_name = rhs._bank_name;
	_user_count = rhs._user_count;
	if(_user_count!=0){_users = new Account[_user_count];}
	if(rhs._users!=nullptr){	
		for(i = 0; i<_user_count; i++){
			_users[i] = rhs._users[i];
		}
	}

}

Bank& Bank::operator+=(const Bank& rhs){
	int i,j,count,c,k,l;
	Account* temp;
	c=k=0;
	if((_user_count != 0 )&&(rhs._user_count != 0)){
		for(i = 0; i<(_user_count); i++){
			for(j = 0; j<rhs._user_count; j++){
				if(_users[j] == rhs._users[i]){
					c++;
					break;
				}
			}
		}
		count = _user_count + rhs._user_count - c;
		temp = new Account[count];
		for(i = 0; i<_user_count;i++){
			temp[i] = _users[i];
		}
		k = _user_count;
		for(i = 0; i<rhs._user_count; i++){
			
			for(l = 0; l<_user_count; l++){
				if(_users[l]==rhs._users[i]){
					break;
				}
			}
			if(l==_user_count){l = -1;}

			if(l==-1){
				temp[k] = rhs._users[i];
				k++;
			}
			else{
				temp[l] += rhs._users[i];
			}

		}
		k = 0;
		delete[] _users;
		_users = temp;
		temp = nullptr;
		_user_count = count;
	}
	else if((_user_count == 0 )&&(rhs._user_count != 0)){
		_user_count = rhs._user_count;
		_users = new Account[_user_count];
		for(i = 0; i<_user_count; i++){
			_users[i] = rhs._users[i];
		}
	}
	else{

	}

}

Bank& Bank::operator+=(const Account& new_acc){
	int l,i;
	Account* temp;
	if(_users != nullptr){
		for(l = 0; l<_user_count; l++){
			if(_users[l]==new_acc){
				break;
			}
		}
	}	
	if(l==_user_count){l = -1;}

	if(l==-1){
		temp = new Account[(_user_count+1)];
		if(_users != nullptr && temp != nullptr){
			for(i = 0; i<_user_count; i++){
				temp[i] = _users[i];
			}

			temp[i] = new_acc;
			delete[] _users;
			_users = temp;
			temp = nullptr;
			_user_count++;
		}
		
	}
	else{
		_users[l] += new_acc;
	}
}

Account& Bank::operator[](uint account_id){
	int i;
	if(_users != nullptr){
		for(i = 0;i<_user_count;i++){
			if(_users[i]==account_id){
				return _users[i];
			}
		}
		return _users[0];
	}
}

ostream& operator<<(std::ostream& os, const Bank& bank){
int el,i,j,count,t;
double total;
time_t t0;
time_t t1;
struct tm times0 = {0};
struct tm times1 = {0};
count = -1;
total = 0;
t = 0;
el=0;
if(bank._users != nullptr){
	for(i=0;i<bank._user_count;i++){
		count = -1;
		if(bank._users!=nullptr){
			t=0;
			times0.tm_hour=23;
			times0.tm_min=59;
			times0.tm_sec=59; 
			times0.tm_mday=31;
			times0.tm_mon=11;
			times0.tm_year=118;
			times1.tm_hour=0;
			times1.tm_min=0;
			times1.tm_sec=0; 
			times1.tm_mday=1;
			times1.tm_mon=1;
			times1.tm_year=119;
			t0 = mktime(&times0);
			t1 = mktime(&times1);
			for(j=0;j<12;j++){
				if(t==1&&(bank._users[i].balance(t0,t1))<0){
					count = 0;
					break;
				}
				else if (t==0&&(bank._users[i].balance(t0,t1))<0){
					t = 1;
				}
				else if (t==1&&(bank._users[i].balance(t0,t1))>=0){
					t = 0;
				}
				else{

				}
				times0.tm_mon++;
				times1.tm_mon++;
				t0 = mktime(&times0);
				t1 = mktime(&times1);
			}
		}
		if(count == -1){
			el++;
		}



		total+=bank._users[i].balance();
	}
}

os<<bank._bank_name<<"\t"<<el<<"\t"<<total<<"\n";
return os;
}

