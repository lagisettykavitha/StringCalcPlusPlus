// StringCalculatorSpecs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../StringCalculator/StringCalculator.h"

using namespace igloo;

Describe(string_calculator_add) {
	Describe(when_passed_a_single_number) {
		It (returns_0_for_empty_string) {
			Assert::That(calculator.Add(""), Equals(0));
		}

		It (returns_0_for_zero) {
			Assert::That(calculator.Add("0"), Equals(0));
		}

		It (returns_1_for_one) {
			Assert::That(calculator.Add("1"), Equals(1));
		}

		StringCalculator calculator;
	};

	Describe(when_passed_two_comma_delimited_numbers) {
		It (returns_their_sum) {
			StringCalculator calculator;
			Assert::That(calculator.Add("1,2"), Equals(3));
		}
	};

	Describe(when_passed_multiple_comma_delimited_numbers) {
		It (returns_their_sum) {
			StringCalculator calculator;
			Assert::That(calculator.Add("1,2,3"), Equals(6));
		}
	};

	Describe(when_delimited_with_newline_and_comma) {
		It (returns_their_sum) {
			StringCalculator calculator;
			Assert::That(calculator.Add("1\n2,3"), Equals(6));
		}
	};

	Describe(when_passed_a_delimiter) {
		It(returns_the_sum_based_on_that_delimiter) {
			StringCalculator calculator;
			Assert::That(calculator.Add("//;\n1;2"), Equals(3));		
		}
	};

	Describe(when_passed_negative_numbers) {
		It(throws_an_exception_listing_invalid_values) {
			StringCalculator calculator;

			AssertThrows(invalid_argument, calculator.Add("1,-2,-4,5"));
			Assert::That(LastException<invalid_argument>().what(), Equals("Negatives not allowed: -2,-4"));
		}
	};

	Describe(when_passed_numbers_over_1000) {
		It(ignores_them) {
			StringCalculator calculator;
			Assert::That(calculator.Add("42,1001,3"), Equals(45));
		}
	};
};


