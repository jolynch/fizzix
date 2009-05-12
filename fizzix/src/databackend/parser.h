#ifndef PARSER_H
#define PARSER_H

#include <libfizzix/fizformula.h>
#include <libfizzix/gen_structs.h>
#include <libfizzix/fizformoperators/operators.h>
#include <libfizzix/fizformanonconst.h>
#include <libfizzix/getters.h>
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

		static FizFormNode * getOperator(QString oper, int num)
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
		static fizstack parse(QString input,int& num)
		{
			input = input.trimmed();
			qDebug()<<"PARSING:" <<input;
			fizstack stack;	
			int iter = 0;
			int e_iter = input.length();
			int counter = 0;
			while(iter < input.length())
			{
				switch(input[iter].toAscii())
				{
					case '(': //function
					{
						iter++;
						QString oper = "";
						for(;input[iter] != ' ';iter++) oper += input[iter];
						qDebug()<<"FOUND OPERATOR: "<<oper;
						int next = iter;
						for(counter = 1; next < input.length() && counter>0;)
						{
							next++;
							if(input[next].toAscii() == '(') counter += 1; 
							if(input[next].toAscii() == ')') counter -= 1;
						} 
						//e_iter--;
						qDebug()<<"RECURING WITH"<<input.mid(iter,next-iter);
						int operand_count = 0;
						fizstack operands = Parser::parse(input.mid(iter,next-iter), operand_count);
						iter = next;
						for(int i = 0; i<operands.size();i++)
							stack.push(operands[i]);
						
						qDebug()<<"PUSHING AN OPERATOR"<<oper<<"WITH"<<operand_count<<"OPERANDS";
						stack.push(getOperator(oper, operand_count));
						num += 1;
						break;
					}
					case '"':
					{
						iter++;
						int next_iter = input.indexOf("\"",iter);
						QString val = input.mid(iter, next_iter-iter);
						qDebug()<<"FOUND CONSTANT"<<val;
 						stack.push(new FizFormGetConst(val.toStdString()));
						iter = next_iter;
						num += 1;
						break;
					}
					case '[':
					{
						iter++;
						int next_iter = input.indexOf("]",iter);
						QString val = input.mid(iter, next_iter-iter);
						qDebug()<<"FOUND MACRO"<<val;
 						stack.push(new FizFormGetMacro(val.toStdString()));
						iter = next_iter;
						num += 1;
						break;
					}
					case '{':
					{
						iter++;
						int next_iter = input.indexOf("}",iter);
						QString val = input.mid(iter, next_iter-iter);
						qDebug()<<"FOUND FORCE"<<val;
						stack.push(new FizFormGetForce(val.toStdString()));
						iter = next_iter;
						num += 1;
						break;					
					}	
					case '$':
					{
						iter++;
						QString val;
						for(; !isspace(input[iter].toAscii()) && iter < input.length(); iter++)
							val+=input[iter]; 
						qDebug()<<"FOUND FROM TOKEN"<<val;
						stack.push(new FizFormGetProp(val.toStdString(),true));
						num += 1;
						break;	
					}
					case '@':
					{
						iter++;
						QString val;
						for(; !isspace(input[iter].toAscii()) && iter < input.length(); iter++)
							val+=input[iter]; 
						qDebug()<<"FOUND TO TOKEN"<<val;
						stack.push(new FizFormGetProp(val.toStdString(),false));			
						num += 1;
						break;
					}
					default:
					{
						if(!isspace(input[iter].toAscii()))
						{
							QString val = "";
							for(; !isspace(input[iter].toAscii()) && iter < e_iter; iter++)
								val+=input[iter]; 
							qDebug()<<"FOUND ANONCONST:"<<val<<val.toDouble();
							//NOTE, for some reason this won't compile UNCOMMENT
							fizdatum f(val.toDouble());
							stack.push(new FizFormAnonConst(f)); 
							num += 1;
						}
						break;
					}
					qDebug()<<"hum";
				}
				if(iter == e_iter)
				{
					//qDebug()<<opers<<stack;
// 					stack.push(
				}
// 				qDebug()<<iter;
				iter++;
			}
			qDebug()<<"Done"<<"FOUND: "<<num<<"arguments";
			stack.reset();
			qDebug()<<stack.pop()<< stack.size();
			//qDebug()<<"DONE PARSING:"<<QString(stack.pop()->toString(stack).c_str());
			stack.reset();
			return stack;
		}
		
};
#endif
