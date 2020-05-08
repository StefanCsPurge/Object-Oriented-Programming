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
    printf("Memory leaks: %d",_CrtDumpMemoryLeaks()); // 1 if there was a memory leak
    return 0;
}
