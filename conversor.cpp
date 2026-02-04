#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) return "";
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::string bundle(std::string html, const std::string& baseDir) {
    size_t pos = 0;
    // Incrustar CSS
    while ((pos = html.find("<link rel=\"stylesheet\"", pos)) != std::string::npos) {
        size_t hrefPos = html.find("href=\"", pos) + 6;
        size_t hrefEnd = html.find("\"", hrefPos);
        std::string fileName = html.substr(hrefPos, hrefEnd - hrefPos);
        std::string css = readFile(baseDir + fileName);
        html.replace(pos, html.find(">", pos) - pos + 1, "<style>" + css + "</style>");
    }
    pos = 0;
    // Incrustar JS
    while ((pos = html.find("<script src=\"", pos)) != std::string::npos) {
        size_t srcPos = pos + 13;
        size_t srcEnd = html.find("\"", srcPos);
        std::string fileName = html.substr(srcPos, srcEnd - srcPos);
        std::string js = readFile(baseDir + fileName);
        html.replace(pos, html.find("></script>", pos) - pos + 10, "<script>" + js + "</script>");
    }
    return html;
}

std::string toDataUri(const std::string& content) {
    std::string encoded = "data:text/html,";
    const char* hex = "0123456789ABCDEF";
    for (unsigned char c : content) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') encoded += c;
        else {
            encoded += '%';
            encoded += hex[c >> 4];
            encoded += hex[c & 0xF];
        }
    }
    return encoded;
}

int main() {
    std::string html = readFile("local/index.html");
    if (html.empty()) {
        std::cerr << "Error: No se encontro local/index.html" << std::endl;
        return 1;
    }

    std::string bundled = bundle(html, "local/");
    std::string finalUri = toDataUri(bundled);

    std::ofstream out("uri.txt");
    out << finalUri;
    std::cout << "Data URI generado en uri.txt (Listo para copiar)" << std::endl;
    return 0;
}