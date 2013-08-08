#include "StringCalculator.h"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>

class GetNegatives {
private:
	vector<string> negatives;

public:
	void operator()(int i) {
		if (i < 0)
			negatives.push_back(to_string(i));
	}

	 operator vector<string>() {
		return negatives;
	}
};

vector<int> get_numbers(const string &input, const string &delimiters) {
	vector<string> items;

	//stringstream ss(input);
	//string item;

	//while(getline(ss, item, ',')) {
	//	if (item.empty())
	//		continue;

	//	items.push_back(item);
	//}

	boost::split(items, input, boost::is_any_of(delimiters));

	//vector<int> numbers(items.size());
	//transform(items.begin(), items.end(), numbers.begin(), [](const string &s) { return stoi(s); });

	vector<int> numbers;
	for (const auto &item : items) {
		numbers.push_back(stoi(item));
	}

	return numbers;
}

void check_for_negatives(const vector<int> &numbers) {
	vector<string> negatives = for_each(numbers.begin(), numbers.end(), GetNegatives());

	if (negatives.size() > 0) {
		throw invalid_argument("Negatives not allowed: " + boost::join(negatives, ","));
	}
}

int StringCalculator::Add(const string &input) {
	if (input.empty())
		return 0;

	string delimiters = ",\n";
	int skip = 0;

	if (input.substr(0, 2) == "//") {
		delimiters = input.substr(2, 1);
		skip = 3;
	}

	vector<int> numbers = get_numbers(input.substr(skip), delimiters);
	check_for_negatives(numbers);

	return accumulate(numbers.begin(), numbers.end(), 0);
}