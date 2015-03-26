#ifndef _Data_
#define _Data_

#include <vector>

class Data
{
	private:
		std::vector<int> counts;
		int total;

	public:
		Data();
		void load(const char* filename);

		// Getter
		const std::vector<int>& get_counts() const
		{ return counts; }

		int get_total() const
		{ return total; }

	// Singleton
	private:
		static Data instance;
	public:
		static Data& get_instance() { return instance; }
};

#endif

