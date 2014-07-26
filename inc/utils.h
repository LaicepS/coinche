template<class T1,  class T2>
bool exists(T1 value, T2 container)
{
	for(auto val : container)
	{
		if (val == value)
			return true;
	}
	return false;
}
