#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int find_named_digit(string &s)
{
  vector<string> nums = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  for (size_t i = 0; i < nums.size(); i++)
  {
    string num_s = nums[i];
    if (s.find(num_s) != string::npos)
    {
      return int(i + 1);
    }
  }

  return -1;
}

int get_calibration_value(string &s)
{
  stringstream first_buffer;
  int first_digit = 0;
  for (int i = 0; i < s.length(); i++)
  {
    int digit = int(s[i] - '0');
    if (digit >= 0 && digit <= 9)
    {
      first_digit = digit;
      break;
    }
    else
    {
      first_buffer << s[i];
      string digit_s = first_buffer.str();
      int digit = find_named_digit(digit_s);
      if (digit > 0)
      {
        first_digit = digit;
        break;
      }
    }
  }

  stringstream last_buffer;
  int last_digit = 0;
  for (int i = s.length() - 1; i > -1; i--)
  {
    int digit = int(s[i] - '0');
    if (digit >= 0 && digit <= 9)
    {
      last_digit = digit;
      break;
    }
    else
    {
      last_buffer << s[i];
      string digit_s = last_buffer.str();
      reverse(digit_s.begin(), digit_s.end());
      int digit = find_named_digit(digit_s);
      if (digit > 0)
      {
        last_digit = digit;
        break;
      }
    }
  }

  return first_digit * 10 + last_digit;
}

int main()
{
  int sum_value = 0;
  string line;
  ifstream file("input.txt");
  if (file.is_open())
  {
    while (getline(file, line))
    {
      sum_value += get_calibration_value(line);
    }
  }
  file.close();

  cout << "ANSWER: " << sum_value << '\n';

  return 0;
}