#include <iostream>
#include <string>
#include <vector>
#include <map>

 using namespace std;

 
void
doParse (map < string, int >*listOfVariables)
{
  
 
map < string, int >variables;
  
map < string, int >prevVariables;
  
 
string str;
  
while (cin >> str)
    {
      
if (str == "{")
	{
	  
doParse (listOfVariables);
	
}
      else if (str == "}")
	{
	
for (pair < string, int >pair:variables)
	    {
	      
(*listOfVariables).erase (pair.first);
	
} 
 
for (pair < string, int >pair:prevVariables)
	    {
	      
(*listOfVariables).insert_or_assign (pair.first, pair.second);
	    
} 
 
return;
	
}
      else
	{
	  
int equalId = str.find ('=');
	  
 
string firstVar = str.substr (0, equalId);
	  
string secondVar = str.substr (equalId + 1, str.size ());
	  
 
if (secondVar.find_first_not_of ("-0123456789") == string::npos)
	    {
	      
if (prevVariables.count (firstVar) == 0
		   && (*listOfVariables).count (firstVar) > 0
		   && variables.count (firstVar) == 0)
		{
		  
prevVariables.insert_or_assign (firstVar,
						   (*listOfVariables).
						   at (firstVar));
		
}
	      
 
		(*listOfVariables).insert_or_assign (firstVar,
						     stoi (secondVar));
	      
variables.insert_or_assign (firstVar, stoi (secondVar));
	    
}
	  else
	    {
	      
int i = 0;
	      
 
if (prevVariables.count (firstVar) == 0
		     && (*listOfVariables).count (firstVar) > 0
		     && variables.count (firstVar) == 0)
		{
		  
prevVariables.insert_or_assign (firstVar,
						   (*listOfVariables).
						   at (firstVar));
		
}
	      
 
if ((*listOfVariables).count (secondVar) > 0)
		{
		  
i = (*listOfVariables).at (secondVar);
		
}
	      
 
(*listOfVariables).insert_or_assign (firstVar, i);
	      
variables.insert_or_assign (firstVar, i);
	      
 
printf ("%d\n", i);
	    
}
	
}
    
}

}


 
int
main ()
{
  
 
map < string, int >listOfVariables;
  
doParse (&listOfVariables);
  
 
return 0;

}
