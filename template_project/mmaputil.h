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
	// 1.replace_key-jel egy kulcsot lehet �tcser�lni egy m�sikra, 
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
	// 2.swap-pel k�t  kulcshoz tartoz� �rt�keket lehet felcser�lni, 
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
	// 3.replace_value-val a multimapben l�v� �rt�keket lehet �t�rni
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
	// 4.erase-zel a multimapb�l lehet t�r�lni �rt�k szerint
	// 5.m�k�dj�n egy�tt custom rendez�ssel m�k�d�
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