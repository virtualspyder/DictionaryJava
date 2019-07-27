a. Your approach in implementing your program.

+ My approach uses std::map to store dictionary data.

+ A section is not case-sensitive when searching. However, a subsection is case-sensitive.

+ istringstream is used to make parsing easier. Also, alias variables are used to clarify the code. 
  string &subsection_name = second_arg;
  If the second argument is also known as a subsection name, then it will make the code more readable.

+ The data contains unnecessary space characters, trimming spaces is necessary.

bookable|adjective => Can be ordered.

This part " => " contains unnecessary space characters. It will be difficult to manage the code without removing those spaces first.

b. Which data structures did you use?

class DictionarySection 
{
public:
	string section_name;
	map<string, vector <string> > subsections; // 1st arg: Subsection name
};

typedef map<string, DictionarySection> Dictionary; // 1st arg: Section name

c. What did you use the data structures for?

+ I used the mentioned data structures to store dictionary data.

+ A section can have a number of subsections. Examples: book, bookable, csc210, csc220, csc340
+ A subsection can have a number of values. For example: 

         csc340 [noun] : A CS upper division course.
         csc340 [noun] : Many hours outside of class.

The section is "csc340", the subsection is "noun". The subsection in this case has two values.

d. Why these data structures but not the others?
+ std::map only allows unique keys (each unique key has a value), so duplicate entires are not a concern. It is also very convenient to access a specific value by a given key.
+ std::vector is used to store a list of values for a subsection.   
