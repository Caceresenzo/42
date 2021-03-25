/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back_rvalue.pass.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 14:03:25 by ecaceres          #+#    #+#             */
/*   Updated: 2020/09/01 14:03:25 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_vector.hpp>

static bool gCopyConstructorShouldThrow = false;

class CMyClass
{
	public:

		CMyClass(int tag) :
		        fMagicValue(kStartedConstructionMagicValue),
		        fTag(tag)
		{
			// Signal that the constructor has finished running
			fMagicValue = kFinishedConstructionMagicValue;
		}

		CMyClass(const CMyClass &iOther) :
		        fMagicValue(kStartedConstructionMagicValue),
		        fTag(iOther.fTag)
		{
			// If requested, throw an exception _before_ setting fMagicValue to kFinishedConstructionMagicValue
			if (gCopyConstructorShouldThrow)
				throw std::exception();
			// Signal that the constructor has finished running
			fMagicValue = kFinishedConstructionMagicValue;
		}

		~CMyClass()
		{
			// Only instances for which the constructor has finished running should be destructed
			ASSERT(fMagicValue == kFinishedConstructionMagicValue);
		}
		bool
		equal(const CMyClass &rhs) const
		{
			return fTag == rhs.fTag && fMagicValue == rhs.fMagicValue;
		}

	private:
		int fMagicValue;
		int fTag;

	private:
		static int kStartedConstructionMagicValue;
		private:
		static int kFinishedConstructionMagicValue;
};

// Value for fMagicValue when the constructor has started running, but not yet finished
int CMyClass::kStartedConstructionMagicValue = 0;
// Value for fMagicValue when the constructor has finished running
int CMyClass::kFinishedConstructionMagicValue = 12345;

bool
operator==(const CMyClass &lhs, const CMyClass &rhs)
{
	return lhs.equal(rhs);
}

int
main(int, char**)
{
	TEST_AWARE_BLOCK({
		VECTOR<Aware<int> > c;

		c.push_back(Aware<int>(0));
		ASSERT(c.size() == 1);

		for (int j = 0; static_cast<std::size_t>(j) < c.size(); ++j)
			ASSERT(c[j] == Aware<int>(j));

		c.push_back(Aware<int>(1));
		ASSERT(c.size() == 2);

		for (int j = 0; static_cast<std::size_t>(j) < c.size(); ++j)
			ASSERT(c[j] == Aware<int>(j));

		c.push_back(Aware<int>(2));
		ASSERT(c.size() == 3);

		for (int j = 0; static_cast<std::size_t>(j) < c.size(); ++j)
			ASSERT(c[j] == Aware<int>(j));

		c.push_back(Aware<int>(3));
		ASSERT(c.size() == 4);

		for (int j = 0; static_cast<std::size_t>(j) < c.size(); ++j)
			ASSERT(c[j] == Aware<int>(j));

		c.push_back(Aware<int>(4));
		ASSERT(c.size() == 5);

		for (int j = 0; static_cast<std::size_t>(j) < c.size(); ++j)
			ASSERT(c[j] == Aware<int>(j));
	});

	return (0);
}
