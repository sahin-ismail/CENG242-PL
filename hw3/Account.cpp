#include "Account.h"

using namespace std;


Account::Account(){
	_id = -1;
	_activity = nullptr;
	_monthly_activity_frequency = nullptr;
}



Account::Account(int id, Transaction** const activity, int* monthly_activity_frequency){
 	int i = 0;
 	int j = 0;
 	int k = 0;
 	int count = 0;
 	Transaction temp;
 	_id = id;
 	
 	_activity = new Transaction*[12];

 	for(i=0;i<12;i++){
 		count = monthly_activity_frequency[i];
 		
  		_activity[i] = new Transaction[count];
  		while(j<count){
 			_activity[i][j] = activity[i][j];
 			j++;
 		}
 		j=0;

		for(k = 0; k<count; k++) {
		   for(j = k+1; j<count; j++)
		   {
		      if(_activity[i][j] < _activity[i][k]) {
		         temp = _activity[i][k];
		         _activity[i][k] = _activity[i][j];
		         _activity[i][j] = temp;
		      }
		   }
		}

		k = 0;
		j = 0;
 	}
 	i = 0;

 	
 	_monthly_activity_frequency = new int[12];
 	for(i=0;i<12;i++){
 		_monthly_activity_frequency[i] = monthly_activity_frequency[i];
 	}
 	i=0;
}


Account::~Account(){
	int i;
	if(_activity != nullptr){
		for(i=0;i<12;i++){
			if(_activity[i]!=nullptr){delete[] _activity[i];}
		}
	}
	if(_activity != nullptr){delete[] _activity;}
	if(_activity != nullptr){delete[] _monthly_activity_frequency;}

}

Account::Account(const Account& rhs){
 	int i = 0;
 	int j = 0;
 	int k = 0;
 	int count = 0;
 	Transaction temp;
 	_id = rhs._id;

 	_activity = new Transaction*[12];
 	for(i=0;i<12;i++){
 		count = rhs._monthly_activity_frequency[i];

  		_activity[i] = new Transaction[count];
  		while(j<count){
 			_activity[i][j] = rhs._activity[i][j];
 			j++;
 		}
 		j=0;

		for(k = 0; k<count; k++) {
		   for(j = k+1; j<count; j++)
		   {
		      if(_activity[i][j] < _activity[i][k]) {
		         temp = _activity[i][k];
		         _activity[i][k] = _activity[i][j];
		         _activity[i][j] = temp;
		      }
		   }
		}

		k = 0;
		j = 0;
 	}
 	i = 0;


 	_monthly_activity_frequency = new int[12];
 	for(i=0;i<12;i++){
 		_monthly_activity_frequency[i] = rhs._monthly_activity_frequency[i];
 	}
 	i=0;
}

Account::Account(const Account& rhs, time_t start_date, time_t end_date){
 	int i = 0;
 	int j = 0;
 	int k = 0;
 	int count = 0;
 	int c = 0;
 	Transaction temp;
 	_id = rhs._id;

 	_activity = new Transaction*[12];

 	_monthly_activity_frequency = new int[12];
 	for(i=0;i<12;i++){
 		count = rhs._monthly_activity_frequency[i];
 		c = 0;
 		for(j=0;j<count;j++){
 			if((rhs._activity[i][j]>start_date)&&(rhs._activity[i][j]<end_date)){
 				c++;
 			}
 		}
 		j = 0;
 		_monthly_activity_frequency[i] = c;
 		if(c == 0){
 			_activity[i] = nullptr;
 		}
 		else{ 

 			_activity[i] = new Transaction[c];

	  		while(j<count){
	 			if((rhs._activity[i][j]>start_date)&&(rhs._activity[i][j]<end_date)){	
	 				_activity[i][k] = rhs._activity[i][j];
	 				j++;
	 				k++;
	 			}
	 			else{
	 				j++;
	 			}
	 		}
	 		j=0;
	 		k = 0;

			for(k = 0; k<c; k++) {
			   for(j = k+1; j<c; j++)
			   {
			      if(_activity[i][j] < _activity[i][k]) {
			         temp = _activity[i][k];
			         _activity[i][k] = _activity[i][j];
			         _activity[i][j] = temp;
			      }
			   }
			}

			k = 0;
			j = 0;
		}
 	}
 	i = 0;

}

Account::Account(Account&& rhs){
	int i;
	_id = rhs._id;
	_activity = rhs._activity;
	_monthly_activity_frequency = rhs._monthly_activity_frequency;
	rhs._id = -1;
	rhs._activity = nullptr;
	rhs._monthly_activity_frequency = nullptr;

}

Account& Account::operator=(Account&& rhs){
	int i = 0;
	if(_activity != nullptr){
		for(i=0;i<12;i++){
			if(_activity[i]!=nullptr){delete[] _activity[i];}
		}
	}
	if(_activity != nullptr){delete[] _activity;}
	if(_activity != nullptr){delete[] _monthly_activity_frequency;}
	_id = rhs._id;
	rhs._id = -1;
	_activity = rhs._activity;
	rhs._activity = nullptr;
	_monthly_activity_frequency = rhs._monthly_activity_frequency;
	rhs._monthly_activity_frequency = nullptr;
}

