#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

char ParseCommand(const std::string& command)
{
    if (command == "quot") return '"';
    if (command == "apos") return '\'';
    if (command == "lt") return '<';
    if (command == "gt") return '>';
    if (command == "amp") return '&';
    return '?';
}

std::string HtmlDecode(const std::string& html)
{
    std::string decodedHtml = "";
    for (size_t i = 0; i < html.size(); i++)
    {
        if (html[i] == '&')
        {
            std::string command = "";
            i++;

            while (html[i] != ';')
            {
                command += html[i];
                i++;
            }
            decodedHtml += ParseCommand(command);
        }
        else
        {
            decodedHtml += html[i];
        }
    }
    return decodedHtml;
}

int main()
{
    std::string html;
    getline(std::cin, html);
    std::cout << HtmlDecode(html) << std::endl;
}
