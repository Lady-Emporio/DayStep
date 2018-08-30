#include "widget.h"
#include <QApplication>
#include <windows.h>

HHOOK hHook = NULL;

LRESULT CALLBACK MyLowLevelKeyBoardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT cKey = *((KBDLLHOOKSTRUCT*)lParam);
    int key=cKey.vkCode;


    if (wParam == WM_KEYDOWN ){
        int realkey=staticVariable::GetStatic()->w->keyToRealValue(key);
        if(-1==realkey){
                staticVariable::GetStatic()->w->soundError(1);
            return 1;
        }
        staticVariable::GetStatic()->w->inputValue(realkey);
        return 1;
    }
    return 1;

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget * w=staticVariable::GetStatic()->w;
    w->show();
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, MyLowLevelKeyBoardProc, NULL, 0);
    if (hHook == NULL)
    {
        QMessageBox msgBox;
        msgBox.setText("Hook Failed");
        msgBox.exec();
    }
    return a.exec();
}
