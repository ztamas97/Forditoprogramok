#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class function{
public:
	virtual double calc(double a, double b)=0;
	virtual ~function();
};

class illegal_input{};

struct number{
	double value;
	double magnitude;
};

class parser{
  private:
    string input;
    unsigned int pos;

    char LookAhead(){
      return input[pos];
    }
    void Match(const char c){
      if (LookAhead()==c)
        pos++;
      else
        throw illegal_input();
    }
    double D(){
    	double value;
    	if (LookAhead()>='0' && LookAhead()<='9'){
    		value=LookAhead()-'0';
    		Match(LookAhead());
    	}
    	else
    		throw illegal_input();
    	return value;
    }
    number N_(){
    	double digitValue;
    	number num,returnValue;
    	if (LookAhead()>='0' && LookAhead()<='9'){
    		digitValue=D();
    		num=N_();
    		returnValue.magnitude=num.magnitude*10;
    		returnValue.value=digitValue*num.magnitude+num.value;
    	}
    	else
    	if (LookAhead()=='+' ||
    		LookAhead()=='-' ||
    		LookAhead()=='*' ||
    		LookAhead()=='/' ||
    		LookAhead()==')' ||
    		LookAhead()=='$'
    		)
    	{
    		returnValue.value=0.0;
    		returnValue.magnitude=1.0;
		}
    	else
    		throw illegal_input();
    	return returnValue;
    }
	double N(){
		double digitValue,value;
		number num;
		if (LookAhead()>='0' && LookAhead()<='9'){
			digitValue=D();
			num=N_();
    		value=digitValue*num.magnitude+num.value;
		}
		else
			throw illegal_input();
		return value;
    }
	double F();
	double T_(){
		double value;
		char c;
		if (LookAhead()=='*' || LookAhead()=='/'){
			c=LookAhead();
			Match(c);
			value=F();
			if (c=='/')
				value=1/value;
			value*=T_();
		}
		else
		if (LookAhead()=='+' || LookAhead()=='-' ||
			LookAhead()==')' || LookAhead()=='$'){
			value=1.0;
		}
		else
			throw illegal_input();
		return value;
	}
	double T(){
		double value;
		if (LookAhead()>='0' && LookAhead()<='9'){
			value=F();
			value*=T_();
		}
		else
		if (LookAhead()=='('){
			value=F();
			value*=T_();
		}
		else if (LookAhead() == 'l' || LookAhead() == 'e')
        {
            value=F();
			value*=T_();
        }
		else
			throw illegal_input();
		return value;
	}
	double E_(){
		double value;
		char c;
		if (LookAhead()=='+' || LookAhead()=='-'){
			c=LookAhead();
			Match(c);
			value=T();
			value+=E_();
			if (c=='-')
				value*=-1.0;
		}
		else
		if (LookAhead()==')' || LookAhead()=='$'){
			value=0.0;
		}
		else
			throw illegal_input();
		return value;
	}
	double E(){
		double value;
		if (LookAhead()>='0' && LookAhead()<='9'){
			value=T();
			value+=E_();
		}
		else
		if (LookAhead()=='('){
			value=T();
			value+=E_();
		}else if(LookAhead()=='l' || LookAhead()=='e'){
		    value = T();
            value += E_();
		}
		else
			throw illegal_input();
		return value;
	}
	
	double MLn(double value)
    {
        Match('l');
        Match('n');
        Match('(');
        return std::log(N());
    }
    double MExp(double value)
    {
        Match('e');
        Match('x');
        Match('p');
        Match('(');
        return std::exp(N());
    }
  public:
    void Parse(const string &s){
      input=s+'$';
      pos=0;
      double value=E();
      //cout<<endl<<"value: "<<value;
      Match('$');
    }
};

double parser::F(){
	double value;
	if (LookAhead()>='0' && LookAhead()<='9'){
		value=N();
	}
	else
	if (LookAhead()=='('){
		Match('(');
		value=E();
		Match(')');
	}
	else if(LookAhead()=='l'){
	    MLn(value);
	    Match(')');
	}else if(LookAhead()=='e'){
	    MExp(value);
	    Match(')');
	}
	else
		throw illegal_input();
	return value;
}


int main(){
  string cases[] = {"5*exp(2)", "10*sin(1)", "6*ln(4)", "5*log(2)", "4+ln(2)-10", "exp(2)+sin(2)"};
  
  for (string c : cases){
      try{
        parser().Parse(c);
        cout<<endl<<c<<endl;
        cout<<"Accepted!"<<endl;
        cout<<"------------"<<endl;
        }
      catch(illegal_input){
        cout<<endl<<c<<endl;
        cout<<"Not accepted!"<<endl;
        cout<<"------------"<<endl;
      }
  }
  return 0;
}