#include <iostream>
#include "../../rapidxml.hpp"
using namespace rapidxml;
int main()
{
    char text[] = R"(<Cameras When="2018-08-26 11:28:07" Count='2'>
    <Item module='capTest.dll' ExtTrigger='0' color='0' id='1' name='#1'>Here is the value of Item</Item>
    <Item module='capLinar.dll' ExtTrigger='1' shutter='4000' color='1' rotate="180" mirror="N" id='2' name='#2'/>
</Cameras>)";
    std::cout<<"The text to be parsed is:\n\"\n"<<text<<"\n\"\n\nparse...\n--------------------------------\n";

    xml_document<> doc;    // character type defaults to char
    doc.parse<0>(text);    // 0 means default parse flags
    xml_node<>* xnCameras = doc.first_node();
    std::cout << "Name of first node is '" << xnCameras->name() << "'. It has attribute:\n";
    for (xml_attribute<> *attr = xnCameras->first_attribute(); attr; attr = attr->next_attribute())
    {
        std::cout << "=> " << attr->name() << " = " << attr->value() << std::endl;
    }

    int iItemCnt = 0;
    for (xml_node<> *node = xnCameras->first_node("Item"); node; node=node->next_sibling("Item"))
    {
        iItemCnt++;
        std::cout << "\n - Item " << iItemCnt << "(" << node->value() << "):\n";
        for (xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute())
        {
            std::cout << "   => " << attr->name() << " = " << attr->value() << std::endl;
        }
    }
    
    int iCameraCnt = atoi(xnCameras->first_attribute("Count")->value());
    std::cout << "\nCheck the number of cameras " << (iCameraCnt == iItemCnt ? "OK!\n" : "FAILED!\n");
}
