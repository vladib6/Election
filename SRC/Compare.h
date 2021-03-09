#pragma once
class Compare
{
public:
	template<class T>
	bool operator()(const T* t1, const T* t2)const {
		if (*t1 < * t2) return true;
		return false;
	}
};