Account& Account::operator=(const Account& rhs){
	int i = 0;
	int j = 0;
 	int k = 0;
 	int count = 0;
 	Transaction temp;
	if(_activity != nullptr){
		for(i=0;i<12;i++){
			if(_activity[i]!=nullptr){delete[] _activity[i];}
		}
	}
	if(_activity != nullptr){delete[] _activity;}
	if(_activity != nullptr){delete[] _monthly_activity_frequency;}

 	i = 0;
 	_id = rhs._id;

 	_activity = new Transaction*[12];

 	for(i=0;i<12;i++){
 		count = rhs._monthly_activity_frequency[i];

  		_activity[i] = new Transaction[count];
  		while(j<count){
 			_activity[i][j] = rhs._activity[i][j];
 			j++;
 		}
 		j=0;

		for(k = 0; k<count; k++) {
		   for(j = k+1; j<count; j++)
		   {
		      if(_activity[i][j] < _activity[i][k]) {
		         temp = _activity[i][k];
		         _activity[i][k] = _activity[i][j];
		         _activity[i][j] = temp;
		      }
		   }
		}

		k = 0;
		j = 0;
 	}
 	i = 0;

 	_monthly_activity_frequency = new int[12];
 	for(i=0;i<12;i++){
 		_monthly_activity_frequency[i] = rhs._monthly_activity_frequency[i];
 	}
 	i=0;	

}

bool Account::operator==(const Account& rhs) const{
	if(_id == rhs._id){
		return true;
	}
	else{
		return false;
	}

}

bool Account::operator==(int id) const{
	if(_id == id){
		return true;
	}
	else{
		return false;
	}
}

Account& Account::operator+=(const Account& rhs){
int i,j,k,count, new_Count,c;
Transaction temp;
Transaction* t;
i = j = k = count = 0;
for(i = 0;i<12;i++){
	if((_monthly_activity_frequency[i] != 0)&&(rhs._monthly_activity_frequency[i] != 0)){
		new_Count = _monthly_activity_frequency[i]+rhs._monthly_activity_frequency[i];
		c = _monthly_activity_frequency[i];

		t = new Transaction[c];
		for(k = 0; k<c;k++){
			t[k] = _activity[i][k];
		}
		k = 0;
		delete[] _activity[i];
		_activity[i] = new Transaction[new_Count];
		for(k = 0; k<c;k++){
			_activity[i][k] = t[k];
		}
		k = 0;
		delete[] t;
	 	count = rhs._monthly_activity_frequency[i];
	 	j = _monthly_activity_frequency[i];
	 	k = 0;
		while(j<new_Count){
			_activity[i][j] = rhs._activity[i][k];
			j++;
			k++;
		}
		j=0;

		for(k = 0; k<new_Count; k++) {
		   for(j = k+1; j<new_Count; j++)
		   {
		      if(_activity[i][j] < _activity[i][k]) {
		         temp = _activity[i][k];
		         _activity[i][k] = _activity[i][j];
		         _activity[i][j] = temp;
		      }
		   }
		}

		k = 0;
		j = 0;
		_monthly_activity_frequency[i] = new_Count;
	}
	else if((_monthly_activity_frequency[i] == 0)&&(rhs._monthly_activity_frequency[i] != 0)){
		new_Count = rhs._monthly_activity_frequency[i];
	 	_activity[i] = new Transaction[new_Count];
	 	count = rhs._monthly_activity_frequency[i];
	 	j = _monthly_activity_frequency[i];
		while(j<count){
			_activity[i][j] = rhs._activity[i][j];
			j++;
		}
		j=0;

		for(k = 0; k<new_Count; k++) {
		   for(j = k+1; j<new_Count; j++)
		   {
		      if(_activity[i][j] < _activity[i][k]) {
		         temp = _activity[i][k];
		         _activity[i][k] = _activity[i][j];
		         _activity[i][j] = temp;
		      }
		   }
		}

		k = 0;
		j = 0;
		_monthly_activity_frequency[i] = new_Count;

	}
	else{

	}
}

}


double Account::balance(){
	int count,i,j,k;
	double sum;
	count = i = j = k = 0;
	sum = 0;
	if(_activity == nullptr || _monthly_activity_frequency == nullptr){
		return 0;
	}
	else{
		while(i<12){
			count = _monthly_activity_frequency[i];
			j = 0;
 			while(j<count){
 				sum = _activity[i][j] + sum;
 				j++;
 			}
 			i++;

  		}
  		return sum;
 	}
}

double Account::balance(time_t end_date){
	int count,i,j,k;
	double sum;
	count = i = j = k = 0;
	sum = 0;
	if(_activity == nullptr || _monthly_activity_frequency == nullptr){
		return 0;
	}
	else{
		while(i<12){
			count = _monthly_activity_frequency[i];
			j = 0;
 			while(j<count){
 				if(_activity[i][j]<end_date){
 					sum = _activity[i][j] + sum;
 					j++;
 				}
 				else{
 					j++;
 				}
 			}
 			i++;

  		}
  		return sum;
 	}
}

double Account::balance(time_t start_date, time_t end_date){
	int count,i,j,k;
	double sum;
	count = i = j = k = 0;
	sum = 0;
	if(_activity == nullptr || _monthly_activity_frequency == nullptr){
		return 0;
	}
	else{
		while(i<12){
			count = _monthly_activity_frequency[i];
			j = 0;
 			while(j<count){
 				if((_activity[i][j]<end_date)&&(_activity[i][j]>start_date)){
 					sum = _activity[i][j] + sum;
 					j++;
 				}
 				else{
 					j++;
 				}
 			}
 			i++;

  		}
  		return sum;
 	}
}

ostream& operator<<(std::ostream& os, const Account& account){

	int count,i,j,k;
	count = i = j = k = 0;
	if(account._activity == nullptr || account._monthly_activity_frequency == nullptr){
		os<<-1<<"\n";

	}
	else{

		os<<account._id<<"\n";
		while(i<12){
			count = account._monthly_activity_frequency[i];
			j = 0;
 			while(j<count){
 				os<<account._activity[i][j];
 				j++;
 			}
 			i++;
  		}
 	}
 	return os;

}

