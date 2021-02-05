//source for rational class

#include "rational.h"

//constructor
//precondition:  newDen cannot be zero
Rational::Rational(int const newNum, int const newDen) {
	sgn = 1;

	if (newDen == 0) {
		cout << "Error creating rational; denominator cannot be zero" << endl;
	}
	else if (newDen < 0) {
		sgn = -sgn;
		den = -newDen;
	}
	else {
		den = newDen;
	}

	if (newNum < 0) {
		sgn = -sgn;
		num = -newNum;
	}
	else {
		num = newNum;
	}
	//call reduce here
	this->reduce();
}

//copy constructor
Rational::Rational(Rational const & original) {
	*this = original;
}

//assignment
Rational & Rational::operator=(Rational const & rhs) {
	num = rhs.num;
	den = rhs.den;
	sgn = rhs.sgn;
	return *this;
}

//includes error message for invalid input
void Rational::setSgn(int const newSgn) {
	if (newSgn != 1 && newSgn != -1) {
		cout << "Error in fcn: setSgn" << endl << "intput is " << newSgn
			<< ", +1 or -1 expected" << endl;
		return;
	}
	sgn = newSgn;
}

//reduces fraction to lowest terms, requires findGCD
void Rational::reduce() {
	//if the numerator is zero, then lowest form is 0/1
	if (num == 0) {
		den = 1;
		return;
	}
	int GCD = findGCD(num, den);
	num /= GCD;
	den /= GCD;
}

//reads rational input from console
istream & operator>>(istream & lhs, Rational & rhs) {
	char tempCharr = '\0';
	int tempInt = 0;
	cin >> tempInt;
	if (tempInt < 0) {
		rhs.setSgn(-1);
		rhs.setNum(-tempInt);
	}
	else
	{
		rhs.setSgn(1);
		rhs.setNum(tempInt);
	}

	//did the user only enter a whole number?  no problem, let's check.
	if (cin.peek() == '\n') {
		rhs.setDen(1);
	}
	else {
		cin >> tempCharr;
		cin >> tempInt;
		if (tempInt == 0) {
			cout << endl << "Error: denominator cannot be zero." << endl;
			cout << "Probable unreliable output beyond this point." << endl;
		}
		else if (tempInt < 0) {
			rhs.setSgn(rhs.getSgn() * -1);
			rhs.setDen(-tempInt);
		}
		else {
			rhs.setDen(tempInt);
		}
	}

	//call reduce here
	if (rhs.getDen() != 0) {
		rhs.reduce();
	}

	return lhs;
}

//displays rational to console
ostream & operator<<(ostream & lhs, Rational const & rhs) {
	if (rhs.getSgn() == -1) {
		cout << "-";
	}
	cout << rhs.getNum();
	if (rhs.getDen() != 1) {
		cout << "/" << rhs.getDen();
	}
	return lhs;
}

//returns greatest common divisor of n1 and n2
//implements Stein's algorithm for computational speed
//precondition - n1 > 0, n2 > 0
unsigned int findGCD(int n1, int n2) {
	//checks precondition - if fails prints warning and returns 0
	//(which is never a valid GCD)
	if (n1 <= 0 || n2 <= 0) {
		cout << "Warning: invalid arguments (<= 0) in find GCD" << endl;
		cout << "Function did not execute; returning 0" << endl;
		return 0;
	}

	//if the two numbers are equal to each other then they
	//are by definition the GCD
	if (n1 == n2) {
		return n1;
	}

	int commonPwrsOfTwo = 0;
	//if both numbers still even
	while (n1 % 2 == 0 && n2 % 2 == 0) {
		n1 = n1 >> 1;
		n2 = n2 >> 1;
		commonPwrsOfTwo++;
	}

	//if one number still even
	while (n1 % 2 == 0) {
		n1 = n1 >> 1;
	}
	while (n2 % 2 == 0) {
		n2 = n2 >> 1;
	}

	//both numbers now odd
	//assign n1 to c so that if n1 = n2 already that will simply be the
	//non-powers of 2 component of the GCD
	int c = n1;
	while (n1 != n2) {
		//c is the (positive) difference between n1 and n2
		//premise of Stein's alg: GCD(smaller of n1 and n2, c) is the same
		//as GCD(n1, n2), so replace the larger of n1 and n2 by c
		
		c = n1 - n2;
		//c cannot be 0 here b/c that would imply n1 == n2 earlier
		if (c < 0) {
			c *= -1;
		}
		//c is guaranteed to be even right now, so bitshift c
		while (c % 2 == 0) {
			c = c >> 1;
		}
		//figure out which one to replace
		if (n1 > n2) {
			n1 = c;
		}
		else {
			n2 = c;
		}
	}
	//at this point n1 = n2 = c 
	//GCD is now c * 2 ^ (commonPwrsOfTwo)
	int GCD = c << commonPwrsOfTwo;
	return GCD;
}

//also reduces result
Rational operator+(Rational const & lhs, Rational const & rhs) {
	int tempInt = 0;
	Rational result;
	//assume sign is positive, fix later if necessary
	result.setSgn(1);
	//for a/b + c/d, denom is simple b*d, will reduce later
	result.setDen(lhs.getDen() * rhs.getDen());
	//figure out numerator, including negative signs
	tempInt = lhs.getSgn() * lhs.getNum() * rhs.getDen() +
		rhs.getSgn() * rhs.getNum() * lhs.getDen();
	//is what will be the numerator negative?
	if (tempInt < 0) {
		result.setSgn(-1);
		tempInt = -tempInt;
	}
	result.setNum(tempInt);
	result.reduce();
	return result;
}

//also reduces result
Rational operator-(Rational const & lhs, Rational const & rhs) {
	int tempInt = 0;
	Rational result;
	//assume sign is positive, fix later if necessary
	result.setSgn(1);
	//for a/b + c/d, denom is simple b*d, will reduce later
	result.setDen(lhs.getDen() * rhs.getDen());
	//figure out numerator, including negative signs
	tempInt = lhs.getSgn() * lhs.getNum() * rhs.getDen() -
		rhs.getSgn() * rhs.getNum() * lhs.getDen();
	//is what will be the numerator negative?
	if (tempInt < 0) {
		result.setSgn(-1);
		tempInt = -tempInt;
	}
	result.setNum(tempInt);
	result.reduce();
	return result;
}

//also reduces result
Rational operator*(Rational const & lhs, Rational const & rhs) {
	Rational result;
	result.setSgn(lhs.getSgn() * rhs.getSgn());
	result.setNum(lhs.getNum() * rhs.getNum());
	result.setDen(lhs.getDen() * rhs.getDen());
	result.reduce();
	return result;
}

//also reduces result
Rational operator/(Rational const & lhs, Rational const & rhs) {
	Rational result;
	result.setSgn(lhs.getSgn() * rhs.getSgn());
	result.setNum(lhs.getNum() * rhs.getDen());
	result.setDen(lhs.getDen() * rhs.getNum());
	result.reduce();
	return result;
}

//checks to see if two rational numbers are equivalent
bool operator==(Rational & lhs, Rational & rhs) {
	//reduces both fractions before attempting match
	lhs.reduce();
	rhs.reduce();
	if (lhs.getSgn() == rhs.getSgn() &&
		lhs.getNum() == rhs.getNum() &&
		lhs.getDen() == rhs.getDen()) {
		return true;
	}
	else {
		return false;
	}
}