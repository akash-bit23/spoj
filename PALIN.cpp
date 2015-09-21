#include <iostream>
#include <algorithm>

#ifdef DEBUG
#include <chrono>
#endif

std::string & ltrim(std::string & str)
{
  auto it2 =  std::find_if( str.begin() , str.end() , [](char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
  str.erase( str.begin() , it2);
  return str;   
}

std::string & rtrim(std::string & str)
{
  auto it1 =  std::find_if( str.rbegin() , str.rend() , [](char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
  str.erase( it1.base() , str.end() );
  return str;   
}

std::string & trim(std::string & str)
{
   return ltrim(rtrim(str));
}

int main()
{
	#ifdef DEBUG
	auto now = [](){return std::chrono::high_resolution_clock::now();};
	auto start = now();
	auto elapsed = [=](){return std::chrono::duration_cast<std::chrono::milliseconds>(now()-start).count();};
	#endif

	int cases;
	std::cin >> cases;
	
	std::string line;
	getline(std::cin, line); // skip first end of line

	for(; cases > 0; --cases)
	{
		getline(std::cin, line);
		trim(line);

		int size = line.size();
		char * begin = (char*) line.c_str();
		char * left0 = begin + (size+1)/2 - 1;
		char * right0 = begin + size - (size+1)/2;
		char * left = left0;
		char * right = right0;
		bool adding = false;

		//find diff
		while(left >= begin)
		{
			if(*left != *right)
			{
				if(*left < *right)
				{
					adding = true;
					left = left0;
					right = right0;
				}
				break;
			}

			--left;
			++right;
		}

		//already polyndromed
		if(left < begin)
		{
			adding = true;
			left = left0;
			right = right0;
		}

		//increase
		while(left >= begin)
		{
			if(adding) 
			{
				if(*left == '9')
				{
					*right = *left = '0';
				}
				else
				{
					*right = *left = *left + 1;
					adding = false;
				}
			}
			else
			{
				*right = *left;
			}

			--left;
			++right;
		}
		
		if(adding)
		{
			*(right-1) = '1';
			std::cout << '1' << line << std::endl << std::endl;
		}
		else
		{
			std::cout << line << std::endl << std::endl;
		}
	}

	#ifdef DEBUG
	std::cout << "Elapsed " << elapsed() << " ms" << std::endl;
	#endif
	
	return 0;
}
