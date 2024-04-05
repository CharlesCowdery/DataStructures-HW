#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "pch.h"
#include "CppUnitTest.h"
//#include"../HW4/BinaryTree.h"
#include"../HW4/Hash1d.h"
#include"../HW4/Hash2d.h"
#include"../HW4/Hash1d.cpp"
#include"../HW4/Hash2d.cpp"
#include"../HW4/Hash2DOverflow.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(Hash1D)
	{
	public:
		
		TEST_METHOD(insert)
		{
			Hash1d data;
			int a = 1;
			int retval = 0;
			data.insert(a);
			retval=data.insert(a);
			Assert::AreEqual(retval, 2);
			
		}
		TEST_METHOD(remove)
		{
			Hash1d data;
			int a = 1;
			int retval = 0;
			data.insert(1);
			data.insert(501);
			retval = data.remove(501);
			Assert::AreEqual(retval, 2);

		}
	};
	TEST_CLASS(Hash2D)
	{
	public:
		TEST_METHOD(insert)
		{
			Hash2d data;
			int a = 1;
			int retval = 0;
			data.insert(a);
			retval = data.insert(a);
			Assert::AreEqual(retval, 2);

		}
		TEST_METHOD(insertToFalure)
		{
			Hash2d data;
			int a = 1;
			int retval = 0;
			data.insert(a);
			data.insert(a);
			data.insert(a);
			data.insert(a);
			data.insert(a);
			try {
				data.insert(a);
				Assert::AreEqual(1, 2);

			}
			catch(HashOverflow s){
				Assert::AreEqual(1,1);
			}

		}

		TEST_METHOD(remove)
		{
			Hash2d data;
			int a = 1;
			int retval = 0;
			data.insert(1);
			data.insert(101);
			retval = data.remove(101);
			Assert::AreEqual(retval, 2);
		}
		TEST_METHOD(removeToFailure)
		{
			Hash2d data;
			int a = 1;
			int retval = 0;
			data.insert(1);
			retval = data.remove(101);
			Assert::AreEqual(5, retval);
		}
	};
}
