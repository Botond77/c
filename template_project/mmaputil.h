#ifndef MMAPUTIL__H
#define MMAPUTIL__H

#include<algorithm>
#include<functional>
#include<map>
template<class T, class Q, class Comp = std::less<Q> >
class multimap_util
{
	typedef std::multimap< T,Q ,Comp> ms;
	typedef typename  std::multimap<T, Q>::iterator iterator;
	ms* mm;

public:

	multimap_util(   std::multimap< T,Q,Comp> &rhs) 
	{
		mm = &rhs;
	}
	// 1.replace_key-jel egy kulcsot lehet átcserélni egy másikra, 
	multimap_util& replace_key( const T& lhs , const T& rhs ) 
	{
		iterator p = mm->find(lhs);
		if(p!= mm->end()  )
		{
			iterator pCopy = p;
			Q tempValue = p->second;
			p++;
			mm->erase(pCopy);
			mm->insert(std::make_pair(rhs,tempValue));
	
		}
		
		return *this;
	}
	// 2.swap-pel két  kulcshoz tartozó értékeket lehet felcserélni, 
	multimap_util& swap(const T& lhs, const T & rhs )
	{

		std::pair <iterator, iterator > p1 = mm->equal_range(lhs);
		std::pair <iterator, iterator > p2 = mm->equal_range(rhs);
		//
		iterator i = p1.first;
		iterator j = p2.first;
		if (i != mm->end() && j != mm->end()) 
		{
			Q temp = i->second;
			i->second = j->second;
			j->second = temp;
		}
		
		return *this;
	}
	// 3.replace_value-val a multimapben lévõ értékeket lehet átírni
	void replace_value(const Q& lhs,const Q& rhs)
	{	
		for (auto it = mm->begin(); it != mm->end(); it++) 
		{
			if ((*it).second == lhs) 
			{
				it->second = rhs;

			}	
		}
	}
	// 4.erase-zel a multimapbõl lehet törölni érték szerint
	// 5.mûködjön együtt custom rendezéssel mûködõ
	void erase(const Q&  d) 
	{
		iterator it= mm->begin();
		while ( it != mm->end() && !((*it).second == d)) 
		{
			it++;
		}
		if(mm->end()!= it)
		{
			mm->erase(it);
		}
	}
};
#endif // !MMAPUTIL__H