#include "Transaction.h"

using namespace std;


    Transaction::Transaction(){
    	this->_amount = -1;
    	this->_date = -1;
    }


    Transaction::Transaction(double amount, time_t date){
    	this->_amount = amount;
    	this->_date = date;
    }

    Transaction::Transaction(const Transaction& rhs){
    	this->_amount = rhs._amount;
    	this->_date = rhs._date;
    }

    bool Transaction::operator<(const Transaction& rhs) const{
    	if(this->_date < rhs._date){
    		return true;
    	}
    	else{
    		return false;
    	}
    }

    bool Transaction::operator>(const Transaction& rhs) const{
    	if(this->_date > rhs._date){
    		return true;
    	}
    	else{
    		return false;
    	}    	
    }

    bool Transaction::operator<(const time_t date) const{
    	if(this->_date < date){
    		return true;
    	}
    	else{
    		return false;
    	}    	
    } 
	bool Transaction::operator>(const time_t date) const{
    	if(this->_date > date){
    		return true;
    	}
    	else{
    		return false;
    	}    	
    }
    double Transaction::operator+(const Transaction& rhs){
    	return this->_amount + rhs._amount;
    }
	double Transaction::operator+(const double add){
		return this->_amount + add;
	}

	Transaction& Transaction::operator=(const Transaction& rhs){
		this->_date = rhs._date;
		this->_amount = rhs._amount;
	}
	
	ostream& operator<<(std::ostream& os, const Transaction& transaction){
		struct tm * times = localtime(&(transaction._date));
		os << transaction._amount<<"\t-\t"<<times->tm_hour<<":"<<times->tm_min<<":"<<times->tm_sec<<"-"<<times->tm_mday<<"/"<<((times->tm_mon)+1)<<"/"<<((times->tm_year)+1900)<<"\n";
    	return os;	
	}