/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back_exception_safety.pass.cpp                :+:      :+:    :+:   */
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
main(void)
{
	TEST_AWARE_BLOCK({
		CMyClass instance(42);
		VECTOR<CMyClass> vec;

		vec.push_back(instance);
		VECTOR<CMyClass> vec2(vec);

		gCopyConstructorShouldThrow = true;

		ASSERT_EXCEPT({
			vec.push_back(instance);
		});

		ASSERT(vec == vec2);
	});

	return (0);
}
