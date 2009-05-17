//after installing cxxtest
//cxxtestgen.pl --error-printer -o runner.cpp fizformulatests.h
//g++ -o runner runner.cpp -lfizzix && ./runner

#ifndef FIZFORMULATESTS_H
#define FIZFORMULATESTS_H

#include <cxxtest/TestSuite.h>
#include <libfizzix/fizformula.h>
#include <libfizzix/gen_structs.h>
#include <libfizzix/fizformoperators/operators.h>
#include <libfizzix/fizsphere.h>
#include <libfizzix/fizformnode.h>
#include <math.h>

class FizFormulaTests: public CxxTest::TestSuite
{
	public:
		void testFormula(void)
		{
			fizstack deff = fizstack(); FizObject defo = FizObject(); triangle deft = triangle();
			
			FizStack<FizFormNode*> s;
			fizdatum foo = fizdatum(vec3(4,6,2));
			TS_ASSERT_EQUALS(foo.vector[0],4);
			TS_ASSERT_EQUALS(foo.vector[1],6);
			TS_ASSERT_EQUALS(foo.vector[2],2);
			
			FizFormAnonConst xs = FizFormAnonConst(foo);
			vec3 z = xs.getValue().vector;
			TS_ASSERT_EQUALS(z[0],4);
			TS_ASSERT_EQUALS(z[1],6);
			TS_ASSERT_EQUALS(z[2],2);
			TS_ASSERT_EQUALS(xs.toString(deff), "<4 6 2>");
			
			FizFormNode* a = new FizFormAnonConst(foo);
			z = a->eval(deff, defo, deft, defo, deft).vector;
			TS_ASSERT_EQUALS(z[0],4);
			TS_ASSERT_EQUALS(z[1],6);
			TS_ASSERT_EQUALS(z[2],2);
			TS_ASSERT_EQUALS(a->toString(deff), "<4 6 2>");

			s.push(a);
			FizFormNode* b = new FizFormAnonConst(fizdatum(vec3(8,1,3)));
			s.push(b);
			FizFormNode* c = new FizFormAnonConst(fizdatum(vec3(1,0,1)));
			s.push(c);
			FizFormNode* d = new FizOper::Sum(3);
			s.push(d);
			s.reset();
			TS_ASSERT_EQUALS(s.pop()->toString(s),"(+ <4 6 2> <8 1 3> <1 0 1>)");
			s.reset();
			FizFormula f = FizFormula(s);
			TS_ASSERT_EQUALS(f.toString(),"(+ <4 6 2> <8 1 3> <1 0 1>)")
			vec3 i = f.eval(FizSphere(),triangle(),FizSphere(),triangle()).vector;
			TS_ASSERT_EQUALS(i[0],13);
			TS_ASSERT_EQUALS(i[1],7);
			TS_ASSERT_EQUALS(i[2],6);
			s.reset();
		}
		
