#include <windows.h>
#include <vector>
#include <string>

struct Segment {
    int row;          // row (0-index)
    int col;          // column (0-index)
    std::string text; // text segment
};

// windows procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            SetTextColor(hdc, RGB(255, 255, 255));
            SetBkMode(hdc, TRANSPARENT);

            // monospaced
            HFONT hFont = CreateFont(
                16, 0, 0, 0, FW_NORMAL,
                FALSE, FALSE, FALSE,
                ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                FIXED_PITCH | FF_DONTCARE,
                "Consolas"
            );
            HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

            // canvas res
            const int HEIGHT = 640;
            const int WIDTH  = 640;
            std::vector<std::string> canvas(HEIGHT, std::string(WIDTH, ' '));

            // win art
            std::vector<Segment> segments = {
                {0,  8,  ",.=:!!t3Z3z.,"},
                {1,  7,  ":tt:::tt333EE3"},
                {2,  7,  "Et:::ztt33EEEL @Ee.,"},
                {2, 33,  "..,"},
                {3,  6,  ";tt:::tt333EE7"},
                {3, 21,  ";EEEEEEttttt33#"},
                {4,  5,  ":Et:::zt333EEQ. $EEEEEttttt33QL"},
                {5,  5,  "it::::tt333EEF @EEEEEEttttt33F"},
                {6,  4,  ";3=*^```\"*4EEV :EEEEEEttttt33@."},
                {7,  4,  ",.=::::!t=., ` @EEEEEEtttz33QF"},
                {8,  3,  ";::::::::zt33)   \"4EEEtttji3P*"},
                {9,  2,  ":t::::::::tt33.:Z3z..  `` ,..g."},
                {10, 2,  "i::::::::zt33F AEEEtttt::::ztF"},
                {11, 1,  ";:::::::::t33V ;EEEttttt::::t3"},
                {12, 1,  "E::::::::zt33L @EEEtttt::::z3F"},
                {13, 0,  "{3=*^```\"*4E3) ;EEEtttt:::::tZ`"},
                {14, 17, "\"VEzjt:;;z>*`"}
            };

            // segments
            for (const auto& seg : segments) {
                if (seg.row < 0 || seg.row >= HEIGHT) continue;
                for (std::size_t i = 0; i < seg.text.size(); ++i) {
                    int pos = seg.col + static_cast<int>(i);
                    if (pos >= 0 && pos < WIDTH) {
                        canvas[seg.row][pos] = seg.text[i];
                    }
                }
            }

            // output each row of the canvas to the windo
            int y = 0;
            for (const auto& line : canvas) {
                TextOutA(hdc, 0, y, line.c_str(), static_cast<int>(line.size()));
                y += 20;
            }

            SelectObject(hdc, hOldFont);
            DeleteObject(hFont);

            EndPaint(hwnd, &ps);
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    const char* className = "AsciiArtWindowClass";

    // window class
    WNDCLASSEX wc = {};
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszClassName = className;

    if (!RegisterClassEx(&wc)) {
        MessageBox(nullptr, "Window Registration Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // create window
    HWND hwnd = CreateWindowEx(
        0,
        className,
        "windows ascii art <3",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400, // pos n size
        nullptr, nullptr, hInstance, nullptr
    );

    if (hwnd == nullptr) {
        MessageBox(nullptr, "Window Creation Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return static_cast<int>(msg.wParam);
}
