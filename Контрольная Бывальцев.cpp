#include "pch.h"
#include "Form1.h"
#include <msclr/marshal_cppstd.h>
#include <vector>
#include <sstream>
#include <iomanip>

namespace CppCLRWinFormsProject
{
	System::Void Form1::button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		auto input = msclr::interop::marshal_as<std::string>(textBox1->Text);

		auto size = input.size();

		if ((size & 1) == 1) // проверка четного количества символов
		{
			System::Windows::Forms::MessageBox::Show("Ошибка ввода");
			return;
		}

		bool isHex = input[0] != '0'; //если первый символ 0 - предполагаем восьмеричный ввод, иначе хекс
		auto result = isHex ? ParseHex(input) : ParseOcta(input);

		auto sb = gcnew System::Text::StringBuilder();
		sb->Append("{ ");

		if (isHex)
		{
			for each (auto block in result)
			{
				// побитовые операции для возврата исходных цифр
				uint8_t left = (block >> 4) & ((1 << 4) - 1);
				uint8_t right = (block) & ((1 << 4) - 1);

				sb->Append("0x");
				sb->Append(Char::ToString(ParseBack(left)));
				sb->Append(Char::ToString(ParseBack(right)));
				sb->Append(" ");
			}
		}

		else
		{
			for each (auto digit in result)
			{
				sb->Append(Char::ToString(ParseBack(digit)));
				sb->Append(" ");
			}
		}

		sb->Append("}");
		textBox2->Text = sb->ToString();
	}

	// BAAB -> { 0xBA, 0xAB }
	std::vector<uint8_t> Form1::ParseHex(std::string& input)
	{
		std::vector<uint8_t> result;
		for (int i = 0; i < input.size(); i += 2) // обрабатываем по две цифры за рза
		{
			uint8_t block = 0;
			auto left = ParseDigit(input[i]); // левая
			auto right = ParseDigit(input[i + 1]); // правая

			// один uint8_t - число на 8 бит, т.е. например 10100101
			// изначально блок выглядит как 00000000
			// первая операция - сдвигаем левую половину на 4 символа (например левая половина - 1101, после сдвига станет 11010000)
			// и складываем с блоком, получаем в блоке 11010000
			// затем просто складываем блок с правой частью, например 11010000 + правая часть 0111 получим 11010111, таким образом сохранили две цифры в одном восьмибитном числе
			block |= left << 4;
			block |= right;
			result.push_back(block);
		}
		return result;
	}

	// 01020304 -> { 1 2 3 4 }
	std::vector<uint8_t> Form1::ParseOcta(std::string& input)
	{
		std::vector<uint8_t> result;
		for (int i = 1; i < input.size(); i += 2) // берем каждый четный символ, нули скип
		{
			result.push_back(input[i] - '0'); // преобразование символа в цифру путем вычитания
		}
		return result;
	}

	// преобразование цифры в хекс строке
	uint8_t Form1::ParseDigit(char ch)
	{
		if (ch >= '0' && ch <= '9') return ch - '0';
		if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
		if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
		return 0;
	}

	char Form1::ParseBack(uint8_t digit)
	{
		if (digit >= 0 && digit <= 9)
			return digit + '0';
		return digit - 10 + 'A';
	}
}