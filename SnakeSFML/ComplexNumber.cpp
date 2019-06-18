#include "ComplexNumber.h"



ComplexNumber::ComplexNumber()
{
	re = 0.0;
	im = 0.0;
}

ComplexNumber::ComplexNumber(double real)
{
	re = real;
	im = 0.0;
}


ComplexNumber::ComplexNumber(double real, double imaginary)
{
	re = real;
	im = imaginary;
}


double ComplexNumber::getRe()
{
	return re;
}


double ComplexNumber::getIm()
{
	return im;
}


void ComplexNumber::setRe()
{
	// TODO: Dodaj kod implementacji w tym miejscu.
}


void ComplexNumber::setIm()
{
	// TODO: Dodaj kod implementacji w tym miejscu.
}
