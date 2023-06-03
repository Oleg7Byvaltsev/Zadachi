#include "pch.h"
#include "Form1.h"
#include <msclr/marshal_cppstd.h>
#include <iostream>>
#include <list>

namespace CppCLRWinFormsProject
{
	System::Void Form1::button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		std::list<std::string> unsuccessful;

		auto runNorm = atof(msclr::interop::marshal_as<std::string>(textBox2->Text).c_str());
		auto horizontalNorm = atof(msclr::interop::marshal_as<std::string>(textBox3->Text).c_str());
		auto verticalNorm = atof(msclr::interop::marshal_as<std::string>(textBox4->Text).c_str());
		auto throwNorm = atof(msclr::interop::marshal_as<std::string>(textBox5->Text).c_str());

		auto lines = textBox1->Text->Split(gcnew array<String^, 1> { "\r\n" }, StringSplitOptions::RemoveEmptyEntries);
		
		double totalLength = 0;
		int firstTries = 0;

		for each (auto line in lines)
		{
			auto split = line->Split(' ');
			auto name = split[0] + " " + split[1] + " " + split[2];

			if (split[3] == "бег")
			{
				auto strResult = split[4];
				auto result = atof(msclr::interop::marshal_as<std::string>(strResult).c_str());
				if (result > runNorm)
					unsuccessful.push_back(msclr::interop::marshal_as<std::string>(name));
			}

			else if (split[3] == "длина")
			{
				double max = 0;
				for (int i = 4; i < 7; i++)
				{
					auto strResult = split[i];
					auto result = atof(msclr::interop::marshal_as<std::string>(strResult).c_str());
					if (result > max)
						max = result;
				}
				if (max < horizontalNorm)
					unsuccessful.push_back(msclr::interop::marshal_as<std::string>(name));
				totalLength += max;
			}

			else if (split[3] == "высота")
			{
				double max = 0, maxAttempt = 0;
				for (int i = 4; i < 7; i++)
				{
					auto strResult = split[i];
					auto result = atof(msclr::interop::marshal_as<std::string>(strResult).c_str());
					if (result > max)
					{
						max = result;
						maxAttempt = i;
					}
				}
				if (max < verticalNorm)
					unsuccessful.push_back(msclr::interop::marshal_as<std::string>(name));
				if (max >= verticalNorm && maxAttempt == 4)
					firstTries++;
			}

			else if (split[3] == "граната")
			{
				double max = 0;
				for (int i = 4; i < 7; i++)
				{
					auto strResult = split[i];
					auto result = atof(msclr::interop::marshal_as<std::string>(strResult).c_str());
					if (result > max)
						max = result;
				}
				if (max < throwNorm)
					unsuccessful.push_back(msclr::interop::marshal_as<std::string>(name));
			}
		}

		unsuccessful.unique();

		label1->Text = "Количество взявших высоту с первой попытки: " + firstTries;
		label2->Text = "Общая длина прыжка: " + totalLength;

		textBox6->Clear();
		for each (auto stud in unsuccessful)
		{
			textBox6->AppendText(msclr::interop::marshal_as<String^>(stud) + "\r\n");
		}
	}
}