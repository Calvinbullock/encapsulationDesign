#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

/* ==========================
 *
 =========================== */

int main()
{
   return 0;
}

std::vector<std::string> readFile(const std::string &fileName)
{
   std::vector<std::string> address;

   std::ifstream fin(fileName.c_str());
   if (fin.fail())
   {
      cout << "Unable to open." << endl;
      return address;
   }

   while (!fin.eof())
   {
      string line;
      getline(fin, line);
      address.push_back(line);
   }
    fin.close();
    return address;
}