		void testOperators(void)
		{
			fizstack deff = fizstack(); FizObject defo = FizObject(); triangle deft = triangle();

			
			fizstack n;
			n.push(new FizFormAnonConst(fizdatum(vec3(1,2,4))));
			n.push(new FizFormAnonConst(fizdatum(3)));
			n.push(new FizOper::Quotient(2));
			n.push(new FizFormAnonConst(fizdatum(vec3(1,8,3))));
			n.push(new FizOper::Dot(2));
			n.push(new FizOper::Exponentiate(1));
			FizFormula p = FizFormula(n);
			TS_ASSERT_EQUALS(p.toString(),"(exp (.* (/ <1 2 4> 3) <1 8 3>))");
			double x = p.eval(defo, deft, defo, deft).scalar;
			TS_ASSERT_EQUALS(x,exp(1/3.+16/3.+4));
			
			n = fizstack();
			n.push(new FizFormAnonConst(fizdatum(5)));
			n.push(new FizFormAnonConst(fizdatum(4)));
			n.push(new FizFormAnonConst(fizdatum(3)));
			n.push(new FizFormAnonConst(fizdatum(9)));
			n.push(new FizFormAnonConst(fizdatum(1)));
			n.push(new FizOper::Quotient(5));
			p = FizFormula(n);
			TS_ASSERT_EQUALS(p.toString(),"(/ 5 4 3 9 1)");
			x = p.eval(defo, deft, defo, deft).scalar;
			TS_ASSERT_DELTA(x,5/4./3./9.,.00001);
			
			n = fizstack();
			n.push(new FizFormAnonConst(fizdatum(7)));
			n.push(new FizOper::Factorial(1));
			n.push(new FizFormAnonConst(fizdatum(8)));
			n.push(new FizFormAnonConst(fizdatum(9)));
			n.push(new FizFormAnonConst(fizdatum(10)));
			n.push(new FizOper::Product(3));
			n.push(new FizFormAnonConst(fizdatum(80)));
			n.push(new FizOper::Difference(3));
			p = FizFormula(n);
			//TS_ASSERT_EQUALS(p.toString(),"(! 7)");
			x = p.eval(defo, deft, defo, deft).scalar;
			TS_ASSERT_EQUALS(x,7*6*5*4*3*2-8*9*10-80);
			
			n = fizstack();
			n.push(new FizFormAnonConst(fizdatum(M_PI)));
			n.push(new FizFormAnonConst(fizdatum(2)));
			n.push(new FizOper::Quotient(2));
			n.push(new FizOper::Sine(1));
			n.push(new FizFormAnonConst(fizdatum(3)));
			n.push(new FizFormAnonConst(fizdatum(.5)));
			n.push(new FizOper::Exponent(2));
			n.push(new FizFormAnonConst(fizdatum(2)));
			n.push(new FizOper::Quotient(2));
			n.push(new FizOper::Arccos(1));
			n.push(new FizFormAnonConst(fizdatum(10)));
			n.push(new FizFormAnonConst(fizdatum(2)));
			n.push(new FizOper::Logarithm(2));
			n.push(new FizOper::Vectorize(3));
			p = FizFormula(n);
			vec3 i = p.eval(defo, deft, defo, deft).vector;
			TS_ASSERT_EQUALS(i[0],1);
			TS_ASSERT_DELTA(i[1],M_PI/6,.00001);
			TS_ASSERT_EQUALS(i[2],log(10)/log(2));
			
			n = fizstack();
			n.push(new FizFormAnonConst(fizdatum(-1)));
			n.push(new FizOper::Arcsin(1));
			n.push(new FizFormAnonConst(fizdatum(sqrt(3))));
			n.push(new FizOper::Arctan(1));
			n.push(new FizFormAnonConst(fizdatum(M_PI/3)));
			n.push(new FizOper::Cosine(1));
			n.push(new FizOper::Vectorize(3));
			n.push(new FizFormAnonConst(fizdatum(2)));
			n.push(new FizOper::Cosh(1));
			n.push(new FizFormAnonConst(fizdatum(2)));
			n.push(new FizOper::Sinh(1));
			n.push(new FizFormAnonConst(fizdatum(2)));
			n.push(new FizOper::Tanh(1));
			n.push(new FizOper::Vectorize(3));
			n.push(new FizOper::Cross(2));
			p = FizFormula(n);
			i = p.eval(defo, deft, defo, deft).vector;
			TS_ASSERT_EQUALS(p.toString(),"(X* <(asin -1) (atan 1.73205) (cos 1.0472)> <(cosh 2) (sinh 2) (tanh 2)>)");
			TS_ASSERT_DELTA(i[0],M_PI/3*tanh(2)-sinh(2)/2,.00001);
			TS_ASSERT_DELTA(i[1],cosh(2)/2 + M_PI/2*tanh(2),.00001);
			TS_ASSERT_EQUALS(i[2],0 - M_PI/2*sinh(2) - M_PI*cosh(2)/3);
			
			n = fizstack();
			n.push(new FizFormAnonConst(fizdatum(vec3(3,4,5))));
			n.push(new FizOper::Magnitude(1));
			n.push(new FizFormAnonConst(fizdatum(4)));
			n.push(new FizOper::Less(2));
			n.push(new FizFormAnonConst(fizdatum(4)));
			n.push(new FizOper::Square(1));
			n.push(new FizFormAnonConst(fizdatum(8)));
			n.push(new FizOper::Tangent(1));
			n.push(new FizOper::If(3));
			p = FizFormula(n);
			x = p.eval(defo, deft, defo, deft).scalar;
 			TS_ASSERT_EQUALS(x,tan(8));
			
			n = fizstack();
			n.push(new FizFormAnonConst(fizdatum(1)));
			n.push(new FizFormAnonConst(fizdatum(2)));
			n.push(new FizOper::Less(2));
			n.push(new FizFormAnonConst(fizdatum(5)));
			n.push(new FizFormAnonConst(fizdatum(4)));
			n.push(new FizOper::Equal(2));
			n.push(new FizOper::Or(2));
			p = FizFormula(n);
			x = p.eval(defo, deft, defo, deft).scalar;
 			TS_ASSERT_EQUALS(x,1);
			
			n = fizstack();
			n.push(new FizOper::Random(0));
			p = FizFormula(n);
			x = p.eval(defo, deft, defo, deft).scalar;
 			TS_ASSERT_DIFFERS(x,-1000);
		}
};

#endif
