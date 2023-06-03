#include "pch.h"
#include "Form1.h"
#include <map>

using namespace System::Collections::Generic;
using namespace System::Text;

namespace CppCLRWinFormsProject
{
	System::Void Form1::button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		std::map<wchar_t, int> symbolCount;
		for each (auto c in textBox1->Text)
		{
			if (c == '\r') // перенос в виде \r\n - два символа, один из них пропустим
				continue;
			symbolCount[c]++;
		}

		auto sb = gcnew StringBuilder();

		for each (auto pair in symbolCount)
		{
			switch (pair.first)
			{
			case ' ':
				sb->Append("Пробел");
				break;
			case '\n':
				sb->Append("Перенос строки");
				break;
			default:
				sb->Append(Char::ToString(pair.first));

			}
			sb->Append(": ");
			sb->Append(pair.second);
			sb->AppendLine();
		}
		
		textBox2->Text = sb->ToString();
	}
}