#include "pch.h"
#include "Form1.h"
#include <msclr/marshal_cppstd.h>
#include <string>
#include <map>
#include <list>

namespace CppCLRWinFormsProject
{
	struct student
	{
		std::string FirstName, LastName;
		int year;
		std::string letter;
	};

	System::Void Form1::button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		std::map<std::string, std::list<student*>> students;
		auto lines = textBox1->Text->Split(gcnew array<String^, 1> { "\r\n" }, StringSplitOptions::RemoveEmptyEntries);
		for each (auto line in lines)
		{
			auto split = line->Split(' ');
			auto st = new student();
			auto first = split[0], last = split[1], year = split[2], letter = split[3];
			st->FirstName = msclr::interop::marshal_as<std::string>(first);
			st->LastName = msclr::interop::marshal_as<std::string>(last);
			st->letter = msclr::interop::marshal_as<std::string>(letter);
			st->year = atoi(msclr::interop::marshal_as<std::string>(year).c_str());

			students[st->LastName].push_back(st);
		}

		System::Text::StringBuilder^ sb = gcnew System::Text::StringBuilder();

		for each (auto pair in students)
		{
			if (pair.second.size() > 1)
			{
				sb->AppendLine(msclr::interop::marshal_as<String^>(pair.first) + "û:");
				for each (auto stud in pair.second)
				{
					sb->AppendLine(msclr::interop::marshal_as<String^>(stud->FirstName) + " "
						+ msclr::interop::marshal_as<String^>(stud->LastName) + " "
						+ stud->year + " "
						+ msclr::interop::marshal_as<String^>(stud->letter));
				}
				sb->AppendLine();
			}
		}

		textBox2->Text = sb->ToString();
	}
}