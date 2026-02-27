#include <iostream>
#include "HTML_Decode.h"

int main()
{
    std::string html;
    getline(std::cin, html);
    std::cout << HtmlDecode(html) << std::endl;
}