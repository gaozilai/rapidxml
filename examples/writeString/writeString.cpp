
#include <iostream>
#include <fstream>
#include "../../rapidxml.hpp"
#include <time.h>
namespace rapidxml {
    namespace internal {
        template<class OutIt, class Ch>
        inline OutIt print_children(OutIt out, const xml_node<Ch>* node, int flags, int indent);
        template<class OutIt, class Ch>
        inline OutIt print_attributes(OutIt out, const xml_node<Ch>* node, int flags);
        template<class OutIt, class Ch>
        inline OutIt print_data_node(OutIt out, const xml_node<Ch>* node, int flags, int indent);
        template<class OutIt, class Ch>
        inline OutIt print_cdata_node(OutIt out, const xml_node<Ch>* node, int flags, int indent);
        template<class OutIt, class Ch>
        inline OutIt print_element_node(OutIt out, const xml_node<Ch>* node, int flags, int indent);
        template<class OutIt, class Ch>
        inline OutIt print_declaration_node(OutIt out, const xml_node<Ch>* node, int flags, int indent);
        template<class OutIt, class Ch>
        inline OutIt print_comment_node(OutIt out, const xml_node<Ch>* node, int flags, int indent);
        template<class OutIt, class Ch>
        inline OutIt print_doctype_node(OutIt out, const xml_node<Ch>* node, int flags, int indent);
        template<class OutIt, class Ch>
        inline OutIt print_pi_node(OutIt out, const xml_node<Ch>* node, int flags, int indent);
    }
}
#include "../../rapidxml_print.hpp"

using namespace rapidxml;

int main()
{
    char sznow[100];

#if defined(_WIN32)
    tm tmCurTime;
    __time64_t tim = _time64(NULL);
    _localtime64_s(&tmCurTime, &tim);
    strftime(sznow, sizeof(sznow), "%Y-%m-%d %H:%M:%S", &tmCurTime);
#elif defined(linux) || defined(__LYNX)
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    sprintf(sznow, "%.24s", ctime(&ts.tv_sec));
#endif

    xml_document<> doc;
    xml_node<>* ndCameras = doc.allocate_node(node_element, "Cameras");  // Set node name to node_name
    ndCameras->append_attribute(doc.allocate_attribute("When", sznow));
    ndCameras->append_attribute(doc.allocate_attribute("Count", "2"));
    doc.append_node(ndCameras);  // 插在后面

    xml_node<>* ndItem = doc.allocate_node(node_element, "Item");
    ndCameras->prepend_node(ndItem); // 从最前插入ndCameras下级，ndItem成为ndCameras的第一个子节点。
    ndItem->append_attribute(doc.allocate_attribute("module", "capLinar.dll"));
    ndItem->append_attribute(doc.allocate_attribute("ExtTrigger", "1"));
    ndItem->append_attribute(doc.allocate_attribute("shutter", "4000"));
    ndItem->append_attribute(doc.allocate_attribute("color", "1"));
    ndItem->append_attribute(doc.allocate_attribute("rotate", "180"));
    ndItem->append_attribute(doc.allocate_attribute("mirror", "N"));
    ndItem->append_attribute(doc.allocate_attribute("id", "2"));
    ndItem->append_attribute(doc.allocate_attribute("name", "#2"));

    xml_node<>* ndItem2 = doc.allocate_node(node_element, "Item", "Here is the value of Item");
    ndCameras->insert_node(ndItem, ndItem2); // 插入ndCameras下级，插在ndItem所在的位置，ndItem下移1个位置。
    ndItem2->append_attribute(doc.allocate_attribute("module", "capTest.dll"));
    ndItem2->append_attribute(doc.allocate_attribute("ExtTrigger", "0"));
    ndItem2->append_attribute(doc.allocate_attribute("color", "0"));
    ndItem2->append_attribute(doc.allocate_attribute("id", "1"));
    ndItem2->append_attribute(doc.allocate_attribute("name", "#1"));

    xml_node<> *ndGoogle = doc.allocate_node(node_element, "a", "Google");
    doc.insert_node(0, ndGoogle); // 插入doc下级，where=0 插在最后。
    ndGoogle->append_attribute(doc.allocate_attribute("href", "www.google.com"));

    char buffer[4096];                     
    char *end = print(buffer, doc, 0);     
    *end = 0;                              

    std::cout << doc;

    xml_node<>* rot = doc.allocate_node(node_pi, "xml version='1.0' encoding='GB2312'");
    doc.prepend_node(rot);  // 插在前面
    std::ofstream out("config.xml");
    out << doc;
}

