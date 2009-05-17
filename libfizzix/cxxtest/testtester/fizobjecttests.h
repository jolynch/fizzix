//after installing cxxtest
//cxxtestgen.pl --error-printer -o runner.cpp fizformulatests.h
//g++ -o runner runner.cpp -lfizzix && ./runner

#ifndef FIZOBJECTTESTS_H
#define FIZOBJECTTESTS_H

#include <cxxtest/TestSuite.h>
#include <libfizzix/fizformula.h>
#include <libfizzix/gen_structs.h>
#include <libfizzix/fizformoperators/operators.h>
#include <libfizzix/fizsphere.h>
#include <libfizzix/fizformnode.h>
#include <math.h>
#include <libfizzix/fizobject.h>
#include <libfizzix/fizsphere.h>
#include <libfizzix/fizcylinder.h>
#include <libfizzix/fizprism.h>
#include <libfizzix/quaternion.h>


class FizObjectTests: public CxxTest::TestSuite
{
	public:
		void testCompute(void)
		{
			vertex p1 = vertex(1,0,0);
			vertex p2 = vertex(-1,0,0);
			vertex p3 = vertex(0,sqrt(3),0);
			vertex p4 = vertex(0,0,sqrt(3));
			triangle t1 = triangle(&p1,&p2,&p3,0);
			triangle t2 = triangle(&p1,&p2,&p4,0);
			triangle t3 = triangle(&p1,&p3,&p4,0);
			triangle t4 = triangle(&p2,&p3,&p4,0);
			std::vector<triangle*> ttt;
			ttt.push_back(&t1);
			ttt.push_back(&t2);
			ttt.push_back(&t3);
			ttt.push_back(&t4);
			FizObject* x = new FizSphere("Purnima", vec3(64,64,64), ttt, 12, 3);
			TS_ASSERT_EQUALS(x->getMass(),12);
			std::vector<double> d(6,0.0);
			d[0] = d[1] = d[2] = 8/15.;
			std::vector<double> i = x->getInertiaTensor();
			TS_ASSERT_EQUALS(d[0],i[0]);
			TS_ASSERT_EQUALS(d[1],i[1]);
			TS_ASSERT_EQUALS(d[2],i[2]);
			TS_ASSERT_EQUALS(d[3],i[3]);
			TS_ASSERT_EQUALS(d[4],i[4]);
			TS_ASSERT_EQUALS(d[5],i[5]);
			d[0] = d[1] = d[2] = 15/8.;
			//i = x->getInertiaTensorInv();
			Quaternion q = x->getQuaternion();
			std::vector<double> r = q.toRotationMatrix();
			//i = x->getInertiaTensorInvWorld();
			TS_ASSERT_EQUALS(d[0],r[0]);
			TS_ASSERT_EQUALS(d[1],r[1]);
			TS_ASSERT_EQUALS(d[2],r[2]);
			TS_ASSERT_EQUALS(d[3],r[3]);
			TS_ASSERT_EQUALS(d[4],r[4]);
			TS_ASSERT_EQUALS(d[5],r[5]);
			
		}
};

#endif
