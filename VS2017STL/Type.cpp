
struct MyStruct
{
	int a;
	int b;
	string d;
	//used in DisplayContents via cout
	operator const char*() const
	{
		return d.c_str();
	}

};