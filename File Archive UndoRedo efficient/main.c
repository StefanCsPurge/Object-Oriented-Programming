#include "tests.h"
#include "UI.h"
#include <crtdbg.h>


int main() {
    runAllTests();

    Repository* repo = createRepo();
    Controller* ctrl = createController(repo);
    UI* ui = createUI(ctrl);
    MyConsole(ui);

    destroyUI(ui);
    destroyController(ctrl);
    destroyRepository(repo);
    _CrtDumpMemoryLeaks(); // returns 1 if there was a memory leak
    return 0;
}
