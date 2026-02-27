#include "HTML_Decode.h"
#include <iostream>

int main()
{
    std::string html;
    getline(std::cin, html);
    std::cout << HtmlDecode(html) << std::endl;
}