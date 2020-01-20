/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    Coby Jenkins
 *    Michael Gibson
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cctype>
#include <cassert>     // for ASSERT
#include <vector>
#include <sstream>
#include "stack.h"     // for STACK

using namespace std;

/*****************************************************
 * ASSEMBLY MODIFIERS
 * Checks if the operand is a number or a variable
 *****************************************************/
string assMod(const string mod)
{
   char ch = mod[0];

   switch(ch)
   {
      case '*':
         return "MUL";
      case '/':
         return "DIV";
      case '%':
         return "MOD";
      case '^':
         return "EXP";
      case '+':
         return "ADD";
      case '-':
         return "SUB";
      default:
         return "Nothing";
   }
}

/*****************************************************
 * IS VARIABLE
 * Checks if the operand is a number or a variable
 *****************************************************/
bool isVariable(const string ch)
{
   return isalpha(ch[0]);
}

/*****************************************************
 * IS OPERAND
 * Checks if the provided value is an operand
 *****************************************************/
bool isOperand(const string &token)
{

   if (isalnum(token[0]) || (token[0] == '.'))
   {
      return true;
   } else
      return false;
}

/*****************************************************
 * DETERMINE PRECEDENCE
 * Checks if the provided value is an operand
 *****************************************************/
int determinePrecedence(string token)
{
   if ((token == "+") || (token == "-"))
      return 0;
   if ((token == "*") || (token == "/") || (token == "%"))
      return 1;
   if ((token == "^"))
      return 2;
   return -1;
}

/*****************************************************
 * VECTOR OF STRINGS
 * convert the string into an vector of strings
 *****************************************************/
vector <string> convertStringToVector(const string &infix)
{
   stringstream ss(infix);
   string tempString = "";

   vector <string> vos;

   while (ss.good())
   {
      ss >> tempString;
      vos.push_back(tempString);
   }

   return vos;
}

/*****************************************************
 * CREATE SPACES
 * take user input and create a new string with spaces between
 * operands/operators
 *****************************************************/
string createSpaces(const string &infix)
{
   string spacedInfix = "";
   string spacedInfix2 = "";
   string tempStr;
   string tempStr0;

   // Add a space before all operators
   tempStr = infix[0];
   spacedInfix += tempStr;

   for(int i = 1; i < infix.size(); ++i)
   {
      tempStr = infix[i];
      tempStr0 = infix[i - 1];

      if ((tempStr == "(" || tempStr == "+" || tempStr == "-" ||
            tempStr == "*" || tempStr == "/" || tempStr == "%" ||
            tempStr == ")" || tempStr == "^") && tempStr0 != " ")
      {
         spacedInfix += " " + tempStr;
      }
      else
      {
         spacedInfix += tempStr;
      }
   }

   // add a space after all operators
   int a = 0; // counting characters in string

   for(int i = 0; i < spacedInfix.size() - 1; ++i)
   {
      tempStr = spacedInfix[i];
      tempStr0 = spacedInfix[i + 1];   

      if ((tempStr == "(" || tempStr == "+" || tempStr == "-" ||
            tempStr == "*" || tempStr == "/" || tempStr == "%" ||
            tempStr == ")" || tempStr == "^") && tempStr0 != " ")
      {
         spacedInfix2 += tempStr + " ";
      }
      else
      {
         spacedInfix2 += tempStr;
      }

      a += 1;

   }
   tempStr = spacedInfix[a];
   spacedInfix2 += tempStr;
   
   return spacedInfix2;
}

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string &infix)
{
   string spacedInfix = createSpaces(infix);
   vector <string> vosTokens = convertStringToVector(spacedInfix);
   string tokens[vosTokens.size()];


   int a = 0;
   for (vector<string>::iterator it = vosTokens.begin();
        it != vosTokens.end(); it++)
   {
      tokens[a] = *it;
      a++;
   }

   int bPostfix = 0;
   string postfix[a];
   custom::stack<string> temp;

   for (int i = 0; i < a; ++i)
   {
      string tempString = tokens[i];

      if (isOperand(tempString))
      {
         postfix[bPostfix++] = tempString;
      } else if (tempString == "(")
      {
         temp.push(tempString);
      } else if (tempString == ")")
      {
         while (temp.top() != "(")
         {
            postfix[bPostfix++] = temp.top();
            temp.pop();
         }
         temp.pop();
      } else
      {
         int stringOperator = determinePrecedence(tempString);
         int tempOperator = -1;

         if (!temp.empty())
            tempOperator = determinePrecedence(temp.top());

         while ((!temp.empty()) && (stringOperator <= tempOperator))
         {
            postfix[bPostfix++] = temp.top();
            temp.pop();
         }
         temp.push(tempString);
      }
   }
   while (!temp.empty())
   {
      postfix[bPostfix++] = temp.top();
      temp.pop();
   }

   string postFixString = " " + postfix[0];
   for (int k = 1; k < bPostfix; ++k)
   {
      postFixString += " " + postfix[k];
   }
   return postFixString;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }

      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix: " << postfix << endl << endl;
      }
   } while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string &postfix)
{

   string spacedPostfix = createSpaces(postfix);
   vector <string> vosTokens = convertStringToVector(spacedPostfix);
   string tokens[vosTokens.size()];


   int a = 0;
   for (vector<string>::iterator it = vosTokens.begin();
        it != vosTokens.end(); it++)
   {
      tokens[a] = *it;
      a++;
   }


   string assembly = "";
   string tempStr;
   string rhs;
   string lhs;
   string v;
   custom::stack <string> s1;
   char variable = '@';

   for(int i = 0; i < a; ++i)
   {
      tempStr = tokens[i];

      if(isOperand(tempStr))
      {
         s1.push(tempStr);
      }
      else
      {
         v = "";
         rhs = s1.top();
         s1.pop();
         lhs = s1.top();
         s1.pop();
         variable++;

         // if the lhs is a variable, it is added to the string
         // with LOD prefix. If it is not, it is added with SET prefix
         if(isVariable(lhs))
         {
            assembly += "\tLOD " + lhs + "\n";
         }
         else
         {
            assembly += "\tSET " + lhs + "\n";
         }

         // convert the char into a string
         v += variable;
         
         // convert operators into assembly modifiers
         tempStr = assMod(tempStr);
         assembly += "\t" + tempStr + " " + rhs + "\n";
         assembly += "\tSAV " + v + "\n";

         s1.push(v);
      }
      
   }

   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }

      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   } while (input != "quit");

}
