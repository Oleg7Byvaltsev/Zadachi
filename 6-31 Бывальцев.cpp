#include "pch.h"
#include "Form1.h"
#include <msclr/marshal_cppstd.h>
#include <fstream>
#include <list>

namespace CppCLRWinFormsProject
{
	System::Void Form1::button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		textBox1->Clear();
		textBox2->Clear();

		std::vector<int> values;
		std::fstream file;
		auto path = msclr::interop::marshal_as<std::string>(textBox3->Text);
		file.open(path, std::fstream::in);

		int val;
		while (file >> val)
		{
			values.push_back(val);
		}
		for each (auto val in values)
		{
			textBox1->AppendText(val + " ");
		}
		file.close();
		file.open(path, std::fstream::trunc | std::fstream::out);
		auto index = values.size() / 2;

		auto swap = values[index];
		values[index] = values[0];
		values[0] = swap;

		file.clear();
		for each (auto val in values)
		{
			textBox2->AppendText(val + " ");
			file << val << " ";
		}
		file.close();
	}
}