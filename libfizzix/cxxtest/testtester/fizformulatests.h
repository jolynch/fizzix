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
			
			fizstack n;
			n.push(new FizFormAnonConst(fizdatum(vec3(1,2,4))));
			n.push(new FizFormAnonConst(fizdatum(3)));
			n.push(new FizOper::Quotient(2));
			n.push(new FizFormAnonConst(fizdatum(vec3(1,8,3))));
			n.push(new FizOper::Dot(2));
			FizFormula p = FizFormula(n);
			TS_ASSERT_EQUALS(p.toString(),"(.* (/ <1 2 4> 3) <1 8 3>)");
			double x = p.eval(defo, deft, defo, deft).scalar;
			TS_ASSERT_EQUALS(x,1/3.+16/3.+4);
		}
};

#endif
