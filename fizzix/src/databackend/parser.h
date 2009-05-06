#ifndef PARSER_H
#define PARSER_H

#include <libfizzix/fizformula.h>
#include <libfizzix/gen_structs.h>
#include <libfizzix/fizformoperators/operators.h>
#include <libfizzix/fizformanonconst.h>
#include <QString>
#include <QStack>
#include <QtDebug> 

#include <stdexcept>
#include <ctype.h>

/* Parser that will parse a lisp stype infix string and return a 
   fizstack representing that string
   -------
   Grammar (eh ... not really a grammar, but heck) 
   -------
   Operators 		= (token arg1 arg2 ...)
   From 		= $token
   To 			= @token
   Constant 		= "token"
   Macro 		= [token]
   Force 		= {token}
   Un-named Constant 	= token
   Un-named Vector	= <token,token,token>

   reserved keywords:
   (,$,@,",[],{},<>

   -------
   Example
   -------
   Gravity = G*m*m / r^2 
   
	|  Human
	v
  
   (/ (* "G" $mass @mass) (^ [r] 2))

   	|  Parser
	v
 
   Fizstack == |Head| /(2) || ^(2) || 2 || [r] || *(3) || @mass || $mass || "G" |Tail|
 */


class Parser
{
       	/* Returns a FizFormNode representing the oper with operands
  	   All Possible operators:
	   And, Arccos, Arcsin, Arctan, Cosh, Cosine, Cross, Difference, Dot, Equal, Exponent,
  	   Exponentiate, Factorial, Greater, Greatereq, If, Less, Lesseq, Logarithm, Magnitude,
	   Notequal, Or, Product, Quotient, Random, Sine, Sinh, Square, Sum, Tangent, Tanh, 
	   Template, Vectorize, 
	 */
	public:

		static FizFormNode * getOperator(QString oper, uint num)
		{
			using namespace FizOper;
			std::string token = oper.toStdString();
			if(token ==  And::token)		{ return new And(num); }  
			else if(token ==  Arccos::token)		{ return new Arccos(num); }
			else if(token ==  Arcsin::token)		{ return new Arcsin(num); }
			else if(token ==  Arctan::token)		{ return new Arctan(num); }
			else if(token ==  Cosh::token)		{ return new Cosh(num); }
			else if(token ==  Cosine::token)		{ return new Cosine(num); }
			else if(token ==  Cross::token)		{ return new Cross(num); }
			else if(token ==  Dot::token)		{ return new Dot(num); }
			else if(token ==  Equal::token)		{ return new Equal(num); }
			else if(token ==  Exponent::token)	{ return new Exponent(num); }
			else if(token ==  Exponentiate::token)	{ return new Exponentiate(num); }
			else if(token ==  Factorial::token)	{ return new Factorial(num); }
			else if(token ==  Greater::token)	{ return new Greater(num); }
			else if(token ==  Greatereq::token)	{ return new Greatereq(num); }
			else if(token ==  If::token)		{ return new If(num); }
			else if(token ==  Less::token)		{ return new Less(num); }
			else if(token ==  Lesseq::token)		{ return new Lesseq(num); }
			else if(token ==  Logarithm::token)	{ return new Logarithm(num); }
			else if(token ==  Magnitude::token)	{ return new Magnitude(num); }
			else if(token ==  Notequal::token)	{ return new Notequal(num); }
			else if(token ==  Or::token)		{ return new Or(num); }
			else if(token ==  Product::token)	{ return new Product(num); }
			else if(token ==  Quotient::token)	{ return new Quotient(num); }
			else if(token ==  Random::token)		{ return new Random(num); }
			else if(token ==  Sine::token)		{ return new Sine(num); }
			else if(token ==  Sinh::token)		{ return new Sinh(num); }
			else if(token ==  Sum::token)		{ return new Sum(num); }
			else if(token ==  Tangent::token)	{ return new Tangent(num); }
			else if(token ==  Tanh::token)		{ return new Tanh(num); }
			else if(token ==  Vectorize::token)	{ return new Vectorize(num); }
			else { throw std::logic_error("It does not seem that we have an operator for: "+token); }
		}
		static fizstack parse(QString input)
		{
			fizstack stack;	
			QString::iterator iter = input.begin();
			QString::iterator e_iter = iter;
			int counter = 0;
			while(iter != input.end())
			{
				switch(iter->toAscii())
				{
					case '(': //TODO move this down a level
					 {
						iter++;
						std::string oper = "";
						for(;*iter != ' ';iter++) oper += iter->toAscii();
						iter++; //skip space
						qDebug()<<"FOUND OPERATOR: "<<oper.c_str();
						e_iter = iter;
						for(counter = 1; e_iter!= input.end() && counter!=0;)
						{
							e_iter++;
							if(e_iter->toAscii() == '(') counter += 1; 
							if(e_iter->toAscii() == ')') counter -= 1;
						}
						while(iter < e_iter && iter!= input.end())
						{	
							switch(iter->toAscii())
							{
								case '(': //recursive call
								{
									QString arg;
									for(counter = 1; iter!=e_iter && counter!=0; iter++)
									{
										if(iter->toAscii() == '(') counter += 1;
										if(iter->toAscii() == ')') counter -= 1;
										arg += *iter;
									}
									//fizstack oper = Parser::parse(arg);

									break;
								}
								case '"':
								{
									break;
								}
								case '[':
								{
									break;
								}
								case '{':
								{
									break;
								}
								default:
								{
									if(!isspace(iter->toAscii()))
									{
										QString num;
										for(; !isspace(iter->toAscii()) && iter != e_iter; iter++)
											num+=*iter; 
// 										qDebug()<<"FOUND ANONCONST:"<<num.toDouble();
										//NOTE, for some reason this won't compile UNCOMMENT
										//fizdatum f(num.toDouble());
										//stack.push(new FizFormAnonConst(f));
									}
									break;
								}
							}
							++iter;
						}

						//fizformnode * fizoper = getOperator(oper);	

						//while(iter != input.end() || iter->toAscii() == ')')
						//{

						//	iter++
						//}
						break;
					}
					default:
						break;

				}
				iter++;
			}
			return stack;
		}
};

#endif
