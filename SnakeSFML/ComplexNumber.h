#pragma once
class ComplexNumber
{
public:
	ComplexNumber();
	ComplexNumber(double real);
	ComplexNumber(double real, double imaginary);
	double getRe();
	double getIm();
	void setRe();
	void setIm();
private:
	double re;
	double im;
};

