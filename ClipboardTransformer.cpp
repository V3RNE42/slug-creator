#include <Windows.h>
#include <string>

std::string TransformText(const std::string& original) {
    std::string transformed;
    char prevChar = '\0';
    int charCount = 0;

    for (char c : original) {
        if ((c == ' ' || c == '\n' || c == '\r') && prevChar != '-' && charCount < 300) {
            transformed += '-';
            prevChar = '-';
            charCount++;
        }
        else if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '-') && charCount < 300) {
            // Avoid adding consecutive hyphens
            if (!(c == '-' && prevChar == '-')) {
                transformed += c;
                prevChar = c;
                charCount++;
            }
        }
    }
    // Remove extra hyphens at the end
    while (!transformed.empty() && transformed.back() == '-') {
        transformed.pop_back();
    }

    return transformed;
}

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    if (!OpenClipboard(nullptr)) {
        MessageBox(nullptr, L"Failed to open the clipboard.", L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    HANDLE hData = GetClipboardData(CF_TEXT);
    if (hData == nullptr) {
        MessageBox(nullptr, L"No text data in the clipboard.", L"Error", MB_OK | MB_ICONERROR);
        CloseClipboard();
        return 1;
    }

    char* pszText = static_cast<char*>(GlobalLock(hData));
    if (pszText == nullptr) {
        MessageBox(nullptr, L"Failed to retrieve text data.", L"Error", MB_OK | MB_ICONERROR);
        CloseClipboard();
        return 1;
    }

    std::string originalText(pszText);
    GlobalUnlock(hData);
    CloseClipboard();

    std::string transformedText = TransformText(originalText);

    if (!OpenClipboard(nullptr)) {
        MessageBox(nullptr, L"Failed to open the clipboard.", L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    EmptyClipboard();

    HGLOBAL hGlob = GlobalAlloc(GMEM_MOVEABLE, transformedText.size() + 1);
    if (hGlob == nullptr) {
        MessageBox(nullptr, L"Failed to allocate memory.", L"Error", MB_OK | MB_ICONERROR);
        CloseClipboard();
        return 1;
    }

    char* pGlobData = static_cast<char*>(GlobalLock(hGlob));
    strcpy_s(pGlobData, transformedText.size() + 1, transformedText.c_str());
    GlobalUnlock(hGlob);

    SetClipboardData(CF_TEXT, hGlob);
    CloseClipboard();

    return 0;
}
