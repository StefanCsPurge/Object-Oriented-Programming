//
// Created by M Stefan on 3/2/2020.
//
#include "UI.h"

UI* createUI(Controller* ctrl)
{
    UI* ui = malloc(sizeof(UI));
    ui->ctrl = ctrl;
    return ui;
}

void destroyUI(UI* ui)
{
    free(ui);
}

void printFile(File* f) {
    printf("archiveCatalogueNumber: %d, stateOfDeterioration: %s, fileType: %s, yearOfCreation: %d\n",
           f->id, f->dState, f->type, f->creationYear);
}

void printFiles(DynamicVector v)
{
    for (int i = 0; i < v.len; i++)
        printFile(v.elements[i]);
}

int isNumber(char *s) {
    unsigned int n = strlen(s);
    for (int i = 0; i < n; i++)
        if (!isdigit(s[i]))
            return 0;
    return 1;
}

void UI_filterFiles(UI* ui, char *criteria) {

    if (isNumber(criteria)) {
        int year = atoi(criteria);
        DynamicVector* v = filter_year(ui->ctrl, year);
        printFiles(*v);
        free(v->elements);
        free(v);
    } else {
        DynamicVector* v = filter_type(ui->ctrl, criteria);
        printFiles(*v);
        free(v->elements);
        free(v);
    }
}

int UI_add(UI* ui, char *cmd) {
    strtok(cmd, " ,"); /// get over the first argument of the command
    char dState[55], type[55], *t;
    t = strtok(0, " ,");
    if(!t || !isNumber(t)) return 0;
    int ID = atoi(t);
    t = strtok(0, " ,");
    if(!t) return 0;
    strcpy(dState, t);
    t = strtok(0, " ,");
    if(!t) return 0;
    strcpy(type, t);
    t = strtok(0, " ,");
    if(!t || !isNumber(t)) return 0;
    int creationYear = atoi(t);
    if (!srv_addFile(ui->ctrl, ID, dState, type, creationYear))
        printf("No!\n");
    return 1;
}

int UI_update(UI* ui, char *cmd) {
    strtok(cmd, " ,");
    char dState[55], type[55], *t;
    t = strtok(0, " ,");
    if(!t || !isNumber(t)) return 0;
    int ID = atoi(t);
    t = strtok(0, " ,");
    if(!t) return 0;
    strcpy(dState, t);
    t = strtok(0, " ,");
    if(!t) return 0;
    strcpy(type, t);
    t = strtok(0, " ,");
    if(!t || !isNumber(t)) return 0;
    int creationYear = atoi(t);
    if (!srv_updateFile(ui->ctrl, ID, dState, type, creationYear))
        printf("No!\n");
    return 1;
}

int UI_delete(UI* ui, char *cmd) {
    strtok(cmd, " ,");
    char *t = strtok(0, " ,");
    if(!t || !isNumber(t)) return 0;
    int ID = atoi(t);
    if (!srv_deleteFile(ui->ctrl, ID))
        printf("No!\n");
    return 1;
}

/// The console - program start point
/// param ui : pointer to the UI struct
void MyConsole(UI* ui) {
    while (1) {
        char tempCmd[222], fullCmd[222], *cmd;
        int validCmd = 1;
        printf(">>");
        scanf("%[^\n]%*c", fullCmd); // Here we read the command.
        strcpy(tempCmd, fullCmd);
        /// Now we extract the first word from the command.
        cmd = strtok(tempCmd, " ,");
        if (strcmp(cmd, "add") == 0)
            validCmd = UI_add(ui, fullCmd);
        else if (strcmp(cmd, "update") == 0)
            validCmd = UI_update(ui, fullCmd);
        else if (strcmp(cmd, "delete") == 0)
            validCmd = UI_delete(ui, fullCmd);
        else if (strcmp(cmd, "list") == 0) {
            cmd = strtok(0, " ,");
            if (!cmd) // we have only "list"
                printFiles(getArchive(ui->ctrl));
            else // we have "list fileType" or "list yearOfCreation"
                UI_filterFiles(ui, cmd);
        } else if (strcmp(cmd,"undo") == 0) {
            if (!srv_undo(ui->ctrl))
                printf("Undo limit reached!\n");
        }
        else if(strcmp(cmd,"redo")==0) {
            if (!srv_redo(ui->ctrl))
                printf("Redo limit reached!\n");
        }
        else if (strcmp(cmd, "exit") == 0)
            break;
        else printf("Non-existent command!\n");
        if(!validCmd)
            printf("Invalid command!\n");
    }
}