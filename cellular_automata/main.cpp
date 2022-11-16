//Note: Class is included in main because this is a very short and sweet one class project

//Automaton Class takes a rule between 0 and 255 inclusive
// that is then applied to a "seed" string to propagate a new "generation"
// propagation is repeated to create pattern which can be formatted for display

#include <string>
#include <cmath>
#include <iostream>

using namespace std;

/*** BEGIN AUTOMATON CLASS PROTOTYPE ****/
class Automaton
{
public:
   static const int RULES_SIZE = 8;
   static const int BITS_IN_RULE_SIZE; 
   static const int MIN_DISPLAY_WIDTH = 21;
   static const int MAX_DISPLAY_WIDTH = 121;
   static const int DFLT_DISPLAY_WIDTH = 79;
   static const int MIN_RULE = 0;
   static const int MAX_RULE; 
   static const char ON_STR;  
   static const char OFF_STR;  // blank " "

private:
   bool rule[RULES_SIZE];
   string thisGen;
   string extremeBit; // bit, "*" or " "
   int displayWidth;  // odd number for centering

public:
   Automaton(int rule);
   string toStringCurrentGen();
   bool setRule(int rule);      // change rule set
   void resetFirstGen();
   bool setDisplayWidth(int width);
   void propagateNewGeneration();
};
const int Automaton::BITS_IN_RULE_SIZE = log2(RULES_SIZE);
const int Automaton::MAX_RULE = pow(2, RULES_SIZE) - 1;  
const char Automaton::ON_STR = '*';
const char Automaton::OFF_STR = ' ';

/*** END AUTOMATON CLASS PROTOTYPE ***/

// Test cases 
int main()
{
   int testRules[] = { 3, 126, 131, 57 };
   int numTests = sizeof(testRules) / sizeof(testRules[0]);
   int numGenerations = 100;
   Automaton testAuto = Automaton(1);

   //each loop of k is one complete rule test.
   for (int k = 0; k < numTests; k++)
   {
      testAuto.setRule(testRules[k]);
      cout << "\nHere is rule #" << testRules[k] << "\n";
      cout << testAuto.toStringCurrentGen() << "\n";

      for (int i = 0; i < numGenerations; i++)
      {
         testAuto.propagateNewGeneration();
         cout << testAuto.toStringCurrentGen() << "\n";
      }

      testAuto.resetFirstGen();
   }
}

/*** AUTOMATON CLASS FUNCTIONS ***/

Automaton::Automaton(int rule)
{
   if (!setRule(rule))
      setRule(MIN_RULE);

   setDisplayWidth(DFLT_DISPLAY_WIDTH);
   thisGen = ON_STR;
   extremeBit = OFF_STR;
}

string Automaton::toStringCurrentGen()
{
   int stringLength = thisGen.length();
   string tempString = thisGen;

   if (stringLength > displayWidth)
   {
      // remove characters from ends to fit into displayWidth
      int removeEnds = ((stringLength - displayWidth) / 2);
      tempString = thisGen.substr((removeEnds - 1), displayWidth);
   }
   else
   {
      //add extremeBits to fill displayWidth characters
      string insertBits = "";
      int padString = ((displayWidth - stringLength) / 2);

      for (int i = padString; i > 0; i--)
         insertBits += extremeBit;

      tempString.insert(stringLength, insertBits);  
      tempString.insert(0, insertBits);
   }

   return tempString;
}

bool Automaton::setRule(int rule)
{
   // check for valid rule value
   if (rule >= MIN_RULE && rule <= MAX_RULE)
   {
      // uses Math.pow to iterate k by powers of 2 for bit comparison
      for (int index = 0; index < (RULES_SIZE); index++)
      {
         int k = (int)(pow(2, index));
         Automaton::rule[index] = ((rule & k) != 0) ? true : false;
      }
      return true; 
   }
   else
      return false;
}

bool Automaton::setDisplayWidth(int width)
{
   if (width % 2 != 0)  // check for odd width
   {
      if (width >= MIN_DISPLAY_WIDTH && width <= MAX_DISPLAY_WIDTH)
      displayWidth = width;
      return true;
   }
   else
      return false;
}

void Automaton::resetFirstGen()
{
   thisGen = ON_STR;
   extremeBit = OFF_STR;
 }

void Automaton::propagateNewGeneration()
{
   string addBits = extremeBit + extremeBit;
   string nextGen;

   // add two extremeBits to beginning and end of thisGen
   thisGen.insert(thisGen.length(), addBits);
   thisGen.insert(0, addBits);

   // analyze triplets to form nextGen using rule[] as a key
   for (int i = 1; i < (thisGen.length() - 1); i++)
   {
      int findRule = 0;

      if (thisGen.at(i - 1) == ON_STR)
         findRule += 4;
      if (thisGen.at(i) == ON_STR)
         findRule += 2;
      if (thisGen.at(i + 1) == ON_STR)
         findRule += 1;

      if (rule[findRule] == true)
         nextGen += ON_STR;
      else
         nextGen += OFF_STR;
   }

   // Determine extremeBit for nextGen
   if (extremeBit.at(0) == ON_STR)
      extremeBit = (rule[RULES_SIZE - 1]) ? ON_STR : OFF_STR;
   else
      extremeBit = (rule[0]) ? ON_STR : OFF_STR;

   thisGen = nextGen;
}

