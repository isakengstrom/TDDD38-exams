class Wrapper
{
public:
	Wrapper(const int);
	void set(const int);
	int get() const;
	std::string str() const;
private:
	int value_;
};

